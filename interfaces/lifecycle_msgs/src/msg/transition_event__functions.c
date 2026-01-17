// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/TransitionEvent functions

#include "lifecycle_msgs/msg/transition_event.h"
#include "rcutils/allocator.h"
#include <string.h>

bool lifecycle_msgs__msg__TransitionEvent__init(lifecycle_msgs__msg__TransitionEvent * msg)
{
  if (!msg) {
    return false;
  }
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    return false;
  }
  if (!lifecycle_msgs__msg__Transition__init(&msg->transition)) {
    builtin_interfaces__msg__Time__fini(&msg->timestamp);
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->start_state)) {
    lifecycle_msgs__msg__Transition__fini(&msg->transition);
    builtin_interfaces__msg__Time__fini(&msg->timestamp);
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->goal_state)) {
    lifecycle_msgs__msg__State__fini(&msg->start_state);
    lifecycle_msgs__msg__Transition__fini(&msg->transition);
    builtin_interfaces__msg__Time__fini(&msg->timestamp);
    return false;
  }
  return true;
}

void lifecycle_msgs__msg__TransitionEvent__fini(lifecycle_msgs__msg__TransitionEvent * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  lifecycle_msgs__msg__Transition__fini(&msg->transition);
  lifecycle_msgs__msg__State__fini(&msg->start_state);
  lifecycle_msgs__msg__State__fini(&msg->goal_state);
}

lifecycle_msgs__msg__TransitionEvent * lifecycle_msgs__msg__TransitionEvent__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__TransitionEvent * msg = (lifecycle_msgs__msg__TransitionEvent *)allocator.allocate(
    sizeof(lifecycle_msgs__msg__TransitionEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__msg__TransitionEvent__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__msg__TransitionEvent__destroy(lifecycle_msgs__msg__TransitionEvent * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__TransitionEvent__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool lifecycle_msgs__msg__TransitionEvent__Sequence__init(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array, size_t size)
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

  array->data = (lifecycle_msgs__msg__TransitionEvent *)allocator.zero_allocate(
    size, sizeof(lifecycle_msgs__msg__TransitionEvent), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!lifecycle_msgs__msg__TransitionEvent__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        lifecycle_msgs__msg__TransitionEvent__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void lifecycle_msgs__msg__TransitionEvent__Sequence__fini(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    lifecycle_msgs__msg__TransitionEvent__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
