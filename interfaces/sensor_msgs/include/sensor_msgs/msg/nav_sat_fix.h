// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/NavSatFix message type

#ifndef SENSOR_MSGS__MSG__NAVSATFIX_H_
#define SENSOR_MSGS__MSG__NAVSATFIX_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "sensor_msgs/msg/nav_sat_status.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  sensor_msgs__msg__NavSatFix__COVARIANCE_TYPE_UNKNOWN = 0,
  sensor_msgs__msg__NavSatFix__COVARIANCE_TYPE_APPROXIMATED = 1,
  sensor_msgs__msg__NavSatFix__COVARIANCE_TYPE_DIAGONAL_KNOWN = 2,
  sensor_msgs__msg__NavSatFix__COVARIANCE_TYPE_KNOWN = 3
}};

typedef struct sensor_msgs__msg__NavSatFix
{
  std_msgs__msg__Header header;
  sensor_msgs__msg__NavSatStatus status;
  double latitude;
  double longitude;
  double altitude;
  double position_covariance[9];
  uint8_t position_covariance_type;
} sensor_msgs__msg__NavSatFix;

typedef struct sensor_msgs__msg__NavSatFix__Sequence
{
  sensor_msgs__msg__NavSatFix * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__NavSatFix__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__NavSatFix__init(sensor_msgs__msg__NavSatFix * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__NavSatFix__fini(sensor_msgs__msg__NavSatFix * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__NavSatFix * sensor_msgs__msg__NavSatFix__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__NavSatFix__destroy(sensor_msgs__msg__NavSatFix * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__NavSatFix__Sequence__init(
  sensor_msgs__msg__NavSatFix__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__NavSatFix__Sequence__fini(
  sensor_msgs__msg__NavSatFix__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__NAVSATFIX_H_
