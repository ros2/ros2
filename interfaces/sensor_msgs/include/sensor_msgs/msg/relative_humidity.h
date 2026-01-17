// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/RelativeHumidity message type

#ifndef SENSOR_MSGS__MSG__RELATIVEHUMIDITY_H_
#define SENSOR_MSGS__MSG__RELATIVEHUMIDITY_H_

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

typedef struct sensor_msgs__msg__RelativeHumidity
{
  std_msgs__msg__Header header;
  double relative_humidity;
  double variance;
} sensor_msgs__msg__RelativeHumidity;

typedef struct sensor_msgs__msg__RelativeHumidity__Sequence
{
  sensor_msgs__msg__RelativeHumidity * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__RelativeHumidity__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__RelativeHumidity__init(sensor_msgs__msg__RelativeHumidity * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__RelativeHumidity__fini(sensor_msgs__msg__RelativeHumidity * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__RelativeHumidity * sensor_msgs__msg__RelativeHumidity__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__RelativeHumidity__destroy(sensor_msgs__msg__RelativeHumidity * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__RelativeHumidity__Sequence__init(
  sensor_msgs__msg__RelativeHumidity__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__RelativeHumidity__Sequence__fini(
  sensor_msgs__msg__RelativeHumidity__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__RELATIVEHUMIDITY_H_
