// Comprehensive mock for rmw/types.h (for cross-compilation only)
// This provides all necessary RMW types for building rmw_dsoftbus without full ROS2 SDK
#ifndef RMW__TYPES_H_
#define RMW__TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

// Forward declaration for rcutils_allocator_t
#include <rcutils/allocator.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// Visibility macros
// ============================================================================
#ifndef RMW_PUBLIC
#define RMW_PUBLIC
#endif

#ifndef RMW_PUBLIC_TYPE
#define RMW_PUBLIC_TYPE
#endif

#ifndef RMW_WARN_UNUSED
#define RMW_WARN_UNUSED
#endif

// ============================================================================
// RMW GID (Global Identifier)
// ============================================================================
#define RMW_GID_STORAGE_SIZE 24

typedef struct rmw_gid_s {
    const char * implementation_identifier;
    uint8_t data[RMW_GID_STORAGE_SIZE];
} rmw_gid_t;

// ============================================================================
// QoS Policy Types
// ============================================================================
typedef enum rmw_qos_reliability_policy_e {
    RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT,
    RMW_QOS_POLICY_RELIABILITY_RELIABLE,
    RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT,
    RMW_QOS_POLICY_RELIABILITY_UNKNOWN,
    RMW_QOS_POLICY_RELIABILITY_BEST_AVAILABLE
} rmw_qos_reliability_policy_t;

typedef enum rmw_qos_durability_policy_e {
    RMW_QOS_POLICY_DURABILITY_SYSTEM_DEFAULT,
    RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL,
    RMW_QOS_POLICY_DURABILITY_VOLATILE,
    RMW_QOS_POLICY_DURABILITY_UNKNOWN
} rmw_qos_durability_policy_t;

typedef enum rmw_qos_history_policy_e {
    RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT,
    RMW_QOS_POLICY_HISTORY_KEEP_LAST,
    RMW_QOS_POLICY_HISTORY_KEEP_ALL,
    RMW_QOS_POLICY_HISTORY_UNKNOWN
} rmw_qos_history_policy_t;

typedef enum rmw_qos_liveliness_policy_e {
    RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT,
    RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
    RMW_QOS_POLICY_LIVELINESS_MANUAL_BY_NODE,
    RMW_QOS_POLICY_LIVELINESS_MANUAL_BY_TOPIC,
    RMW_QOS_POLICY_LIVELINESS_UNKNOWN
} rmw_qos_liveliness_policy_t;

typedef struct rmw_time_s {
    uint64_t sec;
    uint64_t nsec;
} rmw_time_t;

typedef struct rmw_qos_profile_s {
    rmw_qos_history_policy_t history;
    size_t depth;
    rmw_qos_reliability_policy_t reliability;
    rmw_qos_durability_policy_t durability;
    rmw_time_t deadline;
    rmw_time_t lifespan;
    rmw_qos_liveliness_policy_t liveliness;
    rmw_time_t liveliness_lease_duration;
    bool avoid_ros_namespace_conventions;
} rmw_qos_profile_t;

// NOTE: rmw_qos_profile_default is defined in rmw/rmw.h, not here

// ============================================================================
// Return Types
// ============================================================================
typedef int32_t rmw_ret_t;
#define RMW_RET_OK 0
#define RMW_RET_ERROR 1
#define RMW_RET_TIMEOUT 2
#define RMW_RET_BAD_ALLOC 10
#define RMW_RET_INVALID_ARGUMENT 11
#define RMW_RET_UNSUPPORTED 12
#define RMW_RET_INCORRECT_RMW_IMPLEMENTATION 13
#define RMW_RET_NODE_NAME_NON_EXISTENT 14

// ============================================================================
// Serialized Message Type
// ============================================================================
typedef struct rmw_serialized_message_s {
    uint8_t * buffer;
    size_t buffer_length;
    size_t buffer_capacity;
    void * allocator;  // rcutils_allocator_t*
} rmw_serialized_message_t;

// ============================================================================
// Context and Init Types
// ============================================================================
typedef struct rmw_context_s {
    uint64_t instance_id;
    const char * implementation_identifier;
    void * impl;
    void * options;
} rmw_context_t;

// Security options (minimal stub)
typedef struct rmw_security_options_s {
    int enforce_security;
    const char * security_root_path;
} rmw_security_options_t;

