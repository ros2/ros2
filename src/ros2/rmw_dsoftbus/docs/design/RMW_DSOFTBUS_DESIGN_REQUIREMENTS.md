---
doc_id: design_rmw_requirements
category: rmw_dsoftbus设计文档
title: rmw_dsoftbus 设计需求分析
description: 基于 FastDDS/dsoftbus 能力对比，确定 rmw_dsoftbus 必须自行实现的功能需求
priority: CRITICAL
last_updated: 2026-01-06
tags: [rmw_dsoftbus, 设计需求, 功能分析, FastDDS, dsoftbus]
use_cases:
  - 理解 rmw_dsoftbus 的功能需求
  - 学习 RMW 接口和 dsoftbus API 的映射关系
  - 识别需要自行实现的功能模块
quick_links:
  - RMW_DSOFTBUS_GAP_ANALYSIS.md: 功能差距分析
  - PHASE2_FINAL_STATUS.md: Phase 2 实现状态
---

# rmw_dsoftbus 设计需求分析报告

**文档版本**: 1.0
**创建日期**: 2026-01-04
**目的**: 基于 FastDDS/dsoftbus 能力对比，确定 rmw_dsoftbus 必须自行实现的功能

---

## 1. 核心问题

**问题**: rmw_fastrtps 能"站在 FastDDS 的肩膀上"，而 rmw_dsoftbus 能"站在 dsoftbus 的肩膀上"吗？

**答案**: 部分可以，但 dsoftbus 的肩膀比 FastDDS 矮很多。

---

## 2. 能力层次对比

### 2.1 架构对比图

```
┌─────────────────────────────────────────────────────────────────────────┐
│                            RMW 需求层                                    │
│  rmw_init / rmw_create_publisher / rmw_publish / rmw_take / rmw_wait    │
│  rmw_create_service / rmw_create_client / rmw_serialize / ...           │
└─────────────────────────────────────────────────────────────────────────┘
                    │                                     │
                    ▼                                     ▼
┌──────────────────────────────────┐   ┌──────────────────────────────────┐
│        rmw_fastrtps              │   │        rmw_dsoftbus              │
│  ┌────────────────────────────┐  │   │  ┌────────────────────────────┐  │
│  │ 类型适配 (TypeSupport)     │  │   │  │ 类型适配 + CDR 序列化 ⭐   │  │
│  │ 命名转换 (rt/rq/rr)        │  │   │  │ 命名转换 (rt/rq/rr)        │  │
│  │ Node 管理                  │  │   │  │ Node 管理                  │  │
│  │ QoS 转换                   │  │   │  │ QoS 转换 + 本地模拟 ⭐     │  │
│  │ GraphCache                 │  │   │  │ GraphCache + 发现协议 ⭐   │  │
│  │ Service/Client 2-Topic     │  │   │  │ Service/Client 2-Session   │  │
│  │ GID 映射                   │  │   │  │ GID 生成 ⭐                │  │
│  │ 事件映射                   │  │   │  │ 事件模拟 + 定时器 ⭐       │  │
│  │ WaitSet 适配               │  │   │  │ WaitSet 完整实现 ⭐⭐      │  │
│  │ 消息队列管理               │  │   │  │ 消息队列管理               │  │
│  │ 1:N 路由 ⭐                │  │   │  │ 1:N 多 Session 路由 ⭐⭐   │  │
│  └────────────────────────────┘  │   │  └────────────────────────────┘  │
└──────────────────────────────────┘   └──────────────────────────────────┘
                    │                                     │
                    ▼                                     ▼
┌──────────────────────────────────┐   ┌──────────────────────────────────┐
│           FastDDS                │   │           dsoftbus               │
│  ┌────────────────────────────┐  │   │  ┌────────────────────────────┐  │
│  │ ✅ DomainParticipant       │  │   │  │ ✅ Session 建立/关闭       │  │
│  │ ✅ Publisher/Subscriber    │  │   │  │ ✅ SendBytes/SendMessage   │  │
│  │ ✅ DataWriter/DataReader   │  │   │  │ ✅ OnBytesReceived 回调    │  │
│  │ ✅ Topic 管理              │  │   │  │ ❌ 无 Topic 抽象          │  │
│  │ ✅ SPDP/SEDP 自动发现      │  │   │  │ ⚠️ 仅设备级发现           │  │
│  │ ✅ FastCDR 序列化          │  │   │  │ ❌ 无序列化               │  │
│  │ ✅ 完整 QoS (22+策略)      │  │   │  │ ⚠️ 有限 QoS (9种)        │  │
│  │ ✅ WaitSet/Condition       │  │   │  │ ❌ 无 WaitSet             │  │
│  │ ✅ 11种状态事件            │  │   │  │ ⚠️ 4种会话事件           │  │
│  │ ✅ GuardCondition          │  │   │  │ ❌ 无 GuardCondition      │  │
│  │ ✅ 1:N 自动路由            │  │   │  │ ❌ 仅点对点               │  │
│  └────────────────────────────┘  │   │  └────────────────────────────┘  │
└──────────────────────────────────┘   └──────────────────────────────────┘

⭐ = rmw_dsoftbus 需要额外实现的功能（相比 rmw_fastrtps）
```

