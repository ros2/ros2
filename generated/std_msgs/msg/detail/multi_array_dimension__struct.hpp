// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from std_msgs:msg/MultiArrayDimension.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/multi_array_dimension.hpp"


#ifndef STD_MSGS__MSG__DETAIL__MULTI_ARRAY_DIMENSION__STRUCT_HPP_
#define STD_MSGS__MSG__DETAIL__MULTI_ARRAY_DIMENSION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__std_msgs__msg__MultiArrayDimension __attribute__((deprecated))
#else
# define DEPRECATED__std_msgs__msg__MultiArrayDimension __declspec(deprecated)
#endif

namespace std_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MultiArrayDimension_
{
  using Type = MultiArrayDimension_<ContainerAllocator>;

  explicit MultiArrayDimension_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
      this->size = 0ul;
      this->stride = 0ul;
    }
  }

  explicit MultiArrayDimension_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : label(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
      this->size = 0ul;
      this->stride = 0ul;
    }
  }

  // field types and members
  using _label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _label_type label;
  using _size_type =
    uint32_t;
  _size_type size;
  using _stride_type =
    uint32_t;
  _stride_type stride;

  // setters for named parameter idiom
  Type & set__label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->label = _arg;
    return *this;
  }
  Type & set__size(
    const uint32_t & _arg)
  {
    this->size = _arg;
    return *this;
  }
  Type & set__stride(
    const uint32_t & _arg)
  {
    this->stride = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    std_msgs::msg::MultiArrayDimension_<ContainerAllocator> *;
  using ConstRawPtr =
    const std_msgs::msg::MultiArrayDimension_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::MultiArrayDimension_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::MultiArrayDimension_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__std_msgs__msg__MultiArrayDimension
    std::shared_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__std_msgs__msg__MultiArrayDimension
    std::shared_ptr<std_msgs::msg::MultiArrayDimension_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MultiArrayDimension_ & other) const
  {
    if (this->label != other.label) {
      return false;
    }
    if (this->size != other.size) {
      return false;
    }
    if (this->stride != other.stride) {
      return false;
    }
    return true;
  }
  bool operator!=(const MultiArrayDimension_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MultiArrayDimension_

// alias to use template instance with default allocator
using MultiArrayDimension =
  std_msgs::msg::MultiArrayDimension_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__MULTI_ARRAY_DIMENSION__STRUCT_HPP_
