// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/ImageMarker type

#ifndef VISUALIZATION_MSGS__MSG__IMAGEMARKER_H_
#define VISUALIZATION_MSGS__MSG__IMAGEMARKER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "std_msgs/msg/color_rgba.h"
#include "rosidl_runtime_c/string.h"
#include "geometry_msgs/msg/point.h"
#include "builtin_interfaces/msg/duration.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define VISUALIZATION_MSGS__MSG__ImageMarker_CIRCLE 0
#define VISUALIZATION_MSGS__MSG__ImageMarker_LINE_STRIP 1
#define VISUALIZATION_MSGS__MSG__ImageMarker_LINE_LIST 2
#define VISUALIZATION_MSGS__MSG__ImageMarker_POLYGON 3
#define VISUALIZATION_MSGS__MSG__ImageMarker_POINTS 4
#define VISUALIZATION_MSGS__MSG__ImageMarker_ADD 0
#define VISUALIZATION_MSGS__MSG__ImageMarker_REMOVE 1

typedef struct visualization_msgs__msg__ImageMarker
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String ns;
  int32_t id;
  int32_t type;
  int32_t action;
  geometry_msgs__msg__Point position;
  float scale;
  std_msgs__msg__ColorRGBA outline_color;
  uint8_t filled;
  std_msgs__msg__ColorRGBA fill_color;
  builtin_interfaces__msg__Duration lifetime;
  geometry_msgs__msg__Point__Sequence points;
  std_msgs__msg__ColorRGBA__Sequence outline_colors;
} visualization_msgs__msg__ImageMarker;

typedef struct visualization_msgs__msg__ImageMarker__Sequence
{
  visualization_msgs__msg__ImageMarker * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__ImageMarker__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__ImageMarker__init(visualization_msgs__msg__ImageMarker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__ImageMarker__fini(visualization_msgs__msg__ImageMarker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__ImageMarker * visualization_msgs__msg__ImageMarker__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__ImageMarker__destroy(visualization_msgs__msg__ImageMarker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__ImageMarker__Sequence__init(
  visualization_msgs__msg__ImageMarker__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__ImageMarker__Sequence__fini(
  visualization_msgs__msg__ImageMarker__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__IMAGEMARKER_H_
