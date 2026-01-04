// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Level 3: Wait set implementation

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

extern "C" {

//=============================================================================
// rmw_create_wait_set
//=============================================================================
RMW_MOCK_PUBLIC
rmw_wait_set_t *
rmw_create_wait_set(rmw_context_t * context, size_t max_conditions)
{
  (void)max_conditions;  // Not used in minimal implementation

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

  // Allocate wait set
  auto * wait_set = new (std::nothrow) rmw_wait_set_t;
  if (!wait_set) {
    RMW_SET_ERROR_MSG("failed to allocate wait_set");
    return nullptr;
  }

  // Allocate implementation data
  auto * impl = new (std::nothrow) rmw_mock::WaitSetImpl;
  if (!impl) {
    delete wait_set;
    RMW_SET_ERROR_MSG("failed to allocate wait_set impl");
    return nullptr;
  }

  impl->context = mock_ctx;

  wait_set->implementation_identifier = rmw_mock::RMW_MOCK_IDENTIFIER;
  wait_set->data = impl;

  return wait_set;
}

//=============================================================================
// rmw_destroy_wait_set
//=============================================================================
RMW_MOCK_PUBLIC
rmw_ret_t
rmw_destroy_wait_set(rmw_wait_set_t * wait_set)
{
  if (!wait_set) {
    RMW_SET_ERROR_MSG("wait_set is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!rmw_mock::check_identifier(wait_set->implementation_identifier)) {
    RMW_SET_ERROR_MSG("wait_set implementation mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * impl = static_cast<rmw_mock::WaitSetImpl *>(wait_set->data);
  delete impl;
  delete wait_set;

  return RMW_RET_OK;
}

}  // extern "C"
