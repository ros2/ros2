// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/Pose2D message type

#ifndef GEOMETRY_MSGS__MSG__POSE2D_H_
#define GEOMETRY_MSGS__MSG__POSE2D_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__Pose2D
{
  double x;
  double y;
  double theta;
} geometry_msgs__msg__Pose2D;

typedef struct geometry_msgs__msg__Pose2D__Sequence
{
  geometry_msgs__msg__Pose2D * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__Pose2D__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Pose2D__init(geometry_msgs__msg__Pose2D * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Pose2D__fini(geometry_msgs__msg__Pose2D * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__Pose2D * geometry_msgs__msg__Pose2D__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Pose2D__destroy(geometry_msgs__msg__Pose2D * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__Pose2D__Sequence__init(
  geometry_msgs__msg__Pose2D__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__Pose2D__Sequence__fini(
  geometry_msgs__msg__Pose2D__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__POSE2D_H_
