// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 3 Acceptance Test: Executor/Wait
// Tests: wait_set, guard_condition, rmw_wait with condvar

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <thread>
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
// Test: Wait set lifecycle
//=============================================================================
static bool test_wait_set_lifecycle()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  // Create wait set
  rmw_wait_set_t * wait_set = rmw_create_wait_set(&context, 10);
  TEST_ASSERT(wait_set != nullptr, "rmw_create_wait_set");
  TEST_ASSERT(rmw_mock::check_identifier(wait_set->implementation_identifier),
    "wait_set identifier");

  // Destroy wait set
  ret = rmw_destroy_wait_set(wait_set);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_destroy_wait_set");

  // Cleanup
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: Guard condition lifecycle
//=============================================================================
static bool test_guard_condition_lifecycle()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  // Create guard condition
  rmw_guard_condition_t * gc = rmw_create_guard_condition(&context);
  TEST_ASSERT(gc != nullptr, "rmw_create_guard_condition");
  TEST_ASSERT(rmw_mock::check_identifier(gc->implementation_identifier),
    "guard_condition identifier");

  // Trigger guard condition
  ret = rmw_trigger_guard_condition(gc);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_trigger_guard_condition");

  // Destroy guard condition
  ret = rmw_destroy_guard_condition(gc);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_destroy_guard_condition");

  // Cleanup
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: rmw_wait with zero timeout (non-blocking)
//=============================================================================
static bool test_wait_zero_timeout()
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

  // Create wait set
  rmw_wait_set_t * wait_set = rmw_create_wait_set(&context, 10);
  TEST_ASSERT(wait_set != nullptr, "rmw_create_wait_set");

  // Create subscription (no messages yet)
  rmw_qos_profile_t qos = rmw_qos_profile_default;
  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription");

  // Prepare wait arrays
  void * subscriptions_array[1] = { sub };
  rmw_subscriptions_t subscriptions;
  subscriptions.subscribers = subscriptions_array;
  subscriptions.subscriber_count = 1;

  // Zero timeout - should return immediately with TIMEOUT
  rmw_time_t timeout = { 0, 0 };
  ret = rmw_wait(&subscriptions, nullptr, nullptr, nullptr, nullptr, wait_set, &timeout);
  TEST_ASSERT(ret == RMW_RET_TIMEOUT, "rmw_wait returns TIMEOUT with no data");

  // Subscription should be set to nullptr (not ready)
  TEST_ASSERT(subscriptions_array[0] == nullptr, "subscription filtered out (not ready)");

  // Cleanup
  rmw_destroy_subscription(node, sub);
  rmw_destroy_wait_set(wait_set);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: rmw_wait wakes on subscription data
