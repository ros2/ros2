// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/SetLoggerLevelsResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/set_logger_levels_result.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/set_logger_levels_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_SetLoggerLevelsResult_reason
{
public:
  explicit Init_SetLoggerLevelsResult_reason(::rcl_interfaces::msg::SetLoggerLevelsResult & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::SetLoggerLevelsResult reason(::rcl_interfaces::msg::SetLoggerLevelsResult::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::SetLoggerLevelsResult msg_;
};

class Init_SetLoggerLevelsResult_successful
{
public:
  Init_SetLoggerLevelsResult_successful()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetLoggerLevelsResult_reason successful(::rcl_interfaces::msg::SetLoggerLevelsResult::_successful_type arg)
  {
    msg_.successful = std::move(arg);
    return Init_SetLoggerLevelsResult_reason(msg_);
  }

private:
  ::rcl_interfaces::msg::SetLoggerLevelsResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::SetLoggerLevelsResult>()
{
  return rcl_interfaces::msg::builder::Init_SetLoggerLevelsResult_successful();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__BUILDER_HPP_
