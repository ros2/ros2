/*
 * Minimal DSoftBus Test - No NativeToken dependency
 * Tests if fresh RK3588S system allows DSoftBus API by default
 *
 * This test DOES NOT use NativeToken API - relies on system default permissions
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
#define NETWORK_ID_BUF_LEN 65

// Function pointers
static int (*CreateSessionServer)(const char *, const char *, const ISessionListener *) = NULL;
static int (*GetLocalNodeDeviceInfo)(const char *, NodeBasicInfo *) = NULL;
static int (*GetAllNodeDeviceInfo)(const char *, NodeBasicInfo **, int *) = NULL;

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
    fprintf(stderr, "=== Minimal DSoftBus Test (No NativeToken) ===\n\n");

    // Step 1: Load DSoftBus library
    fprintf(stderr, "[Step 1] Loading DSoftBus library...\n");
    void *handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "[ERROR] dlopen failed: %s\n", dlerror());
        return 1;
    }

    CreateSessionServer = (int (*)(const char*, const char*, const ISessionListener*))dlsym(handle, "CreateSessionServer");
    GetLocalNodeDeviceInfo = (int (*)(const char*, NodeBasicInfo*))dlsym(handle, "GetLocalNodeDeviceInfo");
    GetAllNodeDeviceInfo = (int (*)(const char*, NodeBasicInfo**, int*))dlsym(handle, "GetAllNodeDeviceInfo");

    if (!CreateSessionServer || !GetLocalNodeDeviceInfo || !GetAllNodeDeviceInfo) {
        fprintf(stderr, "[ERROR] Failed to load required DSoftBus symbols\n");
        fprintf(stderr, "  CreateSessionServer: %p\n", (void*)CreateSessionServer);
        fprintf(stderr, "  GetLocalNodeDeviceInfo: %p\n", (void*)GetLocalNodeDeviceInfo);
        fprintf(stderr, "  GetAllNodeDeviceInfo: %p\n", (void*)GetAllNodeDeviceInfo);
        return 1;
    }

    fprintf(stderr, "[OK] DSoftBus library loaded\n");
    fprintf(stderr, "  CreateSessionServer: %p\n", (void*)CreateSessionServer);
    fprintf(stderr, "  GetLocalNodeDeviceInfo: %p\n", (void*)GetLocalNodeDeviceInfo);
    fprintf(stderr, "  GetAllNodeDeviceInfo: %p\n", (void*)GetAllNodeDeviceInfo);

    // Step 2: Get local device info
    fprintf(stderr, "\n[Step 2] Getting local device info...\n");
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));

    int ret = GetLocalNodeDeviceInfo("com.huawei.ros2_test", &localInfo);
    fprintf(stderr, "[INFO] GetLocalNodeDeviceInfo returned: %d\n", ret);

    if (ret == 0) {
        fprintf(stderr, "[OK] Local device info:\n");
        fprintf(stderr, "  Network ID: %s\n", localInfo.networkId);
        fprintf(stderr, "  Device Name: %s\n", localInfo.deviceName);
        fprintf(stderr, "  Device Type: %d\n", localInfo.deviceTypeId);
    } else {
        fprintf(stderr, "[WARNING] GetLocalNodeDeviceInfo failed: %d\n", ret);
        fprintf(stderr, "[INFO] Continuing anyway...\n");
    }

    // Step 3: Get all devices in network
    fprintf(stderr, "\n[Step 3] Discovering peer devices...\n");
    NodeBasicInfo *deviceList = NULL;
    int deviceCount = 0;

    ret = GetAllNodeDeviceInfo("com.huawei.ros2_test", &deviceList, &deviceCount);
    fprintf(stderr, "[INFO] GetAllNodeDeviceInfo returned: %d, count=%d\n", ret, deviceCount);

    if (ret == 0 && deviceCount > 0) {
        fprintf(stderr, "[OK] Found %d peer device(s):\n", deviceCount);
        for (int i = 0; i < deviceCount; i++) {
            fprintf(stderr, "  [%d] %s (%s)\n", i, deviceList[i].networkId, deviceList[i].deviceName);
        }
    } else {
        fprintf(stderr, "[INFO] No peer devices found (expected on single device)\n");
    }

    // Step 4: Create Session Server
    fprintf(stderr, "\n[Step 4] Creating SessionServer...\n");
    fprintf(stderr, "[INFO] Package: com.huawei.ros2_test\n");
    fprintf(stderr, "[INFO] Session: *softbus.minimal_test\n");

    ret = CreateSessionServer("com.huawei.ros2_test",
                              "*softbus.minimal_test",
                              &g_listener);

    fprintf(stderr, "[RESULT] CreateSessionServer returned: %d\n", ret);

    if (ret >= 0) {
        fprintf(stderr, "✅ SUCCESS: CreateSessionServer works WITHOUT NativeToken!\n");
        fprintf(stderr, "   This means the fresh system allows DSoftBus by default\n");
        fprintf(stderr, "   or uses different permission mechanism.\n");

        // Wait a bit to see if any callbacks trigger
        fprintf(stderr, "\n[Waiting 5 seconds for callbacks...]\n");
        sleep(5);

    } else {
        fprintf(stderr, "❌ FAILED: CreateSessionServer failed: %d\n", ret);
        fprintf(stderr, "   Error code: %d (0x%X)\n", ret, (unsigned int)ret);

        // Common error codes:
        // -426442706 (0xE6815FAE): Permission denied or service not ready
        // -426442743 (0xE6815FD9): Invalid parameters

        if (ret == -426442706) {
            fprintf(stderr, "\n[DIAGNOSIS] Error -426442706 typically means:\n");
            fprintf(stderr, "  1. DSoftBus service not fully initialized (wait longer)\n");
            fprintf(stderr, "  2. Permission configuration missing/incorrect\n");
            fprintf(stderr, "  3. Package name not in softbus_trans_permission.json\n");
            fprintf(stderr, "  4. System requires NativeToken (can't use default permissions)\n");
        }
    }

    fprintf(stderr, "\n=== Test Complete ===\n");
    return (ret >= 0) ? 0 : 1;
}
