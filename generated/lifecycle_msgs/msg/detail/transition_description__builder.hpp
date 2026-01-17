// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lifecycle_msgs:msg/TransitionDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition_description.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__BUILDER_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lifecycle_msgs/msg/detail/transition_description__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lifecycle_msgs
{

namespace msg
{

namespace builder
{

class Init_TransitionDescription_goal_state
{
public:
  explicit Init_TransitionDescription_goal_state(::lifecycle_msgs::msg::TransitionDescription & msg)
  : msg_(msg)
  {}
  ::lifecycle_msgs::msg::TransitionDescription goal_state(::lifecycle_msgs::msg::TransitionDescription::_goal_state_type arg)
  {
    msg_.goal_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::msg::TransitionDescription msg_;
};

class Init_TransitionDescription_start_state
{
public:
  explicit Init_TransitionDescription_start_state(::lifecycle_msgs::msg::TransitionDescription & msg)
  : msg_(msg)
  {}
  Init_TransitionDescription_goal_state start_state(::lifecycle_msgs::msg::TransitionDescription::_start_state_type arg)
  {
    msg_.start_state = std::move(arg);
    return Init_TransitionDescription_goal_state(msg_);
  }

private:
  ::lifecycle_msgs::msg::TransitionDescription msg_;
};

class Init_TransitionDescription_transition
{
public:
  Init_TransitionDescription_transition()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransitionDescription_start_state transition(::lifecycle_msgs::msg::TransitionDescription::_transition_type arg)
  {
    msg_.transition = std::move(arg);
    return Init_TransitionDescription_start_state(msg_);
  }

private:
  ::lifecycle_msgs::msg::TransitionDescription msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::msg::TransitionDescription>()
{
  return lifecycle_msgs::msg::builder::Init_TransitionDescription_transition();
}

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__BUILDER_HPP_
