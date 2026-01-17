// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:srv/GetParameterTypes.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/get_parameter_types.hpp"


#ifndef RCL_INTERFACES__SRV__DETAIL__GET_PARAMETER_TYPES__BUILDER_HPP_
#define RCL_INTERFACES__SRV__DETAIL__GET_PARAMETER_TYPES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/srv/detail/get_parameter_types__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetParameterTypes_Request_names
{
public:
  Init_GetParameterTypes_Request_names()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rcl_interfaces::srv::GetParameterTypes_Request names(::rcl_interfaces::srv::GetParameterTypes_Request::_names_type arg)
  {
    msg_.names = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::GetParameterTypes_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::GetParameterTypes_Request>()
{
  return rcl_interfaces::srv::builder::Init_GetParameterTypes_Request_names();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetParameterTypes_Response_types
{
public:
  Init_GetParameterTypes_Response_types()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rcl_interfaces::srv::GetParameterTypes_Response types(::rcl_interfaces::srv::GetParameterTypes_Response::_types_type arg)
  {
    msg_.types = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::GetParameterTypes_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::GetParameterTypes_Response>()
{
  return rcl_interfaces::srv::builder::Init_GetParameterTypes_Response_types();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetParameterTypes_Event_response
{
public:
  explicit Init_GetParameterTypes_Event_response(::rcl_interfaces::srv::GetParameterTypes_Event & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::srv::GetParameterTypes_Event response(::rcl_interfaces::srv::GetParameterTypes_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::GetParameterTypes_Event msg_;
};

class Init_GetParameterTypes_Event_request
{
public:
  explicit Init_GetParameterTypes_Event_request(::rcl_interfaces::srv::GetParameterTypes_Event & msg)
  : msg_(msg)
  {}
  Init_GetParameterTypes_Event_response request(::rcl_interfaces::srv::GetParameterTypes_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetParameterTypes_Event_response(msg_);
  }

private:
  ::rcl_interfaces::srv::GetParameterTypes_Event msg_;
};

class Init_GetParameterTypes_Event_info
{
public:
  Init_GetParameterTypes_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetParameterTypes_Event_request info(::rcl_interfaces::srv::GetParameterTypes_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetParameterTypes_Event_request(msg_);
  }

private:
  ::rcl_interfaces::srv::GetParameterTypes_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::GetParameterTypes_Event>()
{
  return rcl_interfaces::srv::builder::Init_GetParameterTypes_Event_info();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__SRV__DETAIL__GET_PARAMETER_TYPES__BUILDER_HPP_
