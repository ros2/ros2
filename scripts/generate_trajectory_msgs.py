#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generator for trajectory_msgs message types

import os
import sys

def generate_header(msg_name, snake_name, fields, includes, constants=None):
    """Generate message header file"""
    pkg = "trajectory_msgs"
    guard = f"TRAJECTORY_MSGS__MSG__{msg_name.upper()}_H_"

    include_lines = '\n'.join([f'#include "{inc}"' for inc in includes])

    const_lines = ""
    if constants:
        const_lines = "\n// Constants\n"
        for const_name, const_type, const_value in constants:
            const_lines += f"#define TRAJECTORY_MSGS__MSG__{msg_name}_{const_name} {const_value}\n"

    field_lines = '\n'.join([f"  {ftype} {fname};" for ftype, fname in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/{msg_name} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "trajectory_msgs/msg/rosidl_generator_c__visibility_control.h"
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

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool {pkg}__msg__{msg_name}__init({pkg}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void {pkg}__msg__{msg_name}__fini({pkg}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
{pkg}__msg__{msg_name} * {pkg}__msg__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void {pkg}__msg__{msg_name}__destroy({pkg}__msg__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool {pkg}__msg__{msg_name}__Sequence__init(
  {pkg}__msg__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void {pkg}__msg__{msg_name}__Sequence__fini(
  {pkg}__msg__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_functions(msg_name, snake_name, init_code, fini_code):
    """Generate message functions implementation"""
    pkg = "trajectory_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/{msg_name} functions

#include "trajectory_msgs/msg/{snake_name}.h"
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
    pkg = "trajectory_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/{msg_name} type support

#include "trajectory_msgs/msg/{snake_name}.h"
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
    # JointTrajectoryPoint - Single point on a joint trajectory
    {
        'name': 'JointTrajectoryPoint',
        'snake': 'joint_trajectory_point',
        'includes': [
            'rosidl_runtime_c/primitives_sequence.h',
            'builtin_interfaces/msg/duration.h',
        ],
        'fields': [
            ('rosidl_runtime_c__double__Sequence', 'positions'),
            ('rosidl_runtime_c__double__Sequence', 'velocities'),
            ('rosidl_runtime_c__double__Sequence', 'accelerations'),
            ('rosidl_runtime_c__double__Sequence', 'effort'),
            ('builtin_interfaces__msg__Duration', 'time_from_start'),
        ],
        'init': '''  rosidl_runtime_c__double__Sequence__init(&msg->positions, 0);
  rosidl_runtime_c__double__Sequence__init(&msg->velocities, 0);
  rosidl_runtime_c__double__Sequence__init(&msg->accelerations, 0);
  rosidl_runtime_c__double__Sequence__init(&msg->effort, 0);
  builtin_interfaces__msg__Duration__init(&msg->time_from_start);''',
        'fini': '''  rosidl_runtime_c__double__Sequence__fini(&msg->positions);
  rosidl_runtime_c__double__Sequence__fini(&msg->velocities);
  rosidl_runtime_c__double__Sequence__fini(&msg->accelerations);
  rosidl_runtime_c__double__Sequence__fini(&msg->effort);
  builtin_interfaces__msg__Duration__fini(&msg->time_from_start);''',
    },

    # JointTrajectory - Trajectory for a set of joints
    {
        'name': 'JointTrajectory',
        'snake': 'joint_trajectory',
        'includes': [
            'std_msgs/msg/header.h',
            'rosidl_runtime_c/string.h',
            'trajectory_msgs/msg/joint_trajectory_point.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('rosidl_runtime_c__String__Sequence', 'joint_names'),
            ('trajectory_msgs__msg__JointTrajectoryPoint__Sequence', 'points'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__Sequence__init(&msg->joint_names, 0);
  trajectory_msgs__msg__JointTrajectoryPoint__Sequence__init(&msg->points, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__Sequence__fini(&msg->joint_names);
  trajectory_msgs__msg__JointTrajectoryPoint__Sequence__fini(&msg->points);''',
    },

    # MultiDOFJointTrajectoryPoint - Single point on a multi-DOF trajectory
    {
        'name': 'MultiDOFJointTrajectoryPoint',
        'snake': 'multi_dof_joint_trajectory_point',
        'includes': [
            'geometry_msgs/msg/transform.h',
            'geometry_msgs/msg/twist.h',
            'builtin_interfaces/msg/duration.h',
        ],
        'fields': [
            ('geometry_msgs__msg__Transform__Sequence', 'transforms'),
            ('geometry_msgs__msg__Twist__Sequence', 'velocities'),
            ('geometry_msgs__msg__Twist__Sequence', 'accelerations'),
            ('builtin_interfaces__msg__Duration', 'time_from_start'),
        ],
        'init': '''  geometry_msgs__msg__Transform__Sequence__init(&msg->transforms, 0);
  geometry_msgs__msg__Twist__Sequence__init(&msg->velocities, 0);
  geometry_msgs__msg__Twist__Sequence__init(&msg->accelerations, 0);
  builtin_interfaces__msg__Duration__init(&msg->time_from_start);''',
        'fini': '''  geometry_msgs__msg__Transform__Sequence__fini(&msg->transforms);
  geometry_msgs__msg__Twist__Sequence__fini(&msg->velocities);
  geometry_msgs__msg__Twist__Sequence__fini(&msg->accelerations);
  builtin_interfaces__msg__Duration__fini(&msg->time_from_start);''',
    },

    # MultiDOFJointTrajectory - Trajectory for multi-DOF joints
    {
        'name': 'MultiDOFJointTrajectory',
        'snake': 'multi_dof_joint_trajectory',
        'includes': [
            'std_msgs/msg/header.h',
            'rosidl_runtime_c/string.h',
            'trajectory_msgs/msg/multi_dof_joint_trajectory_point.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('rosidl_runtime_c__String__Sequence', 'joint_names'),
            ('trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence', 'points'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__Sequence__init(&msg->joint_names, 0);
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__init(&msg->points, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__Sequence__fini(&msg->joint_names);
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__fini(&msg->points);''',
    },
]


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output_dir>")
        sys.exit(1)

    output_dir = sys.argv[1]
    include_dir = os.path.join(output_dir, "include", "trajectory_msgs", "msg")
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
