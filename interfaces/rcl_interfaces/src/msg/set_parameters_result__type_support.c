// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/SetParametersResult type support

#include "rcl_interfaces/msg/set_parameters_result.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t rcl_interfaces__msg__SetParametersResult__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, msg, SetParametersResult)()
{
  return &rcl_interfaces__msg__SetParametersResult__type_support_handle;
}
