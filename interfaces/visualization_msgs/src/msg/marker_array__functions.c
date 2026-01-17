// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/MarkerArray functions

#include "visualization_msgs/msg/marker_array.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__MarkerArray__init(visualization_msgs__msg__MarkerArray * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  visualization_msgs__msg__Marker__Sequence__init(&msg->markers, 0);
  return true;
}

void visualization_msgs__msg__MarkerArray__fini(visualization_msgs__msg__MarkerArray * msg)
{
  if (!msg) {
    return;
  }
  visualization_msgs__msg__Marker__Sequence__fini(&msg->markers);
}

visualization_msgs__msg__MarkerArray * visualization_msgs__msg__MarkerArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__MarkerArray * msg = (visualization_msgs__msg__MarkerArray *)allocator.allocate(
    sizeof(visualization_msgs__msg__MarkerArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__MarkerArray__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__MarkerArray__destroy(visualization_msgs__msg__MarkerArray * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__MarkerArray__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__MarkerArray__Sequence__init(
  visualization_msgs__msg__MarkerArray__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__MarkerArray *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__MarkerArray), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__MarkerArray__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__MarkerArray__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__MarkerArray__Sequence__fini(
  visualization_msgs__msg__MarkerArray__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__MarkerArray__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
