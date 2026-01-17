#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generate stub type support files for rcl_interfaces

import os
import sys

OUTPUT_DIR = sys.argv[1] if len(sys.argv) > 1 else "ohos_ros2/interfaces/rcl_interfaces"

# Messages that need type support stubs
MESSAGES = [
    "parameter_value",
    "parameter_descriptor",
    "parameter",
    "set_parameters_result",
    "list_parameters_result",
    "parameter_event",
    "parameter_event_descriptors",
    "log",
    "logger_level",
    "set_logger_levels_result",
]

# Services that need type support stubs
SERVICES = [
    "get_parameters",
    "set_parameters",
    "describe_parameters",
    "list_parameters",
    "get_parameter_types",
    "set_parameters_atomically",
    "get_logger_levels",
    "set_logger_levels",
]

TYPE_SUPPORT_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/{msg_name} type support (stub)

#include "rcl_interfaces/msg/{lower_name}.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

// Stub type support - member introspection details omitted for brevity
static const rosidl_typesupport_introspection_c__MessageMembers
rcl_interfaces__msg__{msg_name}__message_members = {{
  "rcl_interfaces", "{msg_name}", 0, sizeof(rcl_interfaces__msg__{msg_name}), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)rcl_interfaces__msg__{msg_name}__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)rcl_interfaces__msg__{msg_name}__fini
}};

static rosidl_message_type_support_t rcl_interfaces__msg__{msg_name}__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &rcl_interfaces__msg__{msg_name}__message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__{msg_name}__type_support
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, rcl_interfaces, msg, {msg_name})()
{{
  return &rcl_interfaces__msg__{msg_name}__type_support;
}}
'''

SERVICE_TYPE_SUPPORT_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/{srv_name} type support (stub)

#include "rcl_interfaces/srv/{lower_name}.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// Request type support
static const rosidl_typesupport_introspection_c__MessageMembers
rcl_interfaces__srv__{srv_name}_Request__message_members = {{
  "rcl_interfaces", "{srv_name}_Request", 0, sizeof(rcl_interfaces__srv__{srv_name}_Request), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)rcl_interfaces__srv__{srv_name}_Request__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)rcl_interfaces__srv__{srv_name}_Request__fini
}};

static rosidl_message_type_support_t rcl_interfaces__srv__{srv_name}_Request__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &rcl_interfaces__srv__{srv_name}_Request__message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__{srv_name}_Request__type_support
}};

// Response type support
static const rosidl_typesupport_introspection_c__MessageMembers
rcl_interfaces__srv__{srv_name}_Response__message_members = {{
  "rcl_interfaces", "{srv_name}_Response", 0, sizeof(rcl_interfaces__srv__{srv_name}_Response), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)rcl_interfaces__srv__{srv_name}_Response__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)rcl_interfaces__srv__{srv_name}_Response__fini
}};

static rosidl_message_type_support_t rcl_interfaces__srv__{srv_name}_Response__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &rcl_interfaces__srv__{srv_name}_Response__message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__{srv_name}_Response__type_support
}};

// Service type support
static const rosidl_typesupport_introspection_c__ServiceMembers
rcl_interfaces__srv__{srv_name}__service_members = {{
  "rcl_interfaces", "{srv_name}",
  &rcl_interfaces__srv__{srv_name}_Request__type_support,
  &rcl_interfaces__srv__{srv_name}_Response__type_support
}};

static rosidl_service_type_support_t rcl_interfaces__srv__{srv_name}__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &rcl_interfaces__srv__{srv_name}__service_members,
  get_service_typesupport_handle_function,
  &rcl_interfaces__srv__{srv_name}__type_support
}};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, rcl_interfaces, srv, {srv_name})()
{{
  return &rcl_interfaces__srv__{srv_name}__type_support;
}}
'''

CPP_TYPE_SUPPORT_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/{msg_name} C++ type support (stub)

#include "rcl_interfaces/msg/{lower_name}.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"

namespace rosidl_typesupport_cpp
{{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces__msg__{msg_name}>()
{{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_introspection_c, rcl_interfaces, msg, {msg_name})();
}}

}}  // namespace rosidl_typesupport_cpp
'''

SERVICE_CPP_TYPE_SUPPORT_TEMPLATE = '''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/{srv_name} C++ type support (stub)

#include "rcl_interfaces/srv/{lower_name}.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"

namespace rosidl_typesupport_cpp
{{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<rcl_interfaces__srv__{srv_name}>()
{{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_introspection_c, rcl_interfaces, srv, {srv_name})();
}}

}}  // namespace rosidl_typesupport_cpp
'''


def to_pascal_case(name):
    """Convert snake_case to PascalCase"""
    return ''.join(word.capitalize() for word in name.split('_'))


def generate_files():
    msg_src_dir = os.path.join(OUTPUT_DIR, "src", "msg")
    srv_src_dir = os.path.join(OUTPUT_DIR, "src", "srv")
    os.makedirs(msg_src_dir, exist_ok=True)
    os.makedirs(srv_src_dir, exist_ok=True)

    # Generate message type support
    for lower_name in MESSAGES:
        msg_name = to_pascal_case(lower_name)

        # C type support
        ts_content = TYPE_SUPPORT_TEMPLATE.format(
            msg_name=msg_name, lower_name=lower_name
        )
        with open(os.path.join(msg_src_dir, f"{lower_name}__type_support.c"), "w") as f:
            f.write(ts_content)

        # C++ type support
        cpp_content = CPP_TYPE_SUPPORT_TEMPLATE.format(
            msg_name=msg_name, lower_name=lower_name
        )
        with open(os.path.join(msg_src_dir, f"{lower_name}__type_support.cpp"), "w") as f:
            f.write(cpp_content)

        print(f"Generated message type support: {msg_name}")

    # Generate service type support
    for lower_name in SERVICES:
        srv_name = to_pascal_case(lower_name)

        # C type support
        ts_content = SERVICE_TYPE_SUPPORT_TEMPLATE.format(
            srv_name=srv_name, lower_name=lower_name
        )
        with open(os.path.join(srv_src_dir, f"{lower_name}__type_support.c"), "w") as f:
            f.write(ts_content)

        # C++ type support
        cpp_content = SERVICE_CPP_TYPE_SUPPORT_TEMPLATE.format(
            srv_name=srv_name, lower_name=lower_name
        )
        with open(os.path.join(srv_src_dir, f"{lower_name}__type_support.cpp"), "w") as f:
            f.write(cpp_content)

        print(f"Generated service type support: {srv_name}")

    print(f"\nGenerated {len(MESSAGES)} message types and {len(SERVICES)} service types")


if __name__ == "__main__":
    generate_files()
