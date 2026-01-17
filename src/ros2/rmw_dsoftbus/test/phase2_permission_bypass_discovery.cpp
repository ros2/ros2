/*
 * Phase 2 Graph Discovery Test with Permission Bypass
 *
 * Demonstrates using OpenHarmony NativeToken permission injection
 * to bypass softbus permission checks and establish cross-device sessions.
 *
 * Compilation (with OHOS SDK):
 *   aarch64-unknown-linux-ohos-clang++ -std=c++17 \
 *     phase2_permission_bypass_discovery.cpp \
 *     softbus_dlopen_shim.cpp \
 *     -I../../OpenHarmony/foundation/communication/dsoftbus/interfaces/kits \
 *     -I../../OpenHarmony/foundation/communication/dsoftbus/interfaces/kits/bus_center \
 *     -I../../OpenHarmony/foundation/communication/dsoftbus/interfaces/kits/transport \
 *     -I../../OpenHarmony/foundation/communication/dsoftbus/interfaces/kits/common \
 *     -I./include -I./mock_includes \
 *     -o phase2_discovery_test \
 *     -ldl -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <iostream>
#include <vector>

// OpenHarmony dsoftbus headers
#include "softbus_bus_center.h"
#include "softbus_common.h"
#include "trans_type.h"
#include "session.h"
#include "socket.h"

// Permission bypass utility (based on dsoftbus official test approach)
#include "softbus_permission_bypass.h"

// Framework initialization
extern "C" {
    int32_t InitSoftBus(const char *pkgName);
}

// ============================================================================
// Constants
// ============================================================================

static const char* PKG_NAME = "com.ros2.phase2.discovery";
static const char* SESSION_NAME_PREFIX = "com.huawei.ros2.graph";

// Permission strings defined in softbus_permission_bypass.h
// No need to redefine here

// Buffer sizes (DEVICE_NAME_BUF_LEN defined in softbus_bus_center.h as 128)
#define NETWORK_ID_BUF_LEN 65

// ============================================================================
// Global State
// ============================================================================

struct PeerDevice {
    char networkId[NETWORK_ID_BUF_LEN];
    char deviceName[DEVICE_NAME_BUF_LEN];  // 128 from softbus_bus_center.h
};

static std::vector<PeerDevice> g_discoveredDevices;
static bool g_discovery_complete = false;
static int g_sessionId = -1;

// Permission injection removed - now using softbus_permission_bypass.h
// Official dsoftbus test approach: system_basic APL + 2 permissions

// ============================================================================
// Bus Center Callbacks
// ============================================================================

void OnNodeOnline(NodeBasicInfo *info) {
    if (info == NULL) return;

    printf("\n[Discovery] ✓ OnNodeOnline\n");
    printf("[Discovery]   Device: %s\n", info->deviceName);
    printf("[Discovery]   NetworkID: %s\n", info->networkId);

    PeerDevice peer;
    strncpy(peer.networkId, info->networkId, NETWORK_ID_BUF_LEN - 1);
    strncpy(peer.deviceName, info->deviceName, DEVICE_NAME_BUF_LEN - 1);
    g_discoveredDevices.push_back(peer);
    g_discovery_complete = true;
}

void OnNodeOffline(NodeBasicInfo *info) {
    if (info == NULL) return;
    printf("[Discovery] OnNodeOffline: %s\n", info->networkId);
}

void OnDeviceInfoChanged(NodeBasicInfoType type, NodeBasicInfo *info) {
    (void)info;  // Suppress unused warning
    printf("[Discovery] OnDeviceInfoChanged: type=%d\n", (int)type);
}

static INodeStateCb g_nodeStateCallback = {
    .events = EVENT_NODE_STATE_ONLINE | EVENT_NODE_STATE_OFFLINE | EVENT_NODE_STATE_INFO_CHANGED,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnDeviceInfoChanged,
};

// ============================================================================
// Session Callbacks
// ============================================================================

int OnSessionOpened(int sessionId, int result) {
    printf("[Session] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);
    if (result == 0) {
        g_sessionId = sessionId;
    }
    return 0;  // Return 0 if session is accepted
}

void OnSessionClosed(int sessionId) {
    printf("[Session] OnSessionClosed: sessionId=%d\n", sessionId);
}

void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen) {
    printf("[Session] OnBytesReceived: sessionId=%d, dataLen=%u\n", sessionId, dataLen);
    if (dataLen > 0 && dataLen < 256) {
        printf("[Session] Data: %.*s\n", dataLen, (const char*)data);
    }
}

void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen) {
    (void)data;  // Suppress unused warning
    printf("[Session] OnMessageReceived: sessionId=%d, dataLen=%u\n", sessionId, dataLen);
}

void OnStreamReceived(int sessionId, const StreamData *data, const StreamData *ext,
                      const StreamFrameInfo *param) {
    (void)data; (void)ext; (void)param;  // Suppress unused warnings
    printf("[Session] OnStreamReceived: sessionId=%d\n", sessionId);
}

void OnQosEvent(int sessionId, int eventId, int tvCount, const QosTv *tvList) {
    (void)tvList;  // Suppress unused warnings
    printf("[Session] OnQosEvent: sessionId=%d, eventId=%d, tvCount=%d\n", sessionId, eventId, tvCount);
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = OnStreamReceived,
    .OnQosEvent = OnQosEvent,
};

// ============================================================================
// Phase 2: Device Discovery
// ============================================================================

int TestDeviceDiscovery() {
    printf("\n========================================\n");
    printf("Phase 2: Device Discovery\n");
    printf("========================================\n");

    // CRITICAL: Initialize SoftBus framework first
    printf("[Discovery] Step 1: Initializing SoftBus framework...\n");
    int initRet = InitSoftBus(PKG_NAME);
    printf("[Discovery] InitSoftBus returned: %d\n", initRet);
    if (initRet != 0) {
        printf("[Discovery] ⚠️ InitSoftBus failed! But continuing anyway...\n");
        printf("[Discovery] This is likely the source of IPC errors!\n");
    } else {
        printf("[Discovery] ✓ SoftBus framework initialized successfully\n");
    }

    // Register bus center callback
    printf("[Discovery] Step 2: Registering device state callback...\n");
    int ret = RegNodeDeviceStateCb(PKG_NAME, &g_nodeStateCallback);
    if (ret != 0) {
        printf("[Discovery] ✗ RegNodeDeviceStateCb failed: %d\n", ret);
        return -1;
    }
    printf("[Discovery] ✓ Callback registered\n");

    // Wait for Bus Center to initialize
    printf("[Discovery] Step 3: Waiting 2 seconds for Bus Center initialization...\n");
    sleep(2);

    // Diagnostic: Try GetAllNodeDeviceInfo first to test IPC connectivity
    printf("[Discovery] ========== DIAGNOSTIC TEST ==========\n");
    printf("[Discovery] Testing GetAllNodeDeviceInfo first (simpler IPC call)...\n");
    NodeBasicInfo *nodeList = nullptr;
    int nodeNum = 0;
    int diagRet = GetAllNodeDeviceInfo(PKG_NAME, &nodeList, &nodeNum);
    printf("[Discovery] GetAllNodeDeviceInfo returned: %d (0x%x)\n", diagRet, (unsigned int)diagRet);
    printf("[Discovery] nodeNum = %d\n", nodeNum);
    if (diagRet != 0) {
        printf("[Discovery] ⚠️ GetAllNodeDeviceInfo also failed with same error!\n");
        printf("[Discovery] This confirms: ALL Bus Center IPC calls are failing\n");
        printf("[Discovery] Root cause is likely at SA/Binder level, not permission system\n");
    } else {
        printf("[Discovery] ✓ GetAllNodeDeviceInfo succeeded! Found %d devices\n", nodeNum);
        for (int i = 0; i < nodeNum; i++) {
            printf("[Discovery]   Device %d: %s (NetworkId: %s)\n",
                   i, nodeList[i].deviceName, nodeList[i].networkId);
        }
        FreeNodeInfo(nodeList);
    }
    printf("[Discovery] ========== END DIAGNOSTIC ==========\n\n");

    // Get local device info with diagnostic output
    printf("[Discovery] Getting local device info (PKG_NAME=\"%s\")...\n", PKG_NAME);
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));
    printf("[Discovery] Size of NodeBasicInfo: %zu bytes\n", sizeof(NodeBasicInfo));
    printf("[Discovery] Calling GetLocalNodeDeviceInfo with PKG_NAME=\"%s\"...\n", PKG_NAME);
    fflush(stdout);
    ret = GetLocalNodeDeviceInfo(PKG_NAME, &localInfo);
    printf("[Discovery] GetLocalNodeDeviceInfo returned: %d (0x%x)\n", ret, (unsigned int)ret);
    printf("[Discovery] localInfo after call: deviceName=\"%s\", networkId=\"%s\"\n",
           localInfo.deviceName, localInfo.networkId);
    if (ret != 0) {
        printf("[Discovery] ✗ GetLocalNodeDeviceInfo failed with error: %d\n", ret);
        printf("[Discovery] Error code explanation:\n");
        printf("[Discovery]   -426442720 = 0xe6950020 (IPC_ERROR from kaihong/communication/plc)\n");
        printf("[Discovery]   This indicates Inter-Process Communication failure\n");
        printf("[Discovery]   Possible causes:\n");
        printf("[Discovery]     1. Bus Center SA not responding to IPC calls\n");
        printf("[Discovery]     2. Service agent lookup failed\n");
        printf("[Discovery]     3. Insufficient IPC permissions for this token\n");
        printf("[Discovery]     4. Binder kernel driver issue\n");
        return -1;
    }
    printf("[Discovery] ✓ Local Device: %s (NetworkId: %s)\n",
           localInfo.deviceName, localInfo.networkId);

    // Wait for device discovery
    printf("[Discovery] Waiting for peer devices (15 seconds timeout)...\n");
    for (int i = 0; i < 15; i++) {
        sleep(1);
        printf("[Discovery] Wait: %d/15 seconds", i + 1);
        if (g_discovery_complete) {
            printf(" - Device found!\n");
            break;
        }
        printf("\n");
    }

    if (g_discoveredDevices.empty()) {
        printf("[Discovery] ✗ No peer devices discovered\n");
        printf("[Discovery] NOTE: This may be expected if no peer is online\n");
        return 1;  // Return 1 to continue anyway
    }

    // Get all online devices
    printf("[Discovery] Fetching all online devices...\n");
    NodeBasicInfo *onlineInfo = NULL;
    int32_t onlineNum = 0;
    ret = GetAllNodeDeviceInfo(PKG_NAME, &onlineInfo, &onlineNum);
    if (ret != 0) {
        printf("[Discovery] ✗ GetAllNodeDeviceInfo failed: %d\n", ret);
        return -1;
    }

    printf("[Discovery] ✓ Total online devices: %d\n", onlineNum);
    for (int i = 0; i < onlineNum; i++) {
        printf("[Discovery]   [%d] %s (NetworkId: %s)\n", i,
               onlineInfo[i].deviceName, onlineInfo[i].networkId);
    }

    FreeNodeInfo(onlineInfo);
    return 0;
}

// ============================================================================
// Phase 2: Session Connection
// ============================================================================

int TestSessionConnection() {
    printf("\n========================================\n");
    printf("Phase 2: Session Connection\n");
    printf("========================================\n");

    if (g_discoveredDevices.empty()) {
        printf("[Session] ✗ No peer devices available for connection\n");
        printf("[Session] Skipping session connection test\n");
        return 1;  // Not a fatal error
    }

    PeerDevice& peerDevice = g_discoveredDevices[0];
    printf("[Session] Connecting to peer: %s\n", peerDevice.deviceName);

    // Create session server (listen for connections)
    printf("[Session] Creating session server...\n");
    char sessionName[256];
    snprintf(sessionName, sizeof(sessionName), "%s.server", SESSION_NAME_PREFIX);

    int ret = CreateSessionServer(PKG_NAME, sessionName, &g_sessionListener);
    if (ret != 0) {
        printf("[Session] ✗ CreateSessionServer failed: %d\n", ret);
        return -1;
    }
    printf("[Session] ✓ Session server created: %s\n", sessionName);

    // Open session to peer device
    printf("[Session] Opening session to peer...\n");
    char peerSessionName[256];
    snprintf(peerSessionName, sizeof(peerSessionName), "%s.client", SESSION_NAME_PREFIX);

    SessionAttribute attr;
    memset(&attr, 0, sizeof(attr));
    attr.dataType = TYPE_BYTES;          // From SessionType enum
    attr.linkTypeNum = 1;
    attr.linkType[0] = LINK_TYPE_WIFI_WLAN_2G;

    g_sessionId = OpenSession(sessionName, peerSessionName,
                              peerDevice.networkId, NULL, &attr);
    if (g_sessionId < 0) {
        printf("[Session] ✗ OpenSession failed: %d\n", g_sessionId);
        RemoveSessionServer(PKG_NAME, sessionName);
        return -1;
    }
    printf("[Session] ✓ Session opened: sessionId=%d\n", g_sessionId);

    // Send discovery message
    printf("[Session] Sending discovery message...\n");
    const char *discoveryMsg = "PHASE2_DISCOVERY_MESSAGE";
    ret = SendBytes(g_sessionId, (void*)discoveryMsg, strlen(discoveryMsg) + 1);
    if (ret != 0) {
        printf("[Session] ✗ SendBytes failed: %d\n", ret);
    } else {
        printf("[Session] ✓ Message sent successfully\n");
    }

    // Wait for responses
    printf("[Session] Waiting for peer responses (5 seconds)...\n");
    sleep(5);

    // Cleanup
    printf("[Session] Closing session...\n");
    CloseSession(g_sessionId);
    RemoveSessionServer(PKG_NAME, sessionName);
    printf("[Session] ✓ Cleanup complete\n");

    return 0;
}

// ============================================================================
// Main
// ============================================================================

int main(int argc, char **argv) {
    (void)argc; (void)argv;  // Suppress unused warnings

    printf("\n");
    printf("█████████████████████████████████████████████████\n");
    printf("  Phase 2 Graph Discovery Test\n");
    printf("  Permission Bypass via NativeToken Injection\n");
    printf("█████████████████████████████████████████████████\n");
    printf("\n");

    // Step 1: Inject permissions (using official dsoftbus test approach)
    printf("[Main] Step 1: Permission Injection (system_basic APL + 2 permissions)\n");
    int permRet = SetSoftbusNativeTokenPermission(PKG_NAME);
    if (permRet != 0) {
        printf("[Main] ⚠ Permission setup failed (error=%d), continuing anyway...\n", permRet);
    }

    // Step 2: Device discovery
    printf("\n[Main] Step 2: Device Discovery\n");
    int discoveryRet = TestDeviceDiscovery();
    if (discoveryRet < 0) {
        printf("[Main] ✗ Device discovery test failed\n");
        return 1;
    }

    // Step 3: Session connection
    printf("\n[Main] Step 3: Session Connection\n");
    int connectionRet = TestSessionConnection();
    if (connectionRet < 0) {
        printf("[Main] ✗ Session connection test failed\n");
        return 1;
    }

    printf("\n");
    printf("█████████████████████████████████████████████████\n");
    printf("  Phase 2 Test Completed\n");
    printf("█████████████████████████████████████████████████\n");
    printf("\n");

    return 0;
}
