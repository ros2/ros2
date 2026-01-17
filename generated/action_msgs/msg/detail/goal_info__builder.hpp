// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from action_msgs:msg/GoalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_info.hpp"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_INFO__BUILDER_HPP_
#define ACTION_MSGS__MSG__DETAIL__GOAL_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "action_msgs/msg/detail/goal_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace action_msgs
{

namespace msg
{

namespace builder
{

class Init_GoalInfo_stamp
{
public:
  explicit Init_GoalInfo_stamp(::action_msgs::msg::GoalInfo & msg)
  : msg_(msg)
  {}
  ::action_msgs::msg::GoalInfo stamp(::action_msgs::msg::GoalInfo::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::action_msgs::msg::GoalInfo msg_;
};

class Init_GoalInfo_goal_id
{
public:
  Init_GoalInfo_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoalInfo_stamp goal_id(::action_msgs::msg::GoalInfo::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_GoalInfo_stamp(msg_);
  }

private:
  ::action_msgs::msg::GoalInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::action_msgs::msg::GoalInfo>()
{
  return action_msgs::msg::builder::Init_GoalInfo_goal_id();
}

}  // namespace action_msgs

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_INFO__BUILDER_HPP_
