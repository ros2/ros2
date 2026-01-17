// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:srv/DescribeParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/describe_parameters.hpp"


#ifndef RCL_INTERFACES__SRV__DETAIL__DESCRIBE_PARAMETERS__BUILDER_HPP_
#define RCL_INTERFACES__SRV__DETAIL__DESCRIBE_PARAMETERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/srv/detail/describe_parameters__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_DescribeParameters_Request_names
{
public:
  Init_DescribeParameters_Request_names()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rcl_interfaces::srv::DescribeParameters_Request names(::rcl_interfaces::srv::DescribeParameters_Request::_names_type arg)
  {
    msg_.names = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::DescribeParameters_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::DescribeParameters_Request>()
{
  return rcl_interfaces::srv::builder::Init_DescribeParameters_Request_names();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_DescribeParameters_Response_descriptors
{
public:
  Init_DescribeParameters_Response_descriptors()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rcl_interfaces::srv::DescribeParameters_Response descriptors(::rcl_interfaces::srv::DescribeParameters_Response::_descriptors_type arg)
  {
    msg_.descriptors = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::DescribeParameters_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::DescribeParameters_Response>()
{
  return rcl_interfaces::srv::builder::Init_DescribeParameters_Response_descriptors();
}

}  // namespace rcl_interfaces


namespace rcl_interfaces
{

namespace srv
{

namespace builder
{

class Init_DescribeParameters_Event_response
{
public:
  explicit Init_DescribeParameters_Event_response(::rcl_interfaces::srv::DescribeParameters_Event & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::srv::DescribeParameters_Event response(::rcl_interfaces::srv::DescribeParameters_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::srv::DescribeParameters_Event msg_;
};

class Init_DescribeParameters_Event_request
{
public:
  explicit Init_DescribeParameters_Event_request(::rcl_interfaces::srv::DescribeParameters_Event & msg)
  : msg_(msg)
  {}
  Init_DescribeParameters_Event_response request(::rcl_interfaces::srv::DescribeParameters_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_DescribeParameters_Event_response(msg_);
  }

private:
  ::rcl_interfaces::srv::DescribeParameters_Event msg_;
};

class Init_DescribeParameters_Event_info
{
public:
  Init_DescribeParameters_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DescribeParameters_Event_request info(::rcl_interfaces::srv::DescribeParameters_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_DescribeParameters_Event_request(msg_);
  }

private:
  ::rcl_interfaces::srv::DescribeParameters_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::srv::DescribeParameters_Event>()
{
  return rcl_interfaces::srv::builder::Init_DescribeParameters_Event_info();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__SRV__DETAIL__DESCRIBE_PARAMETERS__BUILDER_HPP_
