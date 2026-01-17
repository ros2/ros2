// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_srvs/srv/Empty C++ type support

#include "std_srvs/srv/empty.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<std_srvs::srv::Empty_Request>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, std_srvs, srv, Empty_Request)();
}

template<>
const rosidl_message_type_support_t *
get_message_type_support_handle<std_srvs::srv::Empty_Response>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, std_srvs, srv, Empty_Response)();
}

template<>
const rosidl_service_type_support_t *
get_service_type_support_handle<std_srvs::srv::Empty>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, std_srvs, srv, Empty)();
}

}  // namespace rosidl_typesupport_cpp
