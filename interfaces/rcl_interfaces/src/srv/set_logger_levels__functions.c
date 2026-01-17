// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/SetLoggerLevels functions

#include "rcl_interfaces/srv/set_logger_levels.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// SetLoggerLevels Request
// =============================================================================

bool rcl_interfaces__srv__SetLoggerLevels__Request__init(rcl_interfaces__srv__SetLoggerLevels__Request * msg)
{
  if (!msg) {
    return false;
  }
  // Initialize levels sequence (empty)
  return true;
}

void rcl_interfaces__srv__SetLoggerLevels__Request__fini(rcl_interfaces__srv__SetLoggerLevels__Request * msg)
{
  if (!msg) {
    return;
  }
  // Finalize levels sequence
}

rcl_interfaces__srv__SetLoggerLevels__Request * rcl_interfaces__srv__SetLoggerLevels__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetLoggerLevels__Request * msg = (rcl_interfaces__srv__SetLoggerLevels__Request *)allocator.allocate(
    sizeof(rcl_interfaces__srv__SetLoggerLevels__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__SetLoggerLevels__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__SetLoggerLevels__Request__destroy(rcl_interfaces__srv__SetLoggerLevels__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetLoggerLevels__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// SetLoggerLevels Response
// =============================================================================

bool rcl_interfaces__srv__SetLoggerLevels__Response__init(rcl_interfaces__srv__SetLoggerLevels__Response * msg)
{
  if (!msg) {
    return false;
  }
  // Initialize results sequence (empty)
  return true;
}

void rcl_interfaces__srv__SetLoggerLevels__Response__fini(rcl_interfaces__srv__SetLoggerLevels__Response * msg)
{
  if (!msg) {
    return;
  }
  // Finalize results sequence
}

rcl_interfaces__srv__SetLoggerLevels__Response * rcl_interfaces__srv__SetLoggerLevels__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetLoggerLevels__Response * msg = (rcl_interfaces__srv__SetLoggerLevels__Response *)allocator.allocate(
    sizeof(rcl_interfaces__srv__SetLoggerLevels__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__srv__SetLoggerLevels__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__srv__SetLoggerLevels__Response__destroy(rcl_interfaces__srv__SetLoggerLevels__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__srv__SetLoggerLevels__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
