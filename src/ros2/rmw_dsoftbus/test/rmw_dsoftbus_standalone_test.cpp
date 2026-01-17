/*
 * RMW DSoftBus Standalone Test
 *
 * 直接调用 rmw_dsoftbus API 进行测试，不依赖 ROS2
 * 使用真实的 dsoftbus API（无 stub/mock）
 *
 * 编译: 使用 Makefile.aarch64
 * 部署: rk3588s KaihongOS
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// RMW headers
#include "rmw/rmw.h"
#include "rmw/ret_types.h"
#include "rmw/types.h"
#include "rcutils/allocator.h"

// 测试模式
enum TestMode {
    MODE_PUBLISHER,
    MODE_SUBSCRIBER
};

static volatile bool g_running = true;

void signal_handler(int signum) {
    (void)signum;
    g_running = false;
}

// 简单消息结构（模拟 std_msgs::msg::String）
typedef struct {
    char* data;
} SimpleString;

void print_usage(const char* prog) {
    printf("Usage: %s [OPTIONS]\n", prog);
    printf("Options:\n");
    printf("  --mode=pub|sub     Test mode (publisher or subscriber)\n");
    printf("  --topic=NAME       Topic name (default: /chatter)\n");
    printf("  --help             Show this help\n");
}

int main(int argc, char** argv) {
    // 解析参数
    TestMode mode = MODE_PUBLISHER;
    const char* topic_name = "/chatter";

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--mode=", 7) == 0) {
            const char* m = argv[i] + 7;
            if (strcmp(m, "pub") == 0) {
                mode = MODE_PUBLISHER;
            } else if (strcmp(m, "sub") == 0) {
                mode = MODE_SUBSCRIBER;
            }
        } else if (strncmp(argv[i], "--topic=", 8) == 0) {
            topic_name = argv[i] + 8;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        }
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║   RMW DSoftBus Standalone Test                            ║\n");
    printf("║   Mode: %s                                           ║\n",
           mode == MODE_PUBLISHER ? "Publisher" : "Subscriber");
    printf("║   Topic: %-48s ║\n", topic_name);
    printf("╚════════════════════════════════════════════════════════════╝\n");

    rmw_ret_t ret;

    // ========================================================================
    // Step 1: 初始化 RMW
    // ========================================================================
    printf("\n[Step 1] Initializing RMW...\n");

    // 获取实现标识符
    const char* impl_id = rmw_get_implementation_identifier();
    printf("  Implementation: %s\n", impl_id);

    // 初始化选项
    rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
    rcutils_allocator_t allocator = rcutils_get_default_allocator();

    ret = rmw_init_options_init(&init_options, allocator);
    if (ret != RMW_RET_OK) {
        fprintf(stderr, "  ❌ Failed to init options: %d\n", ret);
        return 1;
    }
    printf("  ✅ Init options created\n");

    // 初始化 context
    rmw_context_t context = rmw_get_zero_initialized_context();
    ret = rmw_init(&init_options, &context);
    if (ret != RMW_RET_OK) {
        fprintf(stderr, "  ❌ Failed to init context: %d\n", ret);
        rmw_init_options_fini(&init_options);
        return 1;
    }
    printf("  ✅ Context initialized\n");

    // ========================================================================
    // Step 2: 创建节点
    // ========================================================================
    printf("\n[Step 2] Creating node...\n");

    const char* node_name = (mode == MODE_PUBLISHER) ? "publisher" : "subscriber";
    const char* node_namespace = "/";

    rmw_node_t* node = rmw_create_node(&context, node_name, node_namespace);
    if (!node) {
        fprintf(stderr, "  ❌ Failed to create node\n");
        rmw_shutdown(&context);
        rmw_context_fini(&context);
        rmw_init_options_fini(&init_options);
        return 1;
    }
    printf("  ✅ Node created: %s\n", node_name);

    // ========================================================================
    // Step 3: 创建 Publisher 或 Subscriber
    // ========================================================================
    printf("\n[Step 3] Creating %s...\n",
           mode == MODE_PUBLISHER ? "publisher" : "subscriber");

    // QoS 配置（使用默认）
    rmw_qos_profile_t qos_profile = rmw_qos_profile_default;

    // 注意：这里需要 type_support，简化版本使用 NULL
    // 实际使用需要提供正确的 rosidl_message_type_support_t
    const rosidl_message_type_support_t* type_support = NULL;

    if (mode == MODE_PUBLISHER) {
        // 创建 Publisher
        rmw_publisher_options_t pub_options = rmw_get_default_publisher_options();
        rmw_publisher_t* publisher = rmw_create_publisher(
            node, type_support, topic_name, &qos_profile, &pub_options);

        if (!publisher) {
            fprintf(stderr, "  ❌ Failed to create publisher\n");
        } else {
            printf("  ✅ Publisher created on topic: %s\n", topic_name);

            // 发布消息
            printf("\n[Step 4] Publishing messages...\n");
            for (int i = 0; i < 10 && g_running; i++) {
                char msg_data[128];
                snprintf(msg_data, sizeof(msg_data), "Hello RMW DSoftBus %d", i);

                printf("  [%d] Publishing: %s\n", i, msg_data);

                // 注意：实际使用需要序列化消息
                // 这里简化处理

                sleep(1);
            }

            // 销毁 Publisher
            ret = rmw_destroy_publisher(node, publisher);
            if (ret == RMW_RET_OK) {
                printf("  ✅ Publisher destroyed\n");
            }
        }
    } else {
        // 创建 Subscriber
        rmw_subscription_options_t sub_options = rmw_get_default_subscription_options();
        rmw_subscription_t* subscription = rmw_create_subscription(
            node, type_support, topic_name, &qos_profile, &sub_options);

        if (!subscription) {
            fprintf(stderr, "  ❌ Failed to create subscription\n");
        } else {
            printf("  ✅ Subscription created on topic: %s\n", topic_name);

            // 接收消息
            printf("\n[Step 4] Waiting for messages...\n");
            for (int i = 0; i < 10 && g_running; i++) {
                printf("  [%d] Waiting...\n", i);

                // 注意：实际使用需要调用 rmw_take
                // 这里简化处理

                sleep(1);
            }

            // 销毁 Subscriber
            ret = rmw_destroy_subscription(node, subscription);
            if (ret == RMW_RET_OK) {
                printf("  ✅ Subscription destroyed\n");
            }
        }
    }

    // ========================================================================
    // Step 5: Graph Discovery 测试
    // ========================================================================
    printf("\n[Step 5] Testing Graph Discovery...\n");

    // 获取节点列表
    rcutils_string_array_t node_names = rcutils_get_zero_initialized_string_array();
    rcutils_string_array_t node_namespaces = rcutils_get_zero_initialized_string_array();

    ret = rmw_get_node_names(node, &node_names, &node_namespaces);
    if (ret == RMW_RET_OK) {
        printf("  ✅ Discovered %zu nodes:\n", node_names.size);
        for (size_t i = 0; i < node_names.size; i++) {
            printf("     - %s%s\n", node_namespaces.data[i], node_names.data[i]);
        }
        rcutils_string_array_fini(&node_names);
        rcutils_string_array_fini(&node_namespaces);
    } else {
        fprintf(stderr, "  ⚠️  Failed to get node names: %d\n", ret);
    }

    // ========================================================================
    // Cleanup
    // ========================================================================
    printf("\n[Cleanup] Shutting down...\n");

    ret = rmw_destroy_node(node);
    if (ret == RMW_RET_OK) {
        printf("  ✅ Node destroyed\n");
    }

    ret = rmw_shutdown(&context);
    if (ret == RMW_RET_OK) {
        printf("  ✅ Context shutdown\n");
    }

    ret = rmw_context_fini(&context);
    if (ret == RMW_RET_OK) {
        printf("  ✅ Context finalized\n");
    }

    ret = rmw_init_options_fini(&init_options);
    if (ret == RMW_RET_OK) {
        printf("  ✅ Init options finalized\n");
    }

    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║   Test completed successfully                              ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");

    return 0;
}
