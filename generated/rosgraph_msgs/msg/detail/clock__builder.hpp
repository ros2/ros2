// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rosgraph_msgs:msg/Clock.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosgraph_msgs/msg/clock.hpp"


#ifndef ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__BUILDER_HPP_
#define ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rosgraph_msgs/msg/detail/clock__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rosgraph_msgs
{

namespace msg
{

namespace builder
{

class Init_Clock_clock
{
public:
  Init_Clock_clock()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rosgraph_msgs::msg::Clock clock(::rosgraph_msgs::msg::Clock::_clock_type arg)
  {
    msg_.clock = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rosgraph_msgs::msg::Clock msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rosgraph_msgs::msg::Clock>()
{
  return rosgraph_msgs::msg::builder::Init_Clock_clock();
}

}  // namespace rosgraph_msgs

#endif  // ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__BUILDER_HPP_