### 2.2 能力分层对比表

| 功能需求 | FastDDS 提供 | rmw_fastrtps 做 | dsoftbus 提供 | rmw_dsoftbus 必须做 |
|---------|-------------|----------------|--------------|-------------------|
| **基础通信** | DataWriter/Reader | 包装 | Session API | 包装 |
| **Topic 抽象** | Topic 类 | 创建/管理 | ❌ 无 | **sessionName 编码** |
| **1:N 发布** | 自动路由 | 无需处理 | ❌ 点对点 | **多 Session 管理** |
| **CDR 序列化** | FastCDR | 调用 | ❌ 无 | **完整实现** |
| **类型自省** | TypeObjectFactory | rosidl 桥接 | ❌ 无 | rosidl 桥接 + CDR |
| **Endpoint 发现** | SEDP 自动 | 转换为 GraphCache | ❌ 无 | **自定义协议** |
| **设备发现** | SPDP 自动 | 转换 GID | 设备级发现 | **过滤 + 扩展** |
| **WaitSet** | 原生支持 | 适配接口 | ❌ 无 | **pipe + select** |
| **GuardCondition** | 原生支持 | 直接映射 | ❌ 无 | **eventfd/pipe** |
| **QoS - Reliability** | 完整支持 | 枚举映射 | 有限支持 | 映射 |
| **QoS - History** | 完整支持 | 枚举映射 | ❌ 无 | **消息队列** |
| **QoS - Deadline** | 完整支持 | Duration 映射 | 仅延迟参数 | **定时器监控** |
| **QoS - Liveliness** | 完整支持 | 枚举映射 | 心跳机制 | **心跳 + 事件** |
| **事件回调** | 11 种 StatusMask | 类型映射 | 4 种会话事件 | **模拟 + 扩展** |
| **Node 概念** | ❌ 无 | 完全实现 | ❌ 无 | 完全实现 |
| **Service/Client** | ❌ 无 | 2 Topics 模拟 | ❌ 无 | 2 Sessions 模拟 |
| **GID/GUID** | GUID 原生 | 转换为 GID | ❌ 无 | **自行生成** |
| **Graph 缓存** | ❌ 无 | rmw_dds_common | ❌ 无 | **参考实现** |

---

## 3. rmw_dsoftbus 必须自行实现的功能清单

### 3.1 P0 - 阻塞性（无此功能，基础 Demo 无法运行）

| 编号 | 功能 | 复杂度 | 代码量 | 说明 |
|-----|------|-------|-------|------|
| **P0-1** | CDR 序列化系统 | 高 | 1500 行 | FastDDS 有 FastCDR，dsoftbus 无 |
| **P0-2** | WaitSet 机制 | 中 | 500 行 | FastDDS 原生支持，dsoftbus 无 |
| **P0-3** | GuardCondition | 低 | 200 行 | FastDDS 原生支持，dsoftbus 无 |
| **P0-4** | 消息队列 | 中 | 400 行 | FastDDS DataReader 内置，dsoftbus 回调需队列 |
| **P0-5** | Topic→Session 映射 | 低 | 100 行 | FastDDS 有 Topic 类，dsoftbus 用 sessionName |

### 3.2 P1 - 功能性（无此功能，ros2 工具不工作）

| 编号 | 功能 | 复杂度 | 代码量 | 说明 |
|-----|------|-------|-------|------|
| **P1-1** | Graph Discovery 协议 | 高 | 1000 行 | FastDDS SEDP 自动发现，dsoftbus 需自定义 |
| **P1-2** | GraphCache | 高 | 800 行 | rmw_dds_common 可参考 |
| **P1-3** | 1:N 发布路由 | 中 | 400 行 | FastDDS 自动，dsoftbus 需管理多 Session |
| **P1-4** | Service/Client RPC | 中 | 600 行 | 两者都需在 rmw 层实现 |
| **P1-5** | GID 生成 | 低 | 100 行 | FastDDS 有 GUID，dsoftbus 需自行生成 |

### 3.3 P2 - 完善性（无此功能，高级特性不工作）

