// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/Log type

#ifndef RCL_INTERFACES__MSG__LOG_H_
#define RCL_INTERFACES__MSG__LOG_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "builtin_interfaces/msg/time.h"
#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RCL_INTERFACES__MSG__LOG__DEBUG ((uint8_t)10)
#define RCL_INTERFACES__MSG__LOG__INFO ((uint8_t)20)
#define RCL_INTERFACES__MSG__LOG__WARN ((uint8_t)30)
#define RCL_INTERFACES__MSG__LOG__ERROR ((uint8_t)40)
#define RCL_INTERFACES__MSG__LOG__FATAL ((uint8_t)50)

/// Log message
typedef struct rcl_interfaces__msg__Log
{
  builtin_interfaces__msg__Time stamp;
  uint8_t level;
  rosidl_runtime_c__String name;
  rosidl_runtime_c__String msg;
  rosidl_runtime_c__String file;
  rosidl_runtime_c__String function;
  uint32_t line;
} rcl_interfaces__msg__Log;

typedef struct rcl_interfaces__msg__Log__Sequence
{
  rcl_interfaces__msg__Log * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__Log__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__Log__init(rcl_interfaces__msg__Log * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__Log__fini(rcl_interfaces__msg__Log * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__Log * rcl_interfaces__msg__Log__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__Log__destroy(rcl_interfaces__msg__Log * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__Log__Sequence__init(
  rcl_interfaces__msg__Log__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__Log__Sequence__fini(
  rcl_interfaces__msg__Log__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__LOG_H_
