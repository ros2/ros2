// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from type_description_interfaces:msg/Field.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/field.h"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__STRUCT_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'name'
// Member 'default_value'
#include "rosidl_runtime_c/string.h"
// Member 'type'
#include "type_description_interfaces/msg/detail/field_type__struct.h"

/// Struct defined in msg/Field in the package type_description_interfaces.
/**
  * Represents a single field in a type.
 */
typedef struct type_description_interfaces__msg__Field
{
  /// Name of the field.
  rosidl_runtime_c__String name;
  /// Type of the field, including details about the type like length, nested name, etc.
  type_description_interfaces__msg__FieldType type;
  /// Literal default value of the field as a string, as it appeared in the original
  /// message description file, whether that be .msg/.srv/.action or .idl.
  rosidl_runtime_c__String default_value;
} type_description_interfaces__msg__Field;

// Struct for a sequence of type_description_interfaces__msg__Field.
typedef struct type_description_interfaces__msg__Field__Sequence
{
  type_description_interfaces__msg__Field * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__msg__Field__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD__STRUCT_H_
