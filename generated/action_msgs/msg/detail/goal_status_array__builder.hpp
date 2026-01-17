// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from action_msgs:msg/GoalStatusArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_status_array.hpp"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__BUILDER_HPP_
#define ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "action_msgs/msg/detail/goal_status_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace action_msgs
{

namespace msg
{

namespace builder
{

class Init_GoalStatusArray_status_list
{
public:
  Init_GoalStatusArray_status_list()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::action_msgs::msg::GoalStatusArray status_list(::action_msgs::msg::GoalStatusArray::_status_list_type arg)
  {
    msg_.status_list = std::move(arg);
    return std::move(msg_);
  }

private:
  ::action_msgs::msg::GoalStatusArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::action_msgs::msg::GoalStatusArray>()
{
  return action_msgs::msg::builder::Init_GoalStatusArray_status_list();
}

}  // namespace action_msgs

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_STATUS_ARRAY__BUILDER_HPP_
