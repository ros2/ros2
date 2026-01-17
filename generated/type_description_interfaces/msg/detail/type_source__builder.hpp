// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from type_description_interfaces:msg/TypeSource.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/type_source.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__BUILDER_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "type_description_interfaces/msg/detail/type_source__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace type_description_interfaces
{

namespace msg
{

namespace builder
{

class Init_TypeSource_raw_file_contents
{
public:
  explicit Init_TypeSource_raw_file_contents(::type_description_interfaces::msg::TypeSource & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::msg::TypeSource raw_file_contents(::type_description_interfaces::msg::TypeSource::_raw_file_contents_type arg)
  {
    msg_.raw_file_contents = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::msg::TypeSource msg_;
};

class Init_TypeSource_encoding
{
public:
  explicit Init_TypeSource_encoding(::type_description_interfaces::msg::TypeSource & msg)
  : msg_(msg)
  {}
  Init_TypeSource_raw_file_contents encoding(::type_description_interfaces::msg::TypeSource::_encoding_type arg)
  {
    msg_.encoding = std::move(arg);
    return Init_TypeSource_raw_file_contents(msg_);
  }

private:
  ::type_description_interfaces::msg::TypeSource msg_;
};

class Init_TypeSource_type_name
{
public:
  Init_TypeSource_type_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TypeSource_encoding type_name(::type_description_interfaces::msg::TypeSource::_type_name_type arg)
  {
    msg_.type_name = std::move(arg);
    return Init_TypeSource_encoding(msg_);
  }

private:
  ::type_description_interfaces::msg::TypeSource msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::msg::TypeSource>()
{
  return type_description_interfaces::msg::builder::Init_TypeSource_type_name();
}

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__BUILDER_HPP_
