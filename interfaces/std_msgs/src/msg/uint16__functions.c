// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/UInt16 functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/uint16.h"
#include "rcutils/allocator.h"

bool std_msgs__msg__UInt16__init(std_msgs__msg__UInt16 * msg)
{
  if (!msg) { return false; }
  msg->data = 0;
  return true;
}

void std_msgs__msg__UInt16__fini(std_msgs__msg__UInt16 * msg)
{
  (void)msg;
}

std_msgs__msg__UInt16 * std_msgs__msg__UInt16__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__UInt16 * msg = (std_msgs__msg__UInt16 *)allocator.allocate(
    sizeof(std_msgs__msg__UInt16), allocator.state);
  if (!msg) { return NULL; }
  if (!std_msgs__msg__UInt16__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__UInt16__destroy(std_msgs__msg__UInt16 * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__UInt16__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__UInt16__Sequence__init(
  std_msgs__msg__UInt16__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (std_msgs__msg__UInt16 *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__UInt16), allocator.state);
    if (!array->data) { return false; }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void std_msgs__msg__UInt16__Sequence__fini(
  std_msgs__msg__UInt16__Sequence * array)
{
  if (!array || !array->data) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
