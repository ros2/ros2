// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/MeshFile type

#ifndef VISUALIZATION_MSGS__MSG__MESHFILE_H_
#define VISUALIZATION_MSGS__MSG__MESHFILE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/primitives_sequence.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct visualization_msgs__msg__MeshFile
{
  rosidl_runtime_c__String filename;
  rosidl_runtime_c__uint8__Sequence data;
} visualization_msgs__msg__MeshFile;

typedef struct visualization_msgs__msg__MeshFile__Sequence
{
  visualization_msgs__msg__MeshFile * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__MeshFile__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__MeshFile__init(visualization_msgs__msg__MeshFile * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MeshFile__fini(visualization_msgs__msg__MeshFile * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__MeshFile * visualization_msgs__msg__MeshFile__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MeshFile__destroy(visualization_msgs__msg__MeshFile * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__MeshFile__Sequence__init(
  visualization_msgs__msg__MeshFile__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MeshFile__Sequence__fini(
  visualization_msgs__msg__MeshFile__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__MESHFILE_H_
