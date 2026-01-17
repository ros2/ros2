// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerFeedback type

#ifndef VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERFEEDBACK_H_
#define VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERFEEDBACK_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "rosidl_runtime_c/string.h"
#include "geometry_msgs/msg/pose.h"
#include "geometry_msgs/msg/point.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerFeedback_KEEP_ALIVE 0
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerFeedback_POSE_UPDATE 1
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerFeedback_MENU_SELECT 2
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerFeedback_BUTTON_CLICK 3
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerFeedback_MOUSE_DOWN 4
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerFeedback_MOUSE_UP 5

typedef struct visualization_msgs__msg__InteractiveMarkerFeedback
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String client_id;
  rosidl_runtime_c__String marker_name;
  rosidl_runtime_c__String control_name;
  uint8_t event_type;
  geometry_msgs__msg__Pose pose;
  uint32_t menu_entry_id;
  geometry_msgs__msg__Point mouse_point;
  bool mouse_point_valid;
} visualization_msgs__msg__InteractiveMarkerFeedback;

typedef struct visualization_msgs__msg__InteractiveMarkerFeedback__Sequence
{
  visualization_msgs__msg__InteractiveMarkerFeedback * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__InteractiveMarkerFeedback__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerFeedback__init(visualization_msgs__msg__InteractiveMarkerFeedback * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerFeedback__fini(visualization_msgs__msg__InteractiveMarkerFeedback * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__InteractiveMarkerFeedback * visualization_msgs__msg__InteractiveMarkerFeedback__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerFeedback__destroy(visualization_msgs__msg__InteractiveMarkerFeedback * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerFeedback__Sequence__init(
  visualization_msgs__msg__InteractiveMarkerFeedback__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerFeedback__Sequence__fini(
  visualization_msgs__msg__InteractiveMarkerFeedback__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERFEEDBACK_H_
