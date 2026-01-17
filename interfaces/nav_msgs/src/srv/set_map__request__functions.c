// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/srv/SetMap_Request functions

#include "nav_msgs/srv/set_map__request.h"
#include "rcutils/allocator.h"
#include <string.h>

bool nav_msgs__srv__SetMap_Request__init(nav_msgs__srv__SetMap_Request * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  nav_msgs__msg__OccupancyGrid__init(&msg->map);
  geometry_msgs__msg__PoseWithCovarianceStamped__init(&msg->initial_pose);
  return true;
}

void nav_msgs__srv__SetMap_Request__fini(nav_msgs__srv__SetMap_Request * msg)
{
  if (!msg) {
    return;
  }
  nav_msgs__msg__OccupancyGrid__fini(&msg->map);
  geometry_msgs__msg__PoseWithCovarianceStamped__fini(&msg->initial_pose);
}

nav_msgs__srv__SetMap_Request * nav_msgs__srv__SetMap_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__srv__SetMap_Request * msg = (nav_msgs__srv__SetMap_Request *)allocator.allocate(
    sizeof(nav_msgs__srv__SetMap_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!nav_msgs__srv__SetMap_Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void nav_msgs__srv__SetMap_Request__destroy(nav_msgs__srv__SetMap_Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__srv__SetMap_Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool nav_msgs__srv__SetMap_Request__Sequence__init(
  nav_msgs__srv__SetMap_Request__Sequence * array, size_t size)
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

  array->data = (nav_msgs__srv__SetMap_Request *)allocator.zero_allocate(
    size, sizeof(nav_msgs__srv__SetMap_Request), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!nav_msgs__srv__SetMap_Request__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        nav_msgs__srv__SetMap_Request__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void nav_msgs__srv__SetMap_Request__Sequence__fini(
  nav_msgs__srv__SetMap_Request__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    nav_msgs__srv__SetMap_Request__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
