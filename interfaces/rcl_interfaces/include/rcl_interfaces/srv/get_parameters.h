// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/GetParameters type

#ifndef RCL_INTERFACES__SRV__GETPARAMETERS_H_
#define RCL_INTERFACES__SRV__GETPARAMETERS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"
#include "rcl_interfaces/msg/parameter_value.h"

#ifdef __cplusplus
extern "C" {
#endif




// =============================================================================
// GetParameters Request
// =============================================================================

typedef struct rcl_interfaces__srv__GetParameters__Request
{
  rosidl_runtime_c__String__Sequence names;
} rcl_interfaces__srv__GetParameters__Request;

typedef struct rcl_interfaces__srv__GetParameters__Request__Sequence
{
  rcl_interfaces__srv__GetParameters__Request * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__GetParameters__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__GetParameters__Request__init(rcl_interfaces__srv__GetParameters__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameters__Request__fini(rcl_interfaces__srv__GetParameters__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__GetParameters__Request * rcl_interfaces__srv__GetParameters__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameters__Request__destroy(rcl_interfaces__srv__GetParameters__Request * msg);

// =============================================================================
// GetParameters Response
// =============================================================================

typedef struct rcl_interfaces__srv__GetParameters__Response
{
  rcl_interfaces__msg__ParameterValue__Sequence values;
} rcl_interfaces__srv__GetParameters__Response;

typedef struct rcl_interfaces__srv__GetParameters__Response__Sequence
{
  rcl_interfaces__srv__GetParameters__Response * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__GetParameters__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__GetParameters__Response__init(rcl_interfaces__srv__GetParameters__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameters__Response__fini(rcl_interfaces__srv__GetParameters__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__GetParameters__Response * rcl_interfaces__srv__GetParameters__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__GetParameters__Response__destroy(rcl_interfaces__srv__GetParameters__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__GETPARAMETERS_H_
