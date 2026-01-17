// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// service_msgs/msg/ServiceEventInfo type support

#include "service_msgs/msg/service_event_info.h"
#include "rosidl_typesupport_c/message_type_support.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

static rosidl_message_type_support_t service_msgs__msg__ServiceEventInfo__type_support_handle = {
  .typesupport_identifier = "rosidl_typesupport_c",
  .data = NULL,
  .func = NULL,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c, service_msgs, msg, ServiceEventInfo)()
{
  return &service_msgs__msg__ServiceEventInfo__type_support_handle;
}
