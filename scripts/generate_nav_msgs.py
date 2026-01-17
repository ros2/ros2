#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generator for nav_msgs message and service types

import os
import sys

def generate_header(msg_name, snake_name, fields, includes, constants=None, is_service=False):
    """Generate message header file"""
    pkg = "nav_msgs"
    subdir = "srv" if is_service else "msg"
    guard = f"NAV_MSGS__{subdir.upper()}__{msg_name.upper()}_H_"

    include_lines = '\n'.join([f'#include "{inc}"' for inc in includes])

    # Build constants
    const_lines = ""
    if constants:
        const_lines = "\n// Constants\n"
        for const_name, const_type, const_value in constants:
            const_lines += f"#define NAV_MSGS__{subdir.upper()}__{msg_name}_{const_name} {const_value}\n"

    # Build struct fields
    field_lines = '\n'.join([f"  {ftype} {fname};" for ftype, fname in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/{subdir}/{msg_name} {"service" if is_service else "message"} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
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

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool {pkg}__{subdir}__{msg_name}__init({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void {pkg}__{subdir}__{msg_name}__fini({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
{pkg}__{subdir}__{msg_name} * {pkg}__{subdir}__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void {pkg}__{subdir}__{msg_name}__destroy({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool {pkg}__{subdir}__{msg_name}__Sequence__init(
  {pkg}__{subdir}__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void {pkg}__{subdir}__{msg_name}__Sequence__fini(
  {pkg}__{subdir}__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_functions(msg_name, snake_name, fields, init_code, fini_code, is_service=False):
    """Generate message functions implementation"""
    pkg = "nav_msgs"
    subdir = "srv" if is_service else "msg"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/{subdir}/{msg_name} functions

#include "nav_msgs/{subdir}/{snake_name}.h"
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


def generate_type_support(msg_name, snake_name, is_service=False):
    """Generate type support file"""
    pkg = "nav_msgs"
    subdir = "srv" if is_service else "msg"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/{subdir}/{msg_name} type support

#include "nav_msgs/{subdir}/{snake_name}.h"
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
    # MapMetaData - Metadata for occupancy grid
    {
        'name': 'MapMetaData',
        'includes': [
            'builtin_interfaces/msg/time.h',
            'geometry_msgs/msg/pose.h',
        ],
        'fields': [
            ('builtin_interfaces__msg__Time', 'map_load_time'),
            ('float', 'resolution'),
            ('uint32_t', 'width'),
            ('uint32_t', 'height'),
            ('geometry_msgs__msg__Pose', 'origin'),
        ],
        'init': '''  builtin_interfaces__msg__Time__init(&msg->map_load_time);
  msg->resolution = 0.0f;
  msg->width = 0;
  msg->height = 0;
  geometry_msgs__msg__Pose__init(&msg->origin);''',
        'fini': '''  builtin_interfaces__msg__Time__fini(&msg->map_load_time);
  geometry_msgs__msg__Pose__fini(&msg->origin);''',
    },

    # OccupancyGrid - 2D occupancy grid map
    {
        'name': 'OccupancyGrid',
        'includes': [
            'std_msgs/msg/header.h',
            'nav_msgs/msg/map_meta_data.h',
            'rosidl_runtime_c/primitives_sequence.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('nav_msgs__msg__MapMetaData', 'info'),
            ('rosidl_runtime_c__int8__Sequence', 'data'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  nav_msgs__msg__MapMetaData__init(&msg->info);
  rosidl_runtime_c__int8__Sequence__init(&msg->data, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  nav_msgs__msg__MapMetaData__fini(&msg->info);
  rosidl_runtime_c__int8__Sequence__fini(&msg->data);''',
    },

    # GridCells - Collection of cells in a grid
    {
        'name': 'GridCells',
        'includes': [
            'std_msgs/msg/header.h',
            'geometry_msgs/msg/point.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('float', 'cell_width'),
            ('float', 'cell_height'),
            ('geometry_msgs__msg__Point__Sequence', 'cells'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  msg->cell_width = 0.0f;
  msg->cell_height = 0.0f;
  geometry_msgs__msg__Point__Sequence__init(&msg->cells, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  geometry_msgs__msg__Point__Sequence__fini(&msg->cells);''',
    },

    # Odometry - Robot odometry
    {
        'name': 'Odometry',
        'includes': [
            'std_msgs/msg/header.h',
            'rosidl_runtime_c/string.h',
            'geometry_msgs/msg/pose_with_covariance.h',
            'geometry_msgs/msg/twist_with_covariance.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('rosidl_runtime_c__String', 'child_frame_id'),
            ('geometry_msgs__msg__PoseWithCovariance', 'pose'),
            ('geometry_msgs__msg__TwistWithCovariance', 'twist'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__init(&msg->child_frame_id);
  geometry_msgs__msg__PoseWithCovariance__init(&msg->pose);
  geometry_msgs__msg__TwistWithCovariance__init(&msg->twist);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->child_frame_id);
  geometry_msgs__msg__PoseWithCovariance__fini(&msg->pose);
  geometry_msgs__msg__TwistWithCovariance__fini(&msg->twist);''',
    },

    # Path - Sequence of poses
    {
        'name': 'Path',
        'includes': [
            'std_msgs/msg/header.h',
            'geometry_msgs/msg/pose_stamped.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('geometry_msgs__msg__PoseStamped__Sequence', 'poses'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  geometry_msgs__msg__PoseStamped__Sequence__init(&msg->poses, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  geometry_msgs__msg__PoseStamped__Sequence__fini(&msg->poses);''',
    },
]

# Service type definitions
SERVICE_TYPES = [
    # GetMap - Request current map
    {
        'name': 'GetMap_Request',
        'includes': [],
        'fields': [
            ('uint8_t', 'structure_needs_at_least_one_member'),
        ],
        'init': '''  msg->structure_needs_at_least_one_member = 0;''',
        'fini': '''''',
    },
    {
        'name': 'GetMap_Response',
        'includes': [
            'nav_msgs/msg/occupancy_grid.h',
        ],
        'fields': [
            ('nav_msgs__msg__OccupancyGrid', 'map'),
        ],
        'init': '''  nav_msgs__msg__OccupancyGrid__init(&msg->map);''',
        'fini': '''  nav_msgs__msg__OccupancyGrid__fini(&msg->map);''',
    },

    # GetPlan - Request path plan
    {
        'name': 'GetPlan_Request',
        'includes': [
            'geometry_msgs/msg/pose_stamped.h',
        ],
        'fields': [
            ('geometry_msgs__msg__PoseStamped', 'start'),
            ('geometry_msgs__msg__PoseStamped', 'goal'),
            ('float', 'tolerance'),
        ],
        'init': '''  geometry_msgs__msg__PoseStamped__init(&msg->start);
  geometry_msgs__msg__PoseStamped__init(&msg->goal);
  msg->tolerance = 0.0f;''',
        'fini': '''  geometry_msgs__msg__PoseStamped__fini(&msg->start);
  geometry_msgs__msg__PoseStamped__fini(&msg->goal);''',
    },
    {
        'name': 'GetPlan_Response',
        'includes': [
            'nav_msgs/msg/path.h',
        ],
        'fields': [
            ('nav_msgs__msg__Path', 'plan'),
        ],
        'init': '''  nav_msgs__msg__Path__init(&msg->plan);''',
        'fini': '''  nav_msgs__msg__Path__fini(&msg->plan);''',
    },

    # SetMap - Set a new map
    {
        'name': 'SetMap_Request',
        'includes': [
            'nav_msgs/msg/occupancy_grid.h',
            'geometry_msgs/msg/pose_with_covariance_stamped.h',
        ],
        'fields': [
            ('nav_msgs__msg__OccupancyGrid', 'map'),
            ('geometry_msgs__msg__PoseWithCovarianceStamped', 'initial_pose'),
        ],
        'init': '''  nav_msgs__msg__OccupancyGrid__init(&msg->map);
  geometry_msgs__msg__PoseWithCovarianceStamped__init(&msg->initial_pose);''',
        'fini': '''  nav_msgs__msg__OccupancyGrid__fini(&msg->map);
  geometry_msgs__msg__PoseWithCovarianceStamped__fini(&msg->initial_pose);''',
    },
    {
        'name': 'SetMap_Response',
        'includes': [],
        'fields': [
            ('bool', 'success'),
        ],
        'init': '''  msg->success = false;''',
        'fini': '''''',
    },

    # LoadMap - Load map from file
    {
        'name': 'LoadMap_Request',
        'includes': [
            'rosidl_runtime_c/string.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'map_url'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->map_url);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->map_url);''',
    },
    {
        'name': 'LoadMap_Response',
        'includes': [
            'nav_msgs/msg/occupancy_grid.h',
        ],
        'fields': [
            ('nav_msgs__msg__OccupancyGrid', 'map'),
            ('uint8_t', 'result'),
        ],
        'constants': [
            ('RESULT_SUCCESS', 'uint8_t', '0'),
            ('RESULT_MAP_DOES_NOT_EXIST', 'uint8_t', '1'),
            ('RESULT_INVALID_MAP_DATA', 'uint8_t', '2'),
            ('RESULT_INVALID_MAP_METADATA', 'uint8_t', '3'),
            ('RESULT_UNDEFINED_FAILURE', 'uint8_t', '255'),
        ],
        'init': '''  nav_msgs__msg__OccupancyGrid__init(&msg->map);
  msg->result = 0;''',
        'fini': '''  nav_msgs__msg__OccupancyGrid__fini(&msg->map);''',
    },
]


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output_dir>")
        sys.exit(1)

    output_dir = sys.argv[1]
    msg_include_dir = os.path.join(output_dir, "include", "nav_msgs", "msg")
    msg_src_dir = os.path.join(output_dir, "src", "msg")
    srv_include_dir = os.path.join(output_dir, "include", "nav_msgs", "srv")
    srv_src_dir = os.path.join(output_dir, "src", "srv")

    os.makedirs(msg_include_dir, exist_ok=True)
    os.makedirs(msg_src_dir, exist_ok=True)
    os.makedirs(srv_include_dir, exist_ok=True)
    os.makedirs(srv_src_dir, exist_ok=True)

    # Generate message types
    for msg in MESSAGE_TYPES:
        name = msg['name']
        snake = to_snake_case(name)

        # Header
        header = generate_header(
            name, snake, msg['fields'], msg['includes'],
            msg.get('constants'), is_service=False
        )
        with open(os.path.join(msg_include_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        # Functions
        functions = generate_functions(
            name, snake, msg['fields'], msg['init'], msg['fini'],
            is_service=False
        )
        with open(os.path.join(msg_src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        # Type support
        type_support = generate_type_support(name, snake, is_service=False)
        with open(os.path.join(msg_src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: {name}")

    # Generate service types
    for srv in SERVICE_TYPES:
        name = srv['name']
        snake = to_snake_case(name)

        # Header
        header = generate_header(
            name, snake, srv['fields'], srv['includes'],
            srv.get('constants'), is_service=True
        )
        with open(os.path.join(srv_include_dir, f"{snake}.h"), 'w') as f:
            f.write(header)

        # Functions
        functions = generate_functions(
            name, snake, srv['fields'], srv['init'], srv['fini'],
            is_service=True
        )
        with open(os.path.join(srv_src_dir, f"{snake}__functions.c"), 'w') as f:
            f.write(functions)

        # Type support
        type_support = generate_type_support(name, snake, is_service=True)
        with open(os.path.join(srv_src_dir, f"{snake}__type_support.c"), 'w') as f:
            f.write(type_support)

        print(f"Generated: {name}")

    print(f"\nGenerated {len(MESSAGE_TYPES)} message types and {len(SERVICE_TYPES)} service types")


if __name__ == "__main__":
    main()
