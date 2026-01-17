// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/UInt64MultiArray functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/uint64_multi_array.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool std_msgs__msg__UInt64MultiArray__init(std_msgs__msg__UInt64MultiArray * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__MultiArrayLayout__init(&msg->layout)) {
    return false;
  }
  if (!rosidl_runtime_c__uint64__Sequence__init(&msg->data, 0)) {
    std_msgs__msg__MultiArrayLayout__fini(&msg->layout);
    return false;
  }
  return true;
}

void std_msgs__msg__UInt64MultiArray__fini(std_msgs__msg__UInt64MultiArray * msg)
{
  if (!msg) { return; }
  std_msgs__msg__MultiArrayLayout__fini(&msg->layout);
  rosidl_runtime_c__uint64__Sequence__fini(&msg->data);
}

std_msgs__msg__UInt64MultiArray * std_msgs__msg__UInt64MultiArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__UInt64MultiArray * msg =
    (std_msgs__msg__UInt64MultiArray *)allocator.allocate(
      sizeof(std_msgs__msg__UInt64MultiArray), allocator.state);
  if (!msg) { return NULL; }
  if (!std_msgs__msg__UInt64MultiArray__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__UInt64MultiArray__destroy(std_msgs__msg__UInt64MultiArray * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__UInt64MultiArray__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__UInt64MultiArray__Sequence__init(
  std_msgs__msg__UInt64MultiArray__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size) {
    array->data = (std_msgs__msg__UInt64MultiArray *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__UInt64MultiArray), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!std_msgs__msg__UInt64MultiArray__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          std_msgs__msg__UInt64MultiArray__fini(&array->data[j]);
        }
        allocator.deallocate(array->data, allocator.state);
        return false;
      }
    }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void std_msgs__msg__UInt64MultiArray__Sequence__fini(
  std_msgs__msg__UInt64MultiArray__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      std_msgs__msg__UInt64MultiArray__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
