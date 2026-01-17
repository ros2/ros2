// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/FloatingPointRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/floating_point_range.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__FLOATING_POINT_RANGE__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__FLOATING_POINT_RANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/floating_point_range__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_FloatingPointRange_step
{
public:
  explicit Init_FloatingPointRange_step(::rcl_interfaces::msg::FloatingPointRange & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::FloatingPointRange step(::rcl_interfaces::msg::FloatingPointRange::_step_type arg)
  {
    msg_.step = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::FloatingPointRange msg_;
};

class Init_FloatingPointRange_to_value
{
public:
  explicit Init_FloatingPointRange_to_value(::rcl_interfaces::msg::FloatingPointRange & msg)
  : msg_(msg)
  {}
  Init_FloatingPointRange_step to_value(::rcl_interfaces::msg::FloatingPointRange::_to_value_type arg)
  {
    msg_.to_value = std::move(arg);
    return Init_FloatingPointRange_step(msg_);
  }

private:
  ::rcl_interfaces::msg::FloatingPointRange msg_;
};

class Init_FloatingPointRange_from_value
{
public:
  Init_FloatingPointRange_from_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FloatingPointRange_to_value from_value(::rcl_interfaces::msg::FloatingPointRange::_from_value_type arg)
  {
    msg_.from_value = std::move(arg);
    return Init_FloatingPointRange_to_value(msg_);
  }

private:
  ::rcl_interfaces::msg::FloatingPointRange msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::FloatingPointRange>()
{
  return rcl_interfaces::msg::builder::Init_FloatingPointRange_from_value();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__FLOATING_POINT_RANGE__BUILDER_HPP_
