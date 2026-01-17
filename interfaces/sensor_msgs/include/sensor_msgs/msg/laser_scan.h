// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/LaserScan message type

#ifndef SENSOR_MSGS__MSG__LASERSCAN_H_
#define SENSOR_MSGS__MSG__LASERSCAN_H_

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

typedef struct sensor_msgs__msg__LaserScan
{
  std_msgs__msg__Header header;
  float angle_min;
  float angle_max;
  float angle_increment;
  float time_increment;
  float scan_time;
  float range_min;
  float range_max;
  rosidl_runtime_c__float__Sequence ranges;
  rosidl_runtime_c__float__Sequence intensities;
} sensor_msgs__msg__LaserScan;

typedef struct sensor_msgs__msg__LaserScan__Sequence
{
  sensor_msgs__msg__LaserScan * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__LaserScan__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__LaserScan__init(sensor_msgs__msg__LaserScan * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__LaserScan__fini(sensor_msgs__msg__LaserScan * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__LaserScan * sensor_msgs__msg__LaserScan__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__LaserScan__destroy(sensor_msgs__msg__LaserScan * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__LaserScan__Sequence__init(
  sensor_msgs__msg__LaserScan__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__LaserScan__Sequence__fini(
  sensor_msgs__msg__LaserScan__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__LASERSCAN_H_
