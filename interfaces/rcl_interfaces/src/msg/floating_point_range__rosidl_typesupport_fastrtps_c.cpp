// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/FloatingPointRange FastRTPS C type support

#include "rcl_interfaces/msg/floating_point_range.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"

extern "C"
{

static const rosidl_message_type_support_t rcl_interfaces__msg__FloatingPointRange__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, rcl_interfaces, msg, FloatingPointRange)()
{
  return &rcl_interfaces__msg__FloatingPointRange__fastrtps_type_support;
}

}  // extern "C"
