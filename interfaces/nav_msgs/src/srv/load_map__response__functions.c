// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/srv/LoadMap_Response functions

#include "nav_msgs/srv/load_map__response.h"
#include "rcutils/allocator.h"
#include <string.h>

bool nav_msgs__srv__LoadMap_Response__init(nav_msgs__srv__LoadMap_Response * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  nav_msgs__msg__OccupancyGrid__init(&msg->map);
  msg->result = 0;
  return true;
}

void nav_msgs__srv__LoadMap_Response__fini(nav_msgs__srv__LoadMap_Response * msg)
{
  if (!msg) {
    return;
  }
  nav_msgs__msg__OccupancyGrid__fini(&msg->map);
}

nav_msgs__srv__LoadMap_Response * nav_msgs__srv__LoadMap_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__srv__LoadMap_Response * msg = (nav_msgs__srv__LoadMap_Response *)allocator.allocate(
    sizeof(nav_msgs__srv__LoadMap_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!nav_msgs__srv__LoadMap_Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void nav_msgs__srv__LoadMap_Response__destroy(nav_msgs__srv__LoadMap_Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__srv__LoadMap_Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool nav_msgs__srv__LoadMap_Response__Sequence__init(
  nav_msgs__srv__LoadMap_Response__Sequence * array, size_t size)
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

  array->data = (nav_msgs__srv__LoadMap_Response *)allocator.zero_allocate(
    size, sizeof(nav_msgs__srv__LoadMap_Response), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!nav_msgs__srv__LoadMap_Response__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        nav_msgs__srv__LoadMap_Response__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void nav_msgs__srv__LoadMap_Response__Sequence__fini(
  nav_msgs__srv__LoadMap_Response__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    nav_msgs__srv__LoadMap_Response__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
