#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generate MultiArray message type implementations for std_msgs

import os
import sys

# MultiArray types configuration
# (lower_name, msg_name, c_type, ros_type, sequence_type)
MULTI_ARRAYS = [
    ("int8", "Int8", "int8_t", "rosidl_typesupport_introspection_c__ROS_TYPE_INT8", "rosidl_runtime_c__int8__Sequence"),
    ("int16", "Int16", "int16_t", "rosidl_typesupport_introspection_c__ROS_TYPE_INT16", "rosidl_runtime_c__int16__Sequence"),
    ("int32", "Int32", "int32_t", "rosidl_typesupport_introspection_c__ROS_TYPE_INT32", "rosidl_runtime_c__int32__Sequence"),
    ("int64", "Int64", "int64_t", "rosidl_typesupport_introspection_c__ROS_TYPE_INT64", "rosidl_runtime_c__int64__Sequence"),
    ("uint8", "UInt8", "uint8_t", "rosidl_typesupport_introspection_c__ROS_TYPE_UINT8", "rosidl_runtime_c__uint8__Sequence"),
    ("uint16", "UInt16", "uint16_t", "rosidl_typesupport_introspection_c__ROS_TYPE_UINT16", "rosidl_runtime_c__uint16__Sequence"),
    ("uint32", "UInt32", "uint32_t", "rosidl_typesupport_introspection_c__ROS_TYPE_UINT32", "rosidl_runtime_c__uint32__Sequence"),
    ("uint64", "UInt64", "uint64_t", "rosidl_typesupport_introspection_c__ROS_TYPE_UINT64", "rosidl_runtime_c__uint64__Sequence"),
    ("float32", "Float32", "float", "rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT", "rosidl_runtime_c__float__Sequence"),
    ("float64", "Float64", "double", "rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE", "rosidl_runtime_c__double__Sequence"),
    ("byte", "Byte", "uint8_t", "rosidl_typesupport_introspection_c__ROS_TYPE_OCTET", "rosidl_runtime_c__uint8__Sequence"),
]

HEADER_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/{msg_name}MultiArray message type

#ifndef STD_MSGS__MSG__{upper_name}_MULTI_ARRAY_H_
#define STD_MSGS__MSG__{upper_name}_MULTI_ARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/multi_array_layout.h"

