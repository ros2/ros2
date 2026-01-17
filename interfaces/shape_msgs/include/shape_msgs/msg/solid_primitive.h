// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/SolidPrimitive type

#ifndef SHAPE_MSGS__MSG__SOLIDPRIMITIVE_H_
#define SHAPE_MSGS__MSG__SOLIDPRIMITIVE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "shape_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "geometry_msgs/msg/polygon.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define SHAPE_MSGS__MSG__SolidPrimitive_BOX 1
#define SHAPE_MSGS__MSG__SolidPrimitive_SPHERE 2
#define SHAPE_MSGS__MSG__SolidPrimitive_CYLINDER 3
#define SHAPE_MSGS__MSG__SolidPrimitive_CONE 4
#define SHAPE_MSGS__MSG__SolidPrimitive_PRISM 5
#define SHAPE_MSGS__MSG__SolidPrimitive_BOX_X 0
#define SHAPE_MSGS__MSG__SolidPrimitive_BOX_Y 1
#define SHAPE_MSGS__MSG__SolidPrimitive_BOX_Z 2
#define SHAPE_MSGS__MSG__SolidPrimitive_SPHERE_RADIUS 0
#define SHAPE_MSGS__MSG__SolidPrimitive_CYLINDER_HEIGHT 0
#define SHAPE_MSGS__MSG__SolidPrimitive_CYLINDER_RADIUS 1
#define SHAPE_MSGS__MSG__SolidPrimitive_CONE_HEIGHT 0
#define SHAPE_MSGS__MSG__SolidPrimitive_CONE_RADIUS 1
#define SHAPE_MSGS__MSG__SolidPrimitive_PRISM_HEIGHT 0

typedef struct shape_msgs__msg__SolidPrimitive
{
  uint8_t type;
  rosidl_runtime_c__double__Sequence dimensions;
  geometry_msgs__msg__Polygon polygon;
} shape_msgs__msg__SolidPrimitive;

typedef struct shape_msgs__msg__SolidPrimitive__Sequence
{
  shape_msgs__msg__SolidPrimitive * data;
  size_t size;
  size_t capacity;
} shape_msgs__msg__SolidPrimitive__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__SolidPrimitive__init(shape_msgs__msg__SolidPrimitive * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__SolidPrimitive__fini(shape_msgs__msg__SolidPrimitive * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
shape_msgs__msg__SolidPrimitive * shape_msgs__msg__SolidPrimitive__create(void);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__SolidPrimitive__destroy(shape_msgs__msg__SolidPrimitive * msg);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
bool shape_msgs__msg__SolidPrimitive__Sequence__init(
  shape_msgs__msg__SolidPrimitive__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_shape_msgs
void shape_msgs__msg__SolidPrimitive__Sequence__fini(
  shape_msgs__msg__SolidPrimitive__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SHAPE_MSGS__MSG__SOLIDPRIMITIVE_H_
