// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterType type support

#include "rcl_interfaces/msg/parameter_type.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t rcl_interfaces__msg__ParameterType__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, rcl_interfaces, msg, ParameterType)()
{
  return &rcl_interfaces__msg__ParameterType__type_support_handle;
}
