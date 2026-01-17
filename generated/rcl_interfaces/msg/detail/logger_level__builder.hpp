// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/LoggerLevel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/logger_level.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/logger_level__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_LoggerLevel_level
{
public:
  explicit Init_LoggerLevel_level(::rcl_interfaces::msg::LoggerLevel & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::LoggerLevel level(::rcl_interfaces::msg::LoggerLevel::_level_type arg)
  {
    msg_.level = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::LoggerLevel msg_;
};

class Init_LoggerLevel_name
{
public:
  Init_LoggerLevel_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LoggerLevel_level name(::rcl_interfaces::msg::LoggerLevel::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_LoggerLevel_level(msg_);
  }

private:
  ::rcl_interfaces::msg::LoggerLevel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::LoggerLevel>()
{
  return rcl_interfaces::msg::builder::Init_LoggerLevel_name();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__LOGGER_LEVEL__BUILDER_HPP_
