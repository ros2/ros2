// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/MultiEchoLaserScan message type

#ifndef SENSOR_MSGS__MSG__MULTIECHOLASERSCAN_H_
#define SENSOR_MSGS__MSG__MULTIECHOLASERSCAN_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "sensor_msgs/msg/laser_echo.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__MultiEchoLaserScan
{
  std_msgs__msg__Header header;
  float angle_min;
  float angle_max;
  float angle_increment;
  float time_increment;
  float scan_time;
  float range_min;
  float range_max;
  sensor_msgs__msg__LaserEcho__Sequence ranges;
  sensor_msgs__msg__LaserEcho__Sequence intensities;
} sensor_msgs__msg__MultiEchoLaserScan;

typedef struct sensor_msgs__msg__MultiEchoLaserScan__Sequence
{
  sensor_msgs__msg__MultiEchoLaserScan * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__MultiEchoLaserScan__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__MultiEchoLaserScan__init(sensor_msgs__msg__MultiEchoLaserScan * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MultiEchoLaserScan__fini(sensor_msgs__msg__MultiEchoLaserScan * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__MultiEchoLaserScan * sensor_msgs__msg__MultiEchoLaserScan__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MultiEchoLaserScan__destroy(sensor_msgs__msg__MultiEchoLaserScan * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__MultiEchoLaserScan__Sequence__init(
  sensor_msgs__msg__MultiEchoLaserScan__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MultiEchoLaserScan__Sequence__fini(
  sensor_msgs__msg__MultiEchoLaserScan__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__MULTIECHOLASERSCAN_H_
