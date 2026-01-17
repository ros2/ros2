// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/msg/DiagnosticStatus type

#ifndef DIAGNOSTIC_MSGS__MSG__DIAGNOSTICSTATUS_H_
#define DIAGNOSTIC_MSGS__MSG__DIAGNOSTICSTATUS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "diagnostic_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"
#include "diagnostic_msgs/msg/key_value.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define DIAGNOSTIC_MSGS__MSG__DiagnosticStatus_OK 0
#define DIAGNOSTIC_MSGS__MSG__DiagnosticStatus_WARN 1
#define DIAGNOSTIC_MSGS__MSG__DiagnosticStatus_ERROR 2
#define DIAGNOSTIC_MSGS__MSG__DiagnosticStatus_STALE 3

typedef struct diagnostic_msgs__msg__DiagnosticStatus
{
  uint8_t level;
  rosidl_runtime_c__String name;
  rosidl_runtime_c__String message;
  rosidl_runtime_c__String hardware_id;
  diagnostic_msgs__msg__KeyValue__Sequence values;
} diagnostic_msgs__msg__DiagnosticStatus;

typedef struct diagnostic_msgs__msg__DiagnosticStatus__Sequence
{
  diagnostic_msgs__msg__DiagnosticStatus * data;
  size_t size;
  size_t capacity;
} diagnostic_msgs__msg__DiagnosticStatus__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__msg__DiagnosticStatus__init(diagnostic_msgs__msg__DiagnosticStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__msg__DiagnosticStatus__fini(diagnostic_msgs__msg__DiagnosticStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
diagnostic_msgs__msg__DiagnosticStatus * diagnostic_msgs__msg__DiagnosticStatus__create(void);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__msg__DiagnosticStatus__destroy(diagnostic_msgs__msg__DiagnosticStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__msg__DiagnosticStatus__Sequence__init(
  diagnostic_msgs__msg__DiagnosticStatus__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__msg__DiagnosticStatus__Sequence__fini(
  diagnostic_msgs__msg__DiagnosticStatus__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // DIAGNOSTIC_MSGS__MSG__DIAGNOSTICSTATUS_H_
