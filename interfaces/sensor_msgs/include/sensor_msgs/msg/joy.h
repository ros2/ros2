// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/Joy message type

#ifndef SENSOR_MSGS__MSG__JOY_H_
#define SENSOR_MSGS__MSG__JOY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__Joy
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__float__Sequence axes;
  rosidl_runtime_c__int32__Sequence buttons;
} sensor_msgs__msg__Joy;

typedef struct sensor_msgs__msg__Joy__Sequence
{
  sensor_msgs__msg__Joy * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__Joy__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Joy__init(sensor_msgs__msg__Joy * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Joy__fini(sensor_msgs__msg__Joy * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__Joy * sensor_msgs__msg__Joy__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Joy__destroy(sensor_msgs__msg__Joy * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Joy__Sequence__init(
  sensor_msgs__msg__Joy__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Joy__Sequence__fini(
  sensor_msgs__msg__Joy__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__JOY_H_
