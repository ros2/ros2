// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/MeshFile functions

#include "visualization_msgs/msg/mesh_file.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__MeshFile__init(visualization_msgs__msg__MeshFile * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__String__init(&msg->filename);
  rosidl_runtime_c__uint8__Sequence__init(&msg->data, 0);
  return true;
}

void visualization_msgs__msg__MeshFile__fini(visualization_msgs__msg__MeshFile * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->filename);
  rosidl_runtime_c__uint8__Sequence__fini(&msg->data);
}

visualization_msgs__msg__MeshFile * visualization_msgs__msg__MeshFile__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__MeshFile * msg = (visualization_msgs__msg__MeshFile *)allocator.allocate(
    sizeof(visualization_msgs__msg__MeshFile), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__MeshFile__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__MeshFile__destroy(visualization_msgs__msg__MeshFile * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__MeshFile__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__MeshFile__Sequence__init(
  visualization_msgs__msg__MeshFile__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__MeshFile *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__MeshFile), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__MeshFile__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__MeshFile__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__MeshFile__Sequence__fini(
  visualization_msgs__msg__MeshFile__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__MeshFile__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
