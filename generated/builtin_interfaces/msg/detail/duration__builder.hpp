// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from builtin_interfaces:msg/Duration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "builtin_interfaces/msg/duration.hpp"


#ifndef BUILTIN_INTERFACES__MSG__DETAIL__DURATION__BUILDER_HPP_
#define BUILTIN_INTERFACES__MSG__DETAIL__DURATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "builtin_interfaces/msg/detail/duration__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace builtin_interfaces
{

namespace msg
{

namespace builder
{

class Init_Duration_nanosec
{
public:
  explicit Init_Duration_nanosec(::builtin_interfaces::msg::Duration & msg)
  : msg_(msg)
  {}
  ::builtin_interfaces::msg::Duration nanosec(::builtin_interfaces::msg::Duration::_nanosec_type arg)
  {
    msg_.nanosec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::builtin_interfaces::msg::Duration msg_;
};

class Init_Duration_sec
{
public:
  Init_Duration_sec()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Duration_nanosec sec(::builtin_interfaces::msg::Duration::_sec_type arg)
  {
    msg_.sec = std::move(arg);
    return Init_Duration_nanosec(msg_);
  }

private:
  ::builtin_interfaces::msg::Duration msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::builtin_interfaces::msg::Duration>()
{
  return builtin_interfaces::msg::builder::Init_Duration_sec();
}

}  // namespace builtin_interfaces

#endif  // BUILTIN_INTERFACES__MSG__DETAIL__DURATION__BUILDER_HPP_
