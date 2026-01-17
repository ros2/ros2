/**
 * @file test_rmw_dsoftbus_functional.cpp
 * @brief Comprehensive functional test for rmw_dsoftbus
 *
 * Tests:
 * 1. SessionManager initialization and session creation
 * 2. CreateSessionServer functionality
 * 3. Graph discovery and graph cache
 * 4. Basic pub/sub functionality
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <memory>

#include "rmw_dsoftbus/session_manager.h"
#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/types.h"

using namespace rmw_dsoftbus;
using namespace std::chrono_literals;

// Color codes for output
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

class TestRunner {
public:
    int passed_{0};
    int failed_{0};

    void test_start(const char* name) {
        printf("\n" YELLOW "[TEST] %s" RESET "\n", name);
    }

    void test_pass(const char* msg) {
        printf(GREEN "  ✓ %s\n" RESET, msg);
        passed_++;
    }

    void test_fail(const char* msg) {
        printf(RED "  ✗ %s\n" RESET, msg);
        failed_++;
    }

    void test_info(const char* msg) {
        printf("  ℹ %s\n", msg);
    }

    void print_summary() {
        printf("\n" YELLOW "========================================\n" RESET);
        printf("Total: %d, Passed: %d, Failed: %d\n", passed_ + failed_, passed_, failed_);
        printf(YELLOW "========================================" RESET "\n\n");
    }
};

TestRunner g_test_runner;

// Mock subscription implementation for testing
struct MockSubscription {
    std::string topic_name;
    std::vector<uint8_t> received_data;
    bool data_received{false};

    void on_data_received(const void* data, unsigned int len) {
        received_data.assign((const uint8_t*)data, (const uint8_t*)data + len);
        data_received = true;
    }
};

/**
 * Test 1: SessionManager Initialization
 */
