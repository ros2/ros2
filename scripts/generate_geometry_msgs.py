#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generate geometry_msgs message type implementations

import os
import sys

OUTPUT_DIR = sys.argv[1] if len(sys.argv) > 1 else "ohos_ros2/interfaces/geometry_msgs"

# Message type definitions
# Format: (snake_name, PascalName, fields, deps, has_covariance_size)
# fields: list of (field_name, c_type, is_array, array_size, nested_type)

BASIC_TYPES = {
    "point": {
        "name": "Point",
        "fields": [("x", "double"), ("y", "double"), ("z", "double")],
        "deps": [],
    },
    "point32": {
        "name": "Point32",
        "fields": [("x", "float"), ("y", "float"), ("z", "float")],
        "deps": [],
    },
    "vector3": {
        "name": "Vector3",
        "fields": [("x", "double"), ("y", "double"), ("z", "double")],
        "deps": [],
    },
    "quaternion": {
        "name": "Quaternion",
        "fields": [("x", "double"), ("y", "double"), ("z", "double"), ("w", "double")],
        "deps": [],
        "default_w": "1.0",
    },
}

COMPOUND_TYPES = {
    "pose": {
        "name": "Pose",
        "fields": [("position", "geometry_msgs__msg__Point"), ("orientation", "geometry_msgs__msg__Quaternion")],
        "deps": ["point", "quaternion"],
    },
    "pose2d": {
        "name": "Pose2D",
        "fields": [("x", "double"), ("y", "double"), ("theta", "double")],
        "deps": [],
    },
    "transform": {
        "name": "Transform",
        "fields": [("translation", "geometry_msgs__msg__Vector3"), ("rotation", "geometry_msgs__msg__Quaternion")],
        "deps": ["vector3", "quaternion"],
    },
    "twist": {
        "name": "Twist",
        "fields": [("linear", "geometry_msgs__msg__Vector3"), ("angular", "geometry_msgs__msg__Vector3")],
        "deps": ["vector3"],
    },
    "wrench": {
        "name": "Wrench",
        "fields": [("force", "geometry_msgs__msg__Vector3"), ("torque", "geometry_msgs__msg__Vector3")],
        "deps": ["vector3"],
    },
    "accel": {
        "name": "Accel",
        "fields": [("linear", "geometry_msgs__msg__Vector3"), ("angular", "geometry_msgs__msg__Vector3")],
        "deps": ["vector3"],
    },
    "inertia": {
        "name": "Inertia",
        "fields": [
            ("m", "double"),
            ("com", "geometry_msgs__msg__Vector3"),
            ("ixx", "double"), ("ixy", "double"), ("ixz", "double"),
            ("iyy", "double"), ("iyz", "double"), ("izz", "double"),
        ],
        "deps": ["vector3"],
    },
}

COVARIANCE_TYPES = {
    "pose_with_covariance": {
        "name": "PoseWithCovariance",
        "base_field": ("pose", "geometry_msgs__msg__Pose"),
        "covariance_size": 36,
        "deps": ["pose"],
    },
    "twist_with_covariance": {
        "name": "TwistWithCovariance",
        "base_field": ("twist", "geometry_msgs__msg__Twist"),
        "covariance_size": 36,
        "deps": ["twist"],
    },
    "accel_with_covariance": {
        "name": "AccelWithCovariance",
        "base_field": ("accel", "geometry_msgs__msg__Accel"),
        "covariance_size": 36,
        "deps": ["accel"],
    },
}

