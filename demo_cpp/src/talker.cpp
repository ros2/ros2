// Minimal talker with HAND-WRITTEN CDR serialization for Step A2
// ZERO rosidl serialization dependencies
// ZERO DDS/introspection dependencies

#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/serialized_message.hpp"
#include "std_msgs/msg/string.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>(
    "minimal_talker_serialized",
    rclcpp::NodeOptions()
      .use_intra_process_comms(false)
      .start_parameter_services(false)
      .enable_rosout(false));

  fprintf(stderr, "[TALKER] Creating publisher...\n");
  auto pub = node->create_publisher<std_msgs::msg::String>("chatter", 10);
  fprintf(stderr, "[TALKER] Publisher created successfully!\n");
  fprintf(stderr, "[TALKER] Node started, publishing to /chatter...\n");

  for (size_t count = 0; count < 20; count++) {
    fprintf(stderr, "[TALKER] === Iteration %zu ===\n", count);

    // Create message string
    std::string msg_data = "Hello ROS2 on KaihongOS! Count: " + std::to_string(count);
    fprintf(stderr, "[TALKER] Message content: '%s'\n", msg_data.c_str());

    // ========================================================================
    // HAND-WRITTEN MINIMAL CDR for std_msgs/String
    // Format: [uint32_t string_length][char data[string_length]]
    // ========================================================================

    uint32_t string_len = msg_data.size();
    std::vector<uint8_t> cdr_buffer;
    cdr_buffer.resize(4 + string_len);

    // Write string length (little-endian uint32_t)
    memcpy(cdr_buffer.data(), &string_len, 4);

    // Write string data
    memcpy(cdr_buffer.data() + 4, msg_data.data(), string_len);

    fprintf(stderr, "[TALKER] CDR serialized: %u bytes (len=%u + data=%u)\n",
            (uint32_t)cdr_buffer.size(), 4u, string_len);

    // Create RCL serialized message
    rclcpp::SerializedMessage serialized;
    auto & rcl_msg = serialized.get_rcl_serialized_message();

    // Allocate buffer
    rcl_msg.buffer_capacity = cdr_buffer.size();
    rcl_msg.buffer_length = cdr_buffer.size();
    rcl_msg.buffer = reinterpret_cast<uint8_t*>(malloc(cdr_buffer.size()));
    rcl_msg.allocator = rcutils_get_default_allocator();

    // Copy CDR data
    memcpy(rcl_msg.buffer, cdr_buffer.data(), cdr_buffer.size());

    fprintf(stderr, "[TALKER] Publishing serialized message...\n");

    // Publish via RCL serialized path
    pub->publish(serialized);

    fprintf(stderr, "[TALKER] ✓ Published successfully!\n\n");

    // Cleanup
    free(rcl_msg.buffer);

    sleep(1);

    if (!rclcpp::ok()) {
      break;
    }
  }

  fprintf(stderr, "[TALKER] Sent %zu messages, exiting.\n", 20);

  rclcpp::shutdown();
  return 0;
}
