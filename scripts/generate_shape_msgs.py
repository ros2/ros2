#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generator for shape_msgs message types

import os
import sys

def generate_header(msg_name, snake_name, fields, includes, constants=None):
    """Generate message header file"""
    pkg = "shape_msgs"
    guard = f"SHAPE_MSGS__MSG__{msg_name.upper()}_H_"

    include_lines = '\n'.join([f'#include "{inc}"' for inc in includes])

    const_lines = ""
    if constants:
        const_lines = "\n// Constants\n"
        for const_name, const_type, const_value in constants:
            const_lines += f"#define SHAPE_MSGS__MSG__{msg_name}_{const_name} {const_value}\n"

    field_lines = '\n'.join([f"  {ftype} {fname};" for ftype, fname in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/{msg_name} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "shape_msgs/msg/rosidl_generator_c__visibility_control.h"
{include_lines}

#ifdef __cplusplus
extern "C" {{
#endif
{const_lines}
typedef struct {pkg}__msg__{msg_name}
{{
{field_lines}
}} {pkg}__msg__{msg_name};

typedef struct {pkg}__msg__{msg_name}__Sequence
{{
  {pkg}__msg__{msg_name} * data;
  size_t size;
  size_t capacity;
}} {pkg}__msg__{msg_name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool {pkg}__msg__{msg_name}__init({pkg}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void {pkg}__msg__{msg_name}__fini({pkg}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
{pkg}__msg__{msg_name} * {pkg}__msg__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void {pkg}__msg__{msg_name}__destroy({pkg}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool {pkg}__msg__{msg_name}__Sequence__init(
  {pkg}__msg__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void {pkg}__msg__{msg_name}__Sequence__fini(
  {pkg}__msg__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_functions(msg_name, snake_name, init_code, fini_code):
    """Generate message functions implementation"""
    pkg = "shape_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/{msg_name} functions

#include "shape_msgs/msg/{snake_name}.h"
#include "rcutils/allocator.h"
#include <string.h>

bool {pkg}__msg__{msg_name}__init({pkg}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return false;
  }}
  memset(msg, 0, sizeof(*msg));
{init_code}
  return true;
}}

void {pkg}__msg__{msg_name}__fini({pkg}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return;
  }}
{fini_code}
}}

{pkg}__msg__{msg_name} * {pkg}__msg__{msg_name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {pkg}__msg__{msg_name} * msg = ({pkg}__msg__{msg_name} *)allocator.allocate(
    sizeof({pkg}__msg__{msg_name}), allocator.state);
  if (!msg) {{
    return NULL;
  }}
  if (!{pkg}__msg__{msg_name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void {pkg}__msg__{msg_name}__destroy({pkg}__msg__{msg_name} * msg)
{{
  if (!msg) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  {pkg}__msg__{msg_name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool {pkg}__msg__{msg_name}__Sequence__init(
  {pkg}__msg__{msg_name}__Sequence * array, size_t size)
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

  array->data = ({pkg}__msg__{msg_name} *)allocator.zero_allocate(
    size, sizeof({pkg}__msg__{msg_name}), allocator.state);
  if (!array->data) {{
    return false;
  }}

  for (size_t i = 0; i < size; ++i) {{
    if (!{pkg}__msg__{msg_name}__init(&array->data[i])) {{
      for (size_t j = 0; j < i; ++j) {{
        {pkg}__msg__{msg_name}__fini(&array->data[j]);
      }}
      allocator.deallocate(array->data, allocator.state);
      return false;
    }}
  }}

  array->size = size;
  array->capacity = size;
  return true;
}}

void {pkg}__msg__{msg_name}__Sequence__fini(
  {pkg}__msg__{msg_name}__Sequence * array)
{{
  if (!array || !array->data) {{
    return;
  }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {{
    {pkg}__msg__{msg_name}__fini(&array->data[i]);
  }}
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}}
'''


def generate_type_support(msg_name, snake_name):
    """Generate type support file"""
    pkg = "shape_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/{msg_name} type support

#include "shape_msgs/msg/{snake_name}.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t {pkg}__msg__{msg_name}__type_support_handle = {{
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, {pkg}, msg, {msg_name})()
{{
  return &{pkg}__msg__{msg_name}__type_support_handle;
}}
'''


# Message type definitions
MESSAGE_TYPES = [
    # MeshTriangle - Three vertex indices
    {
        'name': 'MeshTriangle',
        'snake': 'mesh_triangle',
        'includes': [],
        'fields': [
            ('uint32_t', 'vertex_indices[3]'),
        ],
        'init': '''  msg->vertex_indices[0] = 0;
  msg->vertex_indices[1] = 0;
  msg->vertex_indices[2] = 0;''',
        'fini': '''''',
    },

    # Mesh - Collection of vertices and triangles
    {
        'name': 'Mesh',
        'snake': 'mesh',
        'includes': [
            'geometry_msgs/msg/point.h',
            'shape_msgs/msg/mesh_triangle.h',
        ],
        'fields': [
            ('geometry_msgs__msg__Point__Sequence', 'vertices'),
            ('shape_msgs__msg__MeshTriangle__Sequence', 'triangles'),
        ],
        'init': '''  geometry_msgs__msg__Point__Sequence__init(&msg->vertices, 0);
  shape_msgs__msg__MeshTriangle__Sequence__init(&msg->triangles, 0);''',
        'fini': '''  geometry_msgs__msg__Point__Sequence__fini(&msg->vertices);
  shape_msgs__msg__MeshTriangle__Sequence__fini(&msg->triangles);''',
    },

    # Plane - Infinite plane (ax + by + cz + d = 0)
    {
        'name': 'Plane',
        'snake': 'plane',
        'includes': [],
        'fields': [
            ('double', 'coef[4]'),  # a, b, c, d coefficients
        ],
        'init': '''  msg->coef[0] = 0.0;
  msg->coef[1] = 0.0;
  msg->coef[2] = 0.0;
  msg->coef[3] = 0.0;''',
        'fini': '''''',
    },

    # SolidPrimitive - Basic solid shapes
    {
        'name': 'SolidPrimitive',
        'snake': 'solid_primitive',
        'includes': [
            'rosidl_runtime_c/primitives_sequence.h',
            'geometry_msgs/msg/polygon.h',
        ],
        'fields': [
            ('uint8_t', 'type'),
            ('rosidl_runtime_c__double__Sequence', 'dimensions'),
            ('geometry_msgs__msg__Polygon', 'polygon'),
        ],
        'constants': [
            # Shape types
            ('BOX', 'uint8_t', '1'),
            ('SPHERE', 'uint8_t', '2'),
            ('CYLINDER', 'uint8_t', '3'),
            ('CONE', 'uint8_t', '4'),
            ('PRISM', 'uint8_t', '5'),
            # Box dimension indices
            ('BOX_X', 'uint8_t', '0'),
            ('BOX_Y', 'uint8_t', '1'),
            ('BOX_Z', 'uint8_t', '2'),
            # Sphere dimension indices
            ('SPHERE_RADIUS', 'uint8_t', '0'),
            # Cylinder dimension indices
            ('CYLINDER_HEIGHT', 'uint8_t', '0'),
            ('CYLINDER_RADIUS', 'uint8_t', '1'),
            # Cone dimension indices
            ('CONE_HEIGHT', 'uint8_t', '0'),
            ('CONE_RADIUS', 'uint8_t', '1'),
            # Prism dimension indices
            ('PRISM_HEIGHT', 'uint8_t', '0'),
        ],
        'init': '''  msg->type = 0;
  rosidl_runtime_c__double__Sequence__init(&msg->dimensions, 0);
  geometry_msgs__msg__Polygon__init(&msg->polygon);''',
        'fini': '''  rosidl_runtime_c__double__Sequence__fini(&msg->dimensions);
  geometry_msgs__msg__Polygon__fini(&msg->polygon);''',
    },
]


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output_dir>")
        sys.exit(1)

    output_dir = sys.argv[1]
    include_dir = os.path.join(output_dir, "include", "shape_msgs", "msg")
    src_dir = os.path.join(output_dir, "src", "msg")

    os.makedirs(include_dir, exist_ok=True)
    os.makedirs(src_dir, exist_ok=True)

    for msg in MESSAGE_TYPES:
        name = msg['name']
        snake = msg['snake']

        # Header
        header = generate_header(name, snake, msg['fields'], msg['includes'],
                                  msg.get('constants'))
        with open(os.path.join(include_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        # Functions
        functions = generate_functions(name, snake, msg['init'], msg['fini'])
        with open(os.path.join(src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        # Type support
        type_support = generate_type_support(name, snake)
        with open(os.path.join(src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: {name}")

    print(f"\nGenerated {len(MESSAGE_TYPES)} message types")


if __name__ == "__main__":
    main()
