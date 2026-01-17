// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/UnloadNode functions

#include "composition_interfaces/srv/unload_node.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// UnloadNode Request
// =============================================================================

bool composition_interfaces__srv__UnloadNode__Request__init(
  composition_interfaces__srv__UnloadNode__Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->unique_id = 0;
  return true;
}

void composition_interfaces__srv__UnloadNode__Request__fini(
  composition_interfaces__srv__UnloadNode__Request * msg)
{
  (void)msg;
}

composition_interfaces__srv__UnloadNode__Request *
composition_interfaces__srv__UnloadNode__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__UnloadNode__Request * msg =
    (composition_interfaces__srv__UnloadNode__Request *)allocator.allocate(
      sizeof(composition_interfaces__srv__UnloadNode__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!composition_interfaces__srv__UnloadNode__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void composition_interfaces__srv__UnloadNode__Request__destroy(
  composition_interfaces__srv__UnloadNode__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__UnloadNode__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// UnloadNode Response
// =============================================================================

bool composition_interfaces__srv__UnloadNode__Response__init(
  composition_interfaces__srv__UnloadNode__Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->success = false;
  rosidl_runtime_c__String__init(&msg->error_message);
  return true;
}

void composition_interfaces__srv__UnloadNode__Response__fini(
  composition_interfaces__srv__UnloadNode__Response * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->error_message);
}

composition_interfaces__srv__UnloadNode__Response *
composition_interfaces__srv__UnloadNode__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__UnloadNode__Response * msg =
    (composition_interfaces__srv__UnloadNode__Response *)allocator.allocate(
      sizeof(composition_interfaces__srv__UnloadNode__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!composition_interfaces__srv__UnloadNode__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void composition_interfaces__srv__UnloadNode__Response__destroy(
  composition_interfaces__srv__UnloadNode__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__UnloadNode__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
