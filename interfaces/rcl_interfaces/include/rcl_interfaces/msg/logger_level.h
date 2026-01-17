// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/LoggerLevel message type

#ifndef RCL_INTERFACES__MSG__LOGGER_LEVEL_H_
#define RCL_INTERFACES__MSG__LOGGER_LEVEL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rosidl_runtime_c/string.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// Logger level constants
enum {
  rcl_interfaces__msg__LoggerLevel__UNSET = 0,
  rcl_interfaces__msg__LoggerLevel__DEBUG = 10,
  rcl_interfaces__msg__LoggerLevel__INFO = 20,
  rcl_interfaces__msg__LoggerLevel__WARN = 30,
  rcl_interfaces__msg__LoggerLevel__ERROR = 40,
  rcl_interfaces__msg__LoggerLevel__FATAL = 50
};

typedef struct rcl_interfaces__msg__LoggerLevel
{
  rosidl_runtime_c__String name;
  uint32_t level;
} rcl_interfaces__msg__LoggerLevel;

typedef struct rcl_interfaces__msg__LoggerLevel__Sequence
{
  rcl_interfaces__msg__LoggerLevel * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__LoggerLevel__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__LoggerLevel__init(rcl_interfaces__msg__LoggerLevel * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__LoggerLevel__fini(rcl_interfaces__msg__LoggerLevel * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__LoggerLevel * rcl_interfaces__msg__LoggerLevel__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__LoggerLevel__destroy(rcl_interfaces__msg__LoggerLevel * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__LoggerLevel__Sequence__init(
  rcl_interfaces__msg__LoggerLevel__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__LoggerLevel__Sequence__fini(
  rcl_interfaces__msg__LoggerLevel__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__LOGGER_LEVEL_H_
