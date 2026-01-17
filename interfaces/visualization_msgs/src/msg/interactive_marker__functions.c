// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarker functions

#include "visualization_msgs/msg/interactive_marker.h"
#include "rcutils/allocator.h"
#include <string.h>

bool visualization_msgs__msg__InteractiveMarker__init(visualization_msgs__msg__InteractiveMarker * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  std_msgs__msg__Header__init(&msg->header);
  geometry_msgs__msg__Pose__init(&msg->pose);
  rosidl_runtime_c__String__init(&msg->name);
  rosidl_runtime_c__String__init(&msg->description);
  msg->scale = 1.0f;
  visualization_msgs__msg__MenuEntry__Sequence__init(&msg->menu_entries, 0);
  visualization_msgs__msg__InteractiveMarkerControl__Sequence__init(&msg->controls, 0);
  return true;
}

void visualization_msgs__msg__InteractiveMarker__fini(visualization_msgs__msg__InteractiveMarker * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  geometry_msgs__msg__Pose__fini(&msg->pose);
  rosidl_runtime_c__String__fini(&msg->name);
  rosidl_runtime_c__String__fini(&msg->description);
  visualization_msgs__msg__MenuEntry__Sequence__fini(&msg->menu_entries);
  visualization_msgs__msg__InteractiveMarkerControl__Sequence__fini(&msg->controls);
}

visualization_msgs__msg__InteractiveMarker * visualization_msgs__msg__InteractiveMarker__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarker * msg = (visualization_msgs__msg__InteractiveMarker *)allocator.allocate(
    sizeof(visualization_msgs__msg__InteractiveMarker), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!visualization_msgs__msg__InteractiveMarker__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void visualization_msgs__msg__InteractiveMarker__destroy(visualization_msgs__msg__InteractiveMarker * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  visualization_msgs__msg__InteractiveMarker__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool visualization_msgs__msg__InteractiveMarker__Sequence__init(
  visualization_msgs__msg__InteractiveMarker__Sequence * array, size_t size)
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

  array->data = (visualization_msgs__msg__InteractiveMarker *)allocator.zero_allocate(
    size, sizeof(visualization_msgs__msg__InteractiveMarker), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!visualization_msgs__msg__InteractiveMarker__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        visualization_msgs__msg__InteractiveMarker__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void visualization_msgs__msg__InteractiveMarker__Sequence__fini(
  visualization_msgs__msg__InteractiveMarker__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    visualization_msgs__msg__InteractiveMarker__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
