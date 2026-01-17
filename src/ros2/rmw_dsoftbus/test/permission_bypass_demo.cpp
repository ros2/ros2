/*
 * Permission Bypass Demo - Shows correct usage of dsoftbus permission bypass
 *
 * This demo replicates the exact approach used by dsoftbus official tests:
 * - Uses system_basic APL (not normal)
 * - Only requests 2 essential permissions
 * - Matches dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp exactly
 *
 * Compile (in OHOS build system):
 *   ohos_executable("permission_bypass_demo") {
 *     sources = [
 *       "test/permission_bypass_demo.cpp",
 *       "test/softbus_permission_bypass.cpp"
 *     ]
 *     external_deps = [
 *       "access_token:libaccesstoken_sdk",
 *       "access_token:libnativetoken",
 *       "access_token:libtoken_setproc",
 *       "dsoftbus:softbus_client",
 *     ]
 *   }
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "softbus_permission_bypass.h"

// DSoftBus headers
extern "C" {
#include "softbus_bus_center.h"
#include "session.h"
}

// ============================================================================
// Device Discovery Callbacks
// ============================================================================

void OnNodeOnline(NodeBasicInfo *info) {
    if (info == NULL) return;
    printf("\n✅ [Discovery] Device Online: %s (NetworkId: %s)\n",
           info->deviceName, info->networkId);
}

void OnNodeOffline(NodeBasicInfo *info) {
    if (info == NULL) return;
    printf("\n❌ [Discovery] Device Offline: %s\n", info->networkId);
}

void OnNodeBasicInfoChanged(NodeBasicInfoType type, NodeBasicInfo *info) {
    printf("[Discovery] Device Info Changed (type=%d)\n", type);
}

static INodeStateCb g_nodeStateCallback = {
    .events = EVENT_NODE_STATE_ONLINE | EVENT_NODE_STATE_OFFLINE | EVENT_NODE_STATE_INFO_CHANGED,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnNodeBasicInfoChanged,
};

// ============================================================================
// Session Callbacks
// ============================================================================

int OnSessionOpened(int sessionId, int result) {
    printf("\n✅ [Session] Opened: sessionId=%d, result=%d\n", sessionId, result);
    return 0;
}

void OnSessionClosed(int sessionId) {
    printf("\n❌ [Session] Closed: sessionId=%d\n", sessionId);
}

void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen) {
    printf("[Session] Data Received: sessionId=%d, len=%u\n", sessionId, dataLen);
    printf("[Session] Data: %.*s\n", (int)dataLen, (const char*)data);
}

void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen) {
    printf("[Session] Message Received: sessionId=%d, len=%u\n", sessionId, dataLen);
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
};

// ============================================================================
// Main Test
// ============================================================================

int main(int argc, char **argv) {
    printf("\n");
    printf("========================================\n");
    printf("DSoftBus Permission Bypass Demo\n");
    printf("Using official dsoftbus test approach\n");
    printf("========================================\n\n");

    // ========================================
    // STEP 1: Set permissions (CRITICAL!)
    // ========================================
    printf("[Step 1] Setting NativeToken permissions...\n");
    const char* processName = "com.rmw_dsoftbus.permission_demo";

    if (SetSoftbusNativeTokenPermission(processName) != 0) {
        printf("❌ ERROR: Failed to set permissions\n");
        printf("   This is required before any dsoftbus API calls!\n");
        return 1;
    }

    printf("\n");

    // ========================================
    // STEP 2: Test Bus Center APIs
    // ========================================
    printf("[Step 2] Testing Bus Center APIs (with permission bypass)...\n");

    // Register device state callback
    printf("[Step 2.1] Registering device state callback...\n");
    int ret = RegNodeDeviceStateCb(processName, &g_nodeStateCallback);
    if (ret != 0) {
        printf("❌ ERROR: RegNodeDeviceStateCb failed: %d\n", ret);
        printf("   Expected: 0 (success) if permission bypass worked\n");
        printf("   Got: %d (likely SOFTBUS_PERMISSION_DENIED = -4)\n", ret);
        return 1;
    }
    printf("✅ Success! Permission bypass is working!\n\n");

    // Get local device info
    printf("[Step 2.2] Getting local device info...\n");
    NodeBasicInfo localInfo;
    ret = GetLocalNodeDeviceInfo(processName, &localInfo);
    if (ret != 0) {
        printf("❌ ERROR: GetLocalNodeDeviceInfo failed: %d\n", ret);
        return 1;
    }
    printf("✅ Local Device: %s\n", localInfo.deviceName);
    printf("   NetworkId: %s\n", localInfo.networkId);
    printf("\n");

    // ========================================
    // STEP 3: Test Session APIs
    // ========================================
    printf("[Step 3] Testing Session APIs...\n");

    const char* sessionName = "com.rmw_dsoftbus.test_session";
    printf("[Step 3.1] Creating session server: %s\n", sessionName);

    ret = CreateSessionServer(processName, sessionName, &g_sessionListener);
    if (ret != 0) {
        printf("❌ ERROR: CreateSessionServer failed: %d\n", ret);
        printf("   Expected: 0 (success)\n");
        printf("   Got: %d\n", ret);
        return 1;
    }
    printf("✅ Session server created successfully!\n\n");

    // ========================================
    // STEP 4: Wait for discovery
    // ========================================
    printf("[Step 4] Waiting for peer devices (10 seconds)...\n");
    printf("   Run this test on multiple devices to see discovery\n");

    for (int i = 0; i < 10; i++) {
        sleep(1);
        printf("   Waiting... %d/10\n", i + 1);
    }

    printf("\n");

    // ========================================
    // STEP 5: Cleanup
    // ========================================
    printf("[Step 5] Cleanup...\n");
    RemoveSessionServer(processName, sessionName);
    UnregNodeDeviceStateCb(&g_nodeStateCallback);

    printf("\n");
    printf("========================================\n");
    printf("✅ Test Completed Successfully!\n");
    printf("========================================\n");
    printf("\n");
    printf("Key Findings:\n");
    printf("1. Permission bypass using system_basic APL: ✅ WORKING\n");
    printf("2. RegNodeDeviceStateCb: ✅ SUCCESS (no SOFTBUS_PERMISSION_DENIED)\n");
    printf("3. GetLocalNodeDeviceInfo: ✅ SUCCESS\n");
    printf("4. CreateSessionServer: ✅ SUCCESS\n");
    printf("\n");
    printf("Next Steps:\n");
    printf("1. Run this test on 2+ devices to verify cross-device discovery\n");
    printf("2. Use this permission bypass approach in your Phase 2/3 tests\n");
    printf("3. Replace old InjectNativeTokenPermissions() with SetSoftbusNativeTokenPermission()\n");
    printf("\n");

    return 0;
}
