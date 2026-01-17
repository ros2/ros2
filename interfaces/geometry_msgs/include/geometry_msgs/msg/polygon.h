// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Polygon message type

#ifndef GEOMETRY_MSGS__MSG__POLYGON_H_
#define GEOMETRY_MSGS__MSG__POLYGON_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "geometry_msgs/msg/point32.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__Polygon
{

  geometry_msgs__msg__Point32__Sequence points;
} geometry_msgs__msg__Polygon;

typedef struct geometry_msgs__msg__Polygon__Sequence
{
  geometry_msgs__msg__Polygon * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Polygon__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Polygon__init(geometry_msgs__msg__Polygon * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Polygon__fini(geometry_msgs__msg__Polygon * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Polygon * geometry_msgs__msg__Polygon__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Polygon__destroy(geometry_msgs__msg__Polygon * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Polygon__Sequence__init(
  geometry_msgs__msg__Polygon__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Polygon__Sequence__fini(
  geometry_msgs__msg__Polygon__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__POLYGON_H_
