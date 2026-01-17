// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/UVCoordinate functions

#include "visualization_msgs/msg/uv_coordinate.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__UVCoordinate__init(visualization_msgs__msg__UVCoordinate * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  msg->u = 0.0f;
  msg->v = 0.0f;
  return true;
}

void visualization_msgs__msg__UVCoordinate__fini(visualization_msgs__msg__UVCoordinate * msg)
{
  if (!msg) {
    return;
  }

}

visualization_msgs__msg__UVCoordinate * visualization_msgs__msg__UVCoordinate__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__UVCoordinate * msg = (visualization_msgs__msg__UVCoordinate *)allocator.allocate(
    sizeof(visualization_msgs__msg__UVCoordinate), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__UVCoordinate__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__UVCoordinate__destroy(visualization_msgs__msg__UVCoordinate * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__UVCoordinate__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__UVCoordinate__Sequence__init(
  visualization_msgs__msg__UVCoordinate__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__UVCoordinate *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__UVCoordinate), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__UVCoordinate__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__UVCoordinate__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__UVCoordinate__Sequence__fini(
  visualization_msgs__msg__UVCoordinate__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__UVCoordinate__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
