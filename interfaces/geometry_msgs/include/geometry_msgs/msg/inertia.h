// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Inertia message type

#ifndef GEOMETRY_MSGS__MSG__INERTIA_H_
#define GEOMETRY_MSGS__MSG__INERTIA_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/vector3.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__Inertia
{
  double m;
  geometry_msgs__msg__Vector3 com;
  double ixx;
  double ixy;
  double ixz;
  double iyy;
  double iyz;
  double izz;
} geometry_msgs__msg__Inertia;

typedef struct geometry_msgs__msg__Inertia__Sequence
{
  geometry_msgs__msg__Inertia * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Inertia__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Inertia__init(geometry_msgs__msg__Inertia * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Inertia__fini(geometry_msgs__msg__Inertia * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Inertia * geometry_msgs__msg__Inertia__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Inertia__destroy(geometry_msgs__msg__Inertia * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Inertia__Sequence__init(
  geometry_msgs__msg__Inertia__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Inertia__Sequence__fini(
  geometry_msgs__msg__Inertia__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__INERTIA_H_
