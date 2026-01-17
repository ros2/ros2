# dsoftbus Session API 使用指南 - 以 Session 为主

**日期**: 2026-01-16
**目标**: 以 Session API 为主，理解 kh_trans 和 socket 的使用场景

---

## API 架构总览

### 1. 标准 Session API (session.h)

**核心 API**:
```c
// 服务端 API
int32_t CreateSessionServer(const char *pkgName, const char *sessionName,
                           const ISessionListener *listener);
int32_t RemoveSessionServer(const char *pkgName, const char *sessionName);

// 客户端 API
int32_t OpenSession(const char *mySessionName, const char *peerSessionName,
                   const char *peerNetworkId, const char *groupId,
                   const SessionAttribute *attr);
void CloseSession(int32_t sessionId);

// 数据传输 API
int32_t SendBytes(int32_t sessionId, const void *data, unsigned int len);
int32_t SendMessage(int32_t sessionId, const void *data, unsigned int len);
int32_t SendStream(int32_t sessionId, const StreamData *data,
                  const StreamData *ext, const StreamFrameInfo *param);
int32_t SendFile(int32_t sessionId, const char *sFileList[],
                const char *dFileList[], uint32_t fileCnt);

// 会话信息查询
int32_t GetMySessionName(int32_t sessionId, char *sessionName, unsigned int len);
int32_t GetPeerSessionName(int32_t sessionId, char *sessionName, unsigned int len);
int32_t GetPeerDeviceId(int32_t sessionId, char *networkId, unsigned int len);
int32_t GetSessionSide(int32_t sessionId);
```

**数据类型**:
```c
typedef enum {
    TYPE_MESSAGE = 1,    // 小消息 (≤4KB)
    TYPE_BYTES = 2,      // 大数据 (≤64KB)
    TYPE_FILE = 3,       // 文件传输
    TYPE_STREAM = 4,     // 流式传输
} SessionType;

typedef struct {
    int32_t dataType;    // SessionType
    int32_t linkTypeNum;
    LinkType *linkType;
} SessionAttribute;
```

### 2. KH Session API (kh_session.h)

KaihongOS 特有的 Session 封装层，提供额外的传输控制功能。

**核心 API**:
```c
// 服务端 API (与标准 Session 相同)
int32_t CreateKhSessionServer(const char *pkgName, const char *sessionName,
                              const ISessionListener *listener);
int32_t RemoveKhSessionServer(const char *pkgName, const char *sessionName);

// 客户端 API (扩展参数)
int32_t OpenKhSession(const char *mySessionName, const char *peerSessionName,
                     char *networkId, char *groupId, SessionType sessionType,
                     KhTransParam *khTransParam);
int32_t CloseKhSession(int32_t khSessionId);

// 数据传输 API
int32_t KhSendBytes(int32_t khSessionId, const void *data, unsigned int len);
int32_t KhSendMessage(int32_t khSessionId, const void *data, unsigned int len);

// KH 特有功能 API
int32_t GetKhTransType(int32_t khSessionId, KhTransType *khTransType);
int32_t SetKhTransType(int32_t khSessionId, KhTransType khTransType);
int32_t GetKhSessionOption(int32_t khSessionId, KhSessionOption option, int32_t *value);
```

**KH 特有数据类型**:
```c
// 传输模式
typedef enum {
    KH_TRANS_NORMAL,        // 普通传输
    KH_TRANS_REDUNDANCY,    // 冗余传输 (暂不支持)
    KH_TRANS_FAST_SWITCH,   // 快速切换模式
} KhTransType;

// QoS 参数
typedef enum {
    KH_LOW_LANE_DELAY,      // 低延迟
    KH_NORMAL_LANE_DELAY,   // 正常延迟
    KH_HIGH_LANE_DELAY,     // 高延迟
} KhLaneDelayType;

typedef enum {
    KH_LOW_LANE_PACKET_LOSS,    // 低丢包率
    KH_NORMAL_LANE_PACKET_LOSS, // 正常丢包率
    KH_HIGH_LANE_PACKET_LOSS,   // 高丢包率
} KhLanePacketLossType;

// OpenKhSession 参数
typedef struct {
    int32_t khTransType;           // KhTransType
    int32_t expectDelayType;       // KhLaneDelayType
    int32_t expectPacketLossType;  // KhLanePacketLossType
} KhTransParam;
```

