// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/MeshTriangle type

#ifndef SHAPE_MSGS__MSG__MESHTRIANGLE_H_
#define SHAPE_MSGS__MSG__MESHTRIANGLE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "shape_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct shape_msgs__msg__MeshTriangle
{
  uint32_t vertex_indices[3];
} shape_msgs__msg__MeshTriangle;

typedef struct shape_msgs__msg__MeshTriangle__Sequence
{
  shape_msgs__msg__MeshTriangle * data;
  size_t size;
  size_t capacity;
} shape_msgs__msg__MeshTriangle__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__MeshTriangle__init(shape_msgs__msg__MeshTriangle * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__MeshTriangle__fini(shape_msgs__msg__MeshTriangle * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
shape_msgs__msg__MeshTriangle * shape_msgs__msg__MeshTriangle__create(void);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__MeshTriangle__destroy(shape_msgs__msg__MeshTriangle * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__MeshTriangle__Sequence__init(
  shape_msgs__msg__MeshTriangle__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__MeshTriangle__Sequence__fini(
  shape_msgs__msg__MeshTriangle__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SHAPE_MSGS__MSG__MESHTRIANGLE_H_
