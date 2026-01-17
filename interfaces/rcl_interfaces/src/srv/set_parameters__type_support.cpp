// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/srv/SetParameters C++ type support

#include "rcl_interfaces/srv/set_parameters.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_service_type_support_t *
get_service_type_support_handle<rcl_interfaces::srv::SetParameters>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, rcl_interfaces, srv, SetParameters)();
}

}  // namespace rosidl_typesupport_cpp
