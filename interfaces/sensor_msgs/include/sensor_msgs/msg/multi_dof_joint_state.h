// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/MultiDOFJointState message type

#ifndef SENSOR_MSGS__MSG__MULTIDOFJOINTSTATE_H_
#define SENSOR_MSGS__MSG__MULTIDOFJOINTSTATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/transform.h"
#include "geometry_msgs/msg/twist.h"
#include "geometry_msgs/msg/wrench.h"
#include "rosidl_runtime_c/string.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__MultiDOFJointState
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String__Sequence joint_names;
  geometry_msgs__msg__Transform__Sequence transforms;
  geometry_msgs__msg__Twist__Sequence twist;
  geometry_msgs__msg__Wrench__Sequence wrench;
} sensor_msgs__msg__MultiDOFJointState;

typedef struct sensor_msgs__msg__MultiDOFJointState__Sequence
{
  sensor_msgs__msg__MultiDOFJointState * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__MultiDOFJointState__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__MultiDOFJointState__init(sensor_msgs__msg__MultiDOFJointState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MultiDOFJointState__fini(sensor_msgs__msg__MultiDOFJointState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__MultiDOFJointState * sensor_msgs__msg__MultiDOFJointState__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MultiDOFJointState__destroy(sensor_msgs__msg__MultiDOFJointState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__MultiDOFJointState__Sequence__init(
  sensor_msgs__msg__MultiDOFJointState__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MultiDOFJointState__Sequence__fini(
  sensor_msgs__msg__MultiDOFJointState__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__MULTIDOFJOINTSTATE_H_
