// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/Range message type

#ifndef SENSOR_MSGS__MSG__RANGE_H_
#define SENSOR_MSGS__MSG__RANGE_H_

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

enum {
  sensor_msgs__msg__Range__ULTRASOUND = 0,
  sensor_msgs__msg__Range__INFRARED = 1
}};

typedef struct sensor_msgs__msg__Range
{
  std_msgs__msg__Header header;
  uint8_t radiation_type;
  float field_of_view;
  float min_range;
  float max_range;
  float range;
} sensor_msgs__msg__Range;

typedef struct sensor_msgs__msg__Range__Sequence
{
  sensor_msgs__msg__Range * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__Range__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Range__init(sensor_msgs__msg__Range * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Range__fini(sensor_msgs__msg__Range * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__Range * sensor_msgs__msg__Range__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Range__destroy(sensor_msgs__msg__Range * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Range__Sequence__init(
  sensor_msgs__msg__Range__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Range__Sequence__fini(
  sensor_msgs__msg__Range__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__RANGE_H_
