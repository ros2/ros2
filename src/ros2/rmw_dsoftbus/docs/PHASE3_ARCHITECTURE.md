# Phase 3 RMW Discovery & Pub/Sub 完整架构设计

**设计日期**: 2026-01-14
**版本**: 1.0
**状态**: ✅ 架构设计完成，准备实现

---

## 📌 执行摘要

### 设计目标
基于 Phase 2 完整验证的跨设备通信框架，设计 Phase 3 以实现 ROS2 核心的 **Discovery（发现）** 和 **Pub/Sub（发布-订阅）** 功能。

### 核心设计
- **6 个分层模块**: DiscoveryManager, PubSubManager, GraphCache, SessionPool, MessageSerializer, Protocol
- **3 个通信协议**: Discovery (JSON), Data (Binary), Service (Binary)
- **4 个实现阶段**: Phase 3.1-3.4，总耗时 3-4 周
- **完整复用 Phase 2**: SessionPool 直接迁移已验证代码

### 关键指标
| 指标 | 目标 |
|------|------|
| 编译成功率 | 100% ✅ |
| API 可用性 | 100% ✅ |
| 跨设备消息延迟 | < 100ms |
| 消息吞吐量 | > 1000 msg/s |
| 节点发现时间 | < 5s |

---

## 🏗️ 架构总览

### 分层架构图

```
┌─────────────────────────────────────────────────────────────┐
│  ROS2 Application Layer                                      │
│  (rclcpp, rclpy - talker/listener)                          │
└─────────────────────────────────────────────────────────────┘
                            ▼
┌─────────────────────────────────────────────────────────────┐
│  RMW API Layer (rmw.h)                                       │
│  - rmw_create_node/publisher/subscription/service/client    │
│  - rmw_publish/take/send_request/take_response             │
│  - rmw_get_node_names/topic_names_and_types                │
└─────────────────────────────────────────────────────────────┘
                            ▼
┌─────────────────────────────────────────────────────────────┐
│  RMW DSoftBus Implementation (rmw_dsoftbus_cpp)             │
│  ┌──────────────┬──────────────┬──────────────┐            │
│  │ Discovery    │ PubSub       │ Service      │            │
│  │ Manager      │ Manager      │ Manager      │            │
│  └──────────────┴──────────────┴──────────────┘            │
│  ┌──────────────────────────────────────────┐              │
│  │ Graph Cache (Node/Endpoint Topology)     │              │
│  └──────────────────────────────────────────┘              │
│  ┌──────────────────────────────────────────┐              │
│  │ Session Pool (Connection Management)     │              │
│  └──────────────────────────────────────────┘              │
│  ┌──────────────────────────────────────────┐              │
│  │ Message Serializer (CDR-like Protocol)   │              │
│  └──────────────────────────────────────────┘              │
└─────────────────────────────────────────────────────────────┘
                            ▼
┌─────────────────────────────────────────────────────────────┐
│  DSoftBus Transport (dlopen shim from Phase 2)              │
│  - CreateSessionServer/OpenSession                          │
│  - SendBytes/OnBytesReceived                                │
│  - GetLocalNodeDeviceInfo/GetNodeKeyInfo                    │
└─────────────────────────────────────────────────────────────┘
                            ▼
┌─────────────────────────────────────────────────────────────┐
│  OpenHarmony System (libsoftbus_client.z.so)               │
└─────────────────────────────────────────────────────────────┘
```

### 核心模块矩阵

| 模块 | 职责 | 关键接口 | 文件 |
|------|------|---------|------|
| **DiscoveryManager** | 节点发现、端点注册 | registerNode, announcePublisher, startDiscoveryThread | discovery_manager.cpp |
| **PubSubManager** | 消息发布订阅 | createPublisher, publish, createSubscriber, take | pubsub_manager.cpp |
| **GraphCache** | 拓扑缓存、快速查询 | addNode, getPublishersByTopic, purgeExpiredEntries | graph_cache.cpp |
| **SessionPool** | 跨设备连接复用 | getOrCreateSession, sendBytes, setOnBytesReceivedCallback | session_pool.cpp (修改) |
| **MessageSerializer** | 消息编解码 | serialize, deserialize | message_serializer.cpp |
| **Protocol** | 协议定义和编码 | encoderDiscoveryMsg, decodeDataMsg | discovery_protocol.cpp |

---

## 📋 实现阶段和计划

### Phase 3.1: 基础框架 (1-2 天)

