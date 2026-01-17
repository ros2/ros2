// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/JointState message type

#ifndef SENSOR_MSGS__MSG__JOINTSTATE_H_
#define SENSOR_MSGS__MSG__JOINTSTATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__JointState
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String__Sequence name;
  rosidl_runtime_c__double__Sequence position;
  rosidl_runtime_c__double__Sequence velocity;
  rosidl_runtime_c__double__Sequence effort;
} sensor_msgs__msg__JointState;

typedef struct sensor_msgs__msg__JointState__Sequence
{
  sensor_msgs__msg__JointState * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__JointState__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__JointState__init(sensor_msgs__msg__JointState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JointState__fini(sensor_msgs__msg__JointState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__JointState * sensor_msgs__msg__JointState__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JointState__destroy(sensor_msgs__msg__JointState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__JointState__Sequence__init(
  sensor_msgs__msg__JointState__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JointState__Sequence__fini(
  sensor_msgs__msg__JointState__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__JOINTSTATE_H_
