// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/ParameterDescriptor.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_descriptor.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_DESCRIPTOR__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_DESCRIPTOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/parameter_descriptor__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_ParameterDescriptor_integer_range
{
public:
  explicit Init_ParameterDescriptor_integer_range(::rcl_interfaces::msg::ParameterDescriptor & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::ParameterDescriptor integer_range(::rcl_interfaces::msg::ParameterDescriptor::_integer_range_type arg)
  {
    msg_.integer_range = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

class Init_ParameterDescriptor_floating_point_range
{
public:
  explicit Init_ParameterDescriptor_floating_point_range(::rcl_interfaces::msg::ParameterDescriptor & msg)
  : msg_(msg)
  {}
  Init_ParameterDescriptor_integer_range floating_point_range(::rcl_interfaces::msg::ParameterDescriptor::_floating_point_range_type arg)
  {
    msg_.floating_point_range = std::move(arg);
    return Init_ParameterDescriptor_integer_range(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

class Init_ParameterDescriptor_dynamic_typing
{
public:
  explicit Init_ParameterDescriptor_dynamic_typing(::rcl_interfaces::msg::ParameterDescriptor & msg)
  : msg_(msg)
  {}
  Init_ParameterDescriptor_floating_point_range dynamic_typing(::rcl_interfaces::msg::ParameterDescriptor::_dynamic_typing_type arg)
  {
    msg_.dynamic_typing = std::move(arg);
    return Init_ParameterDescriptor_floating_point_range(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

class Init_ParameterDescriptor_read_only
{
public:
  explicit Init_ParameterDescriptor_read_only(::rcl_interfaces::msg::ParameterDescriptor & msg)
  : msg_(msg)
  {}
  Init_ParameterDescriptor_dynamic_typing read_only(::rcl_interfaces::msg::ParameterDescriptor::_read_only_type arg)
  {
    msg_.read_only = std::move(arg);
    return Init_ParameterDescriptor_dynamic_typing(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

class Init_ParameterDescriptor_additional_constraints
{
public:
  explicit Init_ParameterDescriptor_additional_constraints(::rcl_interfaces::msg::ParameterDescriptor & msg)
  : msg_(msg)
  {}
  Init_ParameterDescriptor_read_only additional_constraints(::rcl_interfaces::msg::ParameterDescriptor::_additional_constraints_type arg)
  {
    msg_.additional_constraints = std::move(arg);
    return Init_ParameterDescriptor_read_only(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

class Init_ParameterDescriptor_description
{
public:
  explicit Init_ParameterDescriptor_description(::rcl_interfaces::msg::ParameterDescriptor & msg)
  : msg_(msg)
  {}
  Init_ParameterDescriptor_additional_constraints description(::rcl_interfaces::msg::ParameterDescriptor::_description_type arg)
  {
    msg_.description = std::move(arg);
    return Init_ParameterDescriptor_additional_constraints(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

class Init_ParameterDescriptor_type
{
public:
  explicit Init_ParameterDescriptor_type(::rcl_interfaces::msg::ParameterDescriptor & msg)
  : msg_(msg)
  {}
  Init_ParameterDescriptor_description type(::rcl_interfaces::msg::ParameterDescriptor::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_ParameterDescriptor_description(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

class Init_ParameterDescriptor_name
{
public:
  Init_ParameterDescriptor_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ParameterDescriptor_type name(::rcl_interfaces::msg::ParameterDescriptor::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_ParameterDescriptor_type(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterDescriptor msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::ParameterDescriptor>()
{
  return rcl_interfaces::msg::builder::Init_ParameterDescriptor_name();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_DESCRIPTOR__BUILDER_HPP_
