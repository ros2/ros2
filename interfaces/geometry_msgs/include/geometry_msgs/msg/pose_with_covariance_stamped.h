// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/PoseWithCovarianceStamped message type

#ifndef GEOMETRY_MSGS__MSG__POSEWITHCOVARIANCESTAMPED_H_
#define GEOMETRY_MSGS__MSG__POSEWITHCOVARIANCESTAMPED_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "geometry_msgs/msg/pose_with_covariance.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__PoseWithCovarianceStamped
{
  std_msgs__msg__Header header;

  geometry_msgs__msg__PoseWithCovariance pose_with_covariance;
} geometry_msgs__msg__PoseWithCovarianceStamped;

typedef struct geometry_msgs__msg__PoseWithCovarianceStamped__Sequence
{
  geometry_msgs__msg__PoseWithCovarianceStamped * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__PoseWithCovarianceStamped__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__PoseWithCovarianceStamped__init(geometry_msgs__msg__PoseWithCovarianceStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseWithCovarianceStamped__fini(geometry_msgs__msg__PoseWithCovarianceStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__PoseWithCovarianceStamped * geometry_msgs__msg__PoseWithCovarianceStamped__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseWithCovarianceStamped__destroy(geometry_msgs__msg__PoseWithCovarianceStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__PoseWithCovarianceStamped__Sequence__init(
  geometry_msgs__msg__PoseWithCovarianceStamped__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseWithCovarianceStamped__Sequence__fini(
  geometry_msgs__msg__PoseWithCovarianceStamped__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__POSEWITHCOVARIANCESTAMPED_H_
