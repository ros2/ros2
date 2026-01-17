// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Point message type

#ifndef GEOMETRY_MSGS__MSG__POINT_H_
#define GEOMETRY_MSGS__MSG__POINT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__Point
{
  double x;
  double y;
  double z;
} geometry_msgs__msg__Point;

typedef struct geometry_msgs__msg__Point__Sequence
{
  geometry_msgs__msg__Point * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Point__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Point__init(geometry_msgs__msg__Point * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Point__fini(geometry_msgs__msg__Point * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Point * geometry_msgs__msg__Point__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Point__destroy(geometry_msgs__msg__Point * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Point__Sequence__init(
  geometry_msgs__msg__Point__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Point__Sequence__fini(
  geometry_msgs__msg__Point__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__POINT_H_
