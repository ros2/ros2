// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/Parameter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/parameter__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_Parameter_value
{
public:
  explicit Init_Parameter_value(::rcl_interfaces::msg::Parameter & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::Parameter value(::rcl_interfaces::msg::Parameter::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::Parameter msg_;
};

class Init_Parameter_name
{
public:
  Init_Parameter_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Parameter_value name(::rcl_interfaces::msg::Parameter::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Parameter_value(msg_);
  }

private:
  ::rcl_interfaces::msg::Parameter msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::Parameter>()
{
  return rcl_interfaces::msg::builder::Init_Parameter_name();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER__BUILDER_HPP_
