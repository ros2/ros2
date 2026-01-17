// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterEventDescriptors type

#ifndef RCL_INTERFACES__MSG__PARAMETEREVENTDESCRIPTORS_H_
#define RCL_INTERFACES__MSG__PARAMETEREVENTDESCRIPTORS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rcl_interfaces/msg/parameter_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif



/// Descriptors for parameter events
typedef struct rcl_interfaces__msg__ParameterEventDescriptors
{
  rcl_interfaces__msg__ParameterDescriptor__Sequence new_parameters;
  rcl_interfaces__msg__ParameterDescriptor__Sequence changed_parameters;
  rcl_interfaces__msg__ParameterDescriptor__Sequence deleted_parameters;
} rcl_interfaces__msg__ParameterEventDescriptors;

typedef struct rcl_interfaces__msg__ParameterEventDescriptors__Sequence
{
  rcl_interfaces__msg__ParameterEventDescriptors * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__ParameterEventDescriptors__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterEventDescriptors__init(rcl_interfaces__msg__ParameterEventDescriptors * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterEventDescriptors__fini(rcl_interfaces__msg__ParameterEventDescriptors * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ParameterEventDescriptors * rcl_interfaces__msg__ParameterEventDescriptors__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterEventDescriptors__destroy(rcl_interfaces__msg__ParameterEventDescriptors * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterEventDescriptors__Sequence__init(
  rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterEventDescriptors__Sequence__fini(
  rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__PARAMETEREVENTDESCRIPTORS_H_
