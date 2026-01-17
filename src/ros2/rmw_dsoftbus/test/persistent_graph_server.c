/**
 * Persistent Graph Server - runs indefinitely
 * Based on graph_discovery_test.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <time.h>
#include <stdint.h>
#include <signal.h>

// Token headers
#include "nativetoken_kit.h"
#include "token_setproc.h"

#define PKG_NAME "rmw_dsoftbus"
#define SESSION_NAME "rmw_dsoftbus.graph"
#define SOFTBUS_LIB_PATH "/system/lib64/platformsdk/libsoftbus_client.z.so"

// ============ dsoftbus type definitions ============

typedef enum {
    TYPE_MESSAGE = 1,
    TYPE_BYTES,
    TYPE_FILE,
    TYPE_STREAM,
    TYPE_BUTT,
} SessionType;

typedef enum {
    LINK_TYPE_WIFI_WLAN_5G = 1,
    LINK_TYPE_WIFI_WLAN_2G = 2,
    LINK_TYPE_WIFI_P2P = 3,
    LINK_TYPE_BR = 4,
    LINK_TYPE_BLE = 5,
    LINK_TYPE_WIFI_P2P_REUSE = 6,
    LINK_TYPE_BLE_DIRECT = 7,
    LINK_TYPE_COC = 8,
    LINK_TYPE_COC_DIRECT = 9,
    LINK_TYPE_MAX = 10,
} LinkType;

typedef enum {
    RAW_STREAM,
    COMMON_VIDEO_STREAM,
    COMMON_AUDIO_STREAM,
    VIDEO_SLICE_STREAM,
} StreamType;

typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnStreamReceived)(int sessionId, void *data, void *ext, void *param);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, void *tvList);
} ISessionListener;

typedef struct {
    StreamType streamType;
} StreamAttr;

typedef struct {
    int dataType;
    int linkTypeNum;
    LinkType linkType[LINK_TYPE_MAX];
    union {
        StreamAttr streamAttr;
    } attr;
} SessionAttribute;

typedef struct {
    char networkId[65];
    char deviceName[128];
    uint16_t deviceTypeId;
} NodeBasicInfo;

// ============ Function pointers ============

typedef int (*CreateSessionServer_t)(const char*, const char*, const ISessionListener*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);
typedef int (*OpenSession_t)(const char*, const char*, const char*, const char*, const SessionAttribute*);
typedef void (*CloseSession_t)(int);
typedef int (*SendBytes_t)(int, const void*, unsigned int);
typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);

static CreateSessionServer_t fn_CreateSessionServer = NULL;
static RemoveSessionServer_t fn_RemoveSessionServer = NULL;
static OpenSession_t fn_OpenSession = NULL;
static CloseSession_t fn_CloseSession = NULL;
static SendBytes_t fn_SendBytes = NULL;
static GetLocalNodeDeviceInfo_t fn_GetLocalNodeDeviceInfo = NULL;

static void *g_softbusHandle = NULL;

// ============ Global state ============

static volatile int g_running = 1;
static volatile int g_connectionCount = 0;
static volatile int g_messageCount = 0;

// ============ Signal handler ============

static void signal_handler(int sig)
{
    printf("\n[SIGNAL] Received signal %d, shutting down...\n", sig);
    g_running = 0;
}

// ============ Session callbacks ============

static int OnSessionOpened(int sessionId, int result)
{
    printf("[%d] [CB] OnSessionOpened: sessionId=%d, result=%d\n", 
           (int)time(NULL), sessionId, result);
    if (result == 0) {
        g_connectionCount++;
        printf("[INFO] Total connections: %d\n", g_connectionCount);
    }
    return 0;
}

static void OnSessionClosed(int sessionId)
{
    printf("[%d] [CB] OnSessionClosed: sessionId=%d\n", (int)time(NULL), sessionId);
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen)
{
    g_messageCount++;
    printf("[%d] [CB] OnBytesReceived: sessionId=%d, len=%u, data=%.*s\n",
           (int)time(NULL), sessionId, dataLen, dataLen, (const char*)data);
    printf("[INFO] Total messages: %d\n", g_messageCount);
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen)
{
    printf("[%d] [CB] OnMessageReceived: sessionId=%d, len=%u\n", 
           (int)time(NULL), sessionId, dataLen);
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = NULL,
    .OnQosEvent = NULL,
};

// ============ Load dsoftbus library ============

static int LoadSoftbusLibrary(void)
{
    printf("[INFO] Loading dsoftbus library from: %s\n", SOFTBUS_LIB_PATH);

    g_softbusHandle = dlopen(SOFTBUS_LIB_PATH, RTLD_NOW | RTLD_GLOBAL);
    if (!g_softbusHandle) {
        printf("[ERROR] dlopen failed: %s\n", dlerror());
        return -1;
    }

    fn_CreateSessionServer = (CreateSessionServer_t)dlsym(g_softbusHandle, "CreateSessionServer");
    fn_RemoveSessionServer = (RemoveSessionServer_t)dlsym(g_softbusHandle, "RemoveSessionServer");
    fn_OpenSession = (OpenSession_t)dlsym(g_softbusHandle, "OpenSession");
    fn_CloseSession = (CloseSession_t)dlsym(g_softbusHandle, "CloseSession");
    fn_SendBytes = (SendBytes_t)dlsym(g_softbusHandle, "SendBytes");
    fn_GetLocalNodeDeviceInfo = (GetLocalNodeDeviceInfo_t)dlsym(g_softbusHandle, "GetLocalNodeDeviceInfo");

    if (!fn_CreateSessionServer || !fn_OpenSession) {
        printf("[ERROR] Failed to load required functions\n");
        return -1;
    }

    printf("[INFO] dsoftbus library loaded successfully\n");
    printf("  CreateSessionServer: %p\n", fn_CreateSessionServer);
    printf("  OpenSession: %p\n", fn_OpenSession);

    return 0;
}

// ============ Set permissions ============

static void SetPermissions(void)
{
    printf("[INFO] Setting permissions...\n");

    const char *perms[] = {
        "ohos.permission.DISTRIBUTED_DATASYNC",
        "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
    };

    NativeTokenInfoParams tokenInfo = {
        .dcapsNum = 0,
        .permsNum = 2,
        .aclsNum = 0,
        .dcaps = NULL,
        .perms = perms,
        .acls = NULL,
        .aplStr = "system_basic",
        .processName = PKG_NAME,
    };

    uint64_t tokenId = GetAccessTokenId(&tokenInfo);
    printf("[INFO] GetAccessTokenId: tokenId=0x%lx\n", tokenId);

    int ret = SetSelfTokenID(tokenId);
    printf("[INFO] SetSelfTokenID: ret=%d\n", ret);
}

// ============ Main ============

int main(int argc, char *argv[])
{
    printf("==============================================\n");
    printf("PERSISTENT SESSION SERVER\n");
    printf("PKG_NAME: %s\n", PKG_NAME);
    printf("SESSION_NAME: %s\n", SESSION_NAME);
    printf("==============================================\n\n");

    // Setup signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Step 1: Set permissions
    SetPermissions();

    // Step 2: Load dsoftbus library
    if (LoadSoftbusLibrary() != 0) {
        printf("[FATAL] Cannot load dsoftbus library!\n");
        return 1;
    }

    // Step 3: Get local node info
    NodeBasicInfo localNode = {0};
    if (fn_GetLocalNodeDeviceInfo && fn_GetLocalNodeDeviceInfo(PKG_NAME, &localNode) == 0) {
        printf("[INFO] Local device: %s (NetworkID: %s)\n", 
               localNode.deviceName, localNode.networkId);
    }

    // Step 4: Create session server
    printf("\n========== STARTING PERSISTENT SERVER ==========\n");

    // Clean up any existing session server first
    if (fn_RemoveSessionServer) {
        int cleanRet = fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
        printf("[SERVER] RemoveSessionServer (cleanup): ret=%d\n", cleanRet);
    }

    int ret = fn_CreateSessionServer(PKG_NAME, SESSION_NAME, &g_sessionListener);
    printf("[SERVER] CreateSessionServer: ret=%d\n", ret);

    if (ret != 0) {
        printf("[ERROR] CreateSessionServer failed!\n");
        return ret;
    }

    printf("\n[INFO] PERSISTENT MODE - NO TIMEOUT\n");
    printf("[INFO] Press Ctrl+C to stop\n");
    printf("[INFO] Server will report status every 30 seconds\n\n");

    // Run indefinitely until signal
    int elapsed = 0;
    while (g_running) {
        sleep(5);
        elapsed += 5;
        
        if (elapsed % 30 == 0) {
            printf("[STATUS] Running for %d seconds | Connections: %d | Messages: %d\n",
                   elapsed, g_connectionCount, g_messageCount);
        }
    }

    // Cleanup
    fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
    printf("[SERVER] Server stopped.\n");

    if (g_softbusHandle) {
        dlclose(g_softbusHandle);
    }

    printf("\n[DONE] Connections: %d, Messages: %d\n", g_connectionCount, g_messageCount);
    return 0;
}
