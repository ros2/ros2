// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/IntegerRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/integer_range.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/integer_range__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_IntegerRange_step
{
public:
  explicit Init_IntegerRange_step(::rcl_interfaces::msg::IntegerRange & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::IntegerRange step(::rcl_interfaces::msg::IntegerRange::_step_type arg)
  {
    msg_.step = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::IntegerRange msg_;
};

class Init_IntegerRange_to_value
{
public:
  explicit Init_IntegerRange_to_value(::rcl_interfaces::msg::IntegerRange & msg)
  : msg_(msg)
  {}
  Init_IntegerRange_step to_value(::rcl_interfaces::msg::IntegerRange::_to_value_type arg)
  {
    msg_.to_value = std::move(arg);
    return Init_IntegerRange_step(msg_);
  }

private:
  ::rcl_interfaces::msg::IntegerRange msg_;
};

class Init_IntegerRange_from_value
{
public:
  Init_IntegerRange_from_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IntegerRange_to_value from_value(::rcl_interfaces::msg::IntegerRange::_from_value_type arg)
  {
    msg_.from_value = std::move(arg);
    return Init_IntegerRange_to_value(msg_);
  }

private:
  ::rcl_interfaces::msg::IntegerRange msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::IntegerRange>()
{
  return rcl_interfaces::msg::builder::Init_IntegerRange_from_value();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__BUILDER_HPP_
