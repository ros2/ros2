// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/action/LookupTransform_Feedback functions

#include "tf2_msgs/action/lookup_transform__feedback.h"
#include "rcutils/allocator.h"
#include <string.h>

bool tf2_msgs__action__LookupTransform_Feedback__init(tf2_msgs__action__LookupTransform_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void tf2_msgs__action__LookupTransform_Feedback__fini(tf2_msgs__action__LookupTransform_Feedback * msg)
{
  if (!msg) {
    return;
  }

}

tf2_msgs__action__LookupTransform_Feedback * tf2_msgs__action__LookupTransform_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__action__LookupTransform_Feedback * msg = (tf2_msgs__action__LookupTransform_Feedback *)allocator.allocate(
    sizeof(tf2_msgs__action__LookupTransform_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!tf2_msgs__action__LookupTransform_Feedback__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void tf2_msgs__action__LookupTransform_Feedback__destroy(tf2_msgs__action__LookupTransform_Feedback * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__action__LookupTransform_Feedback__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool tf2_msgs__action__LookupTransform_Feedback__Sequence__init(
  tf2_msgs__action__LookupTransform_Feedback__Sequence * array, size_t size)
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

  array->data = (tf2_msgs__action__LookupTransform_Feedback *)allocator.zero_allocate(
    size, sizeof(tf2_msgs__action__LookupTransform_Feedback), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!tf2_msgs__action__LookupTransform_Feedback__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        tf2_msgs__action__LookupTransform_Feedback__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void tf2_msgs__action__LookupTransform_Feedback__Sequence__fini(
  tf2_msgs__action__LookupTransform_Feedback__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    tf2_msgs__action__LookupTransform_Feedback__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
