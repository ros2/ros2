/**
 * @file test_core_functionality.cpp
 * @brief Test core rmw_dsoftbus functionality (SessionManager & GraphCache)
 *
 * This test focuses on testing core Session and Graph functionality
 * without requiring full Discovery initialization.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>

#include "rmw_dsoftbus/session_manager.h"
#include "rmw_dsoftbus/graph_cache.h"

using namespace rmw_dsoftbus;

// Color codes for output
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

int test_count = 0;
int pass_count = 0;
int fail_count = 0;

void test_header(const char* name) {
    printf("\n" YELLOW "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n");
    printf(YELLOW "[TEST %d] %s" RESET "\n", ++test_count, name);
    printf(YELLOW "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n");
}

void pass(const char* msg) {
    printf(GREEN "  ✓ %s\n" RESET, msg);
    pass_count++;
}

void fail(const char* msg) {
    printf(RED "  ✗ %s\n" RESET, msg);
    fail_count++;
}

void info(const char* msg) {
    printf("  ℹ %s\n", msg);
}

/**
 * Test 1: GraphCache Node Registration & Query
 */
void test_graph_cache_nodes() {
    test_header("GraphCache Node Registration");

    try {
        GraphCache& gc = GraphCache::instance();
        gc.initialize();

        // Register nodes
        gc.register_node("talker_node", "/test", "");
        gc.register_node("listener_node", "/test", "");

        // Query all nodes
        auto nodes = gc.get_all_nodes();
        info("Registered nodes:");
        for (const auto& n : nodes) {
            printf("    - %s/%s\n", n.node_namespace.c_str(), n.node_name.c_str());
        }

        if (nodes.size() == 2) {
            pass("Node registration succeeded (count=2)");
        } else {
            fail("Node registration count mismatch");
        }

    } catch (const std::exception& e) {
        fail(e.what());
    }
}

/**
 * Test 2: GraphCache Publisher Registration & Querying
 */
void test_graph_cache_publishers() {
    test_header("GraphCache Publisher Registration");

    try {
        GraphCache& gc = GraphCache::instance();

        // Create GID for publisher
        rmw_gid_t pub_gid;
        memset(pub_gid.data, 0x11, RMW_GID_STORAGE_SIZE);

        rmw_qos_profile_t qos;
        memset(&qos, 0, sizeof(qos));

        // Register publisher
        gc.register_publisher(
            "/chatter",              // topic_name
            "std_msgs/String",       // type_name
            "talker_node",           // node_name
            "/test",                 // node_namespace
            &qos,                    // qos
            &pub_gid,                // gid
            nullptr);                // impl_ptr

        // Query publishers count
        size_t pub_count = gc.count_publishers("/chatter");
        info("Publisher count for /chatter: " + std::to_string(pub_count));

        if (pub_count == 1) {
            pass("Publisher registration and counting succeeded");
        } else {
            fail("Publisher count mismatch");
        }

        // Get topic names
        auto topics = gc.get_topic_names_and_types();
        info("Registered topics: " + std::to_string(topics.size()));

        if (topics.find("/chatter") != topics.end()) {
            pass("Topic /chatter found in topic list");
        }

    } catch (const std::exception& e) {
        fail(e.what());
    }
}

/**
 * Test 3: GraphCache Subscription Registration & Matching
 */
void test_graph_cache_subscriptions() {
    test_header("GraphCache Subscription Registration");

    try {
        GraphCache& gc = GraphCache::instance();

        // Create GID for subscription
        rmw_gid_t sub_gid;
        memset(sub_gid.data, 0x22, RMW_GID_STORAGE_SIZE);

        rmw_qos_profile_t qos;
        memset(&qos, 0, sizeof(qos));

        // Register subscription
        gc.register_subscription(
            "/chatter",              // topic_name
            "std_msgs/String",       // type_name
            "listener_node",         // node_name
            "/test",                 // node_namespace
            &qos,                    // qos
            &sub_gid,                // gid
            nullptr);                // impl_ptr

        // Query subscribers count
        size_t sub_count = gc.count_subscribers("/chatter");
        info("Subscriber count for /chatter: " + std::to_string(sub_count));

        if (sub_count == 1) {
            pass("Subscription registration and counting succeeded");
        } else {
            fail("Subscription count mismatch");
        }

        // Query both pub and sub for same topic
        size_t pub_count = gc.count_publishers("/chatter");
        size_t final_sub_count = gc.count_subscribers("/chatter");
        info("Final topic state: " + std::to_string(pub_count) + " publishers, " +
             std::to_string(final_sub_count) + " subscribers");

        if (pub_count == 1 && final_sub_count == 1) {
            pass("Topic has both publisher and subscriber");
        }

    } catch (const std::exception& e) {
        fail(e.what());
    }
}

