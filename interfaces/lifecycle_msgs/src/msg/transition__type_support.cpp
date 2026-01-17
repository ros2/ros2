// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/Transition C++ type support

#include "lifecycle_msgs/msg/transition.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<lifecycle_msgs::msg::Transition>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, lifecycle_msgs, msg, Transition)();
}

}  // namespace rosidl_typesupport_cpp
