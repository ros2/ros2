/*
 * Permission Bypass Test - 使用 softbus_dlopen_shim
 *
 * 策略: 利用现有的 softbus_dlopen_shim.cpp 自动加载机制
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

// 使用 softbus_dlopen_shim.cpp 提供的符号
// 它会在程序启动时自动通过 __attribute__((constructor)) 加载库

// dsoftbus 类型定义
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

// AccessToken 类型
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

// 外部符号声明（由 softbus_dlopen_shim.cpp 提供）
extern "C" {
    int RegNodeDeviceStateCb(const char *pkgName, const INodeStateCb *callback);
    int GetLocalNodeDeviceInfo(const char *pkgName, NodeBasicInfo *info);
    int CreateSessionServer(const char *pkgName, const char *sessionName, const ISessionListener *listener);
    int RemoveSessionServer(const char *pkgName, const char *sessionName);
    uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
    int SetSelfTokenID(uint64_t tokenID);
    int InitSoftBus(const char *pkgName);
}

// 权限常量
#define OHOS_PERMISSION_DISTRIBUTED_DATASYNC "ohos.permission.DISTRIBUTED_DATASYNC"
#define OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"

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
    printf("[Discovery] Device offline\n");
}

void OnDeviceInfoChanged(int type, NodeBasicInfo *info) {
    printf("[Discovery] Device info changed: type=%d\n", type);
}

static INodeStateCb g_nodeCallback = {
    .events = 0xFFFF,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) {
    printf("[Session] ✓ Session opened: id=%d, result=%d\n", sessionId, result);
    return 0;
}

void OnSessionClosed(int sessionId) {
    printf("[Session] Session closed: id=%d\n", sessionId);
}

void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓ Received %u bytes\n", len);
}

void OnMessageReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓ Message: %u bytes\n", len);
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
// 权限设置函数（使用 shim 提供的符号）
// ============================================================================

int SetupPermissions(const char* processName) {
    printf("[Permission] Setting up permissions (using softbus_dlopen_shim)...\n");
    printf("[Permission] Process: %s\n", processName);

    const char* perms[2];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;

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

    // 调用 shim 提供的函数（可能是真实的或 fallback）
    uint64_t tokenId = GetAccessTokenId(&infoInstance);
    printf("[Permission] GetAccessTokenId returned: 0x%lx\n", tokenId);

    int setRet = SetSelfTokenID(tokenId);
    printf("[Permission] SetSelfTokenID returned: %d\n", setRet);

    printf("[Permission] ✅ Permission setup complete\n");
    printf("[Permission]    - APL: system_basic\n");
    printf("[Permission]    - Permissions: 2 (DATASYNC, SOFTBUS_CENTER)\n");

    return 0;
}

// ============================================================================
// 主程序
// ============================================================================

int main() {
    const char* PKG_NAME = "com.permission_test.shim";

    printf("\n");
    printf("================================================\n");
    printf("  Permission Test (using softbus_dlopen_shim)\n");
    printf("  Auto-loads libs via __attribute__((constructor))\n");
    printf("================================================\n\n");

    // 等待库自动加载（constructor 在 main 之前执行）
    printf("[Info] Libraries should be auto-loaded by shim...\n");
    sleep(1);

    // Step 1: 设置权限
    printf("\n[Step 1] Setup Permissions\n");
    SetupPermissions(PKG_NAME);

    // Step 2: 初始化 SoftBus
    printf("\n[Step 2] Initialize SoftBus\n");
    int ret = InitSoftBus(PKG_NAME);
    printf("[Step 2] InitSoftBus returned: %d\n", ret);

    // Step 3: 测试 Bus Center API
    printf("\n[Step 3] Test Bus Center APIs\n");
    printf("[Step 3.1] Calling RegNodeDeviceStateCb...\n");
    ret = RegNodeDeviceStateCb(PKG_NAME, &g_nodeCallback);
    if (ret == 0) {
        printf("[Step 3.1] ✅ SUCCESS (ret=0) - Permission bypass worked!\n");
    } else if (ret == -4) {
        printf("[Step 3.1] ❌ PERMISSION_DENIED (ret=-4) - Permission bypass failed\n");
    } else {
        printf("[Step 3.1] Result: %d (0x%x)\n", ret, (unsigned int)ret);
    }

    // Step 4: 获取本地设备信息
    printf("\n[Step 4] Test GetLocalNodeDeviceInfo\n");
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));
    ret = GetLocalNodeDeviceInfo(PKG_NAME, &localInfo);
    if (ret == 0) {
        printf("[Step 4] ✅ SUCCESS\n");
        printf("[Step 4]    Device: %s\n", localInfo.deviceName);
        printf("[Step 4]    NetworkID: %s\n", localInfo.networkId);
    } else {
        printf("[Step 4] Failed: %d (0x%x)\n", ret, (unsigned int)ret);
    }

    // Step 5: 测试 Session API
    printf("\n[Step 5] Test Session APIs\n");
    printf("[Step 5.1] Calling CreateSessionServer...\n");
    ret = CreateSessionServer(PKG_NAME, "test_session", &g_sessionListener);
    if (ret == 0) {
        printf("[Step 5.1] ✅ SUCCESS - Session server created\n");

        // 清理
        printf("[Step 5.2] Cleaning up...\n");
        RemoveSessionServer(PKG_NAME, "test_session");
        printf("[Step 5.2] ✓ Session server removed\n");
    } else {
        printf("[Step 5.1] Failed: %d (0x%x)\n", ret, (unsigned int)ret);
    }

    printf("\n");
    printf("================================================\n");
    printf("  ✅ Test Complete\n");
    printf("================================================\n\n");

    return 0;
}
