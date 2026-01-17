// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/KeyValue FastRTPS C type support

#include "type_description_interfaces/msg/key_value.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

static const rosidl_message_type_support_t type_description_interfaces__msg__KeyValue__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, type_description_interfaces, msg, KeyValue)()
{
  return &type_description_interfaces__msg__KeyValue__fastrtps_type_support;
}

}  // extern "C"
