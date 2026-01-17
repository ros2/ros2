// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/ParameterValue.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_value.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__ParameterValue __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__ParameterValue __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ParameterValue_
{
  using Type = ParameterValue_<ContainerAllocator>;

  explicit ParameterValue_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0;
      this->bool_value = false;
      this->integer_value = 0ll;
      this->double_value = 0.0;
      this->string_value = "";
    }
  }

  explicit ParameterValue_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : string_value(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0;
      this->bool_value = false;
      this->integer_value = 0ll;
      this->double_value = 0.0;
      this->string_value = "";
    }
  }

  // field types and members
  using _type_type =
    uint8_t;
  _type_type type;
  using _bool_value_type =
    bool;
  _bool_value_type bool_value;
  using _integer_value_type =
    int64_t;
  _integer_value_type integer_value;
  using _double_value_type =
    double;
  _double_value_type double_value;
  using _string_value_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _string_value_type string_value;
  using _byte_array_value_type =
    std::vector<unsigned char, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<unsigned char>>;
  _byte_array_value_type byte_array_value;
  using _bool_array_value_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _bool_array_value_type bool_array_value;
  using _integer_array_value_type =
    std::vector<int64_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int64_t>>;
  _integer_array_value_type integer_array_value;
  using _double_array_value_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _double_array_value_type double_array_value;
  using _string_array_value_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _string_array_value_type string_array_value;

  // setters for named parameter idiom
  Type & set__type(
    const uint8_t & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__bool_value(
    const bool & _arg)
  {
    this->bool_value = _arg;
    return *this;
  }
  Type & set__integer_value(
    const int64_t & _arg)
  {
    this->integer_value = _arg;
    return *this;
  }
  Type & set__double_value(
    const double & _arg)
  {
    this->double_value = _arg;
    return *this;
  }
  Type & set__string_value(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->string_value = _arg;
    return *this;
  }
  Type & set__byte_array_value(
    const std::vector<unsigned char, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<unsigned char>> & _arg)
  {
    this->byte_array_value = _arg;
    return *this;
  }
  Type & set__bool_array_value(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->bool_array_value = _arg;
    return *this;
  }
  Type & set__integer_array_value(
    const std::vector<int64_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int64_t>> & _arg)
  {
    this->integer_array_value = _arg;
    return *this;
  }
  Type & set__double_array_value(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->double_array_value = _arg;
    return *this;
  }
  Type & set__string_array_value(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->string_array_value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::ParameterValue_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::ParameterValue_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterValue_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterValue_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__ParameterValue
    std::shared_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__ParameterValue
    std::shared_ptr<rcl_interfaces::msg::ParameterValue_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ParameterValue_ & other) const
  {
    if (this->type != other.type) {
      return false;
    }
    if (this->bool_value != other.bool_value) {
      return false;
    }
    if (this->integer_value != other.integer_value) {
      return false;
    }
    if (this->double_value != other.double_value) {
      return false;
    }
    if (this->string_value != other.string_value) {
      return false;
    }
    if (this->byte_array_value != other.byte_array_value) {
      return false;
    }
    if (this->bool_array_value != other.bool_array_value) {
      return false;
    }
    if (this->integer_array_value != other.integer_array_value) {
      return false;
    }
    if (this->double_array_value != other.double_array_value) {
      return false;
    }
    if (this->string_array_value != other.string_array_value) {
      return false;
    }
    return true;
  }
  bool operator!=(const ParameterValue_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ParameterValue_

// alias to use template instance with default allocator
using ParameterValue =
  rcl_interfaces::msg::ParameterValue_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_VALUE__STRUCT_HPP_
