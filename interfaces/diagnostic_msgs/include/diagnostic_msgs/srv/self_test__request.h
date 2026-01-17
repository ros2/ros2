// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/srv/SelfTest_Request type

#ifndef DIAGNOSTIC_MSGS__SRV__SELFTEST_REQUEST_H_
#define DIAGNOSTIC_MSGS__SRV__SELFTEST_REQUEST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "diagnostic_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct diagnostic_msgs__srv__SelfTest_Request
{
  uint8_t structure_needs_at_least_one_member;
} diagnostic_msgs__srv__SelfTest_Request;

typedef struct diagnostic_msgs__srv__SelfTest_Request__Sequence
{
  diagnostic_msgs__srv__SelfTest_Request * data;
  size_t size;
  size_t capacity;
} diagnostic_msgs__srv__SelfTest_Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__srv__SelfTest_Request__init(diagnostic_msgs__srv__SelfTest_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__srv__SelfTest_Request__fini(diagnostic_msgs__srv__SelfTest_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
diagnostic_msgs__srv__SelfTest_Request * diagnostic_msgs__srv__SelfTest_Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__srv__SelfTest_Request__destroy(diagnostic_msgs__srv__SelfTest_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
bool diagnostic_msgs__srv__SelfTest_Request__Sequence__init(
  diagnostic_msgs__srv__SelfTest_Request__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs
void diagnostic_msgs__srv__SelfTest_Request__Sequence__fini(
  diagnostic_msgs__srv__SelfTest_Request__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // DIAGNOSTIC_MSGS__SRV__SELFTEST_REQUEST_H_
