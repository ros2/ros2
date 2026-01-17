/**
 * APL Debug Test - 测试 system_core vs system_basic APL 级别
 *
 * 尝试解决 CreateSessionServer 返回 -426442743 (SOFTBUS_ACCESS_TOKEN_DENIED) 问题
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>

// Token headers
#include "nativetoken_kit.h"
#include "token_setproc.h"

// 测试两种 PKG_NAME：com.softbus.tool (已知工作) 和我们的
#define PKG_NAME_TOOL "com.softbus.tool"
#define PKG_NAME_RMW "com.huawei.ros2_rmw_dsoftbus"

#define SESSION_NAME_TEST "com.huawei.ros2_rmw_dsoftbus.apl_test"
#define SOFTBUS_LIB_PATH "/system/lib64/platformsdk/libsoftbus_client.z.so"

// dsoftbus types
typedef enum { TYPE_MESSAGE = 1, TYPE_BYTES, TYPE_FILE, TYPE_STREAM } SessionType;
typedef enum { LINK_TYPE_WIFI_WLAN_2G = 2, LINK_TYPE_MAX = 10 } LinkType;
typedef enum { RAW_STREAM } StreamType;

typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnStreamReceived)(int sessionId, void *data, void *ext, void *param);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, void *tvList);
} ISessionListener;

typedef struct { StreamType streamType; } StreamAttr;
typedef struct {
    int dataType;
    int linkTypeNum;
    LinkType linkType[LINK_TYPE_MAX];
    union { StreamAttr streamAttr; } attr;
} SessionAttribute;

typedef struct { char networkId[65]; char deviceName[128]; uint16_t deviceTypeId; } NodeBasicInfo;

// Function pointers
typedef int (*CreateSessionServer_t)(const char*, const char*, const ISessionListener*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);
typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);

static CreateSessionServer_t fn_CreateSessionServer = NULL;
static RemoveSessionServer_t fn_RemoveSessionServer = NULL;
static GetLocalNodeDeviceInfo_t fn_GetLocalNodeDeviceInfo = NULL;

// Session callbacks (minimal)
static int OnSessionOpened(int id, int res) { printf("[CB] SessionOpened: %d, %d\n", id, res); return 0; }
static void OnSessionClosed(int id) { printf("[CB] SessionClosed: %d\n", id); }
static void OnBytesReceived(int id, const void *d, unsigned int l) { printf("[CB] Bytes: %d\n", id); }
static void OnMessageReceived(int id, const void *d, unsigned int l) { printf("[CB] Msg: %d\n", id); }

static ISessionListener g_listener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = NULL,
    .OnQosEvent = NULL,
};

static void *g_handle = NULL;

static int LoadLib(void)
{
    g_handle = dlopen(SOFTBUS_LIB_PATH, RTLD_NOW | RTLD_GLOBAL);
    if (!g_handle) {
        printf("[ERROR] dlopen: %s\n", dlerror());
        return -1;
    }
    fn_CreateSessionServer = (CreateSessionServer_t)dlsym(g_handle, "CreateSessionServer");
    fn_RemoveSessionServer = (RemoveSessionServer_t)dlsym(g_handle, "RemoveSessionServer");
    fn_GetLocalNodeDeviceInfo = (GetLocalNodeDeviceInfo_t)dlsym(g_handle, "GetLocalNodeDeviceInfo");

    if (!fn_CreateSessionServer || !fn_GetLocalNodeDeviceInfo) {
        printf("[ERROR] Missing symbols\n");
        return -1;
    }
    printf("[OK] Library loaded\n");
    return 0;
}

static void TestWithAPL(const char *pkgName, const char *aplStr)
{
    printf("\n========================================\n");
    printf("Testing: PKG=%s, APL=%s\n", pkgName, aplStr);
    printf("========================================\n");

    // Set permissions
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
        .aplStr = aplStr,
        .processName = pkgName,
    };

    uint64_t tokenId = GetAccessTokenId(&tokenInfo);
    printf("[1] GetAccessTokenId: 0x%lx (%lu)\n", tokenId, tokenId);

    int ret = SetSelfTokenID(tokenId);
    printf("[2] SetSelfTokenID: ret=%d\n", ret);

    // Small delay
    usleep(100000);

    // Test GetLocalNodeDeviceInfo (uses IPC, requires permission)
    NodeBasicInfo localNode = {0};
    ret = fn_GetLocalNodeDeviceInfo(pkgName, &localNode);
    printf("[3] GetLocalNodeDeviceInfo: ret=%d", ret);
    if (ret == 0) {
        printf(" ✅ (device=%s)\n", localNode.deviceName);
    } else {
        printf(" ❌\n");
    }

    // Generate unique session name
    char sessionName[128];
    snprintf(sessionName, sizeof(sessionName), "%s.%ld", SESSION_NAME_TEST, (long)getpid());

    // Cleanup first
    if (fn_RemoveSessionServer) {
        fn_RemoveSessionServer(pkgName, sessionName);
    }

    // Test CreateSessionServer
    ret = fn_CreateSessionServer(pkgName, sessionName, &g_listener);
    printf("[4] CreateSessionServer: ret=%d", ret);
    if (ret == 0) {
        printf(" ✅\n");
        // Cleanup
        fn_RemoveSessionServer(pkgName, sessionName);
    } else if (ret == -426442743) {
        printf(" ❌ SOFTBUS_ACCESS_TOKEN_DENIED\n");
    } else if (ret == -426442749) {
        printf(" ❌ SOFTBUS_INVALID_PARAM\n");
    } else if (ret == -426442753) {
        printf(" ❌ SOFTBUS_PERMISSION_DENIED\n");
    } else {
        printf(" ❌ (0x%x)\n", ret);
    }
}

int main(int argc, char *argv[])
{
    printf("=== APL Level Debug Test ===\n");
    printf("PID: %d, UID: %d\n", getpid(), getuid());

    if (LoadLib() != 0) {
        return 1;
    }

    // Test 1: 使用 com.softbus.tool + system_core (已知工作配置)
    TestWithAPL(PKG_NAME_TOOL, "system_core");

    // Test 2: 使用 RMW PKG_NAME + system_core
    TestWithAPL(PKG_NAME_RMW, "system_core");

    // Test 3: 使用 RMW PKG_NAME + system_basic (当前配置)
    TestWithAPL(PKG_NAME_RMW, "system_basic");

    if (g_handle) dlclose(g_handle);

    printf("\n=== Test Complete ===\n");
    return 0;
}
