// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/NavSatStatus message type

#ifndef SENSOR_MSGS__MSG__NAVSATSTATUS_H_
#define SENSOR_MSGS__MSG__NAVSATSTATUS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

enum {
  sensor_msgs__msg__NavSatStatus__STATUS_NO_FIX = -1,
  sensor_msgs__msg__NavSatStatus__STATUS_FIX = 0,
  sensor_msgs__msg__NavSatStatus__STATUS_SBAS_FIX = 1,
  sensor_msgs__msg__NavSatStatus__STATUS_GBAS_FIX = 2,
  sensor_msgs__msg__NavSatStatus__SERVICE_GPS = 1,
  sensor_msgs__msg__NavSatStatus__SERVICE_GLONASS = 2,
  sensor_msgs__msg__NavSatStatus__SERVICE_COMPASS = 4,
  sensor_msgs__msg__NavSatStatus__SERVICE_GALILEO = 8
}};

typedef struct sensor_msgs__msg__NavSatStatus
{
  int8_t status;
  uint16_t service;
} sensor_msgs__msg__NavSatStatus;

typedef struct sensor_msgs__msg__NavSatStatus__Sequence
{
  sensor_msgs__msg__NavSatStatus * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__NavSatStatus__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__NavSatStatus__init(sensor_msgs__msg__NavSatStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__NavSatStatus__fini(sensor_msgs__msg__NavSatStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__NavSatStatus * sensor_msgs__msg__NavSatStatus__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__NavSatStatus__destroy(sensor_msgs__msg__NavSatStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__NavSatStatus__Sequence__init(
  sensor_msgs__msg__NavSatStatus__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__NavSatStatus__Sequence__fini(
  sensor_msgs__msg__NavSatStatus__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__NAVSATSTATUS_H_
