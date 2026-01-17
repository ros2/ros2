# Phase 3 快速参考卡片

**设计日期**: 2026-01-14
**状态**: ✅ 架构设计完成

---

## 📌 5 分钟快速了解 Phase 3

### Phase 3 做什么？
实现 ROS2 核心的 **Discovery（节点发现）** 和 **Pub/Sub（消息传输）** 功能，让 talker/listener 能在两个 rk3588s 上跨设备通信。

### 关键成果（4 周）
```
Week 1: 基础框架搭建 → GraphCache + SessionPool
Week 2: Discovery 协议 → 节点和端点发现
Week 3: Pub/Sub 实现  → 消息发布和订阅
Week 4: 集成和优化   → talker/listener 端到端测试
```

### 核心模块（6 个）
| 模块 | 职责 | 复杂度 |
|------|------|--------|
| **DiscoveryManager** | 节点/端点发现 | 中 |
| **PubSubManager** | 消息发布/订阅 | 高 |
| **GraphCache** | 拓扑缓存 | 中 |
| **SessionPool** | 连接复用（复用 Phase 2） | 低 |
| **MessageSerializer** | 消息编解码 | 中 |
| **Protocol** | 协议编码 | 低 |

### 通信协议（3 个）
| 协议 | 格式 | 用途 |
|------|------|------|
| **Discovery** | JSON | 节点和端点发现（5s 心跳） |
| **Data** | Binary | 消息发送接收 |
| **Service** | Binary | 请求应答（Phase 4） |

---

## 🎯 关键数据

### 两设备的 Phase 2 基础
```
设备 1: ec29004133314d38433031a522413c00
  Token: 0x28055235
  NetworkID: 2ce0442a2400c631a9ca0b8c89f5b31514ecf9a065ab8a50e826480999eebb77

设备 2: ec29004133314d38433031a751c63c00
  Token: 0x280883bb
  NetworkID: 8d1b112eb9c39f85d73cb704995b75379adbb394d5b83e11d7abe542430a6b92
```

### Phase 3 的新增数据结构
```cpp
// 节点信息
struct NodeInfo {
    std::string node_name;        // /talker
    std::string namespace_;       // /
    std::string network_id;       // 64 字符 NetworkID
    uint64_t timestamp_ms;
};

// 端点信息（Publisher/Subscriber）
struct EndpointInfo {
    Type type;                    // PUBLISHER/SUBSCRIBER
    std::string topic_name;       // /chatter
    std::string type_name;        // std_msgs::msg::String
    std::string node_name;        // /talker
    std::string network_id;
    rmw_qos_profile_t qos;
};

// 序列化消息
struct SerializedMsg {
    std::vector<uint8_t> payload;
    std::string source_network_id;
    uint64_t sequence_number;
    uint64_t timestamp_ns;
};
```

---

## 📋 4 个实现阶段

### Phase 3.1: 基础框架（1-2 天）
**做什么**: 搭建所有核心模块的框架
**关键交付**:
- ✅ GraphCache（完整实现）
- ✅ SessionPool（重构）
- ✅ MessageSerializer（基础）
- ✅ 编译通过

**命令**:
```bash
gn gen build-ohos && ninja -C build-ohos
ninja -C build-ohos test_graph_cache  # 单元测试
```

---

### Phase 3.2: Discovery（2-3 天）
**做什么**: 实现节点和端点发现
**关键交付**:
- ✅ DiscoveryManager（节点注册、广播）
- ✅ Discovery 协议（JSON 编解码）
- ✅ 定时广播（5s 心跳）
- ✅ 过期清理（15s 超时）

**测试**:
```bash
# Device 1
./rmw_discovery_test --role=publisher --node-name=/node1

# Device 2 应看到 /node1 被发现
```

---

### Phase 3.3: Pub/Sub（3-4 天）
**做什么**: 实现消息发布和订阅
**关键交付**:
- ✅ PubSubManager（发布/订阅）
- ✅ Data 消息头和负载
- ✅ 消息队列管理
- ✅ 消息路由

**测试**:
```bash
# Device 1: Publisher
./rmw_pubsub_test --role=publisher --topic=/chatter --rate=1

# Device 2: Subscriber 应每秒收到 1 条消息
```

---

### Phase 3.4: 集成（2 天）
**做什么**: 运行 talker/listener 端到端测试
**关键交付**:
- ✅ RMW API 接口完整
- ✅ talker/listener 正常通信
- ✅ 性能达标（< 100ms 延迟）
- ✅ 文档完善

**测试**:
```bash
# Device 1: talker
export RMW_IMPLEMENTATION=rmw_dsoftbus_cpp
./talker

# Device 2: listener 应打印消息
./listener
```

---

## 📂 文件清单速查

### 新增文件（按优先级）
```
include/rmw_dsoftbus/
  ├── discovery_manager.h      (P0)
  ├── pubsub_manager.h         (P0)
  ├── graph_cache.h            (P0)
  ├── session_pool.h           (P0)
  ├── message_serializer.h     (P0)
  └── protocol.h               (P0)

src/
  ├── discovery_protocol.cpp   (P0)
  ├── pubsub_manager.cpp       (P0)
  ├── graph_cache.cpp          (P0)
  ├── message_serializer.cpp   (P1)
  └── message_queue.cpp        (P1)

test/
  ├── test_graph_cache.cpp     (P1)
  └── test_pubsub_e2e.cpp      (P1)

docs/
  ├── PHASE3_ARCHITECTURE.md   (本文档)
  └── PHASE3_QUICK_REFERENCE.md (本卡片)
```

