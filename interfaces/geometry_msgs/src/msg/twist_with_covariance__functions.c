// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/TwistWithCovariance functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "geometry_msgs/msg/twist_with_covariance.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__TwistWithCovariance__init(geometry_msgs__msg__TwistWithCovariance * msg)
{
  if (!msg) { return false; }
  if (!geometry_msgs__msg__Twist__init(&msg->twist)) {
    return false;
  }
  memset(msg->covariance, 0, sizeof(msg->covariance));
  return true;
}

void geometry_msgs__msg__TwistWithCovariance__fini(geometry_msgs__msg__TwistWithCovariance * msg)
{
  if (!msg) { return; }
  geometry_msgs__msg__Twist__fini(&msg->twist);
}

geometry_msgs__msg__TwistWithCovariance * geometry_msgs__msg__TwistWithCovariance__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__TwistWithCovariance * msg =
    (geometry_msgs__msg__TwistWithCovariance *)allocator.allocate(
      sizeof(geometry_msgs__msg__TwistWithCovariance), allocator.state);
  if (!msg) { return NULL; }
  if (!geometry_msgs__msg__TwistWithCovariance__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void geometry_msgs__msg__TwistWithCovariance__destroy(geometry_msgs__msg__TwistWithCovariance * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__TwistWithCovariance__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool geometry_msgs__msg__TwistWithCovariance__Sequence__init(
  geometry_msgs__msg__TwistWithCovariance__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (geometry_msgs__msg__TwistWithCovariance *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__TwistWithCovariance), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!geometry_msgs__msg__TwistWithCovariance__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          geometry_msgs__msg__TwistWithCovariance__fini(&array->data[j]);
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

void geometry_msgs__msg__TwistWithCovariance__Sequence__fini(
  geometry_msgs__msg__TwistWithCovariance__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      geometry_msgs__msg__TwistWithCovariance__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
