/*
 * Persistent Session Test - 持久化 Server
 * 解决 SOFTBUS_TRANS_PEER_SESSION_NOT_CREATED 问题
 *
 * 根本原因: 之前的 Server 有超时退出机制，导致 Client 连接时 Server 已退出
 * 解决方案: Server 无限等待，直到手动 Ctrl+C 退出
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

typedef int (*CreateSessionServer_t)(const char*, const char*, void*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);
typedef int (*OpenSession_t)(const char*, const char*, const char*, const char*, void*);
typedef void (*CloseSession_t)(int);
typedef int (*SendBytes_t)(int, const void*, unsigned int);
typedef int (*GetAllNodeDeviceInfo_t)(const char*, void**, int*);
typedef void (*FreeNodeInfo_t)(void*);

typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void* data, unsigned int len);
    void (*OnMessageReceived)(int sessionId, const void* data, unsigned int len);
} ISessionListener;

typedef struct {
    int dataType;
    int linkTypeNum;
    void *linkType;
} SessionAttribute;

typedef struct {
    char networkId[65];
    char deviceName[65];
    int deviceTypeId;
} NodeBasicInfo;

// 全局变量
static int g_inboundSessionId = -1;
static int g_outboundSessionId = -1;
static int g_messagesReceived = 0;
static int g_messagesSent = 0;
static bool g_running = true;

static const char *g_pkgName = "com.huawei.ros2_rmw_dsoftbus";
static const char *g_sessionName = "com.huawei.ros2_rmw_dsoftbus.complete_test";

static SendBytes_t g_sendBytes = NULL;

// 信号处理
static void signal_handler(int sig) {
    printf("\n[SIGNAL] Received signal %d, shutting down...\n", sig);
    g_running = false;
}

// 回调函数
static int OnSessionOpened(int sessionId, int result) {
    printf("\n[CALLBACK] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);

    if (result == 0) {
        printf("[OK] Session opened successfully\n");
        if (g_inboundSessionId == -1) {
            g_inboundSessionId = sessionId;
            printf("[SERVER] Inbound session established: sessionId=%d\n", sessionId);
        } else if (g_outboundSessionId == -1) {
            g_outboundSessionId = sessionId;
            printf("[CLIENT] Outbound session established: sessionId=%d\n", sessionId);
        }
    } else {
        printf("[WARNING] Session callback failed: %d\n", result);
        printf("[INFO] This may be KH_TRANS issue, checking if sessionId is still valid...\n");

        // 即使回调失败，sessionId 可能仍然有效
        // 尝试使用该 sessionId
        if (g_outboundSessionId == -1) {
            g_outboundSessionId = sessionId;
            printf("[INFO] Saving sessionId anyway for testing: %d\n", sessionId);
        }
    }

    return result;
}

static void OnSessionClosed(int sessionId) {
    printf("\n[CALLBACK] OnSessionClosed: sessionId=%d\n", sessionId);

    if (sessionId == g_inboundSessionId) {
        g_inboundSessionId = -1;
        printf("[SERVER] Inbound session closed\n");
    } else if (sessionId == g_outboundSessionId) {
        g_outboundSessionId = -1;
        printf("[CLIENT] Outbound session closed\n");
    }
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    g_messagesReceived++;
    printf("\n[CALLBACK] OnBytesReceived #%d:\n", g_messagesReceived);
    printf("  sessionId: %d\n", sessionId);
    printf("  length: %u bytes\n", len);
    printf("  data: %.*s\n", (int)len, (const char*)data);

    // 自动回复（如果是 inbound session）
    if (sessionId == g_inboundSessionId && g_sendBytes) {
        char reply[256];
        snprintf(reply, sizeof(reply), "Server received message #%d", g_messagesReceived);
        printf("[SERVER] Sending reply: %s\n", reply);
        int ret = g_sendBytes(sessionId, reply, strlen(reply) + 1);
        printf("[SERVER] SendBytes returned: %d\n", ret);
    }
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int len) {
    printf("\n[CALLBACK] OnMessageReceived: sessionId=%d, len=%u\n", sessionId, len);
}

static ISessionListener g_listener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  %s server                 - Run persistent server (no timeout)\n", argv[0]);
        printf("  %s client <networkId>     - Connect and send messages\n", argv[0]);
        printf("  %s list                   - List online devices\n", argv[0]);
        return 1;
    }

    const char *mode = argv[1];

    printf("==============================================\n");
    printf("Persistent Session Test (No Timeout)\n");
    printf("==============================================\n");
    printf("PKG_NAME:     %s\n", g_pkgName);
    printf("SESSION_NAME: %s\n", g_sessionName);
    printf("MODE:         %s\n", mode);
    printf("==============================================\n\n");

    // 设置信号处理
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // 加载库
    void* handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW);
    if (!handle) {
        printf("[ERROR] Failed to load library: %s\n", dlerror());
        return 1;
    }

    CreateSessionServer_t createServer = dlsym(handle, "CreateSessionServer");
    RemoveSessionServer_t removeServer = dlsym(handle, "RemoveSessionServer");
    OpenSession_t openSession = dlsym(handle, "OpenSession");
    CloseSession_t closeSession = dlsym(handle, "CloseSession");
    g_sendBytes = dlsym(handle, "SendBytes");
    GetAllNodeDeviceInfo_t getAllDevices = dlsym(handle, "GetAllNodeDeviceInfo");
    FreeNodeInfo_t freeInfo = dlsym(handle, "FreeNodeInfo");

    if (!createServer || !removeServer || !openSession || !g_sendBytes) {
        printf("[ERROR] Failed to resolve symbols\n");
        dlclose(handle);
        return 1;
    }

    printf("[OK] Library loaded and symbols resolved\n\n");

    // List mode
    if (strcmp(mode, "list") == 0) {
        NodeBasicInfo *devices = NULL;
        int deviceCount = 0;
        int ret = getAllDevices(g_pkgName, (void**)&devices, &deviceCount);

        if (ret == 0 && devices) {
            printf("[DISCOVERY] Found %d device(s):\n", deviceCount);
            for (int i = 0; i < deviceCount; i++) {
                printf("  [%d] %s\n", i, devices[i].deviceName);
                printf("      networkId: %s\n", devices[i].networkId);
            }
            freeInfo(devices);
        } else {
            printf("[ERROR] GetAllNodeDeviceInfo failed: %d\n", ret);
        }

        dlclose(handle);
        return 0;
    }

    // 创建 Session Server
    printf("[STEP 1] Creating Session Server...\n");
    int ret = createServer(g_pkgName, g_sessionName, &g_listener);
    printf("[RESULT] CreateSessionServer returned: %d\n", ret);

    if (ret != 0 && ret != -986) {
        printf("[ERROR] Failed to create session server\n");
        dlclose(handle);
        return 1;
    }
    printf("[OK] Session server created\n\n");

    // Server mode
    if (strcmp(mode, "server") == 0) {
        printf("[SERVER] *** PERSISTENT MODE - NO TIMEOUT ***\n");
        printf("[SERVER] Waiting for incoming connections indefinitely...\n");
        printf("[SERVER] Press Ctrl+C to exit\n\n");

        // 列出可发现的设备
        NodeBasicInfo *devices = NULL;
        int deviceCount = 0;
        ret = getAllDevices(g_pkgName, (void**)&devices, &deviceCount);

        if (ret == 0 && devices) {
            printf("[SERVER] Online devices:\n");
            for (int i = 0; i < deviceCount; i++) {
                printf("  [%d] %s (%s)\n", i, devices[i].deviceName,
                       devices[i].networkId);
            }
            freeInfo(devices);
        }
        printf("\n");

        // 无限等待循环
        int counter = 0;
        while (g_running) {
            sleep(5);
            counter++;

            printf("[SERVER] Running... (%d sec elapsed)\n", counter * 5);
            printf("  Inbound sessions: %d\n", g_inboundSessionId >= 0 ? 1 : 0);
            printf("  Messages received: %d\n", g_messagesReceived);

            if (g_messagesReceived > 0) {
                printf("  ✅ Successfully received messages!\n");
            }
        }

        printf("\n[SERVER] Shutting down...\n");

    } else if (strcmp(mode, "client") == 0) {
        // Client mode
        if (argc < 3) {
            printf("[ERROR] Client mode requires peer network ID\n");
            printf("Usage: %s client <networkId>\n", argv[0]);
            removeServer(g_pkgName, g_sessionName);
            dlclose(handle);
            return 1;
        }

        const char *peerNetworkId = argv[2];
        printf("[CLIENT] Target peer: %s\n\n", peerNetworkId);

        printf("[STEP 2] Opening Session...\n");
        SessionAttribute attr = {
            .dataType = 2,
            .linkTypeNum = 0,
            .linkType = NULL
        };

        int sessionId = openSession(g_sessionName, g_sessionName,
                                   peerNetworkId, "", &attr);
        printf("[RESULT] OpenSession returned: %d\n", sessionId);

        if (sessionId < 0) {
            printf("[ERROR] OpenSession failed\n");
            printf("[HINT] Make sure server is running: ./persistent_session_test server\n");
            removeServer(g_pkgName, g_sessionName);
            dlclose(handle);
            return 1;
        }

        g_outboundSessionId = sessionId;
        printf("[OK] Session ID: %d\n\n", sessionId);

        printf("[STEP 3] Waiting for OnSessionOpened callback (10 sec)...\n");
        int waitCount = 0;
        bool callbackReceived = false;

        for (int i = 0; i < 10; i++) {
            sleep(1);
            printf(".");
            fflush(stdout);

            // 检查是否收到回调
            if (g_outboundSessionId > 0) {
                callbackReceived = true;
            }
        }
        printf("\n\n");

        if (callbackReceived) {
            printf("[OK] Callback received (or sessionId saved)\n");
        } else {
            printf("[WARNING] Callback may have failed\n");
            printf("[INFO] Attempting to send anyway...\n");
        }

        printf("\n[STEP 4] Sending test messages...\n");
        for (int i = 0; i < 5; i++) {
            char msg[256];
            snprintf(msg, sizeof(msg),
                    "Test message #%d from Device 2 at %d seconds",
                    i + 1, (int)time(NULL));

            printf("\n[SEND #%d] %s\n", i + 1, msg);
            ret = g_sendBytes(sessionId, msg, strlen(msg) + 1);
            printf("[RESULT] SendBytes returned: %d\n", ret);

            if (ret == 0) {
                g_messagesSent++;
                printf("[OK] Message sent (total: %d)\n", g_messagesSent);
            } else {
                printf("[FAIL] SendBytes failed: %d\n", ret);
                printf("[HINT] Error -426115004 means peer session not created\n");
                printf("       Make sure server is still running!\n");
                break;
            }

            sleep(2);
        }

        printf("\n[STEP 5] Waiting for replies (10 sec)...\n");
        for (int i = 0; i < 10; i++) {
            sleep(1);
            if (g_messagesReceived > 0) {
                printf("\n[OK] Received %d replies!\n", g_messagesReceived);
                break;
            }
        }

        printf("\n[STEP 6] Closing session...\n");
        closeSession(sessionId);
        sleep(1);
    }

    // 清理
    printf("\n[CLEANUP] Removing session server...\n");
    removeServer(g_pkgName, g_sessionName);
    dlclose(handle);

    printf("\n==============================================\n");
    printf("Test Complete\n");
    printf("  Messages sent: %d\n", g_messagesSent);
    printf("  Messages received: %d\n", g_messagesReceived);
    printf("==============================================\n");

    return 0;
}
