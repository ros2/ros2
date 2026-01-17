// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Empty type support

#include "std_msgs/msg/empty.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static const rosidl_typesupport_introspection_c__MessageMembers
std_msgs__msg__Empty__message_members = {
  "std_msgs", "Empty", 0, sizeof(std_msgs__msg__Empty), false,
  NULL,
  (rosidl_typesupport_introspection_c__MessageInitFunction)std_msgs__msg__Empty__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)std_msgs__msg__Empty__fini
};

static rosidl_message_type_support_t std_msgs__msg__Empty__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &std_msgs__msg__Empty__message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__Empty__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, std_msgs, msg, Empty)()
{
  return &std_msgs__msg__Empty__type_support;
}
