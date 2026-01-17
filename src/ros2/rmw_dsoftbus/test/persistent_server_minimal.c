/**
 * Minimal Persistent Session Server
 * Runs indefinitely waiting for connections
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>

#define PKG_NAME "rmw_dsoftbus"
#define SESSION_NAME "rmw_dsoftbus.graph"
#define SOFTBUS_LIB_PATH "/system/lib64/platformsdk/libsoftbus_client.z.so"
#define TOKEN_LIB_PATH "/system/lib64/libnativetoken.z.so"
#define SETPROC_LIB_PATH "/system/lib64/libtoken_setproc.z.so"

// ============ Token types ============

typedef struct {
    unsigned int dcapsNum;
    unsigned int permsNum;
    unsigned int aclsNum;
    const char **dcaps;
    const char **perms;
    const char **acls;
    const char *aplStr;
    const char *processName;
} NativeTokenInfoParams;

// ============ dsoftbus types ============

typedef enum {
    TYPE_BYTES = 2,
} SessionType;

typedef enum {
    LINK_TYPE_WIFI_WLAN_2G = 2,
    LINK_TYPE_MAX = 10,
} LinkType;

typedef enum {
    RAW_STREAM = 0,
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

// Token functions
typedef uint64_t (*GetAccessTokenId_t)(NativeTokenInfoParams*);
typedef int (*SetSelfTokenID_t)(uint64_t);

// dsoftbus functions
typedef int (*CreateSessionServer_t)(const char*, const char*, const ISessionListener*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);
typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);

static GetAccessTokenId_t fn_GetAccessTokenId = NULL;
static SetSelfTokenID_t fn_SetSelfTokenID = NULL;
static CreateSessionServer_t fn_CreateSessionServer = NULL;
static RemoveSessionServer_t fn_RemoveSessionServer = NULL;
static GetLocalNodeDeviceInfo_t fn_GetLocalNodeDeviceInfo = NULL;

static void *g_tokenHandle = NULL;
static void *g_setprocHandle = NULL;
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
    time_t now = time(NULL);
    printf("[%ld] [CB] OnSessionOpened: sessionId=%d, result=%d\n", 
           (long)now, sessionId, result);
    if (result == 0) {
        g_connectionCount++;
        printf("[INFO] Total connections: %d\n", g_connectionCount);
    }
    return 0;
}

static void OnSessionClosed(int sessionId)
{
    time_t now = time(NULL);
    printf("[%ld] [CB] OnSessionClosed: sessionId=%d\n", (long)now, sessionId);
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen)
{
    time_t now = time(NULL);
    g_messageCount++;
    printf("[%ld] [CB] OnBytesReceived: sessionId=%d, len=%u, data=%.*s\n",
           (long)now, sessionId, dataLen, dataLen < 256 ? dataLen : 256, (const char*)data);
    printf("[INFO] Total messages: %d\n", g_messageCount);
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen)
{
    time_t now = time(NULL);
    printf("[%ld] [CB] OnMessageReceived: sessionId=%d, len=%u\n", 
           (long)now, sessionId, dataLen);
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = NULL,
    .OnQosEvent = NULL,
};

// ============ Load libraries ============

static int LoadLibraries(void)
{
    // Load token library
    printf("[INFO] Loading token library from: %s\n", TOKEN_LIB_PATH);
    g_tokenHandle = dlopen(TOKEN_LIB_PATH, RTLD_NOW | RTLD_GLOBAL);
    if (!g_tokenHandle) {
        printf("[ERROR] dlopen token failed: %s\n", dlerror());
        return -1;
    }

    fn_GetAccessTokenId = (GetAccessTokenId_t)dlsym(g_tokenHandle, "GetAccessTokenId");
    if (!fn_GetAccessTokenId) {
        printf("[ERROR] Cannot find GetAccessTokenId\n");
        return -1;
    }

    // Load setproc library
    printf("[INFO] Loading setproc library from: %s\n", SETPROC_LIB_PATH);
    g_setprocHandle = dlopen(SETPROC_LIB_PATH, RTLD_NOW | RTLD_GLOBAL);
    if (!g_setprocHandle) {
        printf("[ERROR] dlopen setproc failed: %s\n", dlerror());
        return -1;
    }

    fn_SetSelfTokenID = (SetSelfTokenID_t)dlsym(g_setprocHandle, "SetSelfTokenID");
    if (!fn_SetSelfTokenID) {
        printf("[ERROR] Cannot find SetSelfTokenID\n");
        return -1;
    }

    // Load dsoftbus library
    printf("[INFO] Loading dsoftbus library from: %s\n", SOFTBUS_LIB_PATH);
    g_softbusHandle = dlopen(SOFTBUS_LIB_PATH, RTLD_NOW | RTLD_GLOBAL);
    if (!g_softbusHandle) {
        printf("[ERROR] dlopen softbus failed: %s\n", dlerror());
        return -1;
    }

    fn_CreateSessionServer = (CreateSessionServer_t)dlsym(g_softbusHandle, "CreateSessionServer");
    fn_RemoveSessionServer = (RemoveSessionServer_t)dlsym(g_softbusHandle, "RemoveSessionServer");
    fn_GetLocalNodeDeviceInfo = (GetLocalNodeDeviceInfo_t)dlsym(g_softbusHandle, "GetLocalNodeDeviceInfo");

    if (!fn_CreateSessionServer) {
        printf("[ERROR] Cannot find CreateSessionServer\n");
        return -1;
    }

    printf("[INFO] All libraries loaded successfully\n");
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

    uint64_t tokenId = fn_GetAccessTokenId(&tokenInfo);
    printf("[INFO] GetAccessTokenId: tokenId=0x%lx\n", (unsigned long)tokenId);

    int ret = fn_SetSelfTokenID(tokenId);
    printf("[INFO] SetSelfTokenID: ret=%d\n", ret);
}

// ============ Main ============

int main(int argc, char *argv[])
{
    printf("==========================================\n");
    printf("PERSISTENT SESSION SERVER\n");
    printf("PKG_NAME: %s\n", PKG_NAME);
    printf("SESSION_NAME: %s\n", SESSION_NAME);
    printf("Start Time: %ld\n", (long)time(NULL));
    printf("==========================================\n\n");

    // Setup signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Load all libraries
    if (LoadLibraries() != 0) {
        printf("[FATAL] Cannot load required libraries!\n");
        return 1;
    }

    // Set permissions
    SetPermissions();

    // Get local node info
    NodeBasicInfo localNode = {0};
    if (fn_GetLocalNodeDeviceInfo && fn_GetLocalNodeDeviceInfo(PKG_NAME, &localNode) == 0) {
        printf("[INFO] Local device: %s\n", localNode.deviceName);
        printf("[INFO] Network ID: %s\n", localNode.networkId);
    }

    // Create session server
    printf("\n========== STARTING PERSISTENT SERVER ==========\n");

    // Clean up any existing session server
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

    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║  PERSISTENT MODE - RUNNING INDEFINITELY       ║\n");
    printf("║  Press Ctrl+C to stop                         ║\n");
    printf("║  Status report every 30 seconds               ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");

    // Run indefinitely
    int elapsed = 0;
    while (g_running) {
        sleep(5);
        elapsed += 5;
        
        if (elapsed % 30 == 0) {
            time_t now = time(NULL);
            printf("[STATUS @ %ld] Running: %d sec | Connections: %d | Messages: %d\n",
                   (long)now, elapsed, g_connectionCount, g_messageCount);
        }
    }

    // Cleanup
    printf("\n[SHUTDOWN] Cleaning up...\n");
    fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
    printf("[SERVER] Server stopped.\n");

    if (g_softbusHandle) dlclose(g_softbusHandle);
    if (g_setprocHandle) dlclose(g_setprocHandle);
    if (g_tokenHandle) dlclose(g_tokenHandle);

    printf("\n[DONE] Total: %d connections, %d messages\n", g_connectionCount, g_messageCount);
    return 0;
}
