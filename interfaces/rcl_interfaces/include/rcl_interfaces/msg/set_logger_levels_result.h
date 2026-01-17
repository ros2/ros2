// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/SetLoggerLevelsResult message type

#ifndef RCL_INTERFACES__MSG__SET_LOGGER_LEVELS_RESULT_H_
#define RCL_INTERFACES__MSG__SET_LOGGER_LEVELS_RESULT_H_

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

typedef struct rcl_interfaces__msg__SetLoggerLevelsResult
{
  bool successful;
  rosidl_runtime_c__String reason;
} rcl_interfaces__msg__SetLoggerLevelsResult;

typedef struct rcl_interfaces__msg__SetLoggerLevelsResult__Sequence
{
  rcl_interfaces__msg__SetLoggerLevelsResult * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__SetLoggerLevelsResult__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__SetLoggerLevelsResult__init(rcl_interfaces__msg__SetLoggerLevelsResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__SetLoggerLevelsResult__fini(rcl_interfaces__msg__SetLoggerLevelsResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__SetLoggerLevelsResult * rcl_interfaces__msg__SetLoggerLevelsResult__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__SetLoggerLevelsResult__destroy(rcl_interfaces__msg__SetLoggerLevelsResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__SetLoggerLevelsResult__Sequence__init(
  rcl_interfaces__msg__SetLoggerLevelsResult__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__SetLoggerLevelsResult__Sequence__fini(
  rcl_interfaces__msg__SetLoggerLevelsResult__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__SET_LOGGER_LEVELS_RESULT_H_
