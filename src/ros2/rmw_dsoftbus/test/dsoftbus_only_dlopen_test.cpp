/*
 * DSoftBus Only dlopen Test
 *
 * 目的: 先验证 dsoftbus API 的 dlopen 是否工作
 * 策略: 跳过 AccessToken，直接测试 dsoftbus API
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>

// ============================================================================
// dsoftbus 类型定义
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

typedef int (*OnSessionOpened_t)(int sessionId, int result);
typedef void (*OnSessionClosed_t)(int sessionId);
typedef void (*OnBytesReceived_t)(int sessionId, const void *data, unsigned int len);
typedef void (*OnMessageReceived_t)(int sessionId, const void *data, unsigned int len);

typedef struct {
    OnSessionOpened_t OnSessionOpened;
    OnSessionClosed_t OnSessionClosed;
    OnBytesReceived_t OnBytesReceived;
    OnMessageReceived_t OnMessageReceived;
    void *OnStreamReceived;
    void *OnQosEvent;
} ISessionListener;

// 函数指针类型
typedef int (*RegNodeDeviceStateCb_t)(const char *pkgName, const INodeStateCb *callback);
typedef int (*GetLocalNodeDeviceInfo_t)(const char *pkgName, NodeBasicInfo *info);
typedef int (*CreateSessionServer_t)(const char *pkgName, const char *sessionName, const ISessionListener *listener);
typedef int (*RemoveSessionServer_t)(const char *pkgName, const char *sessionName);

// 全局函数指针
static void* g_softbus_handle = nullptr;
static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;

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
    printf("[Callback] Device info changed\n");
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
    printf("[Callback] ✓ Message received: %u bytes\n", len);
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
// 主程序
// ============================================================================

int main() {
    printf("\n============================================\n");
    printf("  DSoftBus Only dlopen Test\n");
    printf("  Purpose: Verify dsoftbus API dlopen works\n");
    printf("============================================\n\n");

    const char* PKG_NAME = "com.dsoftbus_only_test";

    // Step 1: 加载 dsoftbus 库
    printf("[Step 1] Loading libsoftbus_client.z.so...\n");
    g_softbus_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_softbus_handle) {
        printf("[ERROR] Failed to load libsoftbus_client.z.so: %s\n", dlerror());
        return 1;
    }
    printf("[Step 1] ✅ libsoftbus_client.z.so loaded\n");

    // Step 2: 解析符号
    printf("\n[Step 2] Resolving dsoftbus symbols...\n");

    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_softbus_handle, "RegNodeDeviceStateCb");
    if (!RegNodeDeviceStateCb_func) {
        printf("[ERROR] RegNodeDeviceStateCb not found: %s\n", dlerror());
    } else {
        printf("[Step 2] ✓ RegNodeDeviceStateCb resolved\n");
    }

    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_softbus_handle, "GetLocalNodeDeviceInfo");
    if (!GetLocalNodeDeviceInfo_func) {
        printf("[WARNING] GetLocalNodeDeviceInfo not found: %s\n", dlerror());
    } else {
        printf("[Step 2] ✓ GetLocalNodeDeviceInfo resolved\n");
    }

    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_softbus_handle, "CreateSessionServer");
    if (!CreateSessionServer_func) {
        printf("[WARNING] CreateSessionServer not found: %s\n", dlerror());
    } else {
        printf("[Step 2] ✓ CreateSessionServer resolved\n");
    }

    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_softbus_handle, "RemoveSessionServer");
    if (!RemoveSessionServer_func) {
        printf("[WARNING] RemoveSessionServer not found: %s\n", dlerror());
    } else {
        printf("[Step 2] ✓ RemoveSessionServer resolved\n");
    }

    // Step 3: 测试 API（无权限绕过）
    printf("\n[Step 3] Testing dsoftbus APIs (WITHOUT permission bypass)...\n");
    printf("[NOTE] We expect permission errors since we're not injecting tokens\n");

    if (RegNodeDeviceStateCb_func) {
        printf("[Step 3.1] Calling RegNodeDeviceStateCb...\n");
        int ret = RegNodeDeviceStateCb_func(PKG_NAME, &g_nodeCallback);
        if (ret == 0) {
            printf("[Step 3.1] ⚠ SUCCESS (ret=0) - Unexpected! No permission check?\n");
        } else if (ret == -4) {
            printf("[Step 3.1] ✓ PERMISSION_DENIED (ret=-4) - Expected without token\n");
        } else {
            printf("[Step 3.1] Result: %d (0x%x)\n", ret, ret);
        }
    }

    if (GetLocalNodeDeviceInfo_func) {
        printf("\n[Step 3.2] Calling GetLocalNodeDeviceInfo...\n");
        NodeBasicInfo info;
        memset(&info, 0, sizeof(info));
        int ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &info);
        if (ret == 0) {
            printf("[Step 3.2] ✅ SUCCESS: Device=%s, NetworkID=%s\n",
                   info.deviceName, info.networkId);
        } else if (ret == -4) {
            printf("[Step 3.2] ✓ PERMISSION_DENIED (ret=-4) - Expected\n");
        } else {
            printf("[Step 3.2] Result: %d\n", ret);
        }
    }

    if (CreateSessionServer_func) {
        printf("\n[Step 3.3] Calling CreateSessionServer...\n");
        int ret = CreateSessionServer_func(PKG_NAME, "test_session", &g_sessionListener);
        if (ret == 0) {
            printf("[Step 3.3] ⚠ SUCCESS - Unexpected without permission!\n");
            if (RemoveSessionServer_func) {
                RemoveSessionServer_func(PKG_NAME, "test_session");
            }
        } else if (ret == -4) {
            printf("[Step 3.3] ✓ PERMISSION_DENIED (ret=-4) - Expected\n");
        } else {
            printf("[Step 3.3] Result: %d\n", ret);
        }
    }

    // Cleanup
    printf("\n[Cleanup] Unloading libraries...\n");
    if (g_softbus_handle) {
        dlclose(g_softbus_handle);
    }

    printf("\n============================================\n");
    printf("  ✅ dlopen Mechanism Test Complete\n");
    printf("  Next: Add AccessToken symbol resolution\n");
    printf("============================================\n\n");

    return 0;
}
