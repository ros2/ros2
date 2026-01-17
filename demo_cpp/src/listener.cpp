// Minimal listener with HAND-WRITTEN CDR deserialization for Step A2
// ZERO rosidl serialization dependencies
// ZERO DDS/introspection dependencies

#include <memory>
#include <string>
#include <cstring>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/serialized_message.hpp"
#include "std_msgs/msg/string.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>(
    "minimal_listener_serialized",
    rclcpp::NodeOptions()
      .use_intra_process_comms(false)
      .start_parameter_services(false)
      .enable_rosout(false));

  fprintf(stderr, "[LISTENER] Creating subscription...\n");

  size_t message_count = 0;

  // Create subscription that receives serialized messages
  auto callback = [&](const std::shared_ptr<rclcpp::SerializedMessage> serialized) {
    fprintf(stderr, "[LISTENER] Callback triggered! Received %zu bytes\n", serialized->size());

    auto & rcl_msg = serialized->get_rcl_serialized_message();

    // ========================================================================
    // HAND-WRITTEN MINIMAL CDR DESERIALIZATION for std_msgs/String
    // Format: [uint32_t string_length][char data[string_length]]
    // ========================================================================

    if (rcl_msg.buffer_length < 4) {
      fprintf(stderr, "[LISTENER] ERROR: Buffer too small (%zu bytes)\n",
              rcl_msg.buffer_length);
      return;
    }

    // Read string length
    uint32_t string_len;
    memcpy(&string_len, rcl_msg.buffer, 4);

    fprintf(stderr, "[LISTENER] CDR string_len = %u\n", string_len);

    if (4 + string_len > rcl_msg.buffer_length) {
      fprintf(stderr, "[LISTENER] ERROR: String length %u exceeds buffer size\n", string_len);
      return;
    }

    // Read string data
    std::string msg_data(reinterpret_cast<const char*>(rcl_msg.buffer + 4), string_len);

    message_count++;

    fprintf(stderr, "[LISTENER] ✓ Received #%zu: '%s'\n",
            message_count, msg_data.c_str());
  };

  auto sub = node->create_subscription<std_msgs::msg::String>(
    "chatter", 10, callback);

  fprintf(stderr, "[LISTENER] Subscription created!\n");
  fprintf(stderr, "[LISTENER] Node started, waiting for messages on /chatter...\n\n");

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
