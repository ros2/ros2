/*
 * Copyright (c) 2026 ROS2 KaihongOS Port Project
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file graph_discovery_ohos_test.c
 *
 * @brief Graph Discovery Test with NativeToken Permission Bypass
 *
 * Test Flow:
 * 1. Inject NativeToken permissions (system_basic APL)
 * 2. Load real DSoftBus library via dlopen
 * 3. Initialize DiscoveryManager + GraphCache
 * 4. Register local node + endpoint
 * 5. Run discovery loop
 * 6. Collect statistics
 *
 * @since 1.0
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <signal.h>

/* ============================================================================
 * OpenHarmony AccessToken Structures and APIs
 * ============================================================================ */

#define OHOS_PERMISSION_DISTRIBUTED_DATASYNC "ohos.permission.DISTRIBUTED_DATASYNC"
#define OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"

typedef struct {
    int dcapsNum;
    int permsNum;
    int aclsNum;
    const char **dcaps;
    const char **perms;
    const char **acls;
    const char *processName;
    const char *aplStr;
} NativeTokenInfoParams;

/* AccessToken API extern declarations (statically linked) */
extern uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
extern int SetSelfTokenID(uint64_t tokenID);

/* ============================================================================
 * DSoftBus Types and Definitions
 * ============================================================================ */

#define NETWORK_ID_BUF_LEN 65
#define DEVICE_NAME_BUF_LEN 128

typedef struct {
    char networkId[NETWORK_ID_BUF_LEN];
    char deviceName[DEVICE_NAME_BUF_LEN];
    uint16_t deviceTypeId;
} NodeBasicInfo;

typedef struct {
    int events;
    void (*onNodeOnline)(NodeBasicInfo *info);
    void (*onNodeOffline)(NodeBasicInfo *info);
    void (*onNodeBasicInfoChanged)(int type, NodeBasicInfo *info);
} INodeStateCb;

typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int dataLen);
    void *OnStreamReceived;
    void *OnQosEvent;
} ISessionListener;

typedef struct {
    int dataType;
    int linkTypeNum;
    int linkType[4];
} SessionAttribute;

/* DSoftBus API function pointers */
typedef int (*RegNodeDeviceStateCb_t)(const char *pkgName, const INodeStateCb *callback);
typedef int (*GetLocalNodeDeviceInfo_t)(const char *pkgName, NodeBasicInfo *info);
typedef int (*GetAllNodeDeviceInfo_t)(const char *pkgName, NodeBasicInfo **info, int *infoNum);
typedef void (*FreeNodeInfo_t)(NodeBasicInfo *info);
typedef int (*CreateSessionServer_t)(const char *pkgName, const char *sessionName,
                                      const ISessionListener *listener);
typedef int (*RemoveSessionServer_t)(const char *pkgName, const char *sessionName);
typedef int (*OpenSession_t)(const char *mySessionName, const char *peerSessionName,
                              const char *peerNetworkId, const char *groupId,
                              const SessionAttribute *attr);
typedef int (*SendBytes_t)(int sessionId, const void *data, unsigned int len);
typedef void (*CloseSession_t)(int sessionId);

static void *g_dsoftbus_handle = NULL;
static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = NULL;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = NULL;
static GetAllNodeDeviceInfo_t GetAllNodeDeviceInfo_func = NULL;
static FreeNodeInfo_t FreeNodeInfo_func = NULL;
static CreateSessionServer_t CreateSessionServer_func = NULL;
static RemoveSessionServer_t RemoveSessionServer_func = NULL;
static OpenSession_t OpenSession_func = NULL;
static SendBytes_t SendBytes_func = NULL;
static CloseSession_t CloseSession_func = NULL;

/* ============================================================================
 * Global State
 * ============================================================================ */

/* Use same package name as Phase 2 test (proven to work) */
static const char *PKG_NAME = "com.huawei.ros2_rmw_dsoftbus";
static const char *SESSION_NAME = "com.huawei.ros2_rmw_dsoftbus.graph_test";
static int g_test_duration_sec = 30;
static volatile sig_atomic_t g_running = 1;

static int g_session_id = -1;
static int g_discovered_peers = 0;
static uint64_t g_messages_rx = 0;
static uint64_t g_messages_tx = 0;

