/*
 * 跨设备 Session 通信测试
 *
 * 用法:
 *   设备 1（Server）: ./cross_device_session_test server
 *   设备 2（Client）: ./cross_device_session_test client <设备1的NetworkID>
 */

#include <stdio.h>
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
    int (*OnSessionOpened)(int, int);
    void (*OnSessionClosed)(int);
    void (*OnBytesReceived)(int, const void *, unsigned int);
    void (*OnMessageReceived)(int, const void *, unsigned int);
    void *OnStreamReceived;
    void *OnQosEvent;
} ISessionListener;

typedef struct {
    int dataType;
    int linkTypeNum;
    int linkType[4];
} SessionAttribute;

// API 函数指针
typedef int (*GetLocalNodeDeviceInfo_t)(const char *, NodeBasicInfo *);
typedef int (*CreateSessionServer_t)(const char *, const char *, const ISessionListener *);
typedef int (*RemoveSessionServer_t)(const char *, const char *);
typedef int (*OpenSession_t)(const char *, const char *, const char *, const char *, const SessionAttribute *);
typedef int (*SendBytes_t)(int, const void *, unsigned int);
typedef void (*CloseSession_t)(int);

static void* g_handle = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;
static OpenSession_t OpenSession_func = nullptr;
static SendBytes_t SendBytes_func = nullptr;
static CloseSession_t CloseSession_func = nullptr;

const char* PKG_NAME = "com.huawei.ros2_rmw_dsoftbus";
const char* SESSION_NAME = "com.huawei.ros2_rmw_dsoftbus.cross_device";

static int g_sessionId = -1;
static bool g_sessionOpened = false;

// 回调
void OnNodeOnline(NodeBasicInfo *info) {
    if (info) {
        printf("[Discovery] ✓✓✓ Peer online: %s\n", info->deviceName);
        printf("[Discovery]     NetworkID: %.40s...\n", info->networkId);
    }
}

void OnNodeOffline(NodeBasicInfo *info) {}
void OnDeviceInfoChanged(int type, NodeBasicInfo *info) {}

static INodeStateCb g_nodeCallback = {
    0xFFFF,
    OnNodeOnline,
    OnNodeOffline,
    OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) {
    printf("[Session] ✓✓✓ Session OPENED: id=%d, result=%d\n", sessionId, result);
    if (result == 0) {
        g_sessionId = sessionId;
        g_sessionOpened = true;
    }
    return 0;
}

void OnSessionClosed(int sessionId) {
    printf("[Session] Session CLOSED: id=%d\n", sessionId);
    if (g_sessionId == sessionId) {
        g_sessionId = -1;
        g_sessionOpened = false;
    }
}

void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓✓✓ RECEIVED %u bytes on session %d\n", len, sessionId);
    if (data && len > 0 && len < 256) {
        printf("[Data] \"%.*s\"\n", len, (const char*)data);
    }
}

void OnMessageReceived(int sessionId, const void *data, unsigned int len) {}

static ISessionListener g_listener = {
    OnSessionOpened,
    OnSessionClosed,
    OnBytesReceived,
    OnMessageReceived,
    nullptr,
    nullptr,
};

