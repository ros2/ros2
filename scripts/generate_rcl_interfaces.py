#!/usr/bin/env python3
"""Generate rcl_interfaces message and service files for OpenHarmony ROS2 port."""

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

# ============================================================================
# Message definitions
# ============================================================================

MESSAGES = {
    # ParameterType - Constants for parameter types
    "ParameterType": {
        "fields": [],
        "constants": [
            ("PARAMETER_NOT_SET", "uint8_t", 0),
            ("PARAMETER_BOOL", "uint8_t", 1),
            ("PARAMETER_INTEGER", "uint8_t", 2),
            ("PARAMETER_DOUBLE", "uint8_t", 3),
            ("PARAMETER_STRING", "uint8_t", 4),
            ("PARAMETER_BYTE_ARRAY", "uint8_t", 5),
            ("PARAMETER_BOOL_ARRAY", "uint8_t", 6),
            ("PARAMETER_INTEGER_ARRAY", "uint8_t", 7),
            ("PARAMETER_DOUBLE_ARRAY", "uint8_t", 8),
            ("PARAMETER_STRING_ARRAY", "uint8_t", 9),
        ],
        "includes": [],
        "description": "Constants for parameter types",
    },
    
    # ParameterValue - Actual parameter value
    "ParameterValue": {
        "fields": [
            ("type", "uint8_t", None),
            ("bool_value", "bool", None),
            ("integer_value", "int64_t", None),
            ("double_value", "double", None),
            ("string_value", "rosidl_runtime_c__String", None),
            ("byte_array_value", "rosidl_runtime_c__octet__Sequence", None),
            ("bool_array_value", "rosidl_runtime_c__boolean__Sequence", None),
            ("integer_array_value", "rosidl_runtime_c__int64__Sequence", None),
            ("double_array_value", "rosidl_runtime_c__double__Sequence", None),
            ("string_array_value", "rosidl_runtime_c__String__Sequence", None),
        ],
        "constants": [],
        "includes": ["rosidl_runtime_c/string.h", "rosidl_runtime_c/primitives_sequence.h"],
        "description": "Parameter value with type discriminator",
    },
    
    # Parameter - Named parameter with value
    "Parameter": {
        "fields": [
            ("name", "rosidl_runtime_c__String", None),
            ("value", f"{PKG}__msg__ParameterValue", None),
        ],
        "constants": [],
        "includes": ["rosidl_runtime_c/string.h", f"{PKG}/msg/parameter_value.h"],
        "description": "Named parameter with value",
    },
    
    # FloatingPointRange - Range constraint for floating point
    "FloatingPointRange": {
        "fields": [
            ("from_value", "double", None),
            ("to_value", "double", None),
            ("step", "double", None),
        ],
        "constants": [],
        "includes": [],
        "description": "Range constraint for floating point parameters",
    },
    
    # IntegerRange - Range constraint for integers
    "IntegerRange": {
        "fields": [
            ("from_value", "int64_t", None),
            ("to_value", "int64_t", None),
            ("step", "uint64_t", None),
        ],
        "constants": [],
        "includes": [],
        "description": "Range constraint for integer parameters",
    },
    
    # ParameterDescriptor - Description with constraints
    "ParameterDescriptor": {
        "fields": [
            ("name", "rosidl_runtime_c__String", None),
            ("type", "uint8_t", None),
            ("description", "rosidl_runtime_c__String", None),
            ("additional_constraints", "rosidl_runtime_c__String", None),
            ("read_only", "bool", None),
            ("dynamic_typing", "bool", None),
            ("floating_point_range", f"{PKG}__msg__FloatingPointRange__Sequence", None),
            ("integer_range", f"{PKG}__msg__IntegerRange__Sequence", None),
        ],
        "constants": [],
        "includes": [
            "rosidl_runtime_c/string.h",
            f"{PKG}/msg/floating_point_range.h",
            f"{PKG}/msg/integer_range.h",
        ],
        "description": "Parameter description with constraints",
    },
    
    # SetParametersResult - Result of setting a parameter
    "SetParametersResult": {
        "fields": [
            ("successful", "bool", None),
            ("reason", "rosidl_runtime_c__String", None),
        ],
        "constants": [],
        "includes": ["rosidl_runtime_c/string.h"],
        "description": "Result of setting a parameter",
    },
    
    # ListParametersResult - Result of listing parameters
    "ListParametersResult": {
        "fields": [
            ("names", "rosidl_runtime_c__String__Sequence", None),
            ("prefixes", "rosidl_runtime_c__String__Sequence", None),
        ],
        "constants": [],
        "includes": ["rosidl_runtime_c/string.h"],
        "description": "Result of listing parameters",
    },
    
    # ParameterEvent - Event when parameters change
    "ParameterEvent": {
        "fields": [
            ("stamp", "builtin_interfaces__msg__Time", None),
            ("node", "rosidl_runtime_c__String", None),
            ("new_parameters", f"{PKG}__msg__Parameter__Sequence", None),
            ("changed_parameters", f"{PKG}__msg__Parameter__Sequence", None),
            ("deleted_parameters", f"{PKG}__msg__Parameter__Sequence", None),
        ],
        "constants": [],
        "includes": [
            "builtin_interfaces/msg/time.h",
            "rosidl_runtime_c/string.h",
            f"{PKG}/msg/parameter.h",
        ],
        "description": "Event when parameters change",
    },
    
    # ParameterEventDescriptors - Descriptors for parameter events
    "ParameterEventDescriptors": {
        "fields": [
            ("new_parameters", f"{PKG}__msg__ParameterDescriptor__Sequence", None),
            ("changed_parameters", f"{PKG}__msg__ParameterDescriptor__Sequence", None),
            ("deleted_parameters", f"{PKG}__msg__ParameterDescriptor__Sequence", None),
        ],
        "constants": [],
        "includes": [f"{PKG}/msg/parameter_descriptor.h"],
        "description": "Descriptors for parameter events",
    },
    
    # Log - Log message
    "Log": {
        "fields": [
            ("stamp", "builtin_interfaces__msg__Time", None),
            ("level", "uint8_t", None),
            ("name", "rosidl_runtime_c__String", None),
            ("msg", "rosidl_runtime_c__String", None),
            ("file", "rosidl_runtime_c__String", None),
            ("function", "rosidl_runtime_c__String", None),
            ("line", "uint32_t", None),
        ],
        "constants": [
            ("DEBUG", "uint8_t", 10),
            ("INFO", "uint8_t", 20),
            ("WARN", "uint8_t", 30),
            ("ERROR", "uint8_t", 40),
            ("FATAL", "uint8_t", 50),
        ],
        "includes": [
            "builtin_interfaces/msg/time.h",
            "rosidl_runtime_c/string.h",
        ],
        "description": "Log message",
    },
}

