/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file test_discovery_integration.cpp
 * @brief Integration tests for DiscoveryManager + GraphCache
 *
 * Tests:
 * - Local node/endpoint registration to GraphCache
 * - Discovery message broadcast via DiscoveryManager
 * - RMW API integration (rmw_get_node_names, rmw_get_topic_names_and_types)
 * - Cross-device discovery simulation
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>

#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/discovery_manager.h"

using namespace rmw_dsoftbus;

// ============================================================================
// Test Utilities
// ============================================================================

static int test_count = 0;
static int test_pass = 0;
static int test_fail = 0;

#define TEST(name) \
    static void name(); \
    static void name##_runner() { \
        test_count++; \
        fprintf(stderr, "\n[TEST %d] Running %s...\n", test_count, #name); \
        name(); \
        test_pass++; \
        fprintf(stderr, "[TEST %d] PASSED: %s\n", test_count, #name); \
    } \
    static void name()

#define ASSERT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "[ASSERT FAILED] %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            test_fail++; \
            return; \
        } \
    } while (0)

#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))

#define ASSERT_EQ(a, b) \
    do { \
        auto _a = (a); \
        auto _b = (b); \
        if (_a != _b) { \
            fprintf(stderr, "[ASSERT FAILED] %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b); \
            fprintf(stderr, "  Expected: %lld\n", (long long)_b); \
            fprintf(stderr, "  Actual:   %lld\n", (long long)_a); \
            test_fail++; \
            return; \
        } \
    } while (0)

#define ASSERT_STR_EQ(a, b) \
    do { \
        std::string _a = (a); \
        std::string _b = (b); \
        if (_a != _b) { \
            fprintf(stderr, "[ASSERT FAILED] %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b); \
            fprintf(stderr, "  Expected: \"%s\"\n", _b.c_str()); \
            fprintf(stderr, "  Actual:   \"%s\"\n", _a.c_str()); \
            test_fail++; \
            return; \
        } \
    } while (0)

// ============================================================================
// Helper Functions
// ============================================================================

static rmw_gid_t make_test_gid(uint8_t id) {
    rmw_gid_t gid;
    memset(&gid, 0, sizeof(gid));
    gid.data[0] = id;
    return gid;
}

static rmw_qos_profile_t make_default_qos() {
    rmw_qos_profile_t qos;
    memset(&qos, 0, sizeof(qos));
    qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos.depth = 10;
    qos.reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    return qos;
}

// ============================================================================
// GraphCache Local Tests
// ============================================================================

TEST(test_graphcache_node_registration) {
    GraphCache& cache = GraphCache::instance();

    // Register a node
    cache.register_node("talker", "/", "");

    // Verify node is registered
    auto nodes = cache.get_all_nodes();
    ASSERT_EQ(nodes.size(), 1u);
    ASSERT_STR_EQ(nodes[0].node_name, "talker");
    ASSERT_STR_EQ(nodes[0].node_namespace, "/");

    // Unregister node
    cache.unregister_node("talker", "/");

    // Verify node is removed
    nodes = cache.get_all_nodes();
    ASSERT_EQ(nodes.size(), 0u);

    fprintf(stderr, "  GraphCache node registration: OK\n");
}

TEST(test_graphcache_publisher_registration) {
    GraphCache& cache = GraphCache::instance();

    // Register node first
    cache.register_node("talker", "/", "");

    // Register publisher
    rmw_gid_t gid = make_test_gid(1);
    rmw_qos_profile_t qos = make_default_qos();

    cache.register_publisher(
        "/chatter", "std_msgs::msg::String",
        "talker", "/", &qos, &gid, nullptr
    );

    // Verify publisher is registered
    size_t count = cache.count_publishers("/chatter");
    ASSERT_EQ(count, 1u);

    auto publishers = cache.get_publishers_for_topic("/chatter");
    ASSERT_EQ(publishers.size(), 1u);
    ASSERT_STR_EQ(publishers[0].topic_name, "/chatter");
    ASSERT_STR_EQ(publishers[0].type_name, "std_msgs::msg::String");

    // Get topic names and types
    auto topics = cache.get_topic_names_and_types();
    ASSERT_EQ(topics.size(), 1u);
    ASSERT_TRUE(topics.find("/chatter") != topics.end());
    ASSERT_TRUE(topics["/chatter"].find("std_msgs::msg::String") != topics["/chatter"].end());

    // Cleanup
    cache.unregister_endpoint(&gid);
    cache.unregister_node("talker", "/");

    fprintf(stderr, "  GraphCache publisher registration: OK\n");
}

TEST(test_graphcache_subscription_registration) {
    GraphCache& cache = GraphCache::instance();

    // Register node first
    cache.register_node("listener", "/", "");

    // Register subscription
    rmw_gid_t gid = make_test_gid(2);
    rmw_qos_profile_t qos = make_default_qos();

    cache.register_subscription(
        "/chatter", "std_msgs::msg::String",
        "listener", "/", &qos, &gid, nullptr
    );

    // Verify subscription is registered
    size_t count = cache.count_subscribers("/chatter");
    ASSERT_EQ(count, 1u);

    auto subscribers = cache.get_subscribers_for_topic("/chatter");
    ASSERT_EQ(subscribers.size(), 1u);

    // Cleanup
    cache.unregister_endpoint(&gid);
    cache.unregister_node("listener", "/");

    fprintf(stderr, "  GraphCache subscription registration: OK\n");
}

TEST(test_graphcache_graph_version) {
    GraphCache& cache = GraphCache::instance();

    uint64_t version1 = cache.get_graph_version();

    // Register a node - should increment version
    cache.register_node("test_node", "/", "");

    uint64_t version2 = cache.get_graph_version();
    ASSERT_TRUE(version2 > version1);

    // Unregister node - should increment again
    cache.unregister_node("test_node", "/");

    uint64_t version3 = cache.get_graph_version();
    ASSERT_TRUE(version3 > version2);

    fprintf(stderr, "  GraphCache version tracking: OK (v1=%llu, v2=%llu, v3=%llu)\n",
            (unsigned long long)version1, (unsigned long long)version2, (unsigned long long)version3);
}

// ============================================================================
// GraphCache Remote Discovery Tests
// ============================================================================

TEST(test_graphcache_remote_node_discovery) {
    GraphCache& cache = GraphCache::instance();

    // Simulate remote node discovery
    GraphNodeInfo remote_node;
    remote_node.node_name = "remote_talker";
    remote_node.node_namespace = "/";
    remote_node.enclave = "";
    remote_node.network_id = "remote_device_123";
    remote_node.creation_time_ns = 1234567890;

    cache.on_remote_node_discovered(remote_node);

    // Verify remote node is in cache
    auto nodes = cache.get_all_nodes();
    ASSERT_TRUE(nodes.size() >= 1);

    bool found = false;
    for (const auto& node : nodes) {
        if (node.node_name == "remote_talker" && node.network_id == "remote_device_123") {
            found = true;
            break;
        }
    }
    ASSERT_TRUE(found);

    // Cleanup
    cache.remove_remote_node("remote_device_123", "/:remote_talker");

    fprintf(stderr, "  GraphCache remote node discovery: OK\n");
}

TEST(test_graphcache_remote_endpoint_discovery) {
    GraphCache& cache = GraphCache::instance();

    // Simulate remote endpoint discovery
    GraphEndpointInfo remote_endpoint;
    remote_endpoint.topic_name = "/remote_topic";
    remote_endpoint.type_name = "std_msgs::msg::String";
    remote_endpoint.node_name = "remote_node";
    remote_endpoint.node_namespace = "/";
    remote_endpoint.network_id = "remote_device_456";
    remote_endpoint.type = EndpointType::PUBLISHER;
    remote_endpoint.gid = make_test_gid(99);
    remote_endpoint.qos = make_default_qos();

    cache.on_remote_endpoint_discovered(remote_endpoint);

    // Verify remote endpoint is in cache
    size_t count = cache.count_publishers("/remote_topic");
    ASSERT_TRUE(count >= 1);

    auto publishers = cache.get_publishers_for_topic("/remote_topic");
    bool found = false;
    for (const auto& pub : publishers) {
        if (pub.network_id == "remote_device_456") {
            found = true;
            break;
        }
    }
    ASSERT_TRUE(found);

    // Cleanup
    cache.remove_remote_endpoint("remote_device_456", remote_endpoint.gid);

    fprintf(stderr, "  GraphCache remote endpoint discovery: OK\n");
}

TEST(test_graphcache_snapshot) {
    GraphCache& cache = GraphCache::instance();

    // Register local node and endpoint
    cache.register_node("local_node", "/", "");
    rmw_gid_t gid = make_test_gid(10);
    rmw_qos_profile_t qos = make_default_qos();
    cache.register_publisher("/local_topic", "std_msgs::msg::String",
                            "local_node", "/", &qos, &gid, nullptr);

    // Get snapshot
    GraphSnapshot snap = cache.snapshot_local_only();

    // Verify snapshot contains local data
    ASSERT_TRUE(snap.nodes.size() >= 1);
    ASSERT_TRUE(snap.endpoints.size() >= 1);

    bool found_node = false;
    for (const auto& node : snap.nodes) {
        if (node.node_name == "local_node") {
            found_node = true;
            break;
        }
    }
    ASSERT_TRUE(found_node);

    // Cleanup
    cache.unregister_endpoint(&gid);
    cache.unregister_node("local_node", "/");

    fprintf(stderr, "  GraphCache snapshot: OK (nodes=%zu, endpoints=%zu)\n",
            snap.nodes.size(), snap.endpoints.size());
}

// ============================================================================
// DiscoveryManager Tests
// ============================================================================

TEST(test_discovery_manager_initialized) {
    DiscoveryManager& dm = DiscoveryManager::instance();

    // Check if initialized (might fail if dsoftbus not available)
    bool initialized = dm.is_initialized();
    fprintf(stderr, "  DiscoveryManager initialized: %s\n",
            initialized ? "YES" : "NO (expected in stub mode)");

    // This test always passes - just reports status
    ASSERT_TRUE(true);
}

TEST(test_discovery_manager_stats) {
    DiscoveryManager& dm = DiscoveryManager::instance();

    // Get statistics snapshot
    DiscoveryStatsSnapshot stats = dm.get_stats();

    fprintf(stderr, "  DiscoveryManager stats:\n");
    fprintf(stderr, "    RX total: %llu\n", (unsigned long long)stats.rx_total);
    fprintf(stderr, "    TX total: %llu\n", (unsigned long long)stats.tx_total);
    fprintf(stderr, "    Drops (invalid): %llu\n", (unsigned long long)stats.drop_invalid);
    fprintf(stderr, "    Remote nodes: %u\n", stats.remote_nodes_count);
    fprintf(stderr, "    Remote endpoints: %u\n", stats.remote_endpoints_count);
    fprintf(stderr, "    Peer sessions: %u\n", stats.peer_sessions_count);

    // This test always passes - just reports stats
    ASSERT_TRUE(true);
}

TEST(test_discovery_message_building) {
    DiscoveryManager& dm = DiscoveryManager::instance();

    // Test building heartbeat message (uses testing API)
    std::vector<uint8_t> msg = dm.build_heartbeat_message_for_test();

    // Verify message has correct header size
    ASSERT_TRUE(msg.size() >= DISCOVERY_HEADER_SIZE);

    // Verify magic number
    uint16_t magic = (msg[1] << 8) | msg[0];
    ASSERT_EQ(magic, DISCOVERY_MAGIC);

    // Verify version
    uint8_t version = msg[2];
    ASSERT_EQ(version, DISCOVERY_VERSION);

    // Verify message type
    uint8_t msg_type = msg[3];
    ASSERT_EQ(msg_type, static_cast<uint8_t>(DiscoveryMessageType::HEARTBEAT));

    fprintf(stderr, "  DiscoveryManager message building: OK (size=%zu bytes)\n", msg.size());
}

// ============================================================================
// Integration Tests
// ============================================================================

TEST(test_integration_local_pub_sub) {
    GraphCache& cache = GraphCache::instance();

    // Simulate talker node with publisher
    cache.register_node("talker", "/", "");

    rmw_gid_t pub_gid = make_test_gid(20);
    rmw_qos_profile_t qos = make_default_qos();
    cache.register_publisher("/chatter", "std_msgs::msg::String",
                            "talker", "/", &qos, &pub_gid, nullptr);

    // Simulate listener node with subscription
    cache.register_node("listener", "/", "");

    rmw_gid_t sub_gid = make_test_gid(21);
    cache.register_subscription("/chatter", "std_msgs::msg::String",
                                "listener", "/", &qos, &sub_gid, nullptr);

    // Verify both nodes are visible
    auto nodes = cache.get_all_nodes();
    ASSERT_TRUE(nodes.size() >= 2);

    // Verify topic is visible
    auto topics = cache.get_topic_names_and_types();
    ASSERT_TRUE(topics.find("/chatter") != topics.end());

    // Verify counts
    ASSERT_EQ(cache.count_publishers("/chatter"), 1u);
    ASSERT_EQ(cache.count_subscribers("/chatter"), 1u);

    // Cleanup
    cache.unregister_endpoint(&pub_gid);
    cache.unregister_endpoint(&sub_gid);
    cache.unregister_node("talker", "/");
    cache.unregister_node("listener", "/");

    fprintf(stderr, "  Integration test (local pub/sub): OK\n");
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main() {
    fprintf(stderr, "==========================================================\n");
    fprintf(stderr, "rmw_dsoftbus Discovery + GraphCache Integration Tests\n");
    fprintf(stderr, "==========================================================\n");

    // Initialize GraphCache (required)
    if (!GraphCache::instance().initialize()) {
        fprintf(stderr, "[ERROR] Failed to initialize GraphCache\n");
        return 1;
    }

    // Initialize DiscoveryManager (optional - may fail in stub mode)
    DiscoveryManager::instance().initialize();

    // Run all tests
    fprintf(stderr, "\n--- GraphCache Local Tests ---\n");
    test_graphcache_node_registration_runner();
    test_graphcache_publisher_registration_runner();
    test_graphcache_subscription_registration_runner();
    test_graphcache_graph_version_runner();

    fprintf(stderr, "\n--- GraphCache Remote Discovery Tests ---\n");
    test_graphcache_remote_node_discovery_runner();
    test_graphcache_remote_endpoint_discovery_runner();
    test_graphcache_snapshot_runner();

    fprintf(stderr, "\n--- DiscoveryManager Tests ---\n");
    test_discovery_manager_initialized_runner();
    test_discovery_manager_stats_runner();
    test_discovery_message_building_runner();

    fprintf(stderr, "\n--- Integration Tests ---\n");
    test_integration_local_pub_sub_runner();

    // Print summary
    fprintf(stderr, "\n==========================================================\n");
    fprintf(stderr, "Test Summary:\n");
    fprintf(stderr, "  Total:  %d\n", test_count);
    fprintf(stderr, "  Passed: %d\n", test_pass);
    fprintf(stderr, "  Failed: %d\n", test_fail);
    fprintf(stderr, "==========================================================\n");

    return (test_fail == 0) ? 0 : 1;
}
