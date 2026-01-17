// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/ColorRGBA functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/color_rgba.h"
#include "rcutils/allocator.h"

bool std_msgs__msg__ColorRGBA__init(std_msgs__msg__ColorRGBA * msg)
{
  if (!msg) { return false; }
  msg->r = 0.0f;
  msg->g = 0.0f;
  msg->b = 0.0f;
  msg->a = 1.0f;
  return true;
}

void std_msgs__msg__ColorRGBA__fini(std_msgs__msg__ColorRGBA * msg)
{
  (void)msg;
}

std_msgs__msg__ColorRGBA * std_msgs__msg__ColorRGBA__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__ColorRGBA * msg =
    (std_msgs__msg__ColorRGBA *)allocator.allocate(
      sizeof(std_msgs__msg__ColorRGBA), allocator.state);
  if (!msg) { return NULL; }
  if (!std_msgs__msg__ColorRGBA__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__ColorRGBA__destroy(std_msgs__msg__ColorRGBA * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__ColorRGBA__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__ColorRGBA__Sequence__init(
  std_msgs__msg__ColorRGBA__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (std_msgs__msg__ColorRGBA *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__ColorRGBA), allocator.state);
    if (!array->data) { return false; }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void std_msgs__msg__ColorRGBA__Sequence__fini(
  std_msgs__msg__ColorRGBA__Sequence * array)
{
  if (!array || !array->data) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
