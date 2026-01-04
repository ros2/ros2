// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// MockRouter implementation - message routing with Level 3 wake support

#include "rmw_mock/types.h"

#include <algorithm>
#include <chrono>

namespace rmw_mock {

//=============================================================================
// now_ns(): Get current timestamp in nanoseconds (monotonic clock)
//=============================================================================
int64_t now_ns()
{
  auto now = std::chrono::steady_clock::now();
  auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
    now.time_since_epoch());
  return ns.count();
}

//=============================================================================
// MockRouter::publish - Route message to all matching subscriptions
//=============================================================================
bool MockRouter::publish(
  const std::string & topic_name,
  std::vector<uint8_t> && serialized_data,
  const rmw_gid_t & publisher_gid,
  int64_t timestamp_ns)
{
  // Snapshot subscription pointers under lock (reduces lock contention)
  std::vector<SubscriptionImpl *> subs_snapshot;
  {
    std::lock_guard<std::mutex> lock(subscriptions_mutex);
    auto it = topic_to_subscriptions.find(topic_name);
    if (it == topic_to_subscriptions.end() || it->second.empty()) {
      // No subscribers - message dropped (valid behavior)
      return true;
    }
    subs_snapshot = it->second;  // Copy pointers
  }
  // subscriptions_mutex released here

  // Get next global sequence number
  uint64_t seq = sequence_counter.fetch_add(1);

  // Create message item
  MessageItem item(
    std::move(serialized_data),
    timestamp_ns,
    seq,
    publisher_gid);

  // Deliver to all matching subscriptions (lock-free iteration on snapshot)
  // Note: If a subscription is destroyed between snapshot and here,
  // unregister_subscription will wait until this publish completes
  // due to queue_mutex ordering. Safe as long as destroy unregisters first.
  bool delivered = false;
  MockContext * ctx = nullptr;

  for (auto * sub : subs_snapshot) {
    if (!sub) continue;  // Safety check

    std::lock_guard<std::mutex> sub_lock(sub->queue_mutex);

    // FIFO overflow: discard oldest if queue is full
    if (sub->message_queue.size() >= sub->queue_depth) {
      sub->message_queue.pop();
    }

    // Copy message (each subscription gets its own copy)
    sub->message_queue.push(MessageItem{
      std::vector<uint8_t>(item.data),
      item.timestamp_ns,
      item.sequence_number,
      item.publisher_gid
    });

    delivered = true;
    if (!ctx && sub->context) {
      ctx = sub->context;
    }
  }

  // Level 3: Notify waiters after enqueuing (enables rmw_wait wake)
  if (delivered && ctx) {
    ctx->notify_waiters();
  }

  return true;
}

//=============================================================================
// MockRouter::register_publisher
//=============================================================================
void MockRouter::register_publisher(const std::string & topic_name, PublisherImpl * pub)
{
  std::lock_guard<std::mutex> lock(publishers_mutex);
  topic_to_publishers[topic_name].push_back(pub);
}

//=============================================================================
// MockRouter::unregister_publisher
//=============================================================================
void MockRouter::unregister_publisher(PublisherImpl * pub)
{
  std::lock_guard<std::mutex> lock(publishers_mutex);

  for (auto & pair : topic_to_publishers) {
    auto & vec = pair.second;
    vec.erase(
      std::remove(vec.begin(), vec.end(), pub),
      vec.end());
  }
}

//=============================================================================
// MockRouter::register_subscription
//=============================================================================
void MockRouter::register_subscription(const std::string & topic_name, SubscriptionImpl * sub)
{
  std::lock_guard<std::mutex> lock(subscriptions_mutex);
  topic_to_subscriptions[topic_name].push_back(sub);
}

//=============================================================================
// MockRouter::unregister_subscription
//=============================================================================
void MockRouter::unregister_subscription(SubscriptionImpl * sub)
{
  std::lock_guard<std::mutex> lock(subscriptions_mutex);

  for (auto & pair : topic_to_subscriptions) {
    auto & vec = pair.second;
    vec.erase(
      std::remove(vec.begin(), vec.end(), sub),
      vec.end());
  }
}

//=============================================================================
// MockRouter::count_publishers
//=============================================================================
size_t MockRouter::count_publishers(const std::string & topic_name) const
{
  std::lock_guard<std::mutex> lock(publishers_mutex);
  auto it = topic_to_publishers.find(topic_name);
  if (it == topic_to_publishers.end()) {
    return 0;
  }
  return it->second.size();
}

//=============================================================================
// MockRouter::count_subscriptions
//=============================================================================
size_t MockRouter::count_subscriptions(const std::string & topic_name) const
{
  std::lock_guard<std::mutex> lock(subscriptions_mutex);
  auto it = topic_to_subscriptions.find(topic_name);
  if (it == topic_to_subscriptions.end()) {
    return 0;
  }
  return it->second.size();
}

//=============================================================================
// MockRouter::clear_all (called by rmw_context_fini)
//=============================================================================
void MockRouter::clear_all()
{
  {
    std::lock_guard<std::mutex> lock(subscriptions_mutex);
    topic_to_subscriptions.clear();
  }
  {
    std::lock_guard<std::mutex> lock(publishers_mutex);
    topic_to_publishers.clear();
  }
  sequence_counter.store(0);
}

}  // namespace rmw_mock
