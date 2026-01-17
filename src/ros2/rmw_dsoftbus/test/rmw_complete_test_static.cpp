/*
 * RMW DSoftBus Complete Test - 静态链接版本
 * 使用正确的项目配置: com.huawei.ros2_rmw_dsoftbus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <dlfcn.h>

// AccessToken（静态链接）
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

// API 函数指针
typedef int (*RegNodeDeviceStateCb_t)(const char *, const INodeStateCb *);
typedef int (*GetLocalNodeDeviceInfo_t)(const char *, NodeBasicInfo *);
typedef int (*CreateSessionServer_t)(const char *, const char *, const ISessionListener *);
typedef int (*RemoveSessionServer_t)(const char *, const char *);

static void* g_handle = nullptr;
static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;

// 回调
void OnNodeOnline(NodeBasicInfo *info) {
    if (info) printf("[CB] ✓ Device online: %s\n", info->deviceName);
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
    printf("[CB] ✓✓✓ Session opened: id=%d, result=%d\n", sessionId, result);
    return 0;
}
void OnSessionClosed(int sessionId) { printf("[CB] Session closed\n"); }
void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("[CB] ✓ Bytes: %u\n", len);
}
void OnMessageReceived(int sessionId, const void *data, unsigned int len) {
    printf("[CB] ✓ Message: %u\n", len);
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

// 权限设置
void SetupPermission(const char* processName) {
    printf("[Permission] Setting up (processName: %s)...\n", processName);

    const char* perms[2];
    perms[0] = "ohos.permission.DISTRIBUTED_DATASYNC";
    perms[1] = "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER";

    NativeTokenInfoParams params = {
        .dcapsNum = 0,
        .permsNum = 2,
        .aclsNum = 0,
        .dcaps = nullptr,
        .perms = perms,
        .acls = nullptr,
        .processName = processName,
        .aplStr = "system_basic",
    };

    uint64_t tokenId = GetAccessTokenId(&params);
    printf("[Permission] Token ID: 0x%llx\n", (unsigned long long)tokenId);

    SetSelfTokenID(tokenId);
    printf("[Permission] ✅ Permission setup complete\n");
}

// 主程序
int main() {
    // 使用正确的配置（匹配设备上的 softbus_trans_permission.json）
    const char* PKG_NAME = "com.huawei.ros2_rmw_dsoftbus";
    const char* SESSION_NAME = "com.huawei.ros2_rmw_dsoftbus.complete_test";

    printf("\n=====================================================\n");
    printf("  RMW DSoftBus Complete Test (Static Link)\n");
    printf("  PKG: %s\n", PKG_NAME);
    printf("  SESSION: %s\n", SESSION_NAME);
    printf("=====================================================\n\n");

    // Step 1: 权限
    printf("[Step 1] Setup Permission\n");
    SetupPermission(PKG_NAME);
    printf("\n");

    // Step 2: 加载 dsoftbus
    printf("[Step 2] Load DSoftBus\n");
    g_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_handle) {
        printf("ERROR: %s\n", dlerror());
        return 1;
    }

    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_handle, "RegNodeDeviceStateCb");
    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_handle, "GetLocalNodeDeviceInfo");
    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_handle, "CreateSessionServer");
    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_handle, "RemoveSessionServer");
    printf("✓ Loaded and resolved\n\n");

    // Step 3: RegNodeDeviceStateCb
    printf("[Step 3] Test RegNodeDeviceStateCb\n");
    int ret = RegNodeDeviceStateCb_func(PKG_NAME, &g_nodeCallback);
    printf("RESULT: %d\n", ret);
    if (ret == 0) printf("✅ SUCCESS\n\n");
    else printf("❌ Failed\n\n");

    // Step 4: GetLocalNodeDeviceInfo
    printf("[Step 4] Test GetLocalNodeDeviceInfo\n");
    NodeBasicInfo info;
    memset(&info, 0, sizeof(info));
    ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &info);
    printf("RESULT: %d\n", ret);

    if (ret == 0) {
        printf("✅✅✅ SUCCESS!\n");
        printf("Device: %s\n", info.deviceName);
        printf("NetworkID: %s\n", info.networkId);
        printf("TypeID: %u\n\n", info.deviceTypeId);
    } else {
        printf("❌ Failed: 0x%x\n\n", (unsigned int)ret);
    }

    // Step 5: CreateSessionServer（使用匹配配置的 session name）
    printf("[Step 5] Test CreateSessionServer\n");
    printf("SESSION: %s\n", SESSION_NAME);
    printf("Should match: com.huawei.ros2_rmw_dsoftbus.*\n");

    ret = CreateSessionServer_func(PKG_NAME, SESSION_NAME, &g_sessionListener);
    printf("RESULT: %d\n", ret);

    if (ret == 0) {
        printf("✅✅✅ SUCCESS! Session server created!\n");
        sleep(3);
        RemoveSessionServer_func(PKG_NAME, SESSION_NAME);
        printf("✓ Cleaned up\n\n");
    } else {
        printf("❌ Failed: 0x%x\n\n", (unsigned int)ret);
    }

    dlclose(g_handle);

    printf("=====================================================\n");
    printf("  Test Complete\n");
    printf("=====================================================\n\n");

    return 0;
}
