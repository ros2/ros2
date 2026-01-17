// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/srv/SelfTest_Request type support

#include "diagnostic_msgs/srv/self_test__request.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t diagnostic_msgs__srv__SelfTest_Request__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, diagnostic_msgs, srv, SelfTest_Request)()
{
  return &diagnostic_msgs__srv__SelfTest_Request__type_support_handle;
}
