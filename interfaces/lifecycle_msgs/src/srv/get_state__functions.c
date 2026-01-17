// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetState functions

#include "lifecycle_msgs/srv/get_state.h"
#include "rcutils/allocator.h"
#include <string.h>

// Request
bool lifecycle_msgs__srv__GetState__Request__init(lifecycle_msgs__srv__GetState__Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void lifecycle_msgs__srv__GetState__Request__fini(lifecycle_msgs__srv__GetState__Request * msg)
{
  (void)msg;
}

lifecycle_msgs__srv__GetState__Request * lifecycle_msgs__srv__GetState__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Request * msg = (lifecycle_msgs__srv__GetState__Request *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetState__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetState__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetState__Request__destroy(lifecycle_msgs__srv__GetState__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// Response
bool lifecycle_msgs__srv__GetState__Response__init(lifecycle_msgs__srv__GetState__Response * msg)
{
  if (!msg) {
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->current_state)) {
    return false;
  }
  return true;
}

void lifecycle_msgs__srv__GetState__Response__fini(lifecycle_msgs__srv__GetState__Response * msg)
{
  if (!msg) {
    return;
  }
  lifecycle_msgs__msg__State__fini(&msg->current_state);
}

lifecycle_msgs__srv__GetState__Response * lifecycle_msgs__srv__GetState__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Response * msg = (lifecycle_msgs__srv__GetState__Response *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetState__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetState__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetState__Response__destroy(lifecycle_msgs__srv__GetState__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
