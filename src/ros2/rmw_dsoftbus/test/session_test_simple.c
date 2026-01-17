/**
 * Simplified Session Test - No AccessToken dependency
 * Relies on softbus_trans_permission.json configuration
 *
 * PKG_NAME and SESSION_NAME use com.huawei.* format
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>

// com.huawei.* format package name - must match softbus_trans_permission.json
#define PKG_NAME "com.huawei.rmw"
#define SESSION_NAME "com.huawei.rmw.session"

// dsoftbus library path
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
typedef int (*GetAllNodeDeviceInfo_t)(const char*, NodeBasicInfo**, int*);
typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);
typedef void (*FreeNodeInfo_t)(NodeBasicInfo*);

static CreateSessionServer_t fn_CreateSessionServer = NULL;
static RemoveSessionServer_t fn_RemoveSessionServer = NULL;
static OpenSession_t fn_OpenSession = NULL;
static CloseSession_t fn_CloseSession = NULL;
static SendBytes_t fn_SendBytes = NULL;
static GetAllNodeDeviceInfo_t fn_GetAllNodeDeviceInfo = NULL;
static GetLocalNodeDeviceInfo_t fn_GetLocalNodeDeviceInfo = NULL;
static FreeNodeInfo_t fn_FreeNodeInfo = NULL;

static void *g_softbusHandle = NULL;

// ============ Global state ============

static int g_sessionId = -1;
static volatile int g_sessionOpened = 0;
static volatile int g_dataReceived = 0;

// ============ Session callbacks ============

static int OnSessionOpened(int sessionId, int result)
{
    printf("[CB] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);
    if (result == 0) {
        g_sessionOpened = 1;
        g_sessionId = sessionId;
    }
    return 0;
}

static void OnSessionClosed(int sessionId)
{
    printf("[CB] OnSessionClosed: sessionId=%d\n", sessionId);
    g_sessionOpened = 0;
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen)
{
    printf("[CB] OnBytesReceived: sessionId=%d, len=%u, data=%.*s\n",
           sessionId, dataLen, dataLen, (const char*)data);
    g_dataReceived = 1;
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen)
{
    printf("[CB] OnMessageReceived: sessionId=%d, len=%u\n", sessionId, dataLen);
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
    fn_GetAllNodeDeviceInfo = (GetAllNodeDeviceInfo_t)dlsym(g_softbusHandle, "GetAllNodeDeviceInfo");
    fn_GetLocalNodeDeviceInfo = (GetLocalNodeDeviceInfo_t)dlsym(g_softbusHandle, "GetLocalNodeDeviceInfo");
    fn_FreeNodeInfo = (FreeNodeInfo_t)dlsym(g_softbusHandle, "FreeNodeInfo");

    if (!fn_CreateSessionServer || !fn_OpenSession || !fn_GetAllNodeDeviceInfo) {
        printf("[ERROR] Failed to load required functions\n");
        printf("  CreateSessionServer: %p\n", (void*)fn_CreateSessionServer);
        printf("  OpenSession: %p\n", (void*)fn_OpenSession);
        printf("  GetAllNodeDeviceInfo: %p\n", (void*)fn_GetAllNodeDeviceInfo);
        return -1;
    }

    printf("[INFO] dsoftbus library loaded successfully\n");
    printf("  CreateSessionServer: %p\n", (void*)fn_CreateSessionServer);
    printf("  OpenSession: %p\n", (void*)fn_OpenSession);
    printf("  GetAllNodeDeviceInfo: %p\n", (void*)fn_GetAllNodeDeviceInfo);
    printf("  GetLocalNodeDeviceInfo: %p\n", (void*)fn_GetLocalNodeDeviceInfo);

    return 0;
}

// ============ Get discovered devices ============

static int GetDiscoveredDevices(NodeBasicInfo **nodes, int *nodeCount)
{
    printf("[INFO] Getting discovered devices...\n");

    int ret = fn_GetAllNodeDeviceInfo(PKG_NAME, nodes, nodeCount);
    if (ret != 0) {
        printf("[ERROR] GetAllNodeDeviceInfo failed: ret=%d\n", ret);
        return ret;
    }

    printf("[INFO] Found %d device(s):\n", *nodeCount);
    for (int i = 0; i < *nodeCount; i++) {
        printf("  [%d] %s (NetworkID: %.20s...)\n",
               i, (*nodes)[i].deviceName, (*nodes)[i].networkId);
    }

    return 0;
}

// ============ Server mode ============

static int RunAsServer(void)
{
    printf("\n========== SERVER MODE ==========\n");
    printf("PKG_NAME: %s\n", PKG_NAME);
    printf("SESSION_NAME: %s\n", SESSION_NAME);

    // Clean up any existing session server first
    if (fn_RemoveSessionServer) {
        int cleanRet = fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
        printf("[SERVER] RemoveSessionServer (cleanup): ret=%d\n", cleanRet);
    }

    int ret = fn_CreateSessionServer(PKG_NAME, SESSION_NAME, &g_sessionListener);
    printf("[SERVER] CreateSessionServer: ret=%d\n", ret);

    if (ret != 0) {
        printf("[ERROR] CreateSessionServer failed!\n");
        printf("[ERROR] Error code analysis:\n");
        if (ret == -426442743) {
            printf("  => SOFTBUS_ACCESS_TOKEN_DENIED - Token/permission check failed\n");
            printf("  => Check softbus_trans_permission.json has PKG_NAME='%s'\n", PKG_NAME);
        } else if (ret == -426442706) {
            printf("  => SOFTBUS_NO_INIT - softbus not initialized\n");
        }
        return ret;
    }

    printf("[SERVER] Session server created successfully!\n");
    printf("[SERVER] Waiting for connections (60 seconds)...\n");

    for (int i = 0; i < 60; i++) {
        if (g_dataReceived) {
            printf("[SERVER] Data received successfully!\n");
            break;
        }
        sleep(1);
        if (i % 10 == 0) {
            printf("[SERVER] Waiting... %d seconds\n", i);
        }
    }

    fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
    printf("[SERVER] Server stopped.\n");

    return 0;
}

// ============ Client mode ============

static int RunAsClient(const char *peerNetworkId)
{
    printf("\n========== CLIENT MODE ==========\n");
    printf("PKG_NAME: %s\n", PKG_NAME);
    printf("SESSION_NAME: %s\n", SESSION_NAME);
    printf("Peer NetworkID: %s\n", peerNetworkId);

    // Clean up any existing session server first
    if (fn_RemoveSessionServer) {
        int cleanRet = fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
        printf("[CLIENT] RemoveSessionServer (cleanup): ret=%d\n", cleanRet);
    }

    int ret = fn_CreateSessionServer(PKG_NAME, SESSION_NAME, &g_sessionListener);
    printf("[CLIENT] CreateSessionServer: ret=%d\n", ret);

    if (ret != 0) {
        printf("[ERROR] CreateSessionServer failed!\n");
        return ret;
    }

    SessionAttribute attr = {
        .dataType = TYPE_BYTES,
        .linkTypeNum = 1,
        .linkType = {LINK_TYPE_WIFI_WLAN_2G},
        .attr = {.streamAttr = {.streamType = RAW_STREAM}},
    };

    printf("[CLIENT] Opening session to peer...\n");
    int sessionId = fn_OpenSession(SESSION_NAME, SESSION_NAME, peerNetworkId, "defaultGroup", &attr);
    printf("[CLIENT] OpenSession: sessionId=%d\n", sessionId);

    if (sessionId < 0) {
        printf("[ERROR] OpenSession failed!\n");
        fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
        return sessionId;
    }

    printf("[CLIENT] Waiting for session to open...\n");
    for (int i = 0; i < 10 && !g_sessionOpened; i++) {
        sleep(1);
    }

    if (!g_sessionOpened) {
        printf("[ERROR] Session did not open!\n");
        fn_CloseSession(sessionId);
        fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
        return -1;
    }

    const char *msg = "Hello from com.huawei.rmw client!";
    printf("[CLIENT] Sending: %s\n", msg);
    ret = fn_SendBytes(sessionId, msg, strlen(msg));
    printf("[CLIENT] SendBytes: ret=%d\n", ret);

    sleep(3);

    fn_CloseSession(sessionId);
    fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
    printf("[CLIENT] Client stopped.\n");

    return 0;
}

// ============ Main ============

int main(int argc, char *argv[])
{
    printf("==============================================\n");
    printf("Simplified Session Test (No AccessToken)\n");
    printf("PKG_NAME: %s\n", PKG_NAME);
    printf("SESSION_NAME: %s\n", SESSION_NAME);
    printf("==============================================\n\n");

    // Skip AccessToken setup - rely on softbus_trans_permission.json

    // Load dsoftbus library
    if (LoadSoftbusLibrary() != 0) {
        printf("[FATAL] Cannot load dsoftbus library!\n");
        return 1;
    }

    // Get local node info
    NodeBasicInfo localNode = {0};
    if (fn_GetLocalNodeDeviceInfo && fn_GetLocalNodeDeviceInfo(PKG_NAME, &localNode) == 0) {
        printf("[INFO] Local device: %s (NetworkID: %.20s...)\n", localNode.deviceName, localNode.networkId);
    } else {
        printf("[INFO] Cannot get local device info\n");
    }

    // Get discovered devices
    NodeBasicInfo *nodes = NULL;
    int nodeCount = 0;
    int ret = GetDiscoveredDevices(&nodes, &nodeCount);

    if (ret != 0 || nodeCount == 0) {
        printf("[WARN] No devices discovered. Running in server mode.\n");
    }

    // Determine mode
    int serverMode = 0;
    char *peerNetworkId = NULL;

    if (argc > 1) {
        if (strcmp(argv[1], "server") == 0 || strcmp(argv[1], "-s") == 0) {
            serverMode = 1;
        } else if (strcmp(argv[1], "client") == 0 || strcmp(argv[1], "-c") == 0) {
            serverMode = 0;
            if (argc > 2) {
                peerNetworkId = argv[2];
            }
        }
    } else {
        printf("[INFO] No mode specified. Use: %s [server|client] [networkId]\n", argv[0]);
        printf("[INFO] Running as server by default.\n");
        serverMode = 1;
    }

    // Auto-select peer if client mode
    if (!serverMode && peerNetworkId == NULL && nodes != NULL && nodeCount > 0) {
        NodeBasicInfo localInfo;
        if (fn_GetLocalNodeDeviceInfo && fn_GetLocalNodeDeviceInfo(PKG_NAME, &localInfo) == 0) {
            for (int i = 0; i < nodeCount; i++) {
                if (strcmp(nodes[i].networkId, localInfo.networkId) != 0) {
                    peerNetworkId = nodes[i].networkId;
                    printf("[INFO] Auto-selected peer: %s (%.20s...)\n",
                           nodes[i].deviceName, peerNetworkId);
                    break;
                }
            }
        } else {
            // Use first device if can't get local info
            peerNetworkId = nodes[0].networkId;
            printf("[INFO] Using first device as peer: %.20s...\n", peerNetworkId);
        }
    }

    // Run
    if (serverMode) {
        ret = RunAsServer();
    } else {
        if (peerNetworkId == NULL) {
            printf("[ERROR] No peer networkId available!\n");
            ret = -1;
        } else {
            ret = RunAsClient(peerNetworkId);
        }
    }

    // Cleanup
    if (nodes != NULL && fn_FreeNodeInfo) {
        fn_FreeNodeInfo(nodes);
    }

    if (g_softbusHandle) {
        dlclose(g_softbusHandle);
    }

    printf("\n[DONE] Exit code: %d\n", ret);
    return ret;
}
