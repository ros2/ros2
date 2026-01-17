// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/RegionOfInterest message type

#ifndef SENSOR_MSGS__MSG__REGIONOFINTEREST_H_
#define SENSOR_MSGS__MSG__REGIONOFINTEREST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__RegionOfInterest
{
  uint32_t x_offset;
  uint32_t y_offset;
  uint32_t height;
  uint32_t width;
  bool do_rectify;
} sensor_msgs__msg__RegionOfInterest;

typedef struct sensor_msgs__msg__RegionOfInterest__Sequence
{
  sensor_msgs__msg__RegionOfInterest * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__RegionOfInterest__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__RegionOfInterest__init(sensor_msgs__msg__RegionOfInterest * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__RegionOfInterest__fini(sensor_msgs__msg__RegionOfInterest * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__RegionOfInterest * sensor_msgs__msg__RegionOfInterest__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__RegionOfInterest__destroy(sensor_msgs__msg__RegionOfInterest * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__RegionOfInterest__Sequence__init(
  sensor_msgs__msg__RegionOfInterest__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__RegionOfInterest__Sequence__fini(
  sensor_msgs__msg__RegionOfInterest__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__REGIONOFINTEREST_H_
