/*
 * Token Brute Force Test
 * Try different token IDs to find one that works
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <dlfcn.h>
#include <stdint.h>

#define ACCESS_TOKEN_ID_IOCTL_BASE 'A'
#define ACCESS_TOKENID_SET_TOKENID _IOW(ACCESS_TOKEN_ID_IOCTL_BASE, 2, uint64_t)
#define ACCESS_TOKENID_GET_TOKENID _IOR(ACCESS_TOKEN_ID_IOCTL_BASE, 1, uint64_t)

#define PKG_NAME "com.huawei.ros2_rmw_dsoftbus"
#define SESSION_NAME "com.huawei.ros2_rmw_dsoftbus.complete_test"

typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnStreamReceived)(int sessionId, const void *data, unsigned int dataLen, int streamType);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, const void *qosTv);
} ISessionListener;

static int (*CreateSessionServer)(const char *, const char *, const ISessionListener *) = NULL;

static int on_session_opened(int sessionId, int result) { return 0; }
static void on_session_closed(int sessionId) {}
static void on_bytes_received(int sessionId, const void *data, unsigned int dataLen) {}

static ISessionListener g_listener = {on_session_opened, on_session_closed, on_bytes_received, NULL, NULL, NULL};

int test_token_id(uint64_t token_id) {
    int fd = open("/dev/access_token_id", O_RDWR);
    if (fd < 0) return -1;

    int ret = ioctl(fd, ACCESS_TOKENID_SET_TOKENID, &token_id);
    close(fd);
    if (ret != 0) return -1;

    // Try CreateSessionServer
    int result = CreateSessionServer(PKG_NAME, SESSION_NAME, &g_listener);
    return result;
}

int main() {
    fprintf(stderr, "=== Token Brute Force Test ===\n\n");

    // Load DSoftBus
    void *handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "[ERROR] Failed to load DSoftBus\n");
        return 1;
    }

    CreateSessionServer = (int (*)(const char*, const char*, const ISessionListener*))
                          dlsym(handle, "CreateSessionServer");
    if (!CreateSessionServer) {
        fprintf(stderr, "[ERROR] Failed to load CreateSessionServer symbol\n");
        return 1;
    }

    fprintf(stderr, "[OK] DSoftBus library loaded\n\n");

    // Try different token IDs
    uint64_t token_ids[] = {
        0,               // Root token
        537429340,       // com.ohos.settingsdata
        671361873,       // Phase 2 success
        671437365,       // Another from Phase 2 logs
        0x1000,          // 4096
        0x2000,          // 8192
        0x10000,         // 65536
        100000000,       // 1亿
        0xFFFFFFFFULL,   // Max 32-bit
    };

    int num_tokens = sizeof(token_ids) / sizeof(token_ids[0]);

    for (int i = 0; i < num_tokens; i++) {
        fprintf(stderr, "[Test %d/%d] Trying token ID: %llu (0x%llX)\n",
                i+1, num_tokens,
                (unsigned long long)token_ids[i],
                (unsigned long long)token_ids[i]);

        int result = test_token_id(token_ids[i]);

        fprintf(stderr, "         CreateSessionServer returned: %d\n", result);

        if (result >= 0) {
            fprintf(stderr, "✅✅✅ SUCCESS with token ID: %llu\n", (unsigned long long)token_ids[i]);
            fprintf(stderr, "\n[SOLUTION] Use this in native_token.cpp:\n");
            fprintf(stderr, "    constexpr uint64_t kDefaultTokenId = %lluULL;\n",
                    (unsigned long long)token_ids[i]);
            return 0;
        }

        if (result != -426442706 && result != -426442720) {
            fprintf(stderr, "⚠️  Different error code: %d (not permission error)\n", result);
        }

        fprintf(stderr, "\n");
    }

    fprintf(stderr, "❌ No working token ID found among tested values\n");
    fprintf(stderr, "\n[Conclusion] New system may require:\n");
    fprintf(stderr, "  1. HAP application with permission declarations\n");
    fprintf(stderr, "  2. System service with proper UID\n");
    fprintf(stderr, "  3. Different permission model entirely\n");

    return 1;
}
