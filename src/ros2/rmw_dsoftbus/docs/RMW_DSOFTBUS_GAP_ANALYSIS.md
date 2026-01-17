---
doc_id: design_rmw_gap_analysis
category: rmw_dsoftbus设计文档
title: rmw_dsoftbus 实现差距分析报告
description: 对标 FastDDS，分析 rmw_dsoftbus 当前与目标功能之间的差距和优先级
priority: HIGH
last_updated: 2026-01-06
tags: [功能差距, rmw_dsoftbus, FastDDS对标, 实现优先级]
use_cases:
  - 了解 rmw_dsoftbus 与 FastDDS 的功能差距
  - 确定实现优先级
  - 规划后续功能开发
---

# rmw_dsoftbus 实现差距分析报告

**文档版本**: 1.0
**创建日期**: 2026-01-04
**目的**: 对比 rmw_dsoftbus 设计需求与当前实现状态，识别差距并制定补完计划

---

## 1. 执行摘要

### 1.1 整体评估

| 维度 | 设计要求 | 当前状态 | 完成度 |
|------|---------|---------|--------|
| **P0 阻塞性功能** | 5 项 | 5 项 ✅ | **100%** |
| **P1 功能性功能** | 5 项 | 2 项 ⚠️ | **40%** |
| **P2 完善性功能** | 3 项 | 1 项 ⚠️ | **33%** |
| **总体** | 13 项 | 8 项 | **62%** |

### 1.2 关键发现

**已完成的核心功能** (可运行基础 Demo):
- ✅ CDR 序列化系统 (675 行，支持 rosidl_typesupport_introspection_c)
- ✅ WaitSet 机制 (pipe + select，484 行)
- ✅ GuardCondition (完整实现)
- ✅ 消息队列 (SubscriptionImpl::message_queue)
- ✅ Topic→Session 映射 (SessionManager，288 行)
- ✅ Publisher/Subscription 完整实现
- ✅ GID 生成

**未完成的功能性功能** (ros2 工具不可用):
- ❌ Graph Discovery 协议 (返回空数组)
- ❌ GraphCache (未实现)
- ❌ Service/Client RPC (Stub only)
- ⚠️ 1:N 发布路由 (需手动配置 peer_network_id)

---

## 2. 详细差距分析

### 2.1 P0 - 阻塞性功能 (100% 完成 ✅)

| 编号 | 功能 | 设计要求 | 实现状态 | 源文件 | 代码行数 |
|-----|------|---------|---------|-------|---------|
| P0-1 | CDR 序列化 | 1500 行 | ✅ **完成** | `rmw_typesupport_serializer.cpp` | 675 行 |
| P0-2 | WaitSet | 500 行 | ✅ **完成** | `rmw_wait.cpp` | 484 行 |
| P0-3 | GuardCondition | 200 行 | ✅ **完成** | `rmw_guard_condition.cpp` | ~200 行 |
| P0-4 | 消息队列 | 400 行 | ✅ **完成** | `types.h` + subscription | 集成 |
| P0-5 | Topic→Session 映射 | 100 行 | ✅ **完成** | `session_manager.cpp` | 288 行 |

**P0-1 CDR 序列化详情**:
```cpp
// rmw_typesupport_serializer.cpp 核心功能:
- GenericCDRSerializer 类
- 支持所有原始类型 (int8-64, float, double, bool)
- 支持 string, wstring
- 支持嵌套消息 (递归序列化)
- 支持静态数组和动态序列 (sequence)
- C API: rmw_dsoftbus_serialize_ros_message() / rmw_dsoftbus_deserialize_ros_message()
```

**P0-2 WaitSet 详情**:
```cpp
// rmw_wait.cpp 核心功能:
- fd_set + select() 实现
- 支持 subscriptions, guard_conditions, services, clients
- 超时处理
- 未就绪项设置为 NULL (符合 RMW 规范)
```

### 2.2 P1 - 功能性功能 (40% 完成 ⚠️)

