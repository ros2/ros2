// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 1 Acceptance Test: Init/Shutdown/Node lifecycle
//
// Validation criteria:
// 1. rmw_init_options lifecycle (init/copy/fini)
// 2. rmw_context lifecycle (init/shutdown/fini)
// 3. rmw_node lifecycle (create/destroy)
// 4. No memory leaks
// 5. Graph APIs return empty (stub)

#include <cassert>
#include <cstdio>
#include <cstring>

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rcutils/allocator.h"

#define TEST_ASSERT(cond, msg) \
  do { \
    if (!(cond)) { \
      fprintf(stderr, "[FAIL] %s: %s\n", __func__, msg); \
      fprintf(stderr, "  RMW error: %s\n", rmw_get_error_string().str); \
      return 1; \
    } \
  } while (0)

#define TEST_PASS(name) \
  fprintf(stdout, "[PASS] %s\n", name)

//=============================================================================
// Test: Implementation identifier
//=============================================================================
int test_identifier()
{
  const char * id = rmw_get_implementation_identifier();
  TEST_ASSERT(id != nullptr, "identifier is null");
  TEST_ASSERT(strcmp(id, "rmw_mock") == 0, "identifier mismatch");

  const char * fmt = rmw_get_serialization_format();
  TEST_ASSERT(fmt != nullptr, "format is null");
  TEST_ASSERT(strcmp(fmt, "cdr") == 0, "format mismatch");

  TEST_PASS("test_identifier");
  return 0;
}

//=============================================================================
// Test: Init options lifecycle
//=============================================================================
int test_init_options()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  // Initialize
  rmw_init_options_t options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&options, allocator);
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init failed");
  TEST_ASSERT(options.implementation_identifier != nullptr, "identifier not set");

  // Copy
  rmw_init_options_t options_copy = rmw_get_zero_initialized_init_options();
  ret = rmw_init_options_copy(&options, &options_copy);
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_copy failed");

  // Finalize
  ret = rmw_init_options_fini(&options);
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_fini failed");

  ret = rmw_init_options_fini(&options_copy);
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_fini (copy) failed");

  TEST_PASS("test_init_options");
  return 0;
}

//=============================================================================
// Test: Context lifecycle
//=============================================================================
int test_context()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  // Init options
  rmw_init_options_t options = rmw_get_zero_initialized_init_options();
  rmw_ret_t ret = rmw_init_options_init(&options, allocator);
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_init failed");

  // Init context
  rmw_context_t context = rmw_get_zero_initialized_context();
  ret = rmw_init(&options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init failed");
  TEST_ASSERT(context.impl != nullptr, "context.impl is null");
  TEST_ASSERT(context.implementation_identifier != nullptr, "context identifier is null");

  // Shutdown
  ret = rmw_shutdown(&context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_shutdown failed");

  // Finalize
  ret = rmw_context_fini(&context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_context_fini failed");
  TEST_ASSERT(context.impl == nullptr, "context.impl not cleared");

  // Cleanup options
  ret = rmw_init_options_fini(&options);
  TEST_ASSERT(ret == RMW_RET_OK, "init_options_fini failed");

  TEST_PASS("test_context");
  return 0;
}

//=============================================================================
// Test: Node lifecycle
//=============================================================================
int test_node()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  // Setup context
  rmw_init_options_t options = rmw_get_zero_initialized_init_options();
  rmw_init_options_init(&options, allocator);

  rmw_context_t context = rmw_get_zero_initialized_context();
  rmw_ret_t ret = rmw_init(&options, &context);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_init failed");

  // Create node
  rmw_node_t * node = rmw_create_node(&context, "test_node", "/test_ns");
  TEST_ASSERT(node != nullptr, "rmw_create_node failed");
  TEST_ASSERT(strcmp(node->name, "test_node") == 0, "node name mismatch");
  TEST_ASSERT(strcmp(node->namespace_, "/test_ns") == 0, "node namespace mismatch");

  // Get graph guard condition (Level 1: should return nullptr)
  const rmw_guard_condition_t * gc = rmw_node_get_graph_guard_condition(node);
  // Level 1: gc == nullptr is expected
  (void)gc;

  // Destroy node
  ret = rmw_destroy_node(node);
  TEST_ASSERT(ret == RMW_RET_OK, "rmw_destroy_node failed");

  // Cleanup
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&options);

  TEST_PASS("test_node");
  return 0;
}

