#!/usr/bin/env python3
"""Generate rcl_interfaces C++ type support and FastRTPS stub files."""

import os

BASE_DIR = "/home/jiusi/M-DDS/ohos_ros2/interfaces/rcl_interfaces"
PKG = "rcl_interfaces"

def to_snake_case(name):
    result = []
    for i, c in enumerate(name):
        if c.isupper() and i > 0:
            result.append('_')
        result.append(c.lower())
    return ''.join(result)

def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)
    print(f"  Created: {path}")


MESSAGES = [
    "ParameterType", "ParameterValue", "Parameter", "FloatingPointRange",
    "IntegerRange", "ParameterDescriptor", "SetParametersResult",
    "ListParametersResult", "ParameterEvent", "ParameterEventDescriptors", "Log"
]

SERVICES = [
    "DescribeParameters", "GetParameters", "GetParameterTypes", "ListParameters",
    "SetParameters", "SetParametersAtomically", "GetLoggerLevels", "SetLoggerLevels"
]


def generate_msg_cpp_type_support(msg_name):
    snake_name = to_snake_case(msg_name)
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} C++ type support

#include "{PKG}/msg/{snake_name}.h"
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


def generate_msg_fastrtps_c(msg_name):
    snake_name = to_snake_case(msg_name)
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} FastRTPS C type support

#include "{PKG}/msg/{snake_name}.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"

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


def generate_srv_cpp_type_support(srv_name):
    snake_name = to_snake_case(srv_name)
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{srv_name} C++ type support

#include "{PKG}/srv/{snake_name}.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace rosidl_typesupport_cpp
{{

template<>
const rosidl_service_type_support_t *
get_service_type_support_handle<{PKG}::srv::{srv_name}>()
{{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, {PKG}, srv, {srv_name})();
}}

}}  // namespace rosidl_typesupport_cpp
'''


def generate_srv_fastrtps_c(srv_name):
    snake_name = to_snake_case(srv_name)
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{srv_name} FastRTPS C type support

#include "{PKG}/srv/{snake_name}.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{{

// Request type support
static const rosidl_message_type_support_t {PKG}__srv__{srv_name}__Request__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, srv, {srv_name}_Request)()
{{
  return &{PKG}__srv__{srv_name}__Request__fastrtps_type_support;
}}

// Response type support
static const rosidl_message_type_support_t {PKG}__srv__{srv_name}__Response__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, srv, {srv_name}_Response)()
{{
  return &{PKG}__srv__{srv_name}__Response__fastrtps_type_support;
}}

// Service type support
static const rosidl_service_type_support_t {PKG}__srv__{srv_name}__fastrtps_type_support = {{
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
}};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, {PKG}, srv, {srv_name})()
{{
  return &{PKG}__srv__{srv_name}__fastrtps_type_support;
}}

}}  // extern "C"
'''


def main():
    print(f"Generating {PKG} C++/FastRTPS type support files...")
    
    # Generate message C++ type support
    print("\nGenerating message C++ type support:")
    for msg_name in MESSAGES:
        snake_name = to_snake_case(msg_name)
        
        # C++ type support
        cpp_path = f"{BASE_DIR}/src/msg/{snake_name}__type_support.cpp"
        write_file(cpp_path, generate_msg_cpp_type_support(msg_name))
        
        # FastRTPS C type support
        fastrtps_path = f"{BASE_DIR}/src/msg/{snake_name}__rosidl_typesupport_fastrtps_c.cpp"
        write_file(fastrtps_path, generate_msg_fastrtps_c(msg_name))
    
    # Generate service C++ type support
    print("\nGenerating service C++ type support:")
    for srv_name in SERVICES:
        snake_name = to_snake_case(srv_name)
        
        # C++ type support
        cpp_path = f"{BASE_DIR}/src/srv/{snake_name}__type_support.cpp"
        write_file(cpp_path, generate_srv_cpp_type_support(srv_name))
        
        # FastRTPS C type support
        fastrtps_path = f"{BASE_DIR}/src/srv/{snake_name}__rosidl_typesupport_fastrtps_c.cpp"
        write_file(fastrtps_path, generate_srv_fastrtps_c(srv_name))
    
    print(f"\nGeneration complete!")


if __name__ == "__main__":
    main()
