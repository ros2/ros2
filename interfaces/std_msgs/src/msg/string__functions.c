// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/String functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "std_msgs/msg/string.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"

bool std_msgs__msg__String__init(std_msgs__msg__String * msg)
{
  if (!msg) {
    return false;
  }
  if (!rosidl_runtime_c__String__init(&msg->data)) {
    return false;
  }
  return true;
}

void std_msgs__msg__String__fini(std_msgs__msg__String * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->data);
}

std_msgs__msg__String * std_msgs__msg__String__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__String * msg =
    (std_msgs__msg__String *)allocator.allocate(
      sizeof(std_msgs__msg__String), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!std_msgs__msg__String__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__String__destroy(std_msgs__msg__String * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__String__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__String__are_equal(
  const std_msgs__msg__String * lhs,
  const std_msgs__msg__String * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (!rosidl_runtime_c__String__are_equal(&lhs->data, &rhs->data)) {
    return false;
  }
  return true;
}

bool std_msgs__msg__String__copy(
  const std_msgs__msg__String * input,
  std_msgs__msg__String * output)
{
  if (!input || !output) {
    return false;
  }
  if (!rosidl_runtime_c__String__copy(&input->data, &output->data)) {
    return false;
  }
  return true;
}

bool std_msgs__msg__String__Sequence__init(
  std_msgs__msg__String__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__String * data = NULL;

  if (size) {
    data = (std_msgs__msg__String *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__String), allocator.state);
    if (!data) {
      return false;
    }
    for (size_t i = 0; i < size; ++i) {
      if (!std_msgs__msg__String__init(&data[i])) {
        for (size_t j = 0; j < i; ++j) {
          std_msgs__msg__String__fini(&data[j]);
        }
        allocator.deallocate(data, allocator.state);
        return false;
      }
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void std_msgs__msg__String__Sequence__fini(
  std_msgs__msg__String__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      std_msgs__msg__String__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}

std_msgs__msg__String__Sequence *
std_msgs__msg__String__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__String__Sequence * array =
    (std_msgs__msg__String__Sequence *)allocator.allocate(
      sizeof(std_msgs__msg__String__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  if (!std_msgs__msg__String__Sequence__init(array, size)) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void std_msgs__msg__String__Sequence__destroy(
  std_msgs__msg__String__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__String__Sequence__fini(array);
  allocator.deallocate(array, allocator.state);
}
