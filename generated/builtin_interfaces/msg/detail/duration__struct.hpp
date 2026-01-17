// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from builtin_interfaces:msg/Duration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "builtin_interfaces/msg/duration.hpp"


#ifndef BUILTIN_INTERFACES__MSG__DETAIL__DURATION__STRUCT_HPP_
#define BUILTIN_INTERFACES__MSG__DETAIL__DURATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__builtin_interfaces__msg__Duration __attribute__((deprecated))
#else
# define DEPRECATED__builtin_interfaces__msg__Duration __declspec(deprecated)
#endif

namespace builtin_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Duration_
{
  using Type = Duration_<ContainerAllocator>;

  explicit Duration_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sec = 0l;
      this->nanosec = 0ul;
    }
  }

  explicit Duration_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sec = 0l;
      this->nanosec = 0ul;
    }
  }

  // field types and members
  using _sec_type =
    int32_t;
  _sec_type sec;
  using _nanosec_type =
    uint32_t;
  _nanosec_type nanosec;

  // setters for named parameter idiom
  Type & set__sec(
    const int32_t & _arg)
  {
    this->sec = _arg;
    return *this;
  }
  Type & set__nanosec(
    const uint32_t & _arg)
  {
    this->nanosec = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    builtin_interfaces::msg::Duration_<ContainerAllocator> *;
  using ConstRawPtr =
    const builtin_interfaces::msg::Duration_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      builtin_interfaces::msg::Duration_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      builtin_interfaces::msg::Duration_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__builtin_interfaces__msg__Duration
    std::shared_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__builtin_interfaces__msg__Duration
    std::shared_ptr<builtin_interfaces::msg::Duration_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Duration_ & other) const
  {
    if (this->sec != other.sec) {
      return false;
    }
    if (this->nanosec != other.nanosec) {
      return false;
    }
    return true;
  }
  bool operator!=(const Duration_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Duration_

// alias to use template instance with default allocator
using Duration =
  builtin_interfaces::msg::Duration_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace builtin_interfaces

#endif  // BUILTIN_INTERFACES__MSG__DETAIL__DURATION__STRUCT_HPP_
