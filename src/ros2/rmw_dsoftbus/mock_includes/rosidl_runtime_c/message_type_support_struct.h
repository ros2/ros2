// Minimal mock for rosidl_runtime_c/message_type_support_struct.h
#ifndef ROSIDL_RUNTIME_C__MESSAGE_TYPE_SUPPORT_STRUCT_H_
#define ROSIDL_RUNTIME_C__MESSAGE_TYPE_SUPPORT_STRUCT_H_

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration for type support
struct rosidl_message_type_support_t;

// Forward declare rmw_serialized_message_t
struct rmw_serialized_message_s;
typedef struct rmw_serialized_message_s rmw_serialized_message_t;

// Typesupport callbacks for introspection-based serialization
typedef struct rosidl_message_type_support_callbacks_t {
    const char * message_namespace_;
    const char * message_name_;
    size_t message_size;  // Size of the message in bytes (0 if variable-length)
    // Function pointer types for serialization callbacks
    bool (*cdr_serialize)(const void * untyped_ros_message, void * cdr_stream);
    bool (*cdr_deserialize)(void * cdr_stream, void * untyped_ros_message);
    size_t (*get_serialized_size)(const void * untyped_ros_message);
    size_t (*max_serialized_size)(void);
    // Serialize function for rmw_serialized_message_t
    bool (*serialize)(const void * ros_message, rmw_serialized_message_t * serialized_message);
    // Deserialize function from rmw_serialized_message_t
    bool (*deserialize)(const rmw_serialized_message_t * serialized_message, void * ros_message);
} rosidl_message_type_support_callbacks_t;

typedef struct rosidl_message_type_support_t {
    const char * typesupport_identifier;
    const void * data;
    const struct rosidl_message_type_support_t * (*func)(
        const struct rosidl_message_type_support_t *, const char *);
} rosidl_message_type_support_t;

// Note: rosidl_service_type_support_t is defined in service_type_support_struct.h

// Macro to get message type support
#define ROSIDL_GET_MSG_TYPE_SUPPORT(pkg, subfolder, msg) \
    rosidl_typesupport_c__get_message_type_support_handle__##pkg##__##subfolder##__##msg()

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_RUNTIME_C__MESSAGE_TYPE_SUPPORT_STRUCT_H_
