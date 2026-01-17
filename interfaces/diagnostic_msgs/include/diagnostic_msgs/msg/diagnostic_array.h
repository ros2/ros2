// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/msg/DiagnosticArray type

#ifndef DIAGNOSTIC_MSGS__MSG__DIAGNOSTICARRAY_H_
#define DIAGNOSTIC_MSGS__MSG__DIAGNOSTICARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "diagnostic_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "diagnostic_msgs/msg/diagnostic_status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct diagnostic_msgs__msg__DiagnosticArray
{
  std_msgs__msg__Header header;
  diagnostic_msgs__msg__DiagnosticStatus__Sequence status;
} diagnostic_msgs__msg__DiagnosticArray;

typedef struct diagnostic_msgs__msg__DiagnosticArray__Sequence
{
  diagnostic_msgs__msg__DiagnosticArray * data;
  size_t size;
  size_t capacity;
} diagnostic_msgs__msg__DiagnosticArray__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__msg__DiagnosticArray__init(diagnostic_msgs__msg__DiagnosticArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__msg__DiagnosticArray__fini(diagnostic_msgs__msg__DiagnosticArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
diagnostic_msgs__msg__DiagnosticArray * diagnostic_msgs__msg__DiagnosticArray__create(void);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__msg__DiagnosticArray__destroy(diagnostic_msgs__msg__DiagnosticArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__msg__DiagnosticArray__Sequence__init(
  diagnostic_msgs__msg__DiagnosticArray__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__msg__DiagnosticArray__Sequence__fini(
  diagnostic_msgs__msg__DiagnosticArray__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // DIAGNOSTIC_MSGS__MSG__DIAGNOSTICARRAY_H_
