// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// rmw_mock: Initialization and shutdown APIs
// Level 1: Foundation/Smoke

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/init.h"
#include "rmw/init_options.h"

#include <cstdlib>
#include <cstring>

extern "C" {

//=============================================================================
// Init Options
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t rmw_init_options_init(
  rmw_init_options_t * init_options,
  rcutils_allocator_t allocator)
{
  if (!init_options) {
    RMW_SET_ERROR_MSG("init_options is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (init_options->implementation_identifier != nullptr) {
    RMW_SET_ERROR_MSG("init_options already initialized");
    return RMW_RET_INVALID_ARGUMENT;
  }

  init_options->implementation_identifier = rmw_mock::RMW_MOCK_IDENTIFIER;
  init_options->allocator = allocator;
  init_options->instance_id = 0;
  init_options->enclave = nullptr;
  init_options->domain_id = RMW_DEFAULT_DOMAIN_ID;
  init_options->security_options = rmw_get_zero_initialized_security_options();
  init_options->localhost_only = RMW_LOCALHOST_ONLY_DEFAULT;
  init_options->discovery_options = rmw_get_zero_initialized_discovery_options();
  init_options->impl = nullptr;

  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_init_options_copy(
  const rmw_init_options_t * src,
  rmw_init_options_t * dst)
{
  if (!src) {
    RMW_SET_ERROR_MSG("src is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!dst) {
    RMW_SET_ERROR_MSG("dst is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(src->implementation_identifier)) {
    RMW_SET_ERROR_MSG("src implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }
  if (dst->implementation_identifier != nullptr) {
    RMW_SET_ERROR_MSG("dst already initialized");
    return RMW_RET_INVALID_ARGUMENT;
  }

  // Copy all fields
  *dst = *src;

  // Deep copy enclave if present
  if (src->enclave) {
    dst->enclave = static_cast<char *>(
      dst->allocator.allocate(strlen(src->enclave) + 1, dst->allocator.state));
    if (!dst->enclave) {
      RMW_SET_ERROR_MSG("failed to allocate enclave");
      return RMW_RET_BAD_ALLOC;
    }
    strcpy(dst->enclave, src->enclave);
  }

  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_init_options_fini(rmw_init_options_t * init_options)
{
  if (!init_options) {
    RMW_SET_ERROR_MSG("init_options is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(init_options->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  // Free enclave if allocated
  if (init_options->enclave) {
    init_options->allocator.deallocate(init_options->enclave, init_options->allocator.state);
    init_options->enclave = nullptr;
  }

  // Reset to zero
  *init_options = rmw_get_zero_initialized_init_options();

  return RMW_RET_OK;
}

//=============================================================================
// Context Initialization
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t rmw_init(
  const rmw_init_options_t * options,
  rmw_context_t * context)
{
  if (!options) {
    RMW_SET_ERROR_MSG("options is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(options->implementation_identifier)) {
    RMW_SET_ERROR_MSG("options implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }
  if (context->implementation_identifier != nullptr) {
    RMW_SET_ERROR_MSG("context already initialized");
    return RMW_RET_INVALID_ARGUMENT;
  }

  // Allocate MockContext
  auto * mock_context = new (std::nothrow) rmw_mock::MockContext();
  if (!mock_context) {
    RMW_SET_ERROR_MSG("failed to allocate MockContext");
    return RMW_RET_BAD_ALLOC;
  }

  // Initialize context
  context->implementation_identifier = rmw_mock::RMW_MOCK_IDENTIFIER;
  context->instance_id = options->instance_id;
  context->actual_domain_id = options->domain_id;
  context->impl = reinterpret_cast<rmw_context_impl_t *>(mock_context);

  // Copy init options
  rmw_ret_t ret = rmw_init_options_copy(options, &context->options);
  if (ret != RMW_RET_OK) {
    delete mock_context;
    context->impl = nullptr;
    context->implementation_identifier = nullptr;
    return ret;
  }

  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_shutdown(rmw_context_t * context)
{
  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(context->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * mock_context = reinterpret_cast<rmw_mock::MockContext *>(context->impl);
  if (mock_context) {
    mock_context->is_shutdown.store(true);
    // Notify all waiters to unblock (Level 3)
    mock_context->notify_waiters();
  }

  return RMW_RET_OK;
}

RMW_MOCK_PUBLIC
rmw_ret_t rmw_context_fini(rmw_context_t * context)
{
  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!rmw_mock::check_identifier(context->implementation_identifier)) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto * mock_context = reinterpret_cast<rmw_mock::MockContext *>(context->impl);
  if (mock_context) {
    // Ensure shutdown flag is set (wake any waiters)
    mock_context->is_shutdown.store(true);
    mock_context->notify_waiters();

    // Wait for all wait operations to complete (reference count → 0)
    // This prevents UAF where we delete context while rmw_wait is still using it
    {
      std::unique_lock<std::mutex> lock(mock_context->wait_mutex);
      mock_context->refcnt_cv.wait(lock, [&]() {
        return mock_context->wait_refcnt.load() == 0;
      });
    }

    // Clear all routing state (critical for test isolation)
    mock_context->router.clear_all();
    delete mock_context;
    context->impl = nullptr;
  }

  // Finalize options
  rmw_init_options_fini(&context->options);

  // Reset context
  context->implementation_identifier = nullptr;
  context->instance_id = 0;
  context->actual_domain_id = 0;

  return RMW_RET_OK;
}

//=============================================================================
// MockContext helper implementations
//=============================================================================

namespace rmw_mock {

void MockContext::generate_gid(rmw_gid_t * gid)
{
  if (!gid) return;

  std::memset(gid->data, 0, RMW_GID_STORAGE_SIZE);

  // Layout: [0-7] counter, [8-15] context pointer hash
  uint64_t counter = gid_counter.fetch_add(1);
  std::memcpy(gid->data, &counter, sizeof(counter));

  // Use context address as uniqueness source
  uintptr_t ctx_addr = reinterpret_cast<uintptr_t>(this);
  std::memcpy(gid->data + 8, &ctx_addr, sizeof(ctx_addr));
}

// By-value convenience overload
rmw_gid_t MockContext::generate_gid()
{
  rmw_gid_t gid;
  generate_gid(&gid);
  return gid;
}

}  // namespace rmw_mock

}  // extern "C"
