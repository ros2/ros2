// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/ParameterEventDescriptors.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_event_descriptors.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/parameter_event_descriptors__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_ParameterEventDescriptors_deleted_parameters
{
public:
  explicit Init_ParameterEventDescriptors_deleted_parameters(::rcl_interfaces::msg::ParameterEventDescriptors & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::ParameterEventDescriptors deleted_parameters(::rcl_interfaces::msg::ParameterEventDescriptors::_deleted_parameters_type arg)
  {
    msg_.deleted_parameters = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEventDescriptors msg_;
};

class Init_ParameterEventDescriptors_changed_parameters
{
public:
  explicit Init_ParameterEventDescriptors_changed_parameters(::rcl_interfaces::msg::ParameterEventDescriptors & msg)
  : msg_(msg)
  {}
  Init_ParameterEventDescriptors_deleted_parameters changed_parameters(::rcl_interfaces::msg::ParameterEventDescriptors::_changed_parameters_type arg)
  {
    msg_.changed_parameters = std::move(arg);
    return Init_ParameterEventDescriptors_deleted_parameters(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEventDescriptors msg_;
};

class Init_ParameterEventDescriptors_new_parameters
{
public:
  Init_ParameterEventDescriptors_new_parameters()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ParameterEventDescriptors_changed_parameters new_parameters(::rcl_interfaces::msg::ParameterEventDescriptors::_new_parameters_type arg)
  {
    msg_.new_parameters = std::move(arg);
    return Init_ParameterEventDescriptors_changed_parameters(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEventDescriptors msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::ParameterEventDescriptors>()
{
  return rcl_interfaces::msg::builder::Init_ParameterEventDescriptors_new_parameters();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT_DESCRIPTORS__BUILDER_HPP_