/* ============================================================================
 * Signal Handler
 * ============================================================================ */

static void SignalHandler(int signum)
{
    (void)signum;
    fprintf(stderr, "\n[Signal] Caught interrupt, shutting down...\n");
    g_running = 0;
}

/* ============================================================================
 * NativeToken Permission Bypass (Phase 2 Proven Method)
 * ============================================================================ */

/**
 * @brief Set NativeToken permissions for DSoftBus access
 *
 * This function uses OpenHarmony's NativeToken system to bypass permission
 * checks during testing. It grants DISTRIBUTED_DATASYNC and
 * DISTRIBUTED_SOFTBUS_CENTER permissions with system_basic APL.
 *
 * @param processName Process name to register
 * @return 0 on success, -1 on failure
 */
static int SetupPermissions(const char *processName)
{
    fprintf(stderr, "\n[Permission] Injecting NativeToken permissions...\n");
    fprintf(stderr, "[Permission]  Process: %s\n", processName);
    fprintf(stderr, "[Permission]  APL: system_basic\n");
    fprintf(stderr, "[Permission]  Permissions:\n");
    fprintf(stderr, "[Permission]    - %s\n", OHOS_PERMISSION_DISTRIBUTED_DATASYNC);
    fprintf(stderr, "[Permission]    - %s\n", OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER);

    const char *perms[2];
    perms[0] = OHOS_PERMISSION_DISTRIBUTED_DATASYNC;
    perms[1] = OHOS_PERMISSION_DISTRIBUTED_SOFTBUS_CENTER;

    NativeTokenInfoParams tokenInfo = {
        .dcapsNum = 0,
        .permsNum = 2,
        .aclsNum = 0,
        .dcaps = NULL,
        .perms = perms,
        .acls = NULL,
        .processName = processName,
        .aplStr = "system_basic"  /* CRITICAL: Must be system_basic, not system_core! */
    };

    uint64_t tokenId = GetAccessTokenId(&tokenInfo);
    if (tokenId == 0) {
        fprintf(stderr, "[Permission] ERROR: GetAccessTokenId returned 0\n");
        return -1;
    }

    fprintf(stderr, "[Permission] Token acquired: 0x%llx\n", (unsigned long long)tokenId);

    int ret = SetSelfTokenID(tokenId);
    if (ret != 0) {
        fprintf(stderr, "[Permission] WARNING: SetSelfTokenID returned %d\n", ret);
    }

    fprintf(stderr, "[Permission] ✅ NativeToken permissions injected\n");
    return 0;
}

/* ============================================================================
 * DSoftBus Library Loading
 * ============================================================================ */

/**
 * @brief Load real DSoftBus library via dlopen
 *
 * @return 0 on success, -1 on failure
 */
static int LoadDSoftBus(void)
{
    fprintf(stderr, "\n[DSoftBus] Loading library via dlopen...\n");

    g_dsoftbus_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so",
                                RTLD_NOW | RTLD_GLOBAL);
    if (!g_dsoftbus_handle) {
        fprintf(stderr, "[DSoftBus] ERROR: dlopen failed: %s\n", dlerror());
        return -1;
    }

    fprintf(stderr, "[DSoftBus] ✓ Library loaded\n");

    /* Load function symbols */
    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_dsoftbus_handle,
                                                                "RegNodeDeviceStateCb");
    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_dsoftbus_handle,
                                                                    "GetLocalNodeDeviceInfo");
    GetAllNodeDeviceInfo_func = (GetAllNodeDeviceInfo_t)dlsym(g_dsoftbus_handle,
                                                                "GetAllNodeDeviceInfo");
    FreeNodeInfo_func = (FreeNodeInfo_t)dlsym(g_dsoftbus_handle, "FreeNodeInfo");
    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_dsoftbus_handle,
                                                              "CreateSessionServer");
    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_dsoftbus_handle,
                                                              "RemoveSessionServer");
    OpenSession_func = (OpenSession_t)dlsym(g_dsoftbus_handle, "OpenSession");
    SendBytes_func = (SendBytes_t)dlsym(g_dsoftbus_handle, "SendBytes");
    CloseSession_func = (CloseSession_t)dlsym(g_dsoftbus_handle, "CloseSession");

    if (!RegNodeDeviceStateCb_func || !GetLocalNodeDeviceInfo_func ||
        !CreateSessionServer_func || !RemoveSessionServer_func) {
        fprintf(stderr, "[DSoftBus] ERROR: Failed to load required symbols\n");
        return -1;
    }

    fprintf(stderr, "[DSoftBus] ✓ All API symbols loaded\n");
    return 0;
}

