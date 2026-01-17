/*
 * Permission Test - 完全对齐 dsoftbus 官方测试风格
 *
 * 参考: dsoftbus/tests/cross_compile_test/softbus_with_accesstoken.cpp
 *       dsoftbus/tests/sdk/bus_center/unittest/bus_center_sdk_test.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <dlfcn.h>

// AccessToken 类型（静态链接）
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

extern "C" {
    uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
    int SetSelfTokenID(uint64_t tokenID);
    uint64_t GetSelfTokenID();
}

// dsoftbus 类型
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

// dsoftbus API 函数指针
typedef int (*RegNodeDeviceStateCb_t)(const char *pkgName, const INodeStateCb *callback);
typedef int (*GetLocalNodeDeviceInfo_t)(const char *pkgName, NodeBasicInfo *info);
typedef int (*CreateSessionServer_t)(const char *pkgName, const char *sessionName, const ISessionListener *listener);
typedef int (*RemoveSessionServer_t)(const char *pkgName, const char *sessionName);

static void* g_softbus_handle = nullptr;
static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;

// 回调
void OnNodeOnline(NodeBasicInfo *info) {
    if (info) {
        printf("[CB] Device online: %s (ID: %s)\n", info->deviceName, info->networkId);
    }
}

void OnNodeOffline(NodeBasicInfo *info) { printf("[CB] Device offline\n"); }
void OnDeviceInfoChanged(int type, NodeBasicInfo *info) { printf("[CB] Info changed\n"); }

static INodeStateCb g_nodeCallback = {
    .events = 0xFFFF,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) {
    printf("[CB] Session opened: id=%d, result=%d\n", sessionId, result);
    return 0;
}

void OnSessionClosed(int sessionId) { printf("[CB] Session closed\n"); }
void OnBytesReceived(int sessionId, const void *data, unsigned int len) { printf("[CB] Bytes: %u\n", len); }
void OnMessageReceived(int sessionId, const void *data, unsigned int len) { printf("[CB] Message: %u\n", len); }

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

// 加载 dsoftbus
bool load_softbus() {
    g_softbus_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_softbus_handle) return false;

    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_softbus_handle, "RegNodeDeviceStateCb");
    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_softbus_handle, "GetLocalNodeDeviceInfo");
    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_softbus_handle, "CreateSessionServer");
    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_softbus_handle, "RemoveSessionServer");

    return (RegNodeDeviceStateCb_func && GetLocalNodeDeviceInfo_func && CreateSessionServer_func);
}

// 权限设置（对齐官方实现）
void SetAccessTokenPermission(const char* processName) {
    printf("[Permission] Setting AccessToken (official method)...\n");

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
        .aplStr = "system_basic",  // 官方方法
    };

    uint64_t tokenId = GetAccessTokenId(&infoInstance);
    printf("[Permission] GetAccessTokenId returned: 0x%llx\n", (unsigned long long)tokenId);

    SetSelfTokenID(tokenId);
    printf("[Permission] SetSelfTokenID called\n");

    // 验证
    uint64_t currentToken = GetSelfTokenID();
    printf("[Permission] Current token: 0x%llx\n", (unsigned long long)currentToken);

    if (currentToken == tokenId) {
        printf("[Permission] ✅ Token set successfully\n");
    }
}

// 主程序（对齐官方风格）
int main() {
    printf("\n========================================\n");
    printf("  SoftBus Test (Official Style)\n");
    printf("========================================\n\n");

    // 使用官方测试的 PKG_NAME 格式
    const char *pkgName = "com.softbus.test";
    const char *sessionName = "com.softbus.test.session";

    // Step 1: 设置权限
    printf("[STEP 1] Setting AccessToken permission...\n");
    SetAccessTokenPermission(pkgName);
    printf("[OK] AccessToken set for process: %s\n\n", pkgName);

    // Step 2: 加载 dsoftbus
    printf("[STEP 2] Loading dsoftbus library...\n");
    if (!load_softbus()) {
        printf("[ERROR] Failed to load dsoftbus\n");
        return 1;
    }
    printf("[OK] dsoftbus library loaded\n\n");

    // Step 3: 测试 GetLocalNodeDeviceInfo
    printf("[STEP 3] Testing GetLocalNodeDeviceInfo...\n");
    printf("         pkgName: %s\n", pkgName);

    NodeBasicInfo info;
    memset(&info, 0, sizeof(info));
    int ret = GetLocalNodeDeviceInfo_func(pkgName, &info);

    printf("[RESULT] GetLocalNodeDeviceInfo returned: %d\n", ret);

    if (ret == 0) {
        printf("[OK] GetLocalNodeDeviceInfo SUCCESS!\n");
        printf("     Device: %s\n", info.deviceName);
        printf("     NetworkID: %s\n", info.networkId);
        printf("     DeviceTypeId: %u\n", info.deviceTypeId);
    } else if (ret == -4) {
        printf("[ERROR] SOFTBUS_PERMISSION_DENIED\n");
    } else {
        printf("[ERROR] Failed with code: %d (0x%x)\n", ret, (unsigned int)ret);
    }

    printf("\n");

    // Step 4: 测试 CreateSessionServer
    printf("[STEP 4] Testing CreateSessionServer...\n");
    printf("         pkgName: %s\n", pkgName);
    printf("         sessionName: %s\n", sessionName);

    ret = CreateSessionServer_func(pkgName, sessionName, &g_sessionListener);
    printf("[RESULT] CreateSessionServer returned: %d\n", ret);

    if (ret == 0) {
        printf("[OK] CreateSessionServer SUCCESS!\n");

        printf("\n[STEP 5] Waiting 5 seconds...\n");
        sleep(5);

        printf("\n[STEP 6] Removing session server...\n");
        ret = RemoveSessionServer_func(pkgName, sessionName);
        printf("[RESULT] RemoveSessionServer returned: %d\n", ret);
    } else {
        printf("[ERROR] Failed with code: %d (0x%x)\n", ret, (unsigned int)ret);
    }

    // Cleanup
    if (g_softbus_handle) {
        dlclose(g_softbus_handle);
    }

    printf("\n========================================\n");
    printf("  Test Complete\n");
    printf("========================================\n\n");

    return (ret == 0) ? 0 : 1;
}
