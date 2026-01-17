// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rmw_dds_common:msg/Gid.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/gid.hpp"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__GID__STRUCT_HPP_
#define RMW_DDS_COMMON__MSG__DETAIL__GID__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rmw_dds_common__msg__Gid __attribute__((deprecated))
#else
# define DEPRECATED__rmw_dds_common__msg__Gid __declspec(deprecated)
#endif

namespace rmw_dds_common
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Gid_
{
  using Type = Gid_<ContainerAllocator>;

  explicit Gid_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->data.begin(), this->data.end(), 0);
    }
  }

  explicit Gid_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : data(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->data.begin(), this->data.end(), 0);
    }
  }

  // field types and members
  using _data_type =
    std::array<uint8_t, 16>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const std::array<uint8_t, 16> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rmw_dds_common::msg::Gid_<ContainerAllocator> *;
  using ConstRawPtr =
    const rmw_dds_common::msg::Gid_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rmw_dds_common::msg::Gid_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rmw_dds_common::msg::Gid_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rmw_dds_common__msg__Gid
    std::shared_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rmw_dds_common__msg__Gid
    std::shared_ptr<rmw_dds_common::msg::Gid_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Gid_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const Gid_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Gid_

// alias to use template instance with default allocator
using Gid =
  rmw_dds_common::msg::Gid_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rmw_dds_common

#endif  // RMW_DDS_COMMON__MSG__DETAIL__GID__STRUCT_HPP_