typedef struct rmw_init_options_s {
    uint64_t instance_id;
    const char * implementation_identifier;
    size_t domain_id;
    rmw_security_options_t security_options;
    rcutils_allocator_t allocator;
    void * impl;
    const char * enclave;
} rmw_init_options_t;

// ============================================================================
// Node Type
// ============================================================================
typedef struct rmw_node_s {
    const char * implementation_identifier;
    void * data;
    const char * name;
    const char * namespace_;
    rmw_context_t * context;
} rmw_node_t;

// ============================================================================
// Publisher Type
// ============================================================================
typedef struct rmw_publisher_options_s {
    void * rmw_specific_publisher_payload;
    bool require_unique_network_flow_endpoints;
} rmw_publisher_options_t;

typedef struct rmw_publisher_s {
    const char * implementation_identifier;
    void * data;
    const char * topic_name;
    rmw_publisher_options_t options;
    bool can_loan_messages;
} rmw_publisher_t;

// ============================================================================
// Subscription Type
// ============================================================================
typedef struct rmw_subscription_options_s {
    void * rmw_specific_subscription_payload;
    bool ignore_local_publications;
    bool require_unique_network_flow_endpoints;
} rmw_subscription_options_t;

typedef struct rmw_subscription_s {
    const char * implementation_identifier;
    void * data;
    const char * topic_name;
    rmw_subscription_options_t options;
    bool can_loan_messages;
    bool is_cft_enabled;
} rmw_subscription_t;

// ============================================================================
// Service and Client Types
// ============================================================================
typedef struct rmw_service_s {
    const char * implementation_identifier;
    void * data;
    const char * service_name;
} rmw_service_t;

typedef struct rmw_client_s {
    const char * implementation_identifier;
    void * data;
    const char * service_name;
} rmw_client_t;

// ============================================================================
// Guard Condition Type
// ============================================================================
typedef struct rmw_guard_condition_s {
    const char * implementation_identifier;
    void * data;
    rmw_context_t * context;
} rmw_guard_condition_t;

// ============================================================================
// Wait Set Type
// ============================================================================
typedef struct rmw_wait_set_s {
    const char * implementation_identifier;
    void * data;
} rmw_wait_set_t;

// ============================================================================
// Subscription Allocation Type
// ============================================================================
typedef struct rmw_subscription_allocation_s {
    const char * implementation_identifier;
    void * data;
    void * impl;
} rmw_subscription_allocation_t;

// ============================================================================
// Publisher Allocation Type
// ============================================================================
typedef struct rmw_publisher_allocation_s {
    const char * implementation_identifier;
    void * data;
    void * impl;
} rmw_publisher_allocation_t;

// ============================================================================
// Message Info Type
// ============================================================================
typedef struct rmw_message_info_s {
    rmw_time_t source_timestamp;
    rmw_time_t received_timestamp;
    uint64_t publication_sequence_number;
    uint64_t reception_sequence_number;
    rmw_gid_t publisher_gid;
    bool from_intra_process;
} rmw_message_info_t;

// ============================================================================
// Service Info Type
// ============================================================================
// ============================================================================
// Request ID Type
// ============================================================================
typedef struct rmw_request_id_s {
    int8_t writer_guid[16];
    int64_t sequence_number;
} rmw_request_id_t;

typedef struct rmw_service_info_s {
    rmw_time_t source_timestamp;
    rmw_time_t received_timestamp;
    rmw_request_id_t request_id;
} rmw_service_info_t;

// ============================================================================
// Event Types
// ============================================================================
typedef enum rmw_event_type_e {
    RMW_EVENT_LIVELINESS_CHANGED = 0,
    RMW_EVENT_REQUESTED_DEADLINE_MISSED,
    RMW_EVENT_LIVELINESS_LOST,
    RMW_EVENT_OFFERED_DEADLINE_MISSED,
    RMW_EVENT_MESSAGE_LOST,
    RMW_EVENT_OFFERED_QOS_INCOMPATIBLE,
    RMW_EVENT_REQUESTED_QOS_INCOMPATIBLE,
    RMW_EVENT_SUBSCRIPTION_MATCHED,
    RMW_EVENT_PUBLICATION_MATCHED,
    RMW_EVENT_INVALID
} rmw_event_type_t;

typedef struct rmw_event_s {
    const char * implementation_identifier;
    void * data;
    rmw_event_type_t event_type;
} rmw_event_t;

