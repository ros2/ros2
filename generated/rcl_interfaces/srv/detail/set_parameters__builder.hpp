// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:srv/SetParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/set_parameters.hpp"


#ifndef RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS__BUILDER_HPP_
#define RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/srv/detail/set_parameters__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetParameters_Request_parameters
{
public:
  Init_SetParameters_Request_parameters()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rcl_interfaces::srv::SetParameters_Request parameters(::rcl_interfaces::srv::SetParameters_Request::_parameters_type arg)
  {
    msg_.parameters = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::SetParameters_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::SetParameters_Request>()
{
  return rcl_interfaces::srv::builder::Init_SetParameters_Request_parameters();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetParameters_Response_results
{
public:
  Init_SetParameters_Response_results()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rcl_interfaces::srv::SetParameters_Response results(::rcl_interfaces::srv::SetParameters_Response::_results_type arg)
  {
    msg_.results = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::SetParameters_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::SetParameters_Response>()
{
  return rcl_interfaces::srv::builder::Init_SetParameters_Response_results();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetParameters_Event_response
{
public:
  explicit Init_SetParameters_Event_response(::rcl_interfaces::srv::SetParameters_Event & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::srv::SetParameters_Event response(::rcl_interfaces::srv::SetParameters_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::SetParameters_Event msg_;
};

class Init_SetParameters_Event_request
{
public:
  explicit Init_SetParameters_Event_request(::rcl_interfaces::srv::SetParameters_Event & msg)
  : msg_(msg)
  {}
  Init_SetParameters_Event_response request(::rcl_interfaces::srv::SetParameters_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetParameters_Event_response(msg_);
  }

private:
  ::rcl_interfaces::srv::SetParameters_Event msg_;
};

class Init_SetParameters_Event_info
{
public:
  Init_SetParameters_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetParameters_Event_request info(::rcl_interfaces::srv::SetParameters_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetParameters_Event_request(msg_);
  }

private:
  ::rcl_interfaces::srv::SetParameters_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::SetParameters_Event>()
{
  return rcl_interfaces::srv::builder::Init_SetParameters_Event_info();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS__BUILDER_HPP_
