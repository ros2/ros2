// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from std_msgs:msg/Empty.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/empty.hpp"


#ifndef STD_MSGS__MSG__DETAIL__EMPTY__STRUCT_HPP_
#define STD_MSGS__MSG__DETAIL__EMPTY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__std_msgs__msg__Empty __attribute__((deprecated))
#else
# define DEPRECATED__std_msgs__msg__Empty __declspec(deprecated)
#endif

namespace std_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Empty_
{
  using Type = Empty_<ContainerAllocator>;

  explicit Empty_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit Empty_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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

  // pointer types
  using RawPtr =
    std_msgs::msg::Empty_<ContainerAllocator> *;
  using ConstRawPtr =
    const std_msgs::msg::Empty_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<std_msgs::msg::Empty_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<std_msgs::msg::Empty_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::Empty_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::Empty_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::Empty_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::Empty_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<std_msgs::msg::Empty_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<std_msgs::msg::Empty_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__std_msgs__msg__Empty
    std::shared_ptr<std_msgs::msg::Empty_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__std_msgs__msg__Empty
    std::shared_ptr<std_msgs::msg::Empty_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Empty_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const Empty_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Empty_

// alias to use template instance with default allocator
using Empty =
  std_msgs::msg::Empty_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__EMPTY__STRUCT_HPP_