// ============================================================================
// Topic Endpoint Info Types
// ============================================================================
typedef enum rmw_endpoint_type_e {
    RMW_ENDPOINT_INVALID = 0,
    RMW_ENDPOINT_PUBLISHER,
    RMW_ENDPOINT_SUBSCRIPTION
} rmw_endpoint_type_t;

typedef struct rmw_topic_endpoint_info_s {
    const char * node_name;
    const char * node_namespace;
    const char * topic_type;
    rmw_endpoint_type_t endpoint_type;
    uint8_t endpoint_gid[RMW_GID_STORAGE_SIZE];
    rmw_qos_profile_t qos_profile;
} rmw_topic_endpoint_info_t;

typedef struct rmw_topic_endpoint_info_array_s {
    size_t size;
    rmw_topic_endpoint_info_t * info_array;
} rmw_topic_endpoint_info_array_t;

// ============================================================================
// Names and Types Info
// ============================================================================
// Note: rcutils_string_array_t is defined in rcutils/allocator.h
// The types field is an array of rcutils_string_array_t, one per name
typedef struct rmw_names_and_types_s {
    rcutils_string_array_t names;
    rcutils_string_array_t * types;  // Array of string arrays (one per name entry)
} rmw_names_and_types_t;

// ============================================================================
// Content Filter Options
// ============================================================================
typedef struct rmw_subscription_content_filter_options_s {
    char * filter_expression;
    rcutils_string_array_t expression_parameters;
} rmw_subscription_content_filter_options_t;

// ============================================================================
// Dynamic Message Type
// ============================================================================
// Forward declaration
struct rosidl_message_type_support_t;

typedef struct rmw_dynamic_message_s {
    void * data;
    const struct rosidl_message_type_support_t * type_support;
} rmw_dynamic_message_t;

// ============================================================================
// Event Callback Type
// ============================================================================
typedef void (* rmw_event_callback_t)(const void * user_data, size_t number_of_events);

// ============================================================================
// Feature Support
// ============================================================================
typedef enum rmw_feature_e {
    RMW_FEATURE_MESSAGE_INFO_PUBLICATION_SEQUENCE_NUMBER = 0,
    RMW_FEATURE_MESSAGE_INFO_RECEPTION_SEQUENCE_NUMBER,
    RMW_FEATURE_COUNT
} rmw_feature_t;

// ============================================================================
// Dynamic Type Support (stub)
// ============================================================================
typedef struct rosidl_dynamic_typesupport_serialization_support_s {
    const char * serialization_library_identifier;
    void * impl;
} rosidl_dynamic_typesupport_serialization_support_t;

// ============================================================================
// Network Flow Endpoints
// ============================================================================
typedef enum rmw_transport_protocol_e {
    RMW_TRANSPORT_PROTOCOL_UNKNOWN = 0,
    RMW_TRANSPORT_PROTOCOL_UDP,
    RMW_TRANSPORT_PROTOCOL_TCP,
    RMW_TRANSPORT_PROTOCOL_COUNT
} rmw_transport_protocol_t;

typedef enum rmw_internet_protocol_e {
    RMW_INTERNET_PROTOCOL_UNKNOWN = 0,
    RMW_INTERNET_PROTOCOL_IPV4,
    RMW_INTERNET_PROTOCOL_IPV6,
    RMW_INTERNET_PROTOCOL_COUNT
} rmw_internet_protocol_t;

typedef struct rmw_network_flow_endpoint_s {
    rmw_transport_protocol_t transport_protocol;
    rmw_internet_protocol_t internet_protocol;
    uint16_t transport_port;
    uint32_t flow_label;
    uint32_t dscp;
    char internet_address[48];
} rmw_network_flow_endpoint_t;

typedef struct rmw_network_flow_endpoint_array_s {
    size_t size;
    rmw_network_flow_endpoint_t * network_flow_endpoint;
    void * allocator;
} rmw_network_flow_endpoint_array_t;

// ============================================================================
// Logging Level
// ============================================================================
typedef enum RCUTILS_LOG_SEVERITY_e {
    RCUTILS_LOG_SEVERITY_UNSET = 0,
    RCUTILS_LOG_SEVERITY_DEBUG = 10,
    RCUTILS_LOG_SEVERITY_INFO = 20,
    RCUTILS_LOG_SEVERITY_WARN = 30,
    RCUTILS_LOG_SEVERITY_ERROR = 40,
    RCUTILS_LOG_SEVERITY_FATAL = 50
} RCUTILS_LOG_SEVERITY;

