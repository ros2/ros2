// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Header functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "std_msgs/msg/header.h"
#include "builtin_interfaces/msg/time.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"

bool std_msgs__msg__Header__init(std_msgs__msg__Header * msg)
{
  if (!msg) {
    return false;
  }
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    return false;
  }
  if (!rosidl_runtime_c__String__init(&msg->frame_id)) {
    builtin_interfaces__msg__Time__fini(&msg->stamp);
    return false;
  }
  return true;
}

void std_msgs__msg__Header__fini(std_msgs__msg__Header * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  rosidl_runtime_c__String__fini(&msg->frame_id);
}

std_msgs__msg__Header * std_msgs__msg__Header__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Header * msg =
    (std_msgs__msg__Header *)allocator.allocate(
      sizeof(std_msgs__msg__Header), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!std_msgs__msg__Header__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__Header__destroy(std_msgs__msg__Header * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Header__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__Header__are_equal(
  const std_msgs__msg__Header * lhs,
  const std_msgs__msg__Header * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (!builtin_interfaces__msg__Time__are_equal(&lhs->stamp, &rhs->stamp)) {
    return false;
  }
  if (!rosidl_runtime_c__String__are_equal(&lhs->frame_id, &rhs->frame_id)) {
    return false;
  }
  return true;
}

bool std_msgs__msg__Header__copy(
  const std_msgs__msg__Header * input,
  std_msgs__msg__Header * output)
{
  if (!input || !output) {
    return false;
  }
  if (!builtin_interfaces__msg__Time__copy(&input->stamp, &output->stamp)) {
    return false;
  }
  if (!rosidl_runtime_c__String__copy(&input->frame_id, &output->frame_id)) {
    return false;
  }
  return true;
}

bool std_msgs__msg__Header__Sequence__init(
  std_msgs__msg__Header__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Header * data = NULL;

  if (size) {
    data = (std_msgs__msg__Header *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__Header), allocator.state);
    if (!data) {
      return false;
    }
    for (size_t i = 0; i < size; ++i) {
      if (!std_msgs__msg__Header__init(&data[i])) {
        for (size_t j = 0; j < i; ++j) {
          std_msgs__msg__Header__fini(&data[j]);
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

void std_msgs__msg__Header__Sequence__fini(
  std_msgs__msg__Header__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      std_msgs__msg__Header__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}

std_msgs__msg__Header__Sequence *
std_msgs__msg__Header__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Header__Sequence * array =
    (std_msgs__msg__Header__Sequence *)allocator.allocate(
      sizeof(std_msgs__msg__Header__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  if (!std_msgs__msg__Header__Sequence__init(array, size)) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void std_msgs__msg__Header__Sequence__destroy(
  std_msgs__msg__Header__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Header__Sequence__fini(array);
  allocator.deallocate(array, allocator.state);
}
