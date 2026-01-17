// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/SetParametersResult C++ type support

#include "rcl_interfaces/msg/set_parameters_result.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces::msg::SetParametersResult>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, rcl_interfaces, msg, SetParametersResult)();
}

}  // namespace rosidl_typesupport_cpp
