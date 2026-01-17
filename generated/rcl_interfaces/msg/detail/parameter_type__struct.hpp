// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/ParameterType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_type.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__ParameterType __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__ParameterType __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ParameterType_
{
  using Type = ParameterType_<ContainerAllocator>;

  explicit ParameterType_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit ParameterType_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations
  static constexpr uint8_t PARAMETER_NOT_SET =
    0u;
  static constexpr uint8_t PARAMETER_BOOL =
    1u;
  static constexpr uint8_t PARAMETER_INTEGER =
    2u;
  static constexpr uint8_t PARAMETER_DOUBLE =
    3u;
  static constexpr uint8_t PARAMETER_STRING =
    4u;
  static constexpr uint8_t PARAMETER_BYTE_ARRAY =
    5u;
  static constexpr uint8_t PARAMETER_BOOL_ARRAY =
    6u;
  static constexpr uint8_t PARAMETER_INTEGER_ARRAY =
    7u;
  static constexpr uint8_t PARAMETER_DOUBLE_ARRAY =
    8u;
  static constexpr uint8_t PARAMETER_STRING_ARRAY =
    9u;

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::ParameterType_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::ParameterType_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterType_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterType_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__ParameterType
    std::shared_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__ParameterType
    std::shared_ptr<rcl_interfaces::msg::ParameterType_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ParameterType_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const ParameterType_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ParameterType_

// alias to use template instance with default allocator
using ParameterType =
  rcl_interfaces::msg::ParameterType_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_NOT_SET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_BOOL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_INTEGER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_DOUBLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_STRING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_BYTE_ARRAY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_BOOL_ARRAY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_INTEGER_ARRAY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_DOUBLE_ARRAY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ParameterType_<ContainerAllocator>::PARAMETER_STRING_ARRAY;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_TYPE__STRUCT_HPP_
