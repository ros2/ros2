// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/PoseWithCovariance message type

#ifndef GEOMETRY_MSGS__MSG__POSEWITHCOVARIANCE_H_
#define GEOMETRY_MSGS__MSG__POSEWITHCOVARIANCE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/pose.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__PoseWithCovariance
{
  geometry_msgs__msg__Pose pose;
  double covariance[36];
} geometry_msgs__msg__PoseWithCovariance;

typedef struct geometry_msgs__msg__PoseWithCovariance__Sequence
{
  geometry_msgs__msg__PoseWithCovariance * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__PoseWithCovariance__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__PoseWithCovariance__init(geometry_msgs__msg__PoseWithCovariance * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseWithCovariance__fini(geometry_msgs__msg__PoseWithCovariance * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__PoseWithCovariance * geometry_msgs__msg__PoseWithCovariance__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseWithCovariance__destroy(geometry_msgs__msg__PoseWithCovariance * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__PoseWithCovariance__Sequence__init(
  geometry_msgs__msg__PoseWithCovariance__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseWithCovariance__Sequence__fini(
  geometry_msgs__msg__PoseWithCovariance__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__POSEWITHCOVARIANCE_H_
