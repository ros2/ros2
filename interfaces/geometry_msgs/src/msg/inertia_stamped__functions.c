// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/InertiaStamped functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/inertia_stamped.h"
#include "rcutils/allocator.h"


bool geometry_msgs__msg__InertiaStamped__init(geometry_msgs__msg__InertiaStamped * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) {
    return false;
  }
  if (!geometry_msgs__msg__Inertia__init(&msg->inertia)) {
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }

  return true;
}

void geometry_msgs__msg__InertiaStamped__fini(geometry_msgs__msg__InertiaStamped * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);

  geometry_msgs__msg__Inertia__fini(&msg->inertia);
}

geometry_msgs__msg__InertiaStamped * geometry_msgs__msg__InertiaStamped__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__InertiaStamped * msg =
    (geometry_msgs__msg__InertiaStamped *)allocator.allocate(
      sizeof(geometry_msgs__msg__InertiaStamped), allocator.state);
  if (!msg) { return NULL; }
  if (!geometry_msgs__msg__InertiaStamped__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void geometry_msgs__msg__InertiaStamped__destroy(geometry_msgs__msg__InertiaStamped * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__InertiaStamped__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool geometry_msgs__msg__InertiaStamped__Sequence__init(
  geometry_msgs__msg__InertiaStamped__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (geometry_msgs__msg__InertiaStamped *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__InertiaStamped), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!geometry_msgs__msg__InertiaStamped__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          geometry_msgs__msg__InertiaStamped__fini(&array->data[j]);
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

void geometry_msgs__msg__InertiaStamped__Sequence__fini(
  geometry_msgs__msg__InertiaStamped__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      geometry_msgs__msg__InertiaStamped__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
