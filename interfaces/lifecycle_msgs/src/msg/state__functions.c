// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/State functions

#include "lifecycle_msgs/msg/state.h"
#include "rcutils/allocator.h"
#include <string.h>

bool lifecycle_msgs__msg__State__init(lifecycle_msgs__msg__State * msg)
{
  if (!msg) {
    return false;
  }
  msg->id = 0;
  rosidl_runtime_c__String__init(&msg->label);
  return true;
}

void lifecycle_msgs__msg__State__fini(lifecycle_msgs__msg__State * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->label);
}

lifecycle_msgs__msg__State * lifecycle_msgs__msg__State__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__State * msg = (lifecycle_msgs__msg__State *)allocator.allocate(
    sizeof(lifecycle_msgs__msg__State), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__msg__State__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__msg__State__destroy(lifecycle_msgs__msg__State * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__State__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool lifecycle_msgs__msg__State__Sequence__init(
  lifecycle_msgs__msg__State__Sequence * array, size_t size)
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

  array->data = (lifecycle_msgs__msg__State *)allocator.zero_allocate(
    size, sizeof(lifecycle_msgs__msg__State), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!lifecycle_msgs__msg__State__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        lifecycle_msgs__msg__State__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void lifecycle_msgs__msg__State__Sequence__fini(
  lifecycle_msgs__msg__State__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    lifecycle_msgs__msg__State__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
