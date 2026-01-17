/*
 * Phase 2 Simple Test - 基于成功的权限绕过方案
 * 测试跨设备发现和 Session 建立
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <dlfcn.h>

// AccessToken（静态链接）
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

extern "C" {
    uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
    int SetSelfTokenID(uint64_t tokenID);
}

// dsoftbus 类型
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
    int (*OnSessionOpened)(int, int);
    void (*OnSessionClosed)(int);
    void (*OnBytesReceived)(int, const void *, unsigned int);
    void (*OnMessageReceived)(int, const void *, unsigned int);
    void *OnStreamReceived;
    void *OnQosEvent;
} ISessionListener;

typedef struct {
    int dataType;
    int linkTypeNum;
    int linkType[4];
} SessionAttribute;

// API 函数指针
typedef int (*RegNodeDeviceStateCb_t)(const char *, const INodeStateCb *);
typedef int (*GetLocalNodeDeviceInfo_t)(const char *, NodeBasicInfo *);
typedef int (*GetAllNodeDeviceInfo_t)(const char *, NodeBasicInfo **, int *);
typedef void (*FreeNodeInfo_t)(NodeBasicInfo *);
typedef int (*CreateSessionServer_t)(const char *, const char *, const ISessionListener *);
typedef int (*OpenSession_t)(const char *, const char *, const char *, const char *, const SessionAttribute *);
typedef int (*SendBytes_t)(int, const void *, unsigned int);
typedef void (*CloseSession_t)(int);
typedef int (*RemoveSessionServer_t)(const char *, const char *);

static void* g_handle = nullptr;
static RegNodeDeviceStateCb_t RegNodeDeviceStateCb_func = nullptr;
static GetLocalNodeDeviceInfo_t GetLocalNodeDeviceInfo_func = nullptr;
static GetAllNodeDeviceInfo_t GetAllNodeDeviceInfo_func = nullptr;
static FreeNodeInfo_t FreeNodeInfo_func = nullptr;
static CreateSessionServer_t CreateSessionServer_func = nullptr;
static OpenSession_t OpenSession_func = nullptr;
static SendBytes_t SendBytes_func = nullptr;
static CloseSession_t CloseSession_func = nullptr;
static RemoveSessionServer_t RemoveSessionServer_func = nullptr;

const char* PKG_NAME = "com.huawei.ros2_rmw_dsoftbus";
const char* SESSION_NAME = "com.huawei.ros2_rmw_dsoftbus.phase2_test";

static int g_sessionId = -1;
static int g_peerCount = 0;

// 回调
void OnNodeOnline(NodeBasicInfo *info) {
    if (info) {
        g_peerCount++;
        printf("[Discovery] ✓✓✓ Device #%d online: %s (NetworkID: %.20s...)\n",
               g_peerCount, info->deviceName, info->networkId);
    }
}

void OnNodeOffline(NodeBasicInfo *info) {
    if (info) printf("[Discovery] Device offline: %.20s...\n", info->networkId);
}

void OnDeviceInfoChanged(int type, NodeBasicInfo *info) {}

static INodeStateCb g_nodeCallback = {
    0xFFFF,  // events
    OnNodeOnline,
    OnNodeOffline,
    OnDeviceInfoChanged,
};

int OnSessionOpened(int sessionId, int result) {
    printf("[Session] ✓✓✓ Session opened: id=%d, result=%d\n", sessionId, result);
    if (result == 0) g_sessionId = sessionId;
    return 0;
}

void OnSessionClosed(int sessionId) {
    printf("[Session] Session closed: id=%d\n", sessionId);
    if (g_sessionId == sessionId) g_sessionId = -1;
}

void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    printf("[Session] ✓✓✓ Received %u bytes on session %d\n", len, sessionId);
    if (data && len < 256) printf("[Data] %.*s\n", len, (const char*)data);
}

void OnMessageReceived(int sessionId, const void *data, unsigned int len) {}

static ISessionListener g_listener = {
    OnSessionOpened,
    OnSessionClosed,
    OnBytesReceived,
    OnMessageReceived,
    nullptr,  // OnStreamReceived
    nullptr,  // OnQosEvent
};

int main(int argc, char *argv[]) {
    printf("\n");
    printf("=======================================================\n");
    printf("  Phase 2 Cross-Device Session Test\n");
    printf("  PKG: %s\n", PKG_NAME);
    printf("  SESSION: %s\n", SESSION_NAME);
    printf("=======================================================\n\n");

    // Step 1: 权限设置
    printf("[Phase2] Step 1: Setup Permission\n");
    const char* perms[2] = {
        "ohos.permission.DISTRIBUTED_DATASYNC",
        "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
    };
    NativeTokenInfoParams params;
    params.dcapsNum = 0;
    params.permsNum = 2;
    params.aclsNum = 0;
    params.dcaps = nullptr;
    params.perms = perms;
    params.acls = nullptr;
    params.processName = PKG_NAME;
    params.aplStr = "system_basic";
    uint64_t tokenId = GetAccessTokenId(&params);
    printf("[Phase2] Token: 0x%llx\n", (unsigned long long)tokenId);
    SetSelfTokenID(tokenId);
    printf("[Phase2] ✅ Permission setup complete\n\n");

    // Step 2: 加载 dsoftbus
    printf("[Phase2] Step 2: Load DSoftBus\n");
    g_handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_handle) {
        printf("ERROR: %s\n", dlerror());
        return 1;
    }

    RegNodeDeviceStateCb_func = (RegNodeDeviceStateCb_t)dlsym(g_handle, "RegNodeDeviceStateCb");
    GetLocalNodeDeviceInfo_func = (GetLocalNodeDeviceInfo_t)dlsym(g_handle, "GetLocalNodeDeviceInfo");
    GetAllNodeDeviceInfo_func = (GetAllNodeDeviceInfo_t)dlsym(g_handle, "GetAllNodeDeviceInfo");
    FreeNodeInfo_func = (FreeNodeInfo_t)dlsym(g_handle, "FreeNodeInfo");
    CreateSessionServer_func = (CreateSessionServer_t)dlsym(g_handle, "CreateSessionServer");
    OpenSession_func = (OpenSession_t)dlsym(g_handle, "OpenSession");
    SendBytes_func = (SendBytes_t)dlsym(g_handle, "SendBytes");
    CloseSession_func = (CloseSession_t)dlsym(g_handle, "CloseSession");
    RemoveSessionServer_func = (RemoveSessionServer_t)dlsym(g_handle, "RemoveSessionServer");
    printf("[Phase2] ✓ DSoftBus loaded\n\n");

    // Step 3: 设备发现
    printf("[Phase2] Step 3: Device Discovery\n");
    int ret = RegNodeDeviceStateCb_func(PKG_NAME, &g_nodeCallback);
    printf("[Phase2] RegNodeDeviceStateCb: %d\n", ret);

    NodeBasicInfo localInfo;
    memset(&localInfo, 0, sizeof(localInfo));
    ret = GetLocalNodeDeviceInfo_func(PKG_NAME, &localInfo);
    if (ret == 0) {
        printf("[Phase2] ✓ Local Device: %s\n", localInfo.deviceName);
        printf("[Phase2]   NetworkID: %.40s...\n", localInfo.networkId);
    }

    printf("[Phase2] Waiting 10s for peer discovery...\n");
    for (int i = 0; i < 10; i++) {
        sleep(1);
        printf(".");
        if (g_peerCount > 0) {
            printf("\n[Phase2] ✓ Found %d peer(s)\n", g_peerCount);
            break;
        }
    }
    printf("\n\n");

    // Step 4: 创建 Session Server
    printf("[Phase2] Step 4: Create Session Server\n");
    ret = CreateSessionServer_func(PKG_NAME, SESSION_NAME, &g_listener);
    printf("[Phase2] CreateSessionServer: %d\n", ret);

    if (ret == 0) {
        printf("[Phase2] ✅ Session server created\n");
        
        // Step 5: 获取所有设备
        printf("\n[Phase2] Step 5: Get All Online Devices\n");
        NodeBasicInfo *devices = nullptr;
        int deviceCount = 0;
        ret = GetAllNodeDeviceInfo_func(PKG_NAME, &devices, &deviceCount);
        printf("[Phase2] Found %d online device(s)\n", deviceCount);
        
        if (deviceCount > 0 && devices) {
            for (int i = 0; i < deviceCount; i++) {
                printf("[Phase2]   Device %d: %s\n", i, devices[i].deviceName);
                printf("[Phase2]     NetworkID: %.40s...\n", devices[i].networkId);
            }
            
            // 如果有对端设备，尝试建立 Session
            if (deviceCount > 0 && argc > 1) {
                printf("\n[Phase2] Step 6: Open Session to Peer\n");
                
                SessionAttribute attr;
                memset(&attr, 0, sizeof(attr));
                attr.dataType = 0;  // TYPE_BYTES
                
                g_sessionId = OpenSession_func(SESSION_NAME, SESSION_NAME,
                                               devices[0].networkId, nullptr, &attr);
                printf("[Phase2] OpenSession: %d\n", g_sessionId);
                
                if (g_sessionId >= 0) {
                    printf("[Phase2] ✅ Session opened\n");
                    
                    sleep(2);
                    
                    // 发送测试消息
                    const char* msg = "Hello from Phase2 test!";
                    ret = SendBytes_func(g_sessionId, msg, strlen(msg) + 1);
                    printf("[Phase2] SendBytes: %d\n", ret);
                    
                    sleep(2);
                    
                    CloseSession_func(g_sessionId);
                    printf("[Phase2] ✓ Session closed\n");
                }
            }
            
            FreeNodeInfo_func(devices);
        }
        
        RemoveSessionServer_func(PKG_NAME, SESSION_NAME);
        printf("\n[Phase2] ✓ Session server removed\n");
    }

    dlclose(g_handle);

    printf("\n");
    printf("=======================================================\n");
    printf("  Phase 2 Test Complete\n");
    printf("  Peers found: %d\n", g_peerCount);
    printf("=======================================================\n\n");

    return 0;
}
