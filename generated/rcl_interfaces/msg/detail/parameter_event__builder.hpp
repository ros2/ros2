// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/ParameterEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_event.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/parameter_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_ParameterEvent_deleted_parameters
{
public:
  explicit Init_ParameterEvent_deleted_parameters(::rcl_interfaces::msg::ParameterEvent & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::ParameterEvent deleted_parameters(::rcl_interfaces::msg::ParameterEvent::_deleted_parameters_type arg)
  {
    msg_.deleted_parameters = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEvent msg_;
};

class Init_ParameterEvent_changed_parameters
{
public:
  explicit Init_ParameterEvent_changed_parameters(::rcl_interfaces::msg::ParameterEvent & msg)
  : msg_(msg)
  {}
  Init_ParameterEvent_deleted_parameters changed_parameters(::rcl_interfaces::msg::ParameterEvent::_changed_parameters_type arg)
  {
    msg_.changed_parameters = std::move(arg);
    return Init_ParameterEvent_deleted_parameters(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEvent msg_;
};

class Init_ParameterEvent_new_parameters
{
public:
  explicit Init_ParameterEvent_new_parameters(::rcl_interfaces::msg::ParameterEvent & msg)
  : msg_(msg)
  {}
  Init_ParameterEvent_changed_parameters new_parameters(::rcl_interfaces::msg::ParameterEvent::_new_parameters_type arg)
  {
    msg_.new_parameters = std::move(arg);
    return Init_ParameterEvent_changed_parameters(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEvent msg_;
};

class Init_ParameterEvent_node
{
public:
  explicit Init_ParameterEvent_node(::rcl_interfaces::msg::ParameterEvent & msg)
  : msg_(msg)
  {}
  Init_ParameterEvent_new_parameters node(::rcl_interfaces::msg::ParameterEvent::_node_type arg)
  {
    msg_.node = std::move(arg);
    return Init_ParameterEvent_new_parameters(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEvent msg_;
};

class Init_ParameterEvent_stamp
{
public:
  Init_ParameterEvent_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ParameterEvent_node stamp(::rcl_interfaces::msg::ParameterEvent::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_ParameterEvent_node(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::ParameterEvent>()
{
  return rcl_interfaces::msg::builder::Init_ParameterEvent_stamp();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_EVENT__BUILDER_HPP_
