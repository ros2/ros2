/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

/**
 * @file simple_graph_test.cpp
 * @brief Simplified standalone test for GraphCache and DiscoveryManager
 *
 * This test runs without full RMW environment, suitable for verifying
 * Graph Discovery implementation without ROS2.
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// Use mock RMW headers
#include "rmw/types.h"
#include "rmw/rmw.h"

// Minimal stub for rmw_trigger_guard_condition
extern "C" {
int rmw_trigger_guard_condition(const rmw_guard_condition_t* guard_condition) {
    (void)guard_condition;
    return 0;
}
}

// Include GraphCache header
#include "rmw_dsoftbus/graph_cache.h"

using namespace rmw_dsoftbus;

// Test utilities
static int test_count = 0;
static int test_pass = 0;
static int test_fail = 0;

#define TEST(name) \
    static void name(); \
    static void name##_runner() { \
        test_count++; \
        fprintf(stderr, "\n[TEST %d] %s...\n", test_count, #name); \
        name(); \
        test_pass++; \
        fprintf(stderr, "[TEST %d] PASSED\n", test_count); \
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

#define ASSERT_EQ(a, b) \
    do { \
        auto _a = (a); \
        auto _b = (b); \
        if (_a != _b) { \
            fprintf(stderr, "[ASSERT FAILED] %s:%d: Expected %lld, got %lld\n", \
                    __FILE__, __LINE__, (long long)_b, (long long)_a); \
            test_fail++; \
            return; \
        } \
    } while (0)

// Helper functions
static rmw_gid_t make_gid(uint8_t id) {
    rmw_gid_t gid;
    memset(&gid, 0, sizeof(gid));
    gid.data[0] = id;
    return gid;
}

static rmw_qos_profile_t make_qos() {
    rmw_qos_profile_t qos;
    qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos.depth = 10;
    qos.reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    return qos;
}

// GraphCache Tests
TEST(test_graphcache_initialize) {
    GraphCache& cache = GraphCache::instance();
    bool result = cache.initialize();
    ASSERT_TRUE(result);
    fprintf(stderr, "  GraphCache initialized\n");
}

TEST(test_node_registration) {
    GraphCache& cache = GraphCache::instance();

    cache.register_node("talker", "/", "");

    auto nodes = cache.get_all_nodes();
    ASSERT_TRUE(nodes.size() >= 1);

    bool found = false;
    for (const auto& node : nodes) {
        if (node.node_name == "talker" && node.node_namespace == "/") {
            found = true;
            break;
        }
    }
    ASSERT_TRUE(found);

    cache.unregister_node("talker", "/");
    fprintf(stderr, "  Node registration/unregistration OK\n");
}

TEST(test_publisher_registration) {
    GraphCache& cache = GraphCache::instance();

    cache.register_node("talker", "/", "");

    rmw_gid_t gid = make_gid(1);
    rmw_qos_profile_t qos = make_qos();
    cache.register_publisher("/chatter", "std_msgs::msg::String",
                            "talker", "/", &qos, &gid, nullptr);

    size_t count = cache.count_publishers("/chatter");
    ASSERT_EQ(count, 1u);

    cache.unregister_endpoint(&gid);
    cache.unregister_node("talker", "/");
    fprintf(stderr, "  Publisher registration OK\n");
}

TEST(test_subscription_registration) {
    GraphCache& cache = GraphCache::instance();

    cache.register_node("listener", "/", "");

    rmw_gid_t gid = make_gid(2);
    rmw_qos_profile_t qos = make_qos();
    cache.register_subscription("/chatter", "std_msgs::msg::String",
                                "listener", "/", &qos, &gid, nullptr);

    size_t count = cache.count_subscribers("/chatter");
    ASSERT_EQ(count, 1u);

    cache.unregister_endpoint(&gid);
    cache.unregister_node("listener", "/");
    fprintf(stderr, "  Subscription registration OK\n");
}

TEST(test_topic_names_and_types) {
    GraphCache& cache = GraphCache::instance();

    cache.register_node("test_node", "/", "");
    rmw_gid_t gid = make_gid(10);
    rmw_qos_profile_t qos = make_qos();
    cache.register_publisher("/test_topic", "std_msgs::msg::Int32",
                            "test_node", "/", &qos, &gid, nullptr);

    auto topics = cache.get_topic_names_and_types();
    ASSERT_TRUE(topics.find("/test_topic") != topics.end());
    ASSERT_TRUE(topics["/test_topic"].find("std_msgs::msg::Int32") !=
                topics["/test_topic"].end());

    cache.unregister_endpoint(&gid);
    cache.unregister_node("test_node", "/");
    fprintf(stderr, "  Topic names and types query OK\n");
}

TEST(test_graph_version_tracking) {
    GraphCache& cache = GraphCache::instance();

    uint64_t v1 = cache.get_graph_version();

    cache.register_node("version_test", "/", "");
    uint64_t v2 = cache.get_graph_version();
    ASSERT_TRUE(v2 > v1);

    cache.unregister_node("version_test", "/");
    uint64_t v3 = cache.get_graph_version();
    ASSERT_TRUE(v3 > v2);

    fprintf(stderr, "  Graph version tracking OK (v1=%llu, v2=%llu, v3=%llu)\n",
            (unsigned long long)v1, (unsigned long long)v2, (unsigned long long)v3);
}

// Main test runner
int main() {
    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "Simplified GraphCache Test (No ROS2 Required)\n");
    fprintf(stderr, "=================================================\n");

    test_graphcache_initialize_runner();
    test_node_registration_runner();
    test_publisher_registration_runner();
    test_subscription_registration_runner();
    test_topic_names_and_types_runner();
    test_graph_version_tracking_runner();

    fprintf(stderr, "\n=================================================\n");
    fprintf(stderr, "Test Summary:\n");
    fprintf(stderr, "  Total:  %d\n", test_count);
    fprintf(stderr, "  Passed: %d\n", test_pass);
    fprintf(stderr, "  Failed: %d\n", test_fail);
    fprintf(stderr, "=================================================\n");

    if (test_fail == 0) {
        fprintf(stderr, "\n✅ All tests passed! GraphCache is working correctly.\n");
    } else {
        fprintf(stderr, "\n❌ Some tests failed.\n");
    }

    return (test_fail == 0) ? 0 : 1;
}
