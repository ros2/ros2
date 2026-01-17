// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/PointStamped functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/point_stamped.h"
#include "rcutils/allocator.h"


bool geometry_msgs__msg__PointStamped__init(geometry_msgs__msg__PointStamped * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) {
    return false;
  }
  if (!geometry_msgs__msg__Point__init(&msg->point)) {
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }

  return true;
}

void geometry_msgs__msg__PointStamped__fini(geometry_msgs__msg__PointStamped * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);

  geometry_msgs__msg__Point__fini(&msg->point);
}

geometry_msgs__msg__PointStamped * geometry_msgs__msg__PointStamped__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__PointStamped * msg =
    (geometry_msgs__msg__PointStamped *)allocator.allocate(
      sizeof(geometry_msgs__msg__PointStamped), allocator.state);
  if (!msg) { return NULL; }
  if (!geometry_msgs__msg__PointStamped__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void geometry_msgs__msg__PointStamped__destroy(geometry_msgs__msg__PointStamped * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__PointStamped__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool geometry_msgs__msg__PointStamped__Sequence__init(
  geometry_msgs__msg__PointStamped__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (geometry_msgs__msg__PointStamped *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__PointStamped), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!geometry_msgs__msg__PointStamped__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          geometry_msgs__msg__PointStamped__fini(&array->data[j]);
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

void geometry_msgs__msg__PointStamped__Sequence__fini(
  geometry_msgs__msg__PointStamped__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      geometry_msgs__msg__PointStamped__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
