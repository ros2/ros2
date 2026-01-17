// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// geometry_msgs/msg/AccelWithCovarianceStamped message type

#ifndef GEOMETRY_MSGS__MSG__ACCELWITHCOVARIANCESTAMPED_H_
#define GEOMETRY_MSGS__MSG__ACCELWITHCOVARIANCESTAMPED_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "geometry_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "geometry_msgs/msg/accel_with_covariance.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct geometry_msgs__msg__AccelWithCovarianceStamped
{
  std_msgs__msg__Header header;

  geometry_msgs__msg__AccelWithCovariance accel_with_covariance;
} geometry_msgs__msg__AccelWithCovarianceStamped;

typedef struct geometry_msgs__msg__AccelWithCovarianceStamped__Sequence
{
  geometry_msgs__msg__AccelWithCovarianceStamped * data;
  size_t size;
  size_t capacity;
} geometry_msgs__msg__AccelWithCovarianceStamped__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__AccelWithCovarianceStamped__init(geometry_msgs__msg__AccelWithCovarianceStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__AccelWithCovarianceStamped__fini(geometry_msgs__msg__AccelWithCovarianceStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
geometry_msgs__msg__AccelWithCovarianceStamped * geometry_msgs__msg__AccelWithCovarianceStamped__create(void);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__AccelWithCovarianceStamped__destroy(geometry_msgs__msg__AccelWithCovarianceStamped * msg);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
bool geometry_msgs__msg__AccelWithCovarianceStamped__Sequence__init(
  geometry_msgs__msg__AccelWithCovarianceStamped__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_geometry_msgs
void geometry_msgs__msg__AccelWithCovarianceStamped__Sequence__fini(
  geometry_msgs__msg__AccelWithCovarianceStamped__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // GEOMETRY_MSGS__MSG__ACCELWITHCOVARIANCESTAMPED_H_
