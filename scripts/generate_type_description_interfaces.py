#!/usr/bin/env python3
"""Generate type_description_interfaces source files."""

import os

BASE_DIR = "/home/jiusi/M-DDS/ohos_ros2/interfaces/type_description_interfaces"
PKG = "type_description_interfaces"

def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  Created: {path}")

MESSAGES = {
    "FieldType": {
        "snake": "field_type",
        "init": '''  msg->type_id = 0;
  msg->capacity = 0;
  msg->string_capacity = 0;
  rosidl_runtime_c__String__init(&msg->nested_type_name);''',
        "fini": '''  rosidl_runtime_c__String__fini(&msg->nested_type_name);''',
    },
    "Field": {
        "snake": "field",
        "init": '''  rosidl_runtime_c__String__init(&msg->name);
  if (!type_description_interfaces__msg__FieldType__init(&msg->type)) {
    return false;
  }
  rosidl_runtime_c__String__init(&msg->default_value);''',
        "fini": '''  rosidl_runtime_c__String__fini(&msg->name);
  type_description_interfaces__msg__FieldType__fini(&msg->type);
  rosidl_runtime_c__String__fini(&msg->default_value);''',
    },
    "IndividualTypeDescription": {
        "snake": "individual_type_description",
        "init": '''  rosidl_runtime_c__String__init(&msg->type_name);
  msg->fields.data = NULL;
  msg->fields.size = 0;
  msg->fields.capacity = 0;''',
        "fini": '''  rosidl_runtime_c__String__fini(&msg->type_name);
  type_description_interfaces__msg__Field__Sequence__fini(&msg->fields);''',
    },
    "TypeDescription": {
        "snake": "type_description",
        "init": '''  if (!type_description_interfaces__msg__IndividualTypeDescription__init(&msg->type_description)) {
    return false;
  }
  msg->referenced_type_descriptions.data = NULL;
  msg->referenced_type_descriptions.size = 0;
  msg->referenced_type_descriptions.capacity = 0;''',
        "fini": '''  type_description_interfaces__msg__IndividualTypeDescription__fini(&msg->type_description);
  type_description_interfaces__msg__IndividualTypeDescription__Sequence__fini(&msg->referenced_type_descriptions);''',
    },
    "TypeSource": {
        "snake": "type_source",
        "init": '''  rosidl_runtime_c__String__init(&msg->type_name);
  rosidl_runtime_c__String__init(&msg->encoding);
  rosidl_runtime_c__String__init(&msg->raw_source);''',
        "fini": '''  rosidl_runtime_c__String__fini(&msg->type_name);
  rosidl_runtime_c__String__fini(&msg->encoding);
  rosidl_runtime_c__String__fini(&msg->raw_source);''',
    },
    "KeyValue": {
        "snake": "key_value",
        "init": '''  rosidl_runtime_c__String__init(&msg->key);
  rosidl_runtime_c__String__init(&msg->value);''',
        "fini": '''  rosidl_runtime_c__String__fini(&msg->key);
  rosidl_runtime_c__String__fini(&msg->value);''',
    },
}


def generate_functions(msg_name, msg_info):
    snake = msg_info["snake"]
    init_code = msg_info["init"]
    fini_code = msg_info["fini"]
    
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} functions

#include "{PKG}/msg/{snake}.h"
#include "rcutils/allocator.h"
#include <string.h>

bool {PKG}__msg__{msg_name}__init({PKG}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return false;
  }}
{init_code}
  return true;
}}

void {PKG}__msg__{msg_name}__fini({PKG}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return;
  }}
{fini_code}
}}

{PKG}__msg__{msg_name} * {PKG}__msg__{msg_name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {PKG}__msg__{msg_name} * msg = ({PKG}__msg__{msg_name} *)allocator.allocate(
    sizeof({PKG}__msg__{msg_name}), allocator.state);
  if (!msg) {{
    return NULL;
  }}
  if (!{PKG}__msg__{msg_name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void {PKG}__msg__{msg_name}__destroy({PKG}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {PKG}__msg__{msg_name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool {PKG}__msg__{msg_name}__Sequence__init(
  {PKG}__msg__{msg_name}__Sequence * array, size_t size)
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

  array->data = ({PKG}__msg__{msg_name} *)allocator.zero_allocate(
    size, sizeof({PKG}__msg__{msg_name}), allocator.state);
  if (!array->data) {{
    return false;
  }}

  for (size_t i = 0; i < size; ++i) {{
    if (!{PKG}__msg__{msg_name}__init(&array->data[i])) {{
      for (size_t j = 0; j < i; ++j) {{
        {PKG}__msg__{msg_name}__fini(&array->data[j]);
      }}
      allocator.deallocate(array->data, allocator.state);
      return false;
    }}
  }}

  array->size = size;
  array->capacity = size;
  return true;
}}

void {PKG}__msg__{msg_name}__Sequence__fini(
  {PKG}__msg__{msg_name}__Sequence * array)
{{
  if (!array || !array->data) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {{
    {PKG}__msg__{msg_name}__fini(&array->data[i]);
  }}
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}}
'''


def generate_type_support_c(msg_name, snake):
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} type support

#include "{PKG}/msg/{snake}.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t {PKG}__msg__{msg_name}__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, msg, {msg_name})()
{{
  return &{PKG}__msg__{msg_name}__type_support_handle;
}}
'''


def generate_type_support_cpp(msg_name, snake):
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} C++ type support

#include "{PKG}/msg/{snake}.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<{PKG}::msg::{msg_name}>()
{{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, {PKG}, msg, {msg_name})();
}}

}}  // namespace rosidl_typesupport_cpp
'''


def generate_fastrtps_c(msg_name, snake):
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} FastRTPS C type support

#include "{PKG}/msg/{snake}.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{{

static const rosidl_message_type_support_t {PKG}__msg__{msg_name}__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, msg, {msg_name})()
{{
  return &{PKG}__msg__{msg_name}__fastrtps_type_support;
}}

}}  // extern "C"
'''


def main():
    print(f"Generating {PKG} source files...")
    
    for msg_name, msg_info in MESSAGES.items():
        snake = msg_info["snake"]
        
        # Functions
        write_file(f"{BASE_DIR}/src/msg/{snake}__functions.c", 
                   generate_functions(msg_name, msg_info))
        
        # Type support C
        write_file(f"{BASE_DIR}/src/msg/{snake}__type_support.c",
                   generate_type_support_c(msg_name, snake))
        
        # Type support C++
        write_file(f"{BASE_DIR}/src/msg/{snake}__type_support.cpp",
                   generate_type_support_cpp(msg_name, snake))
        
        # FastRTPS
        write_file(f"{BASE_DIR}/src/msg/{snake}__rosidl_typesupport_fastrtps_c.cpp",
                   generate_fastrtps_c(msg_name, snake))
    
    print(f"\nGeneration complete! Messages: {len(MESSAGES)}")


if __name__ == "__main__":
    main()
