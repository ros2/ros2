// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerPose type

#ifndef VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERPOSE_H_
#define VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERPOSE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "rosidl_runtime_c/string.h"
#include "geometry_msgs/msg/pose.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct visualization_msgs__msg__InteractiveMarkerPose
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__Pose pose;
  rosidl_runtime_c__String name;
} visualization_msgs__msg__InteractiveMarkerPose;

typedef struct visualization_msgs__msg__InteractiveMarkerPose__Sequence
{
  visualization_msgs__msg__InteractiveMarkerPose * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__InteractiveMarkerPose__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerPose__init(visualization_msgs__msg__InteractiveMarkerPose * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerPose__fini(visualization_msgs__msg__InteractiveMarkerPose * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__InteractiveMarkerPose * visualization_msgs__msg__InteractiveMarkerPose__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerPose__destroy(visualization_msgs__msg__InteractiveMarkerPose * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerPose__Sequence__init(
  visualization_msgs__msg__InteractiveMarkerPose__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerPose__Sequence__fini(
  visualization_msgs__msg__InteractiveMarkerPose__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERPOSE_H_
