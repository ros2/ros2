// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetAvailableTransitions functions

#include "lifecycle_msgs/srv/get_available_transitions.h"
#include "rcutils/allocator.h"
#include <string.h>

// Request
bool lifecycle_msgs__srv__GetAvailableTransitions__Request__init(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Request__fini(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg)
{
  (void)msg;
}

lifecycle_msgs__srv__GetAvailableTransitions__Request * lifecycle_msgs__srv__GetAvailableTransitions__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Request * msg = (lifecycle_msgs__srv__GetAvailableTransitions__Request *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetAvailableTransitions__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetAvailableTransitions__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Request__destroy(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// Response
bool lifecycle_msgs__srv__GetAvailableTransitions__Response__init(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->available_transitions.data = NULL;
  msg->available_transitions.size = 0;
  msg->available_transitions.capacity = 0;
  return true;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Response__fini(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg)
{
  if (!msg) {
    return;
  }
  lifecycle_msgs__msg__TransitionDescription__Sequence__fini(&msg->available_transitions);
}

lifecycle_msgs__srv__GetAvailableTransitions__Response * lifecycle_msgs__srv__GetAvailableTransitions__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Response * msg = (lifecycle_msgs__srv__GetAvailableTransitions__Response *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetAvailableTransitions__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetAvailableTransitions__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Response__destroy(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
