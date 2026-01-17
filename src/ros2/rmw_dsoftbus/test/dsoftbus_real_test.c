/*
 * DSoftBus Real API Test - Strict Configuration
 * Uses EXACT PKG_NAME and SESSION_NAME as configured in softbus_trans_permission.json
 *
 * Configuration:
 *   PKG_NAME: "com.huawei.ros2_rmw_dsoftbus"
 *   SESSION_NAME: "com.huawei.ros2_rmw_dsoftbus.complete_test"
 *   (Both sides MUST use same names)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

// DSoftBus API structures
typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnStreamReceived)(int sessionId, const void *data, unsigned int dataLen, int streamType);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, const void *qosTv);
} ISessionListener;

typedef struct {
    int dataType;
    int linkTypeNum;
    int linkType[4];
} SessionAttribute;

typedef struct {
    char networkId[65];
    char deviceName[65];
    int deviceTypeId;
} NodeBasicInfo;

#define TYPE_BYTES 0x01

// EXACT configuration from softbus_trans_permission.json
#define PKG_NAME "com.huawei.ros2_rmw_dsoftbus"
#define SESSION_NAME "com.huawei.ros2_rmw_dsoftbus.complete_test"

// Function pointers
static int (*CreateSessionServer)(const char *, const char *, const ISessionListener *) = NULL;
static int (*RemoveSessionServer)(const char *, const char *) = NULL;
static int (*OpenSession)(const char *, const char *, const char *, const char *, const SessionAttribute *) = NULL;
static void (*CloseSession)(int) = NULL;
static int (*SendBytes)(int, const void *, unsigned int) = NULL;
static int (*GetLocalNodeDeviceInfo)(const char *, NodeBasicInfo *) = NULL;

// Test state
static int g_received_bytes = 0;

// Callbacks
static int on_session_opened(int sessionId, int result) {
    fprintf(stderr, "[Callback] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);
    return 0;
}

static void on_session_closed(int sessionId) {
    fprintf(stderr, "[Callback] OnSessionClosed: sessionId=%d\n", sessionId);
}

static void on_bytes_received(int sessionId, const void *data, unsigned int dataLen) {
    fprintf(stderr, "[Callback] OnBytesReceived: sessionId=%d, len=%u\n", sessionId, dataLen);
    fprintf(stderr, "[Data] %.*s\n", (int)dataLen, (const char*)data);
    g_received_bytes++;
}

static ISessionListener g_listener = {
    on_session_opened,
    on_session_closed,
    on_bytes_received,
    NULL,
    NULL,
    NULL
};

int main(int argc, char *argv[]) {
    fprintf(stderr, "=== DSoftBus Real API Test ===\n");
    fprintf(stderr, "PKG_NAME: %s\n", PKG_NAME);
    fprintf(stderr, "SESSION_NAME: %s\n\n", SESSION_NAME);

    // Step 1: Load DSoftBus library
    fprintf(stderr, "[Step 1] Loading DSoftBus library...\n");
    void *handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "[ERROR] dlopen failed: %s\n", dlerror());
        return 1;
    }

    CreateSessionServer = (int (*)(const char*, const char*, const ISessionListener*))dlsym(handle, "CreateSessionServer");
    RemoveSessionServer = (int (*)(const char*, const char*))dlsym(handle, "RemoveSessionServer");
    OpenSession = (int (*)(const char*, const char*, const char*, const char*, const SessionAttribute*))dlsym(handle, "OpenSession");
    CloseSession = (void (*)(int))dlsym(handle, "CloseSession");
    SendBytes = (int (*)(int, const void*, unsigned int))dlsym(handle, "SendBytes");
    GetLocalNodeDeviceInfo = (int (*)(const char*, NodeBasicInfo*))dlsym(handle, "GetLocalNodeDeviceInfo");

    if (!CreateSessionServer || !OpenSession || !SendBytes) {
        fprintf(stderr, "[ERROR] Failed to load required DSoftBus symbols\n");
        return 1;
    }
    fprintf(stderr, "[OK] DSoftBus library loaded\n\n");

    // Step 2: Get local network ID
    fprintf(stderr, "[Step 2] Getting local network ID...\n");
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));

    int ret = GetLocalNodeDeviceInfo(PKG_NAME, &localInfo);
    fprintf(stderr, "[INFO] GetLocalNodeDeviceInfo returned: %d\n", ret);

    if (ret == 0) {
        fprintf(stderr, "[OK] Local Network ID: %s\n", localInfo.networkId);
        fprintf(stderr, "[OK] Device Name: %s\n\n", localInfo.deviceName);
    } else {
        fprintf(stderr, "[WARNING] GetLocalNodeDeviceInfo failed: %d\n", ret);
        fprintf(stderr, "[INFO] Continuing without network ID...\n\n");
    }

    const char *mode = (argc > 1) ? argv[1] : "service";

    if (strcmp(mode, "service") == 0) {
        // === Service Mode ===
        fprintf(stderr, "[Step 3] Creating SessionServer (Service Mode)...\n");
        fprintf(stderr, "[INFO] PKG_NAME: %s\n", PKG_NAME);
        fprintf(stderr, "[INFO] SESSION_NAME: %s\n", SESSION_NAME);

        ret = CreateSessionServer(PKG_NAME, SESSION_NAME, &g_listener);
        fprintf(stderr, "[RESULT] CreateSessionServer returned: %d\n", ret);

        if (ret < 0) {
            fprintf(stderr, "❌ CreateSessionServer FAILED: %d\n", ret);
            fprintf(stderr, "\n[Diagnosis] Error %d means:\n", ret);
            if (ret == -426442706) {
                fprintf(stderr, "  - Permission denied (check softbus_trans_permission.json)\n");
                fprintf(stderr, "  - DSoftBus service not ready\n");
                fprintf(stderr, "  - NativeToken required but not set\n");
            }
            return 1;
        }

        fprintf(stderr, "✅ SUCCESS: CreateSessionServer returned: %d\n", ret);
        fprintf(stderr, "\n[Service] Waiting for client connections...\n");
        fprintf(stderr, "[Info] Run on client device:\n");
        fprintf(stderr, "       ./dsoftbus_real_test client %s\n", localInfo.networkId);

        // Wait for connections
        for (int i = 0; i < 60; i++) {
            sleep(1);
            if (g_received_bytes > 0) {
                fprintf(stderr, "\n✅ SUCCESS: Received %d messages from client!\n", g_received_bytes);
                break;
            }
        }

        fprintf(stderr, "\n[Service] Cleaning up...\n");
        if (RemoveSessionServer) {
            RemoveSessionServer(PKG_NAME, SESSION_NAME);
        }

    } else if (strcmp(mode, "client") == 0) {
        // === Client Mode ===
        if (argc < 3) {
            fprintf(stderr, "[ERROR] Client mode requires peer_network_id\n");
            fprintf(stderr, "Usage: %s client <peer_network_id>\n", argv[0]);
            return 1;
        }

        const char *peer_network_id = argv[2];
        fprintf(stderr, "[Step 3] Opening session to peer (Client Mode)...\n");
        fprintf(stderr, "[INFO] Peer Network ID: %s\n", peer_network_id);
        fprintf(stderr, "[INFO] My SESSION_NAME: %s\n", SESSION_NAME);
        fprintf(stderr, "[INFO] Peer SESSION_NAME: %s\n", SESSION_NAME);

        SessionAttribute attr;
        memset(&attr, 0, sizeof(attr));
        attr.dataType = TYPE_BYTES;

        // Both sides use SAME SESSION_NAME
        ret = OpenSession(SESSION_NAME,    // My session name
                          SESSION_NAME,    // Peer session name (SAME)
                          peer_network_id,
                          "GROUP_ID",
                          &attr);

        fprintf(stderr, "[RESULT] OpenSession returned: %d\n", ret);

        if (ret < 0) {
            fprintf(stderr, "❌ OpenSession FAILED: %d\n", ret);
            return 1;
        }

        fprintf(stderr, "✅ SUCCESS: Session opened: session_id=%d\n", ret);

        // Send test message
        sleep(2);
        fprintf(stderr, "\n[Step 4] Sending test message...\n");
        const char *msg = "Hello from RMW DSoftBus Client!";
        int send_ret = SendBytes(ret, msg, strlen(msg) + 1);
        fprintf(stderr, "[RESULT] SendBytes returned: %d\n", send_ret);

        if (send_ret > 0) {
            fprintf(stderr, "✅ SUCCESS: Message sent successfully!\n");
        } else {
            fprintf(stderr, "❌ SendBytes failed: %d\n", send_ret);
        }

        sleep(5);
        CloseSession(ret);

    } else {
        fprintf(stderr, "[ERROR] Invalid mode: %s\n", mode);
        fprintf(stderr, "Usage: %s [service|client <peer_network_id>]\n", argv[0]);
        return 1;
    }

    fprintf(stderr, "\n=== Test Complete ===\n");
    return 0;
}
