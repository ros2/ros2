// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/MeshTriangle functions

#include "shape_msgs/msg/mesh_triangle.h"
#include "rcutils/allocator.h"
#include <string.h>

bool shape_msgs__msg__MeshTriangle__init(shape_msgs__msg__MeshTriangle * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  msg->vertex_indices[0] = 0;
  msg->vertex_indices[1] = 0;
  msg->vertex_indices[2] = 0;
  return true;
}

void shape_msgs__msg__MeshTriangle__fini(shape_msgs__msg__MeshTriangle * msg)
{
  if (!msg) {
    return;
  }

}

shape_msgs__msg__MeshTriangle * shape_msgs__msg__MeshTriangle__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  shape_msgs__msg__MeshTriangle * msg = (shape_msgs__msg__MeshTriangle *)allocator.allocate(
    sizeof(shape_msgs__msg__MeshTriangle), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!shape_msgs__msg__MeshTriangle__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void shape_msgs__msg__MeshTriangle__destroy(shape_msgs__msg__MeshTriangle * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  shape_msgs__msg__MeshTriangle__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool shape_msgs__msg__MeshTriangle__Sequence__init(
  shape_msgs__msg__MeshTriangle__Sequence * array, size_t size)
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

  array->data = (shape_msgs__msg__MeshTriangle *)allocator.zero_allocate(
    size, sizeof(shape_msgs__msg__MeshTriangle), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!shape_msgs__msg__MeshTriangle__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        shape_msgs__msg__MeshTriangle__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void shape_msgs__msg__MeshTriangle__Sequence__fini(
  shape_msgs__msg__MeshTriangle__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    shape_msgs__msg__MeshTriangle__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
