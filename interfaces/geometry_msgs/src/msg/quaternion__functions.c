// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Quaternion functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/quaternion.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__Quaternion__init(geometry_msgs__msg__Quaternion * msg)
{
  if (!msg) { return false; }
  msg->x = 0.0;
  msg->y = 0.0;
  msg->z = 0.0;
  msg->w = 1.0;
  return true;
}

void geometry_msgs__msg__Quaternion__fini(geometry_msgs__msg__Quaternion * msg)
{
  (void)msg;
}

geometry_msgs__msg__Quaternion * geometry_msgs__msg__Quaternion__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__Quaternion * msg =
    (geometry_msgs__msg__Quaternion *)allocator.allocate(
      sizeof(geometry_msgs__msg__Quaternion), allocator.state);
  if (!msg) { return NULL; }
  if (!geometry_msgs__msg__Quaternion__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void geometry_msgs__msg__Quaternion__destroy(geometry_msgs__msg__Quaternion * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__Quaternion__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool geometry_msgs__msg__Quaternion__Sequence__init(
  geometry_msgs__msg__Quaternion__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (geometry_msgs__msg__Quaternion *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__Quaternion), allocator.state);
    if (!array->data) { return false; }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void geometry_msgs__msg__Quaternion__Sequence__fini(
  geometry_msgs__msg__Quaternion__Sequence * array)
{
  if (!array || !array->data) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
