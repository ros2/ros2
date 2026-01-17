// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from action_msgs:srv/CancelGoal.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/srv/cancel_goal.hpp"


#ifndef ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__BUILDER_HPP_
#define ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "action_msgs/srv/detail/cancel_goal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace action_msgs
{

namespace srv
{

namespace builder
{

class Init_CancelGoal_Request_goal_info
{
public:
  Init_CancelGoal_Request_goal_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::action_msgs::srv::CancelGoal_Request goal_info(::action_msgs::srv::CancelGoal_Request::_goal_info_type arg)
  {
    msg_.goal_info = std::move(arg);
    return std::move(msg_);
  }

private:
  ::action_msgs::srv::CancelGoal_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::action_msgs::srv::CancelGoal_Request>()
{
  return action_msgs::srv::builder::Init_CancelGoal_Request_goal_info();
}

}  // namespace action_msgs


namespace action_msgs
{

namespace srv
{

namespace builder
{

class Init_CancelGoal_Response_goals_canceling
{
public:
  explicit Init_CancelGoal_Response_goals_canceling(::action_msgs::srv::CancelGoal_Response & msg)
  : msg_(msg)
  {}
  ::action_msgs::srv::CancelGoal_Response goals_canceling(::action_msgs::srv::CancelGoal_Response::_goals_canceling_type arg)
  {
    msg_.goals_canceling = std::move(arg);
    return std::move(msg_);
  }

private:
  ::action_msgs::srv::CancelGoal_Response msg_;
};

class Init_CancelGoal_Response_return_code
{
public:
  Init_CancelGoal_Response_return_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CancelGoal_Response_goals_canceling return_code(::action_msgs::srv::CancelGoal_Response::_return_code_type arg)
  {
    msg_.return_code = std::move(arg);
    return Init_CancelGoal_Response_goals_canceling(msg_);
  }

private:
  ::action_msgs::srv::CancelGoal_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::action_msgs::srv::CancelGoal_Response>()
{
  return action_msgs::srv::builder::Init_CancelGoal_Response_return_code();
}

}  // namespace action_msgs


namespace action_msgs
{

namespace srv
{

namespace builder
{

class Init_CancelGoal_Event_response
{
public:
  explicit Init_CancelGoal_Event_response(::action_msgs::srv::CancelGoal_Event & msg)
  : msg_(msg)
  {}
  ::action_msgs::srv::CancelGoal_Event response(::action_msgs::srv::CancelGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::action_msgs::srv::CancelGoal_Event msg_;
};

class Init_CancelGoal_Event_request
{
public:
  explicit Init_CancelGoal_Event_request(::action_msgs::srv::CancelGoal_Event & msg)
  : msg_(msg)
  {}
  Init_CancelGoal_Event_response request(::action_msgs::srv::CancelGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_CancelGoal_Event_response(msg_);
  }

private:
  ::action_msgs::srv::CancelGoal_Event msg_;
};

class Init_CancelGoal_Event_info
{
public:
  Init_CancelGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CancelGoal_Event_request info(::action_msgs::srv::CancelGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_CancelGoal_Event_request(msg_);
  }

private:
  ::action_msgs::srv::CancelGoal_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::action_msgs::srv::CancelGoal_Event>()
{
  return action_msgs::srv::builder::Init_CancelGoal_Event_info();
}

}  // namespace action_msgs

#endif  // ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__BUILDER_HPP_
