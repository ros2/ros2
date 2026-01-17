// Mock rosidl_typesupport_introspection_c/service_introspection.h

#ifndef ROSIDL_TYPESUPPORT_INTROSPECTION_C__SERVICE_INTROSPECTION_H_
#define ROSIDL_TYPESUPPORT_INTROSPECTION_C__SERVICE_INTROSPECTION_H_

#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

// Service members structure (introspection C)
typedef struct rosidl_typesupport_introspection_c__ServiceMembers {
    const char* service_namespace;
    const char* service_name;

    // Request and response message type supports
    const rosidl_message_type_support_t* request_members_;
    const rosidl_message_type_support_t* response_members_;
} rosidl_typesupport_introspection_c__ServiceMembers;

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_TYPESUPPORT_INTROSPECTION_C__SERVICE_INTROSPECTION_H_
