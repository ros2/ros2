/*
 * Final Test - 使用正确的 Session Name
 *
 * 修复: 使用 com.huawei.ros2_rmw_dsoftbus.* 模式的 session name
 * 匹配 /system/etc/communication/softbus/softbus_trans_permission.json
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <dlfcn.h>

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

static void* g_handle = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;

void OnNodeOnline(NodeBasicInfo *info) { if (info) printf("[CB] Device online: %s\n", info->deviceName); }
void OnNodeOffline(NodeBasicInfo *info) { printf("[CB] Device offline\n"); }
void OnDeviceInfoChanged(int type, NodeBasicInfo *info) { printf("[CB] Info changed\n"); }

static INodeStateCb g_nodeCallback = {
    .events = 0xFFFF,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) {
    printf("[CB] ✓ Session opened: id=%d, result=%d\n", sessionId, result);
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

int main() {
    // 使用匹配配置文件的 PKG_NAME 和 SESSION_NAME
    const char* PKG_NAME = "com.huawei.ros2_rmw_dsoftbus";
    const char* SESSION_NAME = "com.huawei.ros2_rmw_dsoftbus.test_session";

    printf("\n=================================================\n");
    printf("  Final Test with Correct Session Name\n");
    printf("  Matches: com.huawei.ros2_rmw_dsoftbus.*\n");
    printf("=================================================\n\n");

    // 加载 dsoftbus
    printf("[1] Loading dsoftbus...\n");
    g_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_handle) {
        printf("ERROR: %s\n", dlerror());
        return 1;
    }
    printf("✓ Loaded\n");

    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_handle, "GetLocalNodeDeviceInfo");
    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_handle, "CreateSessionServer");
    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_handle, "RemoveSessionServer");
    printf("✓ Symbols resolved\n");

    // 测试 GetLocalNodeDeviceInfo
    printf("\n[2] Test GetLocalNodeDeviceInfo\n");
    printf("    PKG_NAME: %s\n", PKG_NAME);

    NodeBasicInfo info;
    memset(&info, 0, sizeof(info));
    int ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &info);

    printf("    RESULT: %d\n", ret);

    if (ret == 0) {
        printf("    ✅ SUCCESS\n");
        printf("    Device: %s\n", info.deviceName);
        printf("    NetworkID: %s\n", info.networkId);
    } else {
        printf("    ❌ Failed: %d (0x%x)\n", ret, (unsigned int)ret);
    }

    // 测试 CreateSessionServer（使用正确的 session name）
    printf("\n[3] Test CreateSessionServer (CORRECT Session Name)\n");
    printf("    PKG_NAME: %s\n", PKG_NAME);
    printf("    SESSION_NAME: %s\n", SESSION_NAME);
    printf("    Matches config: com.huawei.ros2_rmw_dsoftbus.*\n");

    ret = CreateSessionServer_func(PKG_NAME, SESSION_NAME, &g_sessionListener);
    printf("    RESULT: %d (0x%x)\n", ret, (unsigned int)ret);

    if (ret == 0) {
        printf("    🎉🎉🎉 SUCCESS! Session server created\n");
        printf("    ✅ CreateSessionServer 完全成功！\n");

        sleep(2);

        printf("\n[4] Removing session server...\n");
        ret = RemoveSessionServer_func(PKG_NAME, SESSION_NAME);
        printf("    RESULT: %d\n", ret);
        if (ret == 0) {
            printf("    ✓ Session server removed\n");
        }
    } else if (ret == -426442743) {
        printf("    ❌ Still SOFTBUS_ACCESS_TOKEN_DENIED (session name mismatch?)\n");
    } else {
        printf("    ⚠️  Failed with code: %d\n", ret);
    }

    dlclose(g_handle);

    printf("\n=================================================\n");
    printf("  Test Complete\n");
    printf("=================================================\n\n");

    return (ret == 0) ? 0 : 1;
}
