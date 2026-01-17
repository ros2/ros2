// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/State FastRTPS C type support

#include "lifecycle_msgs/msg/state.h"
#include "rosidl_typesupport_fastrtps_c/identifier.h"

extern "C"
{

static const rosidl_message_type_support_t lifecycle_msgs__msg__State__fastrtps_type_support = {
  .typesupport_identifier = rosidl_typesupport_fastrtps_c__identifier,
  .data = nullptr,
  .func = nullptr,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_fastrtps_c, lifecycle_msgs, msg, State)()
{
  return &lifecycle_msgs__msg__State__fastrtps_type_support;
}

}  // extern "C"
