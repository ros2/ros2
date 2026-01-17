// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/msg/TF2Error type support

#include "tf2_msgs/msg/t_f2_error.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Type support handle
static rosidl_message_type_support_t tf2_msgs__msg__TF2Error__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, tf2_msgs, msg, TF2Error)()
{
  return &tf2_msgs__msg__TF2Error__type_support_handle;
}
