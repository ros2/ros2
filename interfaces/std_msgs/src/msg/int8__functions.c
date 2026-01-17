// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Int8 functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/int8.h"
#include "rcutils/allocator.h"

bool std_msgs__msg__Int8__init(std_msgs__msg__Int8 * msg)
{
  if (!msg) { return false; }
  msg->data = 0;
  return true;
}

void std_msgs__msg__Int8__fini(std_msgs__msg__Int8 * msg)
{
  (void)msg;
}

std_msgs__msg__Int8 * std_msgs__msg__Int8__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Int8 * msg = (std_msgs__msg__Int8 *)allocator.allocate(
    sizeof(std_msgs__msg__Int8), allocator.state);
  if (!msg) { return NULL; }
  if (!std_msgs__msg__Int8__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__Int8__destroy(std_msgs__msg__Int8 * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Int8__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__Int8__Sequence__init(
  std_msgs__msg__Int8__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (std_msgs__msg__Int8 *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__Int8), allocator.state);
    if (!array->data) { return false; }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void std_msgs__msg__Int8__Sequence__fini(
  std_msgs__msg__Int8__Sequence * array)
{
  if (!array || !array->data) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