#ifdef __cplusplus
extern "C" {{
#endif

/// {msg_name}MultiArray message
/// Please look at the MultiArrayLayout message definition for
/// documentation on all multiarrays.
typedef struct std_msgs__msg__{msg_name}MultiArray
{{
  /// specification of data layout
  std_msgs__msg__MultiArrayLayout layout;
  /// array of data
  {sequence_type} data;
}} std_msgs__msg__{msg_name}MultiArray;

typedef struct std_msgs__msg__{msg_name}MultiArray__Sequence
{{
  std_msgs__msg__{msg_name}MultiArray * data;
  size_t size;
  size_t capacity;
}} std_msgs__msg__{msg_name}MultiArray__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__{msg_name}MultiArray__init(std_msgs__msg__{msg_name}MultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__{msg_name}MultiArray__fini(std_msgs__msg__{msg_name}MultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__{msg_name}MultiArray * std_msgs__msg__{msg_name}MultiArray__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__{msg_name}MultiArray__destroy(std_msgs__msg__{msg_name}MultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__{msg_name}MultiArray__Sequence__init(
  std_msgs__msg__{msg_name}MultiArray__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__{msg_name}MultiArray__Sequence__fini(
  std_msgs__msg__{msg_name}MultiArray__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // STD_MSGS__MSG__{upper_name}_MULTI_ARRAY_H_
'''

FUNCTIONS_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/{msg_name}MultiArray functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/{lower_name}_multi_array.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool std_msgs__msg__{msg_name}MultiArray__init(std_msgs__msg__{msg_name}MultiArray * msg)
{{
  if (!msg) {{ return false; }}
  if (!std_msgs__msg__MultiArrayLayout__init(&msg->layout)) {{
    return false;
  }}
  if (!{seq_init_func}(&msg->data, 0)) {{
    std_msgs__msg__MultiArrayLayout__fini(&msg->layout);
    return false;
  }}
  return true;
}}

void std_msgs__msg__{msg_name}MultiArray__fini(std_msgs__msg__{msg_name}MultiArray * msg)
{{
  if (!msg) {{ return; }}
  std_msgs__msg__MultiArrayLayout__fini(&msg->layout);
  {seq_fini_func}(&msg->data);
}}

std_msgs__msg__{msg_name}MultiArray * std_msgs__msg__{msg_name}MultiArray__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__{msg_name}MultiArray * msg =
    (std_msgs__msg__{msg_name}MultiArray *)allocator.allocate(
      sizeof(std_msgs__msg__{msg_name}MultiArray), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!std_msgs__msg__{msg_name}MultiArray__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void std_msgs__msg__{msg_name}MultiArray__destroy(std_msgs__msg__{msg_name}MultiArray * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__{msg_name}MultiArray__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool std_msgs__msg__{msg_name}MultiArray__Sequence__init(
  std_msgs__msg__{msg_name}MultiArray__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size) {{
    array->data = (std_msgs__msg__{msg_name}MultiArray *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__{msg_name}MultiArray), allocator.state);
    if (!array->data) {{ return false; }}
    for (size_t i = 0; i < size; ++i) {{
      if (!std_msgs__msg__{msg_name}MultiArray__init(&array->data[i])) {{
        for (size_t j = 0; j < i; ++j) {{
          std_msgs__msg__{msg_name}MultiArray__fini(&array->data[j]);
        }}
        allocator.deallocate(array->data, allocator.state);
        return false;
      }}
    }}
  }} else {{
    array->data = NULL;
  }}
  array->size = size;
  array->capacity = size;
  return true;
}}

void std_msgs__msg__{msg_name}MultiArray__Sequence__fini(
  std_msgs__msg__{msg_name}MultiArray__Sequence * array)
{{
  if (!array) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {{
    for (size_t i = 0; i < array->size; ++i) {{
      std_msgs__msg__{msg_name}MultiArray__fini(&array->data[i]);
    }}
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }}
}}
'''

TYPE_SUPPORT_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/{msg_name}MultiArray type support

#include "std_msgs/msg/{lower_name}_multi_array.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

// Stub type support - detailed introspection omitted for brevity
static const rosidl_typesupport_introspection_c__MessageMembers
std_msgs__msg__{msg_name}MultiArray__message_members = {{
  "std_msgs", "{msg_name}MultiArray", 0, sizeof(std_msgs__msg__{msg_name}MultiArray), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)std_msgs__msg__{msg_name}MultiArray__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)std_msgs__msg__{msg_name}MultiArray__fini
}};

static rosidl_message_type_support_t std_msgs__msg__{msg_name}MultiArray__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &std_msgs__msg__{msg_name}MultiArray__message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__{msg_name}MultiArray__type_support
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, std_msgs, msg, {msg_name}MultiArray)()
{{
  return &std_msgs__msg__{msg_name}MultiArray__type_support;
}}
'''

# Map from base type to sequence init/fini function names
SEQ_FUNC_MAP = {
    "int8": ("rosidl_runtime_c__int8__Sequence__init", "rosidl_runtime_c__int8__Sequence__fini"),
    "int16": ("rosidl_runtime_c__int16__Sequence__init", "rosidl_runtime_c__int16__Sequence__fini"),
    "int32": ("rosidl_runtime_c__int32__Sequence__init", "rosidl_runtime_c__int32__Sequence__fini"),
    "int64": ("rosidl_runtime_c__int64__Sequence__init", "rosidl_runtime_c__int64__Sequence__fini"),
    "uint8": ("rosidl_runtime_c__uint8__Sequence__init", "rosidl_runtime_c__uint8__Sequence__fini"),
    "uint16": ("rosidl_runtime_c__uint16__Sequence__init", "rosidl_runtime_c__uint16__Sequence__fini"),
    "uint32": ("rosidl_runtime_c__uint32__Sequence__init", "rosidl_runtime_c__uint32__Sequence__fini"),
    "uint64": ("rosidl_runtime_c__uint64__Sequence__init", "rosidl_runtime_c__uint64__Sequence__fini"),
    "float32": ("rosidl_runtime_c__float__Sequence__init", "rosidl_runtime_c__float__Sequence__fini"),
    "float64": ("rosidl_runtime_c__double__Sequence__init", "rosidl_runtime_c__double__Sequence__fini"),
    "byte": ("rosidl_runtime_c__uint8__Sequence__init", "rosidl_runtime_c__uint8__Sequence__fini"),
}


def generate_files(output_dir):
    include_dir = os.path.join(output_dir, "include", "std_msgs", "msg")
    src_dir = os.path.join(output_dir, "src", "msg")
    os.makedirs(include_dir, exist_ok=True)
    os.makedirs(src_dir, exist_ok=True)

    for lower_name, msg_name, c_type, ros_type, sequence_type in MULTI_ARRAYS:
        upper_name = msg_name.upper()
        seq_init_func, seq_fini_func = SEQ_FUNC_MAP[lower_name]

        # Header file
        header_content = HEADER_TEMPLATE.format(
            msg_name=msg_name, upper_name=upper_name, c_type=c_type,
            lower_name=lower_name, sequence_type=sequence_type
        )
        with open(os.path.join(include_dir, f"{lower_name}_multi_array.h"), "w") as f:
            f.write(header_content)

        # Functions file
        funcs_content = FUNCTIONS_TEMPLATE.format(
            msg_name=msg_name, lower_name=lower_name,
            seq_init_func=seq_init_func, seq_fini_func=seq_fini_func
        )
        with open(os.path.join(src_dir, f"{lower_name}_multi_array__functions.c"), "w") as f:
            f.write(funcs_content)

        # Type support file
        ts_content = TYPE_SUPPORT_TEMPLATE.format(
            msg_name=msg_name, lower_name=lower_name
        )
        with open(os.path.join(src_dir, f"{lower_name}_multi_array__type_support.c"), "w") as f:
            f.write(ts_content)

        print(f"Generated: {msg_name}MultiArray")

    print(f"\nGenerated {len(MULTI_ARRAYS)} MultiArray message types")


if __name__ == "__main__":
    output_dir = sys.argv[1] if len(sys.argv) > 1 else "ohos_ros2/interfaces/std_msgs"
    generate_files(output_dir)
