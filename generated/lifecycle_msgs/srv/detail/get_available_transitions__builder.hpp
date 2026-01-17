// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lifecycle_msgs:srv/GetAvailableTransitions.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/get_available_transitions.hpp"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__BUILDER_HPP_
#define LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lifecycle_msgs/srv/detail/get_available_transitions__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lifecycle_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::srv::GetAvailableTransitions_Request>()
{
  return ::lifecycle_msgs::srv::GetAvailableTransitions_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace lifecycle_msgs


namespace lifecycle_msgs
{

namespace srv
{

namespace builder
{

class Init_GetAvailableTransitions_Response_available_transitions
{
public:
  Init_GetAvailableTransitions_Response_available_transitions()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lifecycle_msgs::srv::GetAvailableTransitions_Response available_transitions(::lifecycle_msgs::srv::GetAvailableTransitions_Response::_available_transitions_type arg)
  {
    msg_.available_transitions = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableTransitions_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::srv::GetAvailableTransitions_Response>()
{
  return lifecycle_msgs::srv::builder::Init_GetAvailableTransitions_Response_available_transitions();
}

}  // namespace lifecycle_msgs


namespace lifecycle_msgs
{

namespace srv
{

namespace builder
{

class Init_GetAvailableTransitions_Event_response
{
public:
  explicit Init_GetAvailableTransitions_Event_response(::lifecycle_msgs::srv::GetAvailableTransitions_Event & msg)
  : msg_(msg)
  {}
  ::lifecycle_msgs::srv::GetAvailableTransitions_Event response(::lifecycle_msgs::srv::GetAvailableTransitions_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableTransitions_Event msg_;
};

class Init_GetAvailableTransitions_Event_request
{
public:
  explicit Init_GetAvailableTransitions_Event_request(::lifecycle_msgs::srv::GetAvailableTransitions_Event & msg)
  : msg_(msg)
  {}
  Init_GetAvailableTransitions_Event_response request(::lifecycle_msgs::srv::GetAvailableTransitions_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetAvailableTransitions_Event_response(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableTransitions_Event msg_;
};

class Init_GetAvailableTransitions_Event_info
{
public:
  Init_GetAvailableTransitions_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetAvailableTransitions_Event_request info(::lifecycle_msgs::srv::GetAvailableTransitions_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetAvailableTransitions_Event_request(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableTransitions_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::srv::GetAvailableTransitions_Event>()
{
  return lifecycle_msgs::srv::builder::Init_GetAvailableTransitions_Event_info();
}

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__BUILDER_HPP_
