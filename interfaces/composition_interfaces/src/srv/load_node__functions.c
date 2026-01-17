// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/LoadNode functions

#include "composition_interfaces/srv/load_node.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// LoadNode Request
// =============================================================================

bool composition_interfaces__srv__LoadNode__Request__init(
  composition_interfaces__srv__LoadNode__Request * msg)
{
  if (!msg) {
    return false;
  }
  rosidl_runtime_c__String__init(&msg->package_name);
  rosidl_runtime_c__String__init(&msg->plugin_name);
  rosidl_runtime_c__String__init(&msg->node_name);
  rosidl_runtime_c__String__init(&msg->node_namespace);
  msg->log_level = 0;
  msg->remap_rules.data = NULL;
  msg->remap_rules.size = 0;
  msg->remap_rules.capacity = 0;
  msg->parameters.data = NULL;
  msg->parameters.size = 0;
  msg->parameters.capacity = 0;
  msg->extra_arguments.data = NULL;
  msg->extra_arguments.size = 0;
  msg->extra_arguments.capacity = 0;
  return true;
}

void composition_interfaces__srv__LoadNode__Request__fini(
  composition_interfaces__srv__LoadNode__Request * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->package_name);
  rosidl_runtime_c__String__fini(&msg->plugin_name);
  rosidl_runtime_c__String__fini(&msg->node_name);
  rosidl_runtime_c__String__fini(&msg->node_namespace);
  rosidl_runtime_c__String__Sequence__fini(&msg->remap_rules);
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->parameters);
  rosidl_runtime_c__String__Sequence__fini(&msg->extra_arguments);
}

composition_interfaces__srv__LoadNode__Request *
composition_interfaces__srv__LoadNode__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__LoadNode__Request * msg =
    (composition_interfaces__srv__LoadNode__Request *)allocator.allocate(
      sizeof(composition_interfaces__srv__LoadNode__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!composition_interfaces__srv__LoadNode__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void composition_interfaces__srv__LoadNode__Request__destroy(
  composition_interfaces__srv__LoadNode__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__LoadNode__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// =============================================================================
// LoadNode Response
// =============================================================================

bool composition_interfaces__srv__LoadNode__Response__init(
  composition_interfaces__srv__LoadNode__Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->success = false;
  rosidl_runtime_c__String__init(&msg->error_message);
  rosidl_runtime_c__String__init(&msg->full_node_name);
  msg->unique_id = 0;
  return true;
}

void composition_interfaces__srv__LoadNode__Response__fini(
  composition_interfaces__srv__LoadNode__Response * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->error_message);
  rosidl_runtime_c__String__fini(&msg->full_node_name);
}

composition_interfaces__srv__LoadNode__Response *
composition_interfaces__srv__LoadNode__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__LoadNode__Response * msg =
    (composition_interfaces__srv__LoadNode__Response *)allocator.allocate(
      sizeof(composition_interfaces__srv__LoadNode__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!composition_interfaces__srv__LoadNode__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void composition_interfaces__srv__LoadNode__Response__destroy(
  composition_interfaces__srv__LoadNode__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  composition_interfaces__srv__LoadNode__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
