// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from type_description_interfaces:msg/FieldType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/field_type.h"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD_TYPE__STRUCT_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD_TYPE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'FIELD_TYPE_NOT_SET'.
/**
  * A constant for each type supported according to:
  *   http://design.ros2.org/articles/legacy_interface_definition.html
  * and:
  *   http://design.ros2.org/articles/idl_interface_definition.html
  * Order is loosely coupled to the order of appearance in the IDL 4.2 spec:
  *  https://www.omg.org/spec/IDL/4.2
  * Layout of constants across the 0-255 decimal values in the uint8:
  *
  * - 000    : Reserved for "not set"
  * - 001-048: Primitive types, strings, and reserved space for future primitive types
  * - 049-096: Fixed sized array of primitive and string types
  * - 097-144: Bounded Sequences of primitive and string types
  * - 145-192: Unbounded Sequences of primitive and string types
  * - 193-255: Reserved space for future array/sequence-like types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_NOT_SET = 0
};

/// Constant 'FIELD_TYPE_NESTED_TYPE'.
/**
  * Nested type defined in other .msg/.idl files.
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_NESTED_TYPE = 1
};

/// Constant 'FIELD_TYPE_INT8'.
/**
  * Integer Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT8 = 2
};

/// Constant 'FIELD_TYPE_UINT8'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT8 = 3
};

/// Constant 'FIELD_TYPE_INT16'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT16 = 4
};

/// Constant 'FIELD_TYPE_UINT16'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT16 = 5
};

/// Constant 'FIELD_TYPE_INT32'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT32 = 6
};

/// Constant 'FIELD_TYPE_UINT32'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT32 = 7
};

/// Constant 'FIELD_TYPE_INT64'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT64 = 8
};

/// Constant 'FIELD_TYPE_UINT64'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT64 = 9
};

/// Constant 'FIELD_TYPE_FLOAT'.
/**
  * Floating-Point Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FLOAT = 10
};

/// Constant 'FIELD_TYPE_DOUBLE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_DOUBLE = 11
};

/// Constant 'FIELD_TYPE_LONG_DOUBLE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_LONG_DOUBLE = 12
};

/// Constant 'FIELD_TYPE_CHAR'.
/**
  * Char and WChar Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_CHAR = 13
};

/// Constant 'FIELD_TYPE_WCHAR'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WCHAR = 14
};

/// Constant 'FIELD_TYPE_BOOLEAN'.
/**
  * Boolean Type
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOOLEAN = 15
};

/// Constant 'FIELD_TYPE_BYTE'.
/**
  * Byte/Octet Type
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BYTE = 16
};

/// Constant 'FIELD_TYPE_STRING'.
/**
  * String Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_STRING = 17
};

/// Constant 'FIELD_TYPE_WSTRING'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WSTRING = 18
};

/// Constant 'FIELD_TYPE_FIXED_STRING'.
/**
  * Fixed String Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_STRING = 19
};

/// Constant 'FIELD_TYPE_FIXED_WSTRING'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_WSTRING = 20
};

/// Constant 'FIELD_TYPE_BOUNDED_STRING'.
/**
  * Bounded String Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_STRING = 21
};

/// Constant 'FIELD_TYPE_BOUNDED_WSTRING'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_WSTRING = 22
};

/// Constant 'FIELD_TYPE_NESTED_TYPE_ARRAY'.
/**
  * Fixed Sized Array Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_NESTED_TYPE_ARRAY = 49
};

/// Constant 'FIELD_TYPE_INT8_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT8_ARRAY = 50
};

/// Constant 'FIELD_TYPE_UINT8_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT8_ARRAY = 51
};

/// Constant 'FIELD_TYPE_INT16_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT16_ARRAY = 52
};

/// Constant 'FIELD_TYPE_UINT16_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT16_ARRAY = 53
};

/// Constant 'FIELD_TYPE_INT32_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT32_ARRAY = 54
};

/// Constant 'FIELD_TYPE_UINT32_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT32_ARRAY = 55
};

/// Constant 'FIELD_TYPE_INT64_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT64_ARRAY = 56
};

/// Constant 'FIELD_TYPE_UINT64_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT64_ARRAY = 57
};

/// Constant 'FIELD_TYPE_FLOAT_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FLOAT_ARRAY = 58
};

/// Constant 'FIELD_TYPE_DOUBLE_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_DOUBLE_ARRAY = 59
};

/// Constant 'FIELD_TYPE_LONG_DOUBLE_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_LONG_DOUBLE_ARRAY = 60
};

/// Constant 'FIELD_TYPE_CHAR_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_CHAR_ARRAY = 61
};

/// Constant 'FIELD_TYPE_WCHAR_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WCHAR_ARRAY = 62
};

/// Constant 'FIELD_TYPE_BOOLEAN_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOOLEAN_ARRAY = 63
};

/// Constant 'FIELD_TYPE_BYTE_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BYTE_ARRAY = 64
};

/// Constant 'FIELD_TYPE_STRING_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_STRING_ARRAY = 65
};

/// Constant 'FIELD_TYPE_WSTRING_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WSTRING_ARRAY = 66
};

/// Constant 'FIELD_TYPE_FIXED_STRING_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_STRING_ARRAY = 67
};

/// Constant 'FIELD_TYPE_FIXED_WSTRING_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_WSTRING_ARRAY = 68
};

/// Constant 'FIELD_TYPE_BOUNDED_STRING_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_STRING_ARRAY = 69
};

/// Constant 'FIELD_TYPE_BOUNDED_WSTRING_ARRAY'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_WSTRING_ARRAY = 70
};

/// Constant 'FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE'.
/**
  * Bounded Sequence Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE = 97
};

/// Constant 'FIELD_TYPE_INT8_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT8_BOUNDED_SEQUENCE = 98
};

/// Constant 'FIELD_TYPE_UINT8_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT8_BOUNDED_SEQUENCE = 99
};

/// Constant 'FIELD_TYPE_INT16_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT16_BOUNDED_SEQUENCE = 100
};

/// Constant 'FIELD_TYPE_UINT16_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT16_BOUNDED_SEQUENCE = 101
};

/// Constant 'FIELD_TYPE_INT32_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT32_BOUNDED_SEQUENCE = 102
};

/// Constant 'FIELD_TYPE_UINT32_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT32_BOUNDED_SEQUENCE = 103
};

/// Constant 'FIELD_TYPE_INT64_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT64_BOUNDED_SEQUENCE = 104
};

/// Constant 'FIELD_TYPE_UINT64_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT64_BOUNDED_SEQUENCE = 105
};

/// Constant 'FIELD_TYPE_FLOAT_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FLOAT_BOUNDED_SEQUENCE = 106
};

/// Constant 'FIELD_TYPE_DOUBLE_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_DOUBLE_BOUNDED_SEQUENCE = 107
};

/// Constant 'FIELD_TYPE_LONG_DOUBLE_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_LONG_DOUBLE_BOUNDED_SEQUENCE = 108
};

/// Constant 'FIELD_TYPE_CHAR_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_CHAR_BOUNDED_SEQUENCE = 109
};

/// Constant 'FIELD_TYPE_WCHAR_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WCHAR_BOUNDED_SEQUENCE = 110
};

/// Constant 'FIELD_TYPE_BOOLEAN_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOOLEAN_BOUNDED_SEQUENCE = 111
};

/// Constant 'FIELD_TYPE_BYTE_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BYTE_BOUNDED_SEQUENCE = 112
};

/// Constant 'FIELD_TYPE_STRING_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_STRING_BOUNDED_SEQUENCE = 113
};

/// Constant 'FIELD_TYPE_WSTRING_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WSTRING_BOUNDED_SEQUENCE = 114
};

/// Constant 'FIELD_TYPE_FIXED_STRING_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_STRING_BOUNDED_SEQUENCE = 115
};

/// Constant 'FIELD_TYPE_FIXED_WSTRING_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_WSTRING_BOUNDED_SEQUENCE = 116
};

/// Constant 'FIELD_TYPE_BOUNDED_STRING_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_STRING_BOUNDED_SEQUENCE = 117
};

/// Constant 'FIELD_TYPE_BOUNDED_WSTRING_BOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_WSTRING_BOUNDED_SEQUENCE = 118
};

/// Constant 'FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE'.
/**
  * Unbounded Sequence Types
 */
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE = 145
};