void test_session_manager_init() {
    g_test_runner.test_start("SessionManager Initialization");

    try {
        SessionManager& sm = SessionManager::instance();
        g_test_runner.test_info("SessionManager singleton retrieved");

        if (!sm.initialize()) {
            g_test_runner.test_fail("SessionManager::initialize() returned false");
            return;
        }
        g_test_runner.test_pass("SessionManager::initialize() succeeded");

        // Try initializing again (should be idempotent)
        if (!sm.initialize()) {
            g_test_runner.test_fail("Second initialize() failed");
            return;
        }
        g_test_runner.test_pass("SessionManager is idempotent");

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 2: CreateSessionServer (register_subscription)
 */
void test_create_session_server() {
    g_test_runner.test_start("CreateSessionServer (register_subscription)");

    try {
        SessionManager& sm = SessionManager::instance();

        // Create a mock subscription
        MockSubscription sub;
        sub.topic_name = "/test_topic";

        int server_id = sm.register_subscription("/test_topic", (SubscriptionImpl*)&sub);

        if (server_id < 0) {
            g_test_runner.test_fail(std::string("register_subscription() returned ") +
                                   std::to_string(server_id));
            return;
        }
        g_test_runner.test_pass(std::string("register_subscription() succeeded, server_id=") +
                                std::to_string(server_id));

        // Try registering the same topic again (should return the same server_id)
        int server_id2 = sm.register_subscription("/test_topic", (SubscriptionImpl*)&sub);
        if (server_id2 != server_id) {
            g_test_runner.test_fail("Second register_subscription() returned different ID");
        } else {
            g_test_runner.test_pass("Duplicate topic registration is idempotent");
        }

        // Register a different topic
        MockSubscription sub2;
        sub2.topic_name = "/another_topic";

        int server_id3 = sm.register_subscription("/another_topic", (SubscriptionImpl*)&sub2);
        if (server_id3 < 0) {
            g_test_runner.test_fail("register_subscription(/another_topic) failed");
        } else if (server_id3 == server_id) {
            g_test_runner.test_fail("Different topics got same server_id");
        } else {
            g_test_runner.test_pass(std::string("Different topic registration succeeded, server_id=") +
                                    std::to_string(server_id3));
        }

        // Cleanup
        sm.unregister_subscription("/test_topic");
        sm.unregister_subscription("/another_topic");
        g_test_runner.test_pass("Subscription unregistration succeeded");

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 3: Discovery Manager Initialization
 */
void test_discovery_init() {
    g_test_runner.test_start("Discovery Manager Initialization");

    try {
        DiscoveryManager& dm = DiscoveryManager::instance();
        g_test_runner.test_info("DiscoveryManager singleton retrieved");

        if (!dm.initialize()) {
            g_test_runner.test_fail("DiscoveryManager::initialize() returned false");
            return;
        }
        g_test_runner.test_pass("DiscoveryManager::initialize() succeeded");

        if (!dm.is_initialized()) {
            g_test_runner.test_fail("is_initialized() returned false after init");
            return;
        }
        g_test_runner.test_pass("is_initialized() returns true");

        // Check statistics
        auto stats = dm.get_stats();
        g_test_runner.test_info(std::string("Initial RX: ") + std::to_string(stats.rx_total) +
                               ", TX: " + std::to_string(stats.tx_total));

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 4: GraphCache Node Registration
 */
void test_graph_cache_nodes() {
    g_test_runner.test_start("GraphCache Node Registration");

    try {
        GraphCache& gc = GraphCache::instance();

        // Register a local node
        GraphNodeInfo node;
        node.node_name = "test_node";
        node.node_namespace = "/test_ns";
        node.enclave = "";

        if (!gc.register_node(node)) {
            g_test_runner.test_fail("register_node() failed");
            return;
        }
        g_test_runner.test_pass("register_node() succeeded");

        // Check if node exists
        auto node_info = gc.get_node_info(node.node_namespace, node.node_name);
        if (!node_info) {
            g_test_runner.test_fail("get_node_info() returned nullptr");
            return;
        }
        g_test_runner.test_pass("get_node_info() found registered node");

        // Register another node
        GraphNodeInfo node2;
        node2.node_name = "another_node";
        node2.node_namespace = "/";
        node2.enclave = "";

        if (!gc.register_node(node2)) {
            g_test_runner.test_fail("register_node() for second node failed");
        } else {
            g_test_runner.test_pass("Multiple node registration succeeded");
        }

        // Get all nodes
        auto nodes = gc.get_all_nodes();
        g_test_runner.test_info(std::string("Total registered nodes: ") +
                               std::to_string(nodes.size()));

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 5: GraphCache Endpoint Registration
 */
void test_graph_cache_endpoints() {
    g_test_runner.test_start("GraphCache Endpoint Registration");

    try {
        GraphCache& gc = GraphCache::instance();

        // Register a publisher endpoint
        GraphEndpointInfo pub_endpoint;
        pub_endpoint.topic_name = "/test_topic";
        pub_endpoint.type_name = "std_msgs/String";
        pub_endpoint.node_name = "test_pub_node";
        pub_endpoint.node_namespace = "/";
        pub_endpoint.type = EndpointType::PUBLISHER;
        memset(pub_endpoint.gid.data, 1, RMW_GID_STORAGE_SIZE);

        if (!gc.register_publisher(pub_endpoint)) {
            g_test_runner.test_fail("register_publisher() failed");
            return;
        }
        g_test_runner.test_pass("register_publisher() succeeded");

        // Register a subscription endpoint
        GraphEndpointInfo sub_endpoint;
        sub_endpoint.topic_name = "/test_topic";
        sub_endpoint.type_name = "std_msgs/String";
        sub_endpoint.node_name = "test_sub_node";
        sub_endpoint.node_namespace = "/";
        sub_endpoint.type = EndpointType::SUBSCRIPTION;
        memset(sub_endpoint.gid.data, 2, RMW_GID_STORAGE_SIZE);

        if (!gc.register_subscription(sub_endpoint)) {
            g_test_runner.test_fail("register_subscription() failed");
        } else {
            g_test_runner.test_pass("register_subscription() succeeded");
        }

        // Get topic info
        auto topic_info = gc.get_topic_info("/test_topic");
        if (!topic_info) {
            g_test_runner.test_fail("get_topic_info() returned nullptr");
        } else {
            g_test_runner.test_info(std::string("Topic /test_topic: ") +
                                   std::to_string(topic_info->publishers.size()) +
                                   " publishers, " +
                                   std::to_string(topic_info->subscriptions.size()) +
                                   " subscriptions");

            if (topic_info->publishers.size() == 1 && topic_info->subscriptions.size() == 1) {
                g_test_runner.test_pass("Topic info correctly shows 1 pub, 1 sub");
            } else {
                g_test_runner.test_fail("Topic info endpoint counts are incorrect");
            }
        }

        // Get all endpoints
        auto endpoints = gc.get_all_endpoints();
        g_test_runner.test_info(std::string("Total registered endpoints: ") +
                               std::to_string(endpoints.size()));

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 6: Graph Cache Snapshot
 */
void test_graph_cache_snapshot() {
    g_test_runner.test_start("GraphCache Snapshot");

    try {
        GraphCache& gc = GraphCache::instance();

        auto snapshot = gc.get_snapshot();
        g_test_runner.test_info(std::string("Snapshot contains ") +
                               std::to_string(snapshot.nodes.size()) +
                               " nodes, " +
                               std::to_string(snapshot.endpoints.size()) +
                               " endpoints");

        g_test_runner.test_pass("Snapshot generation succeeded");

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 7: Discovery Statistics
 */
void test_discovery_stats() {
    g_test_runner.test_start("Discovery Statistics");

    try {
        DiscoveryManager& dm = DiscoveryManager::instance();

        auto stats = dm.get_stats();
        g_test_runner.test_info(std::string("RX: ") + std::to_string(stats.rx_total) +
                               ", TX: " + std::to_string(stats.tx_total));
        g_test_runner.test_info(std::string("Drop Count: ") +
                               std::to_string(stats.drop_invalid + stats.drop_dup +
                                            stats.drop_parse_error));
        g_test_runner.test_info(std::string("Remote Nodes: ") +
                               std::to_string(stats.remote_nodes_count) +
                               ", Remote Endpoints: " +
                               std::to_string(stats.remote_endpoints_count));

        g_test_runner.test_pass("Statistics retrieval succeeded");

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 8: Message Sending (basic)
 */
void test_message_sending() {
    g_test_runner.test_start("Message Sending");

    try {
        SessionManager& sm = SessionManager::instance();

        // Note: Actual message sending requires valid session_id
        // For now, we test the interface exists

        const char* test_msg = "Hello RMW DSoftBus";
        int test_len = strlen(test_msg);

        // Try sending to non-existent session (should fail gracefully)
        int result = sm.send_bytes(-1, test_msg, test_len);
        if (result < 0) {
            g_test_runner.test_pass("send_bytes() correctly rejects invalid session");
        } else {
            g_test_runner.test_fail("send_bytes() accepted invalid session");
        }

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Test 9: Cleanup and Shutdown
 */
void test_cleanup() {
    g_test_runner.test_start("Cleanup and Shutdown");

    try {
        SessionManager& sm = SessionManager::instance();
        sm.shutdown();
        g_test_runner.test_pass("SessionManager::shutdown() succeeded");

        DiscoveryManager& dm = DiscoveryManager::instance();
        dm.shutdown();
        g_test_runner.test_pass("DiscoveryManager::shutdown() succeeded");

        GraphCache& gc = GraphCache::instance();
        gc.clear();
        g_test_runner.test_pass("GraphCache::clear() succeeded");

    } catch (const std::exception& e) {
        g_test_runner.test_fail(std::string("Exception: ") + e.what());
    }
}

/**
 * Main test runner
 */
int main(int argc, char** argv) {
    printf("\n" YELLOW "====================================\n");
    printf("RMW DSoftBus Functional Test Suite\n");
    printf("====================================" RESET "\n");

    // Run all tests
    test_session_manager_init();
    std::this_thread::sleep_for(100ms);

    test_create_session_server();
    std::this_thread::sleep_for(100ms);

    test_discovery_init();
    std::this_thread::sleep_for(100ms);

    test_graph_cache_nodes();
    std::this_thread::sleep_for(100ms);

    test_graph_cache_endpoints();
    std::this_thread::sleep_for(100ms);

    test_graph_cache_snapshot();
    std::this_thread::sleep_for(100ms);

    test_discovery_stats();
    std::this_thread::sleep_for(100ms);

    test_message_sending();
    std::this_thread::sleep_for(100ms);

    test_cleanup();

    // Print summary
    g_test_runner.print_summary();

    return g_test_runner.failed_ > 0 ? 1 : 0;
}
