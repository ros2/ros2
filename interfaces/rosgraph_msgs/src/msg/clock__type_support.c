// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rosgraph_msgs/msg/Clock type support

#include "rosgraph_msgs/msg/clock.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t rosgraph_msgs__msg__Clock__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, rosgraph_msgs, msg, Clock)()
{
  return &rosgraph_msgs__msg__Clock__type_support_handle;
}
