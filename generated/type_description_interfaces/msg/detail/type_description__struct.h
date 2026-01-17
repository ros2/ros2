// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from type_description_interfaces:msg/TypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/type_description.h"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__STRUCT_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'type_description'
// Member 'referenced_type_descriptions'
#include "type_description_interfaces/msg/detail/individual_type_description__struct.h"

/// Struct defined in msg/TypeDescription in the package type_description_interfaces.
/**
  * Represents a complete type description, including the type itself as well as the types it references.
 */
typedef struct type_description_interfaces__msg__TypeDescription
{
  /// Description of the type.
  type_description_interfaces__msg__IndividualTypeDescription type_description;
  /// Descriptions of all referenced types, recursively.
  type_description_interfaces__msg__IndividualTypeDescription__Sequence referenced_type_descriptions;
} type_description_interfaces__msg__TypeDescription;

// Struct for a sequence of type_description_interfaces__msg__TypeDescription.
typedef struct type_description_interfaces__msg__TypeDescription__Sequence
{
  type_description_interfaces__msg__TypeDescription * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__msg__TypeDescription__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_DESCRIPTION__STRUCT_H_
