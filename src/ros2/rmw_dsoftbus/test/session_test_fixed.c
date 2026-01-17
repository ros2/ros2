/**
 * Session API Test with correct PKG_NAME format
 * Uses dlopen for ALL external functions to avoid static linking issues
 * Based on graph_discovery_test_v2.c approach
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>

// Use com.xxx.xxx format - this is required by dsoftbus!
#define PKG_NAME "com.huawei.rmw"
#define SESSION_NAME "com.huawei.rmw.session"

// Library paths
#define SOFTBUS_LIB_PATH "/system/lib64/platformsdk/libsoftbus_client.z.so"
#define ACCESSTOKEN_SDK_LIB_PATH "/system/lib64/chipset-pub-sdk/libaccesstoken_sdk.z.so"
#define TOKENID_SDK_LIB_PATH "/system/lib64/platformsdk/libtokenid_sdk.z.so"

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

// ============ NativeTokenInfoParams definition (inline) ============

typedef struct {
    int dcapsNum;
    int permsNum;
    int aclsNum;
    const char **dcaps;
    const char **perms;
    const char **acls;
    const char *aplStr;
    const char *processName;
} NativeTokenInfoParams;

// ============ Function pointers ============

// dsoftbus functions
typedef int (*CreateSessionServer_t)(const char*, const char*, const ISessionListener*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);
typedef int (*OpenSession_t)(const char*, const char*, const char*, const char*, const SessionAttribute*);
typedef void (*CloseSession_t)(int);
typedef int (*SendBytes_t)(int, const void*, unsigned int);
typedef int (*GetAllNodeDeviceInfo_t)(const char*, NodeBasicInfo**, int*);
typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);
typedef void (*FreeNodeInfo_t)(NodeBasicInfo*);

// AccessToken functions
typedef uint64_t (*GetAccessTokenId_t)(NativeTokenInfoParams*);
typedef int (*SetSelfTokenID_t)(uint64_t);

static CreateSessionServer_t fn_CreateSessionServer = NULL;
static RemoveSessionServer_t fn_RemoveSessionServer = NULL;
static OpenSession_t fn_OpenSession = NULL;
static CloseSession_t fn_CloseSession = NULL;
static SendBytes_t fn_SendBytes = NULL;
static GetAllNodeDeviceInfo_t fn_GetAllNodeDeviceInfo = NULL;
static GetLocalNodeDeviceInfo_t fn_GetLocalNodeDeviceInfo = NULL;
static FreeNodeInfo_t fn_FreeNodeInfo = NULL;
static GetAccessTokenId_t fn_GetAccessTokenId = NULL;
static SetSelfTokenID_t fn_SetSelfTokenID = NULL;

static void *g_softbusHandle = NULL;
static void *g_accesstokenHandle = NULL;
static void *g_tokenidHandle = NULL;

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

// ============ Load libraries ============

static int LoadAccessTokenLibrary(void)
{
    printf("[INFO] Loading AccessToken libraries...\n");

    g_accesstokenHandle = dlopen(ACCESSTOKEN_SDK_LIB_PATH, RTLD_NOW | RTLD_GLOBAL);
    if (!g_accesstokenHandle) {
        printf("[ERROR] dlopen accesstoken_sdk failed: %s\n", dlerror());
        return -1;
    }

    g_tokenidHandle = dlopen(TOKENID_SDK_LIB_PATH, RTLD_NOW | RTLD_GLOBAL);
    if (!g_tokenidHandle) {
        printf("[ERROR] dlopen tokenid_sdk failed: %s\n", dlerror());
        return -1;
    }

    fn_GetAccessTokenId = (GetAccessTokenId_t)dlsym(g_accesstokenHandle, "GetAccessTokenId");
    fn_SetSelfTokenID = (SetSelfTokenID_t)dlsym(g_tokenidHandle, "SetSelfTokenID");

    if (!fn_GetAccessTokenId || !fn_SetSelfTokenID) {
        printf("[ERROR] Failed to load AccessToken functions\n");
        printf("  GetAccessTokenId: %p\n", fn_GetAccessTokenId);
        printf("  SetSelfTokenID: %p\n", fn_SetSelfTokenID);
        return -1;
    }

    printf("[INFO] AccessToken libraries loaded successfully\n");
    return 0;
}

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
        return -1;
    }

    printf("[INFO] dsoftbus library loaded successfully\n");
    return 0;
}

// ============ Set permissions ============

static void SetPermissions(void)
{
    printf("[INFO] Setting permissions for PKG_NAME: %s\n", PKG_NAME);

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
    printf("[INFO] GetAccessTokenId: tokenId=0x%lx\n", tokenId);

    int ret = fn_SetSelfTokenID(tokenId);
    printf("[INFO] SetSelfTokenID: ret=%d\n", ret);
}

// ============ Main test ============

int main(int argc, char *argv[])
{
    printf("==============================================\n");
    printf("Session API Test (Fixed PKG_NAME format)\n");
    printf("PKG_NAME: %s\n", PKG_NAME);
    printf("SESSION_NAME: %s\n", SESSION_NAME);
    printf("==============================================\n\n");

    // Step 1: Load AccessToken library and set permissions
    if (LoadAccessTokenLibrary() != 0) {
        printf("[FATAL] Cannot load AccessToken libraries!\n");
        return 1;
    }
    SetPermissions();

    // Step 2: Load dsoftbus library
    if (LoadSoftbusLibrary() != 0) {
        printf("[FATAL] Cannot load dsoftbus library!\n");
        return 1;
    }

    // Step 3: Get local node info (this should work)
    NodeBasicInfo localNode = {0};
    if (fn_GetLocalNodeDeviceInfo && fn_GetLocalNodeDeviceInfo(PKG_NAME, &localNode) == 0) {
        printf("[INFO] Local device: %s\n", localNode.deviceName);
        printf("[INFO] Local NetworkID: %s\n", localNode.networkId);
    } else {
        printf("[WARN] Cannot get local device info\n");
    }

    // Step 4: Get discovered devices (Discovery test)
    printf("\n[TEST] Discovery Test...\n");
    NodeBasicInfo *nodes = NULL;
    int nodeCount = 0;
    int ret = fn_GetAllNodeDeviceInfo(PKG_NAME, &nodes, &nodeCount);
    if (ret == 0) {
        printf("[PASS] Discovery: Found %d device(s)\n", nodeCount);
        for (int i = 0; i < nodeCount; i++) {
            printf("  [%d] %s (%s)\n", i, nodes[i].deviceName, nodes[i].networkId);
        }
    } else {
        printf("[FAIL] Discovery failed: ret=%d\n", ret);
    }

    // Step 5: CreateSessionServer test
    printf("\n[TEST] CreateSessionServer Test...\n");

    // Cleanup first
    if (fn_RemoveSessionServer) {
        fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
    }

    ret = fn_CreateSessionServer(PKG_NAME, SESSION_NAME, &g_sessionListener);
    printf("[RESULT] CreateSessionServer: ret=%d\n", ret);

    if (ret == 0) {
        printf("[PASS] CreateSessionServer SUCCESS!\n");

        // Step 6: If we're in client mode, try OpenSession
        if (argc > 1 && strcmp(argv[1], "client") == 0) {
            char *peerNetworkId = NULL;

            // Auto-select peer
            if (argc > 2) {
                peerNetworkId = argv[2];
            } else if (nodes && nodeCount > 0) {
                // Find a peer that's not ourselves
                for (int i = 0; i < nodeCount; i++) {
                    if (strcmp(nodes[i].networkId, localNode.networkId) != 0) {
                        peerNetworkId = nodes[i].networkId;
                        break;
                    }
                }
            }

            if (peerNetworkId) {
                printf("\n[TEST] OpenSession Test...\n");
                printf("[INFO] Target peer: %s\n", peerNetworkId);

                SessionAttribute attr = {
                    .dataType = TYPE_BYTES,
                    .linkTypeNum = 1,
                    .linkType = {LINK_TYPE_WIFI_WLAN_2G},
                };

                int sessionId = fn_OpenSession(SESSION_NAME, SESSION_NAME, peerNetworkId, "defaultGroup", &attr);
                printf("[RESULT] OpenSession: sessionId=%d\n", sessionId);

                if (sessionId >= 0) {
                    printf("[PASS] OpenSession SUCCESS!\n");

                    // Wait for connection
                    printf("[INFO] Waiting for session to open...\n");
                    for (int i = 0; i < 10 && !g_sessionOpened; i++) {
                        sleep(1);
                    }

                    if (g_sessionOpened) {
                        // Send test message
                        const char *msg = "Hello from session test!";
                        ret = fn_SendBytes(sessionId, msg, strlen(msg));
                        printf("[RESULT] SendBytes: ret=%d\n", ret);
                    }

                    fn_CloseSession(sessionId);
                } else {
                    printf("[FAIL] OpenSession failed!\n");
                }
            }
        } else {
            // Server mode - wait for connections
            printf("\n[SERVER] Waiting for connections (30 seconds)...\n");
            for (int i = 0; i < 30; i++) {
                if (g_dataReceived) {
                    printf("[SERVER] Data received!\n");
                    break;
                }
                sleep(1);
                if (i % 10 == 0) {
                    printf("[SERVER] Waiting... %d seconds\n", i);
                }
            }
        }

        fn_RemoveSessionServer(PKG_NAME, SESSION_NAME);
    } else {
        printf("[FAIL] CreateSessionServer failed with error: %d\n", ret);

        // Decode error
        if (ret == -426442743) {
            printf("[ERROR] SOFTBUS_ACCESS_TOKEN_DENIED - Token permission check failed\n");
        } else if (ret == -426442706) {
            printf("[ERROR] SOFTBUS_NO_INIT - Session server not initialized\n");
        }
    }

    // Cleanup
    if (nodes && fn_FreeNodeInfo) {
        fn_FreeNodeInfo(nodes);
    }

    if (g_softbusHandle) dlclose(g_softbusHandle);
    if (g_accesstokenHandle) dlclose(g_accesstokenHandle);
    if (g_tokenidHandle) dlclose(g_tokenidHandle);

    printf("\n[DONE] Test completed\n");
    return ret;
}