| 编号 | 功能 | 设计要求 | 实现状态 | 当前代码位置 | 差距说明 |
|-----|------|---------|---------|-------------|---------|
| P1-1 | Graph Discovery | 1000 行 | ❌ **Stub** | `rmw_get_info.cpp` | 返回空数组 |
| P1-2 | GraphCache | 800 行 | ❌ **未实现** | - | 无任何实现 |
| P1-3 | 1:N 发布路由 | 400 行 | ⚠️ **部分** | `rmw_publisher.cpp` | 需手动配置 |
| P1-4 | Service/Client RPC | 600 行 | ❌ **Stub** | `rmw_service.cpp`, `rmw_client.cpp` | 仅框架 |
| P1-5 | GID 生成 | 100 行 | ✅ **完成** | `rmw_publisher.cpp:234-240` | - |

**P1-1 Graph Discovery 当前状态**:
```cpp
// rmw_get_info.cpp 第32行注释:
// TODO: Implement node discovery via dsoftbus

// rmw_get_node_names() 返回:
names->size = 0;  // 空数组
namespaces->size = 0;

// rmw_get_topic_names_and_types() 返回:
topics->names.size = 0;  // 空数组
```

**P1-3 1:N 发布路由当前状态**:
```cpp
// rmw_publisher.cpp 第244-259行:
auto context = rmw_dsoftbus::get_context_impl();
if (context && !context->peer_network_id.empty()) {
    // 仅连接单个预配置的 peer
    int session_id = rmw_dsoftbus::SessionManager::instance().open_session(
        topic_name, context->peer_network_id);
    pub_impl->session_ids.push_back(session_id);
}

// 问题: 只能连接一个 peer，且需要手动配置 peer_network_id
// 需要: 自动发现多个 subscriber 并建立连接
```

**P1-4 Service/Client 当前状态**:
```cpp
// rmw_service.cpp 第92行:
fprintf(stderr, "[rmw_create_service] STUB - Service/Client not implemented in Phase 1\n");
return nullptr;

// rmw_client.cpp 使用了未实现的函数:
// - rmw_dsoftbus::create_service_client()  <- 声明但未实现
// - rmw_dsoftbus::send_service_request()   <- 声明但未实现
// - rmw_dsoftbus::is_service_available()   <- 声明但未实现
```

### 2.3 P2 - 完善性功能 (33% 完成 ⚠️)

| 编号 | 功能 | 设计要求 | 实现状态 | 说明 |
|-----|------|---------|---------|------|
| P2-1 | QoS 事件监控 | 300 行 | ⚠️ **部分** | qos_mapper.cpp 存在，但无定时器 |
| P2-2 | Deadline/Liveliness | 400 行 | ⚠️ **部分** | QoS 结构存在，但无监控线程 |
| P2-3 | History 队列管理 | 200 行 | ✅ **完成** | message_queue 在 SubscriptionImpl |

---

## 3. 代码量对比

### 3.1 设计预估 vs 实际实现

| 模块 | 设计预估 | 实际代码 | 状态 |
|-----|---------|---------|------|
| CDR 序列化 | 1500 行 | 675 行 | ✅ 精简实现 |
| WaitSet/Condition | 700 行 | ~680 行 | ✅ 符合预期 |
| Topic→Session 映射 | 100 行 | 288 行 | ✅ 更完善 |
| 消息队列 | 400 行 | ~150 行 | ✅ 集成实现 |
| Graph Discovery | 1800 行 | ~50 行 (stub) | ❌ 缺 1750 行 |
| Service/Client RPC | 600 行 | ~590 行 (框架) | ⚠️ 需完善 |
| 1:N 路由 | 400 行 | ~50 行 | ⚠️ 缺 350 行 |
| **总计** | ~9600 行 | ~9000 行 | **差距 ~2100 行** |

### 3.2 当前源文件统计

```
rmw_dsoftbus/src/ 统计 (2026-01-04):
─────────────────────────────────────────
rmw_subscription.cpp      855 行  ✅ 完整
rmw_typesupport_serializer.cpp  675 行  ✅ 完整
rmw_publisher.cpp         557 行  ✅ 完整
rmw_wait.cpp              484 行  ✅ 完整
rmw_get_info.cpp          391 行  ⚠️ Stub
rmw_init.cpp              ~350 行  ✅ 完整
rmw_service.cpp           296 行  ❌ Stub
rmw_client.cpp            295 行  ⚠️ 框架
session_manager.cpp       288 行  ✅ 完整
rmw_node.cpp              ~250 行  ✅ 完整
qos_mapper.cpp            ~200 行  ✅ 完整
cdr_serializer.cpp        ~300 行  ✅ 完整
其他文件                  ~1000 行
─────────────────────────────────────────
总计                      ~9000 行
```

