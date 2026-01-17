// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/SetParametersAtomically functions

#include "rcl_interfaces/srv/set_parameters_atomically.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// SetParametersAtomically Request
// =============================================================================

bool rcl_interfaces__srv__SetParametersAtomically__Request__init(rcl_interfaces__srv__SetParametersAtomically__Request * msg)
{
  if (!msg) {
    return false;
  }
  // parameters sequence initialized to empty
  return true;
}

void rcl_interfaces__srv__SetParametersAtomically__Request__fini(rcl_interfaces__srv__SetParametersAtomically__Request * msg)
{
  if (!msg) {
    return;
  }
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->parameters);
}

rcl_interfaces__srv__SetParametersAtomically__Request * rcl_interfaces__srv__SetParametersAtomically__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParametersAtomically__Request * msg = (rcl_interfaces__srv__SetParametersAtomically__Request *)allocator.allocate(
    sizeof(rcl_interfaces__srv__SetParametersAtomically__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__SetParametersAtomically__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__SetParametersAtomically__Request__destroy(rcl_interfaces__srv__SetParametersAtomically__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParametersAtomically__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// SetParametersAtomically Response
// =============================================================================

bool rcl_interfaces__srv__SetParametersAtomically__Response__init(rcl_interfaces__srv__SetParametersAtomically__Response * msg)
{
  if (!msg) {
    return false;
  }
  rcl_interfaces__msg__SetParametersResult__init(&msg->result);
  return true;
}

void rcl_interfaces__srv__SetParametersAtomically__Response__fini(rcl_interfaces__srv__SetParametersAtomically__Response * msg)
{
  if (!msg) {
    return;
  }
  rcl_interfaces__msg__SetParametersResult__fini(&msg->result);
}

rcl_interfaces__srv__SetParametersAtomically__Response * rcl_interfaces__srv__SetParametersAtomically__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParametersAtomically__Response * msg = (rcl_interfaces__srv__SetParametersAtomically__Response *)allocator.allocate(
    sizeof(rcl_interfaces__srv__SetParametersAtomically__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__SetParametersAtomically__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__SetParametersAtomically__Response__destroy(rcl_interfaces__srv__SetParametersAtomically__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetParametersAtomically__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
