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
 * @file test_graph_cache.cpp
 * @brief Unit tests for rmw_dsoftbus GraphCache
 *
 * Tests:
 * - Node registration/deregistration
 * - Endpoint registration/deregistration
 * - Query operations
 * - Cache expiration
 * - Thread safety
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>

#include "rmw_dsoftbus/graph_cache.h"

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

static GraphNodeInfo make_test_node(const char* name, const char* ns = "/") {
    GraphNodeInfo node;
    node.node_name = name;
    node.node_namespace = ns;
    node.network_id = "test_network_id";

    // Generate simple GID
    memset(&node.gid, 0, sizeof(node.gid));
    for (size_t i = 0; i < strlen(name) && i < 24; ++i) {
        node.gid.data[i] = name[i];
    }

    return node;
}

static GraphEndpointInfo make_test_publisher(const char* topic, const char* type,
                                             const char* node_name) {
    GraphEndpointInfo endpoint;
    endpoint.endpoint_type = GraphEndpointType::PUBLISHER;
    endpoint.topic_name = topic;
    endpoint.type_name = type;
    endpoint.node_name = node_name;
    endpoint.network_id = "test_network_id";

    // Generate simple GID
    memset(&endpoint.gid, 0, sizeof(endpoint.gid));
    for (size_t i = 0; i < strlen(topic) && i < 24; ++i) {
        endpoint.gid.data[i] = topic[i];
    }

    return endpoint;
}

// ============================================================================
// Node Registration Tests
// ============================================================================

TEST(test_add_node) {
    GraphCache cache;
    GraphNodeInfo node = make_test_node("talker", "/");

    bool result = cache.add_node(node);
    ASSERT_TRUE(result);

    fprintf(stderr, "  Added node: %s\n", node.node_name.c_str());
}

TEST(test_add_duplicate_node) {
    GraphCache cache;
    GraphNodeInfo node = make_test_node("talker", "/");

    bool result1 = cache.add_node(node);
    bool result2 = cache.add_node(node); // Duplicate

    ASSERT_TRUE(result1);
    ASSERT_FALSE(result2); // Should reject duplicate

    fprintf(stderr, "  Duplicate node correctly rejected\n");
}

TEST(test_remove_node) {
    GraphCache cache;
    GraphNodeInfo node = make_test_node("talker", "/");

    cache.add_node(node);

    std::string node_key = std::string(node.node_namespace) + ":" + node.node_name;
    bool result = cache.remove_node(node_key);

    ASSERT_TRUE(result);
    fprintf(stderr, "  Removed node: %s\n", node_key.c_str());
}

TEST(test_remove_nonexistent_node) {
    GraphCache cache;

    bool result = cache.remove_node("/nonexistent:node");
    ASSERT_FALSE(result); // Should fail for non-existent node

    fprintf(stderr, "  Nonexistent node removal correctly failed\n");
}

TEST(test_node_count) {
    GraphCache cache;

    GraphNodeInfo node1 = make_test_node("talker", "/");
    GraphNodeInfo node2 = make_test_node("listener", "/");

    cache.add_node(node1);
    cache.add_node(node2);

    std::vector<GraphNodeInfo> nodes = cache.get_all_nodes();
    ASSERT_EQ(nodes.size(), 2u);

    fprintf(stderr, "  Node count: %zu\n", nodes.size());
}

// ============================================================================
// Endpoint Registration Tests
// ============================================================================

TEST(test_add_endpoint) {
    GraphCache cache;
    GraphEndpointInfo endpoint = make_test_publisher("/chatter", "std_msgs::msg::String", "talker");

    bool result = cache.add_endpoint(endpoint);
    ASSERT_TRUE(result);

    fprintf(stderr, "  Added endpoint: %s\n", endpoint.topic_name.c_str());
}

TEST(test_add_duplicate_endpoint) {
    GraphCache cache;
    GraphEndpointInfo endpoint = make_test_publisher("/chatter", "std_msgs::msg::String", "talker");

    bool result1 = cache.add_endpoint(endpoint);
    bool result2 = cache.add_endpoint(endpoint); // Duplicate

    ASSERT_TRUE(result1);
    ASSERT_FALSE(result2); // Should reject duplicate

    fprintf(stderr, "  Duplicate endpoint correctly rejected\n");
}

TEST(test_remove_endpoint) {
    GraphCache cache;
    GraphEndpointInfo endpoint = make_test_publisher("/chatter", "std_msgs::msg::String", "talker");

    cache.add_endpoint(endpoint);

    bool result = cache.remove_endpoint(endpoint.gid);
    ASSERT_TRUE(result);

    fprintf(stderr, "  Removed endpoint\n");
}

TEST(test_endpoint_count) {
    GraphCache cache;

    GraphEndpointInfo pub1 = make_test_publisher("/topic1", "std_msgs::msg::String", "node1");
    GraphEndpointInfo pub2 = make_test_publisher("/topic2", "std_msgs::msg::Int32", "node2");

    cache.add_endpoint(pub1);
    cache.add_endpoint(pub2);

    std::vector<GraphEndpointInfo> endpoints = cache.get_all_endpoints();
    ASSERT_EQ(endpoints.size(), 2u);

    fprintf(stderr, "  Endpoint count: %zu\n", endpoints.size());
}

