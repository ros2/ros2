// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/Path message type

#ifndef NAV_MSGS__MSG__PATH_H_
#define NAV_MSGS__MSG__PATH_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "geometry_msgs/msg/pose_stamped.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__msg__Path
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__PoseStamped__Sequence poses;
} nav_msgs__msg__Path;

typedef struct nav_msgs__msg__Path__Sequence
{
  nav_msgs__msg__Path * data;
  size_t size;
  size_t capacity;
} nav_msgs__msg__Path__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__Path__init(nav_msgs__msg__Path * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__Path__fini(nav_msgs__msg__Path * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__msg__Path * nav_msgs__msg__Path__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__Path__destroy(nav_msgs__msg__Path * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__Path__Sequence__init(
  nav_msgs__msg__Path__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__Path__Sequence__fini(
  nav_msgs__msg__Path__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__MSG__PATH_H_
