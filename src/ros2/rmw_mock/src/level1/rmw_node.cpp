// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// rmw_mock: Node management APIs
// Level 1: Foundation/Smoke

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/validate_node_name.h"
#include "rmw/validate_namespace.h"

#include <cstdlib>
#include <cstring>

extern "C" {

RMW_MOCK_PUBLIC
rmw_node_t * rmw_create_node(
  rmw_context_t * context,
  const char * name,
  const char * namespace_)
{
  // Validate context
  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return nullptr;
  }
  if (!rmw_mock::check_identifier(context->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return nullptr;
  }

  auto * mock_context = reinterpret_cast<rmw_mock::MockContext *>(context->impl);
  if (!mock_context) {
    RMW_SET_ERROR_MSG("context impl is null");
    return nullptr;
  }
  if (mock_context->is_shutdown.load()) {
    RMW_SET_ERROR_MSG("context is shutdown");
    return nullptr;
  }

  // Validate node name
  if (!name || strlen(name) == 0) {
    RMW_SET_ERROR_MSG("node name is null or empty");
    return nullptr;
  }

  // Validate namespace
  if (!namespace_ || strlen(namespace_) == 0) {
    RMW_SET_ERROR_MSG("namespace is null or empty");
    return nullptr;
  }

  // Allocate node implementation
  auto * node_impl = new (std::nothrow) rmw_mock::NodeImpl();
  if (!node_impl) {
    RMW_SET_ERROR_MSG("failed to allocate NodeImpl");
    return nullptr;
  }

  node_impl->name = name;
  node_impl->namespace_ = namespace_;
  node_impl->context = mock_context;
  node_impl->graph_guard_condition = nullptr;  // Level 3

  // Allocate rmw_node_t
  auto * node = static_cast<rmw_node_t *>(std::malloc(sizeof(rmw_node_t)));
  if (!node) {
    delete node_impl;
    RMW_SET_ERROR_MSG("failed to allocate rmw_node_t");
    return nullptr;
  }

  // Duplicate strings for node
  node->name = strdup(name);
  node->namespace_ = strdup(namespace_);
  if (!node->name || !node->namespace_) {
    std::free(const_cast<char *>(node->name));
    std::free(const_cast<char *>(node->namespace_));
    std::free(node);
    delete node_impl;
    RMW_SET_ERROR_MSG("failed to duplicate node name/namespace");
    return nullptr;
  }

  node->implementation_identifier = rmw_mock::RMW_MOCK_IDENTIFIER;
  node->data = node_impl;
  node->context = context;

  return node;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_destroy_node(rmw_node_t * node)
{
  if (!node) {
    RMW_SET_ERROR_MSG("node is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(node->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * node_impl = static_cast<rmw_mock::NodeImpl *>(node->data);

  // Free node strings
  std::free(const_cast<char *>(node->name));
  std::free(const_cast<char *>(node->namespace_));

  // Free node implementation
  delete node_impl;

  // Free node
  std::free(node);

  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
const rmw_guard_condition_t * rmw_node_get_graph_guard_condition(const rmw_node_t * node)
{
  if (!node) {
    RMW_SET_ERROR_MSG("node is null");
    return nullptr;
  }
  if (!rmw_mock::check_identifier(node->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return nullptr;
  }

  // Level 1: Return nullptr (graph guard condition not implemented)
  // Level 3: Return actual guard condition for graph changes
  auto * node_impl = static_cast<rmw_mock::NodeImpl *>(node->data);
  return node_impl ? node_impl->graph_guard_condition : nullptr;
}

//=============================================================================
// Graph API stubs (Level 1: return empty/zero)
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t rmw_count_publishers(
  const rmw_node_t * node,
  const char * topic_name,
  size_t * count)
{
  if (!node || !topic_name || !count) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(node->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  // Level 1: Return 0 (stub)
  // Level 2+: Query MockRouter
  *count = 0;
  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_count_subscribers(
  const rmw_node_t * node,
  const char * topic_name,
  size_t * count)
{
  if (!node || !topic_name || !count) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(node->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  // Level 1: Return 0 (stub)
  *count = 0;
  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_get_node_names(
  const rmw_node_t * node,
  rcutils_string_array_t * node_names,
  rcutils_string_array_t * node_namespaces)
{
  if (!node || !node_names || !node_namespaces) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(node->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  // Level 1: Return empty arrays (stub)
  node_names->size = 0;
  node_names->data = nullptr;
  node_namespaces->size = 0;
  node_namespaces->data = nullptr;

  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_get_node_names_with_enclaves(
  const rmw_node_t * node,
  rcutils_string_array_t * node_names,
  rcutils_string_array_t * node_namespaces,
  rcutils_string_array_t * enclaves)
{
  if (!node || !node_names || !node_namespaces || !enclaves) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(node->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  // Level 1: Return empty arrays (stub)
  node_names->size = 0;
  node_names->data = nullptr;
  node_namespaces->size = 0;
  node_namespaces->data = nullptr;
  enclaves->size = 0;
  enclaves->data = nullptr;

  return RMW_RET_OK;
}

}  // extern "C"
