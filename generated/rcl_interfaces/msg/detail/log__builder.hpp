// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/Log.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/log.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__LOG__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__LOG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/log__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_Log_line
{
public:
  explicit Init_Log_line(::rcl_interfaces::msg::Log & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::Log line(::rcl_interfaces::msg::Log::_line_type arg)
  {
    msg_.line = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::Log msg_;
};

class Init_Log_function
{
public:
  explicit Init_Log_function(::rcl_interfaces::msg::Log & msg)
  : msg_(msg)
  {}
  Init_Log_line function(::rcl_interfaces::msg::Log::_function_type arg)
  {
    msg_.function = std::move(arg);
    return Init_Log_line(msg_);
  }

private:
  ::rcl_interfaces::msg::Log msg_;
};

class Init_Log_file
{
public:
  explicit Init_Log_file(::rcl_interfaces::msg::Log & msg)
  : msg_(msg)
  {}
  Init_Log_function file(::rcl_interfaces::msg::Log::_file_type arg)
  {
    msg_.file = std::move(arg);
    return Init_Log_function(msg_);
  }

private:
  ::rcl_interfaces::msg::Log msg_;
};

class Init_Log_msg
{
public:
  explicit Init_Log_msg(::rcl_interfaces::msg::Log & msg)
  : msg_(msg)
  {}
  Init_Log_file msg(::rcl_interfaces::msg::Log::_msg_type arg)
  {
    msg_.msg = std::move(arg);
    return Init_Log_file(msg_);
  }

private:
  ::rcl_interfaces::msg::Log msg_;
};

class Init_Log_name
{
public:
  explicit Init_Log_name(::rcl_interfaces::msg::Log & msg)
  : msg_(msg)
  {}
  Init_Log_msg name(::rcl_interfaces::msg::Log::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Log_msg(msg_);
  }

private:
  ::rcl_interfaces::msg::Log msg_;
};

class Init_Log_level
{
public:
  explicit Init_Log_level(::rcl_interfaces::msg::Log & msg)
  : msg_(msg)
  {}
  Init_Log_name level(::rcl_interfaces::msg::Log::_level_type arg)
  {
    msg_.level = std::move(arg);
    return Init_Log_name(msg_);
  }

private:
  ::rcl_interfaces::msg::Log msg_;
};

class Init_Log_stamp
{
public:
  Init_Log_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Log_level stamp(::rcl_interfaces::msg::Log::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_Log_level(msg_);
  }

private:
  ::rcl_interfaces::msg::Log msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::Log>()
{
  return rcl_interfaces::msg::builder::Init_Log_stamp();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__LOG__BUILDER_HPP_