/// Constant 'FIELD_TYPE_INT8_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT8_UNBOUNDED_SEQUENCE = 146
};

/// Constant 'FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE = 147
};

/// Constant 'FIELD_TYPE_INT16_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT16_UNBOUNDED_SEQUENCE = 148
};

/// Constant 'FIELD_TYPE_UINT16_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT16_UNBOUNDED_SEQUENCE = 149
};

/// Constant 'FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE = 150
};

/// Constant 'FIELD_TYPE_UINT32_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT32_UNBOUNDED_SEQUENCE = 151
};

/// Constant 'FIELD_TYPE_INT64_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_INT64_UNBOUNDED_SEQUENCE = 152
};

/// Constant 'FIELD_TYPE_UINT64_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_UINT64_UNBOUNDED_SEQUENCE = 153
};

/// Constant 'FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE = 154
};

/// Constant 'FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE = 155
};

/// Constant 'FIELD_TYPE_LONG_DOUBLE_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_LONG_DOUBLE_UNBOUNDED_SEQUENCE = 156
};

/// Constant 'FIELD_TYPE_CHAR_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_CHAR_UNBOUNDED_SEQUENCE = 157
};

/// Constant 'FIELD_TYPE_WCHAR_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WCHAR_UNBOUNDED_SEQUENCE = 158
};

