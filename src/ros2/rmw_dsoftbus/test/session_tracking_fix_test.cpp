// Session ID Tracking Fix Verification Test
// Tests the deferred registration fix for GetPeerDeviceId failures

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <atomic>
#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/native_token.h"

static std::atomic<bool> running{true};

void signal_handler(int sig) {
    (void)sig;
    running = false;
}

int main(int argc, char** argv) {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    const char* mode = (argc > 1) ? argv[1] : "auto";
    fprintf(stderr, "\n========================================\n");
    fprintf(stderr, " Session ID Tracking Fix Test\n");
    fprintf(stderr, " Mode: %s\n", mode);
    fprintf(stderr, "========================================\n\n");

    // Initialize
    fprintf(stderr, "[INIT] Initializing subsystems...\n");
    rmw_dsoftbus::try_init_native_token();
    rmw_dsoftbus::GraphCache::instance().initialize();
    rmw_dsoftbus::DiscoveryManager::instance().initialize();

    // Register test node
    rmw_dsoftbus::GraphCache::instance().register_node("test_node", "/test", "");
    fprintf(stderr, "[INIT] Test node registered\n");

    // Wait for session establishment (max 20 seconds)
    fprintf(stderr, "[INIT] Waiting for peer session (max 20s)...\n");
    bool session_ok = false;
    for (int i = 0; i < 20 && running; i++) {
        auto stats = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
        if (stats.peer_sessions_count > 0) {
            fprintf(stderr, "[INIT] ✅ Session established (count=%u)\n",
                    stats.peer_sessions_count);
            session_ok = true;
            break;
        }
        fprintf(stderr, "[INIT] T+%ds: waiting (peers=%u)...\n", i+1, stats.peer_sessions_count);
        sleep(1);
    }

    if (!session_ok) {
        fprintf(stderr, "[ERROR] ❌ No peer session after 20 seconds\n");
        return 1;
    }

    // Main test loop (30 seconds)
    fprintf(stderr, "\n[RUNNING] Monitoring for 30 seconds...\n");
    fprintf(stderr, "Press Ctrl+C to stop early\n\n");

    uint64_t last_rx = 0;
    int no_drop_streak = 0;

    for (int sec = 0; sec < 30 && running; sec++) {
        auto stats = rmw_dsoftbus::DiscoveryManager::instance().get_stats();

        uint64_t new_rx = stats.rx_total - last_rx;
        last_rx = stats.rx_total;

        // Track success streak (no drops)
        if (stats.drop_invalid == 0 && stats.rx_total > 0) {
            no_drop_streak++;
        }

        fprintf(stderr, "[T+%02d] RX=%lu (+%lu) TX=%lu peers=%u hb=%lu drops=%lu\n",
                sec, stats.rx_total, new_rx, stats.tx_total,
                stats.peer_sessions_count, stats.heartbeat_recv, stats.drop_invalid);

        sleep(1);
    }

    // Final statistics
    auto final = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
    fprintf(stderr, "\n========================================\n");
    fprintf(stderr, "Final Statistics:\n");
    fprintf(stderr, "========================================\n");
    fprintf(stderr, "RX total:           %lu\n", final.rx_total);
    fprintf(stderr, "TX total:           %lu\n", final.tx_total);
    fprintf(stderr, "Heartbeat recv:     %lu\n", final.heartbeat_recv);
    fprintf(stderr, "Query sent:         %lu\n", final.query_sent);
    fprintf(stderr, "Snapshot recv:      %lu\n", final.snapshot_recv);
    fprintf(stderr, "Drop invalid:       %lu\n", final.drop_invalid);
    fprintf(stderr, "Drop dup:           %lu\n", final.drop_dup);
    fprintf(stderr, "Peer sessions:      %u\n", final.peer_sessions_count);
    fprintf(stderr, "Remote nodes:       %u\n", final.remote_nodes_count);
    fprintf(stderr, "Remote endpoints:   %u\n", final.remote_endpoints_count);
    fprintf(stderr, "========================================\n\n");

    // Validation
    bool success = true;

    fprintf(stderr, "[VALIDATION]\n");

    if (final.peer_sessions_count == 0) {
        fprintf(stderr, "❌ FAIL: No peer session (expected >= 1)\n");
        success = false;
    } else {
        fprintf(stderr, "✅ PASS: Peer session established (%u)\n", final.peer_sessions_count);
    }

    if (final.rx_total < 10) {
        fprintf(stderr, "❌ FAIL: Too few messages received (RX=%lu < 10)\n", final.rx_total);
        success = false;
    } else {
        fprintf(stderr, "✅ PASS: Messages received (RX=%lu >= 10)\n", final.rx_total);
    }

    // Critical test: drop_invalid should be 0 or very low
    double drop_rate = (final.rx_total > 0) ? (100.0 * final.drop_invalid / final.rx_total) : 0.0;
    if (final.drop_invalid > 0) {
        fprintf(stderr, "⚠️  WARN: Some invalid drops (%lu, %.1f%%)\n", final.drop_invalid, drop_rate);
        if (drop_rate > 10.0) {
            fprintf(stderr, "❌ FAIL: Drop rate too high (%.1f%% > 10%%)\n", drop_rate);
            success = false;
        }
    } else {
        fprintf(stderr, "✅ PASS: Zero invalid drops (session tracking fix working!)\n");
    }

    if (final.heartbeat_recv < 5) {
        fprintf(stderr, "⚠️  WARN: Few heartbeats received (%lu < 5)\n", final.heartbeat_recv);
    } else {
        fprintf(stderr, "✅ PASS: Heartbeat received (%lu >= 5)\n", final.heartbeat_recv);
    }

    if (no_drop_streak >= 20) {
        fprintf(stderr, "✅ PASS: Sustained operation (%d sec without drops)\n", no_drop_streak);
    }

    fprintf(stderr, "\n");

    if (success) {
        fprintf(stderr, "========================================\n");
        fprintf(stderr, "✅ TEST PASSED\n");
        fprintf(stderr, "========================================\n");
    } else {
        fprintf(stderr, "========================================\n");
        fprintf(stderr, "❌ TEST FAILED\n");
        fprintf(stderr, "========================================\n");
    }

    fprintf(stderr, "\n");

    // Cleanup
    rmw_dsoftbus::DiscoveryManager::instance().shutdown();
    return success ? 0 : 1;
}
