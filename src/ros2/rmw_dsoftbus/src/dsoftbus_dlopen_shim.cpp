/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

// Copyright (c) 2024 ROS2 KaihongOS Port Project
// DSoftBus API dlopen shim - loads real libsoftbus_client.z.so at runtime

#include <dlfcn.h>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <unistd.h>
#include <mutex>

// ============================================================================
// DSoftBus library paths
// ============================================================================
static const char* DSOFTBUS_LIB_PATHS[] = {
    "/system/lib64/platformsdk/libsoftbus_client.z.so",
    "/system/lib64/libsoftbus_client.z.so",
    "libsoftbus_client.z.so",
    nullptr
};

// ============================================================================
// Forward declarations from dsoftbus_session.h (to avoid circular includes)
// ============================================================================
struct ISessionListener;
struct SessionAttribute;

struct NodeBasicInfo {
    char networkId[65];
    char deviceName[128];
    uint16_t deviceTypeId;
    int32_t osType;
    char osVersion[128];
};

// ============================================================================
// Function pointer types
// ============================================================================
typedef int (*CreateSessionServer_fn)(const char*, const char*, const ISessionListener*);
typedef int (*RemoveSessionServer_fn)(const char*, const char*);
typedef int (*OpenSession_fn)(const char*, const char*, const char*, const char*, const SessionAttribute*);
typedef void (*CloseSession_fn)(int);
typedef int (*SendBytes_fn)(int, const void*, unsigned int);
typedef int (*SendMessage_fn)(int, const void*, unsigned int);
typedef int (*GetLocalNodeDeviceInfo_fn)(const char*, NodeBasicInfo*);
typedef int (*GetAllNodeDeviceInfo_fn)(const char*, NodeBasicInfo**, int32_t*);
typedef void (*FreeNodeInfo_fn)(NodeBasicInfo*);
typedef int (*GetPeerDeviceId_fn)(int, char*, unsigned int);
typedef int (*GetPeerSessionName_fn)(int, char*, unsigned int);
typedef int (*GetSessionSide_fn)(int);
typedef int (*GetMySessionName_fn)(int, char*, unsigned int);

// ============================================================================
// Global state
// ============================================================================
static void* g_dsoftbus_handle = nullptr;
static bool g_initialized = false;
static std::mutex g_init_mutex;

// Function pointers
static CreateSessionServer_fn g_CreateSessionServer = nullptr;
static RemoveSessionServer_fn g_RemoveSessionServer = nullptr;
static OpenSession_fn g_OpenSession = nullptr;
static CloseSession_fn g_CloseSession = nullptr;
static SendBytes_fn g_SendBytes = nullptr;
static SendMessage_fn g_SendMessage = nullptr;
static GetLocalNodeDeviceInfo_fn g_GetLocalNodeDeviceInfo = nullptr;
static GetAllNodeDeviceInfo_fn g_GetAllNodeDeviceInfo = nullptr;
static FreeNodeInfo_fn g_FreeNodeInfo = nullptr;
static GetPeerDeviceId_fn g_GetPeerDeviceId = nullptr;
static GetPeerSessionName_fn g_GetPeerSessionName = nullptr;
static GetSessionSide_fn g_GetSessionSide = nullptr;
static GetMySessionName_fn g_GetMySessionName = nullptr;

