// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from type_description_interfaces:msg/TypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/type_description.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__STRUCT_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'type_description'
// Member 'referenced_type_descriptions'
#include "type_description_interfaces/msg/detail/individual_type_description__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__type_description_interfaces__msg__TypeDescription __attribute__((deprecated))
#else
# define DEPRECATED__type_description_interfaces__msg__TypeDescription __declspec(deprecated)
#endif

namespace type_description_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TypeDescription_
{
  using Type = TypeDescription_<ContainerAllocator>;

  explicit TypeDescription_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : type_description(_init)
  {
    (void)_init;
  }

  explicit TypeDescription_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : type_description(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _type_description_type =
    type_description_interfaces::msg::IndividualTypeDescription_<ContainerAllocator>;
  _type_description_type type_description;
  using _referenced_type_descriptions_type =
    std::vector<type_description_interfaces::msg::IndividualTypeDescription_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::msg::IndividualTypeDescription_<ContainerAllocator>>>;
  _referenced_type_descriptions_type referenced_type_descriptions;

  // setters for named parameter idiom
  Type & set__type_description(
    const type_description_interfaces::msg::IndividualTypeDescription_<ContainerAllocator> & _arg)
  {
    this->type_description = _arg;
    return *this;
  }
  Type & set__referenced_type_descriptions(
    const std::vector<type_description_interfaces::msg::IndividualTypeDescription_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<type_description_interfaces::msg::IndividualTypeDescription_<ContainerAllocator>>> & _arg)
  {
    this->referenced_type_descriptions = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    type_description_interfaces::msg::TypeDescription_<ContainerAllocator> *;
  using ConstRawPtr =
    const type_description_interfaces::msg::TypeDescription_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::msg::TypeDescription_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      type_description_interfaces::msg::TypeDescription_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__type_description_interfaces__msg__TypeDescription
    std::shared_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__type_description_interfaces__msg__TypeDescription
    std::shared_ptr<type_description_interfaces::msg::TypeDescription_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TypeDescription_ & other) const
  {
    if (this->type_description != other.type_description) {
      return false;
    }
    if (this->referenced_type_descriptions != other.referenced_type_descriptions) {
      return false;
    }
    return true;
  }
  bool operator!=(const TypeDescription_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TypeDescription_

// alias to use template instance with default allocator
using TypeDescription =
  type_description_interfaces::msg::TypeDescription_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace type_description_interfaces

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__STRUCT_HPP_
