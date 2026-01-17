// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Int8MultiArray type support

#include "std_msgs/msg/int8_multi_array.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

// Stub type support - detailed introspection omitted for brevity
static const rosidl_typesupport_introspection_c__MessageMembers
std_msgs__msg__Int8MultiArray__message_members = {
  "std_msgs", "Int8MultiArray", 0, sizeof(std_msgs__msg__Int8MultiArray), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)std_msgs__msg__Int8MultiArray__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)std_msgs__msg__Int8MultiArray__fini
};

static rosidl_message_type_support_t std_msgs__msg__Int8MultiArray__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &std_msgs__msg__Int8MultiArray__message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__Int8MultiArray__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, std_msgs, msg, Int8MultiArray)()
{
  return &std_msgs__msg__Int8MultiArray__type_support;
}
