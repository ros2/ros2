// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/State C++ type support

#include "lifecycle_msgs/msg/state.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<lifecycle_msgs::msg::State>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, lifecycle_msgs, msg, State)();
}

}  // namespace rosidl_typesupport_cpp
