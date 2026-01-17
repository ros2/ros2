// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from action_msgs:msg/GoalStatusArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "action_msgs/msg/detail/goal_status_array__rosidl_typesupport_introspection_c.h"
#include "action_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "action_msgs/msg/detail/goal_status_array__functions.h"
#include "action_msgs/msg/detail/goal_status_array__struct.h"


// Include directives for member types
// Member `status_list`
#include "action_msgs/msg/goal_status.h"
// Member `status_list`
#include "action_msgs/msg/detail/goal_status__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  action_msgs__msg__GoalStatusArray__init(message_memory);
}

void action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_fini_function(void * message_memory)
{
  action_msgs__msg__GoalStatusArray__fini(message_memory);
}

size_t action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__size_function__GoalStatusArray__status_list(
  const void * untyped_member)
{
  const action_msgs__msg__GoalStatus__Sequence * member =
    (const action_msgs__msg__GoalStatus__Sequence *)(untyped_member);
  return member->size;
}

const void * action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__get_const_function__GoalStatusArray__status_list(
  const void * untyped_member, size_t index)
{
  const action_msgs__msg__GoalStatus__Sequence * member =
    (const action_msgs__msg__GoalStatus__Sequence *)(untyped_member);
  return &member->data[index];
}

void * action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__get_function__GoalStatusArray__status_list(
  void * untyped_member, size_t index)
{
  action_msgs__msg__GoalStatus__Sequence * member =
    (action_msgs__msg__GoalStatus__Sequence *)(untyped_member);
  return &member->data[index];
}

void action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__fetch_function__GoalStatusArray__status_list(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const action_msgs__msg__GoalStatus * item =
    ((const action_msgs__msg__GoalStatus *)
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__get_const_function__GoalStatusArray__status_list(untyped_member, index));
  action_msgs__msg__GoalStatus * value =
    (action_msgs__msg__GoalStatus *)(untyped_value);
  *value = *item;
}

void action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__assign_function__GoalStatusArray__status_list(
  void * untyped_member, size_t index, const void * untyped_value)
{
  action_msgs__msg__GoalStatus * item =
    ((action_msgs__msg__GoalStatus *)
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__get_function__GoalStatusArray__status_list(untyped_member, index));
  const action_msgs__msg__GoalStatus * value =
    (const action_msgs__msg__GoalStatus *)(untyped_value);
  *item = *value;
}

bool action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__resize_function__GoalStatusArray__status_list(
  void * untyped_member, size_t size)
{
  action_msgs__msg__GoalStatus__Sequence * member =
    (action_msgs__msg__GoalStatus__Sequence *)(untyped_member);
  action_msgs__msg__GoalStatus__Sequence__fini(member);
  return action_msgs__msg__GoalStatus__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_member_array[1] = {
  {
    "status_list",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs__msg__GoalStatusArray, status_list),  // bytes offset in struct
    NULL,  // default value
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__size_function__GoalStatusArray__status_list,  // size() function pointer
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__get_const_function__GoalStatusArray__status_list,  // get_const(index) function pointer
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__get_function__GoalStatusArray__status_list,  // get(index) function pointer
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__fetch_function__GoalStatusArray__status_list,  // fetch(index, &value) function pointer
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__assign_function__GoalStatusArray__status_list,  // assign(index, value) function pointer
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__resize_function__GoalStatusArray__status_list  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_members = {
  "action_msgs__msg",  // message namespace
  "GoalStatusArray",  // message name
  1,  // number of fields
  sizeof(action_msgs__msg__GoalStatusArray),
  false,  // has_any_key_member_
  action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_member_array,  // message members
  action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_init_function,  // function to initialize message memory (memory has to be allocated)
  action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_type_support_handle = {
  0,
  &action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_members,
  get_message_typesupport_handle_function,
  &action_msgs__msg__GoalStatusArray__get_type_hash,
  &action_msgs__msg__GoalStatusArray__get_type_description,
  &action_msgs__msg__GoalStatusArray__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_action_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, msg, GoalStatusArray)() {
  action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, action_msgs, msg, GoalStatus)();
  if (!action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_type_support_handle.typesupport_identifier) {
    action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &action_msgs__msg__GoalStatusArray__rosidl_typesupport_introspection_c__GoalStatusArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
