// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/GetParameterTypes type

#ifndef RCL_INTERFACES__SRV__GETPARAMETERTYPES_H_
#define RCL_INTERFACES__SRV__GETPARAMETERTYPES_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/primitives_sequence.h"

#ifdef __cplusplus
extern "C" {
#endif




// =============================================================================
// GetParameterTypes Request
// =============================================================================

typedef struct rcl_interfaces__srv__GetParameterTypes__Request
{
  rosidl_runtime_c__String__Sequence names;
} rcl_interfaces__srv__GetParameterTypes__Request;

typedef struct rcl_interfaces__srv__GetParameterTypes__Request__Sequence
{
  rcl_interfaces__srv__GetParameterTypes__Request * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__GetParameterTypes__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__GetParameterTypes__Request__init(rcl_interfaces__srv__GetParameterTypes__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameterTypes__Request__fini(rcl_interfaces__srv__GetParameterTypes__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__GetParameterTypes__Request * rcl_interfaces__srv__GetParameterTypes__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameterTypes__Request__destroy(rcl_interfaces__srv__GetParameterTypes__Request * msg);

// =============================================================================
// GetParameterTypes Response
// =============================================================================

typedef struct rcl_interfaces__srv__GetParameterTypes__Response
{
  rosidl_runtime_c__uint8__Sequence types;
} rcl_interfaces__srv__GetParameterTypes__Response;

typedef struct rcl_interfaces__srv__GetParameterTypes__Response__Sequence
{
  rcl_interfaces__srv__GetParameterTypes__Response * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__GetParameterTypes__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__GetParameterTypes__Response__init(rcl_interfaces__srv__GetParameterTypes__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameterTypes__Response__fini(rcl_interfaces__srv__GetParameterTypes__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__GetParameterTypes__Response * rcl_interfaces__srv__GetParameterTypes__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameterTypes__Response__destroy(rcl_interfaces__srv__GetParameterTypes__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__GETPARAMETERTYPES_H_