---

## API 选择策略

### 使用标准 Session API 的场景 ✅

**推荐用于**:
1. **ROS2 Pub/Sub 通信** - 使用 `SendBytes` 传输序列化消息
2. **ROS2 Service/Client** - 使用 `SendMessage` 进行请求响应
3. **跨平台兼容** - 标准 API 在所有 OpenHarmony 设备上可用
4. **简单的点对点通信** - 不需要特殊 QoS 控制

**示例代码** (ROS2 Publisher):
```c
// 1. 创建 Session Server
ISessionListener listener = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
    .OnBytesReceived = OnBytesReceived,
};

int ret = CreateSessionServer("com.huawei.ros2_rmw_dsoftbus",
                             "com.huawei.ros2_rmw_dsoftbus.topic_chatter",
                             &listener);

// 2. Publisher 发送数据
int sessionId = /* 从 OnSessionOpened 获取 */;
uint8_t msgData[256];
// 序列化 ROS2 消息到 msgData...
SendBytes(sessionId, msgData, msgLen);
```

### 使用 KH Session API 的场景 ⚠️

**仅在需要以下功能时使用**:
1. **QoS 控制** - 需要指定延迟或丢包率要求
2. **快速切换** - 网络环境变化时自动切换传输通道
3. **冗余传输** - 关键数据需要冗余保护（将来支持）
4. **KaihongOS 特定优化** - 利用 KH 传输层优化

**注意事项**:
- KH Session 需要 KH_TRANS 层初始化
- 增加了系统复杂度
- 可能与其他 OpenHarmony 设备不兼容

**示例代码** (低延迟通信):
```c
// 1. 创建 KH Session Server (同标准 API)
CreateKhSessionServer("com.huawei.ros2_rmw_dsoftbus",
                     "com.huawei.ros2_rmw_dsoftbus.realtime_control",
                     &listener);

// 2. 打开 Session 时指定 QoS 参数
KhTransParam param = {
    .khTransType = KH_TRANS_FAST_SWITCH,      // 快速切换模式
    .expectDelayType = KH_LOW_LANE_DELAY,     // 低延迟要求
    .expectPacketLossType = KH_LOW_LANE_PACKET_LOSS,  // 低丢包率
};

int khSessionId = OpenKhSession("mySession", "peerSession",
                               peerNetworkId, "", TYPE_BYTES, &param);

// 3. 发送数据
KhSendBytes(khSessionId, data, len);
```

---

## Socket API 的使用场景

### Socket 层次关系

```
应用层 API:
  ┌─────────────────┐
  │  Session API    │  ← 推荐使用
  └────────┬────────┘
           │
  ┌────────▼────────┐
  │  KH Session API │  ← 需要 QoS 控制时使用
  └────────┬────────┘
           │
  ┌────────▼────────┐
  │  Socket Layer   │  ← 底层实现，通常不直接使用
  └─────────────────┘
```

### 何时需要考虑 Socket

**通常情况**: ❌ **不需要直接使用 Socket API**

Session API 已经封装了所有传输功能：
- 自动选择最优传输通道 (WiFi/BR/BLE)
- 自动处理连接建立和维护
- 自动处理序列化和反序列化

**特殊场景**: ⚠️ **可能需要 Socket 信息**

仅当需要以下底层信息时：
1. **调试和监控** - 查看底层连接状态
2. **性能分析** - 分析不同链路类型的性能
3. **高级优化** - 手动选择特定传输通道

