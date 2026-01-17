// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lifecycle_msgs:msg/TransitionEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition_event.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__BUILDER_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lifecycle_msgs/msg/detail/transition_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lifecycle_msgs
{

namespace msg
{

namespace builder
{

class Init_TransitionEvent_goal_state
{
public:
  explicit Init_TransitionEvent_goal_state(::lifecycle_msgs::msg::TransitionEvent & msg)
  : msg_(msg)
  {}
  ::lifecycle_msgs::msg::TransitionEvent goal_state(::lifecycle_msgs::msg::TransitionEvent::_goal_state_type arg)
  {
    msg_.goal_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::msg::TransitionEvent msg_;
};

class Init_TransitionEvent_start_state
{
public:
  explicit Init_TransitionEvent_start_state(::lifecycle_msgs::msg::TransitionEvent & msg)
  : msg_(msg)
  {}
  Init_TransitionEvent_goal_state start_state(::lifecycle_msgs::msg::TransitionEvent::_start_state_type arg)
  {
    msg_.start_state = std::move(arg);
    return Init_TransitionEvent_goal_state(msg_);
  }

private:
  ::lifecycle_msgs::msg::TransitionEvent msg_;
};

class Init_TransitionEvent_transition
{
public:
  explicit Init_TransitionEvent_transition(::lifecycle_msgs::msg::TransitionEvent & msg)
  : msg_(msg)
  {}
  Init_TransitionEvent_start_state transition(::lifecycle_msgs::msg::TransitionEvent::_transition_type arg)
  {
    msg_.transition = std::move(arg);
    return Init_TransitionEvent_start_state(msg_);
  }

private:
  ::lifecycle_msgs::msg::TransitionEvent msg_;
};

class Init_TransitionEvent_timestamp
{
public:
  Init_TransitionEvent_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransitionEvent_transition timestamp(::lifecycle_msgs::msg::TransitionEvent::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_TransitionEvent_transition(msg_);
  }

private:
  ::lifecycle_msgs::msg::TransitionEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::msg::TransitionEvent>()
{
  return lifecycle_msgs::msg::builder::Init_TransitionEvent_timestamp();
}

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_EVENT__BUILDER_HPP_
