// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rosgraph_msgs/msg/Clock FastRTPS C type support

#include "rosgraph_msgs/msg/clock.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

static const rosidl_message_type_support_t rosgraph_msgs__msg__Clock__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, rosgraph_msgs, msg, Clock)()
{
  return &rosgraph_msgs__msg__Clock__fastrtps_type_support;
}

}  // extern "C"
