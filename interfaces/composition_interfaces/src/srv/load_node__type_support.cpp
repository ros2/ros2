// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/LoadNode C++ type support

#include "composition_interfaces/srv/load_node.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace rosidl_typesupport_cpp
{

template<>
const rosidl_service_type_support_t *
get_service_type_support_handle<composition_interfaces::srv::LoadNode>()
{
  return ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, composition_interfaces, srv, LoadNode)();
}

}  // namespace rosidl_typesupport_cpp
