// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Transform message type

#ifndef GEOMETRY_MSGS__MSG__TRANSFORM_H_
#define GEOMETRY_MSGS__MSG__TRANSFORM_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/vector3.h"
#include "geometry_msgs/msg/quaternion.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__Transform
{
  geometry_msgs__msg__Vector3 translation;
  geometry_msgs__msg__Quaternion rotation;
} geometry_msgs__msg__Transform;

typedef struct geometry_msgs__msg__Transform__Sequence
{
  geometry_msgs__msg__Transform * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Transform__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Transform__init(geometry_msgs__msg__Transform * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Transform__fini(geometry_msgs__msg__Transform * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Transform * geometry_msgs__msg__Transform__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Transform__destroy(geometry_msgs__msg__Transform * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Transform__Sequence__init(
  geometry_msgs__msg__Transform__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Transform__Sequence__fini(
  geometry_msgs__msg__Transform__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__TRANSFORM_H_
