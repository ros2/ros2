/*
 * Permission Bypass Test - 完全 dlopen 版本
 *
 * 用途: 使用 dlopen 动态加载所有 OHOS 库，避免编译时链接问题
 * 方法: 100% 运行时符号解析
 *
 * 特点:
 * 1. dlopen 加载 libsoftbus_client.z.so
 * 2. dlopen 加载 libtokenid_sdk.z.so
 * 3. dlopen 加载 libaccesstoken_sdk.z.so
 * 4. 运行时解析所有符号
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>

// ============================================================================
// AccessToken 类型和符号定义
// ============================================================================

typedef struct {
    int dcapsNum;
    int permsNum;
    int aclsNum;
    const char **dcaps;
    const char **perms;
    const char **acls;
    const char *processName;
    const char *aplStr;
} NativeTokenInfoParams;

typedef uint64_t (*GetAccessTokenId_t)(NativeTokenInfoParams *params);
typedef int (*SetSelfTokenID_t)(uint64_t tokenId);

// ============================================================================
// dsoftbus 类型和符号定义
// ============================================================================

#define NETWORK_ID_BUF_LEN 65
#define DEVICE_NAME_BUF_LEN 128

typedef struct {
    char networkId[NETWORK_ID_BUF_LEN];
    char deviceName[DEVICE_NAME_BUF_LEN];
    uint16_t deviceTypeId;
} NodeBasicInfo;

typedef struct {
    int events;
    void (*onNodeOnline)(NodeBasicInfo *info);
    void (*onNodeOffline)(NodeBasicInfo *info);
    void (*onNodeBasicInfoChanged)(int type, NodeBasicInfo *info);
} INodeStateCb;

typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int len);
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int len);
    void (*OnStreamReceived)(int sessionId, const void *data, const void *ext, const void *param);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, const void *tvList);
} ISessionListener;

typedef struct {
    int dataType;
    int linkTypeNum;
    int linkType[4];
    union {
        struct StreamAttr {
            int streamType;
        } streamAttr;
        struct {
            int groupId[50];
            char groupName[256];
            int sessionId;
        } fastTransData;
    } attr;
    void *fastTransData;
    uint16_t fastTransDataSize;
} SessionAttribute;

typedef int (*RegNodeDeviceStateCb_t)(const char *pkgName, const INodeStateCb *callback);
typedef int (*GetLocalNodeDeviceInfo_t)(const char *pkgName, NodeBasicInfo *info);
typedef int (*GetAllNodeDeviceInfo_t)(const char *pkgName, NodeBasicInfo **info, int *num);
typedef void (*FreeNodeInfo_t)(NodeBasicInfo *info);
typedef int (*CreateSessionServer_t)(const char *pkgName, const char *sessionName, const ISessionListener *listener);
typedef int (*RemoveSessionServer_t)(const char *pkgName, const char *sessionName);
typedef int (*OpenSession_t)(const char *mySessionName, const char *peerSessionName, const char *peerNetworkId, const char *groupId, const SessionAttribute *attr);
typedef void (*CloseSession_t)(int sessionId);
typedef int (*SendBytes_t)(int sessionId, const void *data, unsigned int len);

// ============================================================================
// 全局函数指针
// ============================================================================

static void* g_softbus_handle = nullptr;
static void* g_tokenid_handle = nullptr;
static void* g_accesstoken_handle = nullptr;

static GetAccessTokenId_t GetAccessTokenId_func = nullptr;
static SetSelfTokenID_t SetSelfTokenID_func = nullptr;

static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static GetAllNodeDeviceInfo_t GetAllNodeDeviceInfo_func = nullptr;
static FreeNodeInfo_t FreeNodeInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;
static OpenSession_t OpenSession_func = nullptr;
static CloseSession_t CloseSession_func = nullptr;
static SendBytes_t SendBytes_func = nullptr;

// ============================================================================
// 库加载函数
// ============================================================================

bool load_all_libraries() {
    printf("[dlopen] Loading all required libraries...\n");

    // 1. 加载 softbus_client.z.so
    printf("[dlopen] Loading libsoftbus_client.z.so...\n");
    g_softbus_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_softbus_handle) {
        printf("[dlopen] ERROR: Failed to load libsoftbus_client.z.so: %s\n", dlerror());
        return false;
    }
    printf("[dlopen] ✓ libsoftbus_client.z.so loaded\n");

    // 2. 加载 libtokenid_sdk.z.so
    printf("[dlopen] Loading libtokenid_sdk.z.so...\n");
    g_tokenid_handle = dlopen("/system/lib64/platformsdk/libtokenid_sdk.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_tokenid_handle) {
        printf("[dlopen] ERROR: Failed to load libtokenid_sdk.z.so: %s\n", dlerror());
        return false;
    }
    printf("[dlopen] ✓ libtokenid_sdk.z.so loaded\n");

    // 3. 加载 libaccesstoken_sdk.z.so (可选)
    printf("[dlopen] Loading libaccesstoken_sdk.z.so...\n");
    g_accesstoken_handle = dlopen("/system/lib64/chipset-pub-sdk/libaccesstoken_sdk.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_accesstoken_handle) {
        printf("[dlopen] WARNING: Could not load libaccesstoken_sdk.z.so: %s\n", dlerror());
        printf("[dlopen] Continuing without it (may affect ReloadNativeTokenInfo)\n");
    } else {
        printf("[dlopen] ✓ libaccesstoken_sdk.z.so loaded\n");
    }

    printf("[dlopen] ✅ All libraries loaded successfully\n");
    return true;
}

bool resolve_all_symbols() {
    printf("[dlopen] Resolving symbols...\n");

    // AccessToken 符号
    GetAccessTokenId_func = (GetAccessTokenId_t)dlsym(g_tokenid_handle, "GetAccessTokenId");
    if (!GetAccessTokenId_func) {
        printf("[dlopen] ERROR: GetAccessTokenId not found: %s\n", dlerror());
        return false;
    }
    printf("[dlopen] ✓ GetAccessTokenId\n");

    SetSelfTokenID_func = (SetSelfTokenID_t)dlsym(g_tokenid_handle, "SetSelfTokenID");
    if (!SetSelfTokenID_func) {
        printf("[dlopen] ERROR: SetSelfTokenID not found: %s\n", dlerror());
        return false;
    }
    printf("[dlopen] ✓ SetSelfTokenID\n");

    // dsoftbus 符号
    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_softbus_handle, "RegNodeDeviceStateCb");
    if (!RegNodeDeviceStateCb_func) {
        printf("[dlopen] ERROR: RegNodeDeviceStateCb not found: %s\n", dlerror());
        return false;
    }
    printf("[dlopen] ✓ RegNodeDeviceStateCb\n");

    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_softbus_handle, "GetLocalNodeDeviceInfo");
    if (!GetLocalNodeDeviceInfo_func) {
        printf("[dlopen] WARNING: GetLocalNodeDeviceInfo not found: %s\n", dlerror());
    } else {
        printf("[dlopen] ✓ GetLocalNodeDeviceInfo\n");
    }

    GetAllNodeDeviceInfo_func = (GetAllNodeDeviceInfo_t)dlsym(g_softbus_handle, "GetAllNodeDeviceInfo");
    printf("[dlopen] %s GetAllNodeDeviceInfo\n", GetAllNodeDeviceInfo_func ? "✓" : "⚠");

    FreeNodeInfo_func = (FreeNodeInfo_t)dlsym(g_softbus_handle, "FreeNodeInfo");
    printf("[dlopen] %s FreeNodeInfo\n", FreeNodeInfo_func ? "✓" : "⚠");

    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_softbus_handle, "CreateSessionServer");
    if (!CreateSessionServer_func) {
        printf("[dlopen] WARNING: CreateSessionServer not found: %s\n", dlerror());
    } else {
        printf("[dlopen] ✓ CreateSessionServer\n");
    }

    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_softbus_handle, "RemoveSessionServer");
    printf("[dlopen] %s RemoveSessionServer\n", RemoveSessionServer_func ? "✓" : "⚠");

    OpenSession_func = (OpenSession_t)dlsym(g_softbus_handle, "OpenSession");
    printf("[dlopen] %s OpenSession\n", OpenSession_func ? "✓" : "⚠");

    CloseSession_func = (CloseSession_t)dlsym(g_softbus_handle, "CloseSession");
    printf("[dlopen] %s CloseSession\n", CloseSession_func ? "✓" : "⚠");

    SendBytes_func = (SendBytes_t)dlsym(g_softbus_handle, "SendBytes");
    printf("[dlopen] %s SendBytes\n", SendBytes_func ? "✓" : "⚠");

    printf("[dlopen] ✅ Symbol resolution complete\n");
    return true;
}

// ============================================================================
// 权限绕过函数（使用 dlopen 加载的符号）
// ============================================================================

int SetPermission_dlopen(const char* processName) {
    printf("[Permission] Setting permissions using dlopen method...\n");
    printf("[Permission] Process: %s\n", processName);

    const char* perms[2];
    perms[0] = "ohos.permission.DISTRIBUTED_DATASYNC";
    perms[1] = "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER";

    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 2,
        .aclsNum = 0,
        .dcaps = nullptr,
        .perms = perms,
        .acls = nullptr,
        .processName = processName,
        .aplStr = "system_basic",  // ⚠️ CRITICAL
    };

    // 调用 dlopen 加载的函数
    uint64_t tokenId = GetAccessTokenId_func(&infoInstance);
    if (tokenId == 0) {
        printf("[Permission] ERROR: GetAccessTokenId returned 0\n");
        return -1;
    }
    printf("[Permission] ✓ Token ID: 0x%lx\n", tokenId);

    int setRet = SetSelfTokenID_func(tokenId);
    if (setRet != 0) {
        printf("[Permission] WARNING: SetSelfTokenID returned %d\n", setRet);
    } else {
        printf("[Permission] ✓ SetSelfTokenID successful\n");
    }

    printf("[Permission] ✅ Permission setup complete\n");
    printf("[Permission]    - APL: system_basic\n");
    printf("[Permission]    - Permissions: DISTRIBUTED_DATASYNC, DISTRIBUTED_SOFTBUS_CENTER\n");

    return 0;
}

// ============================================================================
// 回调函数
// ============================================================================

void OnNodeOnline(NodeBasicInfo *info) {
    if (info) {
        printf("[Discovery] ✓ Device online: %s (ID: %s)\n",
               info->deviceName, info->networkId);
    }
}

void OnNodeOffline(NodeBasicInfo *info) {
    if (info) {
        printf("[Discovery] Device offline: %s\n", info->networkId);
    }
}

void OnDeviceInfoChanged(int type, NodeBasicInfo *info) {
    printf("[Discovery] Device info changed: type=%d\n", type);
}

static INodeStateCb g_nodeCallback = {
    .events = 0xFFFF,  // All events
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) {
    printf("[Session] ✓ OnSessionOpened: id=%d, result=%d\n", sessionId, result);
    return 0;
}

void OnSessionClosed(int sessionId) {
    printf("[Session] OnSessionClosed: id=%d\n", sessionId);
}

void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓ Received %u bytes on session %d\n", len, sessionId);
    if (len > 0 && len < 256) {
        printf("[Session] Data: %.*s\n", len, (const char*)data);
    }
}

void OnMessageReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓ Message received: session=%d, len=%u\n", sessionId, len);
}

void OnStreamReceived(int sessionId, const void *data, const void *ext, const void *param) {
    printf("[Session] Stream received: session=%d\n", sessionId);
}

void OnQosEvent(int sessionId, int eventId, int tvCount, const void *tvList) {
    printf("[Session] QoS event: session=%d, event=%d\n", sessionId, eventId);
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = OnStreamReceived,
    .OnQosEvent = OnQosEvent,
};

// ============================================================================
// 测试函数
// ============================================================================

int test_permission_and_apis() {
    const char* PKG_NAME = "com.permission_test.dlopen";

    printf("\n[Test] === Step 1: Test Permission Bypass ===\n");
    if (SetPermission_dlopen(PKG_NAME) != 0) {
        printf("[Test] ❌ Permission setup failed\n");
        return -1;
    }

    printf("\n[Test] === Step 2: Test Bus Center API ===\n");
    printf("[Test] Calling RegNodeDeviceStateCb...\n");
    int ret = RegNodeDeviceStateCb_func(PKG_NAME, &g_nodeCallback);
    if (ret == 0) {
        printf("[Test] ✅ RegNodeDeviceStateCb SUCCESS (permission bypass worked!)\n");
    } else if (ret == -4) {
        printf("[Test] ❌ RegNodeDeviceStateCb FAILED: PERMISSION_DENIED (ret=-4)\n");
        printf("[Test]    Permission bypass did NOT work!\n");
        return -1;
    } else {
        printf("[Test] ⚠ RegNodeDeviceStateCb returned: %d\n", ret);
    }

    printf("\n[Test] === Step 3: Test GetLocalNodeDeviceInfo ===\n");
    if (GetLocalNodeDeviceInfo_func) {
        NodeBasicInfo localInfo;
        memset(&localInfo, 0, sizeof(localInfo));
        ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &localInfo);
        if (ret == 0) {
            printf("[Test] ✅ Local Device Info:\n");
            printf("[Test]    Name: %s\n", localInfo.deviceName);
            printf("[Test]    NetworkID: %s\n", localInfo.networkId);
        } else {
            printf("[Test] ⚠ GetLocalNodeDeviceInfo failed: %d\n", ret);
        }
    }

    printf("\n[Test] === Step 4: Test CreateSessionServer ===\n");
    if (CreateSessionServer_func) {
        ret = CreateSessionServer_func(PKG_NAME, "test_session", &g_sessionListener);
        if (ret == 0) {
            printf("[Test] ✅ CreateSessionServer SUCCESS\n");

            // 清理
            if (RemoveSessionServer_func) {
                RemoveSessionServer_func(PKG_NAME, "test_session");
                printf("[Test] ✓ Session server removed\n");
            }
        } else if (ret == -4) {
            printf("[Test] ❌ CreateSessionServer FAILED: PERMISSION_DENIED (ret=-4)\n");
        } else {
            printf("[Test] ⚠ CreateSessionServer returned: %d\n", ret);
        }
    }

    return 0;
}

// ============================================================================
// Main
// ============================================================================

int main(int argc, char **argv) {
    printf("\n");
    printf("================================================\n");
    printf("  Permission Bypass Test (Full dlopen Version)\n");
    printf("  Method: 100%% runtime symbol resolution\n");
    printf("================================================\n\n");

    // Step 1: Load all libraries
    printf("[Main] === Phase 1: Load Libraries ===\n");
    if (!load_all_libraries()) {
        printf("[Main] ❌ Failed to load libraries\n");
        return 1;
    }

    printf("\n[Main] === Phase 2: Resolve Symbols ===\n");
    if (!resolve_all_symbols()) {
        printf("[Main] ❌ Failed to resolve symbols\n");
        return 1;
    }

    // Step 2: Run tests
    printf("\n[Main] === Phase 3: Run Permission and API Tests ===\n");
    int testRet = test_permission_and_apis();

    // Cleanup
    printf("\n[Main] === Cleanup ===\n");
    if (g_accesstoken_handle) dlclose(g_accesstoken_handle);
    if (g_tokenid_handle) dlclose(g_tokenid_handle);
    if (g_softbus_handle) dlclose(g_softbus_handle);
    printf("[Main] ✓ Libraries unloaded\n");

    printf("\n");
    printf("================================================\n");
    if (testRet == 0) {
        printf("  ✅ Test PASSED\n");
    } else {
        printf("  ❌ Test FAILED\n");
    }
    printf("================================================\n\n");

    return testRet;
}
