// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/MultiArrayDimension type support

#include "std_msgs/msg/multi_array_dimension.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

static rosidl_typesupport_introspection_c__MessageMember
std_msgs__msg__MultiArrayDimension__members[3] = {
  {
    "label",
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,
    0, NULL, false, 0, false,
    offsetof(std_msgs__msg__MultiArrayDimension, label),
    NULL, NULL, NULL, NULL, NULL, NULL
  },
  {
    "size",
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,
    0, NULL, false, 0, false,
    offsetof(std_msgs__msg__MultiArrayDimension, size),
    NULL, NULL, NULL, NULL, NULL, NULL
  },
  {
    "stride",
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,
    0, NULL, false, 0, false,
    offsetof(std_msgs__msg__MultiArrayDimension, stride),
    NULL, NULL, NULL, NULL, NULL, NULL
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers
std_msgs__msg__MultiArrayDimension__message_members = {
  "std_msgs", "MultiArrayDimension", 3, sizeof(std_msgs__msg__MultiArrayDimension), false,
  std_msgs__msg__MultiArrayDimension__members,
  (rosidl_typesupport_introspection_c__MessageInitFunction)std_msgs__msg__MultiArrayDimension__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)std_msgs__msg__MultiArrayDimension__fini
};

static rosidl_message_type_support_t std_msgs__msg__MultiArrayDimension__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &std_msgs__msg__MultiArrayDimension__message_members,
  get_message_typesupport_handle_function,
  &std_msgs__msg__MultiArrayDimension__type_support
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, std_msgs, msg, MultiArrayDimension)()
{
  return &std_msgs__msg__MultiArrayDimension__type_support;
}
