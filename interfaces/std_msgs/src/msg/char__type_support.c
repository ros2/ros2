// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Char type support

#include "std_msgs/msg/char.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static rosidl_typesupport_introspection_c__MessageMember
std_msgs__msg__Char__members[1] = {
  {
    "data",
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,
    0, NULL, false, 0, false,
    offsetof(std_msgs__msg__Char, data),
    NULL, NULL, NULL, NULL, NULL, NULL
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers
std_msgs__msg__Char__message_members = {
  "std_msgs", "Char", 1, sizeof(std_msgs__msg__Char), false,
  std_msgs__msg__Char__members,
  (rosidl_typesupport_introspection_c__MessageInitFunction)std_msgs__msg__Char__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)std_msgs__msg__Char__fini
};

static rosidl_message_type_support_t std_msgs__msg__Char__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &std_msgs__msg__Char__message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__Char__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, std_msgs, msg, Char)()
{
  return &std_msgs__msg__Char__type_support;
}
