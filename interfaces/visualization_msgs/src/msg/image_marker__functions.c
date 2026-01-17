// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/ImageMarker functions

#include "visualization_msgs/msg/image_marker.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__ImageMarker__init(visualization_msgs__msg__ImageMarker * msg)
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
  geometry_msgs__msg__Point__init(&msg->position);
  msg->scale = 1.0f;
  std_msgs__msg__ColorRGBA__init(&msg->outline_color);
  msg->filled = 0;
  std_msgs__msg__ColorRGBA__init(&msg->fill_color);
  builtin_interfaces__msg__Duration__init(&msg->lifetime);
  geometry_msgs__msg__Point__Sequence__init(&msg->points, 0);
  std_msgs__msg__ColorRGBA__Sequence__init(&msg->outline_colors, 0);
  return true;
}

void visualization_msgs__msg__ImageMarker__fini(visualization_msgs__msg__ImageMarker * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->ns);
  geometry_msgs__msg__Point__fini(&msg->position);
  std_msgs__msg__ColorRGBA__fini(&msg->outline_color);
  std_msgs__msg__ColorRGBA__fini(&msg->fill_color);
  builtin_interfaces__msg__Duration__fini(&msg->lifetime);
  geometry_msgs__msg__Point__Sequence__fini(&msg->points);
  std_msgs__msg__ColorRGBA__Sequence__fini(&msg->outline_colors);
}

visualization_msgs__msg__ImageMarker * visualization_msgs__msg__ImageMarker__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__ImageMarker * msg = (visualization_msgs__msg__ImageMarker *)allocator.allocate(
    sizeof(visualization_msgs__msg__ImageMarker), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__ImageMarker__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__ImageMarker__destroy(visualization_msgs__msg__ImageMarker * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__ImageMarker__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__ImageMarker__Sequence__init(
  visualization_msgs__msg__ImageMarker__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__ImageMarker *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__ImageMarker), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__ImageMarker__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__ImageMarker__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__ImageMarker__Sequence__fini(
  visualization_msgs__msg__ImageMarker__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__ImageMarker__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
