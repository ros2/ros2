// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Vector3 message type

#ifndef GEOMETRY_MSGS__MSG__VECTOR3_H_
#define GEOMETRY_MSGS__MSG__VECTOR3_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__Vector3
{
  double x;
  double y;
  double z;
} geometry_msgs__msg__Vector3;

typedef struct geometry_msgs__msg__Vector3__Sequence
{
  geometry_msgs__msg__Vector3 * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Vector3__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Vector3__init(geometry_msgs__msg__Vector3 * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Vector3__fini(geometry_msgs__msg__Vector3 * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Vector3 * geometry_msgs__msg__Vector3__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Vector3__destroy(geometry_msgs__msg__Vector3 * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Vector3__Sequence__init(
  geometry_msgs__msg__Vector3__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Vector3__Sequence__fini(
  geometry_msgs__msg__Vector3__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__VECTOR3_H_