| 编号 | 功能 | 复杂度 | 代码量 | 说明 |
|-----|------|-------|-------|------|
| **P2-1** | QoS 事件监控 | 中 | 300 行 | FastDDS 原生，dsoftbus 需定时器模拟 |
| **P2-2** | Deadline/Liveliness | 中 | 400 行 | FastDDS 原生，dsoftbus 需定时器 |
| **P2-3** | History 队列管理 | 低 | 200 行 | FastDDS 原生，dsoftbus 需消息队列 |

---

## 4. 工作量对比

### 4.1 代码量估算

| 层次 | rmw_fastrtps | rmw_dsoftbus | 差异原因 |
|-----|--------------|--------------|---------|
| 核心 RMW API 实现 | ~3,000 行 | ~3,500 行 | 多 500 行（1:N 路由） |
| 类型/序列化 | ~1,500 行 | ~2,500 行 | 多 1,000 行（无 FastCDR） |
| Graph 发现 | ~1,000 行 | ~1,800 行 | 多 800 行（无 SEDP） |
| WaitSet/Condition | ~300 行 | ~700 行 | 多 400 行（无原生支持） |
| QoS/事件 | ~500 行 | ~800 行 | 多 300 行（需模拟） |
| 传输层适配 | ~500 行 | ~300 行 | 少 200 行（SessionManager 较简单） |
| **总计** | **~6,800 行** | **~9,600 行** | **多 40%** |

### 4.2 开发时间估算

| 阶段 | rmw_fastrtps | rmw_dsoftbus | 差异 |
|-----|--------------|--------------|------|
| 基础 Pub/Sub | 2 周 | 3 周 | +50% (序列化) |
| Service/Client | 1 周 | 1.5 周 | +50% (无参考) |
| Graph Discovery | 1.5 周 | 3 周 | +100% (无 SEDP) |
| WaitSet/QoS | 1 周 | 2 周 | +100% (从零实现) |
| 测试/调试 | 2 周 | 3 周 | +50% |
| **总计** | **7.5 周** | **12.5 周** | **+67%** |

---

## 5. 架构设计建议

### 5.1 推荐的 rmw_dsoftbus 架构

```
+------------------------------------------------------------------+
|                          RMW API Layer                            |
|  (rmw_init, rmw_publish, rmw_take, rmw_wait, rmw_serialize, ...)  |
+------------------------------------------------------------------+
                               |
+------------------------------------------------------------------+
|                      rmw_dsoftbus Core                            |
|  +------------------+  +------------------+  +------------------+  |
|  | Serialization    |  | Topic Router     |  | Graph Discovery  |  |
|  | - CDR Encoder    |  | - Topic→Session  |  | - GraphCache     |  |
|  | - CDR Decoder    |  | - 1:N Routing    |  | - Broadcast Msg  |  |
|  | - Type Introspect|  | - Session Pool   |  | - Node Tracking  |  |
|  +------------------+  +------------------+  +------------------+  |
|                                                                    |
|  +------------------+  +------------------+  +------------------+  |
|  | Wait Mechanism   |  | QoS Manager      |  | RPC Handler      |  |
|  | - WaitSet        |  | - History Queue  |  | - Service        |  |
|  | - GuardCondition |  | - Deadline Timer |  | - Client         |  |
|  | - pipe + select  |  | - Liveliness     |  | - RequestID Match|  |
|  +------------------+  +------------------+  +------------------+  |
+------------------------------------------------------------------+
                               |
+------------------------------------------------------------------+
|                      SessionManager                               |
|  +------------------+  +------------------+  +------------------+  |
|  | Session Pool     |  | Connection Mgmt  |  | Callback Router  |  |
|  | - Create/Destroy |  | - Open/Close     |  | - OnBytesRecv    |  |
|  | - Topic Mapping  |  | - Peer NetworkID |  | - OnSessionOpen  |  |
|  +------------------+  +------------------+  +------------------+  |
+------------------------------------------------------------------+
                               |
+------------------------------------------------------------------+
|                      dsoftbus SDK                                 |
|  CreateSessionServer / OpenSession / SendBytes / CloseSession     |
|  PublishLNN / RefreshLNN / GetAllNodeDeviceInfo                   |
+------------------------------------------------------------------+
```

### 5.2 关键设计决策

#### D1: Topic 映射策略
```cpp
// sessionName = "ros2." + topic_hash
// 例: /chatter -> "ros2.chatter"
// 例: /namespace/topic -> "ros2.namespace_topic"
std::string topic_to_session_name(const std::string& topic);
std::string session_name_to_topic(const std::string& session_name);
```

