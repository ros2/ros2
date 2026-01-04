// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 2: Publisher implementation - serialized message publish only

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

extern "C" {

//=============================================================================
// rmw_create_publisher
//=============================================================================
RMW_MOCK_PUBLIC
rmw_publisher_t *
rmw_create_publisher(
  const rmw_node_t * node,
  const rosidl_message_type_support_t * type_support,
  const char * topic_name,
  const rmw_qos_profile_t * qos_policies,
  const rmw_publisher_options_t * publisher_options)
{
  (void)type_support;
  (void)publisher_options;

  if (!node || !topic_name || !qos_policies) {
    RMW_SET_ERROR_MSG("invalid argument");
    return nullptr;
  }

  if (!rmw_mock::check_identifier(node->implementation_identifier)) {
    RMW_SET_ERROR_MSG("node implementation mismatch");
    return nullptr;
  }

  auto * node_impl = static_cast<rmw_mock::NodeImpl *>(node->data);
  if (!node_impl || !node_impl->context) {
    RMW_SET_ERROR_MSG("invalid node data");
    return nullptr;
  }

  // Allocate publisher
  auto * publisher = new (std::nothrow) rmw_publisher_t;
  if (!publisher) {
    RMW_SET_ERROR_MSG("failed to allocate publisher");
    return nullptr;
  }

  // Allocate implementation data
  auto * pub_impl = new (std::nothrow) rmw_mock::PublisherImpl;
  if (!pub_impl) {
    delete publisher;
    RMW_SET_ERROR_MSG("failed to allocate publisher impl");
    return nullptr;
  }

  // Initialize implementation data
  pub_impl->topic_name = topic_name;
  pub_impl->qos = *qos_policies;
  pub_impl->node = node_impl;
  pub_impl->context = node_impl->context;
  pub_impl->sequence_number.store(0);

  // Generate unique GID
  pub_impl->gid = node_impl->context->generate_gid();

  // Register with router
  node_impl->context->router.register_publisher(topic_name, pub_impl);

  // Duplicate topic_name string (avoid dangling pointer to impl's string)
  char * topic_name_dup = strdup(topic_name);
  if (!topic_name_dup) {
    node_impl->context->router.unregister_publisher(pub_impl);
    delete pub_impl;
    delete publisher;
    RMW_SET_ERROR_MSG("failed to duplicate topic_name");
    return nullptr;
  }

  // Initialize rmw_publisher_t
  publisher->implementation_identifier = rmw_mock::RMW_MOCK_IDENTIFIER;
  publisher->data = pub_impl;
  publisher->topic_name = topic_name_dup;  // Owned by publisher, freed in destroy
  publisher->options = publisher_options ? *publisher_options : rmw_get_default_publisher_options();
  publisher->can_loan_messages = false;

  return publisher;
}

//=============================================================================
// rmw_destroy_publisher
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_destroy_publisher(rmw_node_t * node, rmw_publisher_t * publisher)
{
  if (!node || !publisher) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(publisher->implementation_identifier)) {
    RMW_SET_ERROR_MSG("publisher implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * pub_impl = static_cast<rmw_mock::PublisherImpl *>(publisher->data);
  if (pub_impl) {
    // Unregister from router
    if (pub_impl->context) {
      pub_impl->context->router.unregister_publisher(pub_impl);
    }
    delete pub_impl;
  }

  // Free topic_name string (allocated in create)
  std::free(const_cast<char *>(publisher->topic_name));

  delete publisher;
  return RMW_RET_OK;
}

//=============================================================================
// rmw_publish (typed - NOT supported in Level 2, use serialized)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publish(
  const rmw_publisher_t * publisher,
  const void * ros_message,
  rmw_publisher_allocation_t * allocation)
{
  (void)publisher;
  (void)ros_message;
  (void)allocation;

  // Level 2: Only serialized message APIs are supported
  // Typed publish requires serialization which is out of scope for mock
  RMW_SET_ERROR_MSG("rmw_publish not supported in rmw_mock; use rmw_publish_serialized_message");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_publish_serialized_message
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publish_serialized_message(
  const rmw_publisher_t * publisher,
  const rmw_serialized_message_t * serialized_message,
  rmw_publisher_allocation_t * allocation)
{
  (void)allocation;

  if (!publisher || !serialized_message) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(publisher->implementation_identifier)) {
    RMW_SET_ERROR_MSG("publisher implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * pub_impl = static_cast<rmw_mock::PublisherImpl *>(publisher->data);
  if (!pub_impl || !pub_impl->context) {
    RMW_SET_ERROR_MSG("invalid publisher data");
    return RMW_RET_ERROR;
  }

  // Copy serialized data
  std::vector<uint8_t> data(
    serialized_message->buffer,
    serialized_message->buffer + serialized_message->buffer_length);

  // Get timestamp
  int64_t ts = rmw_mock::now_ns();

  // Route through MockRouter
  bool ok = pub_impl->context->router.publish(
    pub_impl->topic_name,
    std::move(data),
    pub_impl->gid,
    ts);

  return ok ? RMW_RET_OK : RMW_RET_ERROR;
}

//=============================================================================
// rmw_publish_loaned_message (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publish_loaned_message(
  const rmw_publisher_t * publisher,
  void * ros_message,
  rmw_publisher_allocation_t * allocation)
{
  (void)publisher;
  (void)ros_message;
  (void)allocation;

  RMW_SET_ERROR_MSG("loaned messages not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_borrow_loaned_message (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_borrow_loaned_message(
  const rmw_publisher_t * publisher,
  const rosidl_message_type_support_t * type_support,
  void ** ros_message)
{
  (void)publisher;
  (void)type_support;
  (void)ros_message;

  RMW_SET_ERROR_MSG("loaned messages not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_return_loaned_message_from_publisher (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_return_loaned_message_from_publisher(
  const rmw_publisher_t * publisher,
  void * loaned_message)
{
  (void)publisher;
  (void)loaned_message;

  RMW_SET_ERROR_MSG("loaned messages not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_publisher_count_matched_subscriptions
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publisher_count_matched_subscriptions(
  const rmw_publisher_t * publisher,
  size_t * subscription_count)
{
  if (!publisher || !subscription_count) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(publisher->implementation_identifier)) {
    RMW_SET_ERROR_MSG("publisher implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * pub_impl = static_cast<rmw_mock::PublisherImpl *>(publisher->data);
  if (!pub_impl || !pub_impl->context) {
    RMW_SET_ERROR_MSG("invalid publisher data");
    return RMW_RET_ERROR;
  }

  *subscription_count = pub_impl->context->router.count_subscriptions(pub_impl->topic_name);
  return RMW_RET_OK;
}

//=============================================================================
// rmw_publisher_get_actual_qos
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publisher_get_actual_qos(
  const rmw_publisher_t * publisher,
  rmw_qos_profile_t * qos)
{
  if (!publisher || !qos) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(publisher->implementation_identifier)) {
    RMW_SET_ERROR_MSG("publisher implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * pub_impl = static_cast<rmw_mock::PublisherImpl *>(publisher->data);
  if (!pub_impl) {
    RMW_SET_ERROR_MSG("invalid publisher data");
    return RMW_RET_ERROR;
  }

  *qos = pub_impl->qos;
  return RMW_RET_OK;
}

//=============================================================================
// rmw_get_gid_for_publisher
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_get_gid_for_publisher(
  const rmw_publisher_t * publisher,
  rmw_gid_t * gid)
{
  if (!publisher || !gid) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(publisher->implementation_identifier)) {
    RMW_SET_ERROR_MSG("publisher implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * pub_impl = static_cast<rmw_mock::PublisherImpl *>(publisher->data);
  if (!pub_impl) {
    RMW_SET_ERROR_MSG("invalid publisher data");
    return RMW_RET_ERROR;
  }

  *gid = pub_impl->gid;
  return RMW_RET_OK;
}

//=============================================================================
// rmw_publisher_assert_liveliness (stub - always succeeds)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publisher_assert_liveliness(const rmw_publisher_t * publisher)
{
  if (!publisher) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(publisher->implementation_identifier)) {
    RMW_SET_ERROR_MSG("publisher implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  // Mock: always succeeds
  return RMW_RET_OK;
}

//=============================================================================
// rmw_publisher_wait_for_all_acked (stub - always succeeds)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publisher_wait_for_all_acked(
  const rmw_publisher_t * publisher,
  rmw_time_t wait_timeout)
{
  (void)wait_timeout;

  if (!publisher) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(publisher->implementation_identifier)) {
    RMW_SET_ERROR_MSG("publisher implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  // Mock: immediate delivery, always acked
  return RMW_RET_OK;
}

}  // extern "C"
