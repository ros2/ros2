// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/TransformStamped functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/transform_stamped.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"

bool geometry_msgs__msg__TransformStamped__init(geometry_msgs__msg__TransformStamped * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) {
    return false;
  }
  if (!geometry_msgs__msg__Transform__init(&msg->transform)) {
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }
  if (!rosidl_runtime_c__String__init(&msg->child_frame_id)) {
    geometry_msgs__msg__Transform__fini(&msg->transform);
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }
  return true;
}

void geometry_msgs__msg__TransformStamped__fini(geometry_msgs__msg__TransformStamped * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->child_frame_id);
  geometry_msgs__msg__Transform__fini(&msg->transform);
}

geometry_msgs__msg__TransformStamped * geometry_msgs__msg__TransformStamped__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__TransformStamped * msg =
    (geometry_msgs__msg__TransformStamped *)allocator.allocate(
      sizeof(geometry_msgs__msg__TransformStamped), allocator.state);
  if (!msg) { return NULL; }
  if (!geometry_msgs__msg__TransformStamped__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void geometry_msgs__msg__TransformStamped__destroy(geometry_msgs__msg__TransformStamped * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__TransformStamped__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool geometry_msgs__msg__TransformStamped__Sequence__init(
  geometry_msgs__msg__TransformStamped__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (geometry_msgs__msg__TransformStamped *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__TransformStamped), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!geometry_msgs__msg__TransformStamped__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          geometry_msgs__msg__TransformStamped__fini(&array->data[j]);
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

void geometry_msgs__msg__TransformStamped__Sequence__fini(
  geometry_msgs__msg__TransformStamped__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      geometry_msgs__msg__TransformStamped__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
