// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/msg/GoalStatus functions

#include "action_msgs/msg/goal_status.h"
#include "rcutils/allocator.h"
#include <string.h>

bool action_msgs__msg__GoalStatus__init(action_msgs__msg__GoalStatus * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  action_msgs__msg__GoalInfo__init(&msg->goal_info);
  msg->status = 0;
  return true;
}

void action_msgs__msg__GoalStatus__fini(action_msgs__msg__GoalStatus * msg)
{
  if (!msg) {
    return;
  }
  action_msgs__msg__GoalInfo__fini(&msg->goal_info);
}

action_msgs__msg__GoalStatus * action_msgs__msg__GoalStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  action_msgs__msg__GoalStatus * msg = (action_msgs__msg__GoalStatus *)allocator.allocate(
    sizeof(action_msgs__msg__GoalStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!action_msgs__msg__GoalStatus__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void action_msgs__msg__GoalStatus__destroy(action_msgs__msg__GoalStatus * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  action_msgs__msg__GoalStatus__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool action_msgs__msg__GoalStatus__Sequence__init(
  action_msgs__msg__GoalStatus__Sequence * array, size_t size)
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

  array->data = (action_msgs__msg__GoalStatus *)allocator.zero_allocate(
    size, sizeof(action_msgs__msg__GoalStatus), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!action_msgs__msg__GoalStatus__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        action_msgs__msg__GoalStatus__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void action_msgs__msg__GoalStatus__Sequence__fini(
  action_msgs__msg__GoalStatus__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    action_msgs__msg__GoalStatus__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
