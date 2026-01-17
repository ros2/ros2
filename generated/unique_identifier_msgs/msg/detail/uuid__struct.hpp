// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unique_identifier_msgs/msg/uuid.hpp"


#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__STRUCT_HPP_
#define UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__unique_identifier_msgs__msg__UUID __attribute__((deprecated))
#else
# define DEPRECATED__unique_identifier_msgs__msg__UUID __declspec(deprecated)
#endif

namespace unique_identifier_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UUID_
{
  using Type = UUID_<ContainerAllocator>;

  explicit UUID_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->uuid.begin(), this->uuid.end(), 0);
    }
  }

  explicit UUID_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : uuid(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->uuid.begin(), this->uuid.end(), 0);
    }
  }

  // field types and members
  using _uuid_type =
    std::array<uint8_t, 16>;
  _uuid_type uuid;

  // setters for named parameter idiom
  Type & set__uuid(
    const std::array<uint8_t, 16> & _arg)
  {
    this->uuid = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator> *;
  using ConstRawPtr =
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      unique_identifier_msgs::msg::UUID_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      unique_identifier_msgs::msg::UUID_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__unique_identifier_msgs__msg__UUID
    std::shared_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__unique_identifier_msgs__msg__UUID
    std::shared_ptr<unique_identifier_msgs::msg::UUID_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UUID_ & other) const
  {
    if (this->uuid != other.uuid) {
      return false;
    }
    return true;
  }
  bool operator!=(const UUID_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UUID_

// alias to use template instance with default allocator
using UUID =
  unique_identifier_msgs::msg::UUID_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace unique_identifier_msgs

#endif  // UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__STRUCT_HPP_
