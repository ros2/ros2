// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/FieldType type

#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "type_description_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// Nested type ID constants
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_NOT_SET ((uint8_t)0)

// Primitive type IDs (1-19)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_NESTED_TYPE ((uint8_t)1)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT8 ((uint8_t)2)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT8 ((uint8_t)3)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT16 ((uint8_t)4)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT16 ((uint8_t)5)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT32 ((uint8_t)6)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT32 ((uint8_t)7)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT64 ((uint8_t)8)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT64 ((uint8_t)9)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_FLOAT ((uint8_t)10)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_DOUBLE ((uint8_t)11)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_LONG_DOUBLE ((uint8_t)12)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_CHAR ((uint8_t)13)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_WCHAR ((uint8_t)14)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BOOLEAN ((uint8_t)15)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BYTE ((uint8_t)16)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_STRING ((uint8_t)17)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_WSTRING ((uint8_t)18)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_FIXED_STRING ((uint8_t)19)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_FIXED_WSTRING ((uint8_t)20)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BOUNDED_STRING ((uint8_t)21)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BOUNDED_WSTRING ((uint8_t)22)

// Array type ID offset (added to base type)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_NESTED_TYPE_ARRAY ((uint8_t)49)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT8_ARRAY ((uint8_t)50)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT8_ARRAY ((uint8_t)51)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT16_ARRAY ((uint8_t)52)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT16_ARRAY ((uint8_t)53)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT32_ARRAY ((uint8_t)54)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT32_ARRAY ((uint8_t)55)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_INT64_ARRAY ((uint8_t)56)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_UINT64_ARRAY ((uint8_t)57)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_FLOAT_ARRAY ((uint8_t)58)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_DOUBLE_ARRAY ((uint8_t)59)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_LONG_DOUBLE_ARRAY ((uint8_t)60)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_CHAR_ARRAY ((uint8_t)61)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_WCHAR_ARRAY ((uint8_t)62)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BOOLEAN_ARRAY ((uint8_t)63)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BYTE_ARRAY ((uint8_t)64)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_STRING_ARRAY ((uint8_t)65)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_WSTRING_ARRAY ((uint8_t)66)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_FIXED_STRING_ARRAY ((uint8_t)67)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_FIXED_WSTRING_ARRAY ((uint8_t)68)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BOUNDED_STRING_ARRAY ((uint8_t)69)
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_BOUNDED_WSTRING_ARRAY ((uint8_t)70)

// Bounded sequence type ID offset
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE ((uint8_t)97)
// ... more bounded sequence types ...

// Unbounded sequence type ID offset
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE ((uint8_t)145)
// ... more unbounded sequence types ...

/// Type information for a field
typedef struct type_description_interfaces__msg__FieldType
{
  /// Type ID (see constants above)
  uint8_t type_id;
  /// Capacity for bounded types (strings, arrays, sequences)
  uint64_t capacity;
  /// Size for fixed-size strings
  uint64_t string_capacity;
  /// Fully qualified name for nested types
  rosidl_runtime_c__String nested_type_name;
} type_description_interfaces__msg__FieldType;

typedef struct type_description_interfaces__msg__FieldType__Sequence
{
  type_description_interfaces__msg__FieldType * data;
  size_t size;
  size_t capacity;
} type_description_interfaces__msg__FieldType__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__FieldType__init(type_description_interfaces__msg__FieldType * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__FieldType__fini(type_description_interfaces__msg__FieldType * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__FieldType * type_description_interfaces__msg__FieldType__create(void);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__FieldType__destroy(type_description_interfaces__msg__FieldType * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__FieldType__Sequence__init(
  type_description_interfaces__msg__FieldType__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__FieldType__Sequence__fini(
  type_description_interfaces__msg__FieldType__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_TYPE_H_
