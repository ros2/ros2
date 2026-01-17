// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Vector3Stamped message type

#ifndef GEOMETRY_MSGS__MSG__VECTOR3STAMPED_H_
#define GEOMETRY_MSGS__MSG__VECTOR3STAMPED_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "geometry_msgs/msg/vector3.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__Vector3Stamped
{
  std_msgs__msg__Header header;

  geometry_msgs__msg__Vector3 vector3;
} geometry_msgs__msg__Vector3Stamped;

typedef struct geometry_msgs__msg__Vector3Stamped__Sequence
{
  geometry_msgs__msg__Vector3Stamped * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Vector3Stamped__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Vector3Stamped__init(geometry_msgs__msg__Vector3Stamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Vector3Stamped__fini(geometry_msgs__msg__Vector3Stamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Vector3Stamped * geometry_msgs__msg__Vector3Stamped__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Vector3Stamped__destroy(geometry_msgs__msg__Vector3Stamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Vector3Stamped__Sequence__init(
  geometry_msgs__msg__Vector3Stamped__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Vector3Stamped__Sequence__fini(
  geometry_msgs__msg__Vector3Stamped__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__VECTOR3STAMPED_H_
