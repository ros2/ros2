// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from type_description_interfaces:msg/FieldType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/field_type.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD_TYPE__BUILDER_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD_TYPE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "type_description_interfaces/msg/detail/field_type__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace type_description_interfaces
{

namespace msg
{

namespace builder
{

class Init_FieldType_nested_type_name
{
public:
  explicit Init_FieldType_nested_type_name(::type_description_interfaces::msg::FieldType & msg)
  : msg_(msg)
  {}
  ::type_description_interfaces::msg::FieldType nested_type_name(::type_description_interfaces::msg::FieldType::_nested_type_name_type arg)
  {
    msg_.nested_type_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::type_description_interfaces::msg::FieldType msg_;
};

class Init_FieldType_string_capacity
{
public:
  explicit Init_FieldType_string_capacity(::type_description_interfaces::msg::FieldType & msg)
  : msg_(msg)
  {}
  Init_FieldType_nested_type_name string_capacity(::type_description_interfaces::msg::FieldType::_string_capacity_type arg)
  {
    msg_.string_capacity = std::move(arg);
    return Init_FieldType_nested_type_name(msg_);
  }

private:
  ::type_description_interfaces::msg::FieldType msg_;
};

class Init_FieldType_capacity
{
public:
  explicit Init_FieldType_capacity(::type_description_interfaces::msg::FieldType & msg)
  : msg_(msg)
  {}
  Init_FieldType_string_capacity capacity(::type_description_interfaces::msg::FieldType::_capacity_type arg)
  {
    msg_.capacity = std::move(arg);
    return Init_FieldType_string_capacity(msg_);
  }

private:
  ::type_description_interfaces::msg::FieldType msg_;
};

class Init_FieldType_type_id
{
public:
  Init_FieldType_type_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FieldType_capacity type_id(::type_description_interfaces::msg::FieldType::_type_id_type arg)
  {
    msg_.type_id = std::move(arg);
    return Init_FieldType_capacity(msg_);
  }

private:
  ::type_description_interfaces::msg::FieldType msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::type_description_interfaces::msg::FieldType>()
{
  return type_description_interfaces::msg::builder::Init_FieldType_type_id();
}

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD_TYPE__BUILDER_HPP_
