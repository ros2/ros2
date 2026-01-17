// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/TypeDescription C++ type support

#include "type_description_interfaces/msg/type_description.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::msg::TypeDescription>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, type_description_interfaces, msg, TypeDescription)();
}

}  // namespace rosidl_typesupport_cpp