**关键任务**:
1. 创建所有头文件和接口定义
2. 实现 GraphCache（完整且带单元测试）
3. 重构 SessionPool（迁移 Phase 2 代码）
4. 实现 MessageSerializer 基础功能

**验收标准**:
- ✅ 编译成功 (`ninja -C build-ohos`)
- ✅ GraphCache 单元测试通过
- ✅ SessionPool 可建立跨设备 Session

**文件列表**:
- `include/rmw_dsoftbus/discovery_manager.h` (新)
- `include/rmw_dsoftbus/pubsub_manager.h` (新)
- `include/rmw_dsoftbus/graph_cache.h` (新)
- `include/rmw_dsoftbus/session_pool.h` (新)
- `include/rmw_dsoftbus/message_serializer.h` (新)
- `include/rmw_dsoftbus/protocol.h` (新)
- `src/graph_cache.cpp` (新)
- `src/session_pool.cpp` (修改)
- `src/message_serializer.cpp` (新)
- `test/test_graph_cache.cpp` (新)

---

### Phase 3.2: Discovery 协议 (2-3 天)

**关键任务**:
1. 实现 DiscoveryManager（节点注册、广播）
2. 实现 discovery_protocol.cpp（JSON 编解码）
3. 集成 Discovery 消息收发
4. 实现定时广播线程（5s 心跳）
5. 实现 GraphCache 过期清理

**验收标准**:
- ✅ 两设备互相发现对方节点
- ✅ GraphCache 正确维护远程节点列表
- ✅ 心跳超时后自动清理过期节点

**测试方案**:
```bash
# Device 1
rmw_discovery_test --role=publisher --node-name=/node1

# Device 2
rmw_discovery_test --role=subscriber --node-name=/node2
# 应看到 /node1 被发现
```

---

### Phase 3.3: Pub/Sub 核心 (3-4 天)

**关键任务**:
1. 实现 PubSubManager（Publisher/Subscriber 管理）
2. 实现 publish() 路由逻辑
3. 实现 take() 消息队列管理
4. 实现 Data 消息头和负载处理
5. 集成序列化和 Session 发送

**验收标准**:
- ✅ 单 Publisher → 单 Subscriber 正常通信
- ✅ 消息完整性验证（Checksum）
- ✅ 支持基本 QoS（Reliable/Best-Effort）

**测试方案**:
```bash
# Device 1: Publisher
rmw_pubsub_test --role=publisher --topic=/chatter --rate=1

# Device 2: Subscriber
rmw_pubsub_test --role=subscriber --topic=/chatter
# 应每秒收到 1 条消息
```

---

### Phase 3.4: 集成与交付 (2 天)

**关键任务**:
1. 编译 talker/listener（依赖 rmw_dsoftbus）
2. 部署到两设备
3. 运行端到端测试
4. 性能测试和优化
5. 文档完善

**验收标准**:
- ✅ talker/listener 正常跨设备通信
- ✅ 消息延迟 < 100ms
- ✅ 无内存泄漏

**测试方案**:
```bash
# Device 1
export RMW_IMPLEMENTATION=rmw_dsoftbus_cpp
./talker

# Device 2
export RMW_IMPLEMENTATION=rmw_dsoftbus_cpp
./listener
# 应打印 "I heard: [Hello World: X]"
```

---

## 📦 文件清单

### 需要创建的文件

| 文件 | 类型 | 优先级 | 预计行数 |
|------|------|--------|---------|
| `include/rmw_dsoftbus/discovery_manager.h` | 头文件 | P0 | 50-80 |
| `include/rmw_dsoftbus/pubsub_manager.h` | 头文件 | P0 | 60-100 |
| `include/rmw_dsoftbus/graph_cache.h` | 头文件 | P0 | 40-60 |
| `include/rmw_dsoftbus/session_pool.h` | 头文件 | P0 | 50-70 |
| `include/rmw_dsoftbus/message_serializer.h` | 头文件 | P0 | 40-60 |
| `include/rmw_dsoftbus/protocol.h` | 头文件 | P0 | 100-150 |
| `src/discovery_protocol.cpp` | 源文件 | P0 | 200-300 |
| `src/pubsub_manager.cpp` | 源文件 | P0 | 300-500 |
| `src/graph_cache.cpp` | 源文件 | P0 | 200-300 |
| `src/message_serializer.cpp` | 源文件 | P1 | 200-300 |
| `src/message_queue.cpp` | 源文件 | P1 | 100-150 |
| `test/test_graph_cache.cpp` | 测试 | P1 | 100-150 |
| `test/test_pubsub_e2e.cpp` | 测试 | P1 | 150-250 |
| `docs/PHASE3_ARCHITECTURE.md` | 文档 | P0 | （本文档）|

