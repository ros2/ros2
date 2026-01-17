// 最终测试 - 使用 com.huawei.ros2_rmw_dsoftbus

#include <stdio.h>
#include <string.h>
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
    int (*OnSessionOpened)(int, int);
    void (*OnSessionClosed)(int);
    void (*OnBytesReceived)(int, const void *, unsigned int);
    void (*OnMessageReceived)(int, const void *, unsigned int);
    void *OnStreamReceived;
    void *OnQosEvent;
} ISessionListener;

int OnSessionOpened(int id, int result) { printf("[CB] Session opened\n"); return 0; }
void OnSessionClosed(int id) { printf("[CB] Session closed\n"); }
void OnBytesReceived(int id, const void *data, unsigned int len) { printf("[CB] Bytes\n"); }
void OnMessageReceived(int id, const void *data, unsigned int len) { printf("[CB] Message\n"); }

static ISessionListener g_listener = {OnSessionOpened, OnSessionClosed, OnBytesReceived, OnMessageReceived, nullptr, nullptr};

int main() {
    const char* PKG = "com.huawei.ros2_rmw_dsoftbus";
    const char* SESSION = "com.huawei.ros2_rmw_dsoftbus.test";

    printf("\n=== RMW Test (Config: com.huawei.ros2_rmw_dsoftbus.*) ===\n\n");

    void* h = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!h) { printf("dlopen failed\n"); return 1; }

    typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);
    typedef int (*CreateSessionServer_t)(const char*, const char*, const ISessionListener*);
    typedef int (*RemoveSessionServer_t)(const char*, const char*);

    auto GetLocalNodeDeviceInfo_f = (GetLocalNodeDeviceInfo_t)dlsym(h, "GetLocalNodeDeviceInfo");
    auto CreateSessionServer_f = (CreateSessionServer_t)dlsym(h, "CreateSessionServer");
    auto RemoveSessionServer_f = (RemoveSessionServer_t)dlsym(h, "RemoveSessionServer");

    printf("[1] GetLocalNodeDeviceInfo (PKG: %s)\n", PKG);
    NodeBasicInfo info;
    memset(&info, 0, sizeof(info));
    int ret = GetLocalNodeDeviceInfo_f(PKG, &info);
    printf("    RESULT: %d\n", ret);
    if (ret == 0) {
        printf("    ✅ SUCCESS - Device: %s, NetworkID: %.20s...\n", info.deviceName, info.networkId);
    } else {
        printf("    ❌ Failed: 0x%x\n", (unsigned int)ret);
    }

    printf("\n[2] CreateSessionServer (PKG: %s, SESSION: %s)\n", PKG, SESSION);
    ret = CreateSessionServer_f(PKG, SESSION, &g_listener);
    printf("    RESULT: %d\n", ret);
    if (ret == 0) {
        printf("    🎉 SUCCESS! Session server created!\n");
        RemoveSessionServer_f(PKG, SESSION);
    } else {
        printf("    ❌ Failed: 0x%x\n", (unsigned int)ret);
    }

    dlclose(h);
    printf("\n=== Test Complete ===\n\n");
    return 0;
}
