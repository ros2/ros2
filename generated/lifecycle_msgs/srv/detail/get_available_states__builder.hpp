// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lifecycle_msgs:srv/GetAvailableStates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/get_available_states.hpp"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_STATES__BUILDER_HPP_
#define LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_STATES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lifecycle_msgs/srv/detail/get_available_states__struct.hpp"
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
auto build<::lifecycle_msgs::srv::GetAvailableStates_Request>()
{
  return ::lifecycle_msgs::srv::GetAvailableStates_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace lifecycle_msgs


namespace lifecycle_msgs
{

namespace srv
{

namespace builder
{

class Init_GetAvailableStates_Response_available_states
{
public:
  Init_GetAvailableStates_Response_available_states()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lifecycle_msgs::srv::GetAvailableStates_Response available_states(::lifecycle_msgs::srv::GetAvailableStates_Response::_available_states_type arg)
  {
    msg_.available_states = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableStates_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::srv::GetAvailableStates_Response>()
{
  return lifecycle_msgs::srv::builder::Init_GetAvailableStates_Response_available_states();
}

}  // namespace lifecycle_msgs


namespace lifecycle_msgs
{

namespace srv
{

namespace builder
{

class Init_GetAvailableStates_Event_response
{
public:
  explicit Init_GetAvailableStates_Event_response(::lifecycle_msgs::srv::GetAvailableStates_Event & msg)
  : msg_(msg)
  {}
  ::lifecycle_msgs::srv::GetAvailableStates_Event response(::lifecycle_msgs::srv::GetAvailableStates_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableStates_Event msg_;
};

class Init_GetAvailableStates_Event_request
{
public:
  explicit Init_GetAvailableStates_Event_request(::lifecycle_msgs::srv::GetAvailableStates_Event & msg)
  : msg_(msg)
  {}
  Init_GetAvailableStates_Event_response request(::lifecycle_msgs::srv::GetAvailableStates_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetAvailableStates_Event_response(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableStates_Event msg_;
};

class Init_GetAvailableStates_Event_info
{
public:
  Init_GetAvailableStates_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetAvailableStates_Event_request info(::lifecycle_msgs::srv::GetAvailableStates_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetAvailableStates_Event_request(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetAvailableStates_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::srv::GetAvailableStates_Event>()
{
  return lifecycle_msgs::srv::builder::Init_GetAvailableStates_Event_info();
}

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_STATES__BUILDER_HPP_
