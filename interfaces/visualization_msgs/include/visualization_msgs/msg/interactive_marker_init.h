// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/InteractiveMarkerInit type

#ifndef VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERINIT_H_
#define VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERINIT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"
#include "visualization_msgs/msg/interactive_marker.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct visualization_msgs__msg__InteractiveMarkerInit
{
  rosidl_runtime_c__String server_id;
  uint64_t seq_num;
  visualization_msgs__msg__InteractiveMarker__Sequence markers;
} visualization_msgs__msg__InteractiveMarkerInit;

typedef struct visualization_msgs__msg__InteractiveMarkerInit__Sequence
{
  visualization_msgs__msg__InteractiveMarkerInit * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__InteractiveMarkerInit__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerInit__init(visualization_msgs__msg__InteractiveMarkerInit * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerInit__fini(visualization_msgs__msg__InteractiveMarkerInit * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__InteractiveMarkerInit * visualization_msgs__msg__InteractiveMarkerInit__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerInit__destroy(visualization_msgs__msg__InteractiveMarkerInit * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__InteractiveMarkerInit__Sequence__init(
  visualization_msgs__msg__InteractiveMarkerInit__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__InteractiveMarkerInit__Sequence__fini(
  visualization_msgs__msg__InteractiveMarkerInit__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__INTERACTIVEMARKERINIT_H_