// ============================================================================
// Initialization
// ============================================================================
static bool load_dsoftbus_library() {
    std::lock_guard<std::mutex> lock(g_init_mutex);

    if (g_initialized) {
        return g_dsoftbus_handle != nullptr;
    }

    g_initialized = true;

    // Try each library path
    for (int i = 0; DSOFTBUS_LIB_PATHS[i] != nullptr; i++) {
        fprintf(stderr, "[dsoftbus_shim] Trying to load: %s\n", DSOFTBUS_LIB_PATHS[i]);
        g_dsoftbus_handle = dlopen(DSOFTBUS_LIB_PATHS[i], RTLD_NOW | RTLD_GLOBAL);
        if (g_dsoftbus_handle) {
            fprintf(stderr, "[dsoftbus_shim] Successfully loaded: %s\n", DSOFTBUS_LIB_PATHS[i]);
            break;
        }
        fprintf(stderr, "[dsoftbus_shim] Failed: %s\n", dlerror());
    }

    if (!g_dsoftbus_handle) {
        fprintf(stderr, "[dsoftbus_shim] ERROR: Could not load dsoftbus library from any path\n");
        return false;
    }

    // Load all function symbols
    #define LOAD_SYM(name) \
        g_##name = (name##_fn)dlsym(g_dsoftbus_handle, #name); \
        if (!g_##name) { \
            fprintf(stderr, "[dsoftbus_shim] WARNING: Symbol not found: %s\n", #name); \
        } else { \
            fprintf(stderr, "[dsoftbus_shim] Loaded: %s @ %p\n", #name, (void*)g_##name); \
        }

    LOAD_SYM(CreateSessionServer);
    LOAD_SYM(RemoveSessionServer);
    LOAD_SYM(OpenSession);
    LOAD_SYM(CloseSession);
    LOAD_SYM(SendBytes);
    LOAD_SYM(SendMessage);
    LOAD_SYM(GetLocalNodeDeviceInfo);
    LOAD_SYM(GetAllNodeDeviceInfo);
    LOAD_SYM(FreeNodeInfo);
    LOAD_SYM(GetPeerDeviceId);
    LOAD_SYM(GetPeerSessionName);
    LOAD_SYM(GetSessionSide);
    LOAD_SYM(GetMySessionName);

    #undef LOAD_SYM

    // Check critical symbols
    if (!g_CreateSessionServer || !g_OpenSession || !g_SendBytes) {
        fprintf(stderr, "[dsoftbus_shim] ERROR: Critical symbols missing\n");
        return false;
    }

    fprintf(stderr, "[dsoftbus_shim] DSoftBus library initialization complete\n");
    return true;
}

// ============================================================================
// Exported C API - Calls real dsoftbus functions via dlopen
// ============================================================================
extern "C" {

int CreateSessionServer(const char* pkgName, const char* sessionName, const ISessionListener* listener) {
    if (!load_dsoftbus_library() || !g_CreateSessionServer) {
        fprintf(stderr, "[dsoftbus_shim] CreateSessionServer: library not loaded\n");
        return -1;
    }
    return g_CreateSessionServer(pkgName, sessionName, listener);
}

int RemoveSessionServer(const char* pkgName, const char* sessionName) {
    if (!load_dsoftbus_library() || !g_RemoveSessionServer) {
        fprintf(stderr, "[dsoftbus_shim] RemoveSessionServer: library not loaded\n");
        return -1;
    }
    return g_RemoveSessionServer(pkgName, sessionName);
}

int OpenSession(const char* mySessionName, const char* peerSessionName,
                const char* peerNetworkId, const char* groupId,
                const SessionAttribute* attr) {
    if (!load_dsoftbus_library() || !g_OpenSession) {
        fprintf(stderr, "[dsoftbus_shim] OpenSession: library not loaded\n");
        return -1;
    }
    return g_OpenSession(mySessionName, peerSessionName, peerNetworkId, groupId, attr);
}

void CloseSession(int sessionId) {
    if (!load_dsoftbus_library() || !g_CloseSession) {
        fprintf(stderr, "[dsoftbus_shim] CloseSession: library not loaded\n");
        return;
    }
    g_CloseSession(sessionId);
}

int SendBytes(int sessionId, const void* data, unsigned int len) {
    if (!load_dsoftbus_library() || !g_SendBytes) {
        fprintf(stderr, "[dsoftbus_shim] SendBytes: library not loaded\n");
        return -1;
    }
    return g_SendBytes(sessionId, data, len);
}

int SendMessage(int sessionId, const void* data, unsigned int len) {
    if (!load_dsoftbus_library() || !g_SendMessage) {
        fprintf(stderr, "[dsoftbus_shim] SendMessage: library not loaded\n");
        return -1;
    }
    return g_SendMessage(sessionId, data, len);
}

int GetLocalNodeDeviceInfo(const char* pkgName, NodeBasicInfo* info) {
    if (!load_dsoftbus_library() || !g_GetLocalNodeDeviceInfo) {
        fprintf(stderr, "[dsoftbus_shim] GetLocalNodeDeviceInfo: library not loaded\n");
        return -1;
    }
    return g_GetLocalNodeDeviceInfo(pkgName, info);
}

int GetAllNodeDeviceInfo(const char* pkgName, NodeBasicInfo** nodeInfo, int32_t* infoNum) {
    if (!load_dsoftbus_library() || !g_GetAllNodeDeviceInfo) {
        fprintf(stderr, "[dsoftbus_shim] GetAllNodeDeviceInfo: library not loaded\n");
        return -1;
    }
    return g_GetAllNodeDeviceInfo(pkgName, nodeInfo, infoNum);
}

void FreeNodeInfo(NodeBasicInfo* nodeInfo) {
    if (!load_dsoftbus_library() || !g_FreeNodeInfo) {
        fprintf(stderr, "[dsoftbus_shim] FreeNodeInfo: library not loaded\n");
        return;
    }
    g_FreeNodeInfo(nodeInfo);
}

int GetPeerDeviceId(int sessionId, char* networkId, unsigned int len) {
    if (!load_dsoftbus_library() || !g_GetPeerDeviceId) {
        fprintf(stderr, "[dsoftbus_shim] GetPeerDeviceId: library not loaded\n");
        return -1;
    }
    return g_GetPeerDeviceId(sessionId, networkId, len);
}

int GetPeerSessionName(int sessionId, char* sessionName, unsigned int len) {
    if (!load_dsoftbus_library() || !g_GetPeerSessionName) {
        fprintf(stderr, "[dsoftbus_shim] GetPeerSessionName: library not loaded\n");
        return -1;
    }
    return g_GetPeerSessionName(sessionId, sessionName, len);
}

int GetSessionSide(int sessionId) {
    if (!load_dsoftbus_library() || !g_GetSessionSide) {
        fprintf(stderr, "[dsoftbus_shim] GetSessionSide: library not loaded\n");
        return -1;
    }
    return g_GetSessionSide(sessionId);
}

int GetMySessionName(int sessionId, char* sessionName, unsigned int len) {
    if (!load_dsoftbus_library() || !g_GetMySessionName) {
        fprintf(stderr, "[dsoftbus_shim] GetMySessionName: library not loaded\n");
        return -1;
    }
    return g_GetMySessionName(sessionId, sessionName, len);
}

}  // extern "C"

// ============================================================================
// Namespace utilities
// ============================================================================
namespace rmw_dsoftbus {

// Service encoding helper (used by both service_client_manager and old code)
std::string encode_service_for_session(const char* service_name) {
    return std::string("com.huawei.dmsdp.ros2.service.") + service_name;
}

}  // namespace rmw_dsoftbus
