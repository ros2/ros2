# ROS2 RMW Interface Research Report

## 1. Overview

RMW (ROS Middleware Interface) is the abstraction layer between ROS2 and the underlying middleware (DDS or custom implementation). This report provides a comprehensive analysis of the RMW interface for the purpose of implementing `rmw_dsoftbus`.

**Source Location**: `/home/jiusi/ros2/src/ros2/rmw/rmw/include/rmw/`

---

## 2. Core Data Types

### 2.1 Node Structure (`rmw_node_t`)

```c
typedef struct rmw_node_s {
    const char * implementation_identifier;  // RMW implementation name
    void * data;                             // Implementation-specific data
    const char * name;                       // Node name
    const char * namespace_;                 // Node namespace
    rmw_context_t * context;                 // Associated context
} rmw_node_t;
```

### 2.2 Publisher Structure (`rmw_publisher_t`)

```c
typedef struct rmw_publisher_s {
    const char * implementation_identifier;
    void * data;                             // Implementation-specific data
    const char * topic_name;
    rmw_publisher_options_t options;
    bool can_loan_messages;                  // Message loaning support
} rmw_publisher_t;
```

### 2.3 Subscription Structure (`rmw_subscription_t`)

```c
typedef struct rmw_subscription_s {
    const char * implementation_identifier;
    void * data;
    const char * topic_name;
    rmw_subscription_options_t options;
    bool can_loan_messages;
    bool is_cft_enabled;                     // Content filtered topic enabled
} rmw_subscription_t;
```

### 2.4 Service Structure (`rmw_service_t`)

```c
typedef struct rmw_service_s {
    const char * implementation_identifier;
    void * data;
    const char * service_name;
} rmw_service_t;
```

### 2.5 Client Structure (`rmw_client_t`)

```c
typedef struct rmw_client_s {
    const char * implementation_identifier;
    void * data;
    const char * service_name;
} rmw_client_t;
```

### 2.6 Guard Condition (`rmw_guard_condition_t`)

```c
typedef struct rmw_guard_condition_s {
    const char * implementation_identifier;
    void * data;
    rmw_context_t * context;
} rmw_guard_condition_t;
```

### 2.7 Wait Set (`rmw_wait_set_t`)

```c
typedef struct rmw_wait_set_s {
    const char * implementation_identifier;
    rmw_guard_conditions_t * guard_conditions;
    void * data;
} rmw_wait_set_t;
```

### 2.8 GID (Global Identifier)

```c
#define RMW_GID_STORAGE_SIZE 16u  // 128 bits

typedef struct rmw_gid_s {
    const char * implementation_identifier;
    uint8_t data[RMW_GID_STORAGE_SIZE];
} rmw_gid_t;
```

### 2.9 Message Info

```c
typedef struct rmw_message_info_s {
    rmw_time_point_value_t source_timestamp;      // Publisher timestamp
    rmw_time_point_value_t received_timestamp;    // Subscription timestamp
    uint64_t publication_sequence_number;
    uint64_t reception_sequence_number;
    rmw_gid_t publisher_gid;
    bool from_intra_process;
} rmw_message_info_t;
```

### 2.10 Request ID (for services)

```c
typedef struct rmw_request_id_s {
    uint8_t writer_guid[RMW_GID_STORAGE_SIZE];
    int64_t sequence_number;
} rmw_request_id_t;
```

---

## 3. QoS (Quality of Service) Configuration

### 3.1 QoS Profile Structure

```c
typedef struct rmw_qos_profile_s {
    enum rmw_qos_history_policy_e history;
    size_t depth;
    enum rmw_qos_reliability_policy_e reliability;
    enum rmw_qos_durability_policy_e durability;
    struct rmw_time_s deadline;
    struct rmw_time_s lifespan;
    enum rmw_qos_liveliness_policy_e liveliness;
    struct rmw_time_s liveliness_lease_duration;
    bool avoid_ros_namespace_conventions;
} rmw_qos_profile_t;
```

### 3.2 History Policy

| Value | Description |
|-------|-------------|
| `RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT` | Implementation default |
| `RMW_QOS_POLICY_HISTORY_KEEP_LAST` | Keep up to N samples |
| `RMW_QOS_POLICY_HISTORY_KEEP_ALL` | Keep all samples |
| `RMW_QOS_POLICY_HISTORY_UNKNOWN` | Not yet set |

### 3.3 Reliability Policy