STAMPED_TYPES = {
    "point_stamped": {"name": "PointStamped", "base": "point", "base_type": "Point"},
    "vector3_stamped": {"name": "Vector3Stamped", "base": "vector3", "base_type": "Vector3"},
    "quaternion_stamped": {"name": "QuaternionStamped", "base": "quaternion", "base_type": "Quaternion"},
    "pose_stamped": {"name": "PoseStamped", "base": "pose", "base_type": "Pose"},
    "pose_with_covariance_stamped": {"name": "PoseWithCovarianceStamped", "base": "pose_with_covariance", "base_type": "PoseWithCovariance"},
    "transform_stamped": {"name": "TransformStamped", "base": "transform", "base_type": "Transform", "extra_field": ("child_frame_id", "rosidl_runtime_c__String")},
    "twist_stamped": {"name": "TwistStamped", "base": "twist", "base_type": "Twist"},
    "twist_with_covariance_stamped": {"name": "TwistWithCovarianceStamped", "base": "twist_with_covariance", "base_type": "TwistWithCovariance"},
    "wrench_stamped": {"name": "WrenchStamped", "base": "wrench", "base_type": "Wrench"},
    "accel_stamped": {"name": "AccelStamped", "base": "accel", "base_type": "Accel"},
    "accel_with_covariance_stamped": {"name": "AccelWithCovarianceStamped", "base": "accel_with_covariance", "base_type": "AccelWithCovariance"},
    "inertia_stamped": {"name": "InertiaStamped", "base": "inertia", "base_type": "Inertia"},
    "velocity_stamped": {"name": "VelocityStamped", "base": "twist", "base_type": "Twist", "field_name": "velocity"},
}

ARRAY_TYPES = {
    "pose_array": {
        "name": "PoseArray",
        "element_type": "Pose",
        "element_snake": "pose",
    },
    "polygon": {
        "name": "Polygon",
        "element_type": "Point32",
        "element_snake": "point32",
        "field_name": "points",
    },
}

POLYGON_STAMPED = {
    "polygon_stamped": {
        "name": "PolygonStamped",
        "base": "polygon",
        "base_type": "Polygon",
    },
}


def generate_basic_header(snake_name, info):
    """Generate header for basic types (Point, Vector3, Quaternion, etc.)"""
    name = info["name"]
    upper = name.upper()
    fields = info["fields"]

    fields_str = "\n".join([f"  {ctype} {fname};" for fname, ctype in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} message type

#ifndef GEOMETRY_MSGS__MSG__{upper}_H_
#define GEOMETRY_MSGS__MSG__{upper}_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {{
#endif

typedef struct geometry_msgs__msg__{name}
{{
{fields_str}
}} geometry_msgs__msg__{name};

typedef struct geometry_msgs__msg__{name}__Sequence
{{
  geometry_msgs__msg__{name} * data;
  size_t size;
  size_t capacity;
}} geometry_msgs__msg__{name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // GEOMETRY_MSGS__MSG__{upper}_H_
'''


def generate_basic_functions(snake_name, info):
    """Generate functions for basic types"""
    name = info["name"]
    fields = info["fields"]

    init_fields = []
    for fname, ctype in fields:
        if ctype == "double":
            default = info.get(f"default_{fname}", "0.0")
            init_fields.append(f"  msg->{fname} = {default};")
        elif ctype == "float":
            default = info.get(f"default_{fname}", "0.0f")
            init_fields.append(f"  msg->{fname} = {default};")

    init_str = "\n".join(init_fields)

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/{snake_name}.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return false; }}
{init_str}
  return true;
}}

void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg)
{{
  (void)msg;
}}

geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name} * msg =
    (geometry_msgs__msg__{name} *)allocator.allocate(
      sizeof(geometry_msgs__msg__{name}), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!geometry_msgs__msg__{name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {{
    array->data = (geometry_msgs__msg__{name} *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__{name}), allocator.state);
    if (!array->data) {{ return false; }}
  }} else {{
    array->data = NULL;
  }}
  array->size = size;
  array->capacity = size;
  return true;
}}

void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array)
{{
  if (!array || !array->data) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}}
'''


def generate_type_support(snake_name, name):
    """Generate type support stub"""
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} type support

#include "geometry_msgs/msg/{snake_name}.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static const rosidl_typesupport_introspection_c__MessageMembers
geometry_msgs__msg__{name}__message_members = {{
  "geometry_msgs", "{name}", 0, sizeof(geometry_msgs__msg__{name}), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)geometry_msgs__msg__{name}__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)geometry_msgs__msg__{name}__fini
}};

