// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterEvent type

#ifndef RCL_INTERFACES__MSG__PARAMETEREVENT_H_
#define RCL_INTERFACES__MSG__PARAMETEREVENT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "builtin_interfaces/msg/time.h"
#include "rosidl_runtime_c/string.h"
#include "rcl_interfaces/msg/parameter.h"

#ifdef __cplusplus
extern "C" {
#endif



/// Event when parameters change
typedef struct rcl_interfaces__msg__ParameterEvent
{
  builtin_interfaces__msg__Time stamp;
  rosidl_runtime_c__String node;
  rcl_interfaces__msg__Parameter__Sequence new_parameters;
  rcl_interfaces__msg__Parameter__Sequence changed_parameters;
  rcl_interfaces__msg__Parameter__Sequence deleted_parameters;
} rcl_interfaces__msg__ParameterEvent;

typedef struct rcl_interfaces__msg__ParameterEvent__Sequence
{
  rcl_interfaces__msg__ParameterEvent * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__ParameterEvent__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterEvent__init(rcl_interfaces__msg__ParameterEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterEvent__fini(rcl_interfaces__msg__ParameterEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ParameterEvent * rcl_interfaces__msg__ParameterEvent__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterEvent__destroy(rcl_interfaces__msg__ParameterEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterEvent__Sequence__init(
  rcl_interfaces__msg__ParameterEvent__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterEvent__Sequence__fini(
  rcl_interfaces__msg__ParameterEvent__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__PARAMETEREVENT_H_