### 需要修改的文件

| 文件 | 修改内容 | 优先级 |
|------|---------|--------|
| `src/session_manager.cpp` | 重构为 SessionPool，迁移 Phase 2 代码 | P0 |
| `src/discovery_manager.cpp` | 完全重构，集成新架构 | P0 |
| `src/rmw_node.cpp` | 调用 DiscoveryManager API | P0 |
| `src/rmw_publisher.cpp` | 调用 PubSubManager API | P0 |
| `src/rmw_subscription.cpp` | 调用 PubSubManager API | P0 |
| `BUILD.gn` | 添加新源文件和依赖 | P0 |
| `include/rmw_dsoftbus/types.h` | 添加新数据结构 | P1 |

### 复用 Phase 2 代码

| Phase 2 文件 | 迁移内容 | 目标文件 |
|-------------|---------|---------|
| `test/phase2_cross_device_session_test.cpp` | OpenSession 逻辑、回调处理 | `src/session_pool.cpp` |
| `test/softbus_dlopen_shim.cpp` | dlopen 加载逻辑 | `src/dsoftbus_shim.cpp` (新) |
| `config/softbus_trans_permission.json` | 权限配置 | 保持不变 |

---

## 🔄 通信协议设计

### Protocol 1: Discovery 消息 (JSON)

**特点**:
- 可读性强，易于调试
- 灵活扩展，版本兼容
- Session Name: `rmw_dsoftbus_discovery`
- 广播频率: 5 秒/次（心跳）

**消息格式**:
```json
{
  "type": "discovery",
  "version": 1,
  "network_id": "2ce0442a2400c631a9ca0b8c89f5b31514ecf9a065ab8a50e826480999eebb77",
  "timestamp_ms": 1736953214567,
  "nodes": [
    {
      "name": "/talker",
      "namespace": "/",
      "gid": "01.0f.c6.27.3b.18.40.55.00.00.00.00|00.00.01.c1"
    }
  ],
  "endpoints": [
    {
      "type": "publisher",
      "topic": "/chatter",
      "type_name": "std_msgs::msg::String",
      "node": "/talker",
      "qos": {
        "reliability": "reliable",
        "durability": "volatile",
        "history_depth": 10
      }
    }
  ]
}
```

---

### Protocol 2: Data 消息 (Binary)

**消息头** (1024 bytes):
```
┌──────────┬─────────┬──────────┬──────────────┬──────────────┐
│  Magic   │ Version │  Flags   │  Topic Name  │  Type Name   │
│(4B:RMWD) │ (2B:1)  │  (2B)    │   (256B)     │    (256B)    │
├──────────┼─────────┼──────────┼──────────────┼──────────────┤
│ Sequence │ Payload │ Checksum │         Reserved (480B)      │
│ (8B)     │(4B Size)│  (4B)    │                              │
└──────────┴─────────┴──────────┴──────────────┴──────────────┘
```

**特点**:
- 高效二进制格式
- 支持大消息标志（Phase 4 分片）
- CRC32 完整性检查
- Session Name: `rmw_dsoftbus_data`

---

### Protocol 3: Service Request/Reply (Binary)

**Request 消息头** (512 bytes):
```
┌──────────┬──────────┬──────────┬─────────────┐
│  Magic   │Msg Type  │ Service  │  Request ID │
│  (4B)    │ (2B:0x01)│ Name(256)│   (8B)      │
├──────────┼──────────┼──────────┼─────────────┤
│ Client   │ Timeout  │Payload   │  Reserved   │
│ GID(24B) │   (4B)   │Size (4B) │   (156B)    │
└──────────┴──────────┴──────────┴─────────────┘
```

**Reply 消息头** (512 bytes):
```
┌──────────┬──────────┬──────────┬──────────┐
│  Magic   │Msg Type  │Request ID│  Status  │
│  (4B)    │ (2B:0x02)│  (8B)    │  (2B)    │
└──────────┴──────────┴──────────┴──────────┘
```

---

## 🎯 关键设计决策

### 决策 1: Discovery 使用 JSON
**理由**:
- 可读性强，便于调试
- 灵活扩展，版本兼容
- 网络带宽非瓶颈（5s 一次）

**后续优化**:
- Phase 4：可升级到 Protocol Buffers

