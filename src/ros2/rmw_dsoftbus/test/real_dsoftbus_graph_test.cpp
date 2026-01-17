/*
 * Real DSoftBus Graph Discovery Test - Simplified Version
 *
 * Purpose: Test DiscoveryManager + GraphCache with REAL libsoftbus_client.z.so
 *
 * Test Flow:
 * 1. Initialize DiscoveryManager + GraphCache
 * 2. Register local node + endpoint
 * 3. Broadcast discovery messages
 * 4. Run for N seconds, collect statistics
 * 5. Print results
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <atomic>

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
    fprintf(stderr, "Real DSoftBus Graph Discovery Test\n");
    fprintf(stderr, "=================================================\n\n");

    if (argc > 1) {
        g_test_duration_sec = atoi(argv[1]);
        if (g_test_duration_sec < 5) g_test_duration_sec = 5;
        if (g_test_duration_sec > 300) g_test_duration_sec = 300;
    }

    fprintf(stderr, "[Config] Test duration: %d seconds\n", g_test_duration_sec);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Initialize DiscoveryManager
    fprintf(stderr, "\n[Step 1] Initializing DiscoveryManager...\n");
    if (!DiscoveryManager::instance().initialize()) {
        fprintf(stderr, "[ERROR] DiscoveryManager initialization failed\n");
        return 1;
    }
    fprintf(stderr, "[OK] DiscoveryManager initialized\n");

    // Initialize GraphCache
    fprintf(stderr, "\n[Step 2] Initializing GraphCache...\n");
    if (!GraphCache::instance().initialize()) {
        fprintf(stderr, "[ERROR] GraphCache initialization failed\n");
        DiscoveryManager::instance().shutdown();
        return 1;
    }
    fprintf(stderr, "[OK] GraphCache initialized\n");

    // Register local node
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

    // Run discovery loop
    fprintf(stderr, "\n[Step 4] Running discovery loop for %d seconds...\n", g_test_duration_sec);

    int elapsed = 0;
    while (g_running && elapsed < g_test_duration_sec) {
        sleep(1);
        elapsed++;

        if (elapsed % 5 == 0) {
            fprintf(stderr, "[Progress] %d/%d seconds\n", elapsed, g_test_duration_sec);

            auto all_nodes = GraphCache::instance().get_all_nodes();
            fprintf(stderr, "[GraphCache] Total nodes: %zu\n", all_nodes.size());
        }
    }

    // Print final statistics
    fprintf(stderr, "\n[Step 5] Final Statistics\n");
    fprintf(stderr, "=================================================\n");

    auto all_nodes = GraphCache::instance().get_all_nodes();
    auto topic_types = GraphCache::instance().get_topic_names_and_types();

    fprintf(stderr, "\n[GraphCache]\n");
    fprintf(stderr, "  Total nodes:  %zu\n", all_nodes.size());
    fprintf(stderr, "  Total topics: %zu\n", topic_types.size());

    fprintf(stderr, "\n[All Nodes]\n");
    for (const auto& node : all_nodes) {
        fprintf(stderr, "  - %s::%s\n",
                node.node_namespace.c_str(),
                node.node_name.c_str());
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

    // Cleanup
    fprintf(stderr, "\n[Step 6] Cleanup\n");
    GraphCache::instance().shutdown();
    DiscoveryManager::instance().shutdown();

    fprintf(stderr, "\n=================================================\n");
    fprintf(stderr, "Test completed!\n");
    fprintf(stderr, "=================================================\n");

    return 0;
}
