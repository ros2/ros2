// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from type_description_interfaces:msg/TypeSource.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/type_source.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__STRUCT_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__type_description_interfaces__msg__TypeSource __attribute__((deprecated))
#else
# define DEPRECATED__type_description_interfaces__msg__TypeSource __declspec(deprecated)
#endif

namespace type_description_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TypeSource_
{
  using Type = TypeSource_<ContainerAllocator>;

  explicit TypeSource_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type_name = "";
      this->encoding = "";
      this->raw_file_contents = "";
    }
  }

  explicit TypeSource_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : type_name(_alloc),
    encoding(_alloc),
    raw_file_contents(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type_name = "";
      this->encoding = "";
      this->raw_file_contents = "";
    }
  }

  // field types and members
  using _type_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _type_name_type type_name;
  using _encoding_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _encoding_type encoding;
  using _raw_file_contents_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _raw_file_contents_type raw_file_contents;

  // setters for named parameter idiom
  Type & set__type_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->type_name = _arg;
    return *this;
  }
  Type & set__encoding(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->encoding = _arg;
    return *this;
  }
  Type & set__raw_file_contents(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->raw_file_contents = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    type_description_interfaces::msg::TypeSource_<ContainerAllocator> *;
  using ConstRawPtr =
    const type_description_interfaces::msg::TypeSource_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::msg::TypeSource_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::msg::TypeSource_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__type_description_interfaces__msg__TypeSource
    std::shared_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__type_description_interfaces__msg__TypeSource
    std::shared_ptr<type_description_interfaces::msg::TypeSource_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TypeSource_ & other) const
  {
    if (this->type_name != other.type_name) {
      return false;
    }
    if (this->encoding != other.encoding) {
      return false;
    }
    if (this->raw_file_contents != other.raw_file_contents) {
      return false;
    }
    return true;
  }
  bool operator!=(const TypeSource_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TypeSource_

// alias to use template instance with default allocator
using TypeSource =
  type_description_interfaces::msg::TypeSource_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__STRUCT_HPP_
