// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 3: rmw_wait implementation - condvar-based blocking wait
// Contract: block until ready or timeout, filter arrays in-place

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

#include <chrono>

namespace {

//=============================================================================
// Helper: Convert rmw_time_t to std::chrono::nanoseconds
//=============================================================================
std::chrono::nanoseconds to_chrono_ns(const rmw_time_t * timeout)
{
  if (!timeout) {
    return std::chrono::nanoseconds::max();  // Infinite
  }
  return std::chrono::seconds(timeout->sec) + std::chrono::nanoseconds(timeout->nsec);
}

//=============================================================================
// Helper: Check if any entity is ready (predicate for condvar wait)
//=============================================================================
bool check_any_ready(
  rmw_subscriptions_t * subscriptions,
  rmw_guard_conditions_t * guard_conditions)
{
  // Check subscriptions
  if (subscriptions) {
    for (size_t i = 0; i < subscriptions->subscriber_count; ++i) {
      if (subscriptions->subscribers[i]) {
        auto * sub = static_cast<rmw_mock::SubscriptionImpl *>(
          static_cast<rmw_subscription_t *>(subscriptions->subscribers[i])->data);
        if (sub && sub->has_data()) {
          return true;
        }
      }
    }
  }

  // Check guard conditions
  if (guard_conditions) {
    for (size_t i = 0; i < guard_conditions->guard_condition_count; ++i) {
      if (guard_conditions->guard_conditions[i]) {
        auto * gc = static_cast<rmw_mock::GuardConditionImpl *>(
          static_cast<rmw_guard_condition_t *>(guard_conditions->guard_conditions[i])->data);
        if (gc && gc->triggered.load(std::memory_order_acquire)) {
          return true;
        }
      }
    }
  }

  return false;
}

//=============================================================================
// Helper: Filter arrays - set non-ready entries to nullptr
//=============================================================================
void filter_arrays(
  rmw_subscriptions_t * subscriptions,
  rmw_guard_conditions_t * guard_conditions,
  rmw_services_t * services,
  rmw_clients_t * clients,
  rmw_events_t * events)
{
  // Filter subscriptions - set to nullptr if queue is empty
  if (subscriptions) {
    for (size_t i = 0; i < subscriptions->subscriber_count; ++i) {
      if (subscriptions->subscribers[i]) {
        auto * sub = static_cast<rmw_mock::SubscriptionImpl *>(
          static_cast<rmw_subscription_t *>(subscriptions->subscribers[i])->data);
        if (!sub || !sub->has_data()) {
          subscriptions->subscribers[i] = nullptr;
        }
      }
    }
  }

  // Filter guard conditions - consume trigger state
  if (guard_conditions) {
    for (size_t i = 0; i < guard_conditions->guard_condition_count; ++i) {
      if (guard_conditions->guard_conditions[i]) {
        auto * gc = static_cast<rmw_mock::GuardConditionImpl *>(
          static_cast<rmw_guard_condition_t *>(guard_conditions->guard_conditions[i])->data);
        if (!gc || !gc->check_and_reset()) {
          // Not triggered or already consumed - set to nullptr
          guard_conditions->guard_conditions[i] = nullptr;
        }
        // If triggered, leave pointer intact (ready) and consume the trigger
      }
    }
  }

  // Services not supported - set all to nullptr
  if (services) {
    for (size_t i = 0; i < services->service_count; ++i) {
      services->services[i] = nullptr;
    }
  }

  // Clients not supported - set all to nullptr
  if (clients) {
    for (size_t i = 0; i < clients->client_count; ++i) {
      clients->clients[i] = nullptr;
    }
  }

  // Events not supported - set all to nullptr
  if (events) {
    for (size_t i = 0; i < events->event_count; ++i) {
      events->events[i] = nullptr;
    }
  }
}

//=============================================================================
// Helper: Get MockContext from wait_set
//=============================================================================
rmw_mock::MockContext * get_context(rmw_wait_set_t * wait_set)
{
  if (!wait_set || !wait_set->data) {
    return nullptr;
  }
  auto * impl = static_cast<rmw_mock::WaitSetImpl *>(wait_set->data);
  return impl->context;
}

}  // namespace

extern "C" {

//=============================================================================
// rmw_wait - Core wait implementation
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_wait(
  rmw_subscriptions_t * subscriptions,
  rmw_guard_conditions_t * guard_conditions,
  rmw_services_t * services,
  rmw_clients_t * clients,
  rmw_events_t * events,
  rmw_wait_set_t * wait_set,
  const rmw_time_t * wait_timeout)
{
  // Validate wait_set
  if (!wait_set) {
    RMW_SET_ERROR_MSG("wait_set is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(wait_set->implementation_identifier)) {
    RMW_SET_ERROR_MSG("wait_set implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  rmw_mock::MockContext * ctx = get_context(wait_set);
  if (!ctx) {
    RMW_SET_ERROR_MSG("wait_set has no context");
    return RMW_RET_ERROR;
  }

  // Retain context to prevent destruction during wait
  ctx->retain();

  // Convert timeout
  auto timeout_ns = to_chrono_ns(wait_timeout);
  bool is_infinite = (timeout_ns == std::chrono::nanoseconds::max());
  bool is_zero = (wait_timeout && wait_timeout->sec == 0 && wait_timeout->nsec == 0);

  // Predicate: any subscription has data or any guard condition triggered
  auto predicate = [&]() {
    return check_any_ready(subscriptions, guard_conditions) || ctx->is_shutdown.load();
  };

  rmw_ret_t result = RMW_RET_OK;

  // Lock and wait
  std::unique_lock<std::mutex> lock(ctx->wait_mutex);

  if (is_zero) {
    // Non-blocking: just check predicate
    if (!predicate()) {
      result = RMW_RET_TIMEOUT;
    }
  } else if (is_infinite) {
    // Infinite wait
    ctx->wait_cv.wait(lock, predicate);
  } else {
    // Timed wait
    bool woke = ctx->wait_cv.wait_for(lock, timeout_ns, predicate);
    if (!woke) {
      result = RMW_RET_TIMEOUT;
    }
  }

  // Check for shutdown before unlocking (safe because we retained context)
  bool is_shutdown = ctx->is_shutdown.load();

  lock.unlock();

  // Filter arrays: set non-ready entries to nullptr
  filter_arrays(subscriptions, guard_conditions, services, clients, events);

  // Release context reference (allows destruction if this was last user)
  ctx->release();

  // Return OK even on shutdown (filtered arrays already set)
  if (is_shutdown) {
    return RMW_RET_OK;
  }

  return result;
}

}  // extern "C"
