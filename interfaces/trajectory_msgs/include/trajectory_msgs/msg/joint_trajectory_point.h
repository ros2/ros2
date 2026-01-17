// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/JointTrajectoryPoint type

#ifndef TRAJECTORY_MSGS__MSG__JOINTTRAJECTORYPOINT_H_
#define TRAJECTORY_MSGS__MSG__JOINTTRAJECTORYPOINT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "trajectory_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "builtin_interfaces/msg/duration.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct trajectory_msgs__msg__JointTrajectoryPoint
{
  rosidl_runtime_c__double__Sequence positions;
  rosidl_runtime_c__double__Sequence velocities;
  rosidl_runtime_c__double__Sequence accelerations;
  rosidl_runtime_c__double__Sequence effort;
  builtin_interfaces__msg__Duration time_from_start;
} trajectory_msgs__msg__JointTrajectoryPoint;

typedef struct trajectory_msgs__msg__JointTrajectoryPoint__Sequence
{
  trajectory_msgs__msg__JointTrajectoryPoint * data;
  size_t size;
  size_t capacity;
} trajectory_msgs__msg__JointTrajectoryPoint__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool trajectory_msgs__msg__JointTrajectoryPoint__init(trajectory_msgs__msg__JointTrajectoryPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__JointTrajectoryPoint__fini(trajectory_msgs__msg__JointTrajectoryPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
trajectory_msgs__msg__JointTrajectoryPoint * trajectory_msgs__msg__JointTrajectoryPoint__create(void);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__JointTrajectoryPoint__destroy(trajectory_msgs__msg__JointTrajectoryPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool trajectory_msgs__msg__JointTrajectoryPoint__Sequence__init(
  trajectory_msgs__msg__JointTrajectoryPoint__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__JointTrajectoryPoint__Sequence__fini(
  trajectory_msgs__msg__JointTrajectoryPoint__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TRAJECTORY_MSGS__MSG__JOINTTRAJECTORYPOINT_H_
