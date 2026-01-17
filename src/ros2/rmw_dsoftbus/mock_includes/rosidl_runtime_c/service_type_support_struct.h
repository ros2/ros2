// Minimal mock for rosidl_runtime_c/service_type_support_struct.h
#ifndef ROSIDL_RUNTIME_C__SERVICE_TYPE_SUPPORT_STRUCT_H_
#define ROSIDL_RUNTIME_C__SERVICE_TYPE_SUPPORT_STRUCT_H_

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare message type support
struct rosidl_message_type_support_t;

/**
 * Service type support structure.
 * Contains type supports for request and response messages.
 */
typedef struct rosidl_service_type_support_t {
    /// Implementation identifier for this type support (e.g., "rosidl_typesupport_introspection_c")
    const char * typesupport_identifier;

    /// Pointer to the type support implementation data
    const void * data;

    /// Function to get the type support by identifier
    const struct rosidl_service_type_support_t * (*func)(
        const struct rosidl_service_type_support_t *, const char *);
} rosidl_service_type_support_t;

/**
 * Get the service type support handle using a specific typesupport implementation.
 */
#define ROSIDL_GET_SRV_TYPE_SUPPORT(PkgName, SrvName) \
    rosidl_get_service_type_support_handle__##PkgName##__srv__##SrvName()

/**
 * Macro to declare a service type support getter.
 */
#define ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_TYPE_SUPPORT_HANDLE_FUNCTION \
    get_service_type_support_handle

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_RUNTIME_C__SERVICE_TYPE_SUPPORT_STRUCT_H_
