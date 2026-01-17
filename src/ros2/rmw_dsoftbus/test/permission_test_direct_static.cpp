/*
 * Permission Test - 直接使用静态链接的 AccessToken
 *
 * 策略: 不使用 softbus_dlopen_shim 的 fallback，直接调用静态链接的符号
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <dlfcn.h>

// ============================================================================
// AccessToken 类型定义（来自 nativetoken_kit.h）
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

// 直接声明外部符号（来自静态链接的 libnativetoken.a 和 libtoken_setproc.a）
extern "C" {
    uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
    int SetSelfTokenID(uint64_t tokenID);
    uint64_t GetSelfTokenID();
}

// ============================================================================
// dsoftbus API 函数指针（通过 dlopen 加载）
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
    void *OnStreamReceived;
    void *OnQosEvent;
} ISessionListener;

typedef int (*RegNodeDeviceStateCb_t)(const char *pkgName, const INodeStateCb *callback);
typedef int (*GetLocalNodeDeviceInfo_t)(const char *pkgName, NodeBasicInfo *info);
typedef int (*CreateSessionServer_t)(const char *pkgName, const char *sessionName, const ISessionListener *listener);
typedef int (*RemoveSessionServer_t)(const char *pkgName, const char *sessionName);
typedef int (*InitSoftBus_t)(const char *pkgName);

static void* g_softbus_handle = nullptr;
static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;
static InitSoftBus_t InitSoftBus_func = nullptr;

// ============================================================================
// 回调函数
// ============================================================================

void OnNodeOnline(NodeBasicInfo *info) {
    if (info) {
        printf("[Callback] ✓ Device online: %s (ID: %s)\n",
               info->deviceName, info->networkId);
    }
}

void OnNodeOffline(NodeBasicInfo *info) {
    printf("[Callback] Device offline\n");
}

void OnDeviceInfoChanged(int type, NodeBasicInfo *info) {
    printf("[Callback] Device info changed: type=%d\n", type);
}

static INodeStateCb g_nodeCallback = {
    .events = 0xFFFF,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) {
    printf("[Callback] ✓ Session opened: id=%d, result=%d\n", sessionId, result);
    return 0;
}

void OnSessionClosed(int sessionId) {
    printf("[Callback] Session closed: id=%d\n", sessionId);
}

void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Callback] ✓ Received %u bytes\n", len);
}

void OnMessageReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Callback] ✓ Message: %u bytes\n", len);
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

// ============================================================================
// 库加载函数
// ============================================================================

bool load_softbus_library() {
    printf("[dlopen] Loading libsoftbus_client.z.so...\n");

    g_softbus_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_softbus_handle) {
        printf("[dlopen] ERROR: %s\n", dlerror());
        return false;
    }
    printf("[dlopen] ✓ libsoftbus_client.z.so loaded\n");

    // 解析符号
    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_softbus_handle, "RegNodeDeviceStateCb");
    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_softbus_handle, "GetLocalNodeDeviceInfo");
    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_softbus_handle, "CreateSessionServer");
    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_softbus_handle, "RemoveSessionServer");
    InitSoftBus_func = (InitSoftBus_t)dlsym(g_softbus_handle, "InitSoftBus");

    printf("[dlopen] ✓ Symbols resolved\n");
    return true;
}

// ============================================================================
// 权限设置（直接使用静态链接的符号）
// ============================================================================

int SetupPermissions_Direct(const char* processName) {
    printf("[Permission] Using DIRECT static-linked AccessToken functions\n");
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
        .aplStr = "system_basic",  // ✅ system_basic APL
    };

    // 直接调用静态链接的函数（不通过 shim）
    printf("[Permission] Calling GetAccessTokenId (static-linked)...\n");
    uint64_t tokenId = GetAccessTokenId(&infoInstance);
    printf("[Permission] GetAccessTokenId returned: 0x%llx\n", (unsigned long long)tokenId);

    if (tokenId == 0 || tokenId == 0x1000) {
        printf("[Permission] WARNING: Token ID looks like fallback or invalid\n");
    } else {
        printf("[Permission] ✓ Got REAL token ID (not 0x1000 fallback)\n");
    }

    printf("[Permission] Calling SetSelfTokenID (static-linked)...\n");
    int setRet = SetSelfTokenID(tokenId);
    printf("[Permission] SetSelfTokenID returned: %d\n", setRet);

    printf("[Permission] Verifying with GetSelfTokenID...\n");
    uint64_t currentToken = GetSelfTokenID();
    printf("[Permission] Current process token: 0x%llx\n", (unsigned long long)currentToken);

    if (currentToken == tokenId) {
        printf("[Permission] ✅ Token verification SUCCESS (set == get)\n");
    } else {
        printf("[Permission] ⚠ Token mismatch (set: 0x%llx, get: 0x%llx)\n",
               (unsigned long long)tokenId, (unsigned long long)currentToken);
    }

    printf("[Permission] ✅ Permission setup complete\n");
    printf("[Permission]    - APL: system_basic\n");
    printf("[Permission]    - Permissions: 2 (DATASYNC, SOFTBUS_CENTER)\n");
    printf("[Permission]    - Token ID: 0x%llx\n", (unsigned long long)tokenId);

    return 0;
}

// ============================================================================
// 主程序
// ============================================================================

int main() {
    const char* PKG_NAME = "com.permission_test.static_link";

    printf("\n");
    printf("=======================================================\n");
    printf("  Permission Test - Direct Static Link Version\n");
    printf("  AccessToken: Static-linked (libnativetoken.a)\n");
    printf("  DSoftBus: dlopen (libsoftbus_client.z.so)\n");
    printf("=======================================================\n\n");

    // Step 1: 加载 dsoftbus 库
    printf("[Step 1] Load DSoftBus Library\n");
    if (!load_softbus_library()) {
        printf("[ERROR] Failed to load softbus library\n");
        return 1;
    }

    // Step 2: 设置权限（使用静态链接的符号）
    printf("\n[Step 2] Setup Permissions (REAL AccessToken)\n");
    SetupPermissions_Direct(PKG_NAME);

    // Step 3: 初始化 SoftBus
    printf("\n[Step 3] Initialize SoftBus\n");
    if (InitSoftBus_func) {
        int ret = InitSoftBus_func(PKG_NAME);
        printf("[Step 3] InitSoftBus returned: %d\n", ret);
    }

    // Step 4: 测试 API
    printf("\n[Step 4] Test Bus Center APIs\n");
    if (RegNodeDeviceStateCb_func) {
        printf("[Step 4.1] Calling RegNodeDeviceStateCb...\n");
        int ret = RegNodeDeviceStateCb_func(PKG_NAME, &g_nodeCallback);
        if (ret == 0) {
            printf("[Step 4.1] ✅ SUCCESS (ret=0) - Permission bypass worked!\n");
        } else if (ret == -4) {
            printf("[Step 4.1] ❌ PERMISSION_DENIED (ret=-4)\n");
        } else {
            printf("[Step 4.1] Result: %d (0x%x)\n", ret, (unsigned int)ret);
        }
    }

    printf("\n[Step 5] Test GetLocalNodeDeviceInfo\n");
    if (GetLocalNodeDeviceInfo_func) {
        NodeBasicInfo localInfo;
        memset(&localInfo, 0, sizeof(localInfo));
        int ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &localInfo);
        if (ret == 0) {
            printf("[Step 5] ✅ SUCCESS\n");
            printf("[Step 5]    Device: %s\n", localInfo.deviceName);
            printf("[Step 5]    NetworkID: %s\n", localInfo.networkId);
        } else if (ret == -4) {
            printf("[Step 5] ❌ PERMISSION_DENIED (ret=-4)\n");
        } else {
            printf("[Step 5] Failed: %d (0x%x)\n", ret, (unsigned int)ret);
        }
    }

    printf("\n[Step 6] Test CreateSessionServer\n");
    if (CreateSessionServer_func) {
        int ret = CreateSessionServer_func(PKG_NAME, "test_session", &g_sessionListener);
        if (ret == 0) {
            printf("[Step 6] ✅ SUCCESS - Session server created\n");
            if (RemoveSessionServer_func) {
                RemoveSessionServer_func(PKG_NAME, "test_session");
            }
        } else if (ret == -4) {
            printf("[Step 6] ❌ PERMISSION_DENIED (ret=-4)\n");
        } else {
            printf("[Step 6] Failed: %d (0x%x)\n", ret, (unsigned int)ret);
        }
    }

    // Cleanup
    if (g_softbus_handle) {
        dlclose(g_softbus_handle);
    }

    printf("\n");
    printf("=======================================================\n");
    printf("  ✅ Test Complete\n");
    printf("=======================================================\n\n");

    return 0;
}