| Value | Description |
|-------|-------------|
| `RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT` | Implementation default |
| `RMW_QOS_POLICY_RELIABILITY_RELIABLE` | Guaranteed delivery with retry |
| `RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT` | Best effort, may lose messages |
| `RMW_QOS_POLICY_RELIABILITY_BEST_AVAILABLE` | Match discovered endpoints |
| `RMW_QOS_POLICY_RELIABILITY_UNKNOWN` | Not yet set |

### 3.4 Durability Policy

| Value | Description |
|-------|-------------|
| `RMW_QOS_POLICY_DURABILITY_SYSTEM_DEFAULT` | Implementation default |
| `RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL` | Persist for late-joiners |
| `RMW_QOS_POLICY_DURABILITY_VOLATILE` | No persistence |
| `RMW_QOS_POLICY_DURABILITY_BEST_AVAILABLE` | Match discovered endpoints |
| `RMW_QOS_POLICY_DURABILITY_UNKNOWN` | Not yet set |

### 3.5 Liveliness Policy

| Value | Description |
|-------|-------------|
| `RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT` | Implementation default |
| `RMW_QOS_POLICY_LIVELINESS_AUTOMATIC` | RMW layer manages liveliness |
| `RMW_QOS_POLICY_LIVELINESS_MANUAL_BY_TOPIC` | Application asserts per topic |
| `RMW_QOS_POLICY_LIVELINESS_BEST_AVAILABLE` | Match discovered endpoints |
| `RMW_QOS_POLICY_LIVELINESS_UNKNOWN` | Not yet set |

### 3.6 Predefined QoS Profiles

| Profile | History | Depth | Reliability | Durability |
|---------|---------|-------|-------------|------------|
| `rmw_qos_profile_default` | KEEP_LAST | 10 | RELIABLE | VOLATILE |
| `rmw_qos_profile_sensor_data` | KEEP_LAST | 5 | BEST_EFFORT | VOLATILE |
| `rmw_qos_profile_services_default` | KEEP_LAST | 10 | RELIABLE | VOLATILE |
| `rmw_qos_profile_parameters` | KEEP_LAST | 1000 | RELIABLE | VOLATILE |
| `rmw_qos_profile_parameter_events` | KEEP_LAST | 1000 | RELIABLE | VOLATILE |
| `rmw_qos_profile_rosout_default` | KEEP_LAST | 1000 | RELIABLE | TRANSIENT_LOCAL |

---

## 4. Return Types

```c
typedef int32_t rmw_ret_t;

#define RMW_RET_OK                          0   // Success
#define RMW_RET_ERROR                       1   // Generic error
#define RMW_RET_TIMEOUT                     2   // Timeout exceeded
#define RMW_RET_UNSUPPORTED                 3   // Not supported
#define RMW_RET_BAD_ALLOC                   10  // Memory allocation failed
#define RMW_RET_INVALID_ARGUMENT            11  // Invalid argument
#define RMW_RET_INCORRECT_RMW_IMPLEMENTATION 12 // Wrong RMW implementation
#define RMW_RET_NODE_NAME_NON_EXISTENT      203 // Node not found
```

---

## 5. Required RMW Functions

### 5.1 Initialization & Shutdown (init.h)

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_init` | `rmw_ret_t rmw_init(const rmw_init_options_t*, rmw_context_t*)` | Initialize middleware |
| `rmw_shutdown` | `rmw_ret_t rmw_shutdown(rmw_context_t*)` | Shutdown middleware |
| `rmw_context_fini` | `rmw_ret_t rmw_context_fini(rmw_context_t*)` | Finalize context |
| `rmw_init_options_init` | `rmw_ret_t rmw_init_options_init(rmw_init_options_t*, rcutils_allocator_t)` | Init options |
| `rmw_init_options_copy` | `rmw_ret_t rmw_init_options_copy(const rmw_init_options_t*, rmw_init_options_t*)` | Copy options |
| `rmw_init_options_fini` | `rmw_ret_t rmw_init_options_fini(rmw_init_options_t*)` | Finalize options |

### 5.2 Identity Functions

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_get_implementation_identifier` | `const char* rmw_get_implementation_identifier(void)` | Get impl name |
| `rmw_get_serialization_format` | `const char* rmw_get_serialization_format(void)` | Get serialization format |

