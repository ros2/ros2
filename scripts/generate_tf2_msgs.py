#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generator for tf2_msgs message, service, and action types

import os
import sys

def generate_header(msg_name, snake_name, fields, includes, constants=None, subdir="msg"):
    """Generate message header file"""
    pkg = "tf2_msgs"
    guard = f"TF2_MSGS__{subdir.upper()}__{msg_name.upper()}_H_"

    include_lines = '\n'.join([f'#include "{inc}"' for inc in includes])

    # Build constants
    const_lines = ""
    if constants:
        const_lines = "\n// Constants\n"
        for const_name, const_type, const_value in constants:
            const_lines += f"#define TF2_MSGS__{subdir.upper()}__{msg_name}_{const_name} {const_value}\n"

    # Build struct fields
    field_lines = '\n'.join([f"  {ftype} {fname};" for ftype, fname in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/{subdir}/{msg_name} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "tf2_msgs/msg/rosidl_generator_c__visibility_control.h"
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

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool {pkg}__{subdir}__{msg_name}__init({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void {pkg}__{subdir}__{msg_name}__fini({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
{pkg}__{subdir}__{msg_name} * {pkg}__{subdir}__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void {pkg}__{subdir}__{msg_name}__destroy({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool {pkg}__{subdir}__{msg_name}__Sequence__init(
  {pkg}__{subdir}__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void {pkg}__{subdir}__{msg_name}__Sequence__fini(
  {pkg}__{subdir}__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_functions(msg_name, snake_name, fields, init_code, fini_code, subdir="msg"):
    """Generate message functions implementation"""
    pkg = "tf2_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/{subdir}/{msg_name} functions

#include "tf2_msgs/{subdir}/{snake_name}.h"
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


def generate_type_support(msg_name, snake_name, subdir="msg"):
    """Generate type support file"""
    pkg = "tf2_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/{subdir}/{msg_name} type support

#include "tf2_msgs/{subdir}/{snake_name}.h"
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
    # TFMessage - Collection of transforms
    {
        'name': 'TFMessage',
        'includes': [
            'geometry_msgs/msg/transform_stamped.h',
        ],
        'fields': [
            ('geometry_msgs__msg__TransformStamped__Sequence', 'transforms'),
        ],
        'init': '''  geometry_msgs__msg__TransformStamped__Sequence__init(&msg->transforms, 0);''',
        'fini': '''  geometry_msgs__msg__TransformStamped__Sequence__fini(&msg->transforms);''',
    },

    # TF2Error - Error information
    {
        'name': 'TF2Error',
        'includes': [
            'rosidl_runtime_c/string.h',
        ],
        'fields': [
            ('uint8_t', 'error'),
            ('rosidl_runtime_c__String', 'error_string'),
        ],
        'constants': [
            ('NO_ERROR', 'uint8_t', '0'),
            ('LOOKUP_ERROR', 'uint8_t', '1'),
            ('CONNECTIVITY_ERROR', 'uint8_t', '2'),
            ('EXTRAPOLATION_ERROR', 'uint8_t', '3'),
            ('INVALID_ARGUMENT_ERROR', 'uint8_t', '4'),
            ('TIMEOUT_ERROR', 'uint8_t', '5'),
            ('TRANSFORM_ERROR', 'uint8_t', '6'),
        ],
        'init': '''  msg->error = 0;
  rosidl_runtime_c__String__init(&msg->error_string);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->error_string);''',
    },
]

# Service type definitions
SERVICE_TYPES = [
    # FrameGraph_Request - Empty request
    {
        'name': 'FrameGraph_Request',
        'includes': [],
        'fields': [
            ('uint8_t', 'structure_needs_at_least_one_member'),
        ],
        'init': '''  msg->structure_needs_at_least_one_member = 0;''',
        'fini': '''''',
    },

    # FrameGraph_Response - YAML string
    {
        'name': 'FrameGraph_Response',
        'includes': [
            'rosidl_runtime_c/string.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'frame_yaml'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->frame_yaml);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->frame_yaml);''',
    },
]

# Action type definitions
ACTION_TYPES = [
    # LookupTransform_Goal
    {
        'name': 'LookupTransform_Goal',
        'includes': [
            'rosidl_runtime_c/string.h',
            'builtin_interfaces/msg/time.h',
            'builtin_interfaces/msg/duration.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'target_frame'),
            ('rosidl_runtime_c__String', 'source_frame'),
            ('builtin_interfaces__msg__Time', 'source_time'),
            ('builtin_interfaces__msg__Duration', 'timeout'),
            ('builtin_interfaces__msg__Time', 'target_time'),
            ('rosidl_runtime_c__String', 'fixed_frame'),
            ('bool', 'advanced'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->target_frame);
  rosidl_runtime_c__String__init(&msg->source_frame);
  builtin_interfaces__msg__Time__init(&msg->source_time);
  builtin_interfaces__msg__Duration__init(&msg->timeout);
  builtin_interfaces__msg__Time__init(&msg->target_time);
  rosidl_runtime_c__String__init(&msg->fixed_frame);
  msg->advanced = false;''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->target_frame);
  rosidl_runtime_c__String__fini(&msg->source_frame);
  builtin_interfaces__msg__Time__fini(&msg->source_time);
  builtin_interfaces__msg__Duration__fini(&msg->timeout);
  builtin_interfaces__msg__Time__fini(&msg->target_time);
  rosidl_runtime_c__String__fini(&msg->fixed_frame);''',
    },

    # LookupTransform_Result
    {
        'name': 'LookupTransform_Result',
        'includes': [
            'geometry_msgs/msg/transform_stamped.h',
            'tf2_msgs/msg/tf2_error.h',
        ],
        'fields': [
            ('geometry_msgs__msg__TransformStamped', 'transform'),
            ('tf2_msgs__msg__TF2Error', 'error'),
        ],
        'init': '''  geometry_msgs__msg__TransformStamped__init(&msg->transform);
  tf2_msgs__msg__TF2Error__init(&msg->error);''',
        'fini': '''  geometry_msgs__msg__TransformStamped__fini(&msg->transform);
  tf2_msgs__msg__TF2Error__fini(&msg->error);''',
    },

    # LookupTransform_Feedback - Empty
    {
        'name': 'LookupTransform_Feedback',
        'includes': [],
        'fields': [
            ('uint8_t', 'structure_needs_at_least_one_member'),
        ],
        'init': '''  msg->structure_needs_at_least_one_member = 0;''',
        'fini': '''''',
    },
]


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output_dir>")
        sys.exit(1)

    output_dir = sys.argv[1]

    # Create directories
    dirs = {
        'msg': (os.path.join(output_dir, "include", "tf2_msgs", "msg"),
                os.path.join(output_dir, "src", "msg")),
        'srv': (os.path.join(output_dir, "include", "tf2_msgs", "srv"),
                os.path.join(output_dir, "src", "srv")),
        'action': (os.path.join(output_dir, "include", "tf2_msgs", "action"),
                   os.path.join(output_dir, "src", "action")),
    }

    for subdir, (inc_dir, src_dir) in dirs.items():
        os.makedirs(inc_dir, exist_ok=True)
        os.makedirs(src_dir, exist_ok=True)

    # Generate message types
    for msg in MESSAGE_TYPES:
        name = msg['name']
        snake = to_snake_case(name)
        inc_dir, src_dir = dirs['msg']

        header = generate_header(name, snake, msg['fields'], msg['includes'],
                                  msg.get('constants'), subdir='msg')
        with open(os.path.join(inc_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        functions = generate_functions(name, snake, msg['fields'],
                                         msg['init'], msg['fini'], subdir='msg')
        with open(os.path.join(src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        type_support = generate_type_support(name, snake, subdir='msg')
        with open(os.path.join(src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: msg/{name}")

    # Generate service types
    for srv in SERVICE_TYPES:
        name = srv['name']
        snake = to_snake_case(name)
        inc_dir, src_dir = dirs['srv']

        header = generate_header(name, snake, srv['fields'], srv['includes'],
                                  srv.get('constants'), subdir='srv')
        with open(os.path.join(inc_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        functions = generate_functions(name, snake, srv['fields'],
                                         srv['init'], srv['fini'], subdir='srv')
        with open(os.path.join(src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        type_support = generate_type_support(name, snake, subdir='srv')
        with open(os.path.join(src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: srv/{name}")

    # Generate action types
    for action in ACTION_TYPES:
        name = action['name']
        snake = to_snake_case(name)
        inc_dir, src_dir = dirs['action']

        header = generate_header(name, snake, action['fields'], action['includes'],
                                  action.get('constants'), subdir='action')
        with open(os.path.join(inc_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        functions = generate_functions(name, snake, action['fields'],
                                         action['init'], action['fini'], subdir='action')
        with open(os.path.join(src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        type_support = generate_type_support(name, snake, subdir='action')
        with open(os.path.join(src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: action/{name}")

    print(f"\nGenerated {len(MESSAGE_TYPES)} message types, "
          f"{len(SERVICE_TYPES)} service types, and {len(ACTION_TYPES)} action types")


if __name__ == "__main__":
    main()
