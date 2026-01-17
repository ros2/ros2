// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/TimeReference message type

#ifndef SENSOR_MSGS__MSG__TIMEREFERENCE_H_
#define SENSOR_MSGS__MSG__TIMEREFERENCE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "builtin_interfaces/msg/time.h"
#include "rosidl_runtime_c/string.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__TimeReference
{
  std_msgs__msg__Header header;
  builtin_interfaces__msg__Time time_ref;
  rosidl_runtime_c__String source;
} sensor_msgs__msg__TimeReference;

typedef struct sensor_msgs__msg__TimeReference__Sequence
{
  sensor_msgs__msg__TimeReference * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__TimeReference__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__TimeReference__init(sensor_msgs__msg__TimeReference * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__TimeReference__fini(sensor_msgs__msg__TimeReference * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__TimeReference * sensor_msgs__msg__TimeReference__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__TimeReference__destroy(sensor_msgs__msg__TimeReference * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__TimeReference__Sequence__init(
  sensor_msgs__msg__TimeReference__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__TimeReference__Sequence__fini(
  sensor_msgs__msg__TimeReference__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__TIMEREFERENCE_H_
