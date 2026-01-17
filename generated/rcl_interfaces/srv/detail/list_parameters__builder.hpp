// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:srv/ListParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/list_parameters.hpp"


#ifndef RCL_INTERFACES__SRV__DETAIL__LIST_PARAMETERS__BUILDER_HPP_
#define RCL_INTERFACES__SRV__DETAIL__LIST_PARAMETERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/srv/detail/list_parameters__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListParameters_Request_depth
{
public:
  explicit Init_ListParameters_Request_depth(::rcl_interfaces::srv::ListParameters_Request & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::srv::ListParameters_Request depth(::rcl_interfaces::srv::ListParameters_Request::_depth_type arg)
  {
    msg_.depth = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::ListParameters_Request msg_;
};

class Init_ListParameters_Request_prefixes
{
public:
  Init_ListParameters_Request_prefixes()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListParameters_Request_depth prefixes(::rcl_interfaces::srv::ListParameters_Request::_prefixes_type arg)
  {
    msg_.prefixes = std::move(arg);
    return Init_ListParameters_Request_depth(msg_);
  }

private:
  ::rcl_interfaces::srv::ListParameters_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::ListParameters_Request>()
{
  return rcl_interfaces::srv::builder::Init_ListParameters_Request_prefixes();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListParameters_Response_result
{
public:
  Init_ListParameters_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rcl_interfaces::srv::ListParameters_Response result(::rcl_interfaces::srv::ListParameters_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::ListParameters_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::ListParameters_Response>()
{
  return rcl_interfaces::srv::builder::Init_ListParameters_Response_result();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListParameters_Event_response
{
public:
  explicit Init_ListParameters_Event_response(::rcl_interfaces::srv::ListParameters_Event & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::srv::ListParameters_Event response(::rcl_interfaces::srv::ListParameters_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::ListParameters_Event msg_;
};

class Init_ListParameters_Event_request
{
public:
  explicit Init_ListParameters_Event_request(::rcl_interfaces::srv::ListParameters_Event & msg)
  : msg_(msg)
  {}
  Init_ListParameters_Event_response request(::rcl_interfaces::srv::ListParameters_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_ListParameters_Event_response(msg_);
  }

private:
  ::rcl_interfaces::srv::ListParameters_Event msg_;
};

class Init_ListParameters_Event_info
{
public:
  Init_ListParameters_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListParameters_Event_request info(::rcl_interfaces::srv::ListParameters_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_ListParameters_Event_request(msg_);
  }

private:
  ::rcl_interfaces::srv::ListParameters_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::ListParameters_Event>()
{
  return rcl_interfaces::srv::builder::Init_ListParameters_Event_info();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__SRV__DETAIL__LIST_PARAMETERS__BUILDER_HPP_
