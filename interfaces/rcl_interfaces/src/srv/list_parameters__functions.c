// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/ListParameters functions

#include "rcl_interfaces/srv/list_parameters.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// ListParameters Request
// =============================================================================

bool rcl_interfaces__srv__ListParameters__Request__init(rcl_interfaces__srv__ListParameters__Request * msg)
{
  if (!msg) {
    return false;
  }
  // prefixes sequence initialized to empty
  msg->depth = 0;
  return true;
}

void rcl_interfaces__srv__ListParameters__Request__fini(rcl_interfaces__srv__ListParameters__Request * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__Sequence__fini(&msg->prefixes);
}

rcl_interfaces__srv__ListParameters__Request * rcl_interfaces__srv__ListParameters__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__ListParameters__Request * msg = (rcl_interfaces__srv__ListParameters__Request *)allocator.allocate(
    sizeof(rcl_interfaces__srv__ListParameters__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__ListParameters__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__ListParameters__Request__destroy(rcl_interfaces__srv__ListParameters__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__ListParameters__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// ListParameters Response
// =============================================================================

bool rcl_interfaces__srv__ListParameters__Response__init(rcl_interfaces__srv__ListParameters__Response * msg)
{
  if (!msg) {
    return false;
  }
  rcl_interfaces__msg__ListParametersResult__init(&msg->result);
  return true;
}

void rcl_interfaces__srv__ListParameters__Response__fini(rcl_interfaces__srv__ListParameters__Response * msg)
{
  if (!msg) {
    return;
  }
  rcl_interfaces__msg__ListParametersResult__fini(&msg->result);
}

rcl_interfaces__srv__ListParameters__Response * rcl_interfaces__srv__ListParameters__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__ListParameters__Response * msg = (rcl_interfaces__srv__ListParameters__Response *)allocator.allocate(
    sizeof(rcl_interfaces__srv__ListParameters__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__ListParameters__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__ListParameters__Response__destroy(rcl_interfaces__srv__ListParameters__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__ListParameters__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
