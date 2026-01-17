#!/usr/bin/env python3
"""Generate lifecycle_msgs service source files."""

import os

BASE_DIR = "/home/jiusi/M-DDS/ohos_ros2/interfaces/lifecycle_msgs"
PKG = "lifecycle_msgs"

def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  Created: {path}")


# ============================================================================
# Service function implementations
# ============================================================================

CHANGE_STATE_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
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
'''

GET_AVAILABLE_STATES_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetAvailableStates functions

#include "lifecycle_msgs/srv/get_available_states.h"
#include "rcutils/allocator.h"
#include <string.h>

// Request
bool lifecycle_msgs__srv__GetAvailableStates__Request__init(lifecycle_msgs__srv__GetAvailableStates__Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void lifecycle_msgs__srv__GetAvailableStates__Request__fini(lifecycle_msgs__srv__GetAvailableStates__Request * msg)
{
  (void)msg;
}

lifecycle_msgs__srv__GetAvailableStates__Request * lifecycle_msgs__srv__GetAvailableStates__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableStates__Request * msg = (lifecycle_msgs__srv__GetAvailableStates__Request *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetAvailableStates__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetAvailableStates__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetAvailableStates__Request__destroy(lifecycle_msgs__srv__GetAvailableStates__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableStates__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// Response
bool lifecycle_msgs__srv__GetAvailableStates__Response__init(lifecycle_msgs__srv__GetAvailableStates__Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->available_states.data = NULL;
  msg->available_states.size = 0;
  msg->available_states.capacity = 0;
  return true;
}

void lifecycle_msgs__srv__GetAvailableStates__Response__fini(lifecycle_msgs__srv__GetAvailableStates__Response * msg)
{
  if (!msg) {
    return;
  }
  lifecycle_msgs__msg__State__Sequence__fini(&msg->available_states);
}

lifecycle_msgs__srv__GetAvailableStates__Response * lifecycle_msgs__srv__GetAvailableStates__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableStates__Response * msg = (lifecycle_msgs__srv__GetAvailableStates__Response *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetAvailableStates__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetAvailableStates__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetAvailableStates__Response__destroy(lifecycle_msgs__srv__GetAvailableStates__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableStates__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
'''

GET_AVAILABLE_TRANSITIONS_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetAvailableTransitions functions

#include "lifecycle_msgs/srv/get_available_transitions.h"
#include "rcutils/allocator.h"
#include <string.h>

