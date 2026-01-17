#!/usr/bin/env python3
"""Generate lifecycle_msgs C source files."""

import os

BASE_DIR = "/home/jiusi/M-DDS/ohos_ros2/interfaces/lifecycle_msgs"
PKG = "lifecycle_msgs"

def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  Created: {path}")


# ============================================================================
# Message function implementations
# ============================================================================

STATE_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/State functions

#include "lifecycle_msgs/msg/state.h"
#include "rcutils/allocator.h"
#include <string.h>

bool lifecycle_msgs__msg__State__init(lifecycle_msgs__msg__State * msg)
{
  if (!msg) {
    return false;
  }
  msg->id = 0;
  rosidl_runtime_c__String__init(&msg->label);
  return true;
}

void lifecycle_msgs__msg__State__fini(lifecycle_msgs__msg__State * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->label);
}

lifecycle_msgs__msg__State * lifecycle_msgs__msg__State__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__State * msg = (lifecycle_msgs__msg__State *)allocator.allocate(
    sizeof(lifecycle_msgs__msg__State), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__msg__State__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__msg__State__destroy(lifecycle_msgs__msg__State * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__State__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool lifecycle_msgs__msg__State__Sequence__init(
  lifecycle_msgs__msg__State__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }

  array->data = (lifecycle_msgs__msg__State *)allocator.zero_allocate(
    size, sizeof(lifecycle_msgs__msg__State), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!lifecycle_msgs__msg__State__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        lifecycle_msgs__msg__State__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void lifecycle_msgs__msg__State__Sequence__fini(
  lifecycle_msgs__msg__State__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    lifecycle_msgs__msg__State__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
'''

TRANSITION_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/Transition functions

#include "lifecycle_msgs/msg/transition.h"
#include "rcutils/allocator.h"
#include <string.h>

bool lifecycle_msgs__msg__Transition__init(lifecycle_msgs__msg__Transition * msg)
{
  if (!msg) {
    return false;
  }
  msg->id = 0;
  rosidl_runtime_c__String__init(&msg->label);
  return true;
}

void lifecycle_msgs__msg__Transition__fini(lifecycle_msgs__msg__Transition * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->label);
}

lifecycle_msgs__msg__Transition * lifecycle_msgs__msg__Transition__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__Transition * msg = (lifecycle_msgs__msg__Transition *)allocator.allocate(
    sizeof(lifecycle_msgs__msg__Transition), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__msg__Transition__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__msg__Transition__destroy(lifecycle_msgs__msg__Transition * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__Transition__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool lifecycle_msgs__msg__Transition__Sequence__init(
  lifecycle_msgs__msg__Transition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }

  array->data = (lifecycle_msgs__msg__Transition *)allocator.zero_allocate(
    size, sizeof(lifecycle_msgs__msg__Transition), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!lifecycle_msgs__msg__Transition__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        lifecycle_msgs__msg__Transition__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void lifecycle_msgs__msg__Transition__Sequence__fini(
  lifecycle_msgs__msg__Transition__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    lifecycle_msgs__msg__Transition__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
'''

TRANSITION_DESC_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/TransitionDescription functions

#include "lifecycle_msgs/msg/transition_description.h"
#include "rcutils/allocator.h"
#include <string.h>

bool lifecycle_msgs__msg__TransitionDescription__init(lifecycle_msgs__msg__TransitionDescription * msg)
{
  if (!msg) {
    return false;
  }
  if (!lifecycle_msgs__msg__Transition__init(&msg->transition)) {
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->start_state)) {
    lifecycle_msgs__msg__Transition__fini(&msg->transition);
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->goal_state)) {
    lifecycle_msgs__msg__State__fini(&msg->start_state);
    lifecycle_msgs__msg__Transition__fini(&msg->transition);
    return false;
  }
  return true;
}

void lifecycle_msgs__msg__TransitionDescription__fini(lifecycle_msgs__msg__TransitionDescription * msg)
{
  if (!msg) {
    return;
  }
  lifecycle_msgs__msg__Transition__fini(&msg->transition);
  lifecycle_msgs__msg__State__fini(&msg->start_state);
  lifecycle_msgs__msg__State__fini(&msg->goal_state);
}

lifecycle_msgs__msg__TransitionDescription * lifecycle_msgs__msg__TransitionDescription__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__TransitionDescription * msg = (lifecycle_msgs__msg__TransitionDescription *)allocator.allocate(
    sizeof(lifecycle_msgs__msg__TransitionDescription), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__msg__TransitionDescription__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__msg__TransitionDescription__destroy(lifecycle_msgs__msg__TransitionDescription * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__TransitionDescription__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool lifecycle_msgs__msg__TransitionDescription__Sequence__init(
  lifecycle_msgs__msg__TransitionDescription__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }

  array->data = (lifecycle_msgs__msg__TransitionDescription *)allocator.zero_allocate(
    size, sizeof(lifecycle_msgs__msg__TransitionDescription), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!lifecycle_msgs__msg__TransitionDescription__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        lifecycle_msgs__msg__TransitionDescription__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void lifecycle_msgs__msg__TransitionDescription__Sequence__fini(
  lifecycle_msgs__msg__TransitionDescription__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    lifecycle_msgs__msg__TransitionDescription__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
'''

TRANSITION_EVENT_FUNCTIONS = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/TransitionEvent functions

#include "lifecycle_msgs/msg/transition_event.h"
#include "rcutils/allocator.h"
#include <string.h>

bool lifecycle_msgs__msg__TransitionEvent__init(lifecycle_msgs__msg__TransitionEvent * msg)
{
  if (!msg) {
    return false;
  }
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    return false;
  }
  if (!lifecycle_msgs__msg__Transition__init(&msg->transition)) {
    builtin_interfaces__msg__Time__fini(&msg->timestamp);
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->start_state)) {
    lifecycle_msgs__msg__Transition__fini(&msg->transition);
    builtin_interfaces__msg__Time__fini(&msg->timestamp);
    return false;
  }
  if (!lifecycle_msgs__msg__State__init(&msg->goal_state)) {
    lifecycle_msgs__msg__State__fini(&msg->start_state);
    lifecycle_msgs__msg__Transition__fini(&msg->transition);
    builtin_interfaces__msg__Time__fini(&msg->timestamp);
    return false;
  }
  return true;
}

void lifecycle_msgs__msg__TransitionEvent__fini(lifecycle_msgs__msg__TransitionEvent * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  lifecycle_msgs__msg__Transition__fini(&msg->transition);
  lifecycle_msgs__msg__State__fini(&msg->start_state);
  lifecycle_msgs__msg__State__fini(&msg->goal_state);
}

lifecycle_msgs__msg__TransitionEvent * lifecycle_msgs__msg__TransitionEvent__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__TransitionEvent * msg = (lifecycle_msgs__msg__TransitionEvent *)allocator.allocate(
    sizeof(lifecycle_msgs__msg__TransitionEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!lifecycle_msgs__msg__TransitionEvent__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void lifecycle_msgs__msg__TransitionEvent__destroy(lifecycle_msgs__msg__TransitionEvent * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__TransitionEvent__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool lifecycle_msgs__msg__TransitionEvent__Sequence__init(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }

  array->data = (lifecycle_msgs__msg__TransitionEvent *)allocator.zero_allocate(
    size, sizeof(lifecycle_msgs__msg__TransitionEvent), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!lifecycle_msgs__msg__TransitionEvent__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        lifecycle_msgs__msg__TransitionEvent__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void lifecycle_msgs__msg__TransitionEvent__Sequence__fini(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    lifecycle_msgs__msg__TransitionEvent__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
'''


def generate_type_support_c(name, is_service=False, prefix="msg"):
    """Generate C type support file."""
    if is_service:
        return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{name} type support

#include "{PKG}/srv/{name.lower()}.h"
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
    else:
        return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{name} type support

#include "{PKG}/msg/{name.lower()}.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t {PKG}__msg__{name}__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, msg, {name})()
{{
  return &{PKG}__msg__{name}__type_support_handle;
}}
'''


def generate_cpp_type_support(name, is_service=False):
    """Generate C++ type support file."""
    snake = name.lower()
    if is_service:
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
    else:
        return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{name} C++ type support

#include "{PKG}/msg/{snake}.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<{PKG}::msg::{name}>()
{{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, {PKG}, msg, {name})();
}}

}}  // namespace rosidl_typesupport_cpp
'''


def generate_fastrtps_c(name, is_service=False):
    """Generate FastRTPS C type support file."""
    snake = name.lower()
    if is_service:
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
    else:
        return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{name} FastRTPS C type support

#include "{PKG}/msg/{snake}.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{{

static const rosidl_message_type_support_t {PKG}__msg__{name}__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, msg, {name})()
{{
  return &{PKG}__msg__{name}__fastrtps_type_support;
}}

}}  // extern "C"
'''


def main():
    print(f"Generating {PKG} C source files...")
    
    # Message function files
    print("\nWriting message functions:")
    write_file(f"{BASE_DIR}/src/msg/state__functions.c", STATE_FUNCTIONS)
    write_file(f"{BASE_DIR}/src/msg/transition__functions.c", TRANSITION_FUNCTIONS)
    write_file(f"{BASE_DIR}/src/msg/transition_description__functions.c", TRANSITION_DESC_FUNCTIONS)
    write_file(f"{BASE_DIR}/src/msg/transition_event__functions.c", TRANSITION_EVENT_FUNCTIONS)
    
    # Message type support
    print("\nWriting message type support:")
    for msg in ["State", "Transition", "TransitionDescription", "TransitionEvent"]:
        snake = msg.lower()
        if msg == "TransitionDescription":
            snake = "transition_description"
        elif msg == "TransitionEvent":
            snake = "transition_event"
        write_file(f"{BASE_DIR}/src/msg/{snake}__type_support.c", generate_type_support_c(msg))
        write_file(f"{BASE_DIR}/src/msg/{snake}__type_support.cpp", generate_cpp_type_support(msg))
        write_file(f"{BASE_DIR}/src/msg/{snake}__rosidl_typesupport_fastrtps_c.cpp", generate_fastrtps_c(msg))
    
    print(f"\nGeneration complete!")


if __name__ == "__main__":
    main()
