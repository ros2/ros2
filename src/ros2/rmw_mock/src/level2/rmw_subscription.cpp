// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 2: Subscription implementation - serialized message take only (polling)

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

extern "C" {

//=============================================================================
// rmw_create_subscription
//=============================================================================
RMW_MOCK_PUBLIC
rmw_subscription_t *
rmw_create_subscription(
  const rmw_node_t * node,
  const rosidl_message_type_support_t * type_support,
  const char * topic_name,
  const rmw_qos_profile_t * qos_policies,
  const rmw_subscription_options_t * subscription_options)
{
  (void)type_support;
  (void)subscription_options;

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

  // Allocate subscription
  auto * subscription = new (std::nothrow) rmw_subscription_t;
  if (!subscription) {
    RMW_SET_ERROR_MSG("failed to allocate subscription");
    return nullptr;
  }

  // Allocate implementation data
  auto * sub_impl = new (std::nothrow) rmw_mock::SubscriptionImpl;
  if (!sub_impl) {
    delete subscription;
    RMW_SET_ERROR_MSG("failed to allocate subscription impl");
    return nullptr;
  }

  // Initialize implementation data
  sub_impl->topic_name = topic_name;
  sub_impl->qos = *qos_policies;
  sub_impl->node = node_impl;
  sub_impl->context = node_impl->context;

  // Set queue depth from QoS (default 10)
  if (qos_policies->depth > 0 && qos_policies->depth < 1000) {
    sub_impl->queue_depth = qos_policies->depth;
  } else {
    sub_impl->queue_depth = 10;
  }

  // Generate unique GID
  sub_impl->gid = node_impl->context->generate_gid();

  // Register with router
  node_impl->context->router.register_subscription(topic_name, sub_impl);

  // Duplicate topic_name string (avoid dangling pointer to impl's string)
  char * topic_name_dup = strdup(topic_name);
  if (!topic_name_dup) {
    node_impl->context->router.unregister_subscription(sub_impl);
    delete sub_impl;
    delete subscription;
    RMW_SET_ERROR_MSG("failed to duplicate topic_name");
    return nullptr;
  }

  // Initialize rmw_subscription_t
  subscription->implementation_identifier = rmw_mock::RMW_MOCK_IDENTIFIER;
  subscription->data = sub_impl;
  subscription->topic_name = topic_name_dup;  // Owned by subscription, freed in destroy
  subscription->options = subscription_options ?
    *subscription_options : rmw_get_default_subscription_options();
  subscription->can_loan_messages = false;
  subscription->is_cft_enabled = false;

  return subscription;
}

//=============================================================================
// rmw_destroy_subscription
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_destroy_subscription(rmw_node_t * node, rmw_subscription_t * subscription)
{
  if (!node || !subscription) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(subscription->implementation_identifier)) {
    RMW_SET_ERROR_MSG("subscription implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * sub_impl = static_cast<rmw_mock::SubscriptionImpl *>(subscription->data);
  if (sub_impl) {
    // Unregister from router
    if (sub_impl->context) {
      sub_impl->context->router.unregister_subscription(sub_impl);
    }
    delete sub_impl;
  }

  // Free topic_name string (allocated in create)
  std::free(const_cast<char *>(subscription->topic_name));

  delete subscription;
  return RMW_RET_OK;
}

//=============================================================================
// rmw_take (typed - NOT supported in Level 2)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take(
  const rmw_subscription_t * subscription,
  void * ros_message,
  bool * taken,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)ros_message;
  (void)taken;
  (void)allocation;

  RMW_SET_ERROR_MSG("rmw_take not supported in rmw_mock; use rmw_take_serialized_message");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_take_with_info (typed - NOT supported in Level 2)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_with_info(
  const rmw_subscription_t * subscription,
  void * ros_message,
  bool * taken,
  rmw_message_info_t * message_info,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)ros_message;
  (void)taken;
  (void)message_info;
  (void)allocation;

  RMW_SET_ERROR_MSG("rmw_take_with_info not supported; use rmw_take_serialized_message_with_info");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_take_serialized_message
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_serialized_message(
  const rmw_subscription_t * subscription,
  rmw_serialized_message_t * serialized_message,
  bool * taken,
  rmw_subscription_allocation_t * allocation)
{
  (void)allocation;

  if (!subscription || !serialized_message || !taken) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(subscription->implementation_identifier)) {
    RMW_SET_ERROR_MSG("subscription implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * sub_impl = static_cast<rmw_mock::SubscriptionImpl *>(subscription->data);
  if (!sub_impl) {
    RMW_SET_ERROR_MSG("invalid subscription data");
    return RMW_RET_ERROR;
  }

  // Try to take message from queue
  std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

  if (sub_impl->message_queue.empty()) {
    *taken = false;
    return RMW_RET_OK;
  }

  // Pop front message
  rmw_mock::MessageItem & item = sub_impl->message_queue.front();

  // Ensure buffer capacity
  if (serialized_message->buffer_capacity < item.data.size()) {
    rmw_ret_t ret = rmw_serialized_message_resize(serialized_message, item.data.size());
    if (ret != RMW_RET_OK) {
      return ret;
    }
  }

  // Copy data
  std::memcpy(serialized_message->buffer, item.data.data(), item.data.size());
  serialized_message->buffer_length = item.data.size();

  // Remove from queue
  sub_impl->message_queue.pop();
  *taken = true;

  return RMW_RET_OK;
}

//=============================================================================
// rmw_take_serialized_message_with_info
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_serialized_message_with_info(
  const rmw_subscription_t * subscription,
  rmw_serialized_message_t * serialized_message,
  bool * taken,
  rmw_message_info_t * message_info,
  rmw_subscription_allocation_t * allocation)
{
  (void)allocation;

  if (!subscription || !serialized_message || !taken || !message_info) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(subscription->implementation_identifier)) {
    RMW_SET_ERROR_MSG("subscription implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * sub_impl = static_cast<rmw_mock::SubscriptionImpl *>(subscription->data);
  if (!sub_impl) {
    RMW_SET_ERROR_MSG("invalid subscription data");
    return RMW_RET_ERROR;
  }

  // Try to take message from queue
  std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

  if (sub_impl->message_queue.empty()) {
    *taken = false;
    return RMW_RET_OK;
  }

  // Pop front message
  rmw_mock::MessageItem & item = sub_impl->message_queue.front();

  // Ensure buffer capacity
  if (serialized_message->buffer_capacity < item.data.size()) {
    rmw_ret_t ret = rmw_serialized_message_resize(serialized_message, item.data.size());
    if (ret != RMW_RET_OK) {
      return ret;
    }
  }

  // Copy data
  std::memcpy(serialized_message->buffer, item.data.data(), item.data.size());
  serialized_message->buffer_length = item.data.size();

  // Fill message info
  message_info->source_timestamp = item.timestamp_ns;
  message_info->received_timestamp = rmw_mock::now_ns();
  message_info->publication_sequence_number = item.sequence_number;
  message_info->reception_sequence_number = item.sequence_number;
  message_info->publisher_gid = item.publisher_gid;
  message_info->from_intra_process = true;  // Mock is always in-process

  // Remove from queue
  sub_impl->message_queue.pop();
  *taken = true;

  return RMW_RET_OK;
}

//=============================================================================
// rmw_take_loaned_message (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_loaned_message(
  const rmw_subscription_t * subscription,
  void ** loaned_message,
  bool * taken,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)loaned_message;
  (void)taken;
  (void)allocation;

  RMW_SET_ERROR_MSG("loaned messages not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_take_loaned_message_with_info (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_loaned_message_with_info(
  const rmw_subscription_t * subscription,
  void ** loaned_message,
  bool * taken,
  rmw_message_info_t * message_info,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)loaned_message;
  (void)taken;
  (void)message_info;
  (void)allocation;

  RMW_SET_ERROR_MSG("loaned messages not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_return_loaned_message_from_subscription (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_return_loaned_message_from_subscription(
  const rmw_subscription_t * subscription,
  void * loaned_message)
{
  (void)subscription;
  (void)loaned_message;

  RMW_SET_ERROR_MSG("loaned messages not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_subscription_count_matched_publishers
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_subscription_count_matched_publishers(
  const rmw_subscription_t * subscription,
  size_t * publisher_count)
{
  if (!subscription || !publisher_count) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(subscription->implementation_identifier)) {
    RMW_SET_ERROR_MSG("subscription implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * sub_impl = static_cast<rmw_mock::SubscriptionImpl *>(subscription->data);
  if (!sub_impl || !sub_impl->context) {
    RMW_SET_ERROR_MSG("invalid subscription data");
    return RMW_RET_ERROR;
  }

  *publisher_count = sub_impl->context->router.count_publishers(sub_impl->topic_name);
  return RMW_RET_OK;
}

//=============================================================================
// rmw_subscription_get_actual_qos
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_subscription_get_actual_qos(
  const rmw_subscription_t * subscription,
  rmw_qos_profile_t * qos)
{
  if (!subscription || !qos) {
    RMW_SET_ERROR_MSG("invalid argument");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(subscription->implementation_identifier)) {
    RMW_SET_ERROR_MSG("subscription implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * sub_impl = static_cast<rmw_mock::SubscriptionImpl *>(subscription->data);
  if (!sub_impl) {
    RMW_SET_ERROR_MSG("invalid subscription data");
    return RMW_RET_ERROR;
  }

  *qos = sub_impl->qos;
  return RMW_RET_OK;
}

//=============================================================================
// rmw_subscription_set_content_filter (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_subscription_set_content_filter(
  rmw_subscription_t * subscription,
  const rmw_subscription_content_filter_options_t * options)
{
  (void)subscription;
  (void)options;

  RMW_SET_ERROR_MSG("content filter not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// rmw_subscription_get_content_filter (NOT supported)
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_subscription_get_content_filter(
  const rmw_subscription_t * subscription,
  rcutils_allocator_t * allocator,
  rmw_subscription_content_filter_options_t * options)
{
  (void)subscription;
  (void)allocator;
  (void)options;

  RMW_SET_ERROR_MSG("content filter not supported");
  return RMW_RET_UNSUPPORTED;
}

}  // extern "C"
