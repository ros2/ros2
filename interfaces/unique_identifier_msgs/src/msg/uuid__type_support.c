// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// unique_identifier_msgs/msg/UUID type support

#include "unique_identifier_msgs/msg/uuid.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t unique_identifier_msgs__msg__UUID__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, unique_identifier_msgs, msg, UUID)()
{
  return &unique_identifier_msgs__msg__UUID__type_support_handle;
}
