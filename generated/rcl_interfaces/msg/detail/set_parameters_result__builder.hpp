// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/SetParametersResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/set_parameters_result.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__SET_PARAMETERS_RESULT__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__SET_PARAMETERS_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/set_parameters_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_SetParametersResult_reason
{
public:
  explicit Init_SetParametersResult_reason(::rcl_interfaces::msg::SetParametersResult & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::SetParametersResult reason(::rcl_interfaces::msg::SetParametersResult::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::SetParametersResult msg_;
};

class Init_SetParametersResult_successful
{
public:
  Init_SetParametersResult_successful()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetParametersResult_reason successful(::rcl_interfaces::msg::SetParametersResult::_successful_type arg)
  {
    msg_.successful = std::move(arg);
    return Init_SetParametersResult_reason(msg_);
  }

private:
  ::rcl_interfaces::msg::SetParametersResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::SetParametersResult>()
{
  return rcl_interfaces::msg::builder::Init_SetParametersResult_successful();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__SET_PARAMETERS_RESULT__BUILDER_HPP_
