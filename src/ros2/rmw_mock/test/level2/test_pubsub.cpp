// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 2 Acceptance Test: Pub/Sub Core
// Tests: publisher, subscription, serialized message, MockRouter, wait UNSUPPORTED

#include <cstdio>
#include <cstring>
#include <vector>

#include "rmw/rmw.h"
#include "rmw_mock/types.h"

//=============================================================================
// Test utilities
//=============================================================================

static int g_test_count = 0;
static int g_pass_count = 0;

#define TEST_ASSERT(cond, msg) do { \
  g_test_count++; \
  if (!(cond)) { \
    fprintf(stderr, "[FAIL] %s: %s\n", __func__, msg); \
    return false; \
  } \
  g_pass_count++; \
  fprintf(stdout, "[PASS] %s: %s\n", __func__, msg); \
} while(0)

#define RUN_TEST(func) do { \
  fprintf(stdout, "\n--- %s ---\n", #func); \
  if (!func()) { \
    fprintf(stderr, "TEST FAILED: %s\n", #func); \
  } \
} while(0)

//=============================================================================
// Test: Publisher lifecycle
//=============================================================================
static bool test_publisher_lifecycle()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  // Create node
  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test");
  TEST_ASSERT(node != nullptr, "rmw_create_node");

  // Create publisher
  rmw_qos_profile_t qos = rmw_qos_profile_default;
  rmw_publisher_options_t pub_options = rmw_get_default_publisher_options();

  rmw_publisher_t * pub = rmw_create_publisher(
    node, nullptr, "/test_topic", &qos, &pub_options);
  TEST_ASSERT(pub != nullptr, "rmw_create_publisher");
  TEST_ASSERT(pub->topic_name != nullptr, "publisher has topic_name");
  TEST_ASSERT(strcmp(pub->topic_name, "/test_topic") == 0, "topic_name matches");

  // Get GID
  rmw_gid_t gid;
  ret = rmw_get_gid_for_publisher(pub, &gid);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_get_gid_for_publisher");

  // Get actual QoS
  rmw_qos_profile_t actual_qos;
  ret = rmw_publisher_get_actual_qos(pub, &actual_qos);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_publisher_get_actual_qos");

  // Destroy publisher
  ret = rmw_destroy_publisher(node, pub);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_destroy_publisher");

  // Cleanup
  ret = rmw_destroy_node(node);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_destroy_node");

  ret = rmw_shutdown(&context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_shutdown");

  ret = rmw_context_fini(&context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_context_fini");

  ret = rmw_init_options_fini(&init_options);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init_options_fini");

  return true;
}

//=============================================================================
// Test: Subscription lifecycle
//=============================================================================
static bool test_subscription_lifecycle()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  // Create node
  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test");
  TEST_ASSERT(node != nullptr, "rmw_create_node");

  // Create subscription
  rmw_qos_profile_t qos = rmw_qos_profile_default;
  rmw_subscription_options_t sub_options = rmw_get_default_subscription_options();

  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, &sub_options);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription");
  TEST_ASSERT(sub->topic_name != nullptr, "subscription has topic_name");
  TEST_ASSERT(strcmp(sub->topic_name, "/test_topic") == 0, "topic_name matches");

  // Get actual QoS
  rmw_qos_profile_t actual_qos;
  ret = rmw_subscription_get_actual_qos(sub, &actual_qos);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_subscription_get_actual_qos");

  // Destroy subscription
  ret = rmw_destroy_subscription(node, sub);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_destroy_subscription");

  // Cleanup
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: Serialized message publish and take
//=============================================================================
static bool test_serialized_pubsub()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  // Create node
  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test");
  TEST_ASSERT(node != nullptr, "rmw_create_node");

  // Create subscription first (so it's registered before publish)
  rmw_qos_profile_t qos = rmw_qos_profile_default;
  rmw_subscription_options_t sub_options = rmw_get_default_subscription_options();

  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, &sub_options);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription");

  // Create publisher
  rmw_publisher_options_t pub_options = rmw_get_default_publisher_options();

  rmw_publisher_t * pub = rmw_create_publisher(
    node, nullptr, "/test_topic", &qos, &pub_options);
  TEST_ASSERT(pub != nullptr, "rmw_create_publisher");

  // Create test message (simulating CDR-serialized data)
  const char * test_data = "Hello, rmw_mock Level 2!";
  size_t test_len = strlen(test_data) + 1;

  rmw_serialized_message_t serialized_msg;
  serialized_msg.buffer = reinterpret_cast<uint8_t *>(const_cast<char *>(test_data));
  serialized_msg.buffer_length = test_len;
  serialized_msg.buffer_capacity = test_len;
  serialized_msg.allocator = rcutils_get_default_allocator();

  // Publish serialized message
  ret = rmw_publish_serialized_message(pub, &serialized_msg, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_publish_serialized_message");

  // Take serialized message
  rmw_serialized_message_t received_msg;
  received_msg.buffer = static_cast<uint8_t *>(malloc(256));
  received_msg.buffer_length = 0;
  received_msg.buffer_capacity = 256;
  received_msg.allocator = rcutils_get_default_allocator();

  bool taken = false;
  ret = rmw_take_serialized_message(sub, &received_msg, &taken, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_take_serialized_message");
  TEST_ASSERT(taken == true, "message was taken");
  TEST_ASSERT(received_msg.buffer_length == test_len, "message length matches");
  TEST_ASSERT(memcmp(received_msg.buffer, test_data, test_len) == 0, "message content matches");

  // Try to take again (should be empty)
  taken = false;
  ret = rmw_take_serialized_message(sub, &received_msg, &taken, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_take_serialized_message (empty queue)");
  TEST_ASSERT(taken == false, "no message available");

  free(received_msg.buffer);

  // Cleanup
  rmw_destroy_publisher(node, pub);
  rmw_destroy_subscription(node, sub);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: Serialized message with info
//=============================================================================
static bool test_serialized_pubsub_with_info()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test");
  TEST_ASSERT(node != nullptr, "rmw_create_node");

  rmw_qos_profile_t qos = rmw_qos_profile_default;

  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription");

  rmw_publisher_t * pub = rmw_create_publisher(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(pub != nullptr, "rmw_create_publisher");

  // Publish
  const char * test_data = "Test with info";
  rmw_serialized_message_t serialized_msg;
  serialized_msg.buffer = reinterpret_cast<uint8_t *>(const_cast<char *>(test_data));
  serialized_msg.buffer_length = strlen(test_data) + 1;
  serialized_msg.buffer_capacity = serialized_msg.buffer_length;
  serialized_msg.allocator = rcutils_get_default_allocator();

  ret = rmw_publish_serialized_message(pub, &serialized_msg, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_publish_serialized_message");

  // Take with info
  rmw_serialized_message_t received_msg;
  received_msg.buffer = static_cast<uint8_t *>(malloc(256));
  received_msg.buffer_length = 0;
  received_msg.buffer_capacity = 256;
  received_msg.allocator = rcutils_get_default_allocator();

  rmw_message_info_t message_info;
  bool taken = false;

  ret = rmw_take_serialized_message_with_info(sub, &received_msg, &taken, &message_info, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_take_serialized_message_with_info");
  TEST_ASSERT(taken == true, "message was taken");
  TEST_ASSERT(message_info.source_timestamp > 0, "source_timestamp is set");
  TEST_ASSERT(message_info.received_timestamp >= message_info.source_timestamp,
    "received_timestamp >= source_timestamp");
  TEST_ASSERT(message_info.from_intra_process == true, "from_intra_process is true");

  free(received_msg.buffer);

  // Cleanup
  rmw_destroy_publisher(node, pub);
  rmw_destroy_subscription(node, sub);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: Matched endpoint counts
//=============================================================================
static bool test_matched_counts()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test");
  TEST_ASSERT(node != nullptr, "rmw_create_node");

  rmw_qos_profile_t qos = rmw_qos_profile_default;

  // Create publisher
  rmw_publisher_t * pub = rmw_create_publisher(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(pub != nullptr, "rmw_create_publisher");

  // Initially no subscribers
  size_t sub_count = 999;
  ret = rmw_publisher_count_matched_subscriptions(pub, &sub_count);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_publisher_count_matched_subscriptions");
  TEST_ASSERT(sub_count == 0, "initially 0 subscriptions");

  // Create subscription
  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription");

  // Now 1 subscriber
  ret = rmw_publisher_count_matched_subscriptions(pub, &sub_count);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_publisher_count_matched_subscriptions after sub");
  TEST_ASSERT(sub_count == 1, "1 subscription after create");

  // Check from subscription side
  size_t pub_count = 999;
  ret = rmw_subscription_count_matched_publishers(sub, &pub_count);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_subscription_count_matched_publishers");
  TEST_ASSERT(pub_count == 1, "1 publisher");

  // Destroy subscription
  rmw_destroy_subscription(node, sub);

  // Now 0 subscribers again
  ret = rmw_publisher_count_matched_subscriptions(pub, &sub_count);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_publisher_count_matched_subscriptions after destroy");
  TEST_ASSERT(sub_count == 0, "0 subscriptions after destroy");

  // Cleanup
  rmw_destroy_publisher(node, pub);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: wait APIs require valid context (Level 3 provides implementation)
// Note: In full build with Level 3, wait APIs are implemented.
// This test verifies error handling for invalid arguments.
//=============================================================================
static bool test_wait_requires_context()
{
  // rmw_wait with null wait_set should return INVALID_ARGUMENT (Level 3 impl)
  // or UNSUPPORTED (Level 2 only build)
  rmw_ret_t ret = rmw_wait(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
  TEST_ASSERT(ret == RMW_RET_INVALID_ARGUMENT || ret == RMW_RET_UNSUPPORTED,
    "rmw_wait returns INVALID_ARGUMENT or UNSUPPORTED with null wait_set");

  // rmw_create_wait_set with null context should return nullptr
  rmw_wait_set_t * wait_set = rmw_create_wait_set(nullptr, 0);
  TEST_ASSERT(wait_set == nullptr, "rmw_create_wait_set returns nullptr with null context");

  // rmw_create_guard_condition with null context should return nullptr
  rmw_guard_condition_t * gc = rmw_create_guard_condition(nullptr);
  TEST_ASSERT(gc == nullptr, "rmw_create_guard_condition returns nullptr with null context");

  return true;
}

//=============================================================================
// Test: Typed publish returns UNSUPPORTED
//=============================================================================
static bool test_typed_publish_unsupported()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test");
  TEST_ASSERT(node != nullptr, "rmw_create_node");

  rmw_qos_profile_t qos = rmw_qos_profile_default;

  rmw_publisher_t * pub = rmw_create_publisher(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(pub != nullptr, "rmw_create_publisher");

  // rmw_publish should return UNSUPPORTED
  int dummy_msg = 42;
  ret = rmw_publish(pub, &dummy_msg, nullptr);
  TEST_ASSERT(ret == RMW_RET_UNSUPPORTED, "rmw_publish returns UNSUPPORTED");

  // Cleanup
  rmw_destroy_publisher(node, pub);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: FIFO overflow (queue depth)
//=============================================================================
static bool test_fifo_overflow()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test");
  TEST_ASSERT(node != nullptr, "rmw_create_node");

  // Create subscription with depth 3
  rmw_qos_profile_t qos = rmw_qos_profile_default;
  qos.depth = 3;

  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription depth=3");

  rmw_publisher_t * pub = rmw_create_publisher(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(pub != nullptr, "rmw_create_publisher");

  // Publish 5 messages (should overflow, keeping newest 3)
  for (int i = 0; i < 5; i++) {
    char msg[32];
    snprintf(msg, sizeof(msg), "msg_%d", i);

    rmw_serialized_message_t serialized_msg;
    serialized_msg.buffer = reinterpret_cast<uint8_t *>(msg);
    serialized_msg.buffer_length = strlen(msg) + 1;
    serialized_msg.buffer_capacity = serialized_msg.buffer_length;
    serialized_msg.allocator = rcutils_get_default_allocator();

    ret = rmw_publish_serialized_message(pub, &serialized_msg, nullptr);
    TEST_ASSERT(ret == RMW_RET_OK, "publish message");
  }

  // Take all messages - should get msg_2, msg_3, msg_4 (oldest discarded)
  rmw_serialized_message_t received_msg;
  received_msg.buffer = static_cast<uint8_t *>(malloc(256));
  received_msg.buffer_capacity = 256;
  received_msg.allocator = rcutils_get_default_allocator();

  int received_count = 0;
  bool taken = true;
  while (taken) {
    received_msg.buffer_length = 0;
    ret = rmw_take_serialized_message(sub, &received_msg, &taken, nullptr);
    TEST_ASSERT(ret == RMW_RET_OK, "take message");
    if (taken) {
      received_count++;
      // First message should be msg_2 (oldest kept)
      if (received_count == 1) {
        TEST_ASSERT(strcmp(reinterpret_cast<char *>(received_msg.buffer), "msg_2") == 0,
          "first message is msg_2 (oldest kept)");
      }
    }
  }

  TEST_ASSERT(received_count == 3, "received exactly 3 messages (queue depth)");

  free(received_msg.buffer);

  // Cleanup
  rmw_destroy_publisher(node, pub);
  rmw_destroy_subscription(node, sub);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: Context isolation
//=============================================================================
static bool test_context_isolation()
{
  // Create two contexts
  rmw_init_options_t init_options1 = rmw_get_zero_initialized_init_options();
  rmw_init_options_t init_options2 = rmw_get_zero_initialized_init_options();

  rmw_init_options_init(&init_options1, rcutils_get_default_allocator());
  rmw_init_options_init(&init_options2, rcutils_get_default_allocator());

  rmw_context_t context1 = rmw_get_zero_initialized_context();
  rmw_context_t context2 = rmw_get_zero_initialized_context();

  rmw_ret_t ret = rmw_init(&init_options1, &context1);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init context1");

  ret = rmw_init(&init_options2, &context2);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init context2");

  // Create nodes in each context
  rmw_node_t * node1 = rmw_create_node(&context1, "node1", "/");
  rmw_node_t * node2 = rmw_create_node(&context2, "node2", "/");
  TEST_ASSERT(node1 != nullptr, "create node1");
  TEST_ASSERT(node2 != nullptr, "create node2");

  rmw_qos_profile_t qos = rmw_qos_profile_default;

  // Create pub in context1, sub in context2 (same topic name)
  rmw_publisher_t * pub1 = rmw_create_publisher(
    node1, nullptr, "/shared_topic", &qos, nullptr);
  rmw_subscription_t * sub2 = rmw_create_subscription(
    node2, nullptr, "/shared_topic", &qos, nullptr);

  TEST_ASSERT(pub1 != nullptr, "create pub1");
  TEST_ASSERT(sub2 != nullptr, "create sub2");

  // Publish from context1
  const char * msg = "from_context1";
  rmw_serialized_message_t serialized_msg;
  serialized_msg.buffer = reinterpret_cast<uint8_t *>(const_cast<char *>(msg));
  serialized_msg.buffer_length = strlen(msg) + 1;
  serialized_msg.buffer_capacity = serialized_msg.buffer_length;
  serialized_msg.allocator = rcutils_get_default_allocator();

  ret = rmw_publish_serialized_message(pub1, &serialized_msg, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "publish from context1");

  // Try to take in context2 (should NOT receive - different contexts are isolated)
  rmw_serialized_message_t received_msg;
  received_msg.buffer = static_cast<uint8_t *>(malloc(256));
  received_msg.buffer_capacity = 256;
  received_msg.allocator = rcutils_get_default_allocator();

  bool taken = false;
  ret = rmw_take_serialized_message(sub2, &received_msg, &taken, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "take in context2");
  TEST_ASSERT(taken == false, "message NOT received (contexts are isolated)");

  free(received_msg.buffer);

  // Cleanup
  rmw_destroy_publisher(node1, pub1);
  rmw_destroy_subscription(node2, sub2);
  rmw_destroy_node(node1);
  rmw_destroy_node(node2);
  rmw_shutdown(&context1);
  rmw_shutdown(&context2);
  rmw_context_fini(&context1);
  rmw_context_fini(&context2);
  rmw_init_options_fini(&init_options1);
  rmw_init_options_fini(&init_options2);

  return true;
}

//=============================================================================
// Main
//=============================================================================
int main()
{
  fprintf(stdout, "=== rmw_mock Level 2 Acceptance Test ===\n");
  fprintf(stdout, "Implementation: %s\n", rmw_get_implementation_identifier());

  RUN_TEST(test_publisher_lifecycle);
  RUN_TEST(test_subscription_lifecycle);
  RUN_TEST(test_serialized_pubsub);
  RUN_TEST(test_serialized_pubsub_with_info);
  RUN_TEST(test_matched_counts);
  RUN_TEST(test_wait_requires_context);
  RUN_TEST(test_typed_publish_unsupported);
  RUN_TEST(test_fifo_overflow);
  RUN_TEST(test_context_isolation);

  fprintf(stdout, "\n=== Summary ===\n");
  fprintf(stdout, "Passed: %d/%d\n", g_pass_count, g_test_count);

  if (g_pass_count == g_test_count) {
    fprintf(stdout, "\n[SUCCESS] All Level 2 tests passed!\n");
    return 0;
  } else {
    fprintf(stderr, "\n[FAILURE] Some tests failed.\n");
    return 1;
  }
}
