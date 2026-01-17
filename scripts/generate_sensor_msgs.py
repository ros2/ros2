#!/usr/bin/env python3
# Copyright (c) 2024 ROS2 OpenHarmony Port Project
# Generate sensor_msgs message type implementations

import os
import sys

OUTPUT_DIR = sys.argv[1] if len(sys.argv) > 1 else "ohos_ros2/interfaces/sensor_msgs"

# ============================================================================
# Message Type Definitions
# ============================================================================

MESSAGES = {
    # ========== Image/Camera Types ==========
    "region_of_interest": {
        "name": "RegionOfInterest",
        "fields": [
            ("x_offset", "uint32_t", None),
            ("y_offset", "uint32_t", None),
            ("height", "uint32_t", None),
            ("width", "uint32_t", None),
            ("do_rectify", "bool", None),
        ],
        "includes": [],
    },
    "image": {
        "name": "Image",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("height", "uint32_t", None),
            ("width", "uint32_t", None),
            ("encoding", "rosidl_runtime_c__String", "rosidl_runtime_c/string.h"),
            ("is_bigendian", "uint8_t", None),
            ("step", "uint32_t", None),
            ("data", "rosidl_runtime_c__uint8__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "compressed_image": {
        "name": "CompressedImage",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("format", "rosidl_runtime_c__String", "rosidl_runtime_c/string.h"),
            ("data", "rosidl_runtime_c__uint8__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "camera_info": {
        "name": "CameraInfo",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("height", "uint32_t", None),
            ("width", "uint32_t", None),
            ("distortion_model", "rosidl_runtime_c__String", "rosidl_runtime_c/string.h"),
            ("d", "rosidl_runtime_c__double__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
            ("k", "double[9]", None),
            ("r", "double[9]", None),
            ("p", "double[12]", None),
            ("binning_x", "uint32_t", None),
            ("binning_y", "uint32_t", None),
            ("roi", "sensor_msgs__msg__RegionOfInterest", "sensor_msgs/msg/region_of_interest.h"),
        ],
        "includes": ["std_msgs/msg/header.h", "sensor_msgs/msg/region_of_interest.h"],
    },

    # ========== Point Cloud Types ==========
    "point_field": {
        "name": "PointField",
        "fields": [
            ("name", "rosidl_runtime_c__String", "rosidl_runtime_c/string.h"),
            ("offset", "uint32_t", None),
            ("datatype", "uint8_t", None),
            ("count", "uint32_t", None),
        ],
        "includes": [],
        "constants": [
            ("INT8", "uint8_t", "1"),
            ("UINT8", "uint8_t", "2"),
            ("INT16", "uint8_t", "3"),
            ("UINT16", "uint8_t", "4"),
            ("INT32", "uint8_t", "5"),
            ("UINT32", "uint8_t", "6"),
            ("FLOAT32", "uint8_t", "7"),
            ("FLOAT64", "uint8_t", "8"),
        ],
    },
    "point_cloud2": {
        "name": "PointCloud2",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("height", "uint32_t", None),
            ("width", "uint32_t", None),
            ("fields", "sensor_msgs__msg__PointField__Sequence", "sensor_msgs/msg/point_field.h"),
            ("is_bigendian", "bool", None),
            ("point_step", "uint32_t", None),
            ("row_step", "uint32_t", None),
            ("data", "rosidl_runtime_c__uint8__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
            ("is_dense", "bool", None),
        ],
        "includes": ["std_msgs/msg/header.h", "sensor_msgs/msg/point_field.h"],
    },
    "channel_float32": {
        "name": "ChannelFloat32",
        "fields": [
            ("name", "rosidl_runtime_c__String", "rosidl_runtime_c/string.h"),
            ("values", "rosidl_runtime_c__float__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
        ],
        "includes": [],
    },

    # ========== Laser Types ==========
    "laser_echo": {
        "name": "LaserEcho",
        "fields": [
            ("echoes", "rosidl_runtime_c__float__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
        ],
        "includes": [],
    },
    "laser_scan": {
        "name": "LaserScan",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("angle_min", "float", None),
            ("angle_max", "float", None),
            ("angle_increment", "float", None),
            ("time_increment", "float", None),
            ("scan_time", "float", None),
            ("range_min", "float", None),
            ("range_max", "float", None),
            ("ranges", "rosidl_runtime_c__float__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
            ("intensities", "rosidl_runtime_c__float__Sequence", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "multi_echo_laser_scan": {
        "name": "MultiEchoLaserScan",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("angle_min", "float", None),
            ("angle_max", "float", None),
            ("angle_increment", "float", None),
            ("time_increment", "float", None),
            ("scan_time", "float", None),
            ("range_min", "float", None),
            ("range_max", "float", None),
            ("ranges", "sensor_msgs__msg__LaserEcho__Sequence", "sensor_msgs/msg/laser_echo.h"),
            ("intensities", "sensor_msgs__msg__LaserEcho__Sequence", None),
        ],
        "includes": ["std_msgs/msg/header.h", "sensor_msgs/msg/laser_echo.h"],
    },

    # ========== IMU/Navigation Types ==========
    "imu": {
        "name": "Imu",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("orientation", "geometry_msgs__msg__Quaternion", "geometry_msgs/msg/quaternion.h"),
            ("orientation_covariance", "double[9]", None),
            ("angular_velocity", "geometry_msgs__msg__Vector3", "geometry_msgs/msg/vector3.h"),
            ("angular_velocity_covariance", "double[9]", None),
            ("linear_acceleration", "geometry_msgs__msg__Vector3", None),
            ("linear_acceleration_covariance", "double[9]", None),
        ],
        "includes": ["std_msgs/msg/header.h", "geometry_msgs/msg/quaternion.h", "geometry_msgs/msg/vector3.h"],
    },
    "magnetic_field": {
        "name": "MagneticField",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("magnetic_field", "geometry_msgs__msg__Vector3", "geometry_msgs/msg/vector3.h"),
            ("magnetic_field_covariance", "double[9]", None),
        ],
        "includes": ["std_msgs/msg/header.h", "geometry_msgs/msg/vector3.h"],
    },
    "nav_sat_status": {
        "name": "NavSatStatus",
        "fields": [
            ("status", "int8_t", None),
            ("service", "uint16_t", None),
        ],
        "includes": [],
        "constants": [
            ("STATUS_NO_FIX", "int8_t", "-1"),
            ("STATUS_FIX", "int8_t", "0"),
            ("STATUS_SBAS_FIX", "int8_t", "1"),
            ("STATUS_GBAS_FIX", "int8_t", "2"),
            ("SERVICE_GPS", "uint16_t", "1"),
            ("SERVICE_GLONASS", "uint16_t", "2"),
            ("SERVICE_COMPASS", "uint16_t", "4"),
            ("SERVICE_GALILEO", "uint16_t", "8"),
        ],
    },
    "nav_sat_fix": {
        "name": "NavSatFix",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("status", "sensor_msgs__msg__NavSatStatus", "sensor_msgs/msg/nav_sat_status.h"),
            ("latitude", "double", None),
            ("longitude", "double", None),
            ("altitude", "double", None),
            ("position_covariance", "double[9]", None),
            ("position_covariance_type", "uint8_t", None),
        ],
        "includes": ["std_msgs/msg/header.h", "sensor_msgs/msg/nav_sat_status.h"],
        "constants": [
            ("COVARIANCE_TYPE_UNKNOWN", "uint8_t", "0"),
            ("COVARIANCE_TYPE_APPROXIMATED", "uint8_t", "1"),
            ("COVARIANCE_TYPE_DIAGONAL_KNOWN", "uint8_t", "2"),
            ("COVARIANCE_TYPE_KNOWN", "uint8_t", "3"),
        ],
    },

    # ========== Range/Environment Types ==========
    "range": {
        "name": "Range",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("radiation_type", "uint8_t", None),
            ("field_of_view", "float", None),
            ("min_range", "float", None),
            ("max_range", "float", None),
            ("range", "float", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
        "constants": [
            ("ULTRASOUND", "uint8_t", "0"),
            ("INFRARED", "uint8_t", "1"),
        ],
    },
    "temperature": {
        "name": "Temperature",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("temperature", "double", None),
            ("variance", "double", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "relative_humidity": {
        "name": "RelativeHumidity",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("relative_humidity", "double", None),
            ("variance", "double", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "fluid_pressure": {
        "name": "FluidPressure",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("fluid_pressure", "double", None),
            ("variance", "double", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "illuminance": {
        "name": "Illuminance",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("illuminance", "double", None),
            ("variance", "double", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },

    # ========== Battery/Power Types ==========
    "battery_state": {
        "name": "BatteryState",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("voltage", "float", None),
            ("temperature", "float", None),
            ("current", "float", None),
            ("charge", "float", None),
            ("capacity", "float", None),
            ("design_capacity", "float", None),
            ("percentage", "float", None),
            ("power_supply_status", "uint8_t", None),
            ("power_supply_health", "uint8_t", None),
            ("power_supply_technology", "uint8_t", None),
            ("present", "bool", None),
            ("cell_voltage", "rosidl_runtime_c__float__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
            ("cell_temperature", "rosidl_runtime_c__float__Sequence", None),
            ("location", "rosidl_runtime_c__String", "rosidl_runtime_c/string.h"),
            ("serial_number", "rosidl_runtime_c__String", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
        "constants": [
            ("POWER_SUPPLY_STATUS_UNKNOWN", "uint8_t", "0"),
            ("POWER_SUPPLY_STATUS_CHARGING", "uint8_t", "1"),
            ("POWER_SUPPLY_STATUS_DISCHARGING", "uint8_t", "2"),
            ("POWER_SUPPLY_STATUS_NOT_CHARGING", "uint8_t", "3"),
            ("POWER_SUPPLY_STATUS_FULL", "uint8_t", "4"),
            ("POWER_SUPPLY_HEALTH_UNKNOWN", "uint8_t", "0"),
            ("POWER_SUPPLY_HEALTH_GOOD", "uint8_t", "1"),
            ("POWER_SUPPLY_HEALTH_OVERHEAT", "uint8_t", "2"),
            ("POWER_SUPPLY_HEALTH_DEAD", "uint8_t", "3"),
            ("POWER_SUPPLY_HEALTH_OVERVOLTAGE", "uint8_t", "4"),
            ("POWER_SUPPLY_HEALTH_UNSPEC_FAILURE", "uint8_t", "5"),
            ("POWER_SUPPLY_HEALTH_COLD", "uint8_t", "6"),
            ("POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE", "uint8_t", "7"),
            ("POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE", "uint8_t", "8"),
            ("POWER_SUPPLY_TECHNOLOGY_UNKNOWN", "uint8_t", "0"),
            ("POWER_SUPPLY_TECHNOLOGY_NIMH", "uint8_t", "1"),
            ("POWER_SUPPLY_TECHNOLOGY_LION", "uint8_t", "2"),
            ("POWER_SUPPLY_TECHNOLOGY_LIPO", "uint8_t", "3"),
            ("POWER_SUPPLY_TECHNOLOGY_LIFE", "uint8_t", "4"),
            ("POWER_SUPPLY_TECHNOLOGY_NICD", "uint8_t", "5"),
            ("POWER_SUPPLY_TECHNOLOGY_LIMN", "uint8_t", "6"),
        ],
    },

    # ========== Input Types ==========
    "joy": {
        "name": "Joy",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("axes", "rosidl_runtime_c__float__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
            ("buttons", "rosidl_runtime_c__int32__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "joy_feedback": {
        "name": "JoyFeedback",
        "fields": [
            ("type", "uint8_t", None),
            ("id", "uint8_t", None),
            ("intensity", "float", None),
        ],
        "includes": [],
        "constants": [
            ("TYPE_LED", "uint8_t", "0"),
            ("TYPE_RUMBLE", "uint8_t", "1"),
            ("TYPE_BUZZER", "uint8_t", "2"),
        ],
    },
    "joy_feedback_array": {
        "name": "JoyFeedbackArray",
        "fields": [
            ("array", "sensor_msgs__msg__JoyFeedback__Sequence", "sensor_msgs/msg/joy_feedback.h"),
        ],
        "includes": ["sensor_msgs/msg/joy_feedback.h"],
    },

    # ========== Joint Types ==========
    "joint_state": {
        "name": "JointState",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("name", "rosidl_runtime_c__String__Sequence", "rosidl_runtime_c/string.h"),
            ("position", "rosidl_runtime_c__double__Sequence", "rosidl_runtime_c/primitives_sequence.h"),
            ("velocity", "rosidl_runtime_c__double__Sequence", None),
            ("effort", "rosidl_runtime_c__double__Sequence", None),
        ],
        "includes": ["std_msgs/msg/header.h"],
    },
    "multi_dof_joint_state": {
        "name": "MultiDOFJointState",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("joint_names", "rosidl_runtime_c__String__Sequence", "rosidl_runtime_c/string.h"),
            ("transforms", "geometry_msgs__msg__Transform__Sequence", "geometry_msgs/msg/transform.h"),
            ("twist", "geometry_msgs__msg__Twist__Sequence", "geometry_msgs/msg/twist.h"),
            ("wrench", "geometry_msgs__msg__Wrench__Sequence", "geometry_msgs/msg/wrench.h"),
        ],
        "includes": ["std_msgs/msg/header.h", "geometry_msgs/msg/transform.h", "geometry_msgs/msg/twist.h", "geometry_msgs/msg/wrench.h"],
    },

    # ========== Time Types ==========
    "time_reference": {
        "name": "TimeReference",
        "fields": [
            ("header", "std_msgs__msg__Header", "std_msgs/msg/header.h"),
            ("time_ref", "builtin_interfaces__msg__Time", "builtin_interfaces/msg/time.h"),
            ("source", "rosidl_runtime_c__String", "rosidl_runtime_c/string.h"),
        ],
        "includes": ["std_msgs/msg/header.h", "builtin_interfaces/msg/time.h"],
    },
}


def get_init_code(field_name, field_type):
    """Generate initialization code for a field"""
    if field_type.endswith("__Sequence"):
        base = field_type.replace("__Sequence", "")
        return f"  if (!{base}__Sequence__init(&msg->{field_name}, 0)) {{ return false; }}"
    elif field_type == "rosidl_runtime_c__String":
        return f"  if (!rosidl_runtime_c__String__init(&msg->{field_name})) {{ return false; }}"
    elif field_type.startswith("std_msgs__msg__"):
        return f"  if (!{field_type}__init(&msg->{field_name})) {{ return false; }}"
    elif field_type.startswith("geometry_msgs__msg__"):
        return f"  if (!{field_type}__init(&msg->{field_name})) {{ return false; }}"
    elif field_type.startswith("sensor_msgs__msg__"):
        return f"  if (!{field_type}__init(&msg->{field_name})) {{ return false; }}"
    elif field_type.startswith("builtin_interfaces__msg__"):
        return f"  if (!{field_type}__init(&msg->{field_name})) {{ return false; }}"
    elif "[" in field_type:  # Fixed array
        return f"  memset(msg->{field_name}, 0, sizeof(msg->{field_name}));"
    elif field_type in ("double", "float"):
        return f"  msg->{field_name} = 0.0;"
    elif field_type in ("uint8_t", "int8_t", "uint16_t", "int16_t", "uint32_t", "int32_t", "uint64_t", "int64_t"):
        return f"  msg->{field_name} = 0;"
    elif field_type == "bool":
        return f"  msg->{field_name} = false;"
    return f"  // TODO: init {field_name}"


def get_fini_code(field_name, field_type):
    """Generate finalization code for a field"""
    if field_type.endswith("__Sequence"):
        base = field_type.replace("__Sequence", "")
        return f"  {base}__Sequence__fini(&msg->{field_name});"
    elif field_type == "rosidl_runtime_c__String":
        return f"  rosidl_runtime_c__String__fini(&msg->{field_name});"
    elif field_type.startswith("std_msgs__msg__"):
        return f"  {field_type}__fini(&msg->{field_name});"
    elif field_type.startswith("geometry_msgs__msg__"):
        return f"  {field_type}__fini(&msg->{field_name});"
    elif field_type.startswith("sensor_msgs__msg__"):
        return f"  {field_type}__fini(&msg->{field_name});"
    elif field_type.startswith("builtin_interfaces__msg__"):
        return f"  {field_type}__fini(&msg->{field_name});"
    return None


def generate_header(snake_name, info):
    """Generate header file"""
    name = info["name"]
    upper = name.upper()
    fields = info["fields"]
    includes = info.get("includes", [])
    constants = info.get("constants", [])

    # Generate includes
    include_set = set()
    for inc in includes:
        include_set.add(f'#include "{inc}"')
    for _, ftype, inc in fields:
        if inc:
            include_set.add(f'#include "{inc}"')
    includes_str = "\n".join(sorted(include_set))

    # Generate constants
    constants_str = ""
    if constants:
        const_lines = []
        for const_name, const_type, const_val in constants:
            const_lines.append(f"  sensor_msgs__msg__{name}__{const_name} = {const_val}")
        constants_str = f"\nenum {{\n" + ",\n".join(const_lines) + "\n}};\n"

    # Generate fields
    field_lines = []
    for fname, ftype, _ in fields:
        if "[" in ftype:  # Fixed array
            base_type = ftype.split("[")[0]
            size = ftype.split("[")[1].rstrip("]")
            field_lines.append(f"  {base_type} {fname}[{size}];")
        else:
            field_lines.append(f"  {ftype} {fname};")
    fields_str = "\n".join(field_lines)

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/{name} message type

#ifndef SENSOR_MSGS__MSG__{upper}_H_
#define SENSOR_MSGS__MSG__{upper}_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
{includes_str}

#ifdef __cplusplus
extern "C" {{
#endif
{constants_str}
typedef struct sensor_msgs__msg__{name}
{{
{fields_str}
}} sensor_msgs__msg__{name};

typedef struct sensor_msgs__msg__{name}__Sequence
{{
  sensor_msgs__msg__{name} * data;
  size_t size;
  size_t capacity;
}} sensor_msgs__msg__{name}__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__{name}__init(sensor_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__{name}__fini(sensor_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__{name} * sensor_msgs__msg__{name}__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__{name}__destroy(sensor_msgs__msg__{name} * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__{name}__Sequence__init(
  sensor_msgs__msg__{name}__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__{name}__Sequence__fini(
  sensor_msgs__msg__{name}__Sequence * array);

#ifdef __cplusplus
}}
#endif

#endif  // SENSOR_MSGS__MSG__{upper}_H_
'''


def generate_functions(snake_name, info):
    """Generate functions file"""
    name = info["name"]
    fields = info["fields"]

    # Check if we need string.h for memset
    needs_memset = any("[" in ftype for _, ftype, _ in fields)
    memset_include = '#include <string.h>' if needs_memset else ''

    # Generate init code
    init_lines = []
    for fname, ftype, _ in fields:
        init_lines.append(get_init_code(fname, ftype))
    init_str = "\n".join(init_lines)

    # Generate fini code
    fini_lines = []
    for fname, ftype, _ in fields:
        code = get_fini_code(fname, ftype)
        if code:
            fini_lines.append(code)
    fini_str = "\n".join(fini_lines) if fini_lines else "  (void)msg;"

    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/{name} functions implementation

#include <stdbool.h>
#include <stdlib.h>
{memset_include}
#include "sensor_msgs/msg/{snake_name}.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__{name}__init(sensor_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return false; }}
{init_str}
  return true;
}}

void sensor_msgs__msg__{name}__fini(sensor_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
{fini_str}
}}

sensor_msgs__msg__{name} * sensor_msgs__msg__{name}__create(void)
{{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__{name} * msg =
    (sensor_msgs__msg__{name} *)allocator.allocate(
      sizeof(sensor_msgs__msg__{name}), allocator.state);
  if (!msg) {{ return NULL; }}
  if (!sensor_msgs__msg__{name}__init(msg)) {{
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }}
  return msg;
}}

void sensor_msgs__msg__{name}__destroy(sensor_msgs__msg__{name} * msg)
{{
  if (!msg) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__{name}__fini(msg);
  allocator.deallocate(msg, allocator.state);
}}

bool sensor_msgs__msg__{name}__Sequence__init(
  sensor_msgs__msg__{name}__Sequence * array, size_t size)
{{
  if (!array) {{ return false; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {{
    array->data = (sensor_msgs__msg__{name} *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__{name}), allocator.state);
    if (!array->data) {{ return false; }}
    for (size_t i = 0; i < size; ++i) {{
      if (!sensor_msgs__msg__{name}__init(&array->data[i])) {{
        for (size_t j = 0; j < i; ++j) {{
          sensor_msgs__msg__{name}__fini(&array->data[j]);
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

void sensor_msgs__msg__{name}__Sequence__fini(
  sensor_msgs__msg__{name}__Sequence * array)
{{
  if (!array) {{ return; }}
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {{
    for (size_t i = 0; i < array->size; ++i) {{
      sensor_msgs__msg__{name}__fini(&array->data[i]);
    }}
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }}
}}
'''


def generate_type_support(snake_name, name):
    """Generate type support stub"""
    return f'''// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/{name} type support

#include "sensor_msgs/msg/{snake_name}.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static const rosidl_typesupport_introspection_c__MessageMembers
sensor_msgs__msg__{name}__message_members = {{
  "sensor_msgs", "{name}", 0, sizeof(sensor_msgs__msg__{name}), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)sensor_msgs__msg__{name}__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)sensor_msgs__msg__{name}__fini
}};

static rosidl_message_type_support_t sensor_msgs__msg__{name}__type_support = {{
  rosidl_typesupport_introspection_c__identifier,
  &sensor_msgs__msg__{name}__message_members,
  get_message_typesupport_handle_function,
  &sensor_msgs__msg__{name}__type_support
}};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, sensor_msgs, msg, {name})()
{{
  return &sensor_msgs__msg__{name}__type_support;
}}
'''


def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        f.write(content)


def generate_all():
    include_dir = os.path.join(OUTPUT_DIR, "include", "sensor_msgs", "msg")
    src_dir = os.path.join(OUTPUT_DIR, "src", "msg")

    for snake_name, info in MESSAGES.items():
        name = info["name"]
        write_file(os.path.join(include_dir, f"{snake_name}.h"), generate_header(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__functions.c"), generate_functions(snake_name, info))
        write_file(os.path.join(src_dir, f"{snake_name}__type_support.c"), generate_type_support(snake_name, name))
        print(f"Generated: {name}")

    print(f"\nGenerated {len(MESSAGES)} sensor_msgs types")


if __name__ == "__main__":
    generate_all()
