// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/Imu message type

#ifndef SENSOR_MSGS__MSG__IMU_H_
#define SENSOR_MSGS__MSG__IMU_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/quaternion.h"
#include "geometry_msgs/msg/vector3.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__Imu
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__Quaternion orientation;
  double orientation_covariance[9];
  geometry_msgs__msg__Vector3 angular_velocity;
  double angular_velocity_covariance[9];
  geometry_msgs__msg__Vector3 linear_acceleration;
  double linear_acceleration_covariance[9];
} sensor_msgs__msg__Imu;

typedef struct sensor_msgs__msg__Imu__Sequence
{
  sensor_msgs__msg__Imu * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__Imu__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Imu__init(sensor_msgs__msg__Imu * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Imu__fini(sensor_msgs__msg__Imu * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__Imu * sensor_msgs__msg__Imu__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Imu__destroy(sensor_msgs__msg__Imu * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Imu__Sequence__init(
  sensor_msgs__msg__Imu__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Imu__Sequence__fini(
  sensor_msgs__msg__Imu__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__IMU_H_
