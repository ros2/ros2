// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 3: Guard condition implementation

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

extern "C" {

//=============================================================================
// rmw_create_guard_condition
//=============================================================================
RMW_MOCK_PUBLIC
rmw_guard_condition_t *
rmw_create_guard_condition(rmw_context_t * context)
{
  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return nullptr;
  }

  if (!rmw_mock::check_identifier(context->implementation_identifier)) {
    RMW_SET_ERROR_MSG("context implementation mismatch");
    return nullptr;
  }

  auto * mock_ctx = reinterpret_cast<rmw_mock::MockContext *>(context->impl);
  if (!mock_ctx) {
    RMW_SET_ERROR_MSG("context impl is null");
    return nullptr;
  }

  // Allocate guard condition
  auto * gc = new (std::nothrow) rmw_guard_condition_t;
  if (!gc) {
    RMW_SET_ERROR_MSG("failed to allocate guard_condition");
    return nullptr;
  }

  // Allocate implementation data
  auto * impl = new (std::nothrow) rmw_mock::GuardConditionImpl;
  if (!impl) {
    delete gc;
    RMW_SET_ERROR_MSG("failed to allocate guard_condition impl");
    return nullptr;
  }

  impl->context = mock_ctx;
  impl->triggered.store(false, std::memory_order_relaxed);

  gc->implementation_identifier = rmw_mock::RMW_MOCK_IDENTIFIER;
  gc->data = impl;
  gc->context = context;

  return gc;
}

//=============================================================================
// rmw_destroy_guard_condition
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_destroy_guard_condition(rmw_guard_condition_t * guard_condition)
{
  if (!guard_condition) {
    RMW_SET_ERROR_MSG("guard_condition is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(guard_condition->implementation_identifier)) {
    RMW_SET_ERROR_MSG("guard_condition implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * impl = static_cast<rmw_mock::GuardConditionImpl *>(guard_condition->data);
  delete impl;
  delete guard_condition;

  return RMW_RET_OK;
}

//=============================================================================
// rmw_trigger_guard_condition
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_trigger_guard_condition(const rmw_guard_condition_t * guard_condition)
{
  if (!guard_condition) {
    RMW_SET_ERROR_MSG("guard_condition is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(guard_condition->implementation_identifier)) {
    RMW_SET_ERROR_MSG("guard_condition implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * impl = static_cast<rmw_mock::GuardConditionImpl *>(guard_condition->data);
  if (!impl) {
    RMW_SET_ERROR_MSG("guard_condition data is null");
    return RMW_RET_ERROR;
  }

  // Use the trigger() method which sets flag and notifies waiters
  impl->trigger();

  return RMW_RET_OK;
}

}  // extern "C"
