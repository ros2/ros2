// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/CompressedImage message type

#ifndef SENSOR_MSGS__MSG__COMPRESSEDIMAGE_H_
#define SENSOR_MSGS__MSG__COMPRESSEDIMAGE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__CompressedImage
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String format;
  rosidl_runtime_c__uint8__Sequence data;
} sensor_msgs__msg__CompressedImage;

typedef struct sensor_msgs__msg__CompressedImage__Sequence
{
  sensor_msgs__msg__CompressedImage * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__CompressedImage__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__CompressedImage__init(sensor_msgs__msg__CompressedImage * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__CompressedImage__fini(sensor_msgs__msg__CompressedImage * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__CompressedImage * sensor_msgs__msg__CompressedImage__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__CompressedImage__destroy(sensor_msgs__msg__CompressedImage * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__CompressedImage__Sequence__init(
  sensor_msgs__msg__CompressedImage__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__CompressedImage__Sequence__fini(
  sensor_msgs__msg__CompressedImage__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__COMPRESSEDIMAGE_H_
