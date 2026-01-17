// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rosgraph_msgs/msg/Clock functions

#include "rosgraph_msgs/msg/clock.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rosgraph_msgs__msg__Clock__init(rosgraph_msgs__msg__Clock * msg)
{
  if (!msg) {
    return false;
  }
  if (!builtin_interfaces__msg__Time__init(&msg->clock)) {
    return false;
  }
  return true;
}

void rosgraph_msgs__msg__Clock__fini(rosgraph_msgs__msg__Clock * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->clock);
}

rosgraph_msgs__msg__Clock * rosgraph_msgs__msg__Clock__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosgraph_msgs__msg__Clock * msg = (rosgraph_msgs__msg__Clock *)allocator.allocate(
    sizeof(rosgraph_msgs__msg__Clock), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rosgraph_msgs__msg__Clock__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rosgraph_msgs__msg__Clock__destroy(rosgraph_msgs__msg__Clock * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosgraph_msgs__msg__Clock__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rosgraph_msgs__msg__Clock__Sequence__init(
  rosgraph_msgs__msg__Clock__Sequence * array, size_t size)
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

  array->data = (rosgraph_msgs__msg__Clock *)allocator.zero_allocate(
    size, sizeof(rosgraph_msgs__msg__Clock), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rosgraph_msgs__msg__Clock__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rosgraph_msgs__msg__Clock__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rosgraph_msgs__msg__Clock__Sequence__fini(
  rosgraph_msgs__msg__Clock__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rosgraph_msgs__msg__Clock__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
