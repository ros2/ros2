// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/FluidPressure message type

#ifndef SENSOR_MSGS__MSG__FLUIDPRESSURE_H_
#define SENSOR_MSGS__MSG__FLUIDPRESSURE_H_

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

typedef struct sensor_msgs__msg__FluidPressure
{
  std_msgs__msg__Header header;
  double fluid_pressure;
  double variance;
} sensor_msgs__msg__FluidPressure;

typedef struct sensor_msgs__msg__FluidPressure__Sequence
{
  sensor_msgs__msg__FluidPressure * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__FluidPressure__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__FluidPressure__init(sensor_msgs__msg__FluidPressure * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__FluidPressure__fini(sensor_msgs__msg__FluidPressure * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__FluidPressure * sensor_msgs__msg__FluidPressure__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__FluidPressure__destroy(sensor_msgs__msg__FluidPressure * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__FluidPressure__Sequence__init(
  sensor_msgs__msg__FluidPressure__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__FluidPressure__Sequence__fini(
  sensor_msgs__msg__FluidPressure__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__FLUIDPRESSURE_H_
