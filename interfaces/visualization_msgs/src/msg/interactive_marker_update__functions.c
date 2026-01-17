// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerUpdate functions

#include "visualization_msgs/msg/interactive_marker_update.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__InteractiveMarkerUpdate__init(visualization_msgs__msg__InteractiveMarkerUpdate * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__String__init(&msg->server_id);
  msg->seq_num = 0;
  msg->type = 0;
  visualization_msgs__msg__InteractiveMarker__Sequence__init(&msg->markers, 0);
  visualization_msgs__msg__InteractiveMarkerPose__Sequence__init(&msg->poses, 0);
  rosidl_runtime_c__String__Sequence__init(&msg->erases, 0);
  return true;
}

void visualization_msgs__msg__InteractiveMarkerUpdate__fini(visualization_msgs__msg__InteractiveMarkerUpdate * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->server_id);
  visualization_msgs__msg__InteractiveMarker__Sequence__fini(&msg->markers);
  visualization_msgs__msg__InteractiveMarkerPose__Sequence__fini(&msg->poses);
  rosidl_runtime_c__String__Sequence__fini(&msg->erases);
}

visualization_msgs__msg__InteractiveMarkerUpdate * visualization_msgs__msg__InteractiveMarkerUpdate__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarkerUpdate * msg = (visualization_msgs__msg__InteractiveMarkerUpdate *)allocator.allocate(
    sizeof(visualization_msgs__msg__InteractiveMarkerUpdate), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__InteractiveMarkerUpdate__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__InteractiveMarkerUpdate__destroy(visualization_msgs__msg__InteractiveMarkerUpdate * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarkerUpdate__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__InteractiveMarkerUpdate__Sequence__init(
  visualization_msgs__msg__InteractiveMarkerUpdate__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__InteractiveMarkerUpdate *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__InteractiveMarkerUpdate), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__InteractiveMarkerUpdate__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__InteractiveMarkerUpdate__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__InteractiveMarkerUpdate__Sequence__fini(
  visualization_msgs__msg__InteractiveMarkerUpdate__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__InteractiveMarkerUpdate__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