int main(int argc, char *argv[]) {
    bool isServer = (argc > 1 && strcmp(argv[1], "server") == 0);
    bool isClient = (argc > 1 && strcmp(argv[1], "client") == 0);
    const char* peerNetworkId = (argc > 2) ? argv[2] : nullptr;

    printf("\n");
    printf("=======================================================\n");
    printf("  Cross-Device Session Communication Test\n");
    printf("  Mode: %s\n", isServer ? "Server" : (isClient ? "Client" : "Auto"));
    printf("=======================================================\n\n");

    // Step 1: 权限设置
    printf("[Step 1] Setup Permission\n");
    const char* perms[2] = {
        "ohos.permission.DISTRIBUTED_DATASYNC",
        "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
    };
    NativeTokenInfoParams params;
    params.dcapsNum = 0;
    params.permsNum = 2;
    params.aclsNum = 0;
    params.dcaps = nullptr;
    params.perms = perms;
    params.acls = nullptr;
    params.processName = PKG_NAME;
    params.aplStr = "system_basic";

    uint64_t tokenId = GetAccessTokenId(&params);
    printf("[Permission] Token: 0x%llx\n", (unsigned long long)tokenId);
    SetSelfTokenID(tokenId);
    printf("[Permission] ✅ Setup complete\n\n");

    // Step 2: 加载 dsoftbus
    printf("[Step 2] Load DSoftBus\n");
    g_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_handle) {
        printf("ERROR: %s\n", dlerror());
        return 1;
    }

    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_handle, "GetLocalNodeDeviceInfo");
    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_handle, "CreateSessionServer");
    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_handle, "RemoveSessionServer");
    OpenSession_func = (OpenSession_t)dlsym(g_handle, "OpenSession");
    SendBytes_func = (SendBytes_t)dlsym(g_handle, "SendBytes");
    CloseSession_func = (CloseSession_t)dlsym(g_handle, "CloseSession");
    printf("✓ DSoftBus loaded\n\n");

    // Step 3: 获取本地信息
    printf("[Step 3] Get Local Device Info\n");
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));
    int ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &localInfo);
    if (ret == 0) {
        printf("✓ Local Device: %s\n", localInfo.deviceName);
        printf("✓ NetworkID: %s\n", localInfo.networkId);
    } else {
        printf("ERROR: GetLocalNodeDeviceInfo failed: %d\n", ret);
        return 1;
    }
    printf("\n");

    // Step 4: 创建 Session Server
    printf("[Step 4] Create Session Server\n");
    ret = CreateSessionServer_func(PKG_NAME, SESSION_NAME, &g_listener);
    if (ret == 0) {
        printf("✅ Session server created: %s\n", SESSION_NAME);
    } else {
        printf("ERROR: CreateSessionServer failed: %d\n", ret);
        return 1;
    }
    printf("\n");

    // Step 5: 如果是 Client 模式，连接到 Server
    if (isClient && peerNetworkId) {
        printf("[Step 5] Connect to Peer (Client Mode)\n");
        printf("Peer NetworkID: %.40s...\n", peerNetworkId);

        SessionAttribute attr;
        memset(&attr, 0, sizeof(attr));
        attr.dataType = 0;  // TYPE_BYTES

        sleep(2);

        int sessionId = OpenSession_func(SESSION_NAME, SESSION_NAME, peerNetworkId, nullptr, &attr);
        printf("OpenSession returned: %d\n", sessionId);

        if (sessionId >= 0) {
            printf("✅✅✅ Session opened successfully!\n");

            sleep(2);

            // 发送测试消息
            printf("\nSending test message...\n");
            const char* msg = "Hello from Client device!";
            ret = SendBytes_func(sessionId, msg, strlen(msg) + 1);
            printf("SendBytes returned: %d\n", ret);

            if (ret == 0) {
                printf("✅ Message sent successfully\n");
            }

            // 保持连接
            printf("\nKeeping session open for 10 seconds...\n");
            for (int i = 0; i < 10; i++) {
                sleep(1);
                printf(".");
            }
            printf("\n");

            CloseSession_func(sessionId);
            printf("✓ Session closed\n");
        } else {
            printf("❌ OpenSession failed: %d\n", sessionId);
        }
    } else if (isServer) {
        // Server 模式：等待连接
        printf("[Step 5] Waiting for connections (Server Mode)\n");
        printf("Keep this running and start client on another device\n\n");

        for (int i = 0; i < 30; i++) {
            printf("Waiting... %d/30s\n", i+1);
            sleep(1);

            if (g_sessionOpened) {
                printf("\n✅✅✅ Session opened by peer!\n");
                printf("Session ID: %d\n", g_sessionId);
                break;
            }
        }
    } else {
        // Auto 模式：只测试本地功能
        printf("[Step 5] Local test only (no peer connection)\n");
        printf("Waiting 5 seconds...\n");
        sleep(5);
    }

    // Cleanup
    printf("\n[Cleanup]\n");
    RemoveSessionServer_func(PKG_NAME, SESSION_NAME);
    printf("✓ Session server removed\n");

    dlclose(g_handle);

    printf("\n");
    printf("=======================================================\n");
    printf("  Test Complete\n");
    printf("=======================================================\n\n");

    return 0;
}
