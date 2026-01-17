// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/PoseStamped message type

#ifndef GEOMETRY_MSGS__MSG__POSESTAMPED_H_
#define GEOMETRY_MSGS__MSG__POSESTAMPED_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "geometry_msgs/msg/pose.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__PoseStamped
{
  std_msgs__msg__Header header;

  geometry_msgs__msg__Pose pose;
} geometry_msgs__msg__PoseStamped;

typedef struct geometry_msgs__msg__PoseStamped__Sequence
{
  geometry_msgs__msg__PoseStamped * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__PoseStamped__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__PoseStamped__init(geometry_msgs__msg__PoseStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseStamped__fini(geometry_msgs__msg__PoseStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__PoseStamped * geometry_msgs__msg__PoseStamped__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseStamped__destroy(geometry_msgs__msg__PoseStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__PoseStamped__Sequence__init(
  geometry_msgs__msg__PoseStamped__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__PoseStamped__Sequence__fini(
  geometry_msgs__msg__PoseStamped__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__POSESTAMPED_H_
