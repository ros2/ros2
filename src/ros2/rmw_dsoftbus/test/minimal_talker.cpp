// Minimal Talker - ROS2 rmw_dsoftbus Cross-Device Communication Test
// Publisher side: sends test messages via dsoftbus to remote listener
//
// Usage:
//   export RMW_DSOFTBUS_PEER_ID=<listener_device_network_id>
//   ./minimal_talker
//
// Expects listener to be running on the peer device first.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <atomic>
#include <thread>
#include <chrono>

#include "rmw_dsoftbus/session_manager.h"
#include "rmw_dsoftbus/native_token.h"

static std::atomic<bool> g_running{true};
static std::atomic<int> g_messages_sent{0};

void signal_handler(int sig) {
    (void)sig;
    g_running = false;
}

// Topic name for the test
static const char* TOPIC_NAME = "rmw_dsoftbus_test_topic";

// Message structure
struct TestMessage {
    uint32_t sequence;
    uint64_t timestamp_ns;
    char data[256];
};

// External function to get local network ID (from dsoftbus_stubs.cpp)
extern "C" {
    struct NodeBasicInfo {
        char networkId[65];
        char deviceName[128];
        uint16_t deviceTypeId;
        int32_t osType;
        char osVersion[128];
    };
    int GetLocalNodeDeviceInfo(const char* pkgName, NodeBasicInfo* info);
}

// Forward declaration for subscription (needed for session server registration)
namespace rmw_dsoftbus {
struct SubscriptionImpl {
    std::string topic_name;
    void* user_data;
    void (*on_message)(const void* data, size_t len, void* user_data);
};
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    fprintf(stderr, "\n");
    fprintf(stderr, "================================================\n");
    fprintf(stderr, " RMW DSoftBus Minimal Talker (Publisher)\n");
    fprintf(stderr, "================================================\n\n");
    fflush(stderr);

    fprintf(stderr, "[INFO] PID=%d UID=%d GID=%d\n", getpid(), getuid(), getgid());

    // Check for peer network ID
    const char* peer_id = getenv("RMW_DSOFTBUS_PEER_ID");
    if (!peer_id || strlen(peer_id) == 0) {
        fprintf(stderr, "\n[ERROR] RMW_DSOFTBUS_PEER_ID environment variable not set!\n");
        fprintf(stderr, "        Run './minimal_listener' on the listener device first.\n");
        fprintf(stderr, "        It will display its network ID.\n");
        fprintf(stderr, "        Then: export RMW_DSOFTBUS_PEER_ID=<network_id>\n\n");
        return 1;
    }
    fprintf(stderr, "[INFO] Target peer network ID: %.32s...\n\n", peer_id);
    fflush(stderr);

    // Initialize native token for dsoftbus permissions
    fprintf(stderr, "[TOKEN] Initializing native token...\n");
    bool token_ok = rmw_dsoftbus::try_init_native_token();
    if (token_ok) {
        fprintf(stderr, "[TOKEN] Native token initialized successfully\n");
    } else {
        fprintf(stderr, "[TOKEN] Native token init skipped (may still work with system permissions)\n");
    }
    fprintf(stderr, "\n");
    fflush(stderr);

    // Initialize SessionManager
    fprintf(stderr, "[SESSION] Initializing SessionManager...\n");
    auto& session_mgr = rmw_dsoftbus::SessionManager::instance();

    if (!session_mgr.initialize()) {
        fprintf(stderr, "[ERROR] SessionManager initialization failed!\n");
        return 1;
    }
    fprintf(stderr, "[SESSION] SessionManager initialized\n");

    // Get local network ID
    NodeBasicInfo local_info;
    memset(&local_info, 0, sizeof(local_info));
    if (GetLocalNodeDeviceInfo("rmw_dsoftbus", &local_info) == 0) {
        fprintf(stderr, "[SESSION] Local network ID: %.32s...\n", local_info.networkId);
    }
    fprintf(stderr, "\n");
    fflush(stderr);

    // Register our own session server first (required for dsoftbus bidirectional communication)
    // Even the active side (talker) needs a session server registered for the session to work
    fprintf(stderr, "[REGISTER] Registering local session server...\n");
    rmw_dsoftbus::SubscriptionImpl dummy_sub;  // Dummy subscription for server registration
    dummy_sub.topic_name = TOPIC_NAME;
    dummy_sub.user_data = nullptr;
    dummy_sub.on_message = nullptr;
    int reg_ret = session_mgr.register_subscription(TOPIC_NAME, &dummy_sub);
    if (reg_ret < 0) {
        fprintf(stderr, "[WARNING] Failed to register local session server (may still work): %d\n", reg_ret);
    } else {
        fprintf(stderr, "[REGISTER] Local session server registered\n");
    }
    fprintf(stderr, "\n");
    fflush(stderr);

    // As Publisher: Open session to peer (active side)
    fprintf(stderr, "[CONNECT] Opening session to peer device...\n");
    fprintf(stderr, "[CONNECT] Topic name: %s\n", TOPIC_NAME);
    fflush(stderr);

    int session_id = session_mgr.open_session(TOPIC_NAME, peer_id);
    if (session_id < 0) {
        fprintf(stderr, "[ERROR] Failed to open session to peer! Error code: %d\n", session_id);
        fprintf(stderr, "        Make sure:\n");
        fprintf(stderr, "        1. Listener is running on the peer device\n");
        fprintf(stderr, "        2. Both devices are on the same network\n");
        fprintf(stderr, "        3. softbus_trans_permission.json is configured correctly\n");
        return 1;
    }
    fprintf(stderr, "[CONNECT] Session opened! Session ID: %d\n\n", session_id);
    fflush(stderr);

    // Send test messages
    fprintf(stderr, "[TALKER] Starting message transmission (10 messages, 1 per second)...\n");
    fprintf(stderr, "         Press Ctrl+C to stop.\n\n");
    fflush(stderr);

    TestMessage msg;
    memset(&msg, 0, sizeof(msg));

    for (int i = 0; i < 10 && g_running; i++) {
        msg.sequence = i + 1;

        // Get current timestamp
        auto now = std::chrono::system_clock::now();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            now.time_since_epoch()).count();
        msg.timestamp_ns = static_cast<uint64_t>(ns);

        snprintf(msg.data, sizeof(msg.data),
                 "Hello from minimal_talker [%d] at %lu ns",
                 msg.sequence, msg.timestamp_ns);

        // Send message
        int ret = session_mgr.send_bytes(session_id, &msg, sizeof(msg));
        if (ret == 0) {
            g_messages_sent++;
            fprintf(stderr, "[TX] Message #%d sent: \"%s\"\n", msg.sequence, msg.data);
        } else {
            fprintf(stderr, "[TX] Message #%d send failed! Error: %d\n", msg.sequence, ret);
        }
        fflush(stderr);

        // Wait 1 second between messages
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Summary
    fprintf(stderr, "\n");
    fprintf(stderr, "================================================\n");
    fprintf(stderr, " Transmission Complete\n");
    fprintf(stderr, "================================================\n");
    fprintf(stderr, " Messages sent:     %d\n", g_messages_sent.load());
    fprintf(stderr, " Target peer:       %.32s...\n", peer_id);
    fprintf(stderr, "================================================\n\n");
    fflush(stderr);

    // Cleanup
    fprintf(stderr, "[CLEANUP] Closing session...\n");
    session_mgr.close_session(session_id);
    session_mgr.shutdown();
    fprintf(stderr, "[CLEANUP] Done.\n");

    return (g_messages_sent >= 10) ? 0 : 1;
}