### 5.3 Node Management

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_create_node` | `rmw_node_t* rmw_create_node(rmw_context_t*, const char* name, const char* namespace_)` | Create node |
| `rmw_destroy_node` | `rmw_ret_t rmw_destroy_node(rmw_node_t*)` | Destroy node |
| `rmw_node_get_graph_guard_condition` | `const rmw_guard_condition_t* rmw_node_get_graph_guard_condition(const rmw_node_t*)` | Get graph GC |

### 5.4 Publisher Management

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_create_publisher` | `rmw_publisher_t* rmw_create_publisher(const rmw_node_t*, const rosidl_message_type_support_t*, const char*, const rmw_qos_profile_t*, const rmw_publisher_options_t*)` | Create publisher |
| `rmw_destroy_publisher` | `rmw_ret_t rmw_destroy_publisher(rmw_node_t*, rmw_publisher_t*)` | Destroy publisher |
| `rmw_publish` | `rmw_ret_t rmw_publish(const rmw_publisher_t*, const void* ros_message, rmw_publisher_allocation_t*)` | Publish message |
| `rmw_publish_serialized_message` | `rmw_ret_t rmw_publish_serialized_message(const rmw_publisher_t*, const rmw_serialized_message_t*, rmw_publisher_allocation_t*)` | Publish serialized |
| `rmw_publish_loaned_message` | `rmw_ret_t rmw_publish_loaned_message(const rmw_publisher_t*, void*, rmw_publisher_allocation_t*)` | Publish loaned |
| `rmw_borrow_loaned_message` | `rmw_ret_t rmw_borrow_loaned_message(const rmw_publisher_t*, const rosidl_message_type_support_t*, void**)` | Borrow message |
| `rmw_return_loaned_message_from_publisher` | `rmw_ret_t rmw_return_loaned_message_from_publisher(const rmw_publisher_t*, void*)` | Return loaned |
| `rmw_publisher_count_matched_subscriptions` | `rmw_ret_t rmw_publisher_count_matched_subscriptions(const rmw_publisher_t*, size_t*)` | Count matched subs |
| `rmw_publisher_get_actual_qos` | `rmw_ret_t rmw_publisher_get_actual_qos(const rmw_publisher_t*, rmw_qos_profile_t*)` | Get actual QoS |
| `rmw_publisher_assert_liveliness` | `rmw_ret_t rmw_publisher_assert_liveliness(const rmw_publisher_t*)` | Assert liveliness |
| `rmw_publisher_wait_for_all_acked` | `rmw_ret_t rmw_publisher_wait_for_all_acked(const rmw_publisher_t*, rmw_time_t)` | Wait for ACKs |
| `rmw_init_publisher_allocation` | `rmw_ret_t rmw_init_publisher_allocation(...)` | Init allocation |
| `rmw_fini_publisher_allocation` | `rmw_ret_t rmw_fini_publisher_allocation(rmw_publisher_allocation_t*)` | Finalize allocation |