#### D2: 1:N 发布实现
```cpp
class PublisherImpl {
    std::string topic_name_;
    std::map<std::string, int> peer_sessions_;  // NetworkID -> sessionId

    rmw_ret_t publish(const void* data, size_t len) {
        for (auto& [peer, session_id] : peer_sessions_) {
            int ret = SendBytes(session_id, data, len);
            // 处理错误...
        }
        return RMW_RET_OK;
    }

    void on_subscriber_discovered(const std::string& peer_network_id) {
        // 主动建立到新 Subscriber 的 Session
        int session_id = OpenSession(..., peer_network_id, ...);
        peer_sessions_[peer_network_id] = session_id;
    }
};
```

#### D3: Graph Discovery 协议
```cpp
// 使用保留 Topic 广播节点信息
// Topic: "ros2._graph_discovery"
// 消息格式: ParticipantEntitiesInfo (参考 rmw_dds_common)
struct GraphDiscoveryMessage {
    uint8_t gid[16];                    // 本节点 GID
    std::vector<NodeInfo> nodes;        // 节点列表
    std::vector<TopicInfo> publishers;  // 发布的 Topic
    std::vector<TopicInfo> subscribers; // 订阅的 Topic
};
```

#### D4: WaitSet 实现
```cpp
class WaitSetImpl {
    std::vector<int> subscription_fds_;
    std::vector<int> guard_condition_fds_;

    rmw_ret_t wait(rmw_time_t* timeout) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        int max_fd = 0;

        for (int fd : subscription_fds_) {
            FD_SET(fd, &read_fds);
            max_fd = std::max(max_fd, fd);
        }
        // ... guard_conditions 同理

        struct timeval tv = {timeout->sec, timeout->nsec / 1000};
        int ret = select(max_fd + 1, &read_fds, nullptr, nullptr, &tv);

        // 设置未就绪项为 NULL
        return (ret > 0) ? RMW_RET_OK : RMW_RET_TIMEOUT;
    }
};
```

---

## 6. 实现路线图

### Phase 1: 最小可运行 (3-4 周)
- [x] SessionManager 基础
- [x] Topic→Session 映射
- [ ] **CDR 序列化完整实现** ← 当前阻塞点
- [x] WaitSet (pipe + select)
- [x] GuardCondition
- [ ] 消息队列优化

### Phase 2: ros2 工具可用 (2-3 周)
- [ ] Graph Discovery 协议设计
- [ ] GraphCache 实现
- [ ] rmw_get_node_names / rmw_count_* 实现
- [ ] 1:N 发布路由优化

### Phase 3: 完整功能 (2-3 周)
- [ ] Service/Client RPC
- [ ] QoS 事件监控 (Deadline/Liveliness)
- [ ] History 队列 (KEEP_LAST/KEEP_ALL)
- [ ] 性能优化

### Phase 4: 生产就绪 (2 周)
- [ ] 多设备测试
- [ ] 异常处理增强
- [ ] 文档完善
- [ ] 性能基准测试

---

## 7. 总结

### 7.1 核心结论

**dsoftbus 与 FastDDS 的根本差异**：

| 维度 | FastDDS | dsoftbus |
|------|---------|----------|
| **定位** | DDS 规范实现 | 分布式设备通信 |
| **通信模型** | Topic-based Pub/Sub | Point-to-Point Session |
| **发现粒度** | Endpoint (Writer/Reader) | Device |
| **消息模型** | Type-aware | Bytes-only |
| **QoS** | 22+ 策略 | 9 种，无时序 |

**rmw_dsoftbus 需要"站在更低的肩膀上"**：
- dsoftbus 只提供了"传输管道"
- rmw_dsoftbus 需要实现 FastDDS 已经提供的很多功能
- 代码量增加约 40%，开发时间增加约 67%

### 7.2 关键技术挑战

1. **序列化系统** - FastDDS 有 FastCDR，dsoftbus 无任何序列化支持
2. **Graph Discovery** - FastDDS 有 SPDP/SEDP 自动发现，dsoftbus 只有设备发现
3. **1:N 路由** - FastDDS 自动处理，dsoftbus 需要管理多个 Session
4. **WaitSet** - FastDDS 原生支持，dsoftbus 需要从零实现

### 7.3 优势与机遇

尽管 dsoftbus 能力有限，但 rmw_dsoftbus 也有独特优势：

1. **轻量级** - 无需整个 DDS 协议栈
2. **灵活性** - 可以针对 OpenHarmony 优化
3. **安全性** - 利用 dsoftbus 原生设备级认证
4. **跨设备** - dsoftbus 专门针对分布式场景优化
5. **多链路** - WiFi/BLE/BR/PLC 统一抽象

---

**文档结束**

**相关文档**:
- `docs/FASTDDS_RMW_CAPABILITY_ANALYSIS.md` - FastDDS 能力详细分析
- `docs/dsoftbus_capability_boundary_analysis.md` - dsoftbus 能力边界分析
- `docs/FASTDDS_VS_DSOFTBUS_QUICK_REFERENCE.md` - 快速参考速查表
