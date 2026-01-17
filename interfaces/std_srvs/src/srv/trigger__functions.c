// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/Trigger functions

#include "std_srvs/srv/trigger.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// Trigger_Request functions
// =============================================================================

bool std_srvs__srv__Trigger_Request__init(std_srvs__srv__Trigger_Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void std_srvs__srv__Trigger_Request__fini(std_srvs__srv__Trigger_Request * msg)
{
  if (!msg) {
    return;
  }
  (void)msg;
}

std_srvs__srv__Trigger_Request * std_srvs__srv__Trigger_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__Trigger_Request * msg = (std_srvs__srv__Trigger_Request *)allocator.allocate(
    sizeof(std_srvs__srv__Trigger_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!std_srvs__srv__Trigger_Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_srvs__srv__Trigger_Request__destroy(std_srvs__srv__Trigger_Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__Trigger_Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_srvs__srv__Trigger_Request__Sequence__init(
  std_srvs__srv__Trigger_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }

  array->data = (std_srvs__srv__Trigger_Request *)allocator.zero_allocate(
    size, sizeof(std_srvs__srv__Trigger_Request), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!std_srvs__srv__Trigger_Request__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        std_srvs__srv__Trigger_Request__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void std_srvs__srv__Trigger_Request__Sequence__fini(
  std_srvs__srv__Trigger_Request__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    std_srvs__srv__Trigger_Request__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}

// =============================================================================
// Trigger_Response functions
// =============================================================================

bool std_srvs__srv__Trigger_Response__init(std_srvs__srv__Trigger_Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->success = false;
  rosidl_runtime_c__String__init(&msg->message);
  return true;
}

void std_srvs__srv__Trigger_Response__fini(std_srvs__srv__Trigger_Response * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->message);
}

std_srvs__srv__Trigger_Response * std_srvs__srv__Trigger_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__Trigger_Response * msg = (std_srvs__srv__Trigger_Response *)allocator.allocate(
    sizeof(std_srvs__srv__Trigger_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!std_srvs__srv__Trigger_Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_srvs__srv__Trigger_Response__destroy(std_srvs__srv__Trigger_Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__Trigger_Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_srvs__srv__Trigger_Response__Sequence__init(
  std_srvs__srv__Trigger_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }

  array->data = (std_srvs__srv__Trigger_Response *)allocator.zero_allocate(
    size, sizeof(std_srvs__srv__Trigger_Response), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!std_srvs__srv__Trigger_Response__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        std_srvs__srv__Trigger_Response__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void std_srvs__srv__Trigger_Response__Sequence__fini(
  std_srvs__srv__Trigger_Response__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    std_srvs__srv__Trigger_Response__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