### 5.5 Subscription Management

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_create_subscription` | `rmw_subscription_t* rmw_create_subscription(const rmw_node_t*, const rosidl_message_type_support_t*, const char*, const rmw_qos_profile_t*, const rmw_subscription_options_t*)` | Create subscription |
| `rmw_destroy_subscription` | `rmw_ret_t rmw_destroy_subscription(rmw_node_t*, rmw_subscription_t*)` | Destroy subscription |
| `rmw_take` | `rmw_ret_t rmw_take(const rmw_subscription_t*, void*, bool*, rmw_subscription_allocation_t*)` | Take message |
| `rmw_take_with_info` | `rmw_ret_t rmw_take_with_info(const rmw_subscription_t*, void*, bool*, rmw_message_info_t*, rmw_subscription_allocation_t*)` | Take with info |
| `rmw_take_sequence` | `rmw_ret_t rmw_take_sequence(const rmw_subscription_t*, size_t, rmw_message_sequence_t*, rmw_message_info_sequence_t*, size_t*, rmw_subscription_allocation_t*)` | Take multiple |
| `rmw_take_serialized_message` | `rmw_ret_t rmw_take_serialized_message(const rmw_subscription_t*, rmw_serialized_message_t*, bool*, rmw_subscription_allocation_t*)` | Take serialized |
| `rmw_take_serialized_message_with_info` | `rmw_ret_t rmw_take_serialized_message_with_info(...)` | Take serialized with info |
| `rmw_take_loaned_message` | `rmw_ret_t rmw_take_loaned_message(const rmw_subscription_t*, void**, bool*, rmw_subscription_allocation_t*)` | Take loaned |
| `rmw_take_loaned_message_with_info` | `rmw_ret_t rmw_take_loaned_message_with_info(...)` | Take loaned with info |
| `rmw_return_loaned_message_from_subscription` | `rmw_ret_t rmw_return_loaned_message_from_subscription(const rmw_subscription_t*, void*)` | Return loaned |
| `rmw_subscription_count_matched_publishers` | `rmw_ret_t rmw_subscription_count_matched_publishers(const rmw_subscription_t*, size_t*)` | Count matched pubs |
| `rmw_subscription_get_actual_qos` | `rmw_ret_t rmw_subscription_get_actual_qos(const rmw_subscription_t*, rmw_qos_profile_t*)` | Get actual QoS |
| `rmw_subscription_set_content_filter` | `rmw_ret_t rmw_subscription_set_content_filter(rmw_subscription_t*, const rmw_subscription_content_filter_options_t*)` | Set content filter |
| `rmw_subscription_get_content_filter` | `rmw_ret_t rmw_subscription_get_content_filter(...)` | Get content filter |
| `rmw_init_subscription_allocation` | `rmw_ret_t rmw_init_subscription_allocation(...)` | Init allocation |
| `rmw_fini_subscription_allocation` | `rmw_ret_t rmw_fini_subscription_allocation(rmw_subscription_allocation_t*)` | Finalize allocation |

### 5.6 Service Server

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_create_service` | `rmw_service_t* rmw_create_service(const rmw_node_t*, const rosidl_service_type_support_t*, const char*, const rmw_qos_profile_t*)` | Create service |
| `rmw_destroy_service` | `rmw_ret_t rmw_destroy_service(rmw_node_t*, rmw_service_t*)` | Destroy service |
| `rmw_take_request` | `rmw_ret_t rmw_take_request(const rmw_service_t*, rmw_service_info_t*, void*, bool*)` | Take request |
| `rmw_send_response` | `rmw_ret_t rmw_send_response(const rmw_service_t*, rmw_request_id_t*, void*)` | Send response |
| `rmw_service_request_subscription_get_actual_qos` | `rmw_ret_t rmw_service_request_subscription_get_actual_qos(const rmw_service_t*, rmw_qos_profile_t*)` | Get request QoS |
| `rmw_service_response_publisher_get_actual_qos` | `rmw_ret_t rmw_service_response_publisher_get_actual_qos(const rmw_service_t*, rmw_qos_profile_t*)` | Get response QoS |

### 5.7 Service Client

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_create_client` | `rmw_client_t* rmw_create_client(const rmw_node_t*, const rosidl_service_type_support_t*, const char*, const rmw_qos_profile_t*)` | Create client |
| `rmw_destroy_client` | `rmw_ret_t rmw_destroy_client(rmw_node_t*, rmw_client_t*)` | Destroy client |
| `rmw_send_request` | `rmw_ret_t rmw_send_request(const rmw_client_t*, const void*, int64_t*)` | Send request |
| `rmw_take_response` | `rmw_ret_t rmw_take_response(const rmw_client_t*, rmw_service_info_t*, void*, bool*)` | Take response |
| `rmw_client_request_publisher_get_actual_qos` | `rmw_ret_t rmw_client_request_publisher_get_actual_qos(const rmw_client_t*, rmw_qos_profile_t*)` | Get request QoS |
| `rmw_client_response_subscription_get_actual_qos` | `rmw_ret_t rmw_client_response_subscription_get_actual_qos(const rmw_client_t*, rmw_qos_profile_t*)` | Get response QoS |

### 5.8 Guard Conditions

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_create_guard_condition` | `rmw_guard_condition_t* rmw_create_guard_condition(rmw_context_t*)` | Create guard condition |
| `rmw_destroy_guard_condition` | `rmw_ret_t rmw_destroy_guard_condition(rmw_guard_condition_t*)` | Destroy guard condition |
| `rmw_trigger_guard_condition` | `rmw_ret_t rmw_trigger_guard_condition(const rmw_guard_condition_t*)` | Trigger guard condition |

