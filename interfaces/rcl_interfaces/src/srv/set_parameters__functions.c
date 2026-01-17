// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/SetParameters functions

#include "rcl_interfaces/srv/set_parameters.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// SetParameters Request
// =============================================================================

bool rcl_interfaces__srv__SetParameters__Request__init(rcl_interfaces__srv__SetParameters__Request * msg)
{
  if (!msg) {
    return false;
  }
  // parameters sequence initialized to empty
  return true;
}

void rcl_interfaces__srv__SetParameters__Request__fini(rcl_interfaces__srv__SetParameters__Request * msg)
{
  if (!msg) {
    return;
  }
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->parameters);
}

rcl_interfaces__srv__SetParameters__Request * rcl_interfaces__srv__SetParameters__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParameters__Request * msg = (rcl_interfaces__srv__SetParameters__Request *)allocator.allocate(
    sizeof(rcl_interfaces__srv__SetParameters__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__SetParameters__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__SetParameters__Request__destroy(rcl_interfaces__srv__SetParameters__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParameters__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// SetParameters Response
// =============================================================================

bool rcl_interfaces__srv__SetParameters__Response__init(rcl_interfaces__srv__SetParameters__Response * msg)
{
  if (!msg) {
    return false;
  }
  // results sequence initialized to empty
  return true;
}

void rcl_interfaces__srv__SetParameters__Response__fini(rcl_interfaces__srv__SetParameters__Response * msg)
{
  if (!msg) {
    return;
  }
  rcl_interfaces__msg__SetParametersResult__Sequence__fini(&msg->results);
}

rcl_interfaces__srv__SetParameters__Response * rcl_interfaces__srv__SetParameters__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParameters__Response * msg = (rcl_interfaces__srv__SetParameters__Response *)allocator.allocate(
    sizeof(rcl_interfaces__srv__SetParameters__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__SetParameters__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__SetParameters__Response__destroy(rcl_interfaces__srv__SetParameters__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParameters__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
