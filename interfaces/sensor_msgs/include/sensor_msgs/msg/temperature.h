// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/Temperature message type

#ifndef SENSOR_MSGS__MSG__TEMPERATURE_H_
#define SENSOR_MSGS__MSG__TEMPERATURE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__Temperature
{
  std_msgs__msg__Header header;
  double temperature;
  double variance;
} sensor_msgs__msg__Temperature;

typedef struct sensor_msgs__msg__Temperature__Sequence
{
  sensor_msgs__msg__Temperature * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__Temperature__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Temperature__init(sensor_msgs__msg__Temperature * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Temperature__fini(sensor_msgs__msg__Temperature * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__Temperature * sensor_msgs__msg__Temperature__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Temperature__destroy(sensor_msgs__msg__Temperature * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Temperature__Sequence__init(
  sensor_msgs__msg__Temperature__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Temperature__Sequence__fini(
  sensor_msgs__msg__Temperature__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__TEMPERATURE_H_