/**
 * Test 4: SessionManager Initialization
 */
void test_session_manager_init() {
    test_header("SessionManager Initialization");

    try {
        SessionManager& sm = SessionManager::instance();

        if (!sm.initialize()) {
            fail("SessionManager::initialize() returned false");
            return;
        }
        pass("SessionManager::initialize() succeeded");

        // Try initializing again (should be idempotent)
        if (!sm.initialize()) {
            fail("Second initialize() failed");
            return;
        }
        pass("SessionManager is idempotent");

    } catch (const std::exception& e) {
        fail(e.what());
    }
}

/**
 * Test 5: SessionManager CreateSessionServer
 */
void test_session_create_server() {
    test_header("SessionManager CreateSessionServer");

    try {
        SessionManager& sm = SessionManager::instance();

        // Register subscription (which calls CreateSessionServer internally)
        MockSubscription* sub = new MockSubscription();
        int server_id = sm.register_subscription("/test_topic", sub);

        if (server_id < 0) {
            fail("register_subscription() returned negative ID");
            delete sub;
            return;
        }
        pass("register_subscription() succeeded, server_id=" + std::to_string(server_id));

        // Register another topic
        MockSubscription* sub2 = new MockSubscription();
        int server_id2 = sm.register_subscription("/another_topic", sub2);

        if (server_id2 >= 0) {
            pass("Multiple subscription servers created");
        } else {
            fail("Second register_subscription() failed");
        }

        // Cleanup
        sm.unregister_subscription("/test_topic");
        sm.unregister_subscription("/another_topic");
        delete sub;
        delete sub2;
        pass("Subscription cleanup succeeded");

    } catch (const std::exception& e) {
        fail(e.what());
    }
}

struct MockSubscription {
    std::string topic_name;
};

/**
 * Test 6: Graph Snapshot
 */
void test_graph_snapshot() {
    test_header("Graph Snapshot");

    try {
        GraphCache& gc = GraphCache::instance();

        // Get snapshot of current state
        auto snap = gc.snapshot();

        info("Snapshot state:");
        info("  Nodes: " + std::to_string(snap.nodes.size()));
        info("  Endpoints: " + std::to_string(snap.endpoints.size()));

        pass("Graph snapshot generation succeeded");

    } catch (const std::exception& e) {
        fail(e.what());
    }
}

/**
 * Test 7: Graph Version Tracking
 */
void test_graph_version() {
    test_header("Graph Version Tracking");

    try {
        GraphCache& gc = GraphCache::instance();

        // Get initial version
        uint64_t v1 = gc.get_graph_version();
        info("Initial graph version: " + std::to_string(v1));

        // Register a new publisher
        rmw_gid_t gid;
        memset(gid.data, 0x33, RMW_GID_STORAGE_SIZE);
        rmw_qos_profile_t qos;
        memset(&qos, 0, sizeof(qos));

        gc.register_publisher(
            "/new_topic",
            "std_msgs/Int32",
            "pub_node",
            "/version_test",
            &qos,
            &gid,
            nullptr);

        // Get new version
        uint64_t v2 = gc.get_graph_version();
        info("Graph version after register_publisher: " + std::to_string(v2));

        if (v2 > v1) {
            pass("Graph version incremented on change");
        } else {
            fail("Graph version did not increment");
        }

    } catch (const std::exception& e) {
        fail(e.what());
    }
}

/**
 * Main test runner
 */
int main(int argc, char** argv) {
    printf("\n" YELLOW "╔════════════════════════════════════════════════╗\n");
    printf("║   rmw_dsoftbus Core Functionality Test Suite   ║\n");
    printf("╚════════════════════════════════════════════════╝" RESET "\n");

    // Run all tests
    test_graph_cache_nodes();
    test_graph_cache_publishers();
    test_graph_cache_subscriptions();
    test_session_manager_init();
    test_session_create_server();
    test_graph_snapshot();
    test_graph_version();

    // Print summary
    printf("\n" YELLOW "════════════════════════════════════════════════\n" RESET);
    printf("Test Results:\n");
    printf(GREEN "  ✓ Passed: %d\n" RESET, pass_count);
    printf(RED "  ✗ Failed: %d\n" RESET, fail_count);
    printf("  Total:  %d\n", test_count);
    printf(YELLOW "════════════════════════════════════════════════" RESET "\n\n");

    return fail_count > 0 ? 1 : 0;
}
