// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/UVCoordinate type

#ifndef VISUALIZATION_MSGS__MSG__UVCOORDINATE_H_
#define VISUALIZATION_MSGS__MSG__UVCOORDINATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct visualization_msgs__msg__UVCoordinate
{
  float u;
  float v;
} visualization_msgs__msg__UVCoordinate;

typedef struct visualization_msgs__msg__UVCoordinate__Sequence
{
  visualization_msgs__msg__UVCoordinate * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__UVCoordinate__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__UVCoordinate__init(visualization_msgs__msg__UVCoordinate * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__UVCoordinate__fini(visualization_msgs__msg__UVCoordinate * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__UVCoordinate * visualization_msgs__msg__UVCoordinate__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__UVCoordinate__destroy(visualization_msgs__msg__UVCoordinate * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__UVCoordinate__Sequence__init(
  visualization_msgs__msg__UVCoordinate__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__UVCoordinate__Sequence__fini(
  visualization_msgs__msg__UVCoordinate__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__UVCOORDINATE_H_
