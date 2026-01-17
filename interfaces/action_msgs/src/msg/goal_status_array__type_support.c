// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/msg/GoalStatusArray type support

#include "action_msgs/msg/goal_status_array.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Type support handle
static rosidl_message_type_support_t action_msgs__msg__GoalStatusArray__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)()
{
  return &action_msgs__msg__GoalStatusArray__type_support_handle;
}
