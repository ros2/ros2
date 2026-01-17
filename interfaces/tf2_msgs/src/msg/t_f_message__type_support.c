// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/msg/TFMessage type support

#include "tf2_msgs/msg/t_f_message.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Type support handle
static rosidl_message_type_support_t tf2_msgs__msg__TFMessage__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, tf2_msgs, msg, TFMessage)()
{
  return &tf2_msgs__msg__TFMessage__type_support_handle;
}