static rosidl_message_type_support_t geometry_msgs__msg__{name}__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &geometry_msgs__msg__{name}__message_members,
  get_message_typesupport_handle_function,
  &geometry_msgs__msg__{name}__type_support
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, geometry_msgs, msg, {name})()
{{
  return &geometry_msgs__msg__{name}__type_support;
}}
'''


def generate_compound_header(snake_name, info):
    """Generate header for compound types (Pose, Transform, Twist, etc.)"""
    name = info["name"]
    upper = name.upper()
    fields = info["fields"]
    deps = info.get("deps", [])

    includes = "\n".join([f'#include "geometry_msgs/msg/{d}.h"' for d in deps])
    fields_str = "\n".join([f"  {ctype} {fname};" for fname, ctype in fields])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} message type

#ifndef GEOMETRY_MSGS__MSG__{upper}_H_
#define GEOMETRY_MSGS__MSG__{upper}_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
{includes}

#ifdef __cplusplus
extern "C" {{
#endif

typedef struct geometry_msgs__msg__{name}
{{
{fields_str}
}} geometry_msgs__msg__{name};

typedef struct geometry_msgs__msg__{name}__Sequence
{{
  geometry_msgs__msg__{name} * data;
  size_t size;
  size_t capacity;
}} geometry_msgs__msg__{name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // GEOMETRY_MSGS__MSG__{upper}_H_
'''


def generate_compound_functions(snake_name, info):
    """Generate functions for compound types"""
    name = info["name"]
    fields = info["fields"]

    init_calls = []
    fini_calls = []
    for fname, ctype in fields:
        if ctype.startswith("geometry_msgs__msg__"):
            base_type = ctype.replace("geometry_msgs__msg__", "")
            init_calls.append(f"  if (!geometry_msgs__msg__{base_type}__init(&msg->{fname})) {{ return false; }}")
            fini_calls.append(f"  geometry_msgs__msg__{base_type}__fini(&msg->{fname});")
        else:
            init_calls.append(f"  msg->{fname} = 0.0;")

    init_str = "\n".join(init_calls)
    fini_str = "\n".join(fini_calls) if fini_calls else "  (void)msg;"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/{snake_name}.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return false; }}
{init_str}
  return true;
}}

void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
{fini_str}
}}

geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name} * msg =
    (geometry_msgs__msg__{name} *)allocator.allocate(
      sizeof(geometry_msgs__msg__{name}), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!geometry_msgs__msg__{name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {{
    array->data = (geometry_msgs__msg__{name} *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__{name}), allocator.state);
    if (!array->data) {{ return false; }}
    for (size_t i = 0; i < size; ++i) {{
      if (!geometry_msgs__msg__{name}__init(&array->data[i])) {{
        for (size_t j = 0; j < i; ++j) {{
          geometry_msgs__msg__{name}__fini(&array->data[j]);
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

void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array)
{{
  if (!array) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {{
    for (size_t i = 0; i < array->size; ++i) {{
      geometry_msgs__msg__{name}__fini(&array->data[i]);
    }}
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }}
}}
'''


def generate_covariance_header(snake_name, info):
    """Generate header for covariance types"""
    name = info["name"]
    upper = name.upper()
    base_fname, base_type = info["base_field"]
    cov_size = info["covariance_size"]
    deps = info.get("deps", [])

    includes = "\n".join([f'#include "geometry_msgs/msg/{d}.h"' for d in deps])

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} message type

#ifndef GEOMETRY_MSGS__MSG__{upper}_H_
#define GEOMETRY_MSGS__MSG__{upper}_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
{includes}

#ifdef __cplusplus
extern "C" {{
#endif

typedef struct geometry_msgs__msg__{name}
{{
  {base_type} {base_fname};
  double covariance[{cov_size}];
}} geometry_msgs__msg__{name};

typedef struct geometry_msgs__msg__{name}__Sequence
{{
  geometry_msgs__msg__{name} * data;
  size_t size;
  size_t capacity;
}} geometry_msgs__msg__{name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // GEOMETRY_MSGS__MSG__{upper}_H_
'''


def generate_covariance_functions(snake_name, info):
    """Generate functions for covariance types"""
    name = info["name"]
    base_fname, base_type = info["base_field"]
    cov_size = info["covariance_size"]
    base_name = base_type.replace("geometry_msgs__msg__", "")

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "geometry_msgs/msg/{snake_name}.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return false; }}
  if (!geometry_msgs__msg__{base_name}__init(&msg->{base_fname})) {{
    return false;
  }}
  memset(msg->covariance, 0, sizeof(msg->covariance));
  return true;
}}

void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  geometry_msgs__msg__{base_name}__fini(&msg->{base_fname});
}}

geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name} * msg =
    (geometry_msgs__msg__{name} *)allocator.allocate(
      sizeof(geometry_msgs__msg__{name}), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!geometry_msgs__msg__{name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {{
    array->data = (geometry_msgs__msg__{name} *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__{name}), allocator.state);
    if (!array->data) {{ return false; }}
    for (size_t i = 0; i < size; ++i) {{
      if (!geometry_msgs__msg__{name}__init(&array->data[i])) {{
        for (size_t j = 0; j < i; ++j) {{
          geometry_msgs__msg__{name}__fini(&array->data[j]);
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

void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array)
{{
  if (!array) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {{
    for (size_t i = 0; i < array->size; ++i) {{
      geometry_msgs__msg__{name}__fini(&array->data[i]);
    }}
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }}
}}
'''


def generate_stamped_header(snake_name, info):
    """Generate header for stamped types"""
    name = info["name"]
    upper = name.upper()
    base = info["base"]
    base_type = info["base_type"]
    field_name = info.get("field_name", base)
    extra_field = info.get("extra_field")

    extra_include = ""
    extra_field_decl = ""
    if extra_field:
        extra_include = '#include "rosidl_runtime_c/string.h"'
        extra_field_decl = f"  {extra_field[1]} {extra_field[0]};"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} message type

#ifndef GEOMETRY_MSGS__MSG__{upper}_H_
#define GEOMETRY_MSGS__MSG__{upper}_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "geometry_msgs/msg/{base}.h"
{extra_include}

#ifdef __cplusplus
extern "C" {{
#endif

typedef struct geometry_msgs__msg__{name}
{{
  std_msgs__msg__Header header;
{extra_field_decl}
  geometry_msgs__msg__{base_type} {field_name};
}} geometry_msgs__msg__{name};

typedef struct geometry_msgs__msg__{name}__Sequence
{{
  geometry_msgs__msg__{name} * data;
  size_t size;
  size_t capacity;
}} geometry_msgs__msg__{name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // GEOMETRY_MSGS__MSG__{upper}_H_
'''


def generate_stamped_functions(snake_name, info):
    """Generate functions for stamped types"""
    name = info["name"]
    base_type = info["base_type"]
    field_name = info.get("field_name", info["base"])
    extra_field = info.get("extra_field")

    extra_init = ""
    extra_fini = ""
    extra_include = ""
    if extra_field:
        extra_include = '#include "rosidl_runtime_c/string_functions.h"'
        extra_init = f'''  if (!rosidl_runtime_c__String__init(&msg->{extra_field[0]})) {{
    geometry_msgs__msg__{base_type}__fini(&msg->{field_name});
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }}'''
        extra_fini = f"  rosidl_runtime_c__String__fini(&msg->{extra_field[0]});"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/{snake_name}.h"
#include "rcutils/allocator.h"
{extra_include}

bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return false; }}
  if (!std_msgs__msg__Header__init(&msg->header)) {{
    return false;
  }}
  if (!geometry_msgs__msg__{base_type}__init(&msg->{field_name})) {{
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }}
{extra_init}
  return true;
}}

void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  std_msgs__msg__Header__fini(&msg->header);
{extra_fini}
  geometry_msgs__msg__{base_type}__fini(&msg->{field_name});
}}

geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name} * msg =
    (geometry_msgs__msg__{name} *)allocator.allocate(
      sizeof(geometry_msgs__msg__{name}), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!geometry_msgs__msg__{name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {{
    array->data = (geometry_msgs__msg__{name} *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__{name}), allocator.state);
    if (!array->data) {{ return false; }}
    for (size_t i = 0; i < size; ++i) {{
      if (!geometry_msgs__msg__{name}__init(&array->data[i])) {{
        for (size_t j = 0; j < i; ++j) {{
          geometry_msgs__msg__{name}__fini(&array->data[j]);
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

void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array)
{{
  if (!array) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {{
    for (size_t i = 0; i < array->size; ++i) {{
      geometry_msgs__msg__{name}__fini(&array->data[i]);
    }}
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }}
}}
'''


def generate_array_header(snake_name, info):
    """Generate header for array types (PoseArray, Polygon)"""
    name = info["name"]
    upper = name.upper()
    elem_type = info["element_type"]
    elem_snake = info["element_snake"]
    field_name = info.get("field_name", "poses")
    is_stamped = "header" in info

    header_field = "  std_msgs__msg__Header header;" if is_stamped else ""
    header_include = '#include "std_msgs/msg/header.h"' if is_stamped else ""

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} message type

#ifndef GEOMETRY_MSGS__MSG__{upper}_H_
#define GEOMETRY_MSGS__MSG__{upper}_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
{header_include}
#include "geometry_msgs/msg/{elem_snake}.h"

#ifdef __cplusplus
extern "C" {{
#endif

typedef struct geometry_msgs__msg__{name}
{{
{header_field}
  geometry_msgs__msg__{elem_type}__Sequence {field_name};
}} geometry_msgs__msg__{name};

typedef struct geometry_msgs__msg__{name}__Sequence
{{
  geometry_msgs__msg__{name} * data;
  size_t size;
  size_t capacity;
}} geometry_msgs__msg__{name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // GEOMETRY_MSGS__MSG__{upper}_H_
'''


def generate_array_functions(snake_name, info):
    """Generate functions for array types"""
    name = info["name"]
    elem_type = info["element_type"]
    field_name = info.get("field_name", "poses")
    is_stamped = "header" in info

    header_init = "  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }" if is_stamped else ""
    header_fini = "  std_msgs__msg__Header__fini(&msg->header);" if is_stamped else ""

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/{name} functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "geometry_msgs/msg/{snake_name}.h"
#include "rcutils/allocator.h"

bool geometry_msgs__msg__{name}__init(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return false; }}
{header_init}
  if (!geometry_msgs__msg__{elem_type}__Sequence__init(&msg->{field_name}, 0)) {{
    return false;
  }}
  return true;
}}

void geometry_msgs__msg__{name}__fini(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
{header_fini}
  geometry_msgs__msg__{elem_type}__Sequence__fini(&msg->{field_name});
}}

geometry_msgs__msg__{name} * geometry_msgs__msg__{name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name} * msg =
    (geometry_msgs__msg__{name} *)allocator.allocate(
      sizeof(geometry_msgs__msg__{name}), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!geometry_msgs__msg__{name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void geometry_msgs__msg__{name}__destroy(geometry_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  geometry_msgs__msg__{name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool geometry_msgs__msg__{name}__Sequence__init(
  geometry_msgs__msg__{name}__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {{
    array->data = (geometry_msgs__msg__{name} *)allocator.zero_allocate(
      size, sizeof(geometry_msgs__msg__{name}), allocator.state);
    if (!array->data) {{ return false; }}
    for (size_t i = 0; i < size; ++i) {{
      if (!geometry_msgs__msg__{name}__init(&array->data[i])) {{
        for (size_t j = 0; j < i; ++j) {{
          geometry_msgs__msg__{name}__fini(&array->data[j]);
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

void geometry_msgs__msg__{name}__Sequence__fini(
  geometry_msgs__msg__{name}__Sequence * array)
{{
  if (!array) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {{
    for (size_t i = 0; i < array->size; ++i) {{
      geometry_msgs__msg__{name}__fini(&array->data[i]);
    }}
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }}
}}
'''


def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        f.write(content)


def generate_all():
    include_dir = os.path.join(OUTPUT_DIR, "include", "geometry_msgs", "msg")
    src_dir = os.path.join(OUTPUT_DIR, "src", "msg")

    # Basic types
    for snake_name, info in BASIC_TYPES.items():
        write_file(os.path.join(include_dir, f"{snake_name}.h"), generate_basic_header(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__functions.c"), generate_basic_functions(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__type_support.c"), generate_type_support(snake_name, info["name"]))
        print(f"Generated: {info['name']}")

    # Compound types
    for snake_name, info in COMPOUND_TYPES.items():
        write_file(os.path.join(include_dir, f"{snake_name}.h"), generate_compound_header(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__functions.c"), generate_compound_functions(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__type_support.c"), generate_type_support(snake_name, info["name"]))
        print(f"Generated: {info['name']}")

    # Covariance types
    for snake_name, info in COVARIANCE_TYPES.items():
        write_file(os.path.join(include_dir, f"{snake_name}.h"), generate_covariance_header(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__functions.c"), generate_covariance_functions(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__type_support.c"), generate_type_support(snake_name, info["name"]))
        print(f"Generated: {info['name']}")

    # Stamped types
    for snake_name, info in STAMPED_TYPES.items():
        write_file(os.path.join(include_dir, f"{snake_name}.h"), generate_stamped_header(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__functions.c"), generate_stamped_functions(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__type_support.c"), generate_type_support(snake_name, info["name"]))
        print(f"Generated: {info['name']}")

    # Array types (PoseArray, Polygon)
    pose_array_info = {"name": "PoseArray", "element_type": "Pose", "element_snake": "pose", "field_name": "poses", "header": True}
    write_file(os.path.join(include_dir, "pose_array.h"), generate_array_header("pose_array", pose_array_info))
    write_file(os.path.join(src_dir, "pose_array__functions.c"), generate_array_functions("pose_array", pose_array_info))
    write_file(os.path.join(src_dir, "pose_array__type_support.c"), generate_type_support("pose_array", "PoseArray"))
    print("Generated: PoseArray")

    polygon_info = {"name": "Polygon", "element_type": "Point32", "element_snake": "point32", "field_name": "points"}
    write_file(os.path.join(include_dir, "polygon.h"), generate_array_header("polygon", polygon_info))
    write_file(os.path.join(src_dir, "polygon__functions.c"), generate_array_functions("polygon", polygon_info))
    write_file(os.path.join(src_dir, "polygon__type_support.c"), generate_type_support("polygon", "Polygon"))
    print("Generated: Polygon")

    # PolygonStamped
    polygon_stamped_info = {"name": "PolygonStamped", "base": "polygon", "base_type": "Polygon"}
    write_file(os.path.join(include_dir, "polygon_stamped.h"), generate_stamped_header("polygon_stamped", polygon_stamped_info))
    write_file(os.path.join(src_dir, "polygon_stamped__functions.c"), generate_stamped_functions("polygon_stamped", polygon_stamped_info))
    write_file(os.path.join(src_dir, "polygon_stamped__type_support.c"), generate_type_support("polygon_stamped", "PolygonStamped"))
    print("Generated: PolygonStamped")

    total = len(BASIC_TYPES) + len(COMPOUND_TYPES) + len(COVARIANCE_TYPES) + len(STAMPED_TYPES) + 3
    print(f"\nGenerated {total} geometry_msgs types")


if __name__ == "__main__":
    generate_all()
