// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/Mesh type

#ifndef SHAPE_MSGS__MSG__MESH_H_
#define SHAPE_MSGS__MSG__MESH_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "shape_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/point.h"
#include "shape_msgs/msg/mesh_triangle.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shape_msgs__msg__Mesh
{
  geometry_msgs__msg__Point__Sequence vertices;
  shape_msgs__msg__MeshTriangle__Sequence triangles;
} shape_msgs__msg__Mesh;

typedef struct shape_msgs__msg__Mesh__Sequence
{
  shape_msgs__msg__Mesh * data;
  size_t size;
  size_t capacity;
} shape_msgs__msg__Mesh__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__Mesh__init(shape_msgs__msg__Mesh * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__Mesh__fini(shape_msgs__msg__Mesh * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
shape_msgs__msg__Mesh * shape_msgs__msg__Mesh__create(void);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__Mesh__destroy(shape_msgs__msg__Mesh * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__Mesh__Sequence__init(
  shape_msgs__msg__Mesh__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__Mesh__Sequence__fini(
  shape_msgs__msg__Mesh__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SHAPE_MSGS__MSG__MESH_H_
