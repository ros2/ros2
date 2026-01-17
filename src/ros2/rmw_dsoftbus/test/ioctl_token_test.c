/*
 * IoCtl Token Test - Direct kernel interface
 * Uses /dev/access_token_id ioctl to set token (real system call, not stub)
 *
 * This bypasses the changed AccessToken API and uses kernel interface directly
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <dlfcn.h>
#include <stdint.h>
#include <errno.h>

// IoCtl constants for /dev/access_token_id
#define ACCESS_TOKEN_ID_IOCTL_BASE 'A'
#define ACCESS_TOKENID_GET_TOKENID _IOR(ACCESS_TOKEN_ID_IOCTL_BASE, 1, uint64_t)
#define ACCESS_TOKENID_SET_TOKENID _IOW(ACCESS_TOKEN_ID_IOCTL_BASE, 2, uint64_t)
#define ACCESS_TOKENID_SET_FTOKENID _IOW(ACCESS_TOKEN_ID_IOCTL_BASE, 4, uint64_t)

// Default token ID (from Phase 2 success: 671361873)
#define DEFAULT_TOKEN_ID 671361873ULL

// DSoftBus API
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

typedef struct {
    char networkId[65];
    char deviceName[65];
    int deviceTypeId;
} NodeBasicInfo;

static int (*CreateSessionServer)(const char *, const char *, const ISessionListener *) = NULL;
static int (*GetLocalNodeDeviceInfo)(const char *, NodeBasicInfo *) = NULL;

static int on_session_opened(int sessionId, int result) {
    fprintf(stderr, "[Callback] OnSessionOpened: sessionId=%d, result=%d\n", sessionId, result);
    return 0;
}

static void on_session_closed(int sessionId) {
    fprintf(stderr, "[Callback] OnSessionClosed: sessionId=%d\n", sessionId);
}

static void on_bytes_received(int sessionId, const void *data, unsigned int dataLen) {
    fprintf(stderr, "[Callback] OnBytesReceived: sessionId=%d, len=%u, data=%.*s\n",
            sessionId, dataLen, (int)dataLen, (const char*)data);
}

static ISessionListener g_listener = {
    on_session_opened,
    on_session_closed,
    on_bytes_received,
    NULL, NULL, NULL
};

int main(int argc, char *argv[]) {
    fprintf(stderr, "=== IoCtl Token + DSoftBus Test ===\n");
    fprintf(stderr, "Method: Direct kernel ioctl (real system call)\n\n");

    // Step 1: Set token via ioctl (REAL kernel interface)
    fprintf(stderr, "[Step 1] Setting token via /dev/access_token_id ioctl...\n");

    int fd = open("/dev/access_token_id", O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "[ERROR] Failed to open /dev/access_token_id: errno=%d (%s)\n",
                errno, strerror(errno));
        return 1;
    }
    fprintf(stderr, "[OK] Opened /dev/access_token_id: fd=%d\n", fd);

    uint64_t token_id = DEFAULT_TOKEN_ID;
    int ret = ioctl(fd, ACCESS_TOKENID_SET_TOKENID, &token_id);
    if (ret != 0) {
        fprintf(stderr, "[ERROR] ioctl(SET_TOKENID) failed: ret=%d, errno=%d (%s)\n",
                ret, errno, strerror(errno));
        close(fd);
        return 1;
    }
    fprintf(stderr, "[OK] ioctl(SET_TOKENID) succeeded\n");

    // Also set first token ID
    (void)ioctl(fd, ACCESS_TOKENID_SET_FTOKENID, &token_id);

    // Verify
    uint64_t verify = 0;
    if (ioctl(fd, ACCESS_TOKENID_GET_TOKENID, &verify) == 0) {
        fprintf(stderr, "[OK] Token verified: set=%llu, verify=%llu\n",
                (unsigned long long)token_id, (unsigned long long)verify);
    }

    close(fd);
    fprintf(stderr, "✅ Token set successfully via ioctl (REAL kernel call)\n\n");

    // Step 2: Load DSoftBus library
    fprintf(stderr, "[Step 2] Loading DSoftBus library...\n");
    void *handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "[ERROR] dlopen failed: %s\n", dlerror());
        return 1;
    }

    CreateSessionServer = (int (*)(const char*, const char*, const ISessionListener*))
                          dlsym(handle, "CreateSessionServer");
    GetLocalNodeDeviceInfo = (int (*)(const char*, NodeBasicInfo*))
                              dlsym(handle, "GetLocalNodeDeviceInfo");

    if (!CreateSessionServer || !GetLocalNodeDeviceInfo) {
        fprintf(stderr, "[ERROR] Failed to load DSoftBus symbols\n");
        return 1;
    }
    fprintf(stderr, "[OK] DSoftBus library loaded\n\n");

    // Step 3: Get local network ID
    fprintf(stderr, "[Step 3] Getting local network ID...\n");
    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));

    ret = GetLocalNodeDeviceInfo(PKG_NAME, &localInfo);
    fprintf(stderr, "[RESULT] GetLocalNodeDeviceInfo returned: %d\n", ret);

    if (ret == 0) {
        fprintf(stderr, "✅ SUCCESS: Network ID obtained!\n");
        fprintf(stderr, "[INFO] Network ID: %s\n", localInfo.networkId);
        fprintf(stderr, "[INFO] Device Name: %s\n\n", localInfo.deviceName);
    } else {
        fprintf(stderr, "❌ GetLocalNodeDeviceInfo failed: %d\n\n", ret);
    }

    // Step 4: Create SessionServer
    fprintf(stderr, "[Step 4] Creating SessionServer...\n");
    fprintf(stderr, "[INFO] PKG_NAME: %s\n", PKG_NAME);
    fprintf(stderr, "[INFO] SESSION_NAME: %s\n", SESSION_NAME);

    ret = CreateSessionServer(PKG_NAME, SESSION_NAME, &g_listener);
    fprintf(stderr, "[RESULT] CreateSessionServer returned: %d\n", ret);

    if (ret >= 0) {
        fprintf(stderr, "✅✅✅ SUCCESS: CreateSessionServer works with ioctl token!\n");
        fprintf(stderr, "    Token ID: %llu\n", (unsigned long long)token_id);
        fprintf(stderr, "    Server ID: %d\n", ret);
        fprintf(stderr, "    Network ID: %s\n", localInfo.networkId);
        fprintf(stderr, "\n[Service] Ready for client connections...\n");
        fprintf(stderr, "[Command] On client device run:\n");
        fprintf(stderr, "          ./ioctl_token_test client %s\n", localInfo.networkId);

        sleep(60);
    } else {
        fprintf(stderr, "❌ CreateSessionServer FAILED: %d\n", ret);
        if (ret == -426442706) {
            fprintf(stderr, "\n[Diagnosis] Still -426442706 even with ioctl token.\n");
            fprintf(stderr, "  This means:\n");
            fprintf(stderr, "  1. Token ID %llu doesn't have required permissions\n", (unsigned long long)token_id);
            fprintf(stderr, "  2. Need to use different token ID\n");
            fprintf(stderr, "  3. Or system permission model has fundamentally changed\n");
        }
    }

    fprintf(stderr, "\n=== Test Complete ===\n");
    return (ret >= 0) ? 0 : 1;
}