### 5.9 Wait Set & Waiting

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_create_wait_set` | `rmw_wait_set_t* rmw_create_wait_set(rmw_context_t*, size_t max_conditions)` | Create wait set |
| `rmw_destroy_wait_set` | `rmw_ret_t rmw_destroy_wait_set(rmw_wait_set_t*)` | Destroy wait set |
| `rmw_wait` | `rmw_ret_t rmw_wait(rmw_subscriptions_t*, rmw_guard_conditions_t*, rmw_services_t*, rmw_clients_t*, rmw_events_t*, rmw_wait_set_t*, const rmw_time_t*)` | Wait for events |

### 5.10 Serialization

| Function | Signature | Description |
|----------|-----------|-------------|
| `rmw_serialize` | `rmw_ret_t rmw_serialize(const void*, const rosidl_message_type_support_t*, rmw_serialized_message_t*)` | Serialize message |
| `rmw_deserialize` | `rmw_ret_t rmw_deserialize(const rmw_serialized_message_t*, const rosidl_message_type_support_t*, void*)` | Deserialize message |
| `rmw_get_serialized_message_size` | `rmw_ret_t rmw_get_serialized_message_size(const rosidl_message_type_support_t*, const rosidl_runtime_c__Sequence__bound*, size_t*)` | Get serialized size |

### 5.11 Graph Introspection

| Function | Description |
|----------|-------------|
| `rmw_get_node_names` | Get all node names and namespaces |
| `rmw_get_node_names_with_enclaves` | Get nodes with enclave info |
| `rmw_count_publishers` | Count publishers for a topic |
| `rmw_count_subscribers` | Count subscribers for a topic |
| `rmw_count_clients` | Count clients for a service |
| `rmw_count_services` | Count services |
| `rmw_get_topic_names_and_types` | Get all topic names and types |
| `rmw_get_subscriber_names_and_types_by_node` | Get topics a node subscribes to |
| `rmw_get_publisher_names_and_types_by_node` | Get topics a node publishes |
| `rmw_get_service_names_and_types_by_node` | Get services a node provides |
| `rmw_get_client_names_and_types_by_node` | Get services a node uses as client |
| `rmw_service_server_is_available` | Check if service server exists |
| `rmw_get_gid_for_publisher` | Get publisher GID |
| `rmw_get_gid_for_client` | Get client GID |
| `rmw_compare_gids_equal` | Compare two GIDs |

### 5.12 Events

| Function | Description |
|----------|-------------|
| `rmw_publisher_event_init` | Initialize publisher event |
| `rmw_subscription_event_init` | Initialize subscription event |
| `rmw_take_event` | Take event |
| `rmw_event_fini` | Finalize event |
| `rmw_event_type_is_supported` | Check if event type is supported |

### 5.13 Callbacks

| Function | Description |
|----------|-------------|
| `rmw_subscription_set_on_new_message_callback` | Set message callback |
| `rmw_service_set_on_new_request_callback` | Set service request callback |
| `rmw_client_set_on_new_response_callback` | Set client response callback |
| `rmw_event_set_callback` | Set event callback |

### 5.14 Logging

| Function | Description |
|----------|-------------|
| `rmw_set_log_severity` | Set log severity level |

### 5.15 Features Query

| Function | Description |
|----------|-------------|
| `rmw_feature_supported` | Check if feature is supported |

---

## 6. Event Types

```c
typedef enum rmw_event_type_e {
    RMW_EVENT_INVALID = 0,

    // Subscription events
    RMW_EVENT_LIVELINESS_CHANGED,
    RMW_EVENT_REQUESTED_DEADLINE_MISSED,
    RMW_EVENT_REQUESTED_QOS_INCOMPATIBLE,
    RMW_EVENT_MESSAGE_LOST,
    RMW_EVENT_SUBSCRIPTION_INCOMPATIBLE_TYPE,
    RMW_EVENT_SUBSCRIPTION_MATCHED,

    // Publisher events
    RMW_EVENT_LIVELINESS_LOST,
    RMW_EVENT_OFFERED_DEADLINE_MISSED,
    RMW_EVENT_OFFERED_QOS_INCOMPATIBLE,
    RMW_EVENT_PUBLISHER_INCOMPATIBLE_TYPE,
    RMW_EVENT_PUBLICATION_MATCHED,

    RMW_EVENT_TYPE_MAX
} rmw_event_type_t;
```

---

## 7. dsoftbus Mapping Proposal

### 7.1 Concept Mapping

| ROS2 Concept | dsoftbus Mapping | Notes |
|--------------|------------------|-------|
| Context | dsoftbus initialization state | Global session management |
| Node | SessionServer | Each node creates a session server |
| Publisher | SendBytes/SendMessage | Topic data via session |
| Subscription | OnBytesReceived | Receive callbacks |
| Service Server | Request-Response pattern | Use sequence numbers |
| Service Client | Request-Response pattern | Use sequence numbers |
| Topic Name | Session Name / pkgName | Encoded topic identifier |
| Guard Condition | Pipe/Signal mechanism | Internal notification |
| Wait Set | select/poll on FDs | Multiple condition wait |

### 7.2 Data Flow

```
[Publisher]
    rmw_publish(publisher, message)
        -> serialize(message)
        -> CreateSessionServer if needed
        -> OpenSession to all matching subscribers
        -> SendBytes(session_id, serialized_data)

