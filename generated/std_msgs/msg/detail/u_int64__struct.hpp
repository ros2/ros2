// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from std_msgs:msg/UInt64.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/u_int64.hpp"


#ifndef STD_MSGS__MSG__DETAIL__U_INT64__STRUCT_HPP_
#define STD_MSGS__MSG__DETAIL__U_INT64__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__std_msgs__msg__UInt64 __attribute__((deprecated))
#else
# define DEPRECATED__std_msgs__msg__UInt64 __declspec(deprecated)
#endif

namespace std_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UInt64_
{
  using Type = UInt64_<ContainerAllocator>;

  explicit UInt64_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->data = 0ull;
    }
  }

  explicit UInt64_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->data = 0ull;
    }
  }

  // field types and members
  using _data_type =
    uint64_t;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const uint64_t & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    std_msgs::msg::UInt64_<ContainerAllocator> *;
  using ConstRawPtr =
    const std_msgs::msg::UInt64_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<std_msgs::msg::UInt64_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<std_msgs::msg::UInt64_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::UInt64_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::UInt64_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::UInt64_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::UInt64_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<std_msgs::msg::UInt64_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<std_msgs::msg::UInt64_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__std_msgs__msg__UInt64
    std::shared_ptr<std_msgs::msg::UInt64_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__std_msgs__msg__UInt64
    std::shared_ptr<std_msgs::msg::UInt64_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UInt64_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const UInt64_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UInt64_

// alias to use template instance with default allocator
using UInt64 =
  std_msgs::msg::UInt64_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__U_INT64__STRUCT_HPP_
