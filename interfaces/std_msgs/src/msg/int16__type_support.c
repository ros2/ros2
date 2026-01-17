// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Int16 type support

#include "std_msgs/msg/int16.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static rosidl_typesupport_introspection_c__MessageMember
std_msgs__msg__Int16__members[1] = {
  {
    "data",
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,
    0, NULL, false, 0, false,
    offsetof(std_msgs__msg__Int16, data),
    NULL, NULL, NULL, NULL, NULL, NULL
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers
std_msgs__msg__Int16__message_members = {
  "std_msgs", "Int16", 1, sizeof(std_msgs__msg__Int16), false,
  std_msgs__msg__Int16__members,
  (rosidl_typesupport_introspection_c__MessageInitFunction)std_msgs__msg__Int16__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)std_msgs__msg__Int16__fini
};

static rosidl_message_type_support_t std_msgs__msg__Int16__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &std_msgs__msg__Int16__message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__Int16__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, std_msgs, msg, Int16)()
{
  return &std_msgs__msg__Int16__type_support;
}
