/*
 * Standard Session API Test
 * 使用标准 Session API 进行跨设备通信测试
 * 基于 OpenHarmony auth_session_test.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdbool.h>

// 动态加载的函数指针
typedef int (*CreateSessionServer_t)(const char*, const char*, void*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);
typedef int (*OpenSession_t)(const char*, const char*, const char*, const char*, void*);
typedef void (*CloseSession_t)(int);
typedef int (*SendBytes_t)(int, const void*, unsigned int);
typedef int (*GetAllNodeDeviceInfo_t)(const char*, void**, int*);
typedef void (*FreeNodeInfo_t)(void*);

// Session Listener 结构
typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void* data, unsigned int len);
    void (*OnMessageReceived)(int sessionId, const void* data, unsigned int len);
} ISessionListener;

// SessionAttribute 结构
typedef struct {
    int dataType;        // 1=MESSAGE, 2=BYTES, 3=FILE, 4=STREAM
    int linkTypeNum;
    void *linkType;
} SessionAttribute;

// NodeBasicInfo 结构
typedef struct {
    char networkId[65];
    char deviceName[65];
    int deviceTypeId;
} NodeBasicInfo;

// 全局变量
static int g_sessionId = -1;
static bool g_sessionOpened = false;
static int g_bytesReceived = 0;

// Session 回调函数
static int OnSessionOpened(int sessionId, int result) {
    printf("\n[CALLBACK] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);
    if (result == 0) {  // SOFTBUS_OK
        g_sessionId = sessionId;
        g_sessionOpened = true;
        printf("[CALLBACK] ✅ Session opened successfully\n");
    } else {
        printf("[CALLBACK] ❌ Session open failed: %d\n", result);
    }
    return result;
}

static void OnSessionClosed(int sessionId) {
    printf("\n[CALLBACK] OnSessionClosed: sessionId=%d\n", sessionId);
    if (sessionId == g_sessionId) {
        g_sessionId = -1;
        g_sessionOpened = false;
    }
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    g_bytesReceived++;
    printf("\n[CALLBACK] OnBytesReceived: sessionId=%d, len=%u\n", sessionId, len);
    printf("[DATA] %.*s\n", len, (const char*)data);
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int len) {
    printf("\n[CALLBACK] OnMessageReceived: sessionId=%d, len=%u\n", sessionId, len);
    printf("[DATA] %.*s\n", len, (const char*)data);
}

// Listener 初始化
static ISessionListener g_listener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived
};

// 显示设备列表
static void list_devices(GetAllNodeDeviceInfo_t getAllDevices, FreeNodeInfo_t freeInfo) {
    NodeBasicInfo *devices = NULL;
    int deviceCount = 0;

    int ret = getAllDevices("com.huawei.ros2_rmw_dsoftbus", (void**)&devices, &deviceCount);
    if (ret != 0 || devices == NULL) {
        printf("[DISCOVERY] No devices found or error: %d\n", ret);
        return;
    }

    printf("\n[DISCOVERY] Found %d device(s):\n", deviceCount);
    for (int i = 0; i < deviceCount; i++) {
        printf("  [%d] %s\n", i, devices[i].deviceName);
        printf("      networkId: %s\n", devices[i].networkId);
    }

    freeInfo(devices);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  %s server              - Run as server\n", argv[0]);
        printf("  %s client <networkId>  - Run as client\n", argv[0]);
        printf("  %s list                - List devices\n", argv[0]);
        return 1;
    }

    const char *mode = argv[1];
    const char *pkgName = "com.huawei.ros2_rmw_dsoftbus";
    const char *sessionName = "com.huawei.ros2_rmw_dsoftbus.complete_test";

    printf("==============================================\n");
    printf("Standard Session API Test\n");
    printf("==============================================\n");
    printf("PKG_NAME:     %s\n", pkgName);
    printf("SESSION_NAME: %s\n", sessionName);
    printf("MODE:         %s\n", mode);
    printf("==============================================\n\n");

    // 加载 dsoftbus 库
    void* handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW);
    if (!handle) {
        printf("[ERROR] Failed to load library: %s\n", dlerror());
        return 1;
    }

    // 解析函数
    CreateSessionServer_t createServer = dlsym(handle, "CreateSessionServer");
    RemoveSessionServer_t removeServer = dlsym(handle, "RemoveSessionServer");
    OpenSession_t openSession = dlsym(handle, "OpenSession");
    CloseSession_t closeSession = dlsym(handle, "CloseSession");
    SendBytes_t sendBytes = dlsym(handle, "SendBytes");
    GetAllNodeDeviceInfo_t getAllDevices = dlsym(handle, "GetAllNodeDeviceInfo");
    FreeNodeInfo_t freeInfo = dlsym(handle, "FreeNodeInfo");

    if (!createServer || !removeServer || !openSession || !sendBytes) {
        printf("[ERROR] Failed to resolve symbols\n");
        dlclose(handle);
        return 1;
    }

    printf("[OK] Library loaded and symbols resolved\n\n");

    // List devices mode
    if (strcmp(mode, "list") == 0) {
        list_devices(getAllDevices, freeInfo);
        dlclose(handle);
        return 0;
    }

    // 创建 Session Server
    printf("[TEST] Creating Session Server...\n");
    int ret = createServer(pkgName, sessionName, &g_listener);
    printf("[TEST] CreateSessionServer returned: %d\n", ret);

    if (ret != 0 && ret != -986) {  // -986 = ALREADY_EXISTS
        printf("[ERROR] CreateSessionServer failed: %d\n", ret);
        dlclose(handle);
        return 1;
    }
    printf("[OK] Session server created\n\n");

    // Server mode
    if (strcmp(mode, "server") == 0) {
        printf("[SERVER] Waiting for incoming connections...\n");
        printf("[SERVER] Press Ctrl+C to exit\n\n");

        list_devices(getAllDevices, freeInfo);

        // 等待连接
        while (1) {
            sleep(1);
            if (g_sessionOpened && g_bytesReceived > 0) {
                // 回复消息
                const char *reply = "Server received your message!";
                printf("\n[SERVER] Sending reply...\n");
                sendBytes(g_sessionId, reply, strlen(reply) + 1);
            }
        }
    }

    // Client mode
    if (strcmp(mode, "client") == 0) {
        if (argc < 3) {
            printf("[ERROR] Client mode requires peer network ID\n");
            printf("Usage: %s client <networkId>\n", argv[0]);
            removeServer(pkgName, sessionName);
            dlclose(handle);
            return 1;
        }

        const char *peerNetworkId = argv[2];
        printf("[CLIENT] Opening session to peer...\n");
        printf("[CLIENT] Peer networkId: %s\n\n", peerNetworkId);

        list_devices(getAllDevices, freeInfo);

        // 配置 SessionAttribute
        SessionAttribute attr = {
            .dataType = 2,  // TYPE_BYTES
            .linkTypeNum = 0,
            .linkType = NULL
        };

        // 打开 Session
        printf("\n[CLIENT] Calling OpenSession...\n");
        int sessionId = openSession(sessionName, sessionName,
                                   peerNetworkId, "", &attr);
        printf("[CLIENT] OpenSession returned: %d\n", sessionId);

        if (sessionId < 0) {
            printf("[ERROR] OpenSession failed: %d\n", sessionId);
            removeServer(pkgName, sessionName);
            dlclose(handle);
            return 1;
        }

        printf("[OK] Session ID: %d\n", sessionId);
        printf("[CLIENT] Waiting for session to open...\n");

        // 等待 Session 打开
        int waitCount = 0;
        while (!g_sessionOpened && waitCount < 10) {
            sleep(1);
            waitCount++;
            printf(".");
            fflush(stdout);
        }
        printf("\n");

        if (!g_sessionOpened) {
            printf("[ERROR] Session did not open in time\n");
            closeSession(sessionId);
            removeServer(pkgName, sessionName);
            dlclose(handle);
            return 1;
        }

        // 发送测试数据
        printf("\n[CLIENT] Sending test messages...\n");
        for (int i = 0; i < 5; i++) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Test message #%d from client", i + 1);

            printf("[CLIENT] Sending: %s\n", msg);
            ret = sendBytes(g_sessionId, msg, strlen(msg) + 1);
            if (ret != 0) {
                printf("[ERROR] SendBytes failed: %d\n", ret);
            } else {
                printf("[OK] Message sent\n");
            }
            sleep(1);
        }

        // 等待回复
        printf("\n[CLIENT] Waiting for replies (5 seconds)...\n");
        sleep(5);

        // 关闭 Session
        printf("\n[CLIENT] Closing session...\n");
        closeSession(sessionId);
    }

    // 清理
    printf("\n[CLEANUP] Removing session server...\n");
    removeServer(pkgName, sessionName);
    dlclose(handle);

    printf("\n==============================================\n");
    printf("Test Complete\n");
    printf("==============================================\n");

    return 0;
}
