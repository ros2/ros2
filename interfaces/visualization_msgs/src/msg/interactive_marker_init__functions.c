// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerInit functions

#include "visualization_msgs/msg/interactive_marker_init.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__InteractiveMarkerInit__init(visualization_msgs__msg__InteractiveMarkerInit * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__String__init(&msg->server_id);
  msg->seq_num = 0;
  visualization_msgs__msg__InteractiveMarker__Sequence__init(&msg->markers, 0);
  return true;
}

void visualization_msgs__msg__InteractiveMarkerInit__fini(visualization_msgs__msg__InteractiveMarkerInit * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->server_id);
  visualization_msgs__msg__InteractiveMarker__Sequence__fini(&msg->markers);
}

visualization_msgs__msg__InteractiveMarkerInit * visualization_msgs__msg__InteractiveMarkerInit__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarkerInit * msg = (visualization_msgs__msg__InteractiveMarkerInit *)allocator.allocate(
    sizeof(visualization_msgs__msg__InteractiveMarkerInit), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__InteractiveMarkerInit__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__InteractiveMarkerInit__destroy(visualization_msgs__msg__InteractiveMarkerInit * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarkerInit__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__InteractiveMarkerInit__Sequence__init(
  visualization_msgs__msg__InteractiveMarkerInit__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__InteractiveMarkerInit *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__InteractiveMarkerInit), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__InteractiveMarkerInit__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__InteractiveMarkerInit__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__InteractiveMarkerInit__Sequence__fini(
  visualization_msgs__msg__InteractiveMarkerInit__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__InteractiveMarkerInit__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
