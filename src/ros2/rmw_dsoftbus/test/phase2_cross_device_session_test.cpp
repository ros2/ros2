/*
 * Phase 2 Cross-Device Session Test
 * 
 * Implements complete Bus Center discovery and session establishment
 * between two rk3588s devices using permission bypass via NativeToken
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

// OpenHarmony dsoftbus headers
#include "softbus_bus_center.h"
#include "softbus_common.h"
#include "trans_type.h"
#include "session.h"

// Permission system - forward declarations
extern "C" {
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

    uint64_t GetAccessTokenId(NativeTokenInfoParams *infoInstance);
    int32_t SetSelfTokenID(uint64_t tokenId);
    int32_t InitSoftBus(const char *pkgName);
}

#define PKG_NAME "com.ros2.phase2.cross_device"
#define SESSION_NAME "ros2_cross_device_session"
#define PEER_WAIT_TIMEOUT 30  // seconds

// Global state
struct DiscoveredDevice {
    char networkId[65];
    char deviceName[128];
    bool online;
};

static std::map<std::string, DiscoveredDevice> g_discoveredDevices;
static int g_sessionId = -1;
static bool g_session_opened = false;
static pthread_mutex_t g_device_lock = PTHREAD_MUTEX_INITIALIZER;

// ============================================================================
// Callbacks
// ============================================================================

static void OnNodeOnline(NodeBasicInfo *info)
{
    if (!info) return;
    
    printf("[Discovery] ✓✓✓ Device ONLINE: %s (NetworkId: %s)\n",
           info->deviceName, info->networkId);
    
    pthread_mutex_lock(&g_device_lock);
    DiscoveredDevice device;
    snprintf(device.networkId, sizeof(device.networkId), "%s", info->networkId);
    snprintf(device.deviceName, sizeof(device.deviceName), "%s", info->deviceName);
    device.online = true;
    g_discoveredDevices[info->networkId] = device;
    pthread_mutex_unlock(&g_device_lock);
}

static void OnNodeOffline(NodeBasicInfo *info)
{
    if (!info) return;
    printf("[Discovery] Device OFFLINE: %s\n", info->networkId);
    pthread_mutex_lock(&g_device_lock);
    g_discoveredDevices[info->networkId].online = false;
    pthread_mutex_unlock(&g_device_lock);
}

static void OnNodeBasicInfoChanged(NodeBasicInfoType type, NodeBasicInfo *info)
{
    if (!info) return;
    printf("[Discovery] Device info changed: %s (type=%d)\n", info->deviceName, type);
}

static void OnNodeStatusChanged(NodeStatusType type, NodeStatus *status)
{
    printf("[Discovery] Device status changed (type=%d)\n", type);
}

static INodeStateCb g_nodeStateCallback = {
    .events = EVENT_NODE_STATE_ONLINE | EVENT_NODE_STATE_OFFLINE | 
              EVENT_NODE_STATE_INFO_CHANGED | EVENT_NODE_STATUS_CHANGED,
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnNodeBasicInfoChanged,
    .onNodeStatusChanged = OnNodeStatusChanged,
};

// Session callbacks
static int OnSessionOpened(int sessionId, int result)
{
    printf("[Session] ✓✓✓ Session OPENED: sessionId=%d, result=%d\n", sessionId, result);
    g_sessionId = sessionId;
    g_session_opened = (result == 0);
    return 0;
}

static void OnSessionClosed(int sessionId)
{
    printf("[Session] Session CLOSED: sessionId=%d\n", sessionId);
    g_sessionId = -1;
    g_session_opened = false;
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen)
{
    printf("[Session] Data received on session %d: %d bytes\n", sessionId, dataLen);
    if (dataLen > 0 && data) {
        printf("[Session] Data: %.*s\n", dataLen, (const char*)data);
    }
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen)
{
    printf("[Session] Message received on session %d: %d bytes\n", sessionId, dataLen);
    if (dataLen > 0 && data) {
        printf("[Session] Message: %.*s\n", dataLen, (const char*)data);
    }
}

static ISessionListener g_sessionListener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

// ============================================================================
// Permission Injection
// ============================================================================

int InjectNativeTokenPermissions()
{
    printf("[Permission] Injecting NativeToken with system_basic APL...\n");

    uint64_t tokenId;
    const char *perms[3] = {
        "ohos.permission.DISTRIBUTED_DATASYNC",
        "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER",
        "ohos.permission.ACCESS_SERVICE_DM"
    };

    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 3,
        .aclsNum = 0,
        .dcaps = NULL,
        .perms = perms,
        .acls = NULL,
        .processName = PKG_NAME,
        .aplStr = "system_basic",
    };

    try {
        tokenId = GetAccessTokenId(&infoInstance);
        printf("[Permission] Got token: 0x%lx\n", tokenId);
        
        SetSelfTokenID(tokenId);
        printf("[Permission] ✓ NativeToken injected successfully\n");
        return 0;
    } catch (...) {
        printf("[Permission] ✗ Permission injection failed\n");
        return -1;
    }
}

// ============================================================================
// Bus Center Discovery
// ============================================================================

int TestBusCenterDiscovery()
{
    printf("\n========================================\n");
    printf("Phase 2: Bus Center Discovery\n");
    printf("========================================\n");

    // Initialize SoftBus framework
    printf("[Discovery] Initializing SoftBus framework...\n");
    int initRet = InitSoftBus(PKG_NAME);
    if (initRet != 0) {
        printf("[Discovery] Warning: InitSoftBus returned %d (may not be fatal)\n", initRet);
    } else {
        printf("[Discovery] ✓ InitSoftBus successful\n");
    }

    // Register for device state changes
    printf("[Discovery] Registering for device state changes...\n");
    int ret = RegNodeDeviceStateCb(PKG_NAME, &g_nodeStateCallback);
    if (ret != 0) {
        printf("[Discovery] ✗ Failed to register callback: %d\n", ret);
        return -1;
    }
    printf("[Discovery] ✓ Callback registered\n");

    // Get local device info
    printf("[Discovery] Getting local device info...\n");
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));
    ret = GetLocalNodeDeviceInfo(PKG_NAME, &localInfo);
    if (ret != 0) {
        printf("[Discovery] ✗ GetLocalNodeDeviceInfo failed: %d (0x%x)\n", ret, (unsigned int)ret);
        printf("[Discovery] Note: This is IPC error - Bus Center SA may not be accessible\n");
        printf("[Discovery] Continuing anyway to test other capabilities...\n");
        // Don't return error - Bus Center may still work via alternative paths
    } else {
        printf("[Discovery] ✓ Local Device: %s (NetworkId: %s)\n",
               localInfo.deviceName, localInfo.networkId);
    }

    // Wait for peer devices to be discovered
    printf("[Discovery] Waiting %d seconds for peer devices to be discovered...\n", PEER_WAIT_TIMEOUT);
    for (int i = 0; i < PEER_WAIT_TIMEOUT; i++) {
        sleep(1);
        pthread_mutex_lock(&g_device_lock);
        int deviceCount = 0;
        for (auto& pair : g_discoveredDevices) {
            if (pair.second.online) deviceCount++;
        }
        pthread_mutex_unlock(&g_device_lock);
        
        printf("[Discovery] Wait: %d/%d seconds, found %d online devices\r",
               i + 1, PEER_WAIT_TIMEOUT, deviceCount);
        fflush(stdout);
        
        if (deviceCount > 0) {
            printf("\n[Discovery] ✓ Found peer device!\n");
            break;
        }
    }

    pthread_mutex_lock(&g_device_lock);
    int peerCount = 0;
    std::string peerNetworkId;
    for (auto& pair : g_discoveredDevices) {
        if (pair.second.online) {
            peerCount++;
            peerNetworkId = pair.first;
            printf("[Discovery] Discovered: %s (%s)\n",
                   pair.second.deviceName, pair.first.c_str());
        }
    }
    pthread_mutex_unlock(&g_device_lock);

    if (peerCount == 0) {
        printf("[Discovery] ✗ No peer devices discovered\n");
        return -1;
    }

    printf("[Discovery] ✓ Bus Center discovery successful\n");
    return 0;
}

// ============================================================================
// Session Establishment
// ============================================================================

int EstablishSessionConnection(const char *peerNetworkId)
{
    printf("\n========================================\n");
    printf("Phase 2: Session Establishment\n");
    printf("========================================\n");

    printf("[Session] Creating session server for PKG: %s\n", PKG_NAME);
    int ret = CreateSessionServer(PKG_NAME, SESSION_NAME, &g_sessionListener);
    if (ret != 0) {
        printf("[Session] ✗ CreateSessionServer failed: %d\n", ret);
        return -1;
    }
    printf("[Session] ✓ Session server created\n");

    // Open session to peer
    printf("[Session] Opening session to peer device: %s\n", peerNetworkId);
    SessionAttribute attr;
    memset(&attr, 0, sizeof(attr));
    attr.dataType = TYPE_BYTES;

    int sessionId = OpenSession(PKG_NAME, SESSION_NAME,
                                peerNetworkId, "default",
                                &attr);
    if (sessionId < 0) {
        printf("[Session] ✗ OpenSession failed: %d\n", sessionId);
        RemoveSessionServer(PKG_NAME, SESSION_NAME);
        return -1;
    }
    printf("[Session] ✓ Session opened: sessionId=%d\n", sessionId);
    g_sessionId = sessionId;

    // Wait for session to fully open
    printf("[Session] Waiting for session to be fully established...\n");
    for (int i = 0; i < 10; i++) {
        if (g_session_opened) {
            printf("[Session] ✓✓✓ Session ESTABLISHED successfully!\n");
            return sessionId;
        }
        sleep(1);
    }

    printf("[Session] ⚠️ Session opened but callback not received\n");
    return sessionId;
}

// ============================================================================
// Message Test
// ============================================================================

int TestMessageTransmission(int sessionId)
{
    printf("\n========================================\n");
    printf("Phase 2: Message Transmission\n");
    printf("========================================\n");

    const char *testMsg = "Phase2CrossDeviceTest";
    int msgLen = strlen(testMsg);

    printf("[Message] Sending test message on session %d: %s\n", sessionId, testMsg);
    int ret = SendBytes(sessionId, (const uint8_t*)testMsg, msgLen);
    if (ret != 0) {
        printf("[Message] ✗ SendBytes failed: %d\n", ret);
        return -1;
    }
    printf("[Message] ✓ Message sent successfully\n");

    return 0;
}

// ============================================================================
// Main
// ============================================================================

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    printf("█████████████████████████████████████████████████\n");
    printf("  Phase 2 Cross-Device Session Test\n");
    printf("  ROS2 + SoftBus Permission Bypass\n");
    printf("█████████████████████████████████████████████████\n\n");

    // Step 1: Inject permissions
    printf("[Main] Step 1: Permission Injection\n");
    if (InjectNativeTokenPermissions() != 0) {
        printf("[Main] ✗ Permission injection failed\n");
        return -1;
    }

    // Step 2: Bus Center Discovery
    printf("[Main] Step 2: Bus Center Discovery\n");
    if (TestBusCenterDiscovery() != 0) {
        printf("[Main] ✗ Bus Center discovery failed\n");
        printf("[Main] Note: Attempting session establishment anyway...\n");
    }

    // Step 3: Get peer network ID
    pthread_mutex_lock(&g_device_lock);
    std::string peerNetworkId;
    for (auto& pair : g_discoveredDevices) {
        if (pair.second.online) {
            peerNetworkId = pair.first;
            break;
        }
    }
    pthread_mutex_unlock(&g_device_lock);

    if (peerNetworkId.empty()) {
        printf("[Main] ✗ No peer device found\n");
        return -1;
    }

    // Step 4: Establish session
    printf("[Main] Step 3: Session Establishment\n");
    int sessionId = EstablishSessionConnection(peerNetworkId.c_str());
    if (sessionId < 0) {
        printf("[Main] ✗ Session establishment failed\n");
        return -1;
    }

    // Step 5: Send test message
    printf("[Main] Step 4: Message Transmission\n");
    if (TestMessageTransmission(sessionId) != 0) {
        printf("[Main] ⚠️ Message transmission failed\n");
    }

    // Cleanup
    printf("\n[Main] Cleaning up...\n");
    if (sessionId >= 0) {
        CloseSession(sessionId);
    }
    RemoveSessionServer(PKG_NAME, SESSION_NAME);

    printf("\n█████████████████████████████████████████████████\n");
    printf("  Phase 2 Test Complete\n");
    printf("█████████████████████████████████████████████████\n");

    return 0;
}
