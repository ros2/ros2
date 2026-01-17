// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/Plane type

#ifndef SHAPE_MSGS__MSG__PLANE_H_
#define SHAPE_MSGS__MSG__PLANE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "shape_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct shape_msgs__msg__Plane
{
  double coef[4];
} shape_msgs__msg__Plane;

typedef struct shape_msgs__msg__Plane__Sequence
{
  shape_msgs__msg__Plane * data;
  size_t size;
  size_t capacity;
} shape_msgs__msg__Plane__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__Plane__init(shape_msgs__msg__Plane * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__Plane__fini(shape_msgs__msg__Plane * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
shape_msgs__msg__Plane * shape_msgs__msg__Plane__create(void);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__Plane__destroy(shape_msgs__msg__Plane * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__Plane__Sequence__init(
  shape_msgs__msg__Plane__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__Plane__Sequence__fini(
  shape_msgs__msg__Plane__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SHAPE_MSGS__MSG__PLANE_H_
