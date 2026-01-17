/*
 * Test CreateSessionServer with specific package and session names
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*CreateSessionServer_t)(const char*, const char*, void*);
typedef int (*RemoveSessionServer_t)(const char*, const char*);

typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void* data, unsigned int len);
    void (*OnMessageReceived)(int sessionId, const void* data, unsigned int len);
} ISessionListener;

static int dummy_opened(int id, int result) { return 0; }
static void dummy_closed(int id) {}
static void dummy_bytes(int id, const void* data, unsigned int len) {}
static void dummy_msg(int id, const void* data, unsigned int len) {}

ISessionListener listener = {
    .OnSessionOpened = dummy_opened,
    .OnSessionClosed = dummy_closed,
    .OnBytesReceived = dummy_bytes,
    .OnMessageReceived = dummy_msg
};

int main() {
    const char* pkgName = "com.huawei.ros2_rmw_dsoftbus";
    const char* sessionName = "com.huawei.ros2_rmw_dsoftbus.complete_test";

    printf("==============================================\n");
    printf("Testing Specific Package and Session Names\n");
    printf("==============================================\n");
    printf("PKG_NAME:     %s\n", pkgName);
    printf("SESSION_NAME: %s\n", sessionName);
    printf("==============================================\n\n");

    void* handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW);
    if (!handle) {
        printf("[ERROR] Failed to load library: %s\n", dlerror());
        return 1;
    }

    CreateSessionServer_t create = (CreateSessionServer_t)dlsym(handle, "CreateSessionServer");
    RemoveSessionServer_t remove = (RemoveSessionServer_t)dlsym(handle, "RemoveSessionServer");

    if (!create || !remove) {
        printf("[ERROR] Failed to resolve symbols\n");
        dlclose(handle);
        return 1;
    }

    printf("[OK] Library loaded and symbols resolved\n\n");

    // Clean up first
    remove(pkgName, sessionName);

    // Test CreateSessionServer
    printf("[TEST] Calling CreateSessionServer...\n");
    int ret = create(pkgName, sessionName, &listener);

    printf("\n[RESULT] CreateSessionServer returned: %d\n", ret);
    if (ret == 0) {
        printf("[SUCCESS] Session server created successfully!\n");
        printf("[INFO] Cleaning up...\n");
        remove(pkgName, sessionName);
    } else {
        printf("[FAILED] Error code: %d (0x%08x)\n", ret, (unsigned int)ret);
        if (ret == -426442743) {
            printf("[ANALYSIS] SOFTBUS_PERMISSION_DENIED\n");
            printf("           This means permission validation failed.\n");
        }
    }

    printf("\n==============================================\n");
    printf("Test Complete\n");
    printf("==============================================\n");

    dlclose(handle);
    return ret == 0 ? 0 : 1;
}
