// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/LaserEcho message type

#ifndef SENSOR_MSGS__MSG__LASERECHO_H_
#define SENSOR_MSGS__MSG__LASERECHO_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__LaserEcho
{
  rosidl_runtime_c__float__Sequence echoes;
} sensor_msgs__msg__LaserEcho;

typedef struct sensor_msgs__msg__LaserEcho__Sequence
{
  sensor_msgs__msg__LaserEcho * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__LaserEcho__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__LaserEcho__init(sensor_msgs__msg__LaserEcho * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__LaserEcho__fini(sensor_msgs__msg__LaserEcho * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__LaserEcho * sensor_msgs__msg__LaserEcho__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__LaserEcho__destroy(sensor_msgs__msg__LaserEcho * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__LaserEcho__Sequence__init(
  sensor_msgs__msg__LaserEcho__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__LaserEcho__Sequence__fini(
  sensor_msgs__msg__LaserEcho__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__LASERECHO_H_
