/*
 * Quick Cross-Device Session Test
 * 快速验证跨设备消息发送
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdbool.h>

typedef int (*CreateSessionServer_t)(const char*, const char*, void*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);
typedef int (*OpenSession_t)(const char*, const char*, const char*, const char*, void*);
typedef void (*CloseSession_t)(int);
typedef int (*SendBytes_t)(int, const void*, unsigned int);

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

static int g_serverSessionId = -1;
static int g_clientSessionId = -1;
static int g_messagesReceived = 0;
static bool g_clientSessionOpened = false;

static int OnSessionOpened(int sessionId, int result) {
    printf("\n[CALLBACK] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);

    if (result == 0) {
        g_clientSessionOpened = true;
        printf("[OK] Session opened successfully\n");
    } else {
        printf("[FAIL] Session open failed: %d\n", result);
        printf("[INFO] This is KH_TRANS callback issue, not Session API issue\n");
    }

    return result;
}

static void OnSessionClosed(int sessionId) {
    printf("\n[CALLBACK] OnSessionClosed: sessionId=%d\n", sessionId);
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    g_messagesReceived++;
    printf("\n[CALLBACK] OnBytesReceived #%d: sessionId=%d, len=%u\n",
           g_messagesReceived, sessionId, len);
    printf("[DATA] %.*s\n", (int)len, (const char*)data);
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
        printf("  %s server          - Wait for connections\n", argv[0]);
        printf("  %s client <netId>  - Connect and send messages\n", argv[0]);
        return 1;
    }

    const char *mode = argv[1];
    const char *pkgName = "com.huawei.ros2_rmw_dsoftbus";
    const char *sessionName = "com.huawei.ros2_rmw_dsoftbus.complete_test";

    printf("==============================================\n");
    printf("Quick Cross-Device Session Test\n");
    printf("==============================================\n");
    printf("PKG_NAME:     %s\n", pkgName);
    printf("SESSION_NAME: %s\n", sessionName);
    printf("MODE:         %s\n", mode);
    printf("==============================================\n\n");

    // Load library
    void* handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW);
    if (!handle) {
        printf("[ERROR] Library load failed: %s\n", dlerror());
        return 1;
    }

    CreateSessionServer_t createServer = dlsym(handle, "CreateSessionServer");
    RemoveSessionServer_t removeServer = dlsym(handle, "RemoveSessionServer");
    OpenSession_t openSession = dlsym(handle, "OpenSession");
    CloseSession_t closeSession = dlsym(handle, "CloseSession");
    SendBytes_t sendBytes = dlsym(handle, "SendBytes");

    if (!createServer || !removeServer || !openSession || !sendBytes) {
        printf("[ERROR] Symbol resolution failed\n");
        dlclose(handle);
        return 1;
    }

    printf("[OK] Library loaded\n\n");

    // Create Session Server
    printf("[STEP 1] Creating Session Server...\n");
    int ret = createServer(pkgName, sessionName, &g_listener);
    printf("[RESULT] CreateSessionServer returned: %d\n", ret);

    if (ret != 0 && ret != -986) {
        printf("[ERROR] Failed to create session server\n");
        dlclose(handle);
        return 1;
    }
    printf("[OK] Session server created\n\n");

    if (strcmp(mode, "server") == 0) {
        // SERVER MODE
        printf("[SERVER] Waiting for connections (30 seconds)...\n");
        printf("[SERVER] Expecting incoming session and messages\n\n");

        for (int i = 0; i < 30; i++) {
            sleep(1);
            printf(".");
            fflush(stdout);

            if (g_messagesReceived > 0) {
                printf("\n\n[SERVER] Received %d messages!\n", g_messagesReceived);
                break;
            }
        }

        printf("\n\n[SERVER] Test complete. Messages received: %d\n", g_messagesReceived);

    } else if (strcmp(mode, "client") == 0) {
        // CLIENT MODE
        if (argc < 3) {
            printf("[ERROR] Client mode requires peer network ID\n");
            removeServer(pkgName, sessionName);
            dlclose(handle);
            return 1;
        }

        const char *peerNetworkId = argv[2];
        printf("[CLIENT] Target peer: %s\n\n", peerNetworkId);

        printf("[STEP 2] Opening Session...\n");
        SessionAttribute attr = {
            .dataType = 2,  // TYPE_BYTES
            .linkTypeNum = 0,
            .linkType = NULL
        };

        int sessionId = openSession(sessionName, sessionName,
                                   peerNetworkId, "", &attr);
        printf("[RESULT] OpenSession returned: %d\n", sessionId);

        if (sessionId < 0) {
            printf("[ERROR] OpenSession failed\n");
            removeServer(pkgName, sessionName);
            dlclose(handle);
            return 1;
        }

        g_clientSessionId = sessionId;
        printf("[OK] Session ID: %d\n\n", sessionId);

        printf("[STEP 3] Waiting for callback (5 sec)...\n");
        for (int i = 0; i < 5; i++) {
            sleep(1);
            printf(".");
            fflush(stdout);
        }
        printf("\n\n");

        if (g_clientSessionOpened) {
            printf("[OK] Callback confirmed session opened\n\n");
        } else {
            printf("[WARNING] Callback failed (KH_TRANS issue)\n");
            printf("[INFO] Attempting to send anyway (API may still work)...\n\n");
        }

        printf("[STEP 4] Sending test messages...\n");
        for (int i = 0; i < 5; i++) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Test message #%d from Device 2", i + 1);

            printf("[SEND] %s\n", msg);
            ret = sendBytes(sessionId, msg, strlen(msg) + 1);
            printf("[RESULT] SendBytes returned: %d\n", ret);

            if (ret == 0) {
                printf("[OK] Message sent\n");
            } else {
                printf("[FAIL] SendBytes failed: %d\n", ret);
            }

            sleep(1);
        }

        printf("\n[STEP 5] Closing session...\n");
        closeSession(sessionId);
    }

    // Cleanup
    printf("\n[CLEANUP] Removing session server...\n");
    removeServer(pkgName, sessionName);
    dlclose(handle);

    printf("\n==============================================\n");
    if (strcmp(mode, "server") == 0) {
        printf("Server Test Complete - Received %d messages\n", g_messagesReceived);
    } else {
        printf("Client Test Complete\n");
    }
    printf("==============================================\n");

    return 0;
}