// Request
bool lifecycle_msgs__srv__GetAvailableTransitions__Request__init(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Request__fini(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg)
{
  (void)msg;
}

lifecycle_msgs__srv__GetAvailableTransitions__Request * lifecycle_msgs__srv__GetAvailableTransitions__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Request * msg = (lifecycle_msgs__srv__GetAvailableTransitions__Request *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetAvailableTransitions__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetAvailableTransitions__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Request__destroy(lifecycle_msgs__srv__GetAvailableTransitions__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// Response
bool lifecycle_msgs__srv__GetAvailableTransitions__Response__init(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg)
{
  if (!msg) {
    return false;
  }
  msg->available_transitions.data = NULL;
  msg->available_transitions.size = 0;
  msg->available_transitions.capacity = 0;
  return true;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Response__fini(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg)
{
  if (!msg) {
    return;
  }
  lifecycle_msgs__msg__TransitionDescription__Sequence__fini(&msg->available_transitions);
}

lifecycle_msgs__srv__GetAvailableTransitions__Response * lifecycle_msgs__srv__GetAvailableTransitions__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Response * msg = (lifecycle_msgs__srv__GetAvailableTransitions__Response *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetAvailableTransitions__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetAvailableTransitions__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetAvailableTransitions__Response__destroy(lifecycle_msgs__srv__GetAvailableTransitions__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetAvailableTransitions__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
'''

GET_STATE_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetState functions

#include "lifecycle_msgs/srv/get_state.h"
#include "rcutils/allocator.h"
#include <string.h>

// Request
bool lifecycle_msgs__srv__GetState__Request__init(lifecycle_msgs__srv__GetState__Request * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void lifecycle_msgs__srv__GetState__Request__fini(lifecycle_msgs__srv__GetState__Request * msg)
{
  (void)msg;
}

lifecycle_msgs__srv__GetState__Request * lifecycle_msgs__srv__GetState__Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Request * msg = (lifecycle_msgs__srv__GetState__Request *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetState__Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetState__Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetState__Request__destroy(lifecycle_msgs__srv__GetState__Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

// Response
bool lifecycle_msgs__srv__GetState__Response__init(lifecycle_msgs__srv__GetState__Response * msg)
{
  if (!msg) {
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->current_state)) {
    return false;
  }
  return true;
}

void lifecycle_msgs__srv__GetState__Response__fini(lifecycle_msgs__srv__GetState__Response * msg)
{
  if (!msg) {
    return;
  }
  lifecycle_msgs__msg__State__fini(&msg->current_state);
}

lifecycle_msgs__srv__GetState__Response * lifecycle_msgs__srv__GetState__Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Response * msg = (lifecycle_msgs__srv__GetState__Response *)allocator.allocate(
    sizeof(lifecycle_msgs__srv__GetState__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__srv__GetState__Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__srv__GetState__Response__destroy(lifecycle_msgs__srv__GetState__Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__GetState__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}
'''


def generate_type_support_c(name):
    """Generate C type support file for service."""
    snake = name.lower()
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{name} type support

#include "{PKG}/srv/{snake}.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t {PKG}__srv__{name}__Request__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, srv, {name}_Request)()
{{
  return &{PKG}__srv__{name}__Request__type_support_handle;
}}

// Response type support
static rosidl_message_type_support_t {PKG}__srv__{name}__Response__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, srv, {name}_Response)()
{{
  return &{PKG}__srv__{name}__Response__type_support_handle;
}}

// Service type support
static rosidl_service_type_support_t {PKG}__srv__{name}__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, srv, {name})()
{{
  return &{PKG}__srv__{name}__type_support_handle;
}}
'''


def generate_cpp_type_support(name):
    """Generate C++ type support file for service."""
    snake = name.lower()
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{name} C++ type support

#include "{PKG}/srv/{snake}.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace rosidl_typesupport_cpp
{{

template<>
const rosidl_service_type_support_t *
get_service_type_support_handle<{PKG}::srv::{name}>()
{{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, {PKG}, srv, {name})();
}}

}}  // namespace rosidl_typesupport_cpp
'''


def generate_fastrtps_c(name):
    """Generate FastRTPS C type support file for service."""
    snake = name.lower()
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{name} FastRTPS C type support

#include "{PKG}/srv/{snake}.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{{

// Request type support
static const rosidl_message_type_support_t {PKG}__srv__{name}__Request__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, srv, {name}_Request)()
{{
  return &{PKG}__srv__{name}__Request__fastrtps_type_support;
}}

// Response type support
static const rosidl_message_type_support_t {PKG}__srv__{name}__Response__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, srv, {name}_Response)()
{{
  return &{PKG}__srv__{name}__Response__fastrtps_type_support;
}}

// Service type support
static const rosidl_service_type_support_t {PKG}__srv__{name}__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, srv, {name})()
{{
  return &{PKG}__srv__{name}__fastrtps_type_support;
}}

}}  // extern "C"
'''


def main():
    print(f"Generating {PKG} service source files...")
    
    # Service function files
    print("\nWriting service functions:")
    write_file(f"{BASE_DIR}/src/srv/change_state__functions.c", CHANGE_STATE_FUNCTIONS)
    write_file(f"{BASE_DIR}/src/srv/get_available_states__functions.c", GET_AVAILABLE_STATES_FUNCTIONS)
    write_file(f"{BASE_DIR}/src/srv/get_available_transitions__functions.c", GET_AVAILABLE_TRANSITIONS_FUNCTIONS)
    write_file(f"{BASE_DIR}/src/srv/get_state__functions.c", GET_STATE_FUNCTIONS)
    
    # Service type support
    print("\nWriting service type support:")
    services = ["ChangeState", "GetAvailableStates", "GetAvailableTransitions", "GetState"]
    for srv in services:
        snake = srv.lower()
        if srv == "ChangeState":
            snake = "change_state"
        elif srv == "GetAvailableStates":
            snake = "get_available_states"
        elif srv == "GetAvailableTransitions":
            snake = "get_available_transitions"
        elif srv == "GetState":
            snake = "get_state"
        
        write_file(f"{BASE_DIR}/src/srv/{snake}__type_support.c", generate_type_support_c(srv))
        write_file(f"{BASE_DIR}/src/srv/{snake}__type_support.cpp", generate_cpp_type_support(srv))
        write_file(f"{BASE_DIR}/src/srv/{snake}__rosidl_typesupport_fastrtps_c.cpp", generate_fastrtps_c(srv))
    
    print(f"\nGeneration complete!")


if __name__ == "__main__":
    main()
