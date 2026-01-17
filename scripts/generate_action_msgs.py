#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generator for action_msgs message and service types

import os
import sys

def generate_header(msg_name, snake_name, fields, includes, constants=None, is_service=False):
    """Generate message header file"""
    pkg = "action_msgs"
    subdir = "srv" if is_service else "msg"
    guard = f"ACTION_MSGS__{subdir.upper()}__{msg_name.upper()}_H_"

    include_lines = '\n'.join([f'#include "{inc}"' for inc in includes])

    # Build constants
    const_lines = ""
    if constants:
        const_lines = "\n// Constants\n"
        for const_name, const_type, const_value in constants:
            const_lines += f"#define ACTION_MSGS__{subdir.upper()}__{msg_name}_{const_name} {const_value}\n"

    # Build struct fields
    field_lines = '\n'.join([f"  {ftype} {fname};" for ftype, fname in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/{subdir}/{msg_name} {"service" if is_service else "message"} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "action_msgs/msg/rosidl_generator_c__visibility_control.h"
{include_lines}

#ifdef __cplusplus
extern "C" {{
#endif
{const_lines}
typedef struct {pkg}__{subdir}__{msg_name}
{{
{field_lines}
}} {pkg}__{subdir}__{msg_name};

typedef struct {pkg}__{subdir}__{msg_name}__Sequence
{{
  {pkg}__{subdir}__{msg_name} * data;
  size_t size;
  size_t capacity;
}} {pkg}__{subdir}__{msg_name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool {pkg}__{subdir}__{msg_name}__init({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void {pkg}__{subdir}__{msg_name}__fini({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
{pkg}__{subdir}__{msg_name} * {pkg}__{subdir}__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void {pkg}__{subdir}__{msg_name}__destroy({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool {pkg}__{subdir}__{msg_name}__Sequence__init(
  {pkg}__{subdir}__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void {pkg}__{subdir}__{msg_name}__Sequence__fini(
  {pkg}__{subdir}__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_functions(msg_name, snake_name, fields, init_code, fini_code, is_service=False):
    """Generate message functions implementation"""
    pkg = "action_msgs"
    subdir = "srv" if is_service else "msg"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/{subdir}/{msg_name} functions

#include "action_msgs/{subdir}/{snake_name}.h"
#include "rcutils/allocator.h"
#include <string.h>

bool {pkg}__{subdir}__{msg_name}__init({pkg}__{subdir}__{msg_name} * msg)
{{
  if (!msg) {{
    return false;
  }}
  memset(msg, 0, sizeof(*msg));
{init_code}
  return true;
}}

void {pkg}__{subdir}__{msg_name}__fini({pkg}__{subdir}__{msg_name} * msg)
{{
  if (!msg) {{
    return;
  }}
{fini_code}
}}

{pkg}__{subdir}__{msg_name} * {pkg}__{subdir}__{msg_name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {pkg}__{subdir}__{msg_name} * msg = ({pkg}__{subdir}__{msg_name} *)allocator.allocate(
    sizeof({pkg}__{subdir}__{msg_name}), allocator.state);
  if (!msg) {{
    return NULL;
  }}
  if (!{pkg}__{subdir}__{msg_name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void {pkg}__{subdir}__{msg_name}__destroy({pkg}__{subdir}__{msg_name} * msg)
{{
  if (!msg) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {pkg}__{subdir}__{msg_name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool {pkg}__{subdir}__{msg_name}__Sequence__init(
  {pkg}__{subdir}__{msg_name}__Sequence * array, size_t size)
{{
  if (!array) {{
    return false;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {{
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }}

  array->data = ({pkg}__{subdir}__{msg_name} *)allocator.zero_allocate(
    size, sizeof({pkg}__{subdir}__{msg_name}), allocator.state);
  if (!array->data) {{
    return false;
  }}

  for (size_t i = 0; i < size; ++i) {{
    if (!{pkg}__{subdir}__{msg_name}__init(&array->data[i])) {{
      for (size_t j = 0; j < i; ++j) {{
        {pkg}__{subdir}__{msg_name}__fini(&array->data[j]);
      }}
      allocator.deallocate(array->data, allocator.state);
      return false;
    }}
  }}

  array->size = size;
  array->capacity = size;
  return true;
}}

void {pkg}__{subdir}__{msg_name}__Sequence__fini(
  {pkg}__{subdir}__{msg_name}__Sequence * array)
{{
  if (!array || !array->data) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {{
    {pkg}__{subdir}__{msg_name}__fini(&array->data[i]);
  }}
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}}
'''


def generate_type_support(msg_name, snake_name, is_service=False):
    """Generate type support file"""
    pkg = "action_msgs"
    subdir = "srv" if is_service else "msg"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/{subdir}/{msg_name} type support

#include "action_msgs/{subdir}/{snake_name}.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Type support handle
static rosidl_message_type_support_t {pkg}__{subdir}__{msg_name}__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {pkg}, {subdir}, {msg_name})()
{{
  return &{pkg}__{subdir}__{msg_name}__type_support_handle;
}}
'''


def to_snake_case(name):
    """Convert CamelCase to snake_case"""
    result = []
    for i, c in enumerate(name):
        if c.isupper() and i > 0:
            result.append('_')
        result.append(c.lower())
    return ''.join(result)


# Message type definitions
MESSAGE_TYPES = [
    # GoalInfo - Goal identifier and timestamp
    {
        'name': 'GoalInfo',
        'includes': [
            'builtin_interfaces/msg/time.h',
        ],
        'fields': [
            ('uint8_t', 'goal_id[16]'),  # UUID as 16 bytes
            ('builtin_interfaces__msg__Time', 'stamp'),
        ],
        'init': '''  memset(msg->goal_id, 0, sizeof(msg->goal_id));
  builtin_interfaces__msg__Time__init(&msg->stamp);''',
        'fini': '''  builtin_interfaces__msg__Time__fini(&msg->stamp);''',
    },

    # GoalStatus - Status of a single goal
    {
        'name': 'GoalStatus',
        'includes': [
            'action_msgs/msg/goal_info.h',
        ],
        'fields': [
            ('action_msgs__msg__GoalInfo', 'goal_info'),
            ('int8_t', 'status'),
        ],
        'constants': [
            ('STATUS_UNKNOWN', 'int8_t', '0'),
            ('STATUS_ACCEPTED', 'int8_t', '1'),
            ('STATUS_EXECUTING', 'int8_t', '2'),
            ('STATUS_CANCELING', 'int8_t', '3'),
            ('STATUS_SUCCEEDED', 'int8_t', '4'),
            ('STATUS_CANCELED', 'int8_t', '5'),
            ('STATUS_ABORTED', 'int8_t', '6'),
        ],
        'init': '''  action_msgs__msg__GoalInfo__init(&msg->goal_info);
  msg->status = 0;''',
        'fini': '''  action_msgs__msg__GoalInfo__fini(&msg->goal_info);''',
    },

    # GoalStatusArray - Array of goal statuses
    {
        'name': 'GoalStatusArray',
        'includes': [
            'action_msgs/msg/goal_status.h',
        ],
        'fields': [
            ('action_msgs__msg__GoalStatus__Sequence', 'status_list'),
        ],
        'init': '''  action_msgs__msg__GoalStatus__Sequence__init(&msg->status_list, 0);''',
        'fini': '''  action_msgs__msg__GoalStatus__Sequence__fini(&msg->status_list);''',
    },
]

# Service type definitions
SERVICE_TYPES = [
    # CancelGoal_Request - Request to cancel goals
    {
        'name': 'CancelGoal_Request',
        'includes': [
            'action_msgs/msg/goal_info.h',
        ],
        'fields': [
            ('action_msgs__msg__GoalInfo', 'goal_info'),
        ],
        'init': '''  action_msgs__msg__GoalInfo__init(&msg->goal_info);''',
        'fini': '''  action_msgs__msg__GoalInfo__fini(&msg->goal_info);''',
    },

    # CancelGoal_Response - Response with canceled goals
    {
        'name': 'CancelGoal_Response',
        'includes': [
            'action_msgs/msg/goal_info.h',
        ],
        'fields': [
            ('int8_t', 'return_code'),
            ('action_msgs__msg__GoalInfo__Sequence', 'goals_canceling'),
        ],
        'constants': [
            ('ERROR_NONE', 'int8_t', '0'),
            ('ERROR_REJECTED', 'int8_t', '1'),
            ('ERROR_UNKNOWN_GOAL_ID', 'int8_t', '2'),
            ('ERROR_GOAL_TERMINATED', 'int8_t', '3'),
        ],
        'init': '''  msg->return_code = 0;
  action_msgs__msg__GoalInfo__Sequence__init(&msg->goals_canceling, 0);''',
        'fini': '''  action_msgs__msg__GoalInfo__Sequence__fini(&msg->goals_canceling);''',
    },
]


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output_dir>")
        sys.exit(1)

    output_dir = sys.argv[1]
    msg_include_dir = os.path.join(output_dir, "include", "action_msgs", "msg")
    msg_src_dir = os.path.join(output_dir, "src", "msg")
    srv_include_dir = os.path.join(output_dir, "include", "action_msgs", "srv")
    srv_src_dir = os.path.join(output_dir, "src", "srv")

    os.makedirs(msg_include_dir, exist_ok=True)
    os.makedirs(msg_src_dir, exist_ok=True)
    os.makedirs(srv_include_dir, exist_ok=True)
    os.makedirs(srv_src_dir, exist_ok=True)

    # Generate message types
    for msg in MESSAGE_TYPES:
        name = msg['name']
        snake = to_snake_case(name)

        # Header
        header = generate_header(
            name, snake, msg['fields'], msg['includes'],
            msg.get('constants'), is_service=False
        )
        with open(os.path.join(msg_include_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        # Functions
        functions = generate_functions(
            name, snake, msg['fields'], msg['init'], msg['fini'],
            is_service=False
        )
        with open(os.path.join(msg_src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        # Type support
        type_support = generate_type_support(name, snake, is_service=False)
        with open(os.path.join(msg_src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: {name}")

    # Generate service types
    for srv in SERVICE_TYPES:
        name = srv['name']
        snake = to_snake_case(name)

        # Header
        header = generate_header(
            name, snake, srv['fields'], srv['includes'],
            srv.get('constants'), is_service=True
        )
        with open(os.path.join(srv_include_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        # Functions
        functions = generate_functions(
            name, snake, srv['fields'], srv['init'], srv['fini'],
            is_service=True
        )
        with open(os.path.join(srv_src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        # Type support
        type_support = generate_type_support(name, snake, is_service=True)
        with open(os.path.join(srv_src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: {name}")

    print(f"\nGenerated {len(MESSAGE_TYPES)} message types and {len(SERVICE_TYPES)} service types")


if __name__ == "__main__":
    main()
