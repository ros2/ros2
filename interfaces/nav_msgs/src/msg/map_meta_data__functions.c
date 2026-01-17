// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/MapMetaData functions

#include "nav_msgs/msg/map_meta_data.h"
#include "rcutils/allocator.h"
#include <string.h>

bool nav_msgs__msg__MapMetaData__init(nav_msgs__msg__MapMetaData * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  builtin_interfaces__msg__Time__init(&msg->map_load_time);
  msg->resolution = 0.0f;
  msg->width = 0;
  msg->height = 0;
  geometry_msgs__msg__Pose__init(&msg->origin);
  return true;
}

void nav_msgs__msg__MapMetaData__fini(nav_msgs__msg__MapMetaData * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->map_load_time);
  geometry_msgs__msg__Pose__fini(&msg->origin);
}

nav_msgs__msg__MapMetaData * nav_msgs__msg__MapMetaData__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__msg__MapMetaData * msg = (nav_msgs__msg__MapMetaData *)allocator.allocate(
    sizeof(nav_msgs__msg__MapMetaData), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!nav_msgs__msg__MapMetaData__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void nav_msgs__msg__MapMetaData__destroy(nav_msgs__msg__MapMetaData * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__msg__MapMetaData__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool nav_msgs__msg__MapMetaData__Sequence__init(
  nav_msgs__msg__MapMetaData__Sequence * array, size_t size)
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

  array->data = (nav_msgs__msg__MapMetaData *)allocator.zero_allocate(
    size, sizeof(nav_msgs__msg__MapMetaData), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!nav_msgs__msg__MapMetaData__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        nav_msgs__msg__MapMetaData__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void nav_msgs__msg__MapMetaData__Sequence__fini(
  nav_msgs__msg__MapMetaData__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    nav_msgs__msg__MapMetaData__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
