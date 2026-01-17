// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/Marker type

#ifndef VISUALIZATION_MSGS__MSG__MARKER_H_
#define VISUALIZATION_MSGS__MSG__MARKER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "std_msgs/msg/color_rgba.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "geometry_msgs/msg/pose.h"
#include "geometry_msgs/msg/vector3.h"
#include "geometry_msgs/msg/point.h"
#include "builtin_interfaces/msg/duration.h"
#include "sensor_msgs/msg/compressed_image.h"
#include "visualization_msgs/msg/uv_coordinate.h"
#include "visualization_msgs/msg/mesh_file.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define VISUALIZATION_MSGS__MSG__Marker_ARROW 0
#define VISUALIZATION_MSGS__MSG__Marker_CUBE 1
#define VISUALIZATION_MSGS__MSG__Marker_SPHERE 2
#define VISUALIZATION_MSGS__MSG__Marker_CYLINDER 3
#define VISUALIZATION_MSGS__MSG__Marker_LINE_STRIP 4
#define VISUALIZATION_MSGS__MSG__Marker_LINE_LIST 5
#define VISUALIZATION_MSGS__MSG__Marker_CUBE_LIST 6
#define VISUALIZATION_MSGS__MSG__Marker_SPHERE_LIST 7
#define VISUALIZATION_MSGS__MSG__Marker_POINTS 8
#define VISUALIZATION_MSGS__MSG__Marker_TEXT_VIEW_FACING 9
#define VISUALIZATION_MSGS__MSG__Marker_MESH_RESOURCE 10
#define VISUALIZATION_MSGS__MSG__Marker_TRIANGLE_LIST 11
#define VISUALIZATION_MSGS__MSG__Marker_ADD 0
#define VISUALIZATION_MSGS__MSG__Marker_MODIFY 0
#define VISUALIZATION_MSGS__MSG__Marker_DELETE 2
#define VISUALIZATION_MSGS__MSG__Marker_DELETEALL 3

typedef struct visualization_msgs__msg__Marker
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String ns;
  int32_t id;
  int32_t type;
  int32_t action;
  geometry_msgs__msg__Pose pose;
  geometry_msgs__msg__Vector3 scale;
  std_msgs__msg__ColorRGBA color;
  builtin_interfaces__msg__Duration lifetime;
  bool frame_locked;
  geometry_msgs__msg__Point__Sequence points;
  std_msgs__msg__ColorRGBA__Sequence colors;
  rosidl_runtime_c__String texture_resource;
  sensor_msgs__msg__CompressedImage texture;
  visualization_msgs__msg__UVCoordinate__Sequence uv_coordinates;
  rosidl_runtime_c__String text;
  rosidl_runtime_c__String mesh_resource;
  visualization_msgs__msg__MeshFile mesh_file;
  bool mesh_use_embedded_materials;
} visualization_msgs__msg__Marker;

typedef struct visualization_msgs__msg__Marker__Sequence
{
  visualization_msgs__msg__Marker * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__Marker__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__Marker__init(visualization_msgs__msg__Marker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__Marker__fini(visualization_msgs__msg__Marker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__Marker * visualization_msgs__msg__Marker__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__Marker__destroy(visualization_msgs__msg__Marker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__Marker__Sequence__init(
  visualization_msgs__msg__Marker__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__Marker__Sequence__fini(
  visualization_msgs__msg__Marker__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__MARKER_H_
