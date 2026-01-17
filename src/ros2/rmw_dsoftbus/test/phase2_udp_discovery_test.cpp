/*
 * Phase 2 UDP Discovery Test
 *
 * UDP broadcast-based peer discovery + OpenHarmony Session API
 * Bypasses Bus Center IPC requirement
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dlfcn.h>
#include "udp_discovery.h"
#include "softbus_bus_center.h"
#include "session.h"

// Permission bypass utility (based on dsoftbus official test approach)
#include "softbus_permission_bypass.h"

// Framework initialization
extern "C" {
    int32_t InitSoftBus(const char *pkgName);
}

#define PKG_NAME "com.ros2.udp_discovery"
#define SESSION_NAME "ros2_udp_session"

static bool g_running = true;
static int g_session_id = -1;

// ============================================================================
// Signal Handler
// ============================================================================

void signal_handler(int sig) {
    printf("\n[Main] Received signal %d, shutting down...\n", sig);
    g_running = false;
}

// ============================================================================
// Session Callbacks
// ============================================================================

static int OnSessionOpened(int sessionId, int result) {
    printf("[Session] ✓✓✓ Session OPENED: sessionId=%d, result=%d\n", sessionId, result);
    g_session_id = sessionId;
    return 0;
}

static void OnSessionClosed(int sessionId) {
    printf("[Session] Session CLOSED: sessionId=%d\n", sessionId);
    if (g_session_id == sessionId) {
        g_session_id = -1;
    }
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓✓✓ Received %u bytes on session %d: %.*s\n",
           len, sessionId, len, (const char*)data);
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓✓✓ Message received on session %d: %u bytes\n", sessionId, len);
}

static ISessionListener g_listener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

// Permission injection removed - now using softbus_permission_bypass.h
// Official dsoftbus test approach: system_basic APL + 2 permissions

// ============================================================================
// Main
// ============================================================================

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("█████████████████████████████████████████████████\n");
    printf("  Phase 2 UDP Discovery Test\n");
    printf("  UDP Broadcast + OpenHarmony Session API\n");
    printf("█████████████████████████████████████████████████\n\n");

    // Step 1: 权限注入 (using official dsoftbus test approach)
    printf("[Main] Step 1: Permission Injection (system_basic APL + 2 permissions)\n");
    int permRet = SetSoftbusNativeTokenPermission(PKG_NAME);
    if (permRet != 0) {
        printf("[Main] Warning: Permission setup failed (error=%d), continuing anyway...\n", permRet);
    } else {
        printf("[Main] ✓ Permission setup successful\n");
    }
    printf("\n");

    // Step 2: 初始化 SoftBus
    printf("[Main] Step 2: SoftBus Initialization\n");
    int ret = InitSoftBus(PKG_NAME);
    if (ret != 0) {
        printf("[Main] Warning: InitSoftBus returned %d\n", ret);
    } else {
        printf("[Main] ✓ InitSoftBus successful\n");
    }
    printf("\n");

    // Step 3: 获取本地 network ID
    printf("[Main] Step 3: Getting Local Network ID\n");
    std::string local_network_id;

    NodeBasicInfo info;
    memset(&info, 0, sizeof(info));
    ret = GetLocalNodeDeviceInfo(PKG_NAME, &info);
    if (ret == 0) {
        local_network_id = info.networkId;
        printf("[Main] ✓ Network ID from Bus Center: %s\n", local_network_id.c_str());
    } else {
        printf("[Main] GetLocalNodeDeviceInfo failed: %d (0x%x)\n", ret, (unsigned int)ret);
        printf("[Main] Using fallback boot_id as network ID...\n");

        UdpDiscovery temp_discovery;
        local_network_id = temp_discovery.get_fallback_network_id();
        printf("[Main] ✓ Network ID from boot_id: %s\n", local_network_id.c_str());
    }
    printf("\n");

    // Step 4: 创建 Session Server
    printf("[Main] Step 4: Creating Session Server\n");
    ret = CreateSessionServer(PKG_NAME, SESSION_NAME, &g_listener);
    if (ret != 0) {
        printf("[Main] ✗ CreateSessionServer failed: %d\n", ret);
        return -1;
    }
    printf("[Main] ✓ Session server created for session name: %s\n", SESSION_NAME);
    printf("\n");

    // Step 5: 启动 UDP 发现
    printf("[Main] Step 5: Starting UDP Discovery\n");
    UdpDiscovery discovery(8888);
    if (!discovery.start(local_network_id, "kaihong_board")) {
        printf("[Main] ✗ Failed to start UDP discovery\n");
        RemoveSessionServer(PKG_NAME, SESSION_NAME);
        return -1;
    }
    printf("[Main] ✓ UDP discovery started\n");
    printf("\n");

    // Step 6: 等待发现设备
    printf("[Main] Step 6: Waiting for Peer Discovery\n");
    printf("[Main] Listening for peer broadcasts (will wait up to 10 seconds)...\n");

    std::vector<PeerDevice> peers;
    for (int i = 0; i < 10 && g_running; i++) {
        sleep(1);
        peers = discovery.get_peers();
        printf("[Main] Wait %d/10 seconds, found %zu peer(s)\r", i + 1, peers.size());
        fflush(stdout);

        if (!peers.empty()) {
            printf("\n[Main] ✓ Peer discovered!\n");
            break;
        }
    }
    printf("\n");

    if (peers.empty()) {
        printf("[Main] No peers found after 10 seconds\n");
        printf("[Main] This device is broadcasting and ready to accept connections\n");
        printf("[Main] Waiting for incoming connections (Ctrl+C to exit)...\n\n");

        while (g_running) {
            sleep(1);
            peers = discovery.get_peers();
            if (!peers.empty()) {
                printf("[Main] ✓ Peer discovered: %s (%s)\n",
                       peers[0].device_name.c_str(), peers[0].network_id.c_str());
                break;
            }
        }
    }

    // Step 7: 连接到第一个 peer
    if (!peers.empty() && g_running) {
        const auto& peer = peers[0];
        printf("\n[Main] Step 7: Opening Session to Peer\n");
        printf("[Main] Peer info:\n");
        printf("  - Device Name: %s\n", peer.device_name.c_str());
        printf("  - Network ID:  %s\n", peer.network_id.c_str());
        printf("  - IP Address:  %s:%u\n", peer.ip_address.c_str(), peer.port);

        SessionAttribute attr;
        memset(&attr, 0, sizeof(attr));
        attr.dataType = TYPE_BYTES;

        printf("[Main] Calling OpenSession...\n");
        int sessionId = OpenSession(PKG_NAME, SESSION_NAME,
                                    peer.network_id.c_str(),
                                    "default", &attr);

        if (sessionId >= 0) {
            printf("[Main] ✓✓✓ Session opened successfully: sessionId=%d\n", sessionId);
            g_session_id = sessionId;

            // Step 8: 发送测试消息
            printf("\n[Main] Step 8: Sending Test Message\n");
            sleep(1); // 等待会话完全建立

            const char *msg = "Hello from UDP discovery test!";
            ret = SendBytes(sessionId, (const uint8_t*)msg, strlen(msg));
            if (ret == 0) {
                printf("[Main] ✓ Message sent: \"%s\"\n", msg);
            } else {
                printf("[Main] ✗ SendBytes failed: %d\n", ret);
            }

            // Step 9: 等待接收
            printf("\n[Main] Step 9: Waiting for Messages\n");
            printf("[Main] Listening for incoming data (Ctrl+C to exit)...\n\n");

            int idle_seconds = 0;
            while (g_running && idle_seconds < 30) {
                sleep(1);
                idle_seconds++;

                // 定期发送心跳消息
                if (idle_seconds % 5 == 0) {
                    char heartbeat[64];
                    snprintf(heartbeat, sizeof(heartbeat), "Heartbeat #%d", idle_seconds / 5);
                    SendBytes(sessionId, (const uint8_t*)heartbeat, strlen(heartbeat));
                    printf("[Main] Sent heartbeat: %s\n", heartbeat);
                }
            }

            printf("\n[Main] Closing session...\n");
            CloseSession(sessionId);
        } else {
            printf("[Main] ✗ OpenSession failed: %d\n", sessionId);
        }
    }

    // 清理
    printf("\n[Main] Cleanup\n");
    discovery.stop();
    RemoveSessionServer(PKG_NAME, SESSION_NAME);

    printf("\n█████████████████████████████████████████████████\n");
    printf("  Test Complete\n");
    printf("█████████████████████████████████████████████████\n");

    return 0;
}
