#ifndef RMW_DSOFTBUS_PUBSUB_MANAGER_H_
#define RMW_DSOFTBUS_PUBSUB_MANAGER_H_

#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

#include "rmw/types.h"
#include "rmw/ret_types.h"
#include "rmw_dsoftbus/protocol.h"

namespace rmw_dsoftbus {

/**
 * PubSubManager handles all publisher and subscriber lifecycle and operations.
 *
 * Responsibilities:
 * - Publisher registration and deregistration
 * - Subscriber registration and deregistration
 * - Message publishing and routing
 * - Message reception and queuing
 * - QoS enforcement
 * - Topic matching and subscription filtering
 */
class PubSubManager {
public:
    PubSubManager();
    ~PubSubManager();

    // ========================================================================
    // Publisher Management
    // ========================================================================

    /**
     * Create a publisher
     */
    rmw_ret_t create_publisher(
        rmw_publisher_t* publisher,
        const rmw_node_t* node,
        const rosidl_message_type_support_t* type_support,
        const char* topic_name,
        const rmw_qos_profile_t* qos_profile);

    /**
     * Destroy a publisher
     */
    rmw_ret_t destroy_publisher(const rmw_publisher_t* publisher);

    /**
     * Publish a message
     */
    rmw_ret_t publish(
        const rmw_publisher_t* publisher,
        const void* ros_message);

    /**
     * Publish bytes (internal use)
     */
    rmw_ret_t publish_bytes(
        const rmw_publisher_t* publisher,
        const uint8_t* serialized_msg,
        size_t len);

    // ========================================================================
    // Subscriber Management
    // ========================================================================

    /**
     * Create a subscriber
     */
    rmw_ret_t create_subscription(
        rmw_subscription_t* subscription,
        const rmw_node_t* node,
        const rosidl_message_type_support_t* type_support,
        const char* topic_name,
        const rmw_qos_profile_t* qos_profile);

    /**
     * Destroy a subscriber
     */
    rmw_ret_t destroy_subscription(const rmw_subscription_t* subscription);

    /**
     * Take a message from a subscription queue
     */
    rmw_ret_t take(
        const rmw_subscription_t* subscription,
        void* ros_message,
        bool* taken,
        rmw_message_info_t* message_info);

    /**
     * Take bytes from subscription (internal use)
     */
    rmw_ret_t take_bytes(
        const rmw_subscription_t* subscription,
        uint8_t* serialized_msg,
        size_t* len,
        bool* taken);

    // ========================================================================
    // Message Routing
    // ========================================================================

    /**
     * Route a message to matching subscribers
     *
     * This is called when a message is received from a remote publisher.
     */
    void route_message(const std::string& topic_name,
                       const uint8_t* data,
                       size_t len,
                       const std::string& source_network_id);

    /**
     * Find all subscribers for a topic (for routing)
     */
    std::vector<const rmw_subscription_t*> find_matching_subscribers(
        const std::string& topic_name);

    /**
     * Find all publishers for a topic
     */
    std::vector<const rmw_publisher_t*> find_publishers_by_topic(
        const std::string& topic_name);

    // ========================================================================
    // Topic Query
    // ========================================================================

    /**
     * Get all topic names and their types
     */
    rmw_ret_t get_topic_names_and_types(
        rmw_names_and_types_t* topic_names_and_types,
        rcutils_allocator_t* allocator,
        bool no_demangle);

    /**
     * Get all publisher information for a topic
     */
    rmw_ret_t get_publishers_info_by_topic(
        const rmw_node_t* node,
        rcutils_allocator_t* allocator,
        const char* topic_name,
        bool no_demangle,
        rmw_topic_endpoint_info_array_t* publishers_info);

    /**
     * Get all subscriber information for a topic
     */
    rmw_ret_t get_subscriptions_info_by_topic(
        const rmw_node_t* node,
        rcutils_allocator_t* allocator,
        const char* topic_name,
        bool no_demangle,
        rmw_topic_endpoint_info_array_t* subscriptions_info);

    // ========================================================================
    // Initialization
    // ========================================================================

    /**
     * Initialize the Pub/Sub manager
     */
    rmw_ret_t initialize();

    /**
     * Shutdown the Pub/Sub manager
     */
    void shutdown();

private:
    // Internal structures
    struct PublisherImpl {
        std::string topic_name;
        std::string type_name;
        rmw_qos_profile_t qos;
        const rosidl_message_type_support_t* type_support;
        const rmw_node_t* node;
        std::string owner_network_id;
    };

    struct SubscriberImpl {
        std::string topic_name;
        std::string type_name;
        rmw_qos_profile_t qos;
        const rosidl_message_type_support_t* type_support;
        const rmw_node_t* node;

        // Message queue for buffering received messages
        // NOTE: Protected by PubSubManager::managers_mutex_, no per-subscriber mutex needed
        std::queue<std::vector<uint8_t>> message_queue;

        // Message source information
        std::queue<std::string> source_network_ids;
    };

    // Data structures
    std::map<const rmw_publisher_t*, PublisherImpl> publishers_;
    std::map<const rmw_subscription_t*, SubscriberImpl> subscribers_;
    std::map<std::string, std::vector<const rmw_subscription_t*>> subscribers_by_topic_;

    // Synchronization
    mutable std::mutex managers_mutex_;

    // Helper functions
    rmw_ret_t serialize_message(
        const void* ros_message,
        const rosidl_message_type_support_t* type_support,
        std::vector<uint8_t>& serialized);

    rmw_ret_t deserialize_message(
        const uint8_t* serialized_msg,
        size_t len,
        const rosidl_message_type_support_t* type_support,
        void* ros_message);

    bool topic_matches(const std::string& pub_topic,
                      const std::string& sub_topic);
};

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS_PUBSUB_MANAGER_H_
