// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/KeyValue type support

#include "type_description_interfaces/msg/key_value.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t type_description_interfaces__msg__KeyValue__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, type_description_interfaces, msg, KeyValue)()
{
  return &type_description_interfaces__msg__KeyValue__type_support_handle;
}
