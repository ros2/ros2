// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Pose2D functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/pose2d.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__Pose2D__init(geometry_msgs__msg__Pose2D * msg)
{
  if (!msg) { return false; }
  msg->x = 0.0;
  msg->y = 0.0;
  msg->theta = 0.0;
  return true;
}

void geometry_msgs__msg__Pose2D__fini(geometry_msgs__msg__Pose2D * msg)
{
  if (!msg) { return; }
  (void)msg;
}

geometry_msgs__msg__Pose2D * geometry_msgs__msg__Pose2D__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__Pose2D * msg =
    (geometry_msgs__msg__Pose2D *)allocator.allocate(
      sizeof(geometry_msgs__msg__Pose2D), allocator.state);
  if (!msg) { return NULL; }
  if (!geometry_msgs__msg__Pose2D__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void geometry_msgs__msg__Pose2D__destroy(geometry_msgs__msg__Pose2D * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__Pose2D__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool geometry_msgs__msg__Pose2D__Sequence__init(
  geometry_msgs__msg__Pose2D__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (geometry_msgs__msg__Pose2D *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__Pose2D), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!geometry_msgs__msg__Pose2D__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          geometry_msgs__msg__Pose2D__fini(&array->data[j]);
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

void geometry_msgs__msg__Pose2D__Sequence__fini(
  geometry_msgs__msg__Pose2D__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      geometry_msgs__msg__Pose2D__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
