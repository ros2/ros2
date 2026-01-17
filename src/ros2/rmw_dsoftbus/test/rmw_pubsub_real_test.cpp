/*
 * RMW DSoftBus Publisher/Subscriber Real Test
 *
 * 实际调用 RMW API 进行 1:N 路由测试
 * 使用序列化消息，不依赖 ROS2 类型系统
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdint.h>

// 测试模式
enum TestMode {
    MODE_PUBLISHER,
    MODE_SUBSCRIBER_1,
    MODE_SUBSCRIBER_2,
    MODE_SUBSCRIBER_3
};

static volatile bool g_running = true;

void signal_handler(int signum) {
    (void)signum;
    g_running = false;
}

// 最小化的 RMW 类型定义
typedef int rmw_ret_t;
#define RMW_RET_OK 0
#define RMW_RET_ERROR 1

enum rmw_qos_history_policy_e {
    RMW_QOS_POLICY_HISTORY_KEEP_LAST = 0,
    RMW_QOS_POLICY_HISTORY_KEEP_ALL = 1
};

enum rmw_qos_reliability_policy_e {
    RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT = 0,
    RMW_QOS_POLICY_RELIABILITY_RELIABLE = 1
};

enum rmw_qos_durability_policy_e {
    RMW_QOS_POLICY_DURABILITY_VOLATILE = 0,
    RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL = 1
};

typedef struct {
    int history;
    size_t depth;
    int reliability;
    int durability;
    // 简化版，省略其他字段
} rmw_qos_profile_t;

typedef struct {
    unsigned char* buffer;
    size_t buffer_length;
    size_t buffer_capacity;
    void* allocator;
} rmw_serialized_message_t;

typedef struct {
    uint64_t source_timestamp;
    uint64_t received_timestamp;
    uint64_t publication_sequence_number;
    uint64_t reception_sequence_number;
    unsigned char publisher_gid[24];
    bool from_intra_process;
} rmw_message_info_t;

// 声明 RMW 函数
extern "C" {
    const char* rmw_get_implementation_identifier(void);

    // Minimal context/options structures
    typedef struct { char dummy[256]; } rmw_context_t;
    typedef struct { char dummy[256]; } rmw_init_options_t;
    typedef struct { char dummy[256]; } rmw_node_t;
    typedef struct { char dummy[256]; } rmw_publisher_t;
    typedef struct { char dummy[256]; } rmw_subscription_t;
    typedef struct { char dummy[64]; } rmw_publisher_options_t;
    typedef struct { char dummy[64]; } rmw_subscription_options_t;
    typedef struct { char dummy[64]; } rcutils_allocator_t;

    // Init functions
    rmw_ret_t rmw_init_options_init(rmw_init_options_t*, rcutils_allocator_t);
    rmw_ret_t rmw_init(const rmw_init_options_t*, rmw_context_t*);
    rmw_ret_t rmw_shutdown(rmw_context_t*);
    rmw_ret_t rmw_context_fini(rmw_context_t*);
    rmw_ret_t rmw_init_options_fini(rmw_init_options_t*);

    // Node functions
    rmw_node_t* rmw_create_node(rmw_context_t*, const char*, const char*);
    rmw_ret_t rmw_destroy_node(rmw_node_t*);

    // Publisher functions
    rmw_publisher_t* rmw_create_publisher(
        const rmw_node_t*, void*, const char*, const rmw_qos_profile_t*, const rmw_publisher_options_t*);
    rmw_ret_t rmw_destroy_publisher(rmw_node_t*, rmw_publisher_t*);
    rmw_ret_t rmw_publish_serialized_message(
        const rmw_publisher_t*, const rmw_serialized_message_t*, rmw_publisher_options_t*);

    // Subscription functions
    rmw_subscription_t* rmw_create_subscription(
        const rmw_node_t*, void*, const char*, const rmw_qos_profile_t*, const rmw_subscription_options_t*);
    rmw_ret_t rmw_destroy_subscription(rmw_node_t*, rmw_subscription_t*);
    rmw_ret_t rmw_take_serialized_message(
        const rmw_subscription_t*, rmw_serialized_message_t*, bool*, rmw_message_info_t*);

    // Helper to get zero-initialized structures (inline implementations)
    static inline rcutils_allocator_t rcutils_get_default_allocator() {
        rcutils_allocator_t alloc;
        memset(&alloc, 0, sizeof(alloc));
        return alloc;
    }

    static inline rmw_context_t rmw_get_zero_initialized_context() {
        rmw_context_t ctx;
        memset(&ctx, 0, sizeof(ctx));
        return ctx;
    }

    static inline rmw_init_options_t rmw_get_zero_initialized_init_options() {
        rmw_init_options_t opts;
        memset(&opts, 0, sizeof(opts));
        return opts;
    }

    static inline rmw_publisher_options_t rmw_get_default_publisher_options() {
        rmw_publisher_options_t opts;
        memset(&opts, 0, sizeof(opts));
        return opts;
    }

    static inline rmw_subscription_options_t rmw_get_default_subscription_options() {
        rmw_subscription_options_t opts;
        memset(&opts, 0, sizeof(opts));
        return opts;
    }

    static inline rmw_serialized_message_t rmw_get_zero_initialized_serialized_message() {
        rmw_serialized_message_t msg;
        msg.buffer = NULL;
        msg.buffer_length = 0;
        msg.buffer_capacity = 0;
        msg.allocator = NULL;
        return msg;
    }
}

void print_usage(const char* prog) {
    printf("Usage: %s [OPTIONS]\n", prog);
    printf("Options:\n");
    printf("  --mode=pub|sub1|sub2|sub3   Test mode\n");
    printf("  --topic=NAME                Topic name (default: /test)\n");
    printf("  --qos=reliable|best-effort  QoS reliability\n");
    printf("  --depth=N                   QoS history depth\n");
    printf("  --count=N                   Message count (default: 20)\n");
    printf("  --help                      Show this help\n");
    printf("\n");
    printf("Example - 1:N Routing Test:\n");
    printf("  Device 1: %s --mode=pub --count=50\n", prog);
    printf("  Device 2: %s --mode=sub1\n", prog);
    printf("  Device 3: %s --mode=sub2\n", prog);
    printf("\n");
    printf("Example - QoS Test:\n");
    printf("  Publisher:  %s --mode=pub --qos=reliable --depth=20\n", prog);
    printf("  Subscriber: %s --mode=sub1 --qos=reliable\n", prog);
}

int main(int argc, char** argv) {
    // 解析参数
    TestMode mode = MODE_PUBLISHER;
    const char* topic_name = "/test";
    int qos_reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    size_t qos_depth = 10;
    int msg_count = 20;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--mode=", 7) == 0) {
            const char* m = argv[i] + 7;
            if (strcmp(m, "pub") == 0) mode = MODE_PUBLISHER;
            else if (strcmp(m, "sub1") == 0) mode = MODE_SUBSCRIBER_1;
            else if (strcmp(m, "sub2") == 0) mode = MODE_SUBSCRIBER_2;
            else if (strcmp(m, "sub3") == 0) mode = MODE_SUBSCRIBER_3;
        } else if (strncmp(argv[i], "--topic=", 8) == 0) {
            topic_name = argv[i] + 8;
        } else if (strncmp(argv[i], "--qos=", 6) == 0) {
            const char* qos = argv[i] + 6;
            if (strcmp(qos, "best-effort") == 0) {
                qos_reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
            }
        } else if (strncmp(argv[i], "--depth=", 8) == 0) {
            qos_depth = atoi(argv[i] + 8);
        } else if (strncmp(argv[i], "--count=", 8) == 0) {
            msg_count = atoi(argv[i] + 8);
        } else if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        }
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    const char* mode_str[] = {"Publisher", "Subscriber 1", "Subscriber 2", "Subscriber 3"};
    const char* qos_str = (qos_reliability == RMW_QOS_POLICY_RELIABILITY_RELIABLE) ? "RELIABLE" : "BEST_EFFORT";

    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║   RMW DSoftBus 1:N Routing & QoS Test                     ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("  Mode:         %s\n", mode_str[mode]);
    printf("  Topic:        %s\n", topic_name);
    printf("  QoS:          %s (depth=%zu)\n", qos_str, qos_depth);
    if (mode == MODE_PUBLISHER) {
        printf("  Message Count: %d\n", msg_count);
    }
    printf("════════════════════════════════════════════════════════════\n\n");

    // 实现标识符
    const char* impl_id = rmw_get_implementation_identifier();
    printf("[Info] RMW Implementation: %s\n\n", impl_id);

    // 配置 QoS
    rmw_qos_profile_t qos_profile;
    memset(&qos_profile, 0, sizeof(qos_profile));
    qos_profile.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos_profile.depth = qos_depth;
    qos_profile.reliability = qos_reliability;
    qos_profile.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;

    printf("[QoS] Configured:\n");
    printf("  - History: KEEP_LAST\n");
    printf("  - Depth: %zu\n", qos_depth);
    printf("  - Reliability: %s\n", qos_str);
    printf("  - Durability: VOLATILE\n\n");

    // ========================================================================
    // Initialize RMW
    // ========================================================================
    printf("[Step 1] Initializing RMW...\n");

    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
    rmw_ret_t ret = rmw_init_options_init(&init_options, allocator);
    if (ret != RMW_RET_OK) {
        fprintf(stderr, "  ❌ Failed to init options: %d\n", ret);
        return 1;
    }

    rmw_context_t context = rmw_get_zero_initialized_context();
    ret = rmw_init(&init_options, &context);
    if (ret != RMW_RET_OK) {
        fprintf(stderr, "  ❌ Failed to init context: %d\n", ret);
        rmw_init_options_fini(&init_options);
        return 1;
    }
    printf("  ✅ RMW initialized\n\n");

    // ========================================================================
    // Create Node
    // ========================================================================
    printf("[Step 2] Creating node...\n");

    const char* node_name = (mode == MODE_PUBLISHER) ? "pub_node" : "sub_node";
    rmw_node_t* node = rmw_create_node(&context, node_name, "/");
    if (!node) {
        fprintf(stderr, "  ❌ Failed to create node\n");
        rmw_shutdown(&context);
        rmw_context_fini(&context);
        rmw_init_options_fini(&init_options);
        return 1;
    }
    printf("  ✅ Node created: %s\n\n", node_name);

    if (mode == MODE_PUBLISHER) {
        // ====================================================================
        // Publisher Mode
        // ====================================================================
        printf("[Step 3] Creating publisher...\n");

        rmw_publisher_options_t pub_opts = rmw_get_default_publisher_options();
        rmw_publisher_t* publisher = rmw_create_publisher(
            node, NULL, topic_name, &qos_profile, &pub_opts);

        if (!publisher) {
            fprintf(stderr, "  ❌ Failed to create publisher\n");
        } else {
            printf("  ✅ Publisher created\n\n");

            printf("[Step 4] Waiting for subscribers (5s)...\n");
            for (int i = 5; i > 0 && g_running; i--) {
                printf("  %d...\n", i);
                sleep(1);
            }

            printf("\n[Step 5] Publishing %d messages...\n\n", msg_count);

            rmw_serialized_message_t msg = rmw_get_zero_initialized_serialized_message();
            msg.buffer_capacity = 256;
            msg.buffer = (unsigned char*)malloc(msg.buffer_capacity);

            for (int i = 0; i < msg_count && g_running; i++) {
                // 创建简单消息
                char text[128];
                snprintf(text, sizeof(text), "Message #%d from Publisher (QoS: %s)", i, qos_str);

                // 简单序列化：前4字节是长度，后面是字符串
                uint32_t len = strlen(text);
                memcpy(msg.buffer, &len, 4);
                memcpy(msg.buffer + 4, text, len);
                msg.buffer_length = 4 + len;

                ret = rmw_publish_serialized_message(publisher, &msg, NULL);
                if (ret == RMW_RET_OK) {
                    printf("[%3d] ✅ Published: %s\n", i+1, text);
                } else {
                    printf("[%3d] ❌ Publish failed: %d\n", i+1, ret);
                }

                usleep(200000); // 200ms
            }

            free(msg.buffer);

            printf("\n  Published %d messages\n", msg_count);

            rmw_destroy_publisher(node, publisher);
            printf("  ✅ Publisher destroyed\n");
        }

    } else {
        // ====================================================================
        // Subscriber Mode
        // ====================================================================
        printf("[Step 3] Creating subscription...\n");

        rmw_subscription_options_t sub_opts = rmw_get_default_subscription_options();
        rmw_subscription_t* subscription = rmw_create_subscription(
            node, NULL, topic_name, &qos_profile, &sub_opts);

        if (!subscription) {
            fprintf(stderr, "  ❌ Failed to create subscription\n");
        } else {
            printf("  ✅ Subscription created\n\n");

            printf("[Step 4] Waiting for messages (30s)...\n\n");

            rmw_serialized_message_t msg = rmw_get_zero_initialized_serialized_message();
            msg.buffer_capacity = 256;
            msg.buffer = (unsigned char*)malloc(msg.buffer_capacity);

            int received = 0;
            time_t start_time = time(NULL);
            const int timeout = 30;

            while (g_running && (time(NULL) - start_time) < timeout) {
                bool taken = false;
                rmw_message_info_t msg_info;
                memset(&msg_info, 0, sizeof(msg_info));

                ret = rmw_take_serialized_message(subscription, &msg, &taken, &msg_info);

                if (ret == RMW_RET_OK && taken) {
                    received++;

                    // 解析消息
                    if (msg.buffer_length >= 4) {
                        uint32_t len;
                        memcpy(&len, msg.buffer, 4);
                        if (len < msg.buffer_capacity && msg.buffer_length >= 4 + len) {
                            char text[256];
                            memcpy(text, msg.buffer + 4, len);
                            text[len] = '\0';
                            printf("[%3d] ✅ Received: %s\n", received, text);
                        }
                    }
                } else {
                    // 没有消息，短暂休眠
                    usleep(100000); // 100ms
                }
            }

            free(msg.buffer);

            printf("\n[Statistics]\n");
            printf("  Total received: %d messages\n", received);
            printf("  Runtime: %ld seconds\n", time(NULL) - start_time);

            if (received > 0) {
                printf("  Status: ✅ PASS\n");
            } else {
                printf("  Status: ⚠️  No messages received\n");
            }

            rmw_destroy_subscription(node, subscription);
            printf("\n  ✅ Subscription destroyed\n");
        }
    }

    // ========================================================================
    // Cleanup
    // ========================================================================
    printf("\n[Cleanup] Shutting down...\n");

    rmw_destroy_node(node);
    rmw_shutdown(&context);
    rmw_context_fini(&context);
    rmw_init_options_fini(&init_options);

    printf("  ✅ Cleanup complete\n");

    printf("\n════════════════════════════════════════════════════════════\n");
    printf("  Test completed\n");
    printf("════════════════════════════════════════════════════════════\n");

    return 0;
}