---

### 决策 2: SessionPool 而非每个 Endpoint 一个 Session
**理由**:
- 减少 DSoftBus 系统 Session 限制
- 降低连接建立开销
- 简化连接生命周期管理

**实现**:
- SessionPool 中按 NetworkID 维护连接
- 消息头中包含 Topic 信息用于路由
- 参考 DDS Virtual Channels 设计

---

### 决策 3: Phase 3 不实现 Service/Client
**理由**:
- Pub/Sub 是 ROS2 核心，优先级更高
- Service 可复用 Pub/Sub 基础设施
- Service 需要 Request-Reply 匹配，复杂度高

**时间线**:
- Phase 3 (现在): Pub/Sub + Discovery
- Phase 4 (后续): Service/Client + 高级 QoS

---

## ⚠️ 风险评估与缓解

### 技术风险

| 风险 | 可能性 | 影响 | 缓解措施 |
|------|--------|------|---------|
| **DSoftBus Session 不稳定** | 中 | 高 | ✅ 复用 Phase 2 已验证代码 + 心跳检测 |
| **消息序列化兼容性** | 低 | 中 | ✅ 使用 ROS2 官方 typesupport + 单元测试 |
| **跨设备时钟同步** | 中 | 低 | ✅ 使用 sequence number 而非时间戳 |
| **大消息传输** | 高 | 中 | ✅ Phase 3 限制 < 64KB，Phase 4 分片 |

### 集成风险

| 风险 | 可能性 | 影响 | 缓解措施 |
|------|--------|------|---------|
| **RMW API 理解偏差** | 低 | 高 | ✅ 参考 rmw_fastrtps 实现 + 官方测试 |
| **多设备权限配置** | 低 | 中 | ✅ 复用 Phase 2 权限配置 + 自动化脚本 |
| **Thread Safety** | 中 | 高 | ✅ 所有共享数据使用互斥锁 + ThreadSanitizer |

---

## 📈 性能目标

| 指标 | 目标 | 验证方法 |
|------|------|---------|
| 节点发现时间 | < 5s | 测量从节点启动到被远程发现的时间 |
| 消息延迟 | < 100ms | 双向 Ping-Pong 测试 |
| 消息吞吐量 | > 1000 msg/s | 高频率发布测试 |
| 发现协议开销 | < 5% 带宽 | 测量 Discovery 消息大小和频率 |
| 内存占用 | < 50MB | 长期运行 + valgrind 检测 |

---

## 🚀 后续计划（Phase 4+）

### Phase 4: 高级 QoS & Service
- 实现所有 ROS2 QoS 策略
- Service/Client 实现
- 消息分片（> 64KB）
- 协议优化（Protocol Buffers）

### Phase 5: 性能优化
- 消息压缩
- 批量发送
- 零拷贝优化
- NUMA 感知

### Phase 6: 生产加固
- 完整的错误恢复
- 日志和监控
- 安全增强
- 官方文档和示例

---

## 📚 参考资源

### 内部文档
- `docs/PHASE2_COMPLETE_SUMMARY.md` - Phase 2 验证成果
- `docs/PHASE2_DEPLOYMENT_AND_TESTING_GUIDE.md` - 部署指南
- `docs/DISCOVERY_PROTOCOL_V3.1.md` - Discovery 协议
- `test/phase2_cross_device_session_test.cpp` - Session 实现参考

### 外部参考
- **RMW FastRTPS**: DDS 基础实现参考
- **RMW Cyclone DDS**: 轻量级实现参考
- **ROS2 Design**: 官方架构和 API 设计
- **OpenHarmony DSoftBus**: 传输层文档

---

## ✅ 最终检查清单

- [x] 架构设计完整
- [x] 6 个核心模块清晰定义
- [x] 3 个通信协议设计完整
- [x] 4 个实现阶段明确规划
- [x] 文件清单详细列出
- [x] 风险评估和缓解完成
- [x] 性能指标明确定义
- [x] Phase 2 代码复用计划确认

---

**🎉 Phase 3 架构设计完成！**

**下一步**:
1. 确认架构（可提出修改意见）
2. 创建 Phase 3 分支
3. 开始 Phase 3.1 基础框架搭建

**预计完成**: 3-4 周内完成所有 4 个阶段，实现 talker/listener 跨设备通信。

---

**设计者**: RMW DSoftBus Architecture Team
**设计日期**: 2026-01-14
**版本**: 1.0
**状态**: ✅ 准备实现
