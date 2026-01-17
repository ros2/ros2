// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from builtin_interfaces:msg/Time.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "builtin_interfaces/msg/time.hpp"


#ifndef BUILTIN_INTERFACES__MSG__DETAIL__TIME__BUILDER_HPP_
#define BUILTIN_INTERFACES__MSG__DETAIL__TIME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "builtin_interfaces/msg/detail/time__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace builtin_interfaces
{

namespace msg
{

namespace builder
{

class Init_Time_nanosec
{
public:
  explicit Init_Time_nanosec(::builtin_interfaces::msg::Time & msg)
  : msg_(msg)
  {}
  ::builtin_interfaces::msg::Time nanosec(::builtin_interfaces::msg::Time::_nanosec_type arg)
  {
    msg_.nanosec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::builtin_interfaces::msg::Time msg_;
};

class Init_Time_sec
{
public:
  Init_Time_sec()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Time_nanosec sec(::builtin_interfaces::msg::Time::_sec_type arg)
  {
    msg_.sec = std::move(arg);
    return Init_Time_nanosec(msg_);
  }

private:
  ::builtin_interfaces::msg::Time msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::builtin_interfaces::msg::Time>()
{
  return builtin_interfaces::msg::builder::Init_Time_sec();
}

}  // namespace builtin_interfaces

#endif  // BUILTIN_INTERFACES__MSG__DETAIL__TIME__BUILDER_HPP_
