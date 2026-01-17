// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Wrench message type

#ifndef GEOMETRY_MSGS__MSG__WRENCH_H_
#define GEOMETRY_MSGS__MSG__WRENCH_H_

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

typedef struct geometry_msgs__msg__Wrench
{
  geometry_msgs__msg__Vector3 force;
  geometry_msgs__msg__Vector3 torque;
} geometry_msgs__msg__Wrench;

typedef struct geometry_msgs__msg__Wrench__Sequence
{
  geometry_msgs__msg__Wrench * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Wrench__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Wrench__init(geometry_msgs__msg__Wrench * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Wrench__fini(geometry_msgs__msg__Wrench * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Wrench * geometry_msgs__msg__Wrench__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Wrench__destroy(geometry_msgs__msg__Wrench * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Wrench__Sequence__init(
  geometry_msgs__msg__Wrench__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Wrench__Sequence__fini(
  geometry_msgs__msg__Wrench__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__WRENCH_H_
