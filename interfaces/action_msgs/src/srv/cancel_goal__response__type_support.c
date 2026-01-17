// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/srv/CancelGoal_Response type support

#include "action_msgs/srv/cancel_goal__response.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

// Type support handle
static rosidl_message_type_support_t action_msgs__srv__CancelGoal_Response__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, action_msgs, srv, CancelGoal_Response)()
{
  return &action_msgs__srv__CancelGoal_Response__type_support_handle;
}
