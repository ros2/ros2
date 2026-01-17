---
doc_id: design_discovery_protocol
category: rmw_dsoftbus设计文档
title: RMW DSoftbus 发现协议 v3.1
description: rmw_dsoftbus 设备发现和 Graph 构建的完整协议规范，包括消息格式和状态机
priority: HIGH
last_updated: 2026-01-06
tags: [发现协议, Graph, 设备发现, 消息格式]
use_cases:
  - 理解 dsoftbus 设备发现的工作原理
  - 了解 Graph 缓存更新机制
  - 设计和实现发现协议相关功能
---

# RMW DSoftbus Discovery Protocol v3.1

**版本**: 3.1
**日期**: 2026-01-04
**状态**: 批准待实现

---

## 1. 概述

本协议定义了 rmw_dsoftbus 跨设备节点/Topic 发现机制，使 `ros2 node list`、`ros2 topic list` 等命令能显示远程设备上的节点和端点。

### 1.1 设计原则

- **点对点同步**: 禁止消息转发/洪泛
- **Local-Only 快照**: SNAPSHOT 仅包含本设备实体
- **两级 Liveliness**: Device (dsoftbus) + Node (timeout)
- **幂等去重**: seq + instance_id 防止重复处理
- **严格校验**: 长度、编码、上限全面验证

### 1.2 传输通道

使用专用 dsoftbus Session: `__ros2_discovery__`

---

## 2. 消息格式

### 2.1 Header 结构 (97 bytes, Little-Endian)

```
Offset  Size  Field                Description
------  ----  -------------------  -----------
0       2     magic                0x524F ("RO")
2       1     version              1
3       1     msg_type             MessageType enum
4       4     payload_len          Payload 长度 (bytes)
8       8     seq                  单调递增序列号 (per origin)
16      8     ts_ns                发送时间戳 (纳秒)
24      8     origin_instance_id   启动时随机生成，进程生命周期内不变
32      1     origin_len           origin_network_id 长度 [1,64]
33      64    origin_network_id    发送设备的 Network ID
```

**Total Header Size**: 97 bytes

### 2.2 Message Types

```cpp
enum class MessageType : uint8_t {
    QUERY           = 0x01,  // 请求全量快照
    SNAPSHOT        = 0x02,  // 全量快照响应 (local-only)
    NODE_ADD        = 0x03,  // 增量：节点上线
    NODE_REMOVE     = 0x04,  // 增量：节点下线
    ENDPOINT_ADD    = 0x05,  // 增量：端点创建
    ENDPOINT_REMOVE = 0x06,  // 增量：端点销毁
    HEARTBEAT       = 0x07   // 心跳 (刷新 liveliness)
};
```

### 2.3 Payload 格式

#### QUERY (0x01)
```
Payload: 空 (payload_len = 0)
```

#### SNAPSHOT (0x02)
```
Offset  Size  Field         Description
------  ----  -----------   -----------
0       2     node_count    节点数量
2       2     endpoint_count 端点数量
4       4     timestamp_sec  时间戳 (秒)
8       var   nodes[]       NodeEntry 数组
var     var   endpoints[]   EndpointEntry 数组
```

**NodeEntry**:
```
[0]     uint8_t   namespace_len
[1-n]   char[]    namespace
[n+1]   uint8_t   name_len
[n+2-m] char[]    name
[m+1]   uint8_t   enclave_len
[m+2-k] char[]    enclave
```

**EndpointEntry**:
```
[0]     uint8_t   type (PUBLISHER=0/SUBSCRIPTION=1/SERVICE=2/CLIENT=3)
[1]     uint8_t   topic_len
[2-n]   char[]    topic_name
[n+1]   uint8_t   type_name_len
[n+2-m] char[]    type_name
[m+1]   uint8_t[24] gid
[m+25]  uint8_t   node_name_len
[m+26-k] char[]   node_name
[k+1]   uint8_t   node_ns_len
[k+2-l] char[]    node_namespace
```