[Subscriber]
    OnBytesReceived(session_id, data, len)
        -> store in message queue
        -> trigger guard condition

    rmw_wait(subscriptions, ...)
        -> poll on guard conditions

    rmw_take(subscription, ...)
        -> pop from message queue
        -> deserialize
        -> return message
```

### 7.3 QoS Implementation Strategy

| ROS2 QoS | dsoftbus Implementation |
|----------|------------------------|
| RELIABLE | Session with acknowledgment + retry |
| BEST_EFFORT | Session without retry |
| KEEP_LAST(N) | Ring buffer with size N |
| KEEP_ALL | Dynamic buffer (resource limited) |
| TRANSIENT_LOCAL | Local cache for late joiners |
| DEADLINE | Timer-based monitoring |
| LIFESPAN | Timestamp-based expiry check |

### 7.4 Service Discovery

```
Node Registration:
    - Broadcast node info via dsoftbus discovery
    - Maintain local registry of known nodes

Topic Discovery:
    - Announce topics when publishers/subscribers created
    - Use custom protocol messages for topic advertisement
    - Match publishers with subscribers based on:
        - Topic name
        - Message type
        - QoS compatibility

Service Discovery:
    - Announce services when created
    - rmw_service_server_is_available queries local registry
```

### 7.5 Implementation Priority

**Phase 1 - Core Functions (Must Have)**
1. `rmw_init` / `rmw_shutdown` / `rmw_context_fini`
2. `rmw_create_node` / `rmw_destroy_node`
3. `rmw_create_publisher` / `rmw_destroy_publisher` / `rmw_publish`
4. `rmw_create_subscription` / `rmw_destroy_subscription` / `rmw_take`
5. `rmw_create_wait_set` / `rmw_destroy_wait_set` / `rmw_wait`
6. `rmw_create_guard_condition` / `rmw_destroy_guard_condition` / `rmw_trigger_guard_condition`
7. `rmw_serialize` / `rmw_deserialize`

**Phase 2 - Services (Should Have)**
1. `rmw_create_service` / `rmw_destroy_service`
2. `rmw_take_request` / `rmw_send_response`
3. `rmw_create_client` / `rmw_destroy_client`
4. `rmw_send_request` / `rmw_take_response`

**Phase 3 - Graph Introspection (Nice to Have)**
1. `rmw_get_node_names`
2. `rmw_count_publishers` / `rmw_count_subscribers`
3. `rmw_get_topic_names_and_types`
4. `rmw_service_server_is_available`

**Phase 4 - Advanced Features (Optional)**
1. Message loaning
2. Content filtered topics
3. Events and callbacks
4. Network flow endpoints

---

## 8. Implementation Notes

### 8.1 Thread Safety Requirements

- All RMW functions must be thread-safe except for finalization
- Concurrent access to same entity is generally safe
- Wait operations are not safe to call concurrently on same wait set

### 8.2 Error Handling

- Always check `implementation_identifier` before operations
- Return early with `RMW_RET_INVALID_ARGUMENT` for NULL pointers
- Return `RMW_RET_INCORRECT_RMW_IMPLEMENTATION` for mismatched identifiers
- Use `rmw_set_error_msg()` for detailed error information

### 8.3 Memory Management

- Functions that create entities allocate memory
- Caller is responsible for calling corresponding destroy functions
- Serialization may allocate memory dynamically

### 8.4 GID Generation Strategy

For rmw_dsoftbus:
- Use device ID + session ID + sequence number
- Ensure uniqueness across the ROS domain
- 16 bytes available for GID storage

---

## 9. Reference Implementation

The `rmw_fastrtps` implementation provides a good reference:
- `/home/jiusi/ros2/src/ros2/rmw_fastrtps/rmw_fastrtps_cpp/src/`

Key patterns to follow:
1. Wrapper functions that delegate to shared implementation
2. Type support introspection for serialization
3. Context reference counting
4. Guard condition for graph changes

---

## 10. Next Steps

1. Design internal data structures for rmw_dsoftbus
2. Implement Phase 1 functions
3. Create test harness for validation
4. Iterate on dsoftbus session management
5. Implement QoS policies incrementally

---

*Report generated for rmw_dsoftbus development project*
*ROS2 Humble distribution*
*Last updated: 2025-12-30*
