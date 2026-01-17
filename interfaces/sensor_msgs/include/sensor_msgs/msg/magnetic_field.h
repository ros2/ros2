// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/MagneticField message type

#ifndef SENSOR_MSGS__MSG__MAGNETICFIELD_H_
#define SENSOR_MSGS__MSG__MAGNETICFIELD_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/vector3.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__MagneticField
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__Vector3 magnetic_field;
  double magnetic_field_covariance[9];
} sensor_msgs__msg__MagneticField;

typedef struct sensor_msgs__msg__MagneticField__Sequence
{
  sensor_msgs__msg__MagneticField * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__MagneticField__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__MagneticField__init(sensor_msgs__msg__MagneticField * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MagneticField__fini(sensor_msgs__msg__MagneticField * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__MagneticField * sensor_msgs__msg__MagneticField__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MagneticField__destroy(sensor_msgs__msg__MagneticField * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__MagneticField__Sequence__init(
  sensor_msgs__msg__MagneticField__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__MagneticField__Sequence__fini(
  sensor_msgs__msg__MagneticField__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__MAGNETICFIELD_H_
