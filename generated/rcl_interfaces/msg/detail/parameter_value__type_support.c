// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rcl_interfaces:msg/ParameterValue.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rcl_interfaces/msg/detail/parameter_value__rosidl_typesupport_introspection_c.h"
#include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rcl_interfaces/msg/detail/parameter_value__functions.h"
#include "rcl_interfaces/msg/detail/parameter_value__struct.h"


// Include directives for member types
// Member `string_value`
// Member `string_array_value`
#include "rosidl_runtime_c/string_functions.h"
// Member `byte_array_value`
// Member `bool_array_value`
// Member `integer_array_value`
// Member `double_array_value`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__msg__ParameterValue__init(message_memory);
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_fini_function(void * message_memory)
{
  rcl_interfaces__msg__ParameterValue__fini(message_memory);
}

size_t rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__byte_array_value(
  const void * untyped_member)
{
  const rosidl_runtime_c__octet__Sequence * member =
    (const rosidl_runtime_c__octet__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__byte_array_value(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__octet__Sequence * member =
    (const rosidl_runtime_c__octet__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__byte_array_value(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__octet__Sequence * member =
    (rosidl_runtime_c__octet__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__byte_array_value(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__byte_array_value(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__byte_array_value(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__byte_array_value(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__byte_array_value(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__octet__Sequence * member =
    (rosidl_runtime_c__octet__Sequence *)(untyped_member);
  rosidl_runtime_c__octet__Sequence__fini(member);
  return rosidl_runtime_c__octet__Sequence__init(member, size);
}

size_t rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__bool_array_value(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__bool_array_value(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__bool_array_value(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__bool_array_value(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__bool_array_value(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__bool_array_value(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__bool_array_value(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__bool_array_value(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

size_t rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__integer_array_value(
  const void * untyped_member)
{
  const rosidl_runtime_c__int64__Sequence * member =
    (const rosidl_runtime_c__int64__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__integer_array_value(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int64__Sequence * member =
    (const rosidl_runtime_c__int64__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__integer_array_value(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int64__Sequence * member =
    (rosidl_runtime_c__int64__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__integer_array_value(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int64_t * item =
    ((const int64_t *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__integer_array_value(untyped_member, index));
  int64_t * value =
    (int64_t *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__integer_array_value(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int64_t * item =
    ((int64_t *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__integer_array_value(untyped_member, index));
  const int64_t * value =
    (const int64_t *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__integer_array_value(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int64__Sequence * member =
    (rosidl_runtime_c__int64__Sequence *)(untyped_member);
  rosidl_runtime_c__int64__Sequence__fini(member);
  return rosidl_runtime_c__int64__Sequence__init(member, size);
}

size_t rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__double_array_value(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__double_array_value(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__double_array_value(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__double_array_value(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__double_array_value(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__double_array_value(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__double_array_value(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__double_array_value(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__string_array_value(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__string_array_value(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__string_array_value(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__string_array_value(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__string_array_value(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__string_array_value(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__string_array_value(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__string_array_value(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_member_array[10] = {
  {
    "type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "bool_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, bool_value),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "integer_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, integer_value),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "double_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, double_value),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "string_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, string_value),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "byte_array_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_OCTET,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, byte_array_value),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__byte_array_value,  // size() function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__byte_array_value,  // get_const(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__byte_array_value,  // get(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__byte_array_value,  // fetch(index, &value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__byte_array_value,  // assign(index, value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__byte_array_value  // resize(index) function pointer
  },
  {
    "bool_array_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, bool_array_value),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__bool_array_value,  // size() function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__bool_array_value,  // get_const(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__bool_array_value,  // get(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__bool_array_value,  // fetch(index, &value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__bool_array_value,  // assign(index, value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__bool_array_value  // resize(index) function pointer
  },
  {
    "integer_array_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, integer_array_value),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__integer_array_value,  // size() function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__integer_array_value,  // get_const(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__integer_array_value,  // get(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__integer_array_value,  // fetch(index, &value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__integer_array_value,  // assign(index, value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__integer_array_value  // resize(index) function pointer
  },
  {
    "double_array_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, double_array_value),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__double_array_value,  // size() function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__double_array_value,  // get_const(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__double_array_value,  // get(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__double_array_value,  // fetch(index, &value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__double_array_value,  // assign(index, value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__double_array_value  // resize(index) function pointer
  },
  {
    "string_array_value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ParameterValue, string_array_value),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__size_function__ParameterValue__string_array_value,  // size() function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_const_function__ParameterValue__string_array_value,  // get_const(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__get_function__ParameterValue__string_array_value,  // get(index) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__fetch_function__ParameterValue__string_array_value,  // fetch(index, &value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__assign_function__ParameterValue__string_array_value,  // assign(index, value) function pointer
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__resize_function__ParameterValue__string_array_value  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_members = {
  "rcl_interfaces__msg",  // message namespace
  "ParameterValue",  // message name
  10,  // number of fields
  sizeof(rcl_interfaces__msg__ParameterValue),
  false,  // has_any_key_member_
  rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_member_array,  // message members
  rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_type_support_handle = {
  0,
  &rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__ParameterValue__get_type_hash,
  &rcl_interfaces__msg__ParameterValue__get_type_description,
  &rcl_interfaces__msg__ParameterValue__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, ParameterValue)() {
  if (!rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__msg__ParameterValue__rosidl_typesupport_introspection_c__ParameterValue_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
