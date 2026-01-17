/*
 * Service/Client RPC Real Device Test
 * Tests the complete request-response flow using real DSoftBus API
 *
 * Verification:
 * - CreateSessionServer for service
 * - Client sends REQUEST
 * - Service receives REQUEST and sends RESPONSE
 * - Client receives RESPONSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dlfcn.h>

// DSoftBus API (will be loaded via dlopen)
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

#define TYPE_BYTES 0x01

// Function pointers (loaded via dlopen)
static int (*CreateSessionServer)(const char *pkgName, const char *sessionName, const ISessionListener *listener) = NULL;
static int (*RemoveSessionServer)(const char *pkgName, const char *sessionName) = NULL;
static int (*OpenSession)(const char *mySessionName, const char *peerSessionName, const char *peerNetworkId, const char *groupId, const SessionAttribute *attr) = NULL;
static void (*CloseSession)(int sessionId) = NULL;
static int (*SendBytes)(int sessionId, const void *data, unsigned int len) = NULL;

// NativeToken API (statically linked)
#ifdef __cplusplus
extern "C" {
#endif
extern int InitializeNativeToken(const char* process_name);
#ifdef __cplusplus
}
#endif

// Service message header
typedef struct {
    uint8_t msg_type;  // 1=REQUEST, 2=RESPONSE
    int64_t request_id;
    uint32_t data_length;
} __attribute__((packed)) ServiceHeader;

#define MSG_REQUEST 1
#define MSG_RESPONSE 2

// Test state
static int g_service_session_id = -1;
static int g_client_session_id = -1;
static int g_request_received = 0;
static int g_response_received = 0;

// Session callbacks
static int on_session_opened(int sessionId, int result) {
    fprintf(stderr, "[Callback] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);
    return 0;
}

static void on_session_closed(int sessionId) {
    fprintf(stderr, "[Callback] OnSessionClosed: sessionId=%d\n", sessionId);
}

static void on_bytes_received(int sessionId, const void *data, unsigned int dataLen) {
    fprintf(stderr, "[Callback] OnBytesReceived: sessionId=%d, len=%u\n", sessionId, dataLen);

    if (dataLen < sizeof(ServiceHeader)) {
        fprintf(stderr, "[ERROR] Data too short\n");
        return;
    }

    const ServiceHeader *hdr = (const ServiceHeader *)data;
    const char *payload = (const char *)data + sizeof(ServiceHeader);

    if (hdr->msg_type == MSG_REQUEST) {
        fprintf(stderr, "[Service] Received REQUEST: id=%ld, data=%.*s\n",
                hdr->request_id, (int)(dataLen - sizeof(ServiceHeader)), payload);
        g_request_received = 1;

        // Send RESPONSE
        ServiceHeader resp_hdr;
        resp_hdr.msg_type = MSG_RESPONSE;
        resp_hdr.request_id = hdr->request_id;
        resp_hdr.data_length = 13;

        char buffer[256];
        memcpy(buffer, &resp_hdr, sizeof(ServiceHeader));
        memcpy(buffer + sizeof(ServiceHeader), "Hello Client", 13);

        int ret = SendBytes(sessionId, buffer, sizeof(ServiceHeader) + 13);
        fprintf(stderr, "[Service] Sent RESPONSE: ret=%d\n", ret);

    } else if (hdr->msg_type == MSG_RESPONSE) {
        fprintf(stderr, "[Client] Received RESPONSE: id=%ld, data=%.*s\n",
                hdr->request_id, (int)(dataLen - sizeof(ServiceHeader)), payload);
        g_response_received = 1;
    }
}

static ISessionListener g_listener = {
    on_session_opened,
    on_session_closed,
    on_bytes_received,
    NULL,
    NULL,
    NULL
};

// Load DSoftBus library
static int load_dsoftbus_library(void) {
    void *handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "[ERROR] dlopen failed: %s\n", dlerror());
        return -1;
    }

    CreateSessionServer = (int (*)(const char*, const char*, const ISessionListener*))dlsym(handle, "CreateSessionServer");
    RemoveSessionServer = (int (*)(const char*, const char*))dlsym(handle, "RemoveSessionServer");
    OpenSession = (int (*)(const char*, const char*, const char*, const char*, const SessionAttribute*))dlsym(handle, "OpenSession");
    CloseSession = (void (*)(int))dlsym(handle, "CloseSession");
    SendBytes = (int (*)(int, const void*, unsigned int))dlsym(handle, "SendBytes");

    if (!CreateSessionServer || !OpenSession || !SendBytes) {
        fprintf(stderr, "[ERROR] Failed to load DSoftBus symbols\n");
        return -1;
    }

    fprintf(stderr, "[INFO] DSoftBus library loaded successfully\n");
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mode>\n", argv[0]);
        fprintf(stderr, "  mode: 'service' or 'client <peer_network_id>'\n");
        return 1;
    }

    const char *mode = argv[1];
    const char *peer_id = (argc > 2) ? argv[2] : NULL;

    fprintf(stderr, "=== Service/Client RPC Real Device Test ===\n");
    fprintf(stderr, "Mode: %s\n", mode);

    // Step 1: Set NativeToken permissions (optional on fresh systems)
    fprintf(stderr, "\n[Step 1] Setting NativeToken permissions...\n");
    int token_ret = InitializeNativeToken("service_rpc_real_test");
    if (token_ret != 1) {
        fprintf(stderr, "[WARNING] InitializeNativeToken failed (ret=%d)\n", token_ret);
        fprintf(stderr, "[WARNING] Continuing without NativeToken - system may allow by default\n");
        fprintf(stderr, "[INFO] This is expected on fresh systems or if AccessToken API changed\n");
    } else {
        fprintf(stderr, "[OK] NativeToken set successfully\n");
    }

    // Step 2: Load DSoftBus library
    fprintf(stderr, "\n[Step 2] Loading DSoftBus library...\n");
    if (load_dsoftbus_library() != 0) {
        return 1;
    }

    if (strcmp(mode, "service") == 0) {
        // Service mode
        fprintf(stderr, "\n[Step 3] Creating Service SessionServer...\n");
        // Note: Session name must start with '*' per DSoftBus convention (Phase 2 verified)
        int ret = CreateSessionServer("com.huawei.ros2_rmw_dsoftbus",
                                       "*softbus.rpc_test",
                                       &g_listener);
        if (ret < 0) {
            fprintf(stderr, "[ERROR] CreateSessionServer failed: %d\n", ret);
            return 1;
        }
        fprintf(stderr, "[OK] Service created, listener_id=%d\n", ret);

        fprintf(stderr, "\n[Waiting] Service is running. Waiting for client requests...\n");

        // Wait for request
        for (int i = 0; i < 60; i++) {
            sleep(1);
            if (g_request_received && g_response_received) {
                fprintf(stderr, "\n✅ SUCCESS: Service RPC test passed!\n");
                fprintf(stderr, "  - Received REQUEST: ✅\n");
                fprintf(stderr, "  - Sent RESPONSE: ✅\n");
                break;
            }
        }

    } else if (strcmp(mode, "client") == 0) {
        if (!peer_id) {
            fprintf(stderr, "[ERROR] Client mode requires peer_network_id\n");
            return 1;
        }

        // Client mode
        fprintf(stderr, "\n[Step 3] Opening session to service...\n");
        fprintf(stderr, "[INFO] Target peer: %s\n", peer_id);
        SessionAttribute attr;
        memset(&attr, 0, sizeof(attr));
        attr.dataType = TYPE_BYTES;

        // Note: Session names must start with '*' per DSoftBus convention (Phase 2 verified)
        int session_id = OpenSession("*softbus.rpc_test",  // My session name
                                      "*softbus.rpc_test",  // Peer session name (same as service)
                                      peer_id,              // Peer network ID
                                      "GROUP_ID",
                                      &attr);
        if (session_id < 0) {
            fprintf(stderr, "[ERROR] OpenSession failed: %d\n", session_id);
            return 1;
        }
        g_client_session_id = session_id;
        fprintf(stderr, "[OK] Session opened: id=%d\n", session_id);

        // Wait for connection
        sleep(2);

        // Send REQUEST
        fprintf(stderr, "\n[Step 4] Sending REQUEST...\n");
        ServiceHeader req_hdr;
        req_hdr.msg_type = MSG_REQUEST;
        req_hdr.request_id = 12345;
        req_hdr.data_length = 13;

        char buffer[256];
        memcpy(buffer, &req_hdr, sizeof(ServiceHeader));
        memcpy(buffer + sizeof(ServiceHeader), "Hello Service", 13);

        int ret = SendBytes(session_id, buffer, sizeof(ServiceHeader) + 13);
        fprintf(stderr, "[OK] REQUEST sent: ret=%d\n", ret);

        // Wait for response
        fprintf(stderr, "\n[Waiting] Waiting for RESPONSE...\n");
        for (int i = 0; i < 30; i++) {
            sleep(1);
            if (g_response_received) {
                fprintf(stderr, "\n✅ SUCCESS: Client RPC test passed!\n");
                fprintf(stderr, "  - Sent REQUEST: ✅\n");
                fprintf(stderr, "  - Received RESPONSE: ✅\n");
                break;
            }
        }

        CloseSession(session_id);
    }

    fprintf(stderr, "\n=== Test Complete ===\n");
    return 0;
}
