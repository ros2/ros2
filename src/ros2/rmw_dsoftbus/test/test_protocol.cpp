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
 * @file test_protocol.cpp
 * @brief Unit tests for rmw_dsoftbus protocol encoding/decoding
 *
 * Tests:
 * - CRC32 checksum calculation
 * - NodeInfo JSON encoding/decoding
 * - DiscoveryMessage JSON encoding/decoding
 * - Protocol constants and data structures
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#include "rmw_dsoftbus/protocol.h"

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
// CRC32 Tests
// ============================================================================

TEST(test_crc32_empty) {
    const uint8_t data[] = {};
    uint32_t crc = calculate_crc32(data, 0);
    fprintf(stderr, "  CRC32(empty) = 0x%08X\n", crc);
    ASSERT_EQ(crc, 0);
}

TEST(test_crc32_simple) {
    const uint8_t data[] = "Hello, World!";
    uint32_t crc = calculate_crc32(data, sizeof(data) - 1);
    fprintf(stderr, "  CRC32(\"Hello, World!\") = 0x%08X\n", crc);
    ASSERT_TRUE(crc != 0);
}

TEST(test_crc32_deterministic) {
    const uint8_t data[] = "Test data";
    uint32_t crc1 = calculate_crc32(data, sizeof(data) - 1);
    uint32_t crc2 = calculate_crc32(data, sizeof(data) - 1);
    fprintf(stderr, "  CRC32 deterministic: 0x%08X == 0x%08X\n", crc1, crc2);
    ASSERT_EQ(crc1, crc2);
}

TEST(test_crc32_different_data) {
    const uint8_t data1[] = "Test data 1";
    const uint8_t data2[] = "Test data 2";
    uint32_t crc1 = calculate_crc32(data1, sizeof(data1) - 1);
    uint32_t crc2 = calculate_crc32(data2, sizeof(data2) - 1);
    fprintf(stderr, "  CRC32 different: 0x%08X != 0x%08X\n", crc1, crc2);
    ASSERT_TRUE(crc1 != crc2);
}

// ============================================================================
// NodeInfo JSON Tests
// ============================================================================

TEST(test_node_info_encode) {
    NodeInfo node;
    node.node_name = "/talker";
    node.namespace_ = "/";
    node.network_id = "test_network_id_123";
    node.timestamp_ms = 1234567890;
    node.gid = "0102030405060708090a0b0c0d0e0f101112131415161718";

    std::string json = encode_node_info_json(node);
    fprintf(stderr, "  Encoded: %s\n", json.c_str());

    ASSERT_TRUE(json.find("\"node_name\":\"/talker\"") != std::string::npos);
    ASSERT_TRUE(json.find("\"namespace_\":\"/\"") != std::string::npos);
    ASSERT_TRUE(json.find("\"network_id\":\"test_network_id_123\"") != std::string::npos);
    ASSERT_TRUE(json.find("\"timestamp_ms\":1234567890") != std::string::npos);
}

TEST(test_node_info_roundtrip) {
    NodeInfo original;
    original.node_name = "/listener";
    original.namespace_ = "/test_ns";
    original.network_id = "network_456";
    original.timestamp_ms = 9876543210;
    original.gid = "abcdef123456789012345678901234567890abcd";

    std::string json = encode_node_info_json(original);
    fprintf(stderr, "  JSON: %s\n", json.c_str());

    NodeInfo decoded;
    bool result = decode_node_info_json(json, decoded);

    ASSERT_TRUE(result);
    ASSERT_STR_EQ(decoded.node_name, original.node_name);
    ASSERT_STR_EQ(decoded.namespace_, original.namespace_);
    ASSERT_STR_EQ(decoded.network_id, original.network_id);
    ASSERT_EQ(decoded.timestamp_ms, original.timestamp_ms);
    ASSERT_STR_EQ(decoded.gid, original.gid);
}

TEST(test_node_info_special_characters) {
    NodeInfo node;
    node.node_name = "/node_with_\"quotes\"";
    node.namespace_ = "/ns\\with\\backslash";
    node.network_id = "id\nwith\nnewline";
    node.timestamp_ms = 12345;
    node.gid = "test_gid";

    std::string json = encode_node_info_json(node);
    fprintf(stderr, "  JSON with escapes: %s\n", json.c_str());

    ASSERT_TRUE(json.find("\\\"") != std::string::npos); // Should have escaped quotes
    ASSERT_TRUE(json.find("\\\\") != std::string::npos); // Should have escaped backslash
}

// ============================================================================
// DiscoveryMessage JSON Tests
// ============================================================================

