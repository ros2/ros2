#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generator for visualization_msgs message and service types

import os
import sys

def generate_header(msg_name, snake_name, fields, includes, constants=None, subdir="msg"):
    """Generate message header file"""
    pkg = "visualization_msgs"
    guard = f"VISUALIZATION_MSGS__{subdir.upper()}__{msg_name.upper()}_H_"

    include_lines = '\n'.join([f'#include "{inc}"' for inc in includes])

    const_lines = ""
    if constants:
        const_lines = "\n// Constants\n"
        for const_name, const_type, const_value in constants:
            const_lines += f"#define VISUALIZATION_MSGS__{subdir.upper()}__{msg_name}_{const_name} {const_value}\n"

    field_lines = '\n'.join([f"  {ftype} {fname};" for ftype, fname in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/{subdir}/{msg_name} type

#ifndef {guard}
#define {guard}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
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

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool {pkg}__{subdir}__{msg_name}__init({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void {pkg}__{subdir}__{msg_name}__fini({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
{pkg}__{subdir}__{msg_name} * {pkg}__{subdir}__{msg_name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void {pkg}__{subdir}__{msg_name}__destroy({pkg}__{subdir}__{msg_name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool {pkg}__{subdir}__{msg_name}__Sequence__init(
  {pkg}__{subdir}__{msg_name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void {pkg}__{subdir}__{msg_name}__Sequence__fini(
  {pkg}__{subdir}__{msg_name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // {guard}
'''


def generate_functions(msg_name, snake_name, init_code, fini_code, subdir="msg"):
    """Generate message functions implementation"""
    pkg = "visualization_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/{subdir}/{msg_name} functions

#include "visualization_msgs/{subdir}/{snake_name}.h"
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
    pkg = "visualization_msgs"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/{subdir}/{msg_name} type support

#include "visualization_msgs/{subdir}/{snake_name}.h"
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
    # UVCoordinate - Texture coordinate
    {
        'name': 'UVCoordinate',
        'snake': 'uv_coordinate',
        'includes': [],
        'fields': [
            ('float', 'u'),
            ('float', 'v'),
        ],
        'init': '''  msg->u = 0.0f;
  msg->v = 0.0f;''',
        'fini': '''''',
    },

    # MeshFile - Reference to mesh file
    {
        'name': 'MeshFile',
        'snake': 'mesh_file',
        'includes': [
            'rosidl_runtime_c/string.h',
            'rosidl_runtime_c/primitives_sequence.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'filename'),
            ('rosidl_runtime_c__uint8__Sequence', 'data'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->filename);
  rosidl_runtime_c__uint8__Sequence__init(&msg->data, 0);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->filename);
  rosidl_runtime_c__uint8__Sequence__fini(&msg->data);''',
    },

    # MenuEntry - Context menu entry
    {
        'name': 'MenuEntry',
        'snake': 'menu_entry',
        'includes': [
            'rosidl_runtime_c/string.h',
        ],
        'fields': [
            ('uint32_t', 'id'),
            ('uint32_t', 'parent_id'),
            ('rosidl_runtime_c__String', 'title'),
            ('rosidl_runtime_c__String', 'command'),
            ('uint8_t', 'command_type'),
        ],
        'constants': [
            ('FEEDBACK', 'uint8_t', '0'),
            ('ROSRUN', 'uint8_t', '1'),
            ('ROSLAUNCH', 'uint8_t', '2'),
        ],
        'init': '''  msg->id = 0;
  msg->parent_id = 0;
  rosidl_runtime_c__String__init(&msg->title);
  rosidl_runtime_c__String__init(&msg->command);
  msg->command_type = 0;''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->title);
  rosidl_runtime_c__String__fini(&msg->command);''',
    },

    # Marker - Main visualization marker
    {
        'name': 'Marker',
        'snake': 'marker',
        'includes': [
            'std_msgs/msg/header.h',
            'std_msgs/msg/color_rgba.h',
            'rosidl_runtime_c/string.h',
            'rosidl_runtime_c/primitives_sequence.h',
            'geometry_msgs/msg/pose.h',
            'geometry_msgs/msg/vector3.h',
            'geometry_msgs/msg/point.h',
            'builtin_interfaces/msg/duration.h',
            'sensor_msgs/msg/compressed_image.h',
            'visualization_msgs/msg/uv_coordinate.h',
            'visualization_msgs/msg/mesh_file.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('rosidl_runtime_c__String', 'ns'),
            ('int32_t', 'id'),
            ('int32_t', 'type'),
            ('int32_t', 'action'),
            ('geometry_msgs__msg__Pose', 'pose'),
            ('geometry_msgs__msg__Vector3', 'scale'),
            ('std_msgs__msg__ColorRGBA', 'color'),
            ('builtin_interfaces__msg__Duration', 'lifetime'),
            ('bool', 'frame_locked'),
            ('geometry_msgs__msg__Point__Sequence', 'points'),
            ('std_msgs__msg__ColorRGBA__Sequence', 'colors'),
            ('rosidl_runtime_c__String', 'texture_resource'),
            ('sensor_msgs__msg__CompressedImage', 'texture'),
            ('visualization_msgs__msg__UVCoordinate__Sequence', 'uv_coordinates'),
            ('rosidl_runtime_c__String', 'text'),
            ('rosidl_runtime_c__String', 'mesh_resource'),
            ('visualization_msgs__msg__MeshFile', 'mesh_file'),
            ('bool', 'mesh_use_embedded_materials'),
        ],
        'constants': [
            ('ARROW', 'int32_t', '0'),
            ('CUBE', 'int32_t', '1'),
            ('SPHERE', 'int32_t', '2'),
            ('CYLINDER', 'int32_t', '3'),
            ('LINE_STRIP', 'int32_t', '4'),
            ('LINE_LIST', 'int32_t', '5'),
            ('CUBE_LIST', 'int32_t', '6'),
            ('SPHERE_LIST', 'int32_t', '7'),
            ('POINTS', 'int32_t', '8'),
            ('TEXT_VIEW_FACING', 'int32_t', '9'),
            ('MESH_RESOURCE', 'int32_t', '10'),
            ('TRIANGLE_LIST', 'int32_t', '11'),
            ('ADD', 'int32_t', '0'),
            ('MODIFY', 'int32_t', '0'),
            ('DELETE', 'int32_t', '2'),
            ('DELETEALL', 'int32_t', '3'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__init(&msg->ns);
  msg->id = 0;
  msg->type = 0;
  msg->action = 0;
  geometry_msgs__msg__Pose__init(&msg->pose);
  geometry_msgs__msg__Vector3__init(&msg->scale);
  std_msgs__msg__ColorRGBA__init(&msg->color);
  builtin_interfaces__msg__Duration__init(&msg->lifetime);
  msg->frame_locked = false;
  geometry_msgs__msg__Point__Sequence__init(&msg->points, 0);
  std_msgs__msg__ColorRGBA__Sequence__init(&msg->colors, 0);
  rosidl_runtime_c__String__init(&msg->texture_resource);
  rosidl_runtime_c__String__init(&msg->text);
  rosidl_runtime_c__String__init(&msg->mesh_resource);
  visualization_msgs__msg__MeshFile__init(&msg->mesh_file);
  visualization_msgs__msg__UVCoordinate__Sequence__init(&msg->uv_coordinates, 0);
  msg->mesh_use_embedded_materials = false;''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->ns);
  geometry_msgs__msg__Pose__fini(&msg->pose);
  geometry_msgs__msg__Vector3__fini(&msg->scale);
  std_msgs__msg__ColorRGBA__fini(&msg->color);
  builtin_interfaces__msg__Duration__fini(&msg->lifetime);
  geometry_msgs__msg__Point__Sequence__fini(&msg->points);
  std_msgs__msg__ColorRGBA__Sequence__fini(&msg->colors);
  rosidl_runtime_c__String__fini(&msg->texture_resource);
  rosidl_runtime_c__String__fini(&msg->text);
  rosidl_runtime_c__String__fini(&msg->mesh_resource);
  visualization_msgs__msg__MeshFile__fini(&msg->mesh_file);
  visualization_msgs__msg__UVCoordinate__Sequence__fini(&msg->uv_coordinates);''',
    },

    # MarkerArray - Collection of markers
    {
        'name': 'MarkerArray',
        'snake': 'marker_array',
        'includes': [
            'visualization_msgs/msg/marker.h',
        ],
        'fields': [
            ('visualization_msgs__msg__Marker__Sequence', 'markers'),
        ],
        'init': '''  visualization_msgs__msg__Marker__Sequence__init(&msg->markers, 0);''',
        'fini': '''  visualization_msgs__msg__Marker__Sequence__fini(&msg->markers);''',
    },

    # ImageMarker - Marker for image overlay
    {
        'name': 'ImageMarker',
        'snake': 'image_marker',
        'includes': [
            'std_msgs/msg/header.h',
            'std_msgs/msg/color_rgba.h',
            'rosidl_runtime_c/string.h',
            'geometry_msgs/msg/point.h',
            'builtin_interfaces/msg/duration.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('rosidl_runtime_c__String', 'ns'),
            ('int32_t', 'id'),
            ('int32_t', 'type'),
            ('int32_t', 'action'),
            ('geometry_msgs__msg__Point', 'position'),
            ('float', 'scale'),
            ('std_msgs__msg__ColorRGBA', 'outline_color'),
            ('uint8_t', 'filled'),
            ('std_msgs__msg__ColorRGBA', 'fill_color'),
            ('builtin_interfaces__msg__Duration', 'lifetime'),
            ('geometry_msgs__msg__Point__Sequence', 'points'),
            ('std_msgs__msg__ColorRGBA__Sequence', 'outline_colors'),
        ],
        'constants': [
            ('CIRCLE', 'int32_t', '0'),
            ('LINE_STRIP', 'int32_t', '1'),
            ('LINE_LIST', 'int32_t', '2'),
            ('POLYGON', 'int32_t', '3'),
            ('POINTS', 'int32_t', '4'),
            ('ADD', 'int32_t', '0'),
            ('REMOVE', 'int32_t', '1'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__init(&msg->ns);
  msg->id = 0;
  msg->type = 0;
  msg->action = 0;
  geometry_msgs__msg__Point__init(&msg->position);
  msg->scale = 1.0f;
  std_msgs__msg__ColorRGBA__init(&msg->outline_color);
  msg->filled = 0;
  std_msgs__msg__ColorRGBA__init(&msg->fill_color);
  builtin_interfaces__msg__Duration__init(&msg->lifetime);
  geometry_msgs__msg__Point__Sequence__init(&msg->points, 0);
  std_msgs__msg__ColorRGBA__Sequence__init(&msg->outline_colors, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->ns);
  geometry_msgs__msg__Point__fini(&msg->position);
  std_msgs__msg__ColorRGBA__fini(&msg->outline_color);
  std_msgs__msg__ColorRGBA__fini(&msg->fill_color);
  builtin_interfaces__msg__Duration__fini(&msg->lifetime);
  geometry_msgs__msg__Point__Sequence__fini(&msg->points);
  std_msgs__msg__ColorRGBA__Sequence__fini(&msg->outline_colors);''',
    },

    # InteractiveMarkerControl
    {
        'name': 'InteractiveMarkerControl',
        'snake': 'interactive_marker_control',
        'includes': [
            'rosidl_runtime_c/string.h',
            'geometry_msgs/msg/quaternion.h',
            'visualization_msgs/msg/marker.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'name'),
            ('geometry_msgs__msg__Quaternion', 'orientation'),
            ('uint8_t', 'orientation_mode'),
            ('uint8_t', 'interaction_mode'),
            ('bool', 'always_visible'),
            ('visualization_msgs__msg__Marker__Sequence', 'markers'),
            ('bool', 'independent_marker_orientation'),
            ('rosidl_runtime_c__String', 'description'),
        ],
        'constants': [
            ('INHERIT', 'uint8_t', '0'),
            ('FIXED', 'uint8_t', '1'),
            ('VIEW_FACING', 'uint8_t', '2'),
            ('NONE', 'uint8_t', '0'),
            ('MENU', 'uint8_t', '1'),
            ('BUTTON', 'uint8_t', '2'),
            ('MOVE_AXIS', 'uint8_t', '3'),
            ('MOVE_PLANE', 'uint8_t', '4'),
            ('ROTATE_AXIS', 'uint8_t', '5'),
            ('MOVE_ROTATE', 'uint8_t', '6'),
            ('MOVE_3D', 'uint8_t', '7'),
            ('ROTATE_3D', 'uint8_t', '8'),
            ('MOVE_ROTATE_3D', 'uint8_t', '9'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->name);
  geometry_msgs__msg__Quaternion__init(&msg->orientation);
  msg->orientation_mode = 0;
  msg->interaction_mode = 0;
  msg->always_visible = false;
  visualization_msgs__msg__Marker__Sequence__init(&msg->markers, 0);
  msg->independent_marker_orientation = false;
  rosidl_runtime_c__String__init(&msg->description);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->name);
  geometry_msgs__msg__Quaternion__fini(&msg->orientation);
  visualization_msgs__msg__Marker__Sequence__fini(&msg->markers);
  rosidl_runtime_c__String__fini(&msg->description);''',
    },

    # InteractiveMarker
    {
        'name': 'InteractiveMarker',
        'snake': 'interactive_marker',
        'includes': [
            'std_msgs/msg/header.h',
            'rosidl_runtime_c/string.h',
            'geometry_msgs/msg/pose.h',
            'visualization_msgs/msg/menu_entry.h',
            'visualization_msgs/msg/interactive_marker_control.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('geometry_msgs__msg__Pose', 'pose'),
            ('rosidl_runtime_c__String', 'name'),
            ('rosidl_runtime_c__String', 'description'),
            ('float', 'scale'),
            ('visualization_msgs__msg__MenuEntry__Sequence', 'menu_entries'),
            ('visualization_msgs__msg__InteractiveMarkerControl__Sequence', 'controls'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  geometry_msgs__msg__Pose__init(&msg->pose);
  rosidl_runtime_c__String__init(&msg->name);
  rosidl_runtime_c__String__init(&msg->description);
  msg->scale = 1.0f;
  visualization_msgs__msg__MenuEntry__Sequence__init(&msg->menu_entries, 0);
  visualization_msgs__msg__InteractiveMarkerControl__Sequence__init(&msg->controls, 0);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  geometry_msgs__msg__Pose__fini(&msg->pose);
  rosidl_runtime_c__String__fini(&msg->name);
  rosidl_runtime_c__String__fini(&msg->description);
  visualization_msgs__msg__MenuEntry__Sequence__fini(&msg->menu_entries);
  visualization_msgs__msg__InteractiveMarkerControl__Sequence__fini(&msg->controls);''',
    },

    # InteractiveMarkerFeedback
    {
        'name': 'InteractiveMarkerFeedback',
        'snake': 'interactive_marker_feedback',
        'includes': [
            'std_msgs/msg/header.h',
            'rosidl_runtime_c/string.h',
            'geometry_msgs/msg/pose.h',
            'geometry_msgs/msg/point.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('rosidl_runtime_c__String', 'client_id'),
            ('rosidl_runtime_c__String', 'marker_name'),
            ('rosidl_runtime_c__String', 'control_name'),
            ('uint8_t', 'event_type'),
            ('geometry_msgs__msg__Pose', 'pose'),
            ('uint32_t', 'menu_entry_id'),
            ('geometry_msgs__msg__Point', 'mouse_point'),
            ('bool', 'mouse_point_valid'),
        ],
        'constants': [
            ('KEEP_ALIVE', 'uint8_t', '0'),
            ('POSE_UPDATE', 'uint8_t', '1'),
            ('MENU_SELECT', 'uint8_t', '2'),
            ('BUTTON_CLICK', 'uint8_t', '3'),
            ('MOUSE_DOWN', 'uint8_t', '4'),
            ('MOUSE_UP', 'uint8_t', '5'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__init(&msg->client_id);
  rosidl_runtime_c__String__init(&msg->marker_name);
  rosidl_runtime_c__String__init(&msg->control_name);
  msg->event_type = 0;
  geometry_msgs__msg__Pose__init(&msg->pose);
  msg->menu_entry_id = 0;
  geometry_msgs__msg__Point__init(&msg->mouse_point);
  msg->mouse_point_valid = false;''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->client_id);
  rosidl_runtime_c__String__fini(&msg->marker_name);
  rosidl_runtime_c__String__fini(&msg->control_name);
  geometry_msgs__msg__Pose__fini(&msg->pose);
  geometry_msgs__msg__Point__fini(&msg->mouse_point);''',
    },

    # InteractiveMarkerInit
    {
        'name': 'InteractiveMarkerInit',
        'snake': 'interactive_marker_init',
        'includes': [
            'rosidl_runtime_c/string.h',
            'visualization_msgs/msg/interactive_marker.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'server_id'),
            ('uint64_t', 'seq_num'),
            ('visualization_msgs__msg__InteractiveMarker__Sequence', 'markers'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->server_id);
  msg->seq_num = 0;
  visualization_msgs__msg__InteractiveMarker__Sequence__init(&msg->markers, 0);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->server_id);
  visualization_msgs__msg__InteractiveMarker__Sequence__fini(&msg->markers);''',
    },

    # InteractiveMarkerPose
    {
        'name': 'InteractiveMarkerPose',
        'snake': 'interactive_marker_pose',
        'includes': [
            'std_msgs/msg/header.h',
            'rosidl_runtime_c/string.h',
            'geometry_msgs/msg/pose.h',
        ],
        'fields': [
            ('std_msgs__msg__Header', 'header'),
            ('geometry_msgs__msg__Pose', 'pose'),
            ('rosidl_runtime_c__String', 'name'),
        ],
        'init': '''  std_msgs__msg__Header__init(&msg->header);
  geometry_msgs__msg__Pose__init(&msg->pose);
  rosidl_runtime_c__String__init(&msg->name);''',
        'fini': '''  std_msgs__msg__Header__fini(&msg->header);
  geometry_msgs__msg__Pose__fini(&msg->pose);
  rosidl_runtime_c__String__fini(&msg->name);''',
    },

    # InteractiveMarkerUpdate
    {
        'name': 'InteractiveMarkerUpdate',
        'snake': 'interactive_marker_update',
        'includes': [
            'rosidl_runtime_c/string.h',
            'visualization_msgs/msg/interactive_marker.h',
            'visualization_msgs/msg/interactive_marker_pose.h',
        ],
        'fields': [
            ('rosidl_runtime_c__String', 'server_id'),
            ('uint64_t', 'seq_num'),
            ('uint8_t', 'type'),
            ('visualization_msgs__msg__InteractiveMarker__Sequence', 'markers'),
            ('visualization_msgs__msg__InteractiveMarkerPose__Sequence', 'poses'),
            ('rosidl_runtime_c__String__Sequence', 'erases'),
        ],
        'constants': [
            ('KEEP_ALIVE', 'uint8_t', '0'),
            ('UPDATE', 'uint8_t', '1'),
        ],
        'init': '''  rosidl_runtime_c__String__init(&msg->server_id);
  msg->seq_num = 0;
  msg->type = 0;
  visualization_msgs__msg__InteractiveMarker__Sequence__init(&msg->markers, 0);
  visualization_msgs__msg__InteractiveMarkerPose__Sequence__init(&msg->poses, 0);
  rosidl_runtime_c__String__Sequence__init(&msg->erases, 0);''',
        'fini': '''  rosidl_runtime_c__String__fini(&msg->server_id);
  visualization_msgs__msg__InteractiveMarker__Sequence__fini(&msg->markers);
  visualization_msgs__msg__InteractiveMarkerPose__Sequence__fini(&msg->poses);
  rosidl_runtime_c__String__Sequence__fini(&msg->erases);''',
    },
]

# Service type definitions
SERVICE_TYPES = [
    {
        'name': 'GetInteractiveMarkers_Request',
        'snake': 'get_interactive_markers__request',
        'includes': [],
        'fields': [
            ('uint8_t', 'structure_needs_at_least_one_member'),
        ],
        'init': '''  msg->structure_needs_at_least_one_member = 0;''',
        'fini': '''''',
    },
    {
        'name': 'GetInteractiveMarkers_Response',
        'snake': 'get_interactive_markers__response',
        'includes': [
            'visualization_msgs/msg/interactive_marker.h',
        ],
        'fields': [
            ('uint64_t', 'sequence_number'),
            ('visualization_msgs__msg__InteractiveMarker__Sequence', 'markers'),
        ],
        'init': '''  msg->sequence_number = 0;
  visualization_msgs__msg__InteractiveMarker__Sequence__init(&msg->markers, 0);''',
        'fini': '''  visualization_msgs__msg__InteractiveMarker__Sequence__fini(&msg->markers);''',
    },
]


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output_dir>")
        sys.exit(1)

    output_dir = sys.argv[1]
    msg_include_dir = os.path.join(output_dir, "include", "visualization_msgs", "msg")
    msg_src_dir = os.path.join(output_dir, "src", "msg")
    srv_include_dir = os.path.join(output_dir, "include", "visualization_msgs", "srv")
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
