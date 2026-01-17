// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/Mesh functions

#include "shape_msgs/msg/mesh.h"
#include "rcutils/allocator.h"
#include <string.h>

bool shape_msgs__msg__Mesh__init(shape_msgs__msg__Mesh * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  geometry_msgs__msg__Point__Sequence__init(&msg->vertices, 0);
  shape_msgs__msg__MeshTriangle__Sequence__init(&msg->triangles, 0);
  return true;
}

void shape_msgs__msg__Mesh__fini(shape_msgs__msg__Mesh * msg)
{
  if (!msg) {
    return;
  }
  geometry_msgs__msg__Point__Sequence__fini(&msg->vertices);
  shape_msgs__msg__MeshTriangle__Sequence__fini(&msg->triangles);
}

shape_msgs__msg__Mesh * shape_msgs__msg__Mesh__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  shape_msgs__msg__Mesh * msg = (shape_msgs__msg__Mesh *)allocator.allocate(
    sizeof(shape_msgs__msg__Mesh), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!shape_msgs__msg__Mesh__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void shape_msgs__msg__Mesh__destroy(shape_msgs__msg__Mesh * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  shape_msgs__msg__Mesh__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool shape_msgs__msg__Mesh__Sequence__init(
  shape_msgs__msg__Mesh__Sequence * array, size_t size)
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

  array->data = (shape_msgs__msg__Mesh *)allocator.zero_allocate(
    size, sizeof(shape_msgs__msg__Mesh), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!shape_msgs__msg__Mesh__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        shape_msgs__msg__Mesh__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void shape_msgs__msg__Mesh__Sequence__fini(
  shape_msgs__msg__Mesh__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    shape_msgs__msg__Mesh__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
