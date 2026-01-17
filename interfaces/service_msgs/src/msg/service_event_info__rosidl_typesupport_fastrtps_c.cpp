// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// service_msgs/msg/ServiceEventInfo FastRTPS C type support

#include "service_msgs/msg/service_event_info.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

static const rosidl_message_type_support_t service_msgs__msg__ServiceEventInfo__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, service_msgs, msg, ServiceEventInfo)()
{
  return &service_msgs__msg__ServiceEventInfo__fastrtps_type_support;
}

}  // extern "C"