# ============================================================================
# Service definitions
# ============================================================================

SERVICES = {
    "DescribeParameters": {
        "request": [("names", "rosidl_runtime_c__String__Sequence", None)],
        "response": [("descriptors", f"{PKG}__msg__ParameterDescriptor__Sequence", None)],
        "includes": ["rosidl_runtime_c/string.h", f"{PKG}/msg/parameter_descriptor.h"],
    },
    "GetParameters": {
        "request": [("names", "rosidl_runtime_c__String__Sequence", None)],
        "response": [("values", f"{PKG}__msg__ParameterValue__Sequence", None)],
        "includes": ["rosidl_runtime_c/string.h", f"{PKG}/msg/parameter_value.h"],
    },
    "GetParameterTypes": {
        "request": [("names", "rosidl_runtime_c__String__Sequence", None)],
        "response": [("types", "rosidl_runtime_c__uint8__Sequence", None)],
        "includes": ["rosidl_runtime_c/string.h", "rosidl_runtime_c/primitives_sequence.h"],
    },
    "ListParameters": {
        "request": [
            ("prefixes", "rosidl_runtime_c__String__Sequence", None),
            ("depth", "uint64_t", None),
        ],
        "response": [("result", f"{PKG}__msg__ListParametersResult", None)],
        "includes": ["rosidl_runtime_c/string.h", f"{PKG}/msg/list_parameters_result.h"],
        "constants": [("DEPTH_RECURSIVE", "uint64_t", 0)],
    },
    "SetParameters": {
        "request": [("parameters", f"{PKG}__msg__Parameter__Sequence", None)],
        "response": [("results", f"{PKG}__msg__SetParametersResult__Sequence", None)],
        "includes": [f"{PKG}/msg/parameter.h", f"{PKG}/msg/set_parameters_result.h"],
    },
    "SetParametersAtomically": {
        "request": [("parameters", f"{PKG}__msg__Parameter__Sequence", None)],
        "response": [("result", f"{PKG}__msg__SetParametersResult", None)],
        "includes": [f"{PKG}/msg/parameter.h", f"{PKG}/msg/set_parameters_result.h"],
    },
    "GetLoggerLevels": {
        "request": [("names", "rosidl_runtime_c__String__Sequence", None)],
        "response": [("levels", "rosidl_runtime_c__uint8__Sequence", None)],
        "includes": ["rosidl_runtime_c/string.h", "rosidl_runtime_c/primitives_sequence.h"],
    },
    "SetLoggerLevels": {
        "request": [
            ("levels", f"{PKG}__msg__SetLoggerLevelsRequest__Level__Sequence", None),
        ],
        "response": [
            ("results", f"{PKG}__msg__SetLoggerLevelsResponse__Result__Sequence", None),
        ],
        "includes": ["rosidl_runtime_c/string.h"],
        # This is a special case - has nested types
        "nested_request": [
            ("logger_name", "rosidl_runtime_c__String", None),
            ("level", "uint8_t", None),
        ],
        "nested_response": [
            ("successful", "bool", None),
            ("reason", "rosidl_runtime_c__String", None),
        ],
    },
}


