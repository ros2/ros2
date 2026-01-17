/*
 * Phase 2 Graph Discovery Test with Permission Bypass
 *
 * Purpose: Test 2-device discovery and session connection using OpenHarmony
 * NativeToken permission bypass method (similar to khdeviceauth_tool approach)
 *
 * Flow:
 * 1. Inject NativeToken permissions for softbus access
 * 2. Initialize dsoftbus bus center
 * 3. Discover peer devices
 * 4. Establish session server
 * 5. Connect to peer device session
 * 6. Exchange discovery messages
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>
#include <dlfcn.h>

// OpenHarmony dsoftbus headers
#include "softbus_bus_center.h"
#include "softbus_common.h"
#include "session.h"
#include "socket.h"

// Permission bypass utility (based on dsoftbus official test approach)
#include "softbus_permission_bypass.h"

// ============================================================================
// Global State
// ============================================================================

static const char* PKG_NAME = "com.softbus_graph_discovery.test";
static const char* SESSION_NAME_PREFIX = "com.huawei.ros2.graph.discovery";

struct PeerDeviceInfo {
    char networkId[NETWORK_ID_BUF_LEN];
    char devName[DEVICE_NAME_BUF_LEN];
};

static std::vector<PeerDeviceInfo> g_discoveredDevices;
static int g_sessionId = -1;
static int g_peerSessionId = -1;

// Permission injection removed - now using softbus_permission_bypass.h
// Official dsoftbus test approach with system_basic APL and 2 permissions

// ============================================================================
// Bus Center Callbacks
// ============================================================================

void OnNodeOnline(NodeBasicInfo *info) {
    if (info == NULL) return;

    printf("\n[Discovery] === OnNodeOnline ===\n");
    printf("[Discovery] Device: %s (NetworkId: %s)\n",
           info->deviceName, info->networkId);

    // Store device info
    PeerDeviceInfo devInfo;
    strncpy(devInfo.networkId, info->networkId, NETWORK_ID_BUF_LEN - 1);
    strncpy(devInfo.devName, info->deviceName, DEVICE_NAME_BUF_LEN - 1);
    g_discoveredDevices.push_back(devInfo);
}

void OnNodeOffline(NodeBasicInfo *info) {
    if (info == NULL) return;
    printf("\n[Discovery] OnNodeOffline: %s\n", info->networkId);
}

void OnDeviceInfoChanged(NodeBasicInfoType type, NodeBasicInfo *info) {
    printf("[Discovery] OnDeviceInfoChanged: type=%d\n", type);
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
    printf("\n[Session] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);
    if (result == 0) {
        g_peerSessionId = sessionId;
    }
    return 0;  // Return 0 to accept the session
}

void OnSessionClosed(int sessionId) {
    printf("[Session] OnSessionClosed: sessionId=%d\n", sessionId);
}

void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen) {
    printf("[Session] OnBytesReceived: sessionId=%d, len=%u\n", sessionId, dataLen);
    printf("[Session] Data: %.*s\n", dataLen, (const char*)data);
}

void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen) {
    printf("[Session] OnMessageReceived: sessionId=%d, len=%u\n", sessionId, dataLen);
    printf("[Session] Data: %.*s\n", dataLen, (const char*)data);
}

void OnStreamReceived(int sessionId, const StreamData *data, const StreamData *ext,
                      const StreamFrameInfo *param) {
    printf("[Session] OnStreamReceived: sessionId=%d\n", sessionId);
}

void OnQosEvent(int sessionId, int eventId, int tvCount, const QosTv *tvList) {
    (void)tvCount;  (void)tvList;  // Suppress unused warnings
    printf("[Session] OnQosEvent: sessionId=%d, eventId=%d\n", sessionId, eventId);
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
// Test Phase 2: Device Discovery
// ============================================================================

int TestDeviceDiscovery() {
    printf("\n[Phase2] === Testing Device Discovery ===\n");

    // Step 1: Initialize bus center
    printf("[Phase2] Registering device state callback...\n");
    int ret = RegNodeDeviceStateCb(PKG_NAME, &g_nodeStateCallback);
    if (ret != 0) {
        printf("[Phase2] ERROR: RegNodeDeviceStateCb failed: %d\n", ret);
        return -1;
    }

    // Step 2: Get local device info
    printf("[Phase2] Getting local device info...\n");
    NodeBasicInfo localInfo;
    ret = GetLocalNodeDeviceInfo(PKG_NAME, &localInfo);
    if (ret != 0) {
        printf("[Phase2] ERROR: GetLocalNodeDeviceInfo failed: %d\n", ret);
        return -1;
    }
    printf("[Phase2] Local Device: %s (NetworkId: %s)\n",
           localInfo.deviceName, localInfo.networkId);

    // Step 3: Wait for device discovery
    printf("[Phase2] Waiting for peer devices (timeout: 10 seconds)...\n");
    for (int i = 0; i < 10; i++) {
        sleep(1);
        printf("[Phase2] Discovery wait: %d/10 seconds\n", i + 1);
        if (!g_discoveredDevices.empty()) {
            printf("[Phase2] Found %lu peer device(s)\n", g_discoveredDevices.size());
            break;
        }
    }

    if (g_discoveredDevices.empty()) {
        printf("[Phase2] WARNING: No peer devices discovered\n");
        return -1;
    }

    // Step 4: Get all online devices
    printf("[Phase2] Fetching all online devices...\n");
    NodeBasicInfo *onlineInfo = NULL;
    int32_t onlineNum = 0;
    ret = GetAllNodeDeviceInfo(PKG_NAME, &onlineInfo, &onlineNum);
    if (ret != 0) {
        printf("[Phase2] ERROR: GetAllNodeDeviceInfo failed: %d\n", ret);
        return -1;
    }

    printf("[Phase2] Total online devices: %d\n", onlineNum);
    for (int i = 0; i < onlineNum; i++) {
        printf("[Phase2]   Device %d: %s (NetworkId: %s)\n", i,
               onlineInfo[i].deviceName, onlineInfo[i].networkId);
    }

    FreeNodeInfo(onlineInfo);
    return 0;
}

// ============================================================================
// Test Phase 2: Session Connection
// ============================================================================

int TestSessionConnection() {
    printf("\n[Phase2] === Testing Session Connection ===\n");

    if (g_discoveredDevices.empty()) {
        printf("[Phase2] ERROR: No peer devices available\n");
        return -1;
    }

    PeerDeviceInfo& peerDevice = g_discoveredDevices[0];
    printf("[Phase2] Connecting to peer: %s (NetworkId: %s)\n",
           peerDevice.devName, peerDevice.networkId);

    // Step 1: Create session server
    printf("[Phase2] Creating session server...\n");
    char sessionName[256];
    snprintf(sessionName, sizeof(sessionName), "%s.server", SESSION_NAME_PREFIX);

    int ret = CreateSessionServer(PKG_NAME, sessionName, &g_sessionListener);
    if (ret != 0) {
        printf("[Phase2] ERROR: CreateSessionServer failed: %d\n", ret);
        return -1;
    }
    printf("[Phase2] Session server created: %s\n", sessionName);

    // Step 2: Open session to peer
    printf("[Phase2] Opening session to peer...\n");
    char peerSessionName[256];
    snprintf(peerSessionName, sizeof(peerSessionName), "%s.client", SESSION_NAME_PREFIX);

    SessionAttribute attr;
    memset(&attr, 0, sizeof(attr));
    attr.dataType = TYPE_BYTES;
    attr.linkTypeNum = 1;
    attr.linkType[0] = LINK_TYPE_WIFI_WLAN_2G;

    g_peerSessionId = OpenSession(sessionName, peerSessionName,
                                   peerDevice.networkId, NULL, &attr);
    if (g_peerSessionId < 0) {
        printf("[Phase2] ERROR: OpenSession failed: %d\n", g_peerSessionId);
        RemoveSessionServer(PKG_NAME, sessionName);
        return -1;
    }
    printf("[Phase2] Session opened successfully: sessionId=%d\n", g_peerSessionId);

    // Step 3: Send discovery message
    printf("[Phase2] Sending discovery message...\n");
    const char *discoveryMsg = "PHASE2_DISCOVERY_TEST_MSG";
    ret = SendBytes(g_peerSessionId, (void*)discoveryMsg, strlen(discoveryMsg) + 1);
    if (ret != 0) {
        printf("[Phase2] ERROR: SendBytes failed: %d\n", ret);
    } else {
        printf("[Phase2] Discovery message sent successfully\n");
    }

    // Step 4: Wait for responses
    printf("[Phase2] Waiting for peer responses (5 seconds)...\n");
    sleep(5);

    // Step 5: Cleanup
    printf("[Phase2] Closing session...\n");
    CloseSession(g_peerSessionId);
    RemoveSessionServer(PKG_NAME, sessionName);

    return 0;
}

// ============================================================================
// Main Test Execution
// ============================================================================

int main(int argc, char **argv) {
    printf("\n");
    printf("=========================================\n");
    printf("Phase 2 Graph Discovery Test\n");
    printf("With Permission Bypass (khdeviceauth_tool approach)\n");
    printf("=========================================\n\n");

    // Step 1: Inject permissions (using official dsoftbus test approach)
    printf("[Main] Step 1: Setting NativeToken permissions...\n");
    int permRet = SetSoftbusNativeTokenPermission(PKG_NAME);
    if (permRet != 0) {
        printf("[Main] WARNING: Permission setup failed (error=%d)\n", permRet);
        printf("[Main] Continuing anyway (may encounter permission errors)...\n");
    }

    // Step 2: Device discovery
    printf("\n[Main] Step 2: Device discovery phase...\n");
    int discoveryRet = TestDeviceDiscovery();
    if (discoveryRet != 0) {
        printf("[Main] Device discovery test failed\n");
        return 1;
    }

    // Step 3: Session connection
    printf("\n[Main] Step 3: Session connection phase...\n");
    int connectionRet = TestSessionConnection();
    if (connectionRet != 0) {
        printf("[Main] Session connection test failed\n");
        return 1;
    }

    printf("\n");
    printf("=========================================\n");
    printf("Phase 2 Test Completed Successfully\n");
    printf("=========================================\n\n");

    return 0;
}