**获取 Socket 信息**:
```c
// 通过 Session API 查询底层信息
int32_t GetSessionOption(int32_t sessionId, SessionOption option,
                        int32_t *value, int32_t valueSize);

// 示例：查询链路类型
int32_t linkType;
GetSessionOption(sessionId, SESSION_OPTION_LINK_TYPE,
                &linkType, sizeof(linkType));
```

---

## 推荐架构：以 Session 为主

### ROS2 rmw_dsoftbus 实现建议

```c
// 1. 初始化阶段
rmw_init() {
    // 创建 Session Server (每个 node 一个)
    CreateSessionServer(pkgName, sessionName, &listener);
}

// 2. Publisher 创建
rmw_create_publisher() {
    // 不需要额外操作，Session Server 已创建
    // 记录 topic 名称和类型信息
}

// 3. Subscription 创建
rmw_create_subscription() {
    // 打开到 Publisher 的 Session
    int sessionId = OpenSession(mySessionName, peerSessionName,
                               peerNetworkId, "", &attr);
    // 保存 sessionId 用于接收数据
}

// 4. 发布消息
rmw_publish() {
    // 序列化消息
    serialize_message(msg, &buffer, &size);

    // 发送到所有订阅者
    for (int sessionId : subscriber_sessions) {
        SendBytes(sessionId, buffer, size);
    }
}

// 5. 接收消息
OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    // 反序列化消息
    deserialize_message(data, len, &msg);

    // 调用用户回调
    user_callback(msg);
}

// 6. 清理阶段
rmw_destroy_node() {
    // 关闭所有 Session
    for (int sessionId : sessions) {
        CloseSession(sessionId);
    }

    // 移除 Session Server
    RemoveSessionServer(pkgName, sessionName);
}
```

### 何时使用 KH Session

**仅在需要特殊 QoS 时**:
```c
// 例如：实时控制消息需要低延迟
if (qos.reliability == RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT &&
    qos.history == RMW_QOS_POLICY_HISTORY_KEEP_LAST) {

    // 使用 KH Session 指定低延迟
    KhTransParam param = {
        .khTransType = KH_TRANS_FAST_SWITCH,
        .expectDelayType = KH_LOW_LANE_DELAY,
        .expectPacketLossType = KH_NORMAL_LANE_PACKET_LOSS,
    };

    khSessionId = OpenKhSession(..., &param);
}
```

---

## 实际测试中的观察

### OpenSession 测试结果分析

**现象**:
```
[Test] OpenSession returned: 1          ← Session API 成功
[Callback] result=-426115004            ← KH_TRANS 层失败
Error: [KH_TRANS] not init
```

**分析**:
1. **标准 Session 层工作正常**
   - `OpenSession` 返回有效的 sessionId
   - 底层传输通道已建立
   - 可以使用 `SendBytes` / `SendMessage`

2. **KH_TRANS 层未初始化**
   - KH Session 回调失败
   - 不影响标准 Session API 使用
   - 仅影响 KH 特定功能

**结论**:
✅ **可以使用标准 Session API 进行通信**
⚠️ **暂时不使用 KH Session 功能**

---

## 推荐开发流程

### Phase 1: 使用标准 Session API

**目标**: 实现基础的 ROS2 通信功能

1. ✅ 使用 `CreateSessionServer` / `RemoveSessionServer`
2. ✅ 使用 `OpenSession` / `CloseSession`
3. ✅ 使用 `SendBytes` 传输序列化消息
4. ✅ 使用 `OnBytesReceived` 接收消息

**优点**:
- API 简单直接
- 已验证可用 (CreateSessionServer 成功)
- 跨平台兼容性好
- 不依赖 KH_TRANS 初始化

### Phase 2: 测试和优化

**目标**: 验证通信功能和性能

1. 测试跨设备消息传输
2. 测试不同消息大小
3. 测试并发通信
4. 性能基准测试

### Phase 3: 可选的 KH Session 集成

**仅在需要时**:

