// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/srv/AddDiagnostics_Response type

#ifndef DIAGNOSTIC_MSGS__SRV__ADDDIAGNOSTICS_RESPONSE_H_
#define DIAGNOSTIC_MSGS__SRV__ADDDIAGNOSTICS_RESPONSE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "diagnostic_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct diagnostic_msgs__srv__AddDiagnostics_Response
{
  bool success;
  rosidl_runtime_c__String message;
} diagnostic_msgs__srv__AddDiagnostics_Response;

typedef struct diagnostic_msgs__srv__AddDiagnostics_Response__Sequence
{
  diagnostic_msgs__srv__AddDiagnostics_Response * data;
  size_t size;
  size_t capacity;
} diagnostic_msgs__srv__AddDiagnostics_Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__srv__AddDiagnostics_Response__init(diagnostic_msgs__srv__AddDiagnostics_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__srv__AddDiagnostics_Response__fini(diagnostic_msgs__srv__AddDiagnostics_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
diagnostic_msgs__srv__AddDiagnostics_Response * diagnostic_msgs__srv__AddDiagnostics_Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__srv__AddDiagnostics_Response__destroy(diagnostic_msgs__srv__AddDiagnostics_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__srv__AddDiagnostics_Response__Sequence__init(
  diagnostic_msgs__srv__AddDiagnostics_Response__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__srv__AddDiagnostics_Response__Sequence__fini(
  diagnostic_msgs__srv__AddDiagnostics_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // DIAGNOSTIC_MSGS__SRV__ADDDIAGNOSTICS_RESPONSE_H_
