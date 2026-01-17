/*
 * Final Permission Test - 最简化版本
 * Token 已预注册到系统，直接测试 API
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
static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;

void OnNodeOnline(NodeBasicInfo *info) { printf("[CB] Device online\n"); }
void OnNodeOffline(NodeBasicInfo *info) { printf("[CB] Device offline\n"); }
void OnDeviceInfoChanged(int type, NodeBasicInfo *info) { printf("[CB] Info changed\n"); }

static INodeStateCb g_nodeCallback = {
    .events = 0xFFFF,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) { printf("[CB] Session opened\n"); return 0; }
void OnSessionClosed(int sessionId) { printf("[CB] Session closed\n"); }
void OnBytesReceived(int sessionId, const void *data, unsigned int len) { printf("[CB] Bytes\n"); }
void OnMessageReceived(int sessionId, const void *data, unsigned int len) { printf("[CB] Message\n"); }

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

int main() {
    const char* PKG_NAME = "com.softbus.test";  // Token 已预注册
    const char* SESSION_NAME = "com.softbus.test.session";

    printf("\n===========================================\n");
    printf("  Final Permission Test\n");
    printf("  Token Pre-registered in System\n");
    printf("===========================================\n\n");

    // 加载 dsoftbus
    printf("[1] Loading dsoftbus...\n");
    g_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_handle) {
        printf("ERROR: %s\n", dlerror());
        return 1;
    }
    printf("✓ Loaded\n");

    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_handle, "RegNodeDeviceStateCb");
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
    
    printf("    RESULT: %d (0x%x)\n", ret, (unsigned int)ret);
    
    if (ret == 0) {
        printf("    🎉🎉🎉 SUCCESS!\n");
        printf("    Device: %s\n", info.deviceName);
        printf("    NetworkID: %s\n", info.networkId);
        printf("    DeviceTypeId: %u\n", info.deviceTypeId);
    } else if (ret == -4) {
        printf("    ❌ PERMISSION_DENIED\n");
    } else {
        printf("    ⚠️  Failed with code: %d\n", ret);
    }

    // 测试 CreateSessionServer
    printf("\n[3] Test CreateSessionServer\n");
    printf("    PKG_NAME: %s\n", PKG_NAME);
    printf("    SESSION_NAME: %s\n", SESSION_NAME);
    
    ret = CreateSessionServer_func(PKG_NAME, SESSION_NAME, &g_sessionListener);
    printf("    RESULT: %d (0x%x)\n", ret, (unsigned int)ret);
    
    if (ret == 0) {
        printf("    🎉 SUCCESS! Session server created\n");
        sleep(2);
        RemoveSessionServer_func(PKG_NAME, SESSION_NAME);
        printf("    ✓ Cleaned up\n");
    } else if (ret == -4) {
        printf("    ❌ PERMISSION_DENIED\n");
    } else {
        printf("    ⚠️  Failed with code: %d\n", ret);
    }

    dlclose(g_handle);

    printf("\n===========================================\n");
    printf("  Test Complete\n");
    printf("===========================================\n\n");

    return 0;
}
