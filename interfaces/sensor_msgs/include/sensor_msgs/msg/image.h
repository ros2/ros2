// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/Image message type

#ifndef SENSOR_MSGS__MSG__IMAGE_H_
#define SENSOR_MSGS__MSG__IMAGE_H_

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

typedef struct sensor_msgs__msg__Image
{
  std_msgs__msg__Header header;
  uint32_t height;
  uint32_t width;
  rosidl_runtime_c__String encoding;
  uint8_t is_bigendian;
  uint32_t step;
  rosidl_runtime_c__uint8__Sequence data;
} sensor_msgs__msg__Image;

typedef struct sensor_msgs__msg__Image__Sequence
{
  sensor_msgs__msg__Image * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__Image__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Image__init(sensor_msgs__msg__Image * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Image__fini(sensor_msgs__msg__Image * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__Image * sensor_msgs__msg__Image__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Image__destroy(sensor_msgs__msg__Image * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__Image__Sequence__init(
  sensor_msgs__msg__Image__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__Image__Sequence__fini(
  sensor_msgs__msg__Image__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__IMAGE_H_
