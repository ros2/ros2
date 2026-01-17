// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/Odometry message type

#ifndef NAV_MSGS__MSG__ODOMETRY_H_
#define NAV_MSGS__MSG__ODOMETRY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "rosidl_runtime_c/string.h"
#include "geometry_msgs/msg/pose_with_covariance.h"
#include "geometry_msgs/msg/twist_with_covariance.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__msg__Odometry
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String child_frame_id;
  geometry_msgs__msg__PoseWithCovariance pose;
  geometry_msgs__msg__TwistWithCovariance twist;
} nav_msgs__msg__Odometry;

typedef struct nav_msgs__msg__Odometry__Sequence
{
  nav_msgs__msg__Odometry * data;
  size_t size;
  size_t capacity;
} nav_msgs__msg__Odometry__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__Odometry__init(nav_msgs__msg__Odometry * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__Odometry__fini(nav_msgs__msg__Odometry * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__msg__Odometry * nav_msgs__msg__Odometry__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__Odometry__destroy(nav_msgs__msg__Odometry * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__Odometry__Sequence__init(
  nav_msgs__msg__Odometry__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__Odometry__Sequence__fini(
  nav_msgs__msg__Odometry__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__MSG__ODOMETRY_H_