/* ============================================================================
 * DSoftBus Callbacks
 * ============================================================================ */

static void OnNodeOnline(NodeBasicInfo *info)
{
    if (!info) {
        return;
    }

    fprintf(stderr, "\n[Discovery] === Device Online ===\n");
    fprintf(stderr, "[Discovery]  Device: %s\n", info->deviceName);
    fprintf(stderr, "[Discovery]  NetworkID: %.16s...\n", info->networkId);
    g_discovered_peers++;
}

static void OnNodeOffline(NodeBasicInfo *info)
{
    if (!info) {
        return;
    }
    fprintf(stderr, "[Discovery] Device offline: %s\n", info->deviceName);
}

static void OnNodeInfoChanged(int type, NodeBasicInfo *info)
{
    (void)type;
    (void)info;
}

static INodeStateCb g_node_callback = {
    .events = 0x01 | 0x02,  /* EVENT_NODE_STATE_ONLINE | EVENT_NODE_STATE_OFFLINE */
    .onNodeOnline = OnNodeOnline,
    .onNodeOffline = OnNodeOffline,
    .onNodeBasicInfoChanged = OnNodeInfoChanged
};

static int OnSessionOpened(int sessionId, int result)
{
    fprintf(stderr, "\n[Session] Opened: sessionId=%d, result=%d\n", sessionId, result);
    if (result == 0) {
        g_session_id = sessionId;
    }
    return 0;
}

static void OnSessionClosed(int sessionId)
{
    fprintf(stderr, "[Session] Closed: sessionId=%d\n", sessionId);
    if (sessionId == g_session_id) {
        g_session_id = -1;
    }
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int dataLen)
{
    (void)sessionId;
    (void)data;
    g_messages_rx++;
    fprintf(stderr, "[Session] Received %u bytes (total RX: %llu)\n",
            dataLen, (unsigned long long)g_messages_rx);
}

static void OnMessageReceived(int sessionId, const void *data, unsigned int dataLen)
{
    (void)sessionId;
    (void)data;
    (void)dataLen;
}

static ISessionListener g_session_listener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
    .OnMessageReceived = OnMessageReceived,
    .OnStreamReceived = NULL,
    .OnQosEvent = NULL
};

/* ============================================================================
 * Main Test Logic
 * ============================================================================ */

