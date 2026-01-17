// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/ListNodes functions

#include "composition_interfaces/srv/list_nodes.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// ListNodes Request
// =============================================================================

bool composition_interfaces__srv__ListNodes__Request__init(
  composition_interfaces__srv__ListNodes__Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void composition_interfaces__srv__ListNodes__Request__fini(
  composition_interfaces__srv__ListNodes__Request * msg)
{
  (void)msg;
}

composition_interfaces__srv__ListNodes__Request *
composition_interfaces__srv__ListNodes__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__ListNodes__Request * msg =
    (composition_interfaces__srv__ListNodes__Request *)allocator.allocate(
      sizeof(composition_interfaces__srv__ListNodes__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!composition_interfaces__srv__ListNodes__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void composition_interfaces__srv__ListNodes__Request__destroy(
  composition_interfaces__srv__ListNodes__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__ListNodes__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// ListNodes Response
// =============================================================================

bool composition_interfaces__srv__ListNodes__Response__init(
  composition_interfaces__srv__ListNodes__Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->full_node_names.data = NULL;
  msg->full_node_names.size = 0;
  msg->full_node_names.capacity = 0;
  msg->unique_ids.data = NULL;
  msg->unique_ids.size = 0;
  msg->unique_ids.capacity = 0;
  return true;
}

void composition_interfaces__srv__ListNodes__Response__fini(
  composition_interfaces__srv__ListNodes__Response * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__Sequence__fini(&msg->full_node_names);
  rosidl_runtime_c__uint64__Sequence__fini(&msg->unique_ids);
}

composition_interfaces__srv__ListNodes__Response *
composition_interfaces__srv__ListNodes__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__ListNodes__Response * msg =
    (composition_interfaces__srv__ListNodes__Response *)allocator.allocate(
      sizeof(composition_interfaces__srv__ListNodes__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!composition_interfaces__srv__ListNodes__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void composition_interfaces__srv__ListNodes__Response__destroy(
  composition_interfaces__srv__ListNodes__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__ListNodes__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
