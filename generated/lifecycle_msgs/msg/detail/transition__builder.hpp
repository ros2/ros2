// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lifecycle_msgs:msg/Transition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION__BUILDER_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lifecycle_msgs/msg/detail/transition__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lifecycle_msgs
{

namespace msg
{

namespace builder
{

class Init_Transition_label
{
public:
  explicit Init_Transition_label(::lifecycle_msgs::msg::Transition & msg)
  : msg_(msg)
  {}
  ::lifecycle_msgs::msg::Transition label(::lifecycle_msgs::msg::Transition::_label_type arg)
  {
    msg_.label = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::msg::Transition msg_;
};

class Init_Transition_id
{
public:
  Init_Transition_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Transition_label id(::lifecycle_msgs::msg::Transition::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Transition_label(msg_);
  }

private:
  ::lifecycle_msgs::msg::Transition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::msg::Transition>()
{
  return lifecycle_msgs::msg::builder::Init_Transition_id();
}

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION__BUILDER_HPP_
