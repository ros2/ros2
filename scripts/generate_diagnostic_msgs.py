#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generator for diagnostic_msgs message and service types

import os
import sys

def generate_header(msg_name, snake_name, fields, includes, constants=None, subdir="msg"):
    """Generate message header file"""
    pkg = "diagnostic_msgs"
    guard = f"DIAGNOSTIC_MSGS__{subdir.upper()}__{msg_name.upper()}_H_"

    include_lines = '\n'.join([f'#include "{inc}"' for inc in includes])

    const_lines = ""
    if constants:
        const_lines = "\n// Constants\n"
        for const_name, const_type, const_value in constants:
            const_lines += f"#define DIAGNOSTIC_MSGS__{subdir.upper()}__{msg_name}_{const_name} {const_value}\n"

    field_lines = '\n'.join([f"  {ftype} {fname};" for ftype, fname in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/{subdir}/{msg_name} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "diagnostic_msgs/msg/rosidl_generator_c__visibility_control.h"
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

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool {pkg}__{subdir}__{msg_name}__init({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void {pkg}__{subdir}__{msg_name}__fini({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
{pkg}__{subdir}__{msg_name} * {pkg}__{subdir}__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void {pkg}__{subdir}__{msg_name}__destroy({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool {pkg}__{subdir}__{msg_name}__Sequence__init(
  {pkg}__{subdir}__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void {pkg}__{subdir}__{msg_name}__Sequence__fini(
  {pkg}__{subdir}__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_functions(msg_name, snake_name, init_code, fini_code, subdir="msg"):
    """Generate message functions implementation"""
    pkg = "diagnostic_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/{subdir}/{msg_name} functions

#include "diagnostic_msgs/{subdir}/{snake_name}.h"
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
    pkg = "diagnostic_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/{subdir}/{msg_name} type support

#include "diagnostic_msgs/{subdir}/{snake_name}.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

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


# Message type definitions
MESSAGE_TYPES = [
    # KeyValue - Key-value pair
    {
        'name': 'KeyValue',
        'snake': 'key_value',
        'includes': [
            'rosidl_runtime_c/string.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'key'),
            ('rosidl_runtime_c__String', 'value'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->key);
  rosidl_runtime_c__String__init(&msg->value);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->key);
  rosidl_runtime_c__String__fini(&msg->value);''',
    },

    # DiagnosticStatus - Status of a single component
    {
        'name': 'DiagnosticStatus',
        'snake': 'diagnostic_status',
        'includes': [
            'rosidl_runtime_c/string.h',
            'diagnostic_msgs/msg/key_value.h',
        ],
        'fields': [
            ('uint8_t', 'level'),
            ('rosidl_runtime_c__String', 'name'),
            ('rosidl_runtime_c__String', 'message'),
            ('rosidl_runtime_c__String', 'hardware_id'),
            ('diagnostic_msgs__msg__KeyValue__Sequence', 'values'),
        ],
        'constants': [
            ('OK', 'uint8_t', '0'),
            ('WARN', 'uint8_t', '1'),
            ('ERROR', 'uint8_t', '2'),
            ('STALE', 'uint8_t', '3'),
        ],
        'init': '''  msg->level = 0;
  rosidl_runtime_c__String__init(&msg->name);
  rosidl_runtime_c__String__init(&msg->message);
  rosidl_runtime_c__String__init(&msg->hardware_id);
  diagnostic_msgs__msg__KeyValue__Sequence__init(&msg->values, 0);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->name);
  rosidl_runtime_c__String__fini(&msg->message);
  rosidl_runtime_c__String__fini(&msg->hardware_id);
  diagnostic_msgs__msg__KeyValue__Sequence__fini(&msg->values);''',
    },

    # DiagnosticArray - Array of diagnostic statuses
    {
        'name': 'DiagnosticArray',
        'snake': 'diagnostic_array',
        'includes': [
            'std_msgs/msg/header.h',
            'diagnostic_msgs/msg/diagnostic_status.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('diagnostic_msgs__msg__DiagnosticStatus__Sequence', 'status'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  diagnostic_msgs__msg__DiagnosticStatus__Sequence__init(&msg->status, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  diagnostic_msgs__msg__DiagnosticStatus__Sequence__fini(&msg->status);''',
    },
]

# Service type definitions
SERVICE_TYPES = [
    # AddDiagnostics_Request
    {
        'name': 'AddDiagnostics_Request',
        'snake': 'add_diagnostics__request',
        'includes': [
            'rosidl_runtime_c/string.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'load_namespace'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->load_namespace);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->load_namespace);''',
    },

    # AddDiagnostics_Response
    {
        'name': 'AddDiagnostics_Response',
        'snake': 'add_diagnostics__response',
        'includes': [
            'rosidl_runtime_c/string.h',
        ],
        'fields': [
            ('bool', 'success'),
            ('rosidl_runtime_c__String', 'message'),
        ],
        'init': '''  msg->success = false;
  rosidl_runtime_c__String__init(&msg->message);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->message);''',
    },

    # SelfTest_Request
    {
        'name': 'SelfTest_Request',
        'snake': 'self_test__request',
        'includes': [],
        'fields': [
            ('uint8_t', 'structure_needs_at_least_one_member'),
        ],
        'init': '''  msg->structure_needs_at_least_one_member = 0;''',
        'fini': '''''',
    },

    # SelfTest_Response
    {
        'name': 'SelfTest_Response',
        'snake': 'self_test__response',
        'includes': [
            'rosidl_runtime_c/string.h',
            'diagnostic_msgs/msg/diagnostic_status.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'id'),
            ('uint8_t', 'passed'),
            ('diagnostic_msgs__msg__DiagnosticStatus__Sequence', 'status'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->id);
  msg->passed = 0;
  diagnostic_msgs__msg__DiagnosticStatus__Sequence__init(&msg->status, 0);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->id);
  diagnostic_msgs__msg__DiagnosticStatus__Sequence__fini(&msg->status);''',
    },
]


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output_dir>")
        sys.exit(1)

    output_dir = sys.argv[1]
    msg_include_dir = os.path.join(output_dir, "include", "diagnostic_msgs", "msg")
    msg_src_dir = os.path.join(output_dir, "src", "msg")
    srv_include_dir = os.path.join(output_dir, "include", "diagnostic_msgs", "srv")
    srv_src_dir = os.path.join(output_dir, "src", "srv")

    os.makedirs(msg_include_dir, exist_ok=True)
    os.makedirs(msg_src_dir, exist_ok=True)
    os.makedirs(srv_include_dir, exist_ok=True)
    os.makedirs(srv_src_dir, exist_ok=True)

    # Generate message types
    for msg in MESSAGE_TYPES:
        name = msg['name']
        snake = msg['snake']

        header = generate_header(name, snake, msg['fields'], msg['includes'],
                                  msg.get('constants'), subdir='msg')
        with open(os.path.join(msg_include_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        functions = generate_functions(name, snake, msg['init'], msg['fini'], subdir='msg')
        with open(os.path.join(msg_src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        type_support = generate_type_support(name, snake, subdir='msg')
        with open(os.path.join(msg_src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: {name}")

    # Generate service types
    for srv in SERVICE_TYPES:
        name = srv['name']
        snake = srv['snake']

        header = generate_header(name, snake, srv['fields'], srv['includes'],
                                  srv.get('constants'), subdir='srv')
        with open(os.path.join(srv_include_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        functions = generate_functions(name, snake, srv['init'], srv['fini'], subdir='srv')
        with open(os.path.join(srv_src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        type_support = generate_type_support(name, snake, subdir='srv')
        with open(os.path.join(srv_src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: {name}")

    print(f"\nGenerated {len(MESSAGE_TYPES)} message types and {len(SERVICE_TYPES)} service types")


if __name__ == "__main__":
    main()
