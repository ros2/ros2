// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/ChangeState functions

#include "lifecycle_msgs/srv/change_state.h"
#include "rcutils/allocator.h"
#include <string.h>

// Request
bool lifecycle_msgs__srv__ChangeState__Request__init(lifecycle_msgs__srv__ChangeState__Request * msg)
{
  if (!msg) {
    return false;
  }
  if (!lifecycle_msgs__msg__Transition__init(&msg->transition)) {
    return false;
  }
  return true;
}

void lifecycle_msgs__srv__ChangeState__Request__fini(lifecycle_msgs__srv__ChangeState__Request * msg)
{
  if (!msg) {
    return;
  }
  lifecycle_msgs__msg__Transition__fini(&msg->transition);
}

lifecycle_msgs__srv__ChangeState__Request * lifecycle_msgs__srv__ChangeState__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState__Request * msg = (lifecycle_msgs__srv__ChangeState__Request *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__ChangeState__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__ChangeState__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__ChangeState__Request__destroy(lifecycle_msgs__srv__ChangeState__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// Response
bool lifecycle_msgs__srv__ChangeState__Response__init(lifecycle_msgs__srv__ChangeState__Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->success = false;
  return true;
}

void lifecycle_msgs__srv__ChangeState__Response__fini(lifecycle_msgs__srv__ChangeState__Response * msg)
{
  (void)msg;
}

lifecycle_msgs__srv__ChangeState__Response * lifecycle_msgs__srv__ChangeState__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState__Response * msg = (lifecycle_msgs__srv__ChangeState__Response *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__ChangeState__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__ChangeState__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__ChangeState__Response__destroy(lifecycle_msgs__srv__ChangeState__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
