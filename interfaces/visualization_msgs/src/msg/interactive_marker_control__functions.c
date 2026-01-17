// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerControl functions

#include "visualization_msgs/msg/interactive_marker_control.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__InteractiveMarkerControl__init(visualization_msgs__msg__InteractiveMarkerControl * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__String__init(&msg->name);
  geometry_msgs__msg__Quaternion__init(&msg->orientation);
  msg->orientation_mode = 0;
  msg->interaction_mode = 0;
  msg->always_visible = false;
  visualization_msgs__msg__Marker__Sequence__init(&msg->markers, 0);
  msg->independent_marker_orientation = false;
  rosidl_runtime_c__String__init(&msg->description);
  return true;
}

void visualization_msgs__msg__InteractiveMarkerControl__fini(visualization_msgs__msg__InteractiveMarkerControl * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->name);
  geometry_msgs__msg__Quaternion__fini(&msg->orientation);
  visualization_msgs__msg__Marker__Sequence__fini(&msg->markers);
  rosidl_runtime_c__String__fini(&msg->description);
}

visualization_msgs__msg__InteractiveMarkerControl * visualization_msgs__msg__InteractiveMarkerControl__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarkerControl * msg = (visualization_msgs__msg__InteractiveMarkerControl *)allocator.allocate(
    sizeof(visualization_msgs__msg__InteractiveMarkerControl), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__InteractiveMarkerControl__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__InteractiveMarkerControl__destroy(visualization_msgs__msg__InteractiveMarkerControl * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarkerControl__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__InteractiveMarkerControl__Sequence__init(
  visualization_msgs__msg__InteractiveMarkerControl__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__InteractiveMarkerControl *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__InteractiveMarkerControl), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__InteractiveMarkerControl__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__InteractiveMarkerControl__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__InteractiveMarkerControl__Sequence__fini(
  visualization_msgs__msg__InteractiveMarkerControl__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__InteractiveMarkerControl__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
