// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/TypeSource type support

#include "type_description_interfaces/msg/type_source.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t type_description_interfaces__msg__TypeSource__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, type_description_interfaces, msg, TypeSource)()
{
  return &type_description_interfaces__msg__TypeSource__type_support_handle;
}
