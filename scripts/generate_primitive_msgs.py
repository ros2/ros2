#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generate primitive message type implementations for std_msgs

import os
import sys

# Primitive types configuration
PRIMITIVES = [
    ("bool", "Bool", "bool", "false"),
    ("byte", "Byte", "uint8_t", "0"),
    ("char", "Char", "uint8_t", "0"),
    ("float32", "Float32", "float", "0.0f"),
    ("float64", "Float64", "double", "0.0"),
    ("int8", "Int8", "int8_t", "0"),
    ("int16", "Int16", "int16_t", "0"),
    ("int32", "Int32", "int32_t", "0"),
    ("int64", "Int64", "int64_t", "0"),
    ("uint8", "UInt8", "uint8_t", "0"),
    ("uint16", "UInt16", "uint16_t", "0"),
    ("uint32", "UInt32", "uint32_t", "0"),
    ("uint64", "UInt64", "uint64_t", "0"),
]

HEADER_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/{msg_name} message type

#ifndef STD_MSGS__MSG__{upper_name}_H_
#define STD_MSGS__MSG__{upper_name}_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {{
#endif

typedef struct std_msgs__msg__{msg_name}
{{
  {c_type} data;
}} std_msgs__msg__{msg_name};

typedef struct std_msgs__msg__{msg_name}__Sequence
{{
  std_msgs__msg__{msg_name} * data;
  size_t size;
  size_t capacity;
}} std_msgs__msg__{msg_name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__{msg_name}__init(std_msgs__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__{msg_name}__fini(std_msgs__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__{msg_name} * std_msgs__msg__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__{msg_name}__destroy(std_msgs__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__{msg_name}__Sequence__init(
  std_msgs__msg__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__{msg_name}__Sequence__fini(
  std_msgs__msg__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // STD_MSGS__MSG__{upper_name}_H_
'''

FUNCTIONS_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/{msg_name} functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/{lower_name}.h"
#include "rcutils/allocator.h"

bool std_msgs__msg__{msg_name}__init(std_msgs__msg__{msg_name} * msg)
{{
  if (!msg) {{ return false; }}
  msg->data = {default_val};
  return true;
}}

void std_msgs__msg__{msg_name}__fini(std_msgs__msg__{msg_name} * msg)
{{
  (void)msg;
}}

std_msgs__msg__{msg_name} * std_msgs__msg__{msg_name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__{msg_name} * msg = (std_msgs__msg__{msg_name} *)allocator.allocate(
    sizeof(std_msgs__msg__{msg_name}), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!std_msgs__msg__{msg_name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void std_msgs__msg__{msg_name}__destroy(std_msgs__msg__{msg_name} * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__{msg_name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool std_msgs__msg__{msg_name}__Sequence__init(
  std_msgs__msg__{msg_name}__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {{
    array->data = (std_msgs__msg__{msg_name} *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__{msg_name}), allocator.state);
    if (!array->data) {{ return false; }}
  }} else {{
    array->data = NULL;
  }}
  array->size = size;
  array->capacity = size;
  return true;
}}

void std_msgs__msg__{msg_name}__Sequence__fini(
  std_msgs__msg__{msg_name}__Sequence * array)
{{
  if (!array || !array->data) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}}
'''

TYPE_SUPPORT_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/{msg_name} type support

#include "std_msgs/msg/{lower_name}.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static rosidl_typesupport_introspection_c__MessageMember
std_msgs__msg__{msg_name}__members[1] = {{
  {{
    "data",
    {ros_type},
    0, NULL, false, 0, false,
    offsetof(std_msgs__msg__{msg_name}, data),
    NULL, NULL, NULL, NULL, NULL, NULL
  }}
}};

static const rosidl_typesupport_introspection_c__MessageMembers
std_msgs__msg__{msg_name}__message_members = {{
  "std_msgs", "{msg_name}", 1, sizeof(std_msgs__msg__{msg_name}), false,
  std_msgs__msg__{msg_name}__members,
  (rosidl_typesupport_introspection_c__MessageInitFunction)std_msgs__msg__{msg_name}__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)std_msgs__msg__{msg_name}__fini
}};

static rosidl_message_type_support_t std_msgs__msg__{msg_name}__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &std_msgs__msg__{msg_name}__message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__{msg_name}__type_support
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, std_msgs, msg, {msg_name})()
{{
  return &std_msgs__msg__{msg_name}__type_support;
}}
'''

# ROS type mapping for introspection
ROS_TYPE_MAP = {
    "bool": "rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN",
    "byte": "rosidl_typesupport_introspection_c__ROS_TYPE_OCTET",
    "char": "rosidl_typesupport_introspection_c__ROS_TYPE_UINT8",
    "float32": "rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT",
    "float64": "rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE",
    "int8": "rosidl_typesupport_introspection_c__ROS_TYPE_INT8",
    "int16": "rosidl_typesupport_introspection_c__ROS_TYPE_INT16",
    "int32": "rosidl_typesupport_introspection_c__ROS_TYPE_INT32",
    "int64": "rosidl_typesupport_introspection_c__ROS_TYPE_INT64",
    "uint8": "rosidl_typesupport_introspection_c__ROS_TYPE_UINT8",
    "uint16": "rosidl_typesupport_introspection_c__ROS_TYPE_UINT16",
    "uint32": "rosidl_typesupport_introspection_c__ROS_TYPE_UINT32",
    "uint64": "rosidl_typesupport_introspection_c__ROS_TYPE_UINT64",
}


def generate_files(output_dir):
    include_dir = os.path.join(output_dir, "include", "std_msgs", "msg")
    src_dir = os.path.join(output_dir, "src", "msg")
    os.makedirs(include_dir, exist_ok=True)
    os.makedirs(src_dir, exist_ok=True)

    for lower_name, msg_name, c_type, default_val in PRIMITIVES:
        upper_name = msg_name.upper()

        # Header file
        header_content = HEADER_TEMPLATE.format(
            msg_name=msg_name, upper_name=upper_name, c_type=c_type, lower_name=lower_name
        )
        with open(os.path.join(include_dir, f"{lower_name}.h"), "w") as f:
            f.write(header_content)

        # Functions file
        funcs_content = FUNCTIONS_TEMPLATE.format(
            msg_name=msg_name, lower_name=lower_name, default_val=default_val
        )
        with open(os.path.join(src_dir, f"{lower_name}__functions.c"), "w") as f:
            f.write(funcs_content)

        # Type support file
        ros_type = ROS_TYPE_MAP.get(lower_name, "rosidl_typesupport_introspection_c__ROS_TYPE_INT32")
        ts_content = TYPE_SUPPORT_TEMPLATE.format(
            msg_name=msg_name, lower_name=lower_name, ros_type=ros_type
        )
        with open(os.path.join(src_dir, f"{lower_name}__type_support.c"), "w") as f:
            f.write(ts_content)

        print(f"Generated: {msg_name}")

    print(f"\nGenerated {len(PRIMITIVES)} primitive message types")


if __name__ == "__main__":
    output_dir = sys.argv[1] if len(sys.argv) > 1 else "ohos_ros2/interfaces/std_msgs"
    generate_files(output_dir)
