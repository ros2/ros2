// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from type_description_interfaces:srv/GetTypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/srv/get_type_description.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__BUILDER_HPP_
#define TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "type_description_interfaces/srv/detail/get_type_description__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace type_description_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetTypeDescription_Request_include_type_sources
{
public:
  explicit Init_GetTypeDescription_Request_include_type_sources(::type_description_interfaces::srv::GetTypeDescription_Request & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::srv::GetTypeDescription_Request include_type_sources(::type_description_interfaces::srv::GetTypeDescription_Request::_include_type_sources_type arg)
  {
    msg_.include_type_sources = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Request msg_;
};

class Init_GetTypeDescription_Request_type_hash
{
public:
  explicit Init_GetTypeDescription_Request_type_hash(::type_description_interfaces::srv::GetTypeDescription_Request & msg)
  : msg_(msg)
  {}
  Init_GetTypeDescription_Request_include_type_sources type_hash(::type_description_interfaces::srv::GetTypeDescription_Request::_type_hash_type arg)
  {
    msg_.type_hash = std::move(arg);
    return Init_GetTypeDescription_Request_include_type_sources(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Request msg_;
};

class Init_GetTypeDescription_Request_type_name
{
public:
  Init_GetTypeDescription_Request_type_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetTypeDescription_Request_type_hash type_name(::type_description_interfaces::srv::GetTypeDescription_Request::_type_name_type arg)
  {
    msg_.type_name = std::move(arg);
    return Init_GetTypeDescription_Request_type_hash(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::srv::GetTypeDescription_Request>()
{
  return type_description_interfaces::srv::builder::Init_GetTypeDescription_Request_type_name();
}

}  // namespace type_description_interfaces


namespace type_description_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetTypeDescription_Response_extra_information
{
public:
  explicit Init_GetTypeDescription_Response_extra_information(::type_description_interfaces::srv::GetTypeDescription_Response & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::srv::GetTypeDescription_Response extra_information(::type_description_interfaces::srv::GetTypeDescription_Response::_extra_information_type arg)
  {
    msg_.extra_information = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Response msg_;
};

class Init_GetTypeDescription_Response_type_sources
{
public:
  explicit Init_GetTypeDescription_Response_type_sources(::type_description_interfaces::srv::GetTypeDescription_Response & msg)
  : msg_(msg)
  {}
  Init_GetTypeDescription_Response_extra_information type_sources(::type_description_interfaces::srv::GetTypeDescription_Response::_type_sources_type arg)
  {
    msg_.type_sources = std::move(arg);
    return Init_GetTypeDescription_Response_extra_information(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Response msg_;
};

class Init_GetTypeDescription_Response_type_description
{
public:
  explicit Init_GetTypeDescription_Response_type_description(::type_description_interfaces::srv::GetTypeDescription_Response & msg)
  : msg_(msg)
  {}
  Init_GetTypeDescription_Response_type_sources type_description(::type_description_interfaces::srv::GetTypeDescription_Response::_type_description_type arg)
  {
    msg_.type_description = std::move(arg);
    return Init_GetTypeDescription_Response_type_sources(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Response msg_;
};

class Init_GetTypeDescription_Response_failure_reason
{
public:
  explicit Init_GetTypeDescription_Response_failure_reason(::type_description_interfaces::srv::GetTypeDescription_Response & msg)
  : msg_(msg)
  {}
  Init_GetTypeDescription_Response_type_description failure_reason(::type_description_interfaces::srv::GetTypeDescription_Response::_failure_reason_type arg)
  {
    msg_.failure_reason = std::move(arg);
    return Init_GetTypeDescription_Response_type_description(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Response msg_;
};

class Init_GetTypeDescription_Response_successful
{
public:
  Init_GetTypeDescription_Response_successful()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetTypeDescription_Response_failure_reason successful(::type_description_interfaces::srv::GetTypeDescription_Response::_successful_type arg)
  {
    msg_.successful = std::move(arg);
    return Init_GetTypeDescription_Response_failure_reason(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::srv::GetTypeDescription_Response>()
{
  return type_description_interfaces::srv::builder::Init_GetTypeDescription_Response_successful();
}

}  // namespace type_description_interfaces


namespace type_description_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetTypeDescription_Event_response
{
public:
  explicit Init_GetTypeDescription_Event_response(::type_description_interfaces::srv::GetTypeDescription_Event & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::srv::GetTypeDescription_Event response(::type_description_interfaces::srv::GetTypeDescription_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Event msg_;
};

class Init_GetTypeDescription_Event_request
{
public:
  explicit Init_GetTypeDescription_Event_request(::type_description_interfaces::srv::GetTypeDescription_Event & msg)
  : msg_(msg)
  {}
  Init_GetTypeDescription_Event_response request(::type_description_interfaces::srv::GetTypeDescription_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetTypeDescription_Event_response(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Event msg_;
};

class Init_GetTypeDescription_Event_info
{
public:
  Init_GetTypeDescription_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetTypeDescription_Event_request info(::type_description_interfaces::srv::GetTypeDescription_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetTypeDescription_Event_request(msg_);
  }

private:
  ::type_description_interfaces::srv::GetTypeDescription_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::srv::GetTypeDescription_Event>()
{
  return type_description_interfaces::srv::builder::Init_GetTypeDescription_Event_info();
}

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__BUILDER_HPP_