// RMW log severity type
typedef enum rmw_log_severity_e {
    RMW_LOG_SEVERITY_DEBUG = RCUTILS_LOG_SEVERITY_DEBUG,
    RMW_LOG_SEVERITY_INFO = RCUTILS_LOG_SEVERITY_INFO,
    RMW_LOG_SEVERITY_WARN = RCUTILS_LOG_SEVERITY_WARN,
    RMW_LOG_SEVERITY_ERROR = RCUTILS_LOG_SEVERITY_ERROR,
    RMW_LOG_SEVERITY_FATAL = RCUTILS_LOG_SEVERITY_FATAL
} rmw_log_severity_t;

// ============================================================================
// QoS Compatibility
// ============================================================================
typedef enum rmw_qos_compatibility_type_e {
    RMW_QOS_COMPATIBILITY_OK = 0,
    RMW_QOS_COMPATIBILITY_WARNING,
    RMW_QOS_COMPATIBILITY_ERROR
} rmw_qos_compatibility_type_t;

// ============================================================================
// Duration Constants
// ============================================================================
#define RMW_DURATION_INFINITE {INT32_MAX, UINT32_MAX}
#define RMW_DURATION_UNSPECIFIED {0, 0}

// QoS Default Values
static const rmw_time_t RMW_QOS_DEADLINE_DEFAULT = {0, 0};
static const rmw_time_t RMW_QOS_LIFESPAN_DEFAULT = {0, 0};
static const rmw_time_t RMW_QOS_LIVELINESS_LEASE_DURATION_DEFAULT = {0, 0};

// ============================================================================
// Message Sequence Types (for batch operations)
// ============================================================================
typedef struct rmw_message_sequence_s {
    void ** data;
    size_t size;
    size_t capacity;
} rmw_message_sequence_t;

typedef struct rmw_message_info_sequence_s {
    rmw_message_info_t * data;
    size_t size;
    size_t capacity;
} rmw_message_info_sequence_t;

// ============================================================================
// Serialized Message Functions
// ============================================================================
static inline rmw_ret_t rmw_serialized_message_resize(
    rmw_serialized_message_t * serialized_message,
    size_t new_size)
{
    if (!serialized_message) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (new_size > serialized_message->buffer_capacity) {
        uint8_t * new_buffer = (uint8_t *)realloc(
            serialized_message->buffer, new_size);
        if (!new_buffer) {
            return RMW_RET_BAD_ALLOC;
        }
        serialized_message->buffer = new_buffer;
        serialized_message->buffer_capacity = new_size;
    }
    serialized_message->buffer_length = new_size;
    return RMW_RET_OK;
}

static inline rmw_serialized_message_t rmw_get_zero_initialized_serialized_message(void) {
    rmw_serialized_message_t msg = {NULL, 0, 0, NULL};
    return msg;
}

// ============================================================================
// Message Info Initialization
// ============================================================================
static inline rmw_message_info_t rmw_get_zero_initialized_message_info(void) {
    rmw_message_info_t info;
    info.source_timestamp.sec = 0;
    info.source_timestamp.nsec = 0;
    info.received_timestamp.sec = 0;
    info.received_timestamp.nsec = 0;
    info.publication_sequence_number = 0;
    info.reception_sequence_number = 0;
    info.publisher_gid.implementation_identifier = NULL;
    for (size_t i = 0; i < RMW_GID_STORAGE_SIZE; ++i) {
        info.publisher_gid.data[i] = 0;
    }
    info.from_intra_process = false;
    return info;
}

// ============================================================================
// Wait Set Array Types for rmw_wait()
// ============================================================================
typedef struct rmw_subscriptions_s {
    size_t subscriber_count;
    void ** subscribers;
} rmw_subscriptions_t;

typedef struct rmw_guard_conditions_s {
    size_t guard_condition_count;
    void ** guard_conditions;
} rmw_guard_conditions_t;

typedef struct rmw_services_s {
    size_t service_count;
    void ** services;
} rmw_services_t;

typedef struct rmw_clients_s {
    size_t client_count;
    void ** clients;
} rmw_clients_t;

typedef struct rmw_events_s {
    size_t event_count;
    void ** events;
} rmw_events_t;

#ifdef __cplusplus
}
#endif

#endif  // RMW__TYPES_H_
