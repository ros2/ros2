// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/MultiDOFJointTrajectoryPoint type

#ifndef TRAJECTORY_MSGS__MSG__MULTIDOFJOINTTRAJECTORYPOINT_H_
#define TRAJECTORY_MSGS__MSG__MULTIDOFJOINTTRAJECTORYPOINT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "trajectory_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/transform.h"
#include "geometry_msgs/msg/twist.h"
#include "builtin_interfaces/msg/duration.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct trajectory_msgs__msg__MultiDOFJointTrajectoryPoint
{
  geometry_msgs__msg__Transform__Sequence transforms;
  geometry_msgs__msg__Twist__Sequence velocities;
  geometry_msgs__msg__Twist__Sequence accelerations;
  builtin_interfaces__msg__Duration time_from_start;
} trajectory_msgs__msg__MultiDOFJointTrajectoryPoint;

typedef struct trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence
{
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * data;
  size_t size;
  size_t capacity;
} trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__init(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__fini(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__create(void);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__destroy(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__init(
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__fini(
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TRAJECTORY_MSGS__MSG__MULTIDOFJOINTTRAJECTORYPOINT_H_
