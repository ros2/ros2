// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/MultiDOFJointTrajectory type

#ifndef TRAJECTORY_MSGS__MSG__MULTIDOFJOINTTRAJECTORY_H_
#define TRAJECTORY_MSGS__MSG__MULTIDOFJOINTTRAJECTORY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "trajectory_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "rosidl_runtime_c/string.h"
#include "trajectory_msgs/msg/multi_dof_joint_trajectory_point.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct trajectory_msgs__msg__MultiDOFJointTrajectory
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String__Sequence joint_names;
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence points;
} trajectory_msgs__msg__MultiDOFJointTrajectory;

typedef struct trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence
{
  trajectory_msgs__msg__MultiDOFJointTrajectory * data;
  size_t size;
  size_t capacity;
} trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool trajectory_msgs__msg__MultiDOFJointTrajectory__init(trajectory_msgs__msg__MultiDOFJointTrajectory * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__MultiDOFJointTrajectory__fini(trajectory_msgs__msg__MultiDOFJointTrajectory * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
trajectory_msgs__msg__MultiDOFJointTrajectory * trajectory_msgs__msg__MultiDOFJointTrajectory__create(void);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__MultiDOFJointTrajectory__destroy(trajectory_msgs__msg__MultiDOFJointTrajectory * msg);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
bool trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence__init(
  trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_trajectory_msgs
void trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence__fini(
  trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TRAJECTORY_MSGS__MSG__MULTIDOFJOINTTRAJECTORY_H_
