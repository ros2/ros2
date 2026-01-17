// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/SetParameters type

#ifndef RCL_INTERFACES__SRV__SETPARAMETERS_H_
#define RCL_INTERFACES__SRV__SETPARAMETERS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rcl_interfaces/msg/parameter.h"
#include "rcl_interfaces/msg/set_parameters_result.h"

#ifdef __cplusplus
extern "C" {
#endif




// =============================================================================
// SetParameters Request
// =============================================================================

typedef struct rcl_interfaces__srv__SetParameters__Request
{
  rcl_interfaces__msg__Parameter__Sequence parameters;
} rcl_interfaces__srv__SetParameters__Request;

typedef struct rcl_interfaces__srv__SetParameters__Request__Sequence
{
  rcl_interfaces__srv__SetParameters__Request * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__SetParameters__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__SetParameters__Request__init(rcl_interfaces__srv__SetParameters__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetParameters__Request__fini(rcl_interfaces__srv__SetParameters__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__SetParameters__Request * rcl_interfaces__srv__SetParameters__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetParameters__Request__destroy(rcl_interfaces__srv__SetParameters__Request * msg);

// =============================================================================
// SetParameters Response
// =============================================================================

typedef struct rcl_interfaces__srv__SetParameters__Response
{
  rcl_interfaces__msg__SetParametersResult__Sequence results;
} rcl_interfaces__srv__SetParameters__Response;

typedef struct rcl_interfaces__srv__SetParameters__Response__Sequence
{
  rcl_interfaces__srv__SetParameters__Response * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__SetParameters__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__SetParameters__Response__init(rcl_interfaces__srv__SetParameters__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetParameters__Response__fini(rcl_interfaces__srv__SetParameters__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__SetParameters__Response * rcl_interfaces__srv__SetParameters__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__SetParameters__Response__destroy(rcl_interfaces__srv__SetParameters__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__SETPARAMETERS_H_
