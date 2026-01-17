// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/MultiArrayDimension functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/multi_array_dimension.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"

bool std_msgs__msg__MultiArrayDimension__init(std_msgs__msg__MultiArrayDimension * msg)
{
  if (!msg) { return false; }
  if (!rosidl_runtime_c__String__init(&msg->label)) {
    return false;
  }
  msg->size = 0;
  msg->stride = 0;
  return true;
}

void std_msgs__msg__MultiArrayDimension__fini(std_msgs__msg__MultiArrayDimension * msg)
{
  if (!msg) { return; }
  rosidl_runtime_c__String__fini(&msg->label);
}

std_msgs__msg__MultiArrayDimension * std_msgs__msg__MultiArrayDimension__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__MultiArrayDimension * msg =
    (std_msgs__msg__MultiArrayDimension *)allocator.allocate(
      sizeof(std_msgs__msg__MultiArrayDimension), allocator.state);
  if (!msg) { return NULL; }
  if (!std_msgs__msg__MultiArrayDimension__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__MultiArrayDimension__destroy(std_msgs__msg__MultiArrayDimension * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__MultiArrayDimension__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__MultiArrayDimension__Sequence__init(
  std_msgs__msg__MultiArrayDimension__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size) {
    array->data = (std_msgs__msg__MultiArrayDimension *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__MultiArrayDimension), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!std_msgs__msg__MultiArrayDimension__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          std_msgs__msg__MultiArrayDimension__fini(&array->data[j]);
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

void std_msgs__msg__MultiArrayDimension__Sequence__fini(
  std_msgs__msg__MultiArrayDimension__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      std_msgs__msg__MultiArrayDimension__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