---

## 4. 功能差距详细说明

### 4.1 Graph Discovery (缺失 ~1800 行)

**设计需求**:
```cpp
// 需要实现:
rmw_get_node_names()           // 获取所有节点名
rmw_get_node_names_with_enclaves()
rmw_count_publishers()         // 统计 Publisher 数量
rmw_count_subscribers()        // 统计 Subscriber 数量
rmw_get_topic_names_and_types() // 获取所有 Topic
rmw_get_publishers_info_by_topic()
rmw_get_subscriptions_info_by_topic()
rmw_get_service_names_and_types()
rmw_get_client_names_and_types_by_node()

// 需要的机制:
- GraphCache: 缓存网络中所有节点和端点信息
- Discovery 协议: 通过 dsoftbus 广播节点信息
- 事件通知: 节点上线/下线时通知
```

**当前状态**:
```cpp
// rmw_get_info.cpp 所有函数返回空:
rmw_ret_t rmw_get_node_names(...) {
    // TODO: Implement node discovery via dsoftbus
    names->size = 0;
    namespaces->size = 0;
    return RMW_RET_OK;
}
```

**影响**: ros2 node list / ros2 topic list 返回空

### 4.2 Service/Client RPC (需完善 ~400 行)

**设计需求**:
```cpp
// Service 端 (被调用方):
rmw_create_service()    // 创建服务
rmw_take_request()      // 接收请求
rmw_send_response()     // 发送响应
rmw_destroy_service()   // 销毁服务

// Client 端 (调用方):
rmw_create_client()     // 创建客户端
rmw_send_request()      // 发送请求
rmw_take_response()     // 接收响应
rmw_destroy_client()    // 销毁客户端

// 需要的机制:
- RequestID 匹配: 将响应匹配到对应请求
- 超时处理: 请求超时机制
- 双向 Session: 或使用两个单向 Session
```

**当前状态**:
```cpp
// rmw_service.cpp:
rmw_service_t * rmw_create_service(...) {
    fprintf(stderr, "[rmw_create_service] STUB - Service/Client not implemented in Phase 1\n");
    return nullptr;  // 直接返回 NULL
}

// rmw_client.cpp 框架存在但依赖未实现的函数:
extern int create_service_client(...);     // 未实现
extern int send_service_request(...);      // 未实现
extern bool is_service_available(...);     // 未实现
```

**影响**: ros2 service call 不可用，参数服务器不可用

### 4.3 1:N 发布路由 (缺失 ~350 行)

**设计需求**:
```cpp
class PublisherImpl {
    // 需要: 管理到多个 Subscriber 的连接
    std::map<std::string, int> peer_sessions_;  // NetworkID -> sessionId

    void on_subscriber_discovered(const std::string& peer_network_id) {
        // 自动发现新 Subscriber 时建立连接
        int session_id = OpenSession(..., peer_network_id, ...);
        peer_sessions_[peer_network_id] = session_id;
    }

    rmw_ret_t publish(const void* data, size_t len) {
        // 向所有连接的 Subscriber 发送
        for (auto& [peer, session_id] : peer_sessions_) {
            SendBytes(session_id, data, len);
        }
    }
};
```

**当前状态**:
```cpp
// rmw_publisher.cpp:244-259
// 只连接预配置的单个 peer:
if (context && !context->peer_network_id.empty()) {
    int session_id = SessionManager::instance().open_session(
        topic_name, context->peer_network_id);
    pub_impl->session_ids.push_back(session_id);
}

// 问题:
// 1. 需要手动设置 RMW_DSOFTBUS_PEER_ID 环境变量
// 2. 只能连接一个 Subscriber
// 3. 无法自动发现新的 Subscriber
```

**影响**: 需要手动配置，无法支持多订阅者

---

## 5. 补完计划

### 5.1 优先级排序

| 优先级 | 功能 | 预计工作量 | 影响范围 |
|-------|------|----------|---------|
| **P1** | Service/Client RPC | 8h | ros2 service, 参数服务器 |
| **P2** | Graph Discovery 基础 | 16h | ros2 node/topic list |
| **P3** | 1:N 自动路由 | 8h | 多订阅者场景 |
| **P4** | GraphCache 完整实现 | 16h | 完整 Graph API |
| **P5** | QoS 事件监控 | 4h | Deadline/Liveliness 事件 |