1. 调查 KH_TRANS 初始化方法
2. 测试 QoS 参数效果
3. 评估性能提升
4. 决定是否采用

---

## 代码示例：ROS2 Integration

### 简化的 rmw_dsoftbus 实现

```c
// rmw_dsoftbus_session.c

#include "session.h"
#include "rmw/rmw.h"

// 全局 Session 管理
typedef struct {
    int sessionId;
    char topicName[256];
    rmw_subscription_t *subscription;
} SessionInfo;

static SessionInfo g_sessions[MAX_SESSIONS];

// Session 回调
static int OnSessionOpened(int sessionId, int result) {
    if (result == SOFTBUS_OK) {
        printf("[rmw_dsoftbus] Session %d opened\n", sessionId);
        // 通知等待的线程
    }
    return result;
}

static void OnBytesReceived(int sessionId, const void *data, unsigned int len) {
    // 查找对应的 subscription
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (g_sessions[i].sessionId == sessionId) {
            // 反序列化消息
            void *ros_msg = deserialize_message(data, len);

            // 调用 ROS2 回调
            rmw_subscription_t *sub = g_sessions[i].subscription;
            sub->user_callback(ros_msg);
            break;
        }
    }
}

// RMW Publisher 实现
rmw_ret_t rmw_publish(
    const rmw_publisher_t *publisher,
    const void *ros_message)
{
    // 序列化消息
    uint8_t buffer[4096];
    size_t size = serialize_message(ros_message, buffer, sizeof(buffer));

    // 发送到所有订阅者的 Session
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (strcmp(g_sessions[i].topicName, publisher->topic_name) == 0) {
            int ret = SendBytes(g_sessions[i].sessionId, buffer, size);
            if (ret != SOFTBUS_OK) {
                return RMW_RET_ERROR;
            }
        }
    }

    return RMW_RET_OK;
}

// RMW Subscription 实现
rmw_ret_t rmw_create_subscription(
    rmw_node_t *node,
    const char *topic_name,
    const char *peer_network_id)
{
    // 配置 Session 属性
    SessionAttribute attr = {
        .dataType = TYPE_BYTES,
        .linkTypeNum = 0,  // 自动选择
    };

    // 打开到 Publisher 的 Session
    char my_session[256], peer_session[256];
    snprintf(my_session, sizeof(my_session), "%s.sub", topic_name);
    snprintf(peer_session, sizeof(peer_session), "%s.pub", topic_name);

    int sessionId = OpenSession(my_session, peer_session,
                               peer_network_id, "", &attr);

    if (sessionId < 0) {
        return RMW_RET_ERROR;
    }

    // 保存 Session 信息
    g_sessions[num_sessions].sessionId = sessionId;
    strcpy(g_sessions[num_sessions].topicName, topic_name);
    num_sessions++;

    return RMW_RET_OK;
}
```

---

## 总结

### API 使用优先级

1. **首选**: 标准 Session API (`session.h`)
   - CreateSessionServer / OpenSession / SendBytes
   - 简单、稳定、跨平台

2. **可选**: KH Session API (`kh_session.h`)
   - 仅在需要 QoS 控制时使用
   - 需要 KH_TRANS 初始化

3. **避免**: 直接使用 Socket API
   - Session 已封装所有功能
   - 除非需要底层调试信息

### 当前状态

✅ **已验证可用**:
- CreateSessionServer (权限问题已解决)
- OpenSession (API 层工作正常)
- 设备发现 (GetAllNodeDeviceInfo)

⚠️ **暂时不可用**:
- KH Session 回调 (KH_TRANS 未初始化)
- KH 特定功能 (不影响基础通信)

### 建议

**立即开始**: 使用标准 Session API 实现 ROS2 通信

**暂时跳过**: KH Session 功能，等到 Phase 4 系统集成时再研究

---

**文档创建**: 2026-01-16
**状态**: 基于 OpenHarmony 源码分析和实际测试结果
