// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Stub implementations for RMW/rcutils helper functions
// These provide zero-dependency implementations for testing

#include "rmw/rmw.h"
#include "rmw/init.h"
#include "rmw/init_options.h"
#include "rmw/publisher_options.h"
#include "rmw/subscription_options.h"
#include "rcutils/allocator.h"
#include "rcutils/types/uint8_array.h"
#include "rcutils/types/string_array.h"
#include "rcutils/error_handling.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>

// Static error message storage for rcutils_get_error_string
static char g_error_msg[256] = "";

extern "C" {

//=============================================================================
// rcutils stubs
//=============================================================================

rcutils_allocator_t rcutils_get_default_allocator(void)
{
  rcutils_allocator_t allocator;
  allocator.allocate = [](size_t size, void *) -> void * {
    return std::malloc(size);
  };
  allocator.deallocate = [](void * ptr, void *) {
    std::free(ptr);
  };
  allocator.reallocate = [](void * ptr, size_t size, void *) -> void * {
    return std::realloc(ptr, size);
  };
  allocator.zero_allocate = [](size_t nmemb, size_t size, void *) -> void * {
    return std::calloc(nmemb, size);
  };
  allocator.state = nullptr;
  return allocator;
}

void rcutils_set_error_state(const char * error_msg, const char * file, size_t line)
{
  (void)file;
  (void)line;
  // Store error message for retrieval
  if (error_msg) {
    std::strncpy(g_error_msg, error_msg, sizeof(g_error_msg) - 1);
    g_error_msg[sizeof(g_error_msg) - 1] = '\0';
  } else {
    g_error_msg[0] = '\0';
  }
}

rcutils_error_string_t rcutils_get_error_string(void)
{
  rcutils_error_string_t error_string;
  std::strncpy(error_string.str, g_error_msg, sizeof(error_string.str) - 1);
  error_string.str[sizeof(error_string.str) - 1] = '\0';
  return error_string;
}

void rcutils_reset_error(void)
{
  g_error_msg[0] = '\0';
}

rcutils_string_array_t rcutils_get_zero_initialized_string_array(void)
{
  rcutils_string_array_t array;
  std::memset(&array, 0, sizeof(array));
  return array;
}

rcutils_ret_t rcutils_uint8_array_init(
  rcutils_uint8_array_t * array,
  size_t buffer_capacity,
  const rcutils_allocator_t * allocator)
{
  if (!array || !allocator) {
    return RCUTILS_RET_INVALID_ARGUMENT;
  }
  array->buffer = static_cast<uint8_t *>(allocator->allocate(buffer_capacity, allocator->state));
  if (!array->buffer && buffer_capacity > 0) {
    return RCUTILS_RET_BAD_ALLOC;
  }
  array->buffer_capacity = buffer_capacity;
  array->buffer_length = 0;
  array->allocator = *allocator;
  return RCUTILS_RET_OK;
}

rcutils_ret_t rcutils_uint8_array_fini(rcutils_uint8_array_t * array)
{
  if (!array) {
    return RCUTILS_RET_INVALID_ARGUMENT;
  }
  if (array->buffer) {
    array->allocator.deallocate(array->buffer, array->allocator.state);
    array->buffer = nullptr;
  }
  array->buffer_capacity = 0;
  array->buffer_length = 0;
  return RCUTILS_RET_OK;
}

rcutils_ret_t rcutils_uint8_array_resize(rcutils_uint8_array_t * array, size_t new_size)
{
  if (!array) {
    return RCUTILS_RET_INVALID_ARGUMENT;
  }
  if (new_size == array->buffer_capacity) {
    return RCUTILS_RET_OK;
  }
  uint8_t * new_buffer = static_cast<uint8_t *>(
    array->allocator.reallocate(array->buffer, new_size, array->allocator.state));
  if (!new_buffer && new_size > 0) {
    return RCUTILS_RET_BAD_ALLOC;
  }
  array->buffer = new_buffer;
  array->buffer_capacity = new_size;
  if (array->buffer_length > new_size) {
    array->buffer_length = new_size;
  }
  return RCUTILS_RET_OK;
}

//=============================================================================
// rmw helper stubs
//=============================================================================

rmw_init_options_t rmw_get_zero_initialized_init_options(void)
{
  rmw_init_options_t options;
  std::memset(&options, 0, sizeof(options));
  return options;
}

rmw_context_t rmw_get_zero_initialized_context(void)
{
  rmw_context_t context;
  std::memset(&context, 0, sizeof(context));
  return context;
}

rmw_security_options_t rmw_get_zero_initialized_security_options(void)
{
  rmw_security_options_t options;
  std::memset(&options, 0, sizeof(options));
  return options;
}

rmw_discovery_options_t rmw_get_zero_initialized_discovery_options(void)
{
  rmw_discovery_options_t options;
  std::memset(&options, 0, sizeof(options));
  return options;
}

rmw_publisher_options_t rmw_get_default_publisher_options(void)
{
  rmw_publisher_options_t options;
  std::memset(&options, 0, sizeof(options));
  return options;
}

rmw_subscription_options_t rmw_get_default_subscription_options(void)
{
  rmw_subscription_options_t options;
  std::memset(&options, 0, sizeof(options));
  return options;
}

}  // extern "C"
