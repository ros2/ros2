// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Pose functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/pose.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__Pose__init(geometry_msgs__msg__Pose * msg)
{
  if (!msg) { return false; }
  if (!geometry_msgs__msg__Point__init(&msg->position)) { return false; }
  if (!geometry_msgs__msg__Quaternion__init(&msg->orientation)) { return false; }
  return true;
}

void geometry_msgs__msg__Pose__fini(geometry_msgs__msg__Pose * msg)
{
  if (!msg) { return; }
  geometry_msgs__msg__Point__fini(&msg->position);
  geometry_msgs__msg__Quaternion__fini(&msg->orientation);
}

geometry_msgs__msg__Pose * geometry_msgs__msg__Pose__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__Pose * msg =
    (geometry_msgs__msg__Pose *)allocator.allocate(
      sizeof(geometry_msgs__msg__Pose), allocator.state);
  if (!msg) { return NULL; }
  if (!geometry_msgs__msg__Pose__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void geometry_msgs__msg__Pose__destroy(geometry_msgs__msg__Pose * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__Pose__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool geometry_msgs__msg__Pose__Sequence__init(
  geometry_msgs__msg__Pose__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (geometry_msgs__msg__Pose *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__Pose), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!geometry_msgs__msg__Pose__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          geometry_msgs__msg__Pose__fini(&array->data[j]);
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

void geometry_msgs__msg__Pose__Sequence__fini(
  geometry_msgs__msg__Pose__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      geometry_msgs__msg__Pose__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
