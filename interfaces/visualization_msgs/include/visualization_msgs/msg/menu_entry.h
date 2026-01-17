// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// visualization_msgs/msg/MenuEntry type

#ifndef VISUALIZATION_MSGS__MSG__MENUENTRY_H_
#define VISUALIZATION_MSGS__MSG__MENUENTRY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "visualization_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define VISUALIZATION_MSGS__MSG__MenuEntry_FEEDBACK 0
#define VISUALIZATION_MSGS__MSG__MenuEntry_ROSRUN 1
#define VISUALIZATION_MSGS__MSG__MenuEntry_ROSLAUNCH 2

typedef struct visualization_msgs__msg__MenuEntry
{
  uint32_t id;
  uint32_t parent_id;
  rosidl_runtime_c__String title;
  rosidl_runtime_c__String command;
  uint8_t command_type;
} visualization_msgs__msg__MenuEntry;

typedef struct visualization_msgs__msg__MenuEntry__Sequence
{
  visualization_msgs__msg__MenuEntry * data;
  size_t size;
  size_t capacity;
} visualization_msgs__msg__MenuEntry__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__MenuEntry__init(visualization_msgs__msg__MenuEntry * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MenuEntry__fini(visualization_msgs__msg__MenuEntry * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
visualization_msgs__msg__MenuEntry * visualization_msgs__msg__MenuEntry__create(void);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MenuEntry__destroy(visualization_msgs__msg__MenuEntry * msg);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
bool visualization_msgs__msg__MenuEntry__Sequence__init(
  visualization_msgs__msg__MenuEntry__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_visualization_msgs
void visualization_msgs__msg__MenuEntry__Sequence__fini(
  visualization_msgs__msg__MenuEntry__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // VISUALIZATION_MSGS__MSG__MENUENTRY_H_
