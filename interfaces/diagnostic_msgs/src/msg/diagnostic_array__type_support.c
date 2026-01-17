// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/msg/DiagnosticArray type support

#include "diagnostic_msgs/msg/diagnostic_array.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t diagnostic_msgs__msg__DiagnosticArray__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, diagnostic_msgs, msg, DiagnosticArray)()
{
  return &diagnostic_msgs__msg__DiagnosticArray__type_support_handle;
}
