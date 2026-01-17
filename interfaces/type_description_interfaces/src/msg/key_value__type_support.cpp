// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/KeyValue C++ type support

#include "type_description_interfaces/msg/key_value.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::msg::KeyValue>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, type_description_interfaces, msg, KeyValue)();
}

}  // namespace rosidl_typesupport_cpp
