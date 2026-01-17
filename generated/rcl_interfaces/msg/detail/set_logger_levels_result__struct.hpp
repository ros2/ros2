// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/SetLoggerLevelsResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/set_logger_levels_result.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__SetLoggerLevelsResult __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__SetLoggerLevelsResult __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SetLoggerLevelsResult_
{
  using Type = SetLoggerLevelsResult_<ContainerAllocator>;

  explicit SetLoggerLevelsResult_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->successful = false;
      this->reason = "";
    }
  }

  explicit SetLoggerLevelsResult_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->successful = false;
      this->reason = "";
    }
  }

  // field types and members
  using _successful_type =
    bool;
  _successful_type successful;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;

  // setters for named parameter idiom
  Type & set__successful(
    const bool & _arg)
  {
    this->successful = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__SetLoggerLevelsResult
    std::shared_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__SetLoggerLevelsResult
    std::shared_ptr<rcl_interfaces::msg::SetLoggerLevelsResult_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetLoggerLevelsResult_ & other) const
  {
    if (this->successful != other.successful) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetLoggerLevelsResult_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetLoggerLevelsResult_

// alias to use template instance with default allocator
using SetLoggerLevelsResult =
  rcl_interfaces::msg::SetLoggerLevelsResult_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__SET_LOGGER_LEVELS_RESULT__STRUCT_HPP_