def get_init_code(field_name, field_type):
    """Generate initialization code for a field."""
    if field_type == "rosidl_runtime_c__String":
        return f"  rosidl_runtime_c__String__init(&msg->{field_name});"
    elif field_type.endswith("__Sequence"):
        return f"  // {field_name} sequence initialized to empty"
    elif field_type.startswith("builtin_interfaces__msg__"):
        type_name = field_type.replace("builtin_interfaces__msg__", "")
        return f"  builtin_interfaces__msg__{type_name}__init(&msg->{field_name});"
    elif field_type.startswith(f"{PKG}__msg__"):
        type_name = field_type.replace(f"{PKG}__msg__", "")
        return f"  {PKG}__msg__{type_name}__init(&msg->{field_name});"
    elif field_type in ["bool", "uint8_t", "int8_t", "uint16_t", "int16_t", 
                         "uint32_t", "int32_t", "uint64_t", "int64_t", 
                         "float", "double"]:
        return f"  msg->{field_name} = 0;"
    return f"  // TODO: Initialize {field_name}"


def get_fini_code(field_name, field_type):
    """Generate finalization code for a field."""
    if field_type == "rosidl_runtime_c__String":
        return f"  rosidl_runtime_c__String__fini(&msg->{field_name});"
    elif field_type.endswith("__Sequence"):
        # Try to determine base type for sequence fini
        base_type = field_type.replace("__Sequence", "")
        if base_type == "rosidl_runtime_c__String":
            return f"  rosidl_runtime_c__String__Sequence__fini(&msg->{field_name});"
        elif base_type.startswith("rosidl_runtime_c__"):
            prim_type = base_type.replace("rosidl_runtime_c__", "")
            return f"  rosidl_runtime_c__{prim_type}__Sequence__fini(&msg->{field_name});"
        elif base_type.startswith(f"{PKG}__msg__"):
            type_name = base_type.replace(f"{PKG}__msg__", "")
            return f"  {PKG}__msg__{type_name}__Sequence__fini(&msg->{field_name});"
        return f"  // TODO: Finalize {field_name} sequence"
    elif field_type.startswith("builtin_interfaces__msg__"):
        type_name = field_type.replace("builtin_interfaces__msg__", "")
        return f"  builtin_interfaces__msg__{type_name}__fini(&msg->{field_name});"
    elif field_type.startswith(f"{PKG}__msg__"):
        type_name = field_type.replace(f"{PKG}__msg__", "")
        return f"  {PKG}__msg__{type_name}__fini(&msg->{field_name});"
    return ""


