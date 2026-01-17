// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/SolidPrimitive functions

#include "shape_msgs/msg/solid_primitive.h"
#include "rcutils/allocator.h"
#include <string.h>

bool shape_msgs__msg__SolidPrimitive__init(shape_msgs__msg__SolidPrimitive * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  msg->type = 0;
  rosidl_runtime_c__double__Sequence__init(&msg->dimensions, 0);
  geometry_msgs__msg__Polygon__init(&msg->polygon);
  return true;
}

void shape_msgs__msg__SolidPrimitive__fini(shape_msgs__msg__SolidPrimitive * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__double__Sequence__fini(&msg->dimensions);
  geometry_msgs__msg__Polygon__fini(&msg->polygon);
}

shape_msgs__msg__SolidPrimitive * shape_msgs__msg__SolidPrimitive__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  shape_msgs__msg__SolidPrimitive * msg = (shape_msgs__msg__SolidPrimitive *)allocator.allocate(
    sizeof(shape_msgs__msg__SolidPrimitive), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!shape_msgs__msg__SolidPrimitive__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void shape_msgs__msg__SolidPrimitive__destroy(shape_msgs__msg__SolidPrimitive * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  shape_msgs__msg__SolidPrimitive__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool shape_msgs__msg__SolidPrimitive__Sequence__init(
  shape_msgs__msg__SolidPrimitive__Sequence * array, size_t size)
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

  array->data = (shape_msgs__msg__SolidPrimitive *)allocator.zero_allocate(
    size, sizeof(shape_msgs__msg__SolidPrimitive), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!shape_msgs__msg__SolidPrimitive__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        shape_msgs__msg__SolidPrimitive__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void shape_msgs__msg__SolidPrimitive__Sequence__fini(
  shape_msgs__msg__SolidPrimitive__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    shape_msgs__msg__SolidPrimitive__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
