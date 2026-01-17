// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/Log C++ type support

#include "rcl_interfaces/msg/log.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces::msg::Log>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, rcl_interfaces, msg, Log)();
}

}  // namespace rosidl_typesupport_cpp