### 修改文件（必需）
```
src/
  ├── session_manager.cpp      (重构为 SessionPool)
  ├── discovery_manager.cpp    (完全重构)
  ├── rmw_node.cpp             (调用 DiscoveryManager)
  ├── rmw_publisher.cpp        (调用 PubSubManager)
  ├── rmw_subscription.cpp     (调用 PubSubManager)
  └── BUILD.gn                 (添加新文件)
```

---

## 🔧 关键技术决策速查

### 为什么用 JSON 作 Discovery?
✅ **优点**: 可读性强，易调试，灵活扩展
❌ **缺点**: 比二进制占用更多带宽
🎯 **决策**: Phase 3 用 JSON（简单），Phase 4 可升级 PB

### 为什么用 SessionPool?
✅ **优点**: 减少系统 Session 数，复用连接，管理简单
❌ **缺点**: 需要在应用层路由
🎯 **决策**: 参考 DDS Virtual Channels，消息头包含 Topic

### 为什么 Phase 3 不做 Service?
✅ **原因**: Pub/Sub 优先级更高，Service 可复用 Pub/Sub
🎯 **规划**: Service 留给 Phase 4

---

## ⚡ 性能指标

| 指标 | 目标 | 如何验证 |
|------|------|---------|
| 节点发现时间 | < 5s | 测量启动到被发现的时间 |
| 消息延迟 | < 100ms | Ping-Pong 双向测试 |
| 消息吞吐量 | > 1000 msg/s | 高频率发布测试 |
| 内存占用 | < 50MB | 长期运行 + valgrind |

---

## 🚨 常见风险和应对

| 风险 | 应对 |
|------|------|
| **DSoftBus Session 不稳定** | 复用 Phase 2 已验证代码 + 心跳检测 |
| **序列化兼容性** | 使用 ROS2 官方 typesupport + 单元测试 |
| **Thread Safety** | 所有共享数据用互斥锁 + ThreadSanitizer |
| **大消息** | Phase 3 限制 < 64KB，Phase 4 分片 |

---

## 📅 时间规划

```
Week 1 (3-4 天)
  Mon-Tue: Phase 3.1 基础框架
  Wed-Thu: Phase 3.1 验收

Week 2 (2-3 天)
  Mon-Tue: Phase 3.2 Discovery 协议
  Wed-Thu: Phase 3.2 验收

Week 3 (3-4 天)
  Mon-Tue: Phase 3.3 Pub/Sub 实现
  Wed-Thu: Phase 3.3 验收

Week 4 (2 天)
  Mon: Phase 3.4 集成和测试
  Tue: 文档和交付

总耗时: 3-4 周
```

---

## 🎯 验收标准

### Phase 3 完成的定义（DoD）
- [ ] 所有头文件定义完整
- [ ] 所有 6 个核心模块实现完毕
- [ ] 单元测试通过率 > 95%
- [ ] 两设备 talker/listener 正常通信
- [ ] 消息延迟 < 100ms
- [ ] 无内存泄漏（valgrind）
- [ ] 文档完善（部署指南、API 文档、性能报告）
- [ ] 代码 review 通过

---

## 📞 快速开始

### 确认架构（Today）
1. 阅读 `docs/phases/phase3/PHASE3_ARCHITECTURE.md`（20 分钟）
2. 反馈修改意见（如有）
3. 确认开始实现

### 创建 Phase 3 分支（Tomorrow）
```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus
git checkout -b phase3-discovery-pubsub
mkdir -p include/rmw_dsoftbus src test
touch include/rmw_dsoftbus/{discovery_manager,pubsub_manager,graph_cache,session_pool,message_serializer,protocol}.h
touch src/{discovery_protocol,pubsub_manager,graph_cache,message_serializer,message_queue}.cpp
git add -A
git commit -m "[phase3] 初始化文件结构"
```

### 开始 Phase 3.1（Week 1）
```bash
# 1. 实现 GraphCache
# 2. 编写单元测试
# 3. 编译验证
ninja -C build-ohos && ninja -C build-ohos test_graph_cache
```

---

## 📚 相关文档导航

| 文档 | 内容 |
|------|------|
| `docs/phases/phase3/PHASE3_ARCHITECTURE.md` | 完整架构设计（详细） |
| `PHASE3_QUICK_REFERENCE.md` | 本卡片（快速查找） |
| `docs/phases/phase2/PHASE2_DEPLOYMENT_AND_TESTING_GUIDE.md` | Phase 2 部署参考 |
| `test/phase2_cross_device_session_test.cpp` | Session 实现参考 |

---

**🚀 准备好了吗？让我们开始 Phase 3！**

**下一步**:
1. ✅ 确认架构设计
2. → 创建 Phase 3 分支
3. → 开始 Phase 3.1 基础框架搭建

---

**设计日期**: 2026-01-14
**预计完成**: 2026-02-04 (3-4 周)
**最终成果**: talker/listener 跨设备通信 ✅