//=============================================================================
// Test: Multiple nodes in same context
//=============================================================================
int test_multiple_nodes()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  // Setup context
  rmw_init_options_t options = rmw_get_zero_initialized_init_options();
  rmw_init_options_init(&options, allocator);

  rmw_context_t context = rmw_get_zero_initialized_context();
  rmw_init(&options, &context);

  // Create multiple nodes
  rmw_node_t * node1 = rmw_create_node(&context, "node1", "/ns1");
  rmw_node_t * node2 = rmw_create_node(&context, "node2", "/ns2");
  rmw_node_t * node3 = rmw_create_node(&context, "node3", "/");

  TEST_ASSERT(node1 != nullptr, "node1 creation failed");
  TEST_ASSERT(node2 != nullptr, "node2 creation failed");
  TEST_ASSERT(node3 != nullptr, "node3 creation failed");

  // Verify isolation
  TEST_ASSERT(node1->data != node2->data, "nodes share same impl");
  TEST_ASSERT(node2->data != node3->data, "nodes share same impl");

  // Destroy in reverse order
  rmw_destroy_node(node3);
  rmw_destroy_node(node2);
  rmw_destroy_node(node1);

  // Cleanup
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&options);

  TEST_PASS("test_multiple_nodes");
  return 0;
}

//=============================================================================
// Test: Graph API stubs
//=============================================================================
int test_graph_stubs()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  // Setup
  rmw_init_options_t options = rmw_get_zero_initialized_init_options();
  rmw_init_options_init(&options, allocator);
  rmw_context_t context = rmw_get_zero_initialized_context();
  rmw_init(&options, &context);
  rmw_node_t * node = rmw_create_node(&context, "graph_test", "/");

  // count_publishers (should return 0)
  size_t count = 999;
  rmw_ret_t ret = rmw_count_publishers(node, "/some_topic", &count);
  TEST_ASSERT(ret == RMW_RET_OK, "count_publishers failed");
  TEST_ASSERT(count == 0, "count_publishers should return 0 in Level 1");

  // count_subscribers (should return 0)
  count = 999;
  ret = rmw_count_subscribers(node, "/some_topic", &count);
  TEST_ASSERT(ret == RMW_RET_OK, "count_subscribers failed");
  TEST_ASSERT(count == 0, "count_subscribers should return 0 in Level 1");

  // get_node_names (should return empty)
  rcutils_string_array_t names = rcutils_get_zero_initialized_string_array();
  rcutils_string_array_t namespaces = rcutils_get_zero_initialized_string_array();
  ret = rmw_get_node_names(node, &names, &namespaces);
  TEST_ASSERT(ret == RMW_RET_OK, "get_node_names failed");
  TEST_ASSERT(names.size == 0, "get_node_names should return empty");

  // Cleanup
  rmw_destroy_node(node);
  rmw_shutdown(&context);
  rmw_context_fini(&context);
  rmw_init_options_fini(&options);

  TEST_PASS("test_graph_stubs");
  return 0;
}

//=============================================================================
// Test: Context isolation (critical for test harness)
//=============================================================================
int test_context_isolation()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  // Create two independent contexts
  rmw_init_options_t options1 = rmw_get_zero_initialized_init_options();
  rmw_init_options_t options2 = rmw_get_zero_initialized_init_options();
  rmw_init_options_init(&options1, allocator);
  rmw_init_options_init(&options2, allocator);

  rmw_context_t context1 = rmw_get_zero_initialized_context();
  rmw_context_t context2 = rmw_get_zero_initialized_context();
  rmw_init(&options1, &context1);
  rmw_init(&options2, &context2);

  // Verify different impl pointers (per-context router)
  TEST_ASSERT(context1.impl != context2.impl, "contexts share same impl (violates isolation)");

  // Create nodes in each context
  rmw_node_t * node1 = rmw_create_node(&context1, "node_ctx1", "/");
  rmw_node_t * node2 = rmw_create_node(&context2, "node_ctx2", "/");
  TEST_ASSERT(node1 != nullptr, "node1 creation failed");
  TEST_ASSERT(node2 != nullptr, "node2 creation failed");

  // Cleanup context1 first
  rmw_destroy_node(node1);
  rmw_shutdown(&context1);
  rmw_context_fini(&context1);
  rmw_init_options_fini(&options1);

  // context2 should still work
  size_t count = 999;
  rmw_ret_t ret = rmw_count_publishers(node2, "/topic", &count);
  TEST_ASSERT(ret == RMW_RET_OK, "context2 should still work after context1 cleanup");

  // Cleanup context2
  rmw_destroy_node(node2);
  rmw_shutdown(&context2);
  rmw_context_fini(&context2);
  rmw_init_options_fini(&options2);

  TEST_PASS("test_context_isolation");
  return 0;
}

//=============================================================================
// Main
//=============================================================================
int main()
{
  fprintf(stdout, "=== rmw_mock Level 1 Acceptance Test ===\n");

  int failures = 0;

  failures += test_identifier();
  failures += test_init_options();
  failures += test_context();
  failures += test_node();
  failures += test_multiple_nodes();
  failures += test_graph_stubs();
  failures += test_context_isolation();

  fprintf(stdout, "=========================================\n");
  if (failures == 0) {
    fprintf(stdout, "[SUCCESS] All Level 1 tests passed!\n");
    return 0;
  } else {
    fprintf(stdout, "[FAILED] %d test(s) failed\n", failures);
    return 1;
  }
}