//=============================================================================
static bool test_wait_subscription_wake()
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

  rmw_wait_set_t * wait_set = rmw_create_wait_set(&context, 10);
  TEST_ASSERT(wait_set != nullptr, "rmw_create_wait_set");

  rmw_qos_profile_t qos = rmw_qos_profile_default;

  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription");

  rmw_publisher_t * pub = rmw_create_publisher(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(pub != nullptr, "rmw_create_publisher");

  // Atomic flag for thread synchronization
  std::atomic<bool> wait_started{false};
  std::atomic<bool> wait_finished{false};
  std::atomic<rmw_ret_t> wait_result{RMW_RET_ERROR};

  // Start wait thread
  std::thread wait_thread([&]() {
    void * subscriptions_array[1] = { sub };
    rmw_subscriptions_t subscriptions;
    subscriptions.subscribers = subscriptions_array;
    subscriptions.subscriber_count = 1;

    // Wait with 2 second timeout
    rmw_time_t timeout = { 2, 0 };
    wait_started.store(true);
    wait_result.store(rmw_wait(&subscriptions, nullptr, nullptr, nullptr, nullptr, wait_set, &timeout));
    wait_finished.store(true);
  });

  // Wait for wait thread to start
  while (!wait_started.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // Small delay to ensure wait is blocked
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Publish a message (should wake the wait)
  const char * test_data = "wake up!";
  rmw_serialized_message_t serialized_msg;
  serialized_msg.buffer = reinterpret_cast<uint8_t *>(const_cast<char *>(test_data));
  serialized_msg.buffer_length = strlen(test_data) + 1;
  serialized_msg.buffer_capacity = serialized_msg.buffer_length;
  serialized_msg.allocator = rcutils_get_default_allocator();

  ret = rmw_publish_serialized_message(pub, &serialized_msg, nullptr);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_publish_serialized_message");

  // Wait for wait thread to finish
  wait_thread.join();

  TEST_ASSERT(wait_finished.load(), "wait thread finished");
  TEST_ASSERT(wait_result.load() == RMW_RET_OK, "rmw_wait returned OK (woken by message)");

  // Cleanup
  rmw_destroy_publisher(node, pub);
  rmw_destroy_subscription(node, sub);
  rmw_destroy_wait_set(wait_set);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: rmw_wait wakes on guard condition trigger
//=============================================================================
static bool test_wait_guard_condition_wake()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  rmw_wait_set_t * wait_set = rmw_create_wait_set(&context, 10);
  TEST_ASSERT(wait_set != nullptr, "rmw_create_wait_set");

  rmw_guard_condition_t * gc = rmw_create_guard_condition(&context);
  TEST_ASSERT(gc != nullptr, "rmw_create_guard_condition");

  // Atomic flag for thread synchronization
  std::atomic<bool> wait_started{false};
  std::atomic<bool> wait_finished{false};
  std::atomic<rmw_ret_t> wait_result{RMW_RET_ERROR};

  // Start wait thread
  std::thread wait_thread([&]() {
    void * gc_array[1] = { gc };
    rmw_guard_conditions_t guard_conditions;
    guard_conditions.guard_conditions = gc_array;
    guard_conditions.guard_condition_count = 1;

    // Wait with 2 second timeout
    rmw_time_t timeout = { 2, 0 };
    wait_started.store(true);
    wait_result.store(rmw_wait(nullptr, &guard_conditions, nullptr, nullptr, nullptr, wait_set, &timeout));
    wait_finished.store(true);
  });

  // Wait for wait thread to start
  while (!wait_started.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // Small delay to ensure wait is blocked
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Trigger guard condition (should wake the wait)
  ret = rmw_trigger_guard_condition(gc);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_trigger_guard_condition");

  // Wait for wait thread to finish
  wait_thread.join();

  TEST_ASSERT(wait_finished.load(), "wait thread finished");
  TEST_ASSERT(wait_result.load() == RMW_RET_OK, "rmw_wait returned OK (woken by trigger)");

  // Cleanup
  rmw_destroy_guard_condition(gc);
  rmw_destroy_wait_set(wait_set);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: rmw_wait timeout
//=============================================================================
static bool test_wait_timeout()
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

  rmw_wait_set_t * wait_set = rmw_create_wait_set(&context, 10);
  TEST_ASSERT(wait_set != nullptr, "rmw_create_wait_set");

  rmw_qos_profile_t qos = rmw_qos_profile_default;
  rmw_subscription_t * sub = rmw_create_subscription(
    node, nullptr, "/test_topic", &qos, nullptr);
  TEST_ASSERT(sub != nullptr, "rmw_create_subscription");

  // Prepare wait arrays
  void * subscriptions_array[1] = { sub };
  rmw_subscriptions_t subscriptions;
  subscriptions.subscribers = subscriptions_array;
  subscriptions.subscriber_count = 1;

  // Short timeout (100ms) - should timeout since no data
  rmw_time_t timeout = { 0, 100000000 };  // 100ms

  auto start = std::chrono::steady_clock::now();
  ret = rmw_wait(&subscriptions, nullptr, nullptr, nullptr, nullptr, wait_set, &timeout);
  auto end = std::chrono::steady_clock::now();

  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  TEST_ASSERT(ret == RMW_RET_TIMEOUT, "rmw_wait returns TIMEOUT");
  TEST_ASSERT(elapsed_ms >= 90, "waited at least 90ms");  // Allow some tolerance
  TEST_ASSERT(elapsed_ms < 500, "waited less than 500ms");  // Should be close to 100ms

  // Cleanup
  rmw_destroy_subscription(node, sub);
  rmw_destroy_wait_set(wait_set);
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: Guard condition trigger is consumed
//=============================================================================
static bool test_guard_condition_consumed()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  rmw_wait_set_t * wait_set = rmw_create_wait_set(&context, 10);
  TEST_ASSERT(wait_set != nullptr, "rmw_create_wait_set");

  rmw_guard_condition_t * gc = rmw_create_guard_condition(&context);
  TEST_ASSERT(gc != nullptr, "rmw_create_guard_condition");

  // Trigger guard condition
  ret = rmw_trigger_guard_condition(gc);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_trigger_guard_condition");

  // First wait - should return immediately (guard condition triggered)
  void * gc_array[1] = { gc };
  rmw_guard_conditions_t guard_conditions;
  guard_conditions.guard_conditions = gc_array;
  guard_conditions.guard_condition_count = 1;

  rmw_time_t timeout = { 0, 0 };  // Zero timeout
  ret = rmw_wait(nullptr, &guard_conditions, nullptr, nullptr, nullptr, wait_set, &timeout);
  TEST_ASSERT(ret == RMW_RET_OK, "first wait returns OK (triggered)");
  TEST_ASSERT(gc_array[0] != nullptr, "guard condition is ready");

  // Second wait - should timeout (trigger was consumed)
  gc_array[0] = gc;  // Reset array
  ret = rmw_wait(nullptr, &guard_conditions, nullptr, nullptr, nullptr, wait_set, &timeout);
  TEST_ASSERT(ret == RMW_RET_TIMEOUT, "second wait returns TIMEOUT (consumed)");
  TEST_ASSERT(gc_array[0] == nullptr, "guard condition not ready (consumed)");

  // Cleanup
  rmw_destroy_guard_condition(gc);
  rmw_destroy_wait_set(wait_set);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Test: Array filtering - services/clients/events set to nullptr
//=============================================================================
static bool test_array_filtering()
{
  // Initialize context
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&init_options, rcutils_get_default_allocator());
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init");

  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&init_options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init");

  rmw_wait_set_t * wait_set = rmw_create_wait_set(&context, 10);
  TEST_ASSERT(wait_set != nullptr, "rmw_create_wait_set");

  // Create dummy pointers (not real services/clients, just for testing filtering)
  int dummy1 = 1, dummy2 = 2, dummy3 = 3;
  void * services_array[1] = { &dummy1 };
  void * clients_array[1] = { &dummy2 };
  void * events_array[1] = { &dummy3 };

  rmw_services_t services;
  services.services = services_array;
  services.service_count = 1;

  rmw_clients_t clients;
  clients.clients = clients_array;
  clients.client_count = 1;

  rmw_events_t events;
  events.events = events_array;
  events.event_count = 1;

  // Wait with zero timeout
  rmw_time_t timeout = { 0, 0 };
  ret = rmw_wait(nullptr, nullptr, &services, &clients, &events, wait_set, &timeout);
  TEST_ASSERT(ret == RMW_RET_TIMEOUT, "rmw_wait returns TIMEOUT");

  // All unsupported arrays should be set to nullptr
  TEST_ASSERT(services_array[0] == nullptr, "service filtered to nullptr");
  TEST_ASSERT(clients_array[0] == nullptr, "client filtered to nullptr");
  TEST_ASSERT(events_array[0] == nullptr, "event filtered to nullptr");

  // Cleanup
  rmw_destroy_wait_set(wait_set);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&init_options);

  return true;
}

//=============================================================================
// Main
//=============================================================================
int main()
{
  fprintf(stdout, "=== rmw_mock Level 3 Acceptance Test ===\n");
  fprintf(stdout, "Implementation: %s\n", rmw_get_implementation_identifier());

  RUN_TEST(test_wait_set_lifecycle);
  RUN_TEST(test_guard_condition_lifecycle);
  RUN_TEST(test_wait_zero_timeout);
  RUN_TEST(test_wait_subscription_wake);
  RUN_TEST(test_wait_guard_condition_wake);
  RUN_TEST(test_wait_timeout);
  RUN_TEST(test_guard_condition_consumed);
  RUN_TEST(test_array_filtering);

  fprintf(stdout, "\n=== Summary ===\n");
  fprintf(stdout, "Passed: %d/%d\n", g_pass_count, g_test_count);

  if (g_pass_count == g_test_count) {
    fprintf(stdout, "\n[SUCCESS] All Level 3 tests passed!\n");
    fprintf(stdout, "rmw_mock is now semantically complete.\n");
    fprintf(stdout, "rclcpp::spin() can block and wake on messages/guard conditions.\n");
    return 0;
  } else {
    fprintf(stderr, "\n[FAILURE] Some tests failed.\n");
    return 1;
  }
}
