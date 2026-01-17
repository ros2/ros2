// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/msg/DiagnosticStatus type support

#include "diagnostic_msgs/msg/diagnostic_status.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t diagnostic_msgs__msg__DiagnosticStatus__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, diagnostic_msgs, msg, DiagnosticStatus)()
{
  return &diagnostic_msgs__msg__DiagnosticStatus__type_support_handle;
}
