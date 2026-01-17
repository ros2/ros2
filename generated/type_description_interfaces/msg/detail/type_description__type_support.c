// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from type_description_interfaces:msg/TypeDescription.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "type_description_interfaces/msg/detail/type_description__rosidl_typesupport_introspection_c.h"
#include "type_description_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "type_description_interfaces/msg/detail/type_description__functions.h"
#include "type_description_interfaces/msg/detail/type_description__struct.h"


// Include directives for member types
// Member `type_description`
// Member `referenced_type_descriptions`
#include "type_description_interfaces/msg/individual_type_description.h"
// Member `type_description`
// Member `referenced_type_descriptions`
#include "type_description_interfaces/msg/detail/individual_type_description__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  type_description_interfaces__msg__TypeDescription__init(message_memory);
}

void type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_fini_function(void * message_memory)
{
  type_description_interfaces__msg__TypeDescription__fini(message_memory);
}

size_t type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__size_function__TypeDescription__referenced_type_descriptions(
  const void * untyped_member)
{
  const type_description_interfaces__msg__IndividualTypeDescription__Sequence * member =
    (const type_description_interfaces__msg__IndividualTypeDescription__Sequence *)(untyped_member);
  return member->size;
}

const void * type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__get_const_function__TypeDescription__referenced_type_descriptions(
  const void * untyped_member, size_t index)
{
  const type_description_interfaces__msg__IndividualTypeDescription__Sequence * member =
    (const type_description_interfaces__msg__IndividualTypeDescription__Sequence *)(untyped_member);
  return &member->data[index];
}

void * type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__get_function__TypeDescription__referenced_type_descriptions(
  void * untyped_member, size_t index)
{
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * member =
    (type_description_interfaces__msg__IndividualTypeDescription__Sequence *)(untyped_member);
  return &member->data[index];
}

void type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__fetch_function__TypeDescription__referenced_type_descriptions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const type_description_interfaces__msg__IndividualTypeDescription * item =
    ((const type_description_interfaces__msg__IndividualTypeDescription *)
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__get_const_function__TypeDescription__referenced_type_descriptions(untyped_member, index));
  type_description_interfaces__msg__IndividualTypeDescription * value =
    (type_description_interfaces__msg__IndividualTypeDescription *)(untyped_value);
  *value = *item;
}

void type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__assign_function__TypeDescription__referenced_type_descriptions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  type_description_interfaces__msg__IndividualTypeDescription * item =
    ((type_description_interfaces__msg__IndividualTypeDescription *)
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__get_function__TypeDescription__referenced_type_descriptions(untyped_member, index));
  const type_description_interfaces__msg__IndividualTypeDescription * value =
    (const type_description_interfaces__msg__IndividualTypeDescription *)(untyped_value);
  *item = *value;
}

bool type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__resize_function__TypeDescription__referenced_type_descriptions(
  void * untyped_member, size_t size)
{
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * member =
    (type_description_interfaces__msg__IndividualTypeDescription__Sequence *)(untyped_member);
  type_description_interfaces__msg__IndividualTypeDescription__Sequence__fini(member);
  return type_description_interfaces__msg__IndividualTypeDescription__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_member_array[2] = {
  {
    "type_description",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__TypeDescription, type_description),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "referenced_type_descriptions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__TypeDescription, referenced_type_descriptions),  // bytes offset in struct
    NULL,  // default value
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__size_function__TypeDescription__referenced_type_descriptions,  // size() function pointer
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__get_const_function__TypeDescription__referenced_type_descriptions,  // get_const(index) function pointer
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__get_function__TypeDescription__referenced_type_descriptions,  // get(index) function pointer
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__fetch_function__TypeDescription__referenced_type_descriptions,  // fetch(index, &value) function pointer
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__assign_function__TypeDescription__referenced_type_descriptions,  // assign(index, value) function pointer
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__resize_function__TypeDescription__referenced_type_descriptions  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_members = {
  "type_description_interfaces__msg",  // message namespace
  "TypeDescription",  // message name
  2,  // number of fields
  sizeof(type_description_interfaces__msg__TypeDescription),
  false,  // has_any_key_member_
  type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_member_array,  // message members
  type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_init_function,  // function to initialize message memory (memory has to be allocated)
  type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_type_support_handle = {
  0,
  &type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__msg__TypeDescription__get_type_hash,
  &type_description_interfaces__msg__TypeDescription__get_type_description,
  &type_description_interfaces__msg__TypeDescription__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_type_description_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, TypeDescription)() {
  type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, IndividualTypeDescription)();
  type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, IndividualTypeDescription)();
  if (!type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_type_support_handle.typesupport_identifier) {
    type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &type_description_interfaces__msg__TypeDescription__rosidl_typesupport_introspection_c__TypeDescription_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
