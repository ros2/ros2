// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/CameraInfo message type

#ifndef SENSOR_MSGS__MSG__CAMERAINFO_H_
#define SENSOR_MSGS__MSG__CAMERAINFO_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"
#include "sensor_msgs/msg/region_of_interest.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__CameraInfo
{
  std_msgs__msg__Header header;
  uint32_t height;
  uint32_t width;
  rosidl_runtime_c__String distortion_model;
  rosidl_runtime_c__double__Sequence d;
  double k[9];
  double r[9];
  double p[12];
  uint32_t binning_x;
  uint32_t binning_y;
  sensor_msgs__msg__RegionOfInterest roi;
} sensor_msgs__msg__CameraInfo;

typedef struct sensor_msgs__msg__CameraInfo__Sequence
{
  sensor_msgs__msg__CameraInfo * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__CameraInfo__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__CameraInfo__init(sensor_msgs__msg__CameraInfo * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__CameraInfo__fini(sensor_msgs__msg__CameraInfo * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__CameraInfo * sensor_msgs__msg__CameraInfo__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__CameraInfo__destroy(sensor_msgs__msg__CameraInfo * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__CameraInfo__Sequence__init(
  sensor_msgs__msg__CameraInfo__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__CameraInfo__Sequence__fini(
  sensor_msgs__msg__CameraInfo__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__CAMERAINFO_H_