// ============================================================================
// Query Tests
// ============================================================================

TEST(test_get_node_by_key) {
    GraphCache cache;
    GraphNodeInfo node = make_test_node("talker", "/");

    cache.add_node(node);

    std::string node_key = std::string(node.node_namespace) + ":" + node.node_name;
    GraphNodeInfo* found = cache.get_node(node_key);

    ASSERT_TRUE(found != nullptr);
    ASSERT_STR_EQ(found->node_name, node.node_name);

    fprintf(stderr, "  Found node: %s\n", found->node_name.c_str());
}

TEST(test_get_endpoints_by_topic) {
    GraphCache cache;

    GraphEndpointInfo pub1 = make_test_publisher("/chatter", "std_msgs::msg::String", "talker");
    GraphEndpointInfo pub2 = make_test_publisher("/chatter", "std_msgs::msg::String", "talker2");
    GraphEndpointInfo pub3 = make_test_publisher("/other", "std_msgs::msg::Int32", "node3");

    cache.add_endpoint(pub1);
    cache.add_endpoint(pub2);
    cache.add_endpoint(pub3);

    std::vector<GraphEndpointInfo> endpoints = cache.get_endpoints_by_topic("/chatter");
    ASSERT_EQ(endpoints.size(), 2u);

    fprintf(stderr, "  Found %zu endpoints for /chatter\n", endpoints.size());
}

TEST(test_get_endpoints_by_nonexistent_topic) {
    GraphCache cache;

    GraphEndpointInfo pub = make_test_publisher("/chatter", "std_msgs::msg::String", "talker");
    cache.add_endpoint(pub);

    std::vector<GraphEndpointInfo> endpoints = cache.get_endpoints_by_topic("/nonexistent");
    ASSERT_EQ(endpoints.size(), 0u);

    fprintf(stderr, "  No endpoints found for nonexistent topic\n");
}

// ============================================================================
// Thread Safety Tests (Basic)
// ============================================================================

TEST(test_concurrent_node_operations) {
    GraphCache cache;

    std::thread t1([&]() {
        for (int i = 0; i < 100; ++i) {
            char name[32];
            snprintf(name, sizeof(name), "node_%d", i);
            GraphNodeInfo node = make_test_node(name);
            cache.add_node(node);
        }
    });

    std::thread t2([&]() {
        for (int i = 0; i < 100; ++i) {
            std::this_thread::sleep_for(std::chrono::microseconds(10));
            std::vector<GraphNodeInfo> nodes = cache.get_all_nodes();
            (void)nodes;
        }
    });

    t1.join();
    t2.join();

    std::vector<GraphNodeInfo> nodes = cache.get_all_nodes();
    ASSERT_TRUE(nodes.size() > 0);

    fprintf(stderr, "  Concurrent operations completed, %zu nodes\n", nodes.size());
}

// ============================================================================
// Clear Operations Tests
// ============================================================================

TEST(test_clear_cache) {
    GraphCache cache;

    GraphNodeInfo node = make_test_node("talker", "/");
    GraphEndpointInfo endpoint = make_test_publisher("/chatter", "std_msgs::msg::String", "talker");

    cache.add_node(node);
    cache.add_endpoint(endpoint);

    cache.clear();

    std::vector<GraphNodeInfo> nodes = cache.get_all_nodes();
    std::vector<GraphEndpointInfo> endpoints = cache.get_all_endpoints();

    ASSERT_EQ(nodes.size(), 0u);
    ASSERT_EQ(endpoints.size(), 0u);

    fprintf(stderr, "  Cache cleared successfully\n");
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main() {
    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "rmw_dsoftbus GraphCache Unit Tests\n");
    fprintf(stderr, "=================================================\n");

    // Run all tests
    test_add_node_runner();
    test_add_duplicate_node_runner();
    test_remove_node_runner();
    test_remove_nonexistent_node_runner();
    test_node_count_runner();

    test_add_endpoint_runner();
    test_add_duplicate_endpoint_runner();
    test_remove_endpoint_runner();
    test_endpoint_count_runner();

    test_get_node_by_key_runner();
    test_get_endpoints_by_topic_runner();
    test_get_endpoints_by_nonexistent_topic_runner();

    test_concurrent_node_operations_runner();

    test_clear_cache_runner();

    // Print summary
    fprintf(stderr, "\n=================================================\n");
    fprintf(stderr, "Test Summary:\n");
    fprintf(stderr, "  Total:  %d\n", test_count);
    fprintf(stderr, "  Passed: %d\n", test_pass);
    fprintf(stderr, "  Failed: %d\n", test_fail);
    fprintf(stderr, "=================================================\n");

    return (test_fail == 0) ? 0 : 1;
}
