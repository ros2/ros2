// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/GetLoggerLevels functions

#include "rcl_interfaces/srv/get_logger_levels.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// GetLoggerLevels Request
// =============================================================================

bool rcl_interfaces__srv__GetLoggerLevels__Request__init(rcl_interfaces__srv__GetLoggerLevels__Request * msg)
{
  if (!msg) {
    return false;
  }
  // names sequence initialized to empty
  return true;
}

void rcl_interfaces__srv__GetLoggerLevels__Request__fini(rcl_interfaces__srv__GetLoggerLevels__Request * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__Sequence__fini(&msg->names);
}

rcl_interfaces__srv__GetLoggerLevels__Request * rcl_interfaces__srv__GetLoggerLevels__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetLoggerLevels__Request * msg = (rcl_interfaces__srv__GetLoggerLevels__Request *)allocator.allocate(
    sizeof(rcl_interfaces__srv__GetLoggerLevels__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__GetLoggerLevels__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__GetLoggerLevels__Request__destroy(rcl_interfaces__srv__GetLoggerLevels__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetLoggerLevels__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// GetLoggerLevels Response
// =============================================================================

bool rcl_interfaces__srv__GetLoggerLevels__Response__init(rcl_interfaces__srv__GetLoggerLevels__Response * msg)
{
  if (!msg) {
    return false;
  }
  // levels sequence initialized to empty
  return true;
}

void rcl_interfaces__srv__GetLoggerLevels__Response__fini(rcl_interfaces__srv__GetLoggerLevels__Response * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__uint8__Sequence__fini(&msg->levels);
}

rcl_interfaces__srv__GetLoggerLevels__Response * rcl_interfaces__srv__GetLoggerLevels__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetLoggerLevels__Response * msg = (rcl_interfaces__srv__GetLoggerLevels__Response *)allocator.allocate(
    sizeof(rcl_interfaces__srv__GetLoggerLevels__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__GetLoggerLevels__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__GetLoggerLevels__Response__destroy(rcl_interfaces__srv__GetLoggerLevels__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__GetLoggerLevels__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
