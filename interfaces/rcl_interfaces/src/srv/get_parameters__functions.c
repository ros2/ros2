// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/GetParameters functions

#include "rcl_interfaces/srv/get_parameters.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// GetParameters Request
// =============================================================================

bool rcl_interfaces__srv__GetParameters__Request__init(rcl_interfaces__srv__GetParameters__Request * msg)
{
  if (!msg) {
    return false;
  }
  // names sequence initialized to empty
  return true;
}

void rcl_interfaces__srv__GetParameters__Request__fini(rcl_interfaces__srv__GetParameters__Request * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__Sequence__fini(&msg->names);
}

rcl_interfaces__srv__GetParameters__Request * rcl_interfaces__srv__GetParameters__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameters__Request * msg = (rcl_interfaces__srv__GetParameters__Request *)allocator.allocate(
    sizeof(rcl_interfaces__srv__GetParameters__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__GetParameters__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__GetParameters__Request__destroy(rcl_interfaces__srv__GetParameters__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameters__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// GetParameters Response
// =============================================================================

bool rcl_interfaces__srv__GetParameters__Response__init(rcl_interfaces__srv__GetParameters__Response * msg)
{
  if (!msg) {
    return false;
  }
  // values sequence initialized to empty
  return true;
}

void rcl_interfaces__srv__GetParameters__Response__fini(rcl_interfaces__srv__GetParameters__Response * msg)
{
  if (!msg) {
    return;
  }
  rcl_interfaces__msg__ParameterValue__Sequence__fini(&msg->values);
}

rcl_interfaces__srv__GetParameters__Response * rcl_interfaces__srv__GetParameters__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameters__Response * msg = (rcl_interfaces__srv__GetParameters__Response *)allocator.allocate(
    sizeof(rcl_interfaces__srv__GetParameters__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__GetParameters__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__GetParameters__Response__destroy(rcl_interfaces__srv__GetParameters__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetParameters__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
