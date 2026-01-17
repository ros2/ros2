// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/MarkerArray type

#ifndef VISUALIZATION_MSGS__MSG__MARKERARRAY_H_
#define VISUALIZATION_MSGS__MSG__MARKERARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "visualization_msgs/msg/marker.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct visualization_msgs__msg__MarkerArray
{
  visualization_msgs__msg__Marker__Sequence markers;
} visualization_msgs__msg__MarkerArray;

typedef struct visualization_msgs__msg__MarkerArray__Sequence
{
  visualization_msgs__msg__MarkerArray * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__MarkerArray__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__MarkerArray__init(visualization_msgs__msg__MarkerArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MarkerArray__fini(visualization_msgs__msg__MarkerArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__MarkerArray * visualization_msgs__msg__MarkerArray__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MarkerArray__destroy(visualization_msgs__msg__MarkerArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__MarkerArray__Sequence__init(
  visualization_msgs__msg__MarkerArray__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MarkerArray__Sequence__fini(
  visualization_msgs__msg__MarkerArray__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__MARKERARRAY_H_