#### NODE_ADD (0x03) / NODE_REMOVE (0x04)
```
Payload: 单个 NodeEntry
```

#### ENDPOINT_ADD (0x05) / ENDPOINT_REMOVE (0x06)
```
Payload: 单个 EndpointEntry
```

#### HEARTBEAT (0x07)
```
Offset  Size  Field       Description
------  ----  ---------   -----------
0       2     node_count  节点数量
2       var   nodes[]     NodeKey 数组 (仅 namespace + name)
```

**NodeKey**:
```
[0]     uint8_t   namespace_len
[1-n]   char[]    namespace
[n+1]   uint8_t   name_len
[n+2-m] char[]    name
```

---

## 3. 协议规则

### 3.1 禁止转发 (Anti-Flooding)

```
收到消息时:
  IF origin_network_id == local_network_id:
      DROP (自己的回显)

  IF origin_network_id != sender_network_id:
      DROP (转发消息，禁止 merge)

  ELSE:
      正常处理
```

### 3.2 去重与幂等

**去重 Key**: `(origin_network_id, origin_instance_id, seq)`

```
last_seq_seen[(network_id, instance_id)] = last_processed_seq

收到消息时:
  IF seq <= last_seq_seen[(origin, instance)]:
      DROP (重复或过时)
  ELSE:
      处理并更新 last_seq_seen
```

### 3.3 重启处理

```
known_instance_ids[network_id] = last_known_instance_id

收到消息时:
  IF origin_instance_id != known_instance_ids[origin]:
      // 设备重启
      清除 last_seq_seen 中该 (origin, old_instance) 的记录
      更新 known_instance_ids[origin] = new_instance_id
      可选: 清除 GraphCache 中该 origin 的数据
```

### 3.4 SNAPSHOT 内容限制

```
SNAPSHOT 消息只能包含:
  - origin_network_id 设备的 本地 nodes
  - origin_network_id 设备的 本地 endpoints

禁止包含:
  - 该设备缓存的 remote nodes/endpoints
```

### 3.5 Remote Endpoint 复合键

```cpp
struct RemoteEndpointKey {
    std::string network_id;
    rmw_gid_t gid;
};

// remote_endpoints_[RemoteEndpointKey] = EndpointInfo
// 防止不同设备生成的 gid 碰撞
```

### 3.6 两级 Liveliness

**Device Liveliness**: dsoftbus `onNodeOffline` 回调
```
设备离线 → 删除该 network_id 下所有 nodes/endpoints
```

**Node Liveliness**: HEARTBEAT + Timeout
```
remote_node_liveness_[network_id][node_key] = last_seen_timestamp

超时检查 (每 5 秒):
  IF now - last_seen > 30秒:
      删除该 node 及其所有 endpoints
      触发 graph guard condition
```

### 3.7 NodeKey 规范化

```cpp
std::string make_node_key(const char* ns, const char* name) {
    // 规则:
    // - namespace 统一以 '/' 开头
    // - root namespace 统一为 "/"
    // - node name 不允许包含 '/'
    // - 输出格式: "{namespace}:{name}"

    std::string normalized_ns;
    if (ns == nullptr || ns[0] == '\0') {
        normalized_ns = "/";
    } else if (ns[0] != '/') {
        normalized_ns = std::string("/") + ns;
    } else {
        normalized_ns = ns;
    }

    return normalized_ns + ":" + (name ? name : "");
}
```

### 3.8 启动状态机

```
Session 建立后:
  1. 立即发送 QUERY
  2. 等待 SNAPSHOT

收到 SNAPSHOT:
  1. merge 到 GraphCache (remote-only)
  2. 刷新该 origin 所有 node 的 last_seen = now
  3. 触发 graph guard condition

周期心跳 (5 秒):
  1. 构建 HEARTBEAT (本地 node 列表)
  2. 发送给所有直连 peers

增量更新 (事件触发):
  1. 本地 node/endpoint 变化时
  2. 发送 NODE_ADD/REMOVE 或 ENDPOINT_ADD/REMOVE
```