TEST(test_discovery_message_encode_empty) {
    DiscoveryMessage msg;
    msg.type = DiscoveryMessage::NODE_ANNOUNCE;
    msg.source_network_id = "source_123";
    msg.timestamp_ms = 1111111111;

    std::string json = encode_discovery_message_json(msg);
    fprintf(stderr, "  Encoded: %s\n", json.c_str());

    ASSERT_TRUE(json.find("\"type\":\"NODE_ANNOUNCE\"") != std::string::npos);
    ASSERT_TRUE(json.find("\"source_network_id\":\"source_123\"") != std::string::npos);
    ASSERT_TRUE(json.find("\"timestamp_ms\":1111111111") != std::string::npos);
    ASSERT_TRUE(json.find("\"nodes\":[]") != std::string::npos);
    ASSERT_TRUE(json.find("\"endpoints\":[]") != std::string::npos);
}

TEST(test_discovery_message_with_nodes) {
    DiscoveryMessage msg;
    msg.type = DiscoveryMessage::GRAPH_SNAPSHOT;
    msg.source_network_id = "source_456";
    msg.timestamp_ms = 2222222222;

    NodeInfo node1;
    node1.node_name = "/node1";
    node1.namespace_ = "/";
    node1.network_id = "net1";
    node1.timestamp_ms = 1000;
    node1.gid = "gid1";
    msg.nodes.push_back(node1);

    NodeInfo node2;
    node2.node_name = "/node2";
    node2.namespace_ = "/ns2";
    node2.network_id = "net2";
    node2.timestamp_ms = 2000;
    node2.gid = "gid2";
    msg.nodes.push_back(node2);

    std::string json = encode_discovery_message_json(msg);
    fprintf(stderr, "  Encoded: %s\n", json.c_str());

    ASSERT_TRUE(json.find("\"node_name\":\"/node1\"") != std::string::npos);
    ASSERT_TRUE(json.find("\"node_name\":\"/node2\"") != std::string::npos);
}

TEST(test_discovery_message_roundtrip) {
    DiscoveryMessage original;
    original.type = DiscoveryMessage::ENDPOINT_ANNOUNCE;
    original.source_network_id = "net_789";
    original.timestamp_ms = 3333333333;

    NodeInfo node;
    node.node_name = "/test_node";
    node.namespace_ = "/test";
    node.network_id = "network_id";
    node.timestamp_ms = 4444;
    node.gid = "test_gid";
    original.nodes.push_back(node);

    std::string json = encode_discovery_message_json(original);
    fprintf(stderr, "  JSON: %s\n", json.c_str());

    DiscoveryMessage decoded;
    bool result = decode_discovery_message_json(json, decoded);

    ASSERT_TRUE(result);
    ASSERT_EQ((int)decoded.type, (int)original.type);
    ASSERT_STR_EQ(decoded.source_network_id, original.source_network_id);
    ASSERT_EQ(decoded.timestamp_ms, original.timestamp_ms);
    ASSERT_EQ(decoded.nodes.size(), 1u);
    ASSERT_STR_EQ(decoded.nodes[0].node_name, node.node_name);
}

// ============================================================================
// Protocol Constants Tests
// ============================================================================

TEST(test_protocol_constants) {
    fprintf(stderr, "  MAGIC_NUMBER = 0x%08X\n", MAGIC_NUMBER);
    fprintf(stderr, "  PROTOCOL_VERSION = %d\n", PROTOCOL_VERSION);
    fprintf(stderr, "  DISCOVERY_BROADCAST_INTERVAL_MS = %u\n", DISCOVERY_BROADCAST_INTERVAL_MS);
    fprintf(stderr, "  NODE_TIMEOUT_MS = %u\n", NODE_TIMEOUT_MS);

    ASSERT_EQ(MAGIC_NUMBER, 0x524D5744); // "RMWD"
    ASSERT_EQ(PROTOCOL_VERSION, 1);
    ASSERT_EQ(DISCOVERY_BROADCAST_INTERVAL_MS, 5000);
    ASSERT_EQ(NODE_TIMEOUT_MS, 15000);
}

TEST(test_data_message_header_size) {
    DataMessageHeader header;
    fprintf(stderr, "  sizeof(DataMessageHeader) = %zu bytes\n", sizeof(header));
    ASSERT_EQ(sizeof(header), 1024u); // Should be exactly 1024 bytes
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main() {
    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "rmw_dsoftbus Protocol Unit Tests\n");
    fprintf(stderr, "=================================================\n");

    // Run all tests
    test_crc32_empty_runner();
    test_crc32_simple_runner();
    test_crc32_deterministic_runner();
    test_crc32_different_data_runner();

    test_node_info_encode_runner();
    test_node_info_roundtrip_runner();
    test_node_info_special_characters_runner();

    test_discovery_message_encode_empty_runner();
    test_discovery_message_with_nodes_runner();
    test_discovery_message_roundtrip_runner();

    test_protocol_constants_runner();
    test_data_message_header_size_runner();

    // Print summary
    fprintf(stderr, "\n=================================================\n");
    fprintf(stderr, "Test Summary:\n");
    fprintf(stderr, "  Total:  %d\n", test_count);
    fprintf(stderr, "  Passed: %d\n", test_pass);
    fprintf(stderr, "  Failed: %d\n", test_fail);
    fprintf(stderr, "=================================================\n");

    return (test_fail == 0) ? 0 : 1;
}
