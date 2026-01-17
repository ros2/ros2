// Minimal mock for rosidl_typesupport_introspection_c/message_introspection.h
#ifndef ROSIDL_TYPESUPPORT_INTROSPECTION_C__MESSAGE_INTROSPECTION_H_
#define ROSIDL_TYPESUPPORT_INTROSPECTION_C__MESSAGE_INTROSPECTION_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// Include field types from the authoritative source
#include "rosidl_typesupport_introspection_c/field_types.h"
// Include rosidl_message_type_support_t definition (not just forward decl)
#include "rosidl_runtime_c/message_type_support_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration
struct rosidl_message_type_support_t;

// Introspection member info
typedef struct rosidl_typesupport_introspection_c__MessageMember_s {
    const char * name_;
    uint8_t type_id_;
    size_t string_upper_bound_;
    const struct rosidl_message_type_support_t * members_;  // For nested messages
    bool is_array_;
    size_t array_size_;
    bool is_upper_bound_;
    size_t offset_;
    size_t size_of_;  // Size of this member type in bytes
    const void * default_value_;
    size_t (*size_function)(const void *);
    const void * (*get_const_function)(const void *, size_t index);
    void * (*get_function)(void *, size_t index);
    void (*fetch_function)(const void *, size_t index, void * output);
    void (*assign_function)(void *, size_t index, const void * input);
    bool (*resize_function)(void *, size_t size);
} rosidl_typesupport_introspection_c__MessageMember;

// Introspection message info
typedef struct rosidl_typesupport_introspection_c__MessageMembers_s {
    const char * message_namespace_;
    const char * message_name_;
    uint32_t member_count_;
    size_t size_of_;
    const rosidl_typesupport_introspection_c__MessageMember * members_;
    void (* init_function)(void *, bool);
    void (* fini_function)(void *);
} rosidl_typesupport_introspection_c__MessageMembers;

// Typesupport identifier
#define ROSIDL_TYPESUPPORT_INTROSPECTION_C__IDENTIFIER_VALUE "rosidl_typesupport_introspection_c"

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_TYPESUPPORT_INTROSPECTION_C__MESSAGE_INTROSPECTION_H_
