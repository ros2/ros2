// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/IndividualTypeDescription C++ type support

#include "type_description_interfaces/msg/individual_type_description.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::msg::IndividualTypeDescription>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, type_description_interfaces, msg, IndividualTypeDescription)();
}

}  // namespace rosidl_typesupport_cpp
