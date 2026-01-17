// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// builtin_interfaces/msg/Time C++ type support

#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_interface/macros.h"

#include "builtin_interfaces/msg/time.h"

namespace rosidl_typesupport_cpp
{

template<>
struct MessageTypeSupport<builtin_interfaces__msg__Time>
{
  static constexpr const char * package_name = "builtin_interfaces";
  static constexpr const char * message_name = "Time";
};

}  // namespace rosidl_typesupport_cpp

extern "C"
{

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_cpp, builtin_interfaces, msg, Time)()
{
  return rosidl_typesupport_cpp::get_message_type_support_handle<
    builtin_interfaces__msg__Time>();
}

}  // extern "C"
