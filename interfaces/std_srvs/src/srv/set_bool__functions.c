// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/SetBool functions

#include "std_srvs/srv/set_bool.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// SetBool_Request functions
// =============================================================================

bool std_srvs__srv__SetBool_Request__init(std_srvs__srv__SetBool_Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->data = false;
  return true;
}

void std_srvs__srv__SetBool_Request__fini(std_srvs__srv__SetBool_Request * msg)
{
  if (!msg) {
    return;
  }
}

std_srvs__srv__SetBool_Request * std_srvs__srv__SetBool_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__SetBool_Request * msg = (std_srvs__srv__SetBool_Request *)allocator.allocate(
    sizeof(std_srvs__srv__SetBool_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!std_srvs__srv__SetBool_Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_srvs__srv__SetBool_Request__destroy(std_srvs__srv__SetBool_Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__SetBool_Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_srvs__srv__SetBool_Request__Sequence__init(
  std_srvs__srv__SetBool_Request__Sequence * array, size_t size)
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

  array->data = (std_srvs__srv__SetBool_Request *)allocator.zero_allocate(
    size, sizeof(std_srvs__srv__SetBool_Request), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!std_srvs__srv__SetBool_Request__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        std_srvs__srv__SetBool_Request__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void std_srvs__srv__SetBool_Request__Sequence__fini(
  std_srvs__srv__SetBool_Request__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    std_srvs__srv__SetBool_Request__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}

// =============================================================================
// SetBool_Response functions
// =============================================================================

bool std_srvs__srv__SetBool_Response__init(std_srvs__srv__SetBool_Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->success = false;
  rosidl_runtime_c__String__init(&msg->message);
  return true;
}

void std_srvs__srv__SetBool_Response__fini(std_srvs__srv__SetBool_Response * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->message);
}

std_srvs__srv__SetBool_Response * std_srvs__srv__SetBool_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__SetBool_Response * msg = (std_srvs__srv__SetBool_Response *)allocator.allocate(
    sizeof(std_srvs__srv__SetBool_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!std_srvs__srv__SetBool_Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_srvs__srv__SetBool_Response__destroy(std_srvs__srv__SetBool_Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_srvs__srv__SetBool_Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_srvs__srv__SetBool_Response__Sequence__init(
  std_srvs__srv__SetBool_Response__Sequence * array, size_t size)
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

  array->data = (std_srvs__srv__SetBool_Response *)allocator.zero_allocate(
    size, sizeof(std_srvs__srv__SetBool_Response), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!std_srvs__srv__SetBool_Response__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        std_srvs__srv__SetBool_Response__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void std_srvs__srv__SetBool_Response__Sequence__fini(
  std_srvs__srv__SetBool_Response__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    std_srvs__srv__SetBool_Response__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