---

## 4. 安全与校验

### 4.1 完整性校验

```cpp
bool validate(const void* data, size_t len) {
    // 1. 最小长度
    if (len < HEADER_SIZE) return false;  // HEADER_SIZE = 97

    // 2. Magic 校验
    if (magic != 0x524F) return false;

    // 3. Payload 上限
    if (payload_len > MAX_DISCOVERY_PAYLOAD) return false;  // 256KB

    // 4. 严格长度匹配
    if (len != HEADER_SIZE + payload_len) return false;

    // 5. origin_len 范围
    if (origin_len == 0 || origin_len > 64) return false;

    return true;
}
```

### 4.2 常量定义

```cpp
static constexpr size_t HEADER_SIZE = 97;
static constexpr size_t MAX_DISCOVERY_PAYLOAD = 256 * 1024;  // 256KB
static constexpr uint64_t NODE_TIMEOUT_NS = 30 * 1000000000ULL;  // 30秒
static constexpr uint64_t HEARTBEAT_INTERVAL_S = 5;  // 5秒
```

### 4.3 端序

**所有多字节整数采用 Little-Endian 编码**

包括: magic, payload_len, seq, ts_ns, origin_instance_id, node_count, endpoint_count, timestamp_sec

---

## 5. 文件修改清单

| 文件 | 操作 | 内容 |
|------|------|------|
| `include/rmw_dsoftbus/discovery_manager.h` | 新增 | DiscoveryManager 类定义 |
| `src/discovery_manager.cpp` | 新增 | 协议实现 (~600 行) |
| `include/rmw_dsoftbus/graph_cache.h` | 修改 | 新增 snapshot_local_only, RemoteEndpointKey, make_node_key |
| `src/graph_cache.cpp` | 修改 | 实现 local/remote 分离存储 |
| `src/rmw_init.cpp` | 修改 | 添加 DiscoveryManager 初始化 |
| `src/dsoftbus_stubs.cpp` | 修改 | 添加 GetAllNodeDeviceInfo stub |
| `CMakeLists.txt` | 修改 | 添加 discovery_manager.cpp |

---

## 6. 预计代码量

| 组件 | 行数 |
|------|------|
| discovery_manager.h | ~120 |
| discovery_manager.cpp | ~600 |
| graph_cache.h 修改 | ~50 |
| graph_cache.cpp 修改 | ~150 |
| rmw_init.cpp 修改 | ~20 |
| dsoftbus_stubs.cpp 修改 | ~40 |
| **总计** | **~980 行** |

---

## 7. 版本历史

| 版本 | 日期 | 变更 |
|------|------|------|
| v1.0 | 2026-01-04 | 初始设计 |
| v2.0 | 2026-01-04 | 修正: 禁止洪泛, local-only snapshot, 两级 liveliness |
| v3.0 | 2026-01-04 | 补充: seq 去重, 复合键, heartbeat, origin 编码, payload 上限 |
| v3.1 | 2026-01-04 | 补充: origin_instance_id, 完整性校验, NodeKey 规范, 启动状态机 |

---

## 8. 审批状态

- [x] 禁止转发 (origin != sender → DROP)
- [x] 去重 (network_id, instance_id, seq)
- [x] 重启处理 (instance_id 变化 → 清空 seq)
- [x] 复合键 (network_id + gid)
- [x] HEARTBEAT 心跳
- [x] Origin 编码 (length-prefixed)
- [x] Payload 上限 (256KB)
- [x] 端序声明 (Little-Endian)
- [x] 长度校验 (严格相等)
- [x] NodeKey 规范 (make_node_key)
- [x] 启动状态机 (QUERY → SNAPSHOT → merge)

**批准状态**: ✅ 待最终确认
