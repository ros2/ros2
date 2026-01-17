// Minimal Listener - ROS2 rmw_dsoftbus Cross-Device Communication Test
// Subscriber side: receives test messages via dsoftbus from remote talker
//
// Usage:
//   ./minimal_listener
//
// Run this first, then run minimal_talker on the other device with:
//   export RMW_DSOFTBUS_PEER_ID=<this_device_network_id>
//   ./minimal_talker

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
static std::atomic<int> g_messages_received{0};

void signal_handler(int sig) {
    (void)sig;
    g_running = false;
}

// Topic name for the test (must match talker)
static const char* TOPIC_NAME = "rmw_dsoftbus_test_topic";

// Message structure (must match talker)
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

// Simple subscription implementation for message reception
namespace rmw_dsoftbus {
struct SubscriptionImpl {
    std::string topic_name;
    void* user_data;
    void (*on_message)(const void* data, size_t len, void* user_data);
};
}

// Message callback
static void on_message_received(const void* data, size_t len, void* user_data) {
    (void)user_data;

    if (len < sizeof(TestMessage)) {
        fprintf(stderr, "[RX] Received partial message (%zu bytes, expected %zu)\n",
                len, sizeof(TestMessage));
        return;
    }

    const TestMessage* msg = static_cast<const TestMessage*>(data);

    // Calculate latency
    auto now = std::chrono::system_clock::now();
    auto now_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count();
    int64_t latency_us = (now_ns - static_cast<int64_t>(msg->timestamp_ns)) / 1000;

    g_messages_received++;
    fprintf(stderr, "[RX] Message #%u: \"%s\" (latency: %ld us)\n",
            msg->sequence, msg->data, latency_us);
    fflush(stderr);
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    fprintf(stderr, "\n");
    fprintf(stderr, "================================================\n");
    fprintf(stderr, " RMW DSoftBus Minimal Listener (Subscriber)\n");
    fprintf(stderr, "================================================\n\n");
    fflush(stderr);

    fprintf(stderr, "[INFO] PID=%d UID=%d GID=%d\n\n", getpid(), getuid(), getgid());
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

    // Get and display local network ID (for talker to use)
    NodeBasicInfo local_info;
    memset(&local_info, 0, sizeof(local_info));
    if (GetLocalNodeDeviceInfo("rmw_dsoftbus", &local_info) == 0) {
        fprintf(stderr, "\n");
        fprintf(stderr, "================================================\n");
        fprintf(stderr, " THIS DEVICE'S NETWORK ID (copy to talker):\n");
        fprintf(stderr, " %s\n", local_info.networkId);
        fprintf(stderr, "================================================\n");
        fprintf(stderr, "\n");
        fprintf(stderr, " On the talker device, run:\n");
        fprintf(stderr, "   export RMW_DSOFTBUS_PEER_ID=%s\n", local_info.networkId);
        fprintf(stderr, "   ./minimal_talker\n");
        fprintf(stderr, "\n");
    } else {
        fprintf(stderr, "[WARNING] Could not get local network ID\n");
    }
    fflush(stderr);

    // Create subscription implementation
    rmw_dsoftbus::SubscriptionImpl sub;
    sub.topic_name = TOPIC_NAME;
    sub.user_data = nullptr;
    sub.on_message = on_message_received;

    // As Subscriber: Register subscription (passive side)
    fprintf(stderr, "[LISTEN] Registering subscription...\n");
    fprintf(stderr, "[LISTEN] Topic name: %s\n", TOPIC_NAME);
    fflush(stderr);

    int ret = session_mgr.register_subscription(TOPIC_NAME, &sub);
    if (ret < 0) {
        fprintf(stderr, "[ERROR] Failed to register subscription! Error: %d\n", ret);
        fprintf(stderr, "        Make sure softbus_trans_permission.json is configured correctly.\n");
        return 1;
    }
    fprintf(stderr, "[LISTEN] Subscription registered. Waiting for connections...\n\n");
    fflush(stderr);

    // Wait for messages
    fprintf(stderr, "[LISTENER] Listening for messages (press Ctrl+C to stop)...\n\n");
    fflush(stderr);

    int timeout_count = 0;
    const int max_timeout = 120;  // 2 minutes max wait

    while (g_running && timeout_count < max_timeout) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        timeout_count += 5;

        fprintf(stderr, "[LISTENER] Waiting... (%d seconds, %d messages received so far)\n",
                timeout_count, g_messages_received.load());
        fflush(stderr);

        // Check if we received all expected messages
        if (g_messages_received >= 10) {
            fprintf(stderr, "[LISTENER] All expected messages received!\n");
            break;
        }
    }

    // Summary
    fprintf(stderr, "\n");
    fprintf(stderr, "================================================\n");
    fprintf(stderr, " Reception Complete\n");
    fprintf(stderr, "================================================\n");
    fprintf(stderr, " Messages received: %d\n", g_messages_received.load());
    fprintf(stderr, " Status:            %s\n",
            g_messages_received >= 10 ? "SUCCESS" : "INCOMPLETE");
    fprintf(stderr, "================================================\n\n");
    fflush(stderr);

    // Cleanup
    fprintf(stderr, "[CLEANUP] Unregistering subscription...\n");
    session_mgr.unregister_subscription(TOPIC_NAME);
    session_mgr.shutdown();
    fprintf(stderr, "[CLEANUP] Done.\n");

    return (g_messages_received >= 10) ? 0 : 1;
}
