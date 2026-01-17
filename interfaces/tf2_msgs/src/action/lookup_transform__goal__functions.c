// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/action/LookupTransform_Goal functions

#include "tf2_msgs/action/lookup_transform__goal.h"
#include "rcutils/allocator.h"
#include <string.h>

bool tf2_msgs__action__LookupTransform_Goal__init(tf2_msgs__action__LookupTransform_Goal * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__String__init(&msg->target_frame);
  rosidl_runtime_c__String__init(&msg->source_frame);
  builtin_interfaces__msg__Time__init(&msg->source_time);
  builtin_interfaces__msg__Duration__init(&msg->timeout);
  builtin_interfaces__msg__Time__init(&msg->target_time);
  rosidl_runtime_c__String__init(&msg->fixed_frame);
  msg->advanced = false;
  return true;
}

void tf2_msgs__action__LookupTransform_Goal__fini(tf2_msgs__action__LookupTransform_Goal * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->target_frame);
  rosidl_runtime_c__String__fini(&msg->source_frame);
  builtin_interfaces__msg__Time__fini(&msg->source_time);
  builtin_interfaces__msg__Duration__fini(&msg->timeout);
  builtin_interfaces__msg__Time__fini(&msg->target_time);
  rosidl_runtime_c__String__fini(&msg->fixed_frame);
}

tf2_msgs__action__LookupTransform_Goal * tf2_msgs__action__LookupTransform_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__action__LookupTransform_Goal * msg = (tf2_msgs__action__LookupTransform_Goal *)allocator.allocate(
    sizeof(tf2_msgs__action__LookupTransform_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!tf2_msgs__action__LookupTransform_Goal__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void tf2_msgs__action__LookupTransform_Goal__destroy(tf2_msgs__action__LookupTransform_Goal * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__action__LookupTransform_Goal__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool tf2_msgs__action__LookupTransform_Goal__Sequence__init(
  tf2_msgs__action__LookupTransform_Goal__Sequence * array, size_t size)
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

  array->data = (tf2_msgs__action__LookupTransform_Goal *)allocator.zero_allocate(
    size, sizeof(tf2_msgs__action__LookupTransform_Goal), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!tf2_msgs__action__LookupTransform_Goal__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        tf2_msgs__action__LookupTransform_Goal__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void tf2_msgs__action__LookupTransform_Goal__Sequence__fini(
  tf2_msgs__action__LookupTransform_Goal__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    tf2_msgs__action__LookupTransform_Goal__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
