/*
 * Session Server-Client 测试
 *
 * 用法:
 *   设备 A: ./session_test server
 *   设备 B: ./session_test client <设备A的NetworkID>
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <dlfcn.h>

// AccessToken
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

// dsoftbus
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

typedef struct {
    int dataType;
    int linkTypeNum;
    int linkType[4];
} SessionAttribute;

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
const char* SESSION_NAME = "com.huawei.ros2_rmw_dsoftbus.session_test";

static int g_sessionId = -1;

// 回调
int OnSessionOpened(int sessionId, int result) {
    printf("\n[Callback] ===== Session OPENED =====\n");
    printf("[Callback] Session ID: %d\n", sessionId);
    printf("[Callback] Result: %d\n", result);

    if (result == 0) {
        g_sessionId = sessionId;
        printf("[Callback] ✅ Session opened successfully!\n");
    } else {
        printf("[Callback] ❌ Session open failed\n");
    }
    printf("[Callback] ============================\n\n");
    return 0;
}

void OnSessionClosed(int sessionId) {
    printf("\n[Callback] Session CLOSED: id=%d\n\n", sessionId);
    if (g_sessionId == sessionId) {
        g_sessionId = -1;
    }
}

void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("\n[Callback] ===== Data RECEIVED =====\n");
    printf("[Callback] Session ID: %d\n", sessionId);
    printf("[Callback] Data Length: %u bytes\n", len);

    if (data && len > 0 && len < 512) {
        printf("[Callback] Data Content: \"%.*s\"\n", len, (const char*)data);
    }

    printf("[Callback] ============================\n\n");
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
    const char* peerNetworkId = (isClient && argc > 2) ? argv[2] : nullptr;

    printf("\n");
    printf("=======================================================\n");
    printf("  Session Server-Client Test\n");
    printf("  Mode: %s\n", isServer ? "SERVER" : (isClient ? "CLIENT" : "UNKNOWN"));
    if (isClient && peerNetworkId) {
        printf("  Target: %.40s...\n", peerNetworkId);
    }
    printf("=======================================================\n\n");

    // Step 1: 权限
    printf("[1] Setup Permission\n");
    const char* perms[2] = {"ohos.permission.DISTRIBUTED_DATASYNC", "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"};
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
    printf("Token: 0x%llx\n", (unsigned long long)tokenId);
    SetSelfTokenID(tokenId);
    printf("✓ Permission setup\n\n");

    // Step 2: 加载 dsoftbus
    printf("[2] Load DSoftBus\n");
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
    printf("✓ Loaded\n\n");

    // Step 3: 获取本地信息
    printf("[3] Get Local Info\n");
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));
    int ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &localInfo);
    if (ret == 0) {
        printf("Device: %s\n", localInfo.deviceName);
        printf("NetworkID: %s\n", localInfo.networkId);
    }
    printf("\n");

    // Step 4: 创建 Session Server
    printf("[4] Create Session Server\n");
    ret = CreateSessionServer_func(PKG_NAME, SESSION_NAME, &g_listener);
    printf("CreateSessionServer: %d\n", ret);

    if (ret != 0) {
        printf("ERROR: CreateSessionServer failed\n");
        return 1;
    }
    printf("✅ Session server created: %s\n\n", SESSION_NAME);

    // Step 5: Server 或 Client 模式
    if (isServer) {
        printf("[5] Server Mode - Waiting for connections\n");
        printf("Keep this running...\n");
        printf("Start client on another device with:\n");
        printf("  ./session_test client %s\n\n", localInfo.networkId);

        for (int i = 0; i < 60; i++) {
            printf("Waiting... %d/60s (Press Ctrl+C to exit)\n", i+1);
            sleep(1);

            if (g_sessionId >= 0) {
                printf("\n✅✅✅ Session opened by peer! ID=%d\n\n", g_sessionId);

                // 发送响应消息
                const char* response = "Hello from Server!";
                ret = SendBytes_func(g_sessionId, response, strlen(response) + 1);
                printf("Sent response: %d\n", ret);

                // 继续等待
                printf("Continuing to wait for more data...\n");
            }
        }

    } else if (isClient && peerNetworkId) {
        printf("[5] Client Mode - Connecting to Server\n");
        printf("Target NetworkID: %.40s...\n\n", peerNetworkId);

        sleep(2);

        SessionAttribute attr;
        memset(&attr, 0, sizeof(attr));
        attr.dataType = 0;  // TYPE_BYTES

        printf("Calling OpenSession...\n");
        int sessionId = OpenSession_func(SESSION_NAME, SESSION_NAME, peerNetworkId, nullptr, &attr);

        printf("OpenSession returned: %d\n", sessionId);

        if (sessionId >= 0) {
            printf("✅✅✅ Session opened successfully!\n");
            printf("Session ID: %d\n\n", sessionId);

            sleep(2);

            // 发送测试消息
            printf("Sending test message...\n");
            const char* msg = "Hello from Client! This is a test message.";
            ret = SendBytes_func(sessionId, msg, strlen(msg) + 1);
            printf("SendBytes: %d\n", ret);

            if (ret == 0) {
                printf("✅ Message sent successfully\n");
            }

            // 等待响应
            printf("\nWaiting for response (10 seconds)...\n");
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
    } else {
        printf("[5] No mode specified\n");
        printf("Usage:\n");
        printf("  Server: ./session_test server\n");
        printf("  Client: ./session_test client <peerNetworkID>\n");
    }

    // Cleanup
    printf("\n[Cleanup]\n");
    RemoveSessionServer_func(PKG_NAME, SESSION_NAME);
    printf("✓ Server removed\n");

    dlclose(g_handle);

    printf("\n");
    printf("=======================================================\n");
    printf("  Test Complete\n");
    printf("=======================================================\n\n");

    return 0;
}