def generate_message_header(msg_name, msg_def):
    """Generate header file for a message."""
    snake_name = to_snake_case(msg_name)
    fields = msg_def["fields"]
    constants = msg_def.get("constants", [])
    includes = msg_def.get("includes", [])
    description = msg_def.get("description", "")
    
    guard = f"{PKG.upper()}__MSG__{msg_name.upper()}_H_"
    
    include_lines = [f'#include "{inc}"' for inc in includes]
    include_block = '\n'.join(include_lines) if include_lines else ""
    
    # Constants
    const_lines = []
    for const_name, const_type, const_val in constants:
        const_lines.append(f"#define {PKG.upper()}__MSG__{msg_name.upper()}__{const_name} (({const_type}){const_val})")
    const_block = '\n'.join(const_lines) if const_lines else ""
    
    # Struct fields
    field_lines = []
    for fname, ftype, _ in fields:
        field_lines.append(f"  {ftype} {fname};")
    fields_block = '\n'.join(field_lines) if field_lines else "  uint8_t structure_needs_at_least_one_member;"
    
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "{PKG}/msg/rosidl_generator_c__visibility_control.h"

{include_block}

#ifdef __cplusplus
extern "C" {{
#endif

{const_block}

/// {description}
typedef struct {PKG}__msg__{msg_name}
{{
{fields_block}
}} {PKG}__msg__{msg_name};

typedef struct {PKG}__msg__{msg_name}__Sequence
{{
  {PKG}__msg__{msg_name} * data;
  size_t size;
  size_t capacity;
}} {PKG}__msg__{msg_name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
bool {PKG}__msg__{msg_name}__init({PKG}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
void {PKG}__msg__{msg_name}__fini({PKG}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
{PKG}__msg__{msg_name} * {PKG}__msg__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
void {PKG}__msg__{msg_name}__destroy({PKG}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
bool {PKG}__msg__{msg_name}__Sequence__init(
  {PKG}__msg__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
void {PKG}__msg__{msg_name}__Sequence__fini(
  {PKG}__msg__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_message_functions(msg_name, msg_def):
    """Generate functions file for a message."""
    snake_name = to_snake_case(msg_name)
    fields = msg_def["fields"]
    
    init_lines = [get_init_code(fname, ftype) for fname, ftype, _ in fields]
    init_block = '\n'.join(init_lines) if init_lines else "  (void)msg;"
    
    fini_lines = [get_fini_code(fname, ftype) for fname, ftype, _ in fields]
    fini_lines = [l for l in fini_lines if l]  # Remove empty lines
    fini_block = '\n'.join(fini_lines) if fini_lines else "  (void)msg;"
    
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} functions

#include "{PKG}/msg/{snake_name}.h"
#include "rcutils/allocator.h"
#include <string.h>

bool {PKG}__msg__{msg_name}__init({PKG}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return false;
  }}
{init_block}
  return true;
}}

void {PKG}__msg__{msg_name}__fini({PKG}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return;
  }}
{fini_block}
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


def generate_message_type_support(msg_name):
    """Generate type support file for a message."""
    snake_name = to_snake_case(msg_name)
    
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/msg/{msg_name} type support

#include "{PKG}/msg/{snake_name}.h"
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


def generate_service_header(srv_name, srv_def):
    """Generate header file for a service."""
    snake_name = to_snake_case(srv_name)
    request_fields = srv_def["request"]
    response_fields = srv_def["response"]
    includes = srv_def.get("includes", [])
    constants = srv_def.get("constants", [])
    
    guard = f"{PKG.upper()}__SRV__{srv_name.upper()}_H_"
    
    include_lines = [f'#include "{inc}"' for inc in includes]
    include_block = '\n'.join(include_lines) if include_lines else ""
    
    # Constants for request
    const_lines = []
    for const_name, const_type, const_val in constants:
        const_lines.append(f"#define {PKG.upper()}__SRV__{srv_name.upper()}__REQUEST__{const_name} (({const_type}){const_val}U)")
    const_block = '\n'.join(const_lines) if const_lines else ""
    
    # Request fields
    req_field_lines = []
    for fname, ftype, _ in request_fields:
        req_field_lines.append(f"  {ftype} {fname};")
    req_fields_block = '\n'.join(req_field_lines) if req_field_lines else "  uint8_t structure_needs_at_least_one_member;"
    
    # Response fields
    resp_field_lines = []
    for fname, ftype, _ in response_fields:
        resp_field_lines.append(f"  {ftype} {fname};")
    resp_fields_block = '\n'.join(resp_field_lines) if resp_field_lines else "  uint8_t structure_needs_at_least_one_member;"
    
    # Handle nested types for SetLoggerLevels
    nested_types = ""
    if "nested_request" in srv_def:
        nested_req = srv_def["nested_request"]
        nested_req_fields = '\n'.join([f"  {ftype} {fname};" for fname, ftype, _ in nested_req])
        nested_types += f'''
// Nested type for request
typedef struct {PKG}__srv__{srv_name}__Request__Level
{{
{nested_req_fields}
}} {PKG}__srv__{srv_name}__Request__Level;

typedef struct {PKG}__srv__{srv_name}__Request__Level__Sequence
{{
  {PKG}__srv__{srv_name}__Request__Level * data;
  size_t size;
  size_t capacity;
}} {PKG}__srv__{srv_name}__Request__Level__Sequence;
'''
        # Update request fields to use the sequence type
        req_fields_block = f"  {PKG}__srv__{srv_name}__Request__Level__Sequence levels;"
    
    if "nested_response" in srv_def:
        nested_resp = srv_def["nested_response"]
        nested_resp_fields = '\n'.join([f"  {ftype} {fname};" for fname, ftype, _ in nested_resp])
        nested_types += f'''
// Nested type for response
typedef struct {PKG}__srv__{srv_name}__Response__Result
{{
{nested_resp_fields}
}} {PKG}__srv__{srv_name}__Response__Result;

typedef struct {PKG}__srv__{srv_name}__Response__Result__Sequence
{{
  {PKG}__srv__{srv_name}__Response__Result * data;
  size_t size;
  size_t capacity;
}} {PKG}__srv__{srv_name}__Response__Result__Sequence;
'''
        # Update response fields to use the sequence type
        resp_fields_block = f"  {PKG}__srv__{srv_name}__Response__Result__Sequence results;"
    
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{srv_name} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "{PKG}/msg/rosidl_generator_c__visibility_control.h"

{include_block}

#ifdef __cplusplus
extern "C" {{
#endif

{const_block}
{nested_types}

// =============================================================================
// {srv_name} Request
// =============================================================================

typedef struct {PKG}__srv__{srv_name}__Request
{{
{req_fields_block}
}} {PKG}__srv__{srv_name}__Request;

typedef struct {PKG}__srv__{srv_name}__Request__Sequence
{{
  {PKG}__srv__{srv_name}__Request * data;
  size_t size;
  size_t capacity;
}} {PKG}__srv__{srv_name}__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
bool {PKG}__srv__{srv_name}__Request__init({PKG}__srv__{srv_name}__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
void {PKG}__srv__{srv_name}__Request__fini({PKG}__srv__{srv_name}__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
{PKG}__srv__{srv_name}__Request * {PKG}__srv__{srv_name}__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
void {PKG}__srv__{srv_name}__Request__destroy({PKG}__srv__{srv_name}__Request * msg);

// =============================================================================
// {srv_name} Response
// =============================================================================

typedef struct {PKG}__srv__{srv_name}__Response
{{
{resp_fields_block}
}} {PKG}__srv__{srv_name}__Response;

typedef struct {PKG}__srv__{srv_name}__Response__Sequence
{{
  {PKG}__srv__{srv_name}__Response * data;
  size_t size;
  size_t capacity;
}} {PKG}__srv__{srv_name}__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
bool {PKG}__srv__{srv_name}__Response__init({PKG}__srv__{srv_name}__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
void {PKG}__srv__{srv_name}__Response__fini({PKG}__srv__{srv_name}__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
{PKG}__srv__{srv_name}__Response * {PKG}__srv__{srv_name}__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_{PKG}
void {PKG}__srv__{srv_name}__Response__destroy({PKG}__srv__{srv_name}__Response * msg);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_service_functions(srv_name, srv_def):
    """Generate functions file for a service."""
    snake_name = to_snake_case(srv_name)
    request_fields = srv_def["request"]
    response_fields = srv_def["response"]
    
    # Check for nested types
    has_nested_req = "nested_request" in srv_def
    has_nested_resp = "nested_response" in srv_def
    
    if has_nested_req:
        req_init = f"  // Initialize levels sequence (empty)"
        req_fini = f"  // Finalize levels sequence"
    else:
        req_init_lines = [get_init_code(fname, ftype) for fname, ftype, _ in request_fields]
        req_init = '\n'.join(req_init_lines) if req_init_lines else "  (void)msg;"
        req_fini_lines = [get_fini_code(fname, ftype) for fname, ftype, _ in request_fields]
        req_fini_lines = [l for l in req_fini_lines if l]
        req_fini = '\n'.join(req_fini_lines) if req_fini_lines else "  (void)msg;"
    
    if has_nested_resp:
        resp_init = f"  // Initialize results sequence (empty)"
        resp_fini = f"  // Finalize results sequence"
    else:
        resp_init_lines = [get_init_code(fname, ftype) for fname, ftype, _ in response_fields]
        resp_init = '\n'.join(resp_init_lines) if resp_init_lines else "  (void)msg;"
        resp_fini_lines = [get_fini_code(fname, ftype) for fname, ftype, _ in response_fields]
        resp_fini_lines = [l for l in resp_fini_lines if l]
        resp_fini = '\n'.join(resp_fini_lines) if resp_fini_lines else "  (void)msg;"
    
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{srv_name} functions

#include "{PKG}/srv/{snake_name}.h"
#include "rcutils/allocator.h"
#include <string.h>

// =============================================================================
// {srv_name} Request
// =============================================================================

bool {PKG}__srv__{srv_name}__Request__init({PKG}__srv__{srv_name}__Request * msg)
{{
  if (!msg) {{
    return false;
  }}
{req_init}
  return true;
}}

void {PKG}__srv__{srv_name}__Request__fini({PKG}__srv__{srv_name}__Request * msg)
{{
  if (!msg) {{
    return;
  }}
{req_fini}
}}

{PKG}__srv__{srv_name}__Request * {PKG}__srv__{srv_name}__Request__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {PKG}__srv__{srv_name}__Request * msg = ({PKG}__srv__{srv_name}__Request *)allocator.allocate(
    sizeof({PKG}__srv__{srv_name}__Request), allocator.state);
  if (!msg) {{
    return NULL;
  }}
  if (!{PKG}__srv__{srv_name}__Request__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void {PKG}__srv__{srv_name}__Request__destroy({PKG}__srv__{srv_name}__Request * msg)
{{
  if (!msg) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {PKG}__srv__{srv_name}__Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

// =============================================================================
// {srv_name} Response
// =============================================================================

bool {PKG}__srv__{srv_name}__Response__init({PKG}__srv__{srv_name}__Response * msg)
{{
  if (!msg) {{
    return false;
  }}
{resp_init}
  return true;
}}

void {PKG}__srv__{srv_name}__Response__fini({PKG}__srv__{srv_name}__Response * msg)
{{
  if (!msg) {{
    return;
  }}
{resp_fini}
}}

{PKG}__srv__{srv_name}__Response * {PKG}__srv__{srv_name}__Response__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {PKG}__srv__{srv_name}__Response * msg = ({PKG}__srv__{srv_name}__Response *)allocator.allocate(
    sizeof({PKG}__srv__{srv_name}__Response), allocator.state);
  if (!msg) {{
    return NULL;
  }}
  if (!{PKG}__srv__{srv_name}__Response__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void {PKG}__srv__{srv_name}__Response__destroy({PKG}__srv__{srv_name}__Response * msg)
{{
  if (!msg) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {PKG}__srv__{srv_name}__Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}
'''


def generate_service_type_support(srv_name):
    """Generate type support file for a service."""
    snake_name = to_snake_case(srv_name)
    
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// {PKG}/srv/{srv_name} type support

#include "{PKG}/srv/{snake_name}.h"
#include "rosidl_typesupport_c/service_type_support.h"
#include "rosidl_runtime_c/service_type_support_struct.h"

// Request type support
static rosidl_message_type_support_t {PKG}__srv__{srv_name}__Request__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, srv, {srv_name}_Request)()
{{
  return &{PKG}__srv__{srv_name}__Request__type_support_handle;
}}

// Response type support
static rosidl_message_type_support_t {PKG}__srv__{srv_name}__Response__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, srv, {srv_name}_Response)()
{{
  return &{PKG}__srv__{srv_name}__Response__type_support_handle;
}}

// Service type support
static rosidl_service_type_support_t {PKG}__srv__{srv_name}__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c, {PKG}, srv, {srv_name})()
{{
  return &{PKG}__srv__{srv_name}__type_support_handle;
}}
'''


def main():
    print(f"Generating {PKG} interface files...")
    
    # Generate message files
    print("\nGenerating messages:")
    for msg_name, msg_def in MESSAGES.items():
        snake_name = to_snake_case(msg_name)
        
        # Header
        header_path = f"{BASE_DIR}/include/{PKG}/msg/{snake_name}.h"
        write_file(header_path, generate_message_header(msg_name, msg_def))
        
        # Functions
        func_path = f"{BASE_DIR}/src/msg/{snake_name}__functions.c"
        write_file(func_path, generate_message_functions(msg_name, msg_def))
        
        # Type support
        ts_path = f"{BASE_DIR}/src/msg/{snake_name}__type_support.c"
        write_file(ts_path, generate_message_type_support(msg_name))
    
    # Generate service files
    print("\nGenerating services:")
    for srv_name, srv_def in SERVICES.items():
        snake_name = to_snake_case(srv_name)
        
        # Header
        header_path = f"{BASE_DIR}/include/{PKG}/srv/{snake_name}.h"
        write_file(header_path, generate_service_header(srv_name, srv_def))
        
        # Functions
        func_path = f"{BASE_DIR}/src/srv/{snake_name}__functions.c"
        write_file(func_path, generate_service_functions(srv_name, srv_def))
        
        # Type support
        ts_path = f"{BASE_DIR}/src/srv/{snake_name}__type_support.c"
        write_file(ts_path, generate_service_type_support(srv_name))
    
    print(f"\nGeneration complete!")
    print(f"Messages: {len(MESSAGES)}")
    print(f"Services: {len(SERVICES)}")


if __name__ == "__main__":
    main()
