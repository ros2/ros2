// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from std_msgs:msg/ColorRGBA.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/color_rgba.hpp"


#ifndef STD_MSGS__MSG__DETAIL__COLOR_RGBA__STRUCT_HPP_
#define STD_MSGS__MSG__DETAIL__COLOR_RGBA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__std_msgs__msg__ColorRGBA __attribute__((deprecated))
#else
# define DEPRECATED__std_msgs__msg__ColorRGBA __declspec(deprecated)
#endif

namespace std_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ColorRGBA_
{
  using Type = ColorRGBA_<ContainerAllocator>;

  explicit ColorRGBA_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->r = 0.0f;
      this->g = 0.0f;
      this->b = 0.0f;
      this->a = 0.0f;
    }
  }

  explicit ColorRGBA_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->r = 0.0f;
      this->g = 0.0f;
      this->b = 0.0f;
      this->a = 0.0f;
    }
  }

  // field types and members
  using _r_type =
    float;
  _r_type r;
  using _g_type =
    float;
  _g_type g;
  using _b_type =
    float;
  _b_type b;
  using _a_type =
    float;
  _a_type a;

  // setters for named parameter idiom
  Type & set__r(
    const float & _arg)
  {
    this->r = _arg;
    return *this;
  }
  Type & set__g(
    const float & _arg)
  {
    this->g = _arg;
    return *this;
  }
  Type & set__b(
    const float & _arg)
  {
    this->b = _arg;
    return *this;
  }
  Type & set__a(
    const float & _arg)
  {
    this->a = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    std_msgs::msg::ColorRGBA_<ContainerAllocator> *;
  using ConstRawPtr =
    const std_msgs::msg::ColorRGBA_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::ColorRGBA_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      std_msgs::msg::ColorRGBA_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__std_msgs__msg__ColorRGBA
    std::shared_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__std_msgs__msg__ColorRGBA
    std::shared_ptr<std_msgs::msg::ColorRGBA_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ColorRGBA_ & other) const
  {
    if (this->r != other.r) {
      return false;
    }
    if (this->g != other.g) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    if (this->a != other.a) {
      return false;
    }
    return true;
  }
  bool operator!=(const ColorRGBA_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ColorRGBA_

// alias to use template instance with default allocator
using ColorRGBA =
  std_msgs::msg::ColorRGBA_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace std_msgs

#endif  // STD_MSGS__MSG__DETAIL__COLOR_RGBA__STRUCT_HPP_
