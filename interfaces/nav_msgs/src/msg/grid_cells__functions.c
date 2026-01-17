// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/GridCells functions

#include "nav_msgs/msg/grid_cells.h"
#include "rcutils/allocator.h"
#include <string.h>

bool nav_msgs__msg__GridCells__init(nav_msgs__msg__GridCells * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  std_msgs__msg__Header__init(&msg->header);
  msg->cell_width = 0.0f;
  msg->cell_height = 0.0f;
  geometry_msgs__msg__Point__Sequence__init(&msg->cells, 0);
  return true;
}

void nav_msgs__msg__GridCells__fini(nav_msgs__msg__GridCells * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  geometry_msgs__msg__Point__Sequence__fini(&msg->cells);
}

nav_msgs__msg__GridCells * nav_msgs__msg__GridCells__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__msg__GridCells * msg = (nav_msgs__msg__GridCells *)allocator.allocate(
    sizeof(nav_msgs__msg__GridCells), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!nav_msgs__msg__GridCells__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void nav_msgs__msg__GridCells__destroy(nav_msgs__msg__GridCells * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  nav_msgs__msg__GridCells__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool nav_msgs__msg__GridCells__Sequence__init(
  nav_msgs__msg__GridCells__Sequence * array, size_t size)
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

  array->data = (nav_msgs__msg__GridCells *)allocator.zero_allocate(
    size, sizeof(nav_msgs__msg__GridCells), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!nav_msgs__msg__GridCells__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        nav_msgs__msg__GridCells__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void nav_msgs__msg__GridCells__Sequence__fini(
  nav_msgs__msg__GridCells__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    nav_msgs__msg__GridCells__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
