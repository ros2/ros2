// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/Marker functions

#include "visualization_msgs/msg/marker.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__Marker__init(visualization_msgs__msg__Marker * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__init(&msg->ns);
  msg->id = 0;
  msg->type = 0;
  msg->action = 0;
  geometry_msgs__msg__Pose__init(&msg->pose);
  geometry_msgs__msg__Vector3__init(&msg->scale);
  std_msgs__msg__ColorRGBA__init(&msg->color);
  builtin_interfaces__msg__Duration__init(&msg->lifetime);
  msg->frame_locked = false;
  geometry_msgs__msg__Point__Sequence__init(&msg->points, 0);
  std_msgs__msg__ColorRGBA__Sequence__init(&msg->colors, 0);
  rosidl_runtime_c__String__init(&msg->texture_resource);
  rosidl_runtime_c__String__init(&msg->text);
  rosidl_runtime_c__String__init(&msg->mesh_resource);
  visualization_msgs__msg__MeshFile__init(&msg->mesh_file);
  visualization_msgs__msg__UVCoordinate__Sequence__init(&msg->uv_coordinates, 0);
  msg->mesh_use_embedded_materials = false;
  return true;
}

void visualization_msgs__msg__Marker__fini(visualization_msgs__msg__Marker * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->ns);
  geometry_msgs__msg__Pose__fini(&msg->pose);
  geometry_msgs__msg__Vector3__fini(&msg->scale);
  std_msgs__msg__ColorRGBA__fini(&msg->color);
  builtin_interfaces__msg__Duration__fini(&msg->lifetime);
  geometry_msgs__msg__Point__Sequence__fini(&msg->points);
  std_msgs__msg__ColorRGBA__Sequence__fini(&msg->colors);
  rosidl_runtime_c__String__fini(&msg->texture_resource);
  rosidl_runtime_c__String__fini(&msg->text);
  rosidl_runtime_c__String__fini(&msg->mesh_resource);
  visualization_msgs__msg__MeshFile__fini(&msg->mesh_file);
  visualization_msgs__msg__UVCoordinate__Sequence__fini(&msg->uv_coordinates);
}

visualization_msgs__msg__Marker * visualization_msgs__msg__Marker__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__Marker * msg = (visualization_msgs__msg__Marker *)allocator.allocate(
    sizeof(visualization_msgs__msg__Marker), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__Marker__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__Marker__destroy(visualization_msgs__msg__Marker * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__Marker__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__Marker__Sequence__init(
  visualization_msgs__msg__Marker__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__Marker *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__Marker), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__Marker__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__Marker__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__Marker__Sequence__fini(
  visualization_msgs__msg__Marker__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__Marker__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
