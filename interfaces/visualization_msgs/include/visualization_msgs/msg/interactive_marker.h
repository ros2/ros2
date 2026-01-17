// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarker type

#ifndef VISUALIZATION_MSGS__MSG__INTERACTIVEMARKER_H_
#define VISUALIZATION_MSGS__MSG__INTERACTIVEMARKER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "rosidl_runtime_c/string.h"
#include "geometry_msgs/msg/pose.h"
#include "visualization_msgs/msg/menu_entry.h"
#include "visualization_msgs/msg/interactive_marker_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct visualization_msgs__msg__InteractiveMarker
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__Pose pose;
  rosidl_runtime_c__String name;
  rosidl_runtime_c__String description;
  float scale;
  visualization_msgs__msg__MenuEntry__Sequence menu_entries;
  visualization_msgs__msg__InteractiveMarkerControl__Sequence controls;
} visualization_msgs__msg__InteractiveMarker;

typedef struct visualization_msgs__msg__InteractiveMarker__Sequence
{
  visualization_msgs__msg__InteractiveMarker * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__InteractiveMarker__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarker__init(visualization_msgs__msg__InteractiveMarker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarker__fini(visualization_msgs__msg__InteractiveMarker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__InteractiveMarker * visualization_msgs__msg__InteractiveMarker__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarker__destroy(visualization_msgs__msg__InteractiveMarker * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarker__Sequence__init(
  visualization_msgs__msg__InteractiveMarker__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarker__Sequence__fini(
  visualization_msgs__msg__InteractiveMarker__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__INTERACTIVEMARKER_H_
