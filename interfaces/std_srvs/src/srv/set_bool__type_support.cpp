// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/SetBool C++ type support

#include "std_srvs/srv/set_bool.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<std_srvs::srv::SetBool_Request>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, std_srvs, srv, SetBool_Request)();
}

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<std_srvs::srv::SetBool_Response>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, std_srvs, srv, SetBool_Response)();
}

template<>
const rosidl_service_type_support_t *
get_service_type_support_handle<std_srvs::srv::SetBool>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, std_srvs, srv, SetBool)();
}

}  // namespace rosidl_typesupport_cpp
