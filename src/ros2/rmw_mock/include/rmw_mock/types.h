// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// rmw_mock core data structures
// Design: per-context router, condvar-based wait mechanism

#ifndef RMW_MOCK__TYPES_H_
#define RMW_MOCK__TYPES_H_

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

#include "rmw/types.h"

namespace rmw_mock {

// Implementation identifier (must match rmw_get_implementation_identifier)
constexpr const char * RMW_MOCK_IDENTIFIER = "rmw_mock";

// Serialization format
constexpr const char * RMW_MOCK_SERIALIZATION_FORMAT = "cdr";

// Safe identifier comparison (use strcmp because constexpr strings may have
// different addresses across translation units/library boundaries)
inline bool check_identifier(const char * identifier)
{
  return identifier != nullptr &&
         std::strcmp(identifier, RMW_MOCK_IDENTIFIER) == 0;
}

// Forward declarations
struct MockContext;
struct NodeImpl;
struct PublisherImpl;
struct SubscriptionImpl;
struct GuardConditionImpl;
struct WaitSetImpl;

//=============================================================================
// MessageItem: Envelope for routed messages (Level 2+)
//=============================================================================
struct MessageItem {
  std::vector<uint8_t> data;       // Serialized CDR data
  int64_t timestamp_ns;            // Publication timestamp (nanoseconds)
  uint64_t sequence_number;        // Per-publisher sequence number
  rmw_gid_t publisher_gid;         // Publisher GID

  MessageItem() = default;

  MessageItem(
    std::vector<uint8_t> && data_,
    int64_t ts,
    uint64_t seq,
    const rmw_gid_t & gid)
  : data(std::move(data_)),
    timestamp_ns(ts),
    sequence_number(seq)
  {
    std::memcpy(publisher_gid.data, gid.data, RMW_GID_STORAGE_SIZE);
  }
};

//=============================================================================
// MockRouter: Per-context message router (NOT a global singleton)
//=============================================================================
struct MockRouter {
  // Topic -> Subscriptions mapping
  mutable std::mutex subscriptions_mutex;
  std::map<std::string, std::vector<SubscriptionImpl *>> topic_to_subscriptions;

  // Topic -> Publishers mapping
  mutable std::mutex publishers_mutex;
  std::map<std::string, std::vector<PublisherImpl *>> topic_to_publishers;

  // Global sequence counter for this context
  std::atomic<uint64_t> sequence_counter{0};

  MockRouter() = default;
  ~MockRouter() = default;

  // Disable copy
  MockRouter(const MockRouter &) = delete;
  MockRouter & operator=(const MockRouter &) = delete;

  // Level 2: Route serialized message to all matching subscriptions
  bool publish(
    const std::string & topic_name,
    std::vector<uint8_t> && serialized_data,
    const rmw_gid_t & publisher_gid,
    int64_t timestamp_ns);

  // Level 2: Register/unregister endpoints
  void register_publisher(const std::string & topic_name, PublisherImpl * pub);
  void unregister_publisher(PublisherImpl * pub);
  void register_subscription(const std::string & topic_name, SubscriptionImpl * sub);
  void unregister_subscription(SubscriptionImpl * sub);

  // Level 2: Query counts
  size_t count_publishers(const std::string & topic_name) const;
  size_t count_subscriptions(const std::string & topic_name) const;

  // Cleanup: called by rmw_context_fini
  void clear_all();
};

//=============================================================================
// MockContext: Per-context state (replaces global singleton)
//=============================================================================
struct MockContext {
  std::atomic<bool> is_shutdown{false};
  std::atomic<uint64_t> gid_counter{1};  // GID generator
  MockRouter router;                      // Per-context router instance

  // Level 3: Wait notification primitives (per-context global notification)
  std::mutex wait_mutex;
  std::condition_variable wait_cv;

  // Reference counting for safe destruction during concurrent wait
  std::atomic<uint32_t> wait_refcnt{0};
  std::condition_variable refcnt_cv;  // Notified when refcnt reaches 0

  MockContext() = default;
  ~MockContext() = default;

  // Disable copy
  MockContext(const MockContext &) = delete;
  MockContext & operator=(const MockContext &) = delete;

  // Reference counting for wait protection
  void retain() {
    wait_refcnt.fetch_add(1, std::memory_order_acq_rel);
  }

  void release() {
    if (wait_refcnt.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      // Last reference dropped, notify fini if waiting
      refcnt_cv.notify_all();
    }
  }

  // Generate unique GID for this context
  void generate_gid(rmw_gid_t * gid);

  // Convenience: return GID by value
  rmw_gid_t generate_gid();

  // Level 3: Notify all waiters (called after publish/trigger)
  void notify_waiters()
  {
    wait_cv.notify_all();
  }
};

//=============================================================================
// NodeImpl: Node implementation data
//=============================================================================
struct NodeImpl {
  std::string name;
  std::string namespace_;
  MockContext * context{nullptr};
  rmw_guard_condition_t * graph_guard_condition{nullptr};  // Level 3

  NodeImpl() = default;
  ~NodeImpl() = default;
};

//=============================================================================
// PublisherImpl: Publisher implementation data (Level 2+)
//=============================================================================
struct PublisherImpl {
  std::string topic_name;
  rmw_gid_t gid;
  rmw_qos_profile_t qos;
  NodeImpl * node{nullptr};
  MockContext * context{nullptr};
  std::atomic<uint64_t> sequence_number{0};

  PublisherImpl() = default;
  ~PublisherImpl() = default;
};

//=============================================================================
// SubscriptionImpl: Subscription implementation data (Level 2+)
//=============================================================================
struct SubscriptionImpl {
  std::string topic_name;
  rmw_gid_t gid;
  rmw_qos_profile_t qos;
  size_t queue_depth{10};
  NodeImpl * node{nullptr};
  MockContext * context{nullptr};

  // Message queue (thread-safe)
  mutable std::mutex queue_mutex;
  std::condition_variable queue_cv;  // Level 3: condvar for wait
  std::queue<MessageItem> message_queue;

  SubscriptionImpl() = default;
  ~SubscriptionImpl() = default;

  // Check if messages available (non-blocking)
  bool has_data() const {
    std::lock_guard<std::mutex> lock(queue_mutex);
    return !message_queue.empty();
  }
};

//=============================================================================
// GuardConditionImpl: Guard condition implementation (Level 3)
// Uses MockContext::notify_waiters() for wake notification
//=============================================================================
struct GuardConditionImpl {
  std::atomic<bool> triggered{false};
  MockContext * context{nullptr};

  GuardConditionImpl() = default;
  ~GuardConditionImpl() = default;

  // Trigger and notify waiters
  void trigger()
  {
    triggered.store(true, std::memory_order_release);
    if (context) {
      context->notify_waiters();
    }
  }

  // Check and consume triggered state
  bool check_and_reset()
  {
    return triggered.exchange(false, std::memory_order_acq_rel);
  }
};

//=============================================================================
// WaitSetImpl: Wait set implementation (Level 3)
// Minimal: just holds context pointer for wait coordination
//=============================================================================
struct WaitSetImpl {
  MockContext * context{nullptr};

  WaitSetImpl() = default;
  ~WaitSetImpl() = default;
};

//=============================================================================
// Utility functions
//=============================================================================

// Get current timestamp in nanoseconds (monotonic clock)
int64_t now_ns();

}  // namespace rmw_mock

#endif  // RMW_MOCK__TYPES_H_
