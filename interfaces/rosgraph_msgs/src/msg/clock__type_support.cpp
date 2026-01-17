// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rosgraph_msgs/msg/Clock C++ type support

#include "rosgraph_msgs/msg/clock.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<rosgraph_msgs::msg::Clock>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, rosgraph_msgs, msg, Clock)();
}

}  // namespace rosidl_typesupport_cpp