/// Constant 'FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE = 159
};

/// Constant 'FIELD_TYPE_BYTE_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BYTE_UNBOUNDED_SEQUENCE = 160
};

/// Constant 'FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE = 161
};

/// Constant 'FIELD_TYPE_WSTRING_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_WSTRING_UNBOUNDED_SEQUENCE = 162
};

/// Constant 'FIELD_TYPE_FIXED_STRING_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_STRING_UNBOUNDED_SEQUENCE = 163
};

/// Constant 'FIELD_TYPE_FIXED_WSTRING_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_FIXED_WSTRING_UNBOUNDED_SEQUENCE = 164
};

/// Constant 'FIELD_TYPE_BOUNDED_STRING_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_STRING_UNBOUNDED_SEQUENCE = 165
};

/// Constant 'FIELD_TYPE_BOUNDED_WSTRING_UNBOUNDED_SEQUENCE'.
enum
{
  type_description_interfaces__msg__FieldType__FIELD_TYPE_BOUNDED_WSTRING_UNBOUNDED_SEQUENCE = 166
};

// Include directives for member types
// Member 'nested_type_name'
#include "rosidl_runtime_c/string.h"

// constants for array fields with an upper bound
// nested_type_name
enum
{
  type_description_interfaces__msg__FieldType__nested_type_name__MAX_STRING_SIZE = 255
};

/// Struct defined in msg/FieldType in the package type_description_interfaces.
/**
  * Represents the type of a field and related meta-data.
 */
typedef struct type_description_interfaces__msg__FieldType
{
  /// Identifying number for the type of the field, using one of the above constants.
  uint8_t type_id;
  /// Only used when the type is an array or a bounded sequence.
  /// In the case of an array, this is the fixed capacity of the array.
  /// In the case of a bounded sequence, this is the maximum capacity of the sequence.
  /// In all other cases this field is unused.
  uint64_t capacity;
  /// Only used when the type is a fixed or bounded string/wstring, or a array/sequence of those.
  /// In the case of a fixed string/wstring, it is the fixed length of the string.
  /// In the case of a bounded string/wstring, it is the maximum capacity of the string.
  /// In the case of an array/sequence of fixed string/wstring, it is the fixed length of the strings.
  /// In the case of an array/sequence of bounded string/wstring, it is the maximum capacity of the strings.
  /// It is not currently possible to have different string capacities per element in the array/sequence.
  uint64_t string_capacity;
  /// Only used when the type is a nested type or array/sequence of nested types.
  /// This is limited to 255 characters.
  /// TODO(wjwwood): this 255 character limit was chosen due to this being the limit
  ///   for DDSI-RTPS based middlewares, which is the most commonly used right now.
  ///   We lack a ROS 2 specific limit in our design documents, but we should update
  ///   this and/or link to the design doc when that is available.
  rosidl_runtime_c__String nested_type_name;
} type_description_interfaces__msg__FieldType;

// Struct for a sequence of type_description_interfaces__msg__FieldType.
typedef struct type_description_interfaces__msg__FieldType__Sequence
{
  type_description_interfaces__msg__FieldType * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} type_description_interfaces__msg__FieldType__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__FIELD_TYPE__STRUCT_H_
