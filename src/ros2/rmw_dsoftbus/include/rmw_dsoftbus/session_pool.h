#ifndef RMW_DSOFTBUS_SESSION_POOL_H_
#define RMW_DSOFTBUS_SESSION_POOL_H_

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace rmw_dsoftbus {

/**
 * SessionPool manages DSoftBus sessions for cross-device communication.
 *
 * It maintains one session per remote device (NetworkID), reusing connections
 * for multiple messages. This reduces system load and simplifies management.
 *
 * Features:
 * - Lazy connection creation (create on demand)
 * - Connection reuse (one session per NetworkID)
 * - Automatic timeout cleanup
 * - Thread-safe operations
 * - Callback support for message reception
 */
class SessionPool {
public:
    SessionPool();
    ~SessionPool();

    // ========================================================================
    // Session Management
    // ========================================================================

    /**
     * Get or create a session to a remote device
     *
     * @param target_network_id The network ID of target device
     * @param session_name The session name (defaults to "rmw_dsoftbus_data")
     * @return Session ID (>= 0) on success, < 0 on failure
     */
    int get_or_create_session(const std::string& target_network_id,
                              const std::string& session_name = "rmw_dsoftbus_data");

    /**
     * Release a session (close and cleanup)
     */
    void release_session(int session_id);

    /**
     * Check if a session is currently active
     */
    bool is_session_active(int session_id) const;

    /**
     * Get the network ID associated with a session
     */
    std::string get_session_network_id(int session_id) const;

    // ========================================================================
    // Data Transfer
    // ========================================================================

    /**
     * Send raw bytes to a remote device
     *
     * @param target_network_id The network ID of target device
     * @param data The data to send
     * @param len Data length in bytes
     * @return 0 on success, error code on failure
     */
    int send_bytes(const std::string& target_network_id,
                   const uint8_t* data, size_t len);

    /**
     * Send bytes to a specific session
     *
     * @param session_id The session ID
     * @param data The data to send
     * @param len Data length in bytes
     * @return 0 on success, error code on failure
     */
    int send_bytes_on_session(int session_id,
                              const uint8_t* data, size_t len);

    // ========================================================================
    // Callbacks
    // ========================================================================

    /**
     * Callback type for receiving bytes
     *
     * Parameters:
     * - session_id: The session ID
     * - data: Pointer to received data
     * - len: Data length in bytes
     * - source_network_id: The network ID of the sender
     */
    using OnBytesReceivedCallback = std::function<void(int session_id,
                                                        const uint8_t* data,
                                                        size_t len,
                                                        const std::string& source_network_id)>;

    /**
     * Set the callback for receiving bytes
     */
    void set_on_bytes_received_callback(OnBytesReceivedCallback callback);

    /**
     * Callback for session state changes
     */
    using OnSessionStateChangedCallback = std::function<void(int session_id,
                                                             bool is_open)>;

    /**
     * Set the callback for session state changes
     */
    void set_on_session_state_changed_callback(OnSessionStateChangedCallback callback);

    // ========================================================================
    // Maintenance
    // ========================================================================

    /**
     * Cleanup inactive sessions (older than timeout_ms)
     * Default timeout: 30000ms (30 seconds)
     */
    void cleanup_inactive_sessions(uint64_t timeout_ms = 30000);

    /**
     * Close all sessions and clear the pool
     */
    void clear_all_sessions();

    /**
     * Get current pool size (number of active sessions)
     */
    size_t get_session_count() const;

    // ========================================================================
    // Initialization & Configuration
    // ========================================================================

    /**
     * Initialize the session pool (must be called once at startup)
     * Sets up DSoftBus library loading via dlopen
     */
    int initialize();

    /**
     * Shutdown the session pool (cleanup and close all sessions)
     */
    void shutdown();

    /**
     * Check if the pool is initialized
     */
    bool is_initialized() const;

private:
    // Internal session entry structure
    struct SessionEntry {
        int session_id;
        std::string network_id;
        std::string session_name;
        uint64_t created_time_ms;
        uint64_t last_used_ms;
        bool is_active;
    };

    // Pool data structures
    std::map<std::string, SessionEntry> sessions_;  // NetworkID -> SessionEntry
    mutable std::mutex pool_mutex_;

    // Callbacks
    OnBytesReceivedCallback on_bytes_received_;
    OnSessionStateChangedCallback on_session_state_changed_;
    std::mutex callback_mutex_;

    // Initialization state
    bool initialized_;
    void* dsoftbus_handle_;  // Handle from dlopen

    // Helper functions
    uint64_t get_current_time_ms() const;
    int create_session_internal(const std::string& target_network_id,
                                const std::string& session_name);
    void close_session_internal(int session_id);
};

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS_SESSION_POOL_H_
