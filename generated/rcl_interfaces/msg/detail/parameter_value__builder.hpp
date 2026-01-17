// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rcl_interfaces:msg/ParameterValue.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_value.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__BUILDER_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rcl_interfaces/msg/detail/parameter_value__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rcl_interfaces
{

namespace msg
{

namespace builder
{

class Init_ParameterValue_string_array_value
{
public:
  explicit Init_ParameterValue_string_array_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  ::rcl_interfaces::msg::ParameterValue string_array_value(::rcl_interfaces::msg::ParameterValue::_string_array_value_type arg)
  {
    msg_.string_array_value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_double_array_value
{
public:
  explicit Init_ParameterValue_double_array_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_string_array_value double_array_value(::rcl_interfaces::msg::ParameterValue::_double_array_value_type arg)
  {
    msg_.double_array_value = std::move(arg);
    return Init_ParameterValue_string_array_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_integer_array_value
{
public:
  explicit Init_ParameterValue_integer_array_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_double_array_value integer_array_value(::rcl_interfaces::msg::ParameterValue::_integer_array_value_type arg)
  {
    msg_.integer_array_value = std::move(arg);
    return Init_ParameterValue_double_array_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_bool_array_value
{
public:
  explicit Init_ParameterValue_bool_array_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_integer_array_value bool_array_value(::rcl_interfaces::msg::ParameterValue::_bool_array_value_type arg)
  {
    msg_.bool_array_value = std::move(arg);
    return Init_ParameterValue_integer_array_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_byte_array_value
{
public:
  explicit Init_ParameterValue_byte_array_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_bool_array_value byte_array_value(::rcl_interfaces::msg::ParameterValue::_byte_array_value_type arg)
  {
    msg_.byte_array_value = std::move(arg);
    return Init_ParameterValue_bool_array_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_string_value
{
public:
  explicit Init_ParameterValue_string_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_byte_array_value string_value(::rcl_interfaces::msg::ParameterValue::_string_value_type arg)
  {
    msg_.string_value = std::move(arg);
    return Init_ParameterValue_byte_array_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_double_value
{
public:
  explicit Init_ParameterValue_double_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_string_value double_value(::rcl_interfaces::msg::ParameterValue::_double_value_type arg)
  {
    msg_.double_value = std::move(arg);
    return Init_ParameterValue_string_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_integer_value
{
public:
  explicit Init_ParameterValue_integer_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_double_value integer_value(::rcl_interfaces::msg::ParameterValue::_integer_value_type arg)
  {
    msg_.integer_value = std::move(arg);
    return Init_ParameterValue_double_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_bool_value
{
public:
  explicit Init_ParameterValue_bool_value(::rcl_interfaces::msg::ParameterValue & msg)
  : msg_(msg)
  {}
  Init_ParameterValue_integer_value bool_value(::rcl_interfaces::msg::ParameterValue::_bool_value_type arg)
  {
    msg_.bool_value = std::move(arg);
    return Init_ParameterValue_integer_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

class Init_ParameterValue_type
{
public:
  Init_ParameterValue_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ParameterValue_bool_value type(::rcl_interfaces::msg::ParameterValue::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_ParameterValue_bool_value(msg_);
  }

private:
  ::rcl_interfaces::msg::ParameterValue msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rcl_interfaces::msg::ParameterValue>()
{
  return rcl_interfaces::msg::builder::Init_ParameterValue_type();
}

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__BUILDER_HPP_
