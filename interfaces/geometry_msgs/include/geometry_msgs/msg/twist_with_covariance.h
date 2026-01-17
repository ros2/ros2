// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/TwistWithCovariance message type

#ifndef GEOMETRY_MSGS__MSG__TWISTWITHCOVARIANCE_H_
#define GEOMETRY_MSGS__MSG__TWISTWITHCOVARIANCE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/twist.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__TwistWithCovariance
{
  geometry_msgs__msg__Twist twist;
  double covariance[36];
} geometry_msgs__msg__TwistWithCovariance;

typedef struct geometry_msgs__msg__TwistWithCovariance__Sequence
{
  geometry_msgs__msg__TwistWithCovariance * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__TwistWithCovariance__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__TwistWithCovariance__init(geometry_msgs__msg__TwistWithCovariance * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__TwistWithCovariance__fini(geometry_msgs__msg__TwistWithCovariance * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__TwistWithCovariance * geometry_msgs__msg__TwistWithCovariance__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__TwistWithCovariance__destroy(geometry_msgs__msg__TwistWithCovariance * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__TwistWithCovariance__Sequence__init(
  geometry_msgs__msg__TwistWithCovariance__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__TwistWithCovariance__Sequence__fini(
  geometry_msgs__msg__TwistWithCovariance__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__TWISTWITHCOVARIANCE_H_
