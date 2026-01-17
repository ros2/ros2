// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/ParameterType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_type.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/parameter_type__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{


}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::ParameterType>()
{
  return ::rcl_interfaces::msg::ParameterType(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__BUILDER_HPP_
