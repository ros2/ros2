// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerUpdate type

#ifndef VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERUPDATE_H_
#define VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERUPDATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"
#include "visualization_msgs/msg/interactive_marker.h"
#include "visualization_msgs/msg/interactive_marker_pose.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerUpdate_KEEP_ALIVE 0
#define VISUALIZATION_MSGS__MSG__InteractiveMarkerUpdate_UPDATE 1

typedef struct visualization_msgs__msg__InteractiveMarkerUpdate
{
  rosidl_runtime_c__String server_id;
  uint64_t seq_num;
  uint8_t type;
  visualization_msgs__msg__InteractiveMarker__Sequence markers;
  visualization_msgs__msg__InteractiveMarkerPose__Sequence poses;
  rosidl_runtime_c__String__Sequence erases;
} visualization_msgs__msg__InteractiveMarkerUpdate;

typedef struct visualization_msgs__msg__InteractiveMarkerUpdate__Sequence
{
  visualization_msgs__msg__InteractiveMarkerUpdate * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__InteractiveMarkerUpdate__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerUpdate__init(visualization_msgs__msg__InteractiveMarkerUpdate * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerUpdate__fini(visualization_msgs__msg__InteractiveMarkerUpdate * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__InteractiveMarkerUpdate * visualization_msgs__msg__InteractiveMarkerUpdate__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerUpdate__destroy(visualization_msgs__msg__InteractiveMarkerUpdate * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerUpdate__Sequence__init(
  visualization_msgs__msg__InteractiveMarkerUpdate__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerUpdate__Sequence__fini(
  visualization_msgs__msg__InteractiveMarkerUpdate__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERUPDATE_H_
