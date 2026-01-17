/*
 * Graph Discovery Test with Permission Bypass
 *
 * Purpose: Test DiscoveryManager + GraphCache with real dsoftbus using
 * NativeToken permission bypass (Phase 2 proven method)
 *
 * Test Flow:
 * 1. Inject NativeToken permissions (system_basic APL)
 * 2. Initialize DiscoveryManager + GraphCache
 * 3. Register local node + endpoint
 * 4. Run discovery loop
 * 5. Collect statistics
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // C-style string functions BEFORE C++ headers (GCC Linaro workaround)
#include <unistd.h>
#include <signal.h>

// C++ headers
#include <atomic>

// Permission bypass utility (Phase 2 proven method)
#include "softbus_permission_bypass.h"

#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/types.h"

using namespace rmw_dsoftbus;

static std::atomic<bool> g_running{true};
static int g_test_duration_sec = 30;

void signal_handler(int signum) {
    (void)signum;
    fprintf(stderr, "\n[Signal] Caught interrupt, shutting down...\n");
    g_running = false;
}

void create_test_gid(rmw_gid_t* gid, uint8_t id) {
    memset(gid->data, 0, RMW_GID_STORAGE_SIZE);
    gid->data[0] = id;
    for (size_t i = 1; i < RMW_GID_STORAGE_SIZE; ++i) {
        gid->data[i] = (uint8_t)((id * 11 + i) % 256);
    }
}

int main(int argc, char** argv) {
    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "Graph Discovery Test with Permission Bypass\n");
    fprintf(stderr, "Phase 2 Proven Method: NativeToken + system_basic APL\n");
    fprintf(stderr, "=================================================\n\n");

    if (argc > 1) {
        g_test_duration_sec = atoi(argv[1]);
        if (g_test_duration_sec < 5) g_test_duration_sec = 5;
        if (g_test_duration_sec > 300) g_test_duration_sec = 300;
    }

    fprintf(stderr, "[Config] Test duration: %d seconds\n", g_test_duration_sec);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // ========================================================================
    // Step 0: Permission Bypass (CRITICAL)
    // ========================================================================

    fprintf(stderr, "\n[Step 0] Injecting NativeToken permissions...\n");
    fprintf(stderr, "[Permission] Using Phase 2 proven method:\n");
    fprintf(stderr, "[Permission]  - APL: system_basic (not system_core!)\n");
    fprintf(stderr, "[Permission]  - Permissions: DISTRIBUTED_DATASYNC + DISTRIBUTED_SOFTBUS_CENTER\n");
    fprintf(stderr, "[Permission]  - Method: GetAccessTokenId() + SetSelfTokenID() + ReloadNativeTokenInfo()\n");

    if (SetSoftbusNativeTokenPermission("com.ros2.graph_discovery.test") != 0) {
        fprintf(stderr, "[ERROR] Failed to inject NativeToken permissions\n");
        fprintf(stderr, "[ERROR] Cannot proceed without proper permissions\n");
        fprintf(stderr, "\n[Hint] This requires:\n");
        fprintf(stderr, "  1. /system/lib64/chipset-pub-sdk/libaccesstoken_sdk.z.so\n");
        fprintf(stderr, "  2. /system/lib64/platformsdk/libaccesstoken_common_cxx.z.so\n");
        fprintf(stderr, "  3. Proper device permissions to call SetSelfTokenID()\n");
        return 1;
    }
    fprintf(stderr, "[OK] NativeToken permissions injected successfully\n");

    // ========================================================================
    // Step 1: Initialize DiscoveryManager (with real dsoftbus)
    // ========================================================================

    fprintf(stderr, "\n[Step 1] Initializing DiscoveryManager...\n");
    if (!DiscoveryManager::instance().initialize()) {
        fprintf(stderr, "[ERROR] DiscoveryManager initialization failed\n");
        fprintf(stderr, "[ERROR] This might be due to:\n");
        fprintf(stderr, "  1. CreateSessionServer still failed (permissions not effective?)\n");
        fprintf(stderr, "  2. dsoftbus service not running\n");
        fprintf(stderr, "  3. Invalid network configuration\n");
        return 1;
    }
    fprintf(stderr, "[OK] DiscoveryManager initialized\n");

    // ========================================================================
    // Step 2: Initialize GraphCache
    // ========================================================================

    fprintf(stderr, "\n[Step 2] Initializing GraphCache...\n");
    if (!GraphCache::instance().initialize()) {
        fprintf(stderr, "[ERROR] GraphCache initialization failed\n");
        DiscoveryManager::instance().shutdown();
        return 1;
    }
    fprintf(stderr, "[OK] GraphCache initialized\n");

    // ========================================================================
    // Step 3: Register local node and endpoint
    // ========================================================================

    fprintf(stderr, "\n[Step 3] Registering test node and endpoint...\n");
    GraphCache::instance().register_node("test_talker", "/", "");
    fprintf(stderr, "[GraphCache] Registered node: test_talker\n");

    // Register test publisher
    rmw_gid_t pub_gid;
    create_test_gid(&pub_gid, 1);

    rmw_qos_profile_t qos = {};

    GraphCache::instance().register_publisher(
        "/chatter",
        "std_msgs::msg::String",
        "test_talker",
        "/",
        &qos,
        &pub_gid,
        nullptr
    );
    fprintf(stderr, "[GraphCache] Registered publisher: /chatter\n");

    // ========================================================================
    // Step 4: Run discovery loop
    // ========================================================================

    fprintf(stderr, "\n[Step 4] Running discovery loop for %d seconds...\n", g_test_duration_sec);
    fprintf(stderr, "[Info] Waiting for remote devices to discover...\n");

    int elapsed = 0;
    while (g_running && elapsed < g_test_duration_sec) {
        sleep(1);
        elapsed++;

        if (elapsed % 5 == 0) {
            fprintf(stderr, "[Progress] %d/%d seconds\n", elapsed, g_test_duration_sec);

            auto all_nodes = GraphCache::instance().get_all_nodes();
            fprintf(stderr, "[GraphCache] Total nodes: %zu\n", all_nodes.size());

            // Show remote nodes if any
            if (all_nodes.size() > 1) {
                fprintf(stderr, "[GraphCache] 🎉 Remote nodes detected!\n");
                for (const auto& node : all_nodes) {
                    fprintf(stderr, "  - %s::%s (network_id: %s)\n",
                            node.node_namespace.c_str(),
                            node.node_name.c_str(),
                            node.network_id.c_str());
                }
            }
        }
    }

    // ========================================================================
    // Step 5: Final Statistics
    // ========================================================================

    fprintf(stderr, "\n[Step 5] Final Statistics\n");
    fprintf(stderr, "=================================================\n");

    auto all_nodes = GraphCache::instance().get_all_nodes();
    auto topic_types = GraphCache::instance().get_topic_names_and_types();

    fprintf(stderr, "\n[GraphCache]\n");
    fprintf(stderr, "  Total nodes:  %zu\n", all_nodes.size());
    fprintf(stderr, "  Total topics: %zu\n", topic_types.size());

    fprintf(stderr, "\n[All Nodes]\n");
    for (const auto& node : all_nodes) {
        fprintf(stderr, "  - %s::%s (network_id: %s)\n",
                node.node_namespace.c_str(),
                node.node_name.c_str(),
                node.network_id.c_str());
    }

    fprintf(stderr, "\n[All Topics]\n");
    for (const auto& [topic, types] : topic_types) {
        fprintf(stderr, "  - %s\n", topic.c_str());
        size_t pub_count = GraphCache::instance().count_publishers(topic.c_str());
        size_t sub_count = GraphCache::instance().count_subscribers(topic.c_str());
        fprintf(stderr, "    Publishers: %zu, Subscribers: %zu\n", pub_count, sub_count);
    }

    auto stats = DiscoveryManager::instance().get_stats();
    fprintf(stderr, "\n[DiscoveryManager Statistics]\n");
    fprintf(stderr, "  Messages RX: %llu\n", (unsigned long long)stats.rx_total);
    fprintf(stderr, "  Messages TX: %llu\n", (unsigned long long)stats.tx_total);
    fprintf(stderr, "  Drops:       %llu\n", (unsigned long long)stats.drop_invalid);
    fprintf(stderr, "  Query sent:  %llu\n", (unsigned long long)stats.query_sent);

    // ========================================================================
    // Success Criteria
    // ========================================================================

    fprintf(stderr, "\n[Success Criteria]\n");
    bool local_ok = (all_nodes.size() >= 1);
    bool discovery_ok = (stats.tx_total > 0);
    bool remote_ok = (all_nodes.size() > 1);
    bool bidirectional_ok = (stats.rx_total > 0);

    fprintf(stderr, "  ✅ Local node registration: %s\n", local_ok ? "PASS" : "FAIL");
    fprintf(stderr, "  ✅ Discovery TX: %s (%llu messages)\n",
            discovery_ok ? "PASS" : "FAIL", (unsigned long long)stats.tx_total);
    fprintf(stderr, "  %s Remote node discovery: %s (%zu remote nodes)\n",
            remote_ok ? "✅" : "⏸️",
            remote_ok ? "PASS" : "PENDING",
            all_nodes.size() - 1);
    fprintf(stderr, "  %s Bidirectional communication: %s (%llu RX)\n",
            bidirectional_ok ? "✅" : "⏸️",
            bidirectional_ok ? "PASS" : "PENDING",
            (unsigned long long)stats.rx_total);

    // ========================================================================
    // Cleanup
    // ========================================================================

    fprintf(stderr, "\n[Step 6] Cleanup\n");
    GraphCache::instance().shutdown();
    DiscoveryManager::instance().shutdown();

    fprintf(stderr, "\n=================================================\n");
    fprintf(stderr, "Test completed!\n");
    fprintf(stderr, "=================================================\n");

    return 0;
}
