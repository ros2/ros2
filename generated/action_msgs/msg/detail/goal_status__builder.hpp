// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from action_msgs:msg/GoalStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_status.hpp"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__BUILDER_HPP_
#define ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "action_msgs/msg/detail/goal_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace action_msgs
{

namespace msg
{

namespace builder
{

class Init_GoalStatus_status
{
public:
  explicit Init_GoalStatus_status(::action_msgs::msg::GoalStatus & msg)
  : msg_(msg)
  {}
  ::action_msgs::msg::GoalStatus status(::action_msgs::msg::GoalStatus::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::action_msgs::msg::GoalStatus msg_;
};

class Init_GoalStatus_goal_info
{
public:
  Init_GoalStatus_goal_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoalStatus_status goal_info(::action_msgs::msg::GoalStatus::_goal_info_type arg)
  {
    msg_.goal_info = std::move(arg);
    return Init_GoalStatus_status(msg_);
  }

private:
  ::action_msgs::msg::GoalStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::action_msgs::msg::GoalStatus>()
{
  return action_msgs::msg::builder::Init_GoalStatus_goal_info();
}

}  // namespace action_msgs

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__BUILDER_HPP_