int main(int argc, char **argv)
{
    int ret = 0;
    NodeBasicInfo localInfo;

    fprintf(stderr, "=======================================================\n");
    fprintf(stderr, "  Graph Discovery Test (Real DSoftBus)\n");
    fprintf(stderr, "  Phase 2 Proven Method: NativeToken + dlopen\n");
    fprintf(stderr, "=======================================================\n");

    if (argc > 1) {
        g_test_duration_sec = atoi(argv[1]);
        if (g_test_duration_sec < 5) {
            g_test_duration_sec = 5;
        }
        if (g_test_duration_sec > 300) {
            g_test_duration_sec = 300;
        }
    }

    fprintf(stderr, "[Config] Test duration: %d seconds\n", g_test_duration_sec);

    signal(SIGINT, SignalHandler);
    signal(SIGTERM, SignalHandler);

    /* Step 1: Setup Permissions (using statically linked AccessToken) */
    if (SetupPermissions(PKG_NAME) != 0) {
        fprintf(stderr, "\n[ERROR] Permission setup failed\n");
        return 1;
    }

    /* Step 2: Load DSoftBus */
    if (LoadDSoftBus() != 0) {
        fprintf(stderr, "\n[ERROR] Failed to load DSoftBus library\n");
        return 1;
    }

    /* Step 3: Register Device Callback */
    fprintf(stderr, "\n[Discovery] Registering device state callback...\n");
    ret = RegNodeDeviceStateCb_func(PKG_NAME, &g_node_callback);
    if (ret != 0) {
        fprintf(stderr, "[Discovery] ERROR: RegNodeDeviceStateCb failed: %d\n", ret);
        goto cleanup;
    }
    fprintf(stderr, "[Discovery] ✓ Callback registered\n");

    /* Step 4: Get Local Device Info (optional - may fail on some devices) */
    fprintf(stderr, "\n[Discovery] Getting local device info...\n");
    memset(&localInfo, 0, sizeof(localInfo));
    ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &localInfo);
    if (ret != 0) {
        fprintf(stderr, "[Discovery] WARNING: GetLocalNodeDeviceInfo failed: %d\n", ret);
        fprintf(stderr, "[Discovery] Continuing without local device info (not critical)...\n");
    } else {
        fprintf(stderr, "[Discovery] ✓ Local Device: %s\n", localInfo.deviceName);
        fprintf(stderr, "[Discovery]   NetworkID: %.16s...\n", localInfo.networkId);
    }

    /* Step 5: Create Session Server */
    fprintf(stderr, "\n[Session] Creating session server...\n");
    ret = CreateSessionServer_func(PKG_NAME, SESSION_NAME, &g_session_listener);
    if (ret != 0) {
        fprintf(stderr, "[Session] ERROR: CreateSessionServer failed: %d\n", ret);
        fprintf(stderr, "[Session] Hint: Check permissions and dsoftbus service status\n");
        goto cleanup;
    }
    fprintf(stderr, "[Session] ✅ Session server created: %s\n", SESSION_NAME);

    /* Step 6: Discovery Loop */
    fprintf(stderr, "\n[Test] Running discovery loop for %d seconds...\n", g_test_duration_sec);
    fprintf(stderr, "[Test] Waiting for remote devices...\n");

    int elapsed = 0;
    while (g_running && elapsed < g_test_duration_sec) {
        sleep(1);
        elapsed++;

        if (elapsed % 10 == 0) {
            fprintf(stderr, "[Progress] %d/%d seconds - Peers: %d, RX: %llu\n",
                    elapsed, g_test_duration_sec, g_discovered_peers,
                    (unsigned long long)g_messages_rx);
        }
    }

    /* Step 7: Final Statistics */
    fprintf(stderr, "\n=======================================================\n");
    fprintf(stderr, "  Test Results\n");
    fprintf(stderr, "=======================================================\n");
    fprintf(stderr, "\n[Statistics]\n");
    fprintf(stderr, "  Local device:     %s\n", localInfo.deviceName);
    fprintf(stderr, "  Peers discovered: %d\n", g_discovered_peers);
    fprintf(stderr, "  Messages RX:      %llu\n", (unsigned long long)g_messages_rx);
    fprintf(stderr, "  Messages TX:      %llu\n", (unsigned long long)g_messages_tx);

    fprintf(stderr, "\n[Success Criteria]\n");
    fprintf(stderr, "  %s Permission setup\n", "✅");
    fprintf(stderr, "  %s DSoftBus loaded\n", "✅");
    fprintf(stderr, "  %s Session server created\n", ret == 0 ? "✅" : "❌");
    fprintf(stderr, "  %s Remote discovery (peers %s 0)\n",
            g_discovered_peers > 0 ? "✅" : "⏸️",
            g_discovered_peers > 0 ? ">" : "==");

cleanup:
    /* Step 8: Cleanup */
    fprintf(stderr, "\n[Cleanup] Shutting down...\n");
    if (CreateSessionServer_func && RemoveSessionServer_func) {
        RemoveSessionServer_func(PKG_NAME, SESSION_NAME);
        fprintf(stderr, "[Cleanup] ✓ Session server removed\n");
    }

    if (g_dsoftbus_handle) {
        dlclose(g_dsoftbus_handle);
        fprintf(stderr, "[Cleanup] ✓ DSoftBus library unloaded\n");
    }

    fprintf(stderr, "[Cleanup] ✓ AccessToken (statically linked)\n");

    fprintf(stderr, "\n=======================================================\n");
    fprintf(stderr, "  Test Complete\n");
    fprintf(stderr, "=======================================================\n");

    return ret == 0 ? 0 : 1;
}