### 5.2 Phase 2 实现计划 (Service/Client)

**目标**: 实现基本的 Service/Client RPC

**关键设计**:
```cpp
// 使用两个 Session 模拟 RPC:
// Session 1: Request (Client → Service)
// Session 2: Response (Service → Client)

// RequestID 格式:
struct ServiceRequestHeader {
    uint8_t client_gid[24];   // 客户端 GID
    int64_t sequence_number;  // 序列号
};

// Service 端实现:
class ServiceImpl {
    int request_session_id;   // 接收请求的 Session
    std::map<GID, int> client_response_sessions_;  // 客户端 GID → 响应 Session

    void on_request_received(const void* data, size_t len) {
        // 解析 header，找到客户端 GID
        // 通过 client_response_sessions_ 发送响应
    }
};
```

**预计代码量**: ~400 行
**预计时间**: 8 小时

### 5.3 Phase 3 实现计划 (Graph Discovery)

**目标**: 实现基础的节点/话题发现

**关键设计**:
```cpp
// 使用保留 Topic 广播节点信息:
// Topic: "ros2._graph_discovery"

struct GraphDiscoveryMessage {
    uint8_t participant_gid[16];
    std::vector<NodeInfo> nodes;
    std::vector<EndpointInfo> publishers;
    std::vector<EndpointInfo> subscribers;
};

class GraphCache {
    std::map<GID, ParticipantInfo> participants_;
    std::map<std::string, std::vector<TopicInfo>> topics_;

    void on_discovery_message(const GraphDiscoveryMessage& msg);
    std::vector<std::string> get_node_names();
    std::vector<std::string> get_topic_names();
};
```

**预计代码量**: ~800 行
**预计时间**: 16 小时

### 5.4 Phase 4 实现计划 (1:N 路由)

**目标**: 自动发现并连接多个 Subscriber

**关键设计**:
```cpp
// 集成 GraphCache，监听新 Subscriber:
class PublisherImpl {
    void on_subscriber_discovered(const std::string& peer_network_id,
                                   const std::string& topic_name) {
        if (topic_name == this->topic_name_) {
            int session_id = OpenSession(..., peer_network_id, ...);
            peer_sessions_[peer_network_id] = session_id;
        }
    }

    void on_subscriber_removed(const std::string& peer_network_id) {
        auto it = peer_sessions_.find(peer_network_id);
        if (it != peer_sessions_.end()) {
            CloseSession(it->second);
            peer_sessions_.erase(it);
        }
    }
};
```

**预计代码量**: ~200 行
**预计时间**: 8 小时

---

## 6. 总结

### 6.1 当前状态评估

**✅ 优势**:
- P0 阻塞性功能 100% 完成，可运行基础 Pub/Sub Demo
- CDR 序列化实现精简高效 (675 行 vs 设计 1500 行)
- WaitSet 实现完整，符合 RMW 规范
- 代码质量良好，有完整的错误处理

**❌ 不足**:
- Graph Discovery 完全缺失，ros2 工具不可用
- Service/Client 仅有框架，RPC 不可用
- 1:N 路由需手动配置，无法自动发现

### 6.2 工作量估算

| 阶段 | 内容 | 预计时间 |
|-----|------|---------|
| Phase 2 | Service/Client RPC | 8 小时 |
| Phase 3 | Graph Discovery 基础 | 16 小时 |
| Phase 4 | 1:N 自动路由 | 8 小时 |
| Phase 5 | GraphCache 完整 | 16 小时 |
| Phase 6 | QoS 事件监控 | 4 小时 |
| **总计** | | **52 小时** |

### 6.3 建议路线

1. **短期 (1 周)**: 完成 Service/Client RPC，支持参数服务器
2. **中期 (2 周)**: 完成 Graph Discovery，使 ros2 工具可用
3. **长期 (1 月)**: 完成 1:N 路由和完整 GraphCache

---

**文档结束**

**相关文档**:
- `docs/RMW_DSOFTBUS_DESIGN_REQUIREMENTS.md` - 设计需求
- `docs/FASTDDS_VS_DSOFTBUS_QUICK_REFERENCE.md` - 能力对比
- `rmw_dsoftbus/src/` - 源代码目录
