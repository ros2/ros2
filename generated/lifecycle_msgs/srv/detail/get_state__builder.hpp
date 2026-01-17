// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lifecycle_msgs:srv/GetState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/get_state.hpp"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__GET_STATE__BUILDER_HPP_
#define LIFECYCLE_MSGS__SRV__DETAIL__GET_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lifecycle_msgs/srv/detail/get_state__struct.hpp"
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
auto build<::lifecycle_msgs::srv::GetState_Request>()
{
  return ::lifecycle_msgs::srv::GetState_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace lifecycle_msgs


namespace lifecycle_msgs
{

namespace srv
{

namespace builder
{

class Init_GetState_Response_current_state
{
public:
  Init_GetState_Response_current_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lifecycle_msgs::srv::GetState_Response current_state(::lifecycle_msgs::srv::GetState_Response::_current_state_type arg)
  {
    msg_.current_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetState_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::srv::GetState_Response>()
{
  return lifecycle_msgs::srv::builder::Init_GetState_Response_current_state();
}

}  // namespace lifecycle_msgs


namespace lifecycle_msgs
{

namespace srv
{

namespace builder
{

class Init_GetState_Event_response
{
public:
  explicit Init_GetState_Event_response(::lifecycle_msgs::srv::GetState_Event & msg)
  : msg_(msg)
  {}
  ::lifecycle_msgs::srv::GetState_Event response(::lifecycle_msgs::srv::GetState_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetState_Event msg_;
};

class Init_GetState_Event_request
{
public:
  explicit Init_GetState_Event_request(::lifecycle_msgs::srv::GetState_Event & msg)
  : msg_(msg)
  {}
  Init_GetState_Event_response request(::lifecycle_msgs::srv::GetState_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetState_Event_response(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetState_Event msg_;
};

class Init_GetState_Event_info
{
public:
  Init_GetState_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetState_Event_request info(::lifecycle_msgs::srv::GetState_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetState_Event_request(msg_);
  }

private:
  ::lifecycle_msgs::srv::GetState_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lifecycle_msgs::srv::GetState_Event>()
{
  return lifecycle_msgs::srv::builder::Init_GetState_Event_info();
}

}  // namespace lifecycle_msgs

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__GET_STATE__BUILDER_HPP_
