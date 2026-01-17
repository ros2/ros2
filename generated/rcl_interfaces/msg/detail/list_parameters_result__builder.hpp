// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/ListParametersResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/list_parameters_result.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__LIST_PARAMETERS_RESULT__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__LIST_PARAMETERS_RESULT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/list_parameters_result__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_ListParametersResult_prefixes
{
public:
  explicit Init_ListParametersResult_prefixes(::rcl_interfaces::msg::ListParametersResult & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::ListParametersResult prefixes(::rcl_interfaces::msg::ListParametersResult::_prefixes_type arg)
  {
    msg_.prefixes = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::ListParametersResult msg_;
};

class Init_ListParametersResult_names
{
public:
  Init_ListParametersResult_names()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListParametersResult_prefixes names(::rcl_interfaces::msg::ListParametersResult::_names_type arg)
  {
    msg_.names = std::move(arg);
    return Init_ListParametersResult_prefixes(msg_);
  }

private:
  ::rcl_interfaces::msg::ListParametersResult msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::ListParametersResult>()
{
  return rcl_interfaces::msg::builder::Init_ListParametersResult_names();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__LIST_PARAMETERS_RESULT__BUILDER_HPP_
