// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/SetLoggerLevels type

#ifndef RCL_INTERFACES__SRV__SETLOGGERLEVELS_H_
#define RCL_INTERFACES__SRV__SETLOGGERLEVELS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif



// Nested type for request
typedef struct rcl_interfaces__srv__SetLoggerLevels__Request__Level
{
  rosidl_runtime_c__String logger_name;
  uint8_t level;
} rcl_interfaces__srv__SetLoggerLevels__Request__Level;

typedef struct rcl_interfaces__srv__SetLoggerLevels__Request__Level__Sequence
{
  rcl_interfaces__srv__SetLoggerLevels__Request__Level * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__SetLoggerLevels__Request__Level__Sequence;

// Nested type for response
typedef struct rcl_interfaces__srv__SetLoggerLevels__Response__Result
{
  bool successful;
  rosidl_runtime_c__String reason;
} rcl_interfaces__srv__SetLoggerLevels__Response__Result;

typedef struct rcl_interfaces__srv__SetLoggerLevels__Response__Result__Sequence
{
  rcl_interfaces__srv__SetLoggerLevels__Response__Result * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__SetLoggerLevels__Response__Result__Sequence;


// =============================================================================
// SetLoggerLevels Request
// =============================================================================

typedef struct rcl_interfaces__srv__SetLoggerLevels__Request
{
  rcl_interfaces__srv__SetLoggerLevels__Request__Level__Sequence levels;
} rcl_interfaces__srv__SetLoggerLevels__Request;

typedef struct rcl_interfaces__srv__SetLoggerLevels__Request__Sequence
{
  rcl_interfaces__srv__SetLoggerLevels__Request * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__SetLoggerLevels__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__SetLoggerLevels__Request__init(rcl_interfaces__srv__SetLoggerLevels__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetLoggerLevels__Request__fini(rcl_interfaces__srv__SetLoggerLevels__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__SetLoggerLevels__Request * rcl_interfaces__srv__SetLoggerLevels__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetLoggerLevels__Request__destroy(rcl_interfaces__srv__SetLoggerLevels__Request * msg);

// =============================================================================
// SetLoggerLevels Response
// =============================================================================

typedef struct rcl_interfaces__srv__SetLoggerLevels__Response
{
  rcl_interfaces__srv__SetLoggerLevels__Response__Result__Sequence results;
} rcl_interfaces__srv__SetLoggerLevels__Response;

typedef struct rcl_interfaces__srv__SetLoggerLevels__Response__Sequence
{
  rcl_interfaces__srv__SetLoggerLevels__Response * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__SetLoggerLevels__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__SetLoggerLevels__Response__init(rcl_interfaces__srv__SetLoggerLevels__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetLoggerLevels__Response__fini(rcl_interfaces__srv__SetLoggerLevels__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__SetLoggerLevels__Response * rcl_interfaces__srv__SetLoggerLevels__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetLoggerLevels__Response__destroy(rcl_interfaces__srv__SetLoggerLevels__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__SETLOGGERLEVELS_H_
