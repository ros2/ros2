// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lifecycle_msgs:msg/State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/state.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__STATE__BUILDER_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lifecycle_msgs/msg/detail/state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lifecycle_msgs
{

namespace msg
{

namespace builder
{

class Init_State_label
{
public:
  explicit Init_State_label(::lifecycle_msgs::msg::State & msg)
  : msg_(msg)
  {}
  ::lifecycle_msgs::msg::State label(::lifecycle_msgs::msg::State::_label_type arg)
  {
    msg_.label = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::msg::State msg_;
};

class Init_State_id
{
public:
  Init_State_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_State_label id(::lifecycle_msgs::msg::State::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_State_label(msg_);
  }

private:
  ::lifecycle_msgs::msg::State msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::msg::State>()
{
  return lifecycle_msgs::msg::builder::Init_State_id();
}

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__STATE__BUILDER_HPP_
