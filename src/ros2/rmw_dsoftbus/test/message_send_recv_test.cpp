// Phase 2 Message Send/Receive Test - v3 with better logging
// Tests actual SendBytes calls and message reception

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <atomic>
#include <thread>
#include <chrono>

#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw_dsoftbus/native_token.h"

static std::atomic<bool> running{true};
static std::atomic<int> messages_sent{0};

void signal_handler(int sig) {
    (void)sig;
    running = false;
}

// External SendBytes function (from softbus_dlopen_shim.cpp)
extern "C" {
    int SendBytes(int sessionId, const void* data, unsigned int len);
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    fprintf(stderr, "\n========================================\n");
    fprintf(stderr, " Phase 2 Message Send/Receive Test v3\n");
    fprintf(stderr, "========================================\n\n");
    fflush(stderr);

    fprintf(stderr, "[PROCESS] PID=%d UID=%d GID=%d\n\n", getpid(), getuid(), getgid());
    fflush(stderr);

    // Initialize native token
    fprintf(stderr, "[TOKEN] Initializing native token...\n");
    fflush(stderr);
    
    bool token_ok = rmw_dsoftbus::try_init_native_token();
    if (token_ok) {
        fprintf(stderr, "[TOKEN] ✅ Native token initialized successfully\n");
    } else {
        fprintf(stderr, "[TOKEN] ⚠️  Native token initialization skipped\n");
    }
    fprintf(stderr, "\n");
    fflush(stderr);

    // Initialize Discovery
    fprintf(stderr, "[DISCOVERY] Initializing DiscoveryManager...\n");
    fflush(stderr);
    
    bool init_ok = rmw_dsoftbus::DiscoveryManager::instance().initialize();
    if (!init_ok) {
        fprintf(stderr, "[ERROR] DiscoveryManager::initialize() failed\n");
        fflush(stderr);
        return 1;
    }
    fprintf(stderr, "[DISCOVERY] ✅ DiscoveryManager initialized\n\n");
    fflush(stderr);

    // Wait for session establishment
    fprintf(stderr, "[MAIN] Waiting 15 seconds for session establishment...\n");
    fflush(stderr);
    
    int session_found = 0;
    for (int i = 0; i < 15 && running; i++) {
        sleep(1);
        auto stats = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
        fprintf(stderr, "[MAIN] T+%2ds: peers=%u RX=%lu TX=%lu\n", 
                i+1, stats.peer_sessions_count, stats.rx_total, stats.tx_total);
        fflush(stderr);
        
        if (stats.peer_sessions_count > 0 && session_found == 0) {
            fprintf(stderr, "[MAIN] ✅ Session established! Starting message test...\n");
            fflush(stderr);
            session_found = 1;
            break;  // Exit wait loop immediately when session found
        }
    }

    if (session_found == 0) {
        fprintf(stderr, "[WARNING] No session found after 15 seconds\n");
        fflush(stderr);
    }

    // Send test messages
    fprintf(stderr, "\n[TEST] Attempting SendBytes calls (10 iterations)...\n");
    fflush(stderr);

    uint8_t test_msg[512];
    for (int i = 0; i < 512; i++) {
        test_msg[i] = (uint8_t)(i % 256);
    }

    for (int iter = 0; iter < 10 && running; iter++) {
        test_msg[0] = (uint8_t)iter;
        
        // Try sending to session IDs 0, 1, 2
        for (int sid = 0; sid <= 2; sid++) {
            int ret = SendBytes(sid, test_msg, 512);

            fprintf(stderr, "[SEND] iter_%d: sid=%d len=512 ret=%d\n", iter, sid, ret);
            if (ret == 0) {
                messages_sent++;
            }
            fflush(stderr);
        }
        
        usleep(500000);  // 500ms between iterations
    }

    fprintf(stderr, "\n[MONITOR] Monitoring for 10 seconds...\n");
    fflush(stderr);
    
    for (int i = 0; i < 10 && running; i++) {
        sleep(1);
        auto stats = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
        fprintf(stderr, "[MONITOR] T+%ds: RX=%lu TX=%lu peers=%u\n",
                i+1, stats.rx_total, stats.tx_total, stats.peer_sessions_count);
        fflush(stderr);
    }

    // Final statistics
    fprintf(stderr, "\n========================================\n");
    fprintf(stderr, " Results\n");
    fprintf(stderr, "========================================\n");
    fflush(stderr);
    
    auto final_stats = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
    
    fprintf(stderr, "SendBytes attempts:        %d\n", (int)messages_sent);
    fprintf(stderr, "Discovery RX:              %lu\n", final_stats.rx_total);
    fprintf(stderr, "Discovery TX:              %lu\n", final_stats.tx_total);
    fprintf(stderr, "Peer sessions:             %u\n", final_stats.peer_sessions_count);
    fprintf(stderr, "Remote nodes:              %u\n", final_stats.remote_nodes_count);
    fprintf(stderr, "Remote endpoints:          %u\n", final_stats.remote_endpoints_count);
    fprintf(stderr, "========================================\n\n");
    fflush(stderr);

    // Conclusion
    fprintf(stderr, "[CONCLUSION]\n");
    if (messages_sent > 0) {
        fprintf(stderr, "✅ SendBytes was callable (%d attempts)\n", (int)messages_sent);
    } else {
        fprintf(stderr, "❌ SendBytes calls were 0\n");
    }
    
    if (final_stats.rx_total > 0) {
        fprintf(stderr, "✅ Discovery messages received (%lu)\n", final_stats.rx_total);
    } else {
        fprintf(stderr, "❌ No discovery messages received\n");
    }
    
    fprintf(stderr, "\n");
    fflush(stderr);

    // Shutdown
    fprintf(stderr, "[SHUTDOWN] Cleaning up...\n");
    fflush(stderr);
    rmw_dsoftbus::DiscoveryManager::instance().shutdown();
    fprintf(stderr, "[SHUTDOWN] Complete\n");
    fflush(stderr);

    return 0;
}
