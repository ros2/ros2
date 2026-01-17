// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/OccupancyGrid functions

#include "nav_msgs/msg/occupancy_grid.h"
#include "rcutils/allocator.h"
#include <string.h>

bool nav_msgs__msg__OccupancyGrid__init(nav_msgs__msg__OccupancyGrid * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  std_msgs__msg__Header__init(&msg->header);
  nav_msgs__msg__MapMetaData__init(&msg->info);
  rosidl_runtime_c__int8__Sequence__init(&msg->data, 0);
  return true;
}

void nav_msgs__msg__OccupancyGrid__fini(nav_msgs__msg__OccupancyGrid * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  nav_msgs__msg__MapMetaData__fini(&msg->info);
  rosidl_runtime_c__int8__Sequence__fini(&msg->data);
}

nav_msgs__msg__OccupancyGrid * nav_msgs__msg__OccupancyGrid__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__msg__OccupancyGrid * msg = (nav_msgs__msg__OccupancyGrid *)allocator.allocate(
    sizeof(nav_msgs__msg__OccupancyGrid), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!nav_msgs__msg__OccupancyGrid__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void nav_msgs__msg__OccupancyGrid__destroy(nav_msgs__msg__OccupancyGrid * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__msg__OccupancyGrid__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool nav_msgs__msg__OccupancyGrid__Sequence__init(
  nav_msgs__msg__OccupancyGrid__Sequence * array, size_t size)
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

  array->data = (nav_msgs__msg__OccupancyGrid *)allocator.zero_allocate(
    size, sizeof(nav_msgs__msg__OccupancyGrid), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!nav_msgs__msg__OccupancyGrid__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        nav_msgs__msg__OccupancyGrid__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void nav_msgs__msg__OccupancyGrid__Sequence__fini(
  nav_msgs__msg__OccupancyGrid__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    nav_msgs__msg__OccupancyGrid__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
