// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// shape_msgs/msg/SolidPrimitive type support

#include "shape_msgs/msg/solid_primitive.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t shape_msgs__msg__SolidPrimitive__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, shape_msgs, msg, SolidPrimitive)()
{
  return &shape_msgs__msg__SolidPrimitive__type_support_handle;
}
