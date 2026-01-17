// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/ListParameters type

#ifndef RCL_INTERFACES__SRV__LISTPARAMETERS_H_
#define RCL_INTERFACES__SRV__LISTPARAMETERS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"
#include "rcl_interfaces/msg/list_parameters_result.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RCL_INTERFACES__SRV__LISTPARAMETERS__REQUEST__DEPTH_RECURSIVE ((uint64_t)0U)


// =============================================================================
// ListParameters Request
// =============================================================================

typedef struct rcl_interfaces__srv__ListParameters__Request
{
  rosidl_runtime_c__String__Sequence prefixes;
  uint64_t depth;
} rcl_interfaces__srv__ListParameters__Request;

typedef struct rcl_interfaces__srv__ListParameters__Request__Sequence
{
  rcl_interfaces__srv__ListParameters__Request * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__ListParameters__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__ListParameters__Request__init(rcl_interfaces__srv__ListParameters__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__ListParameters__Request__fini(rcl_interfaces__srv__ListParameters__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__ListParameters__Request * rcl_interfaces__srv__ListParameters__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__ListParameters__Request__destroy(rcl_interfaces__srv__ListParameters__Request * msg);

// =============================================================================
// ListParameters Response
// =============================================================================

typedef struct rcl_interfaces__srv__ListParameters__Response
{
  rcl_interfaces__msg__ListParametersResult result;
} rcl_interfaces__srv__ListParameters__Response;

typedef struct rcl_interfaces__srv__ListParameters__Response__Sequence
{
  rcl_interfaces__srv__ListParameters__Response * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__srv__ListParameters__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__srv__ListParameters__Response__init(rcl_interfaces__srv__ListParameters__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__ListParameters__Response__fini(rcl_interfaces__srv__ListParameters__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__srv__ListParameters__Response * rcl_interfaces__srv__ListParameters__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__srv__ListParameters__Response__destroy(rcl_interfaces__srv__ListParameters__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__SRV__LISTPARAMETERS_H_
