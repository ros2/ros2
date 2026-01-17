# Phase 依赖关系图谱

**日期**: 2026-01-05
**目的**: 可视化各 Phase 之间的依赖关系

---

## 依赖层次结构

```
Phase 1: Session-based 重构 (基础会话管理)
    ├── SessionManager (380 lines)
    ├── Native Token (权限)
    └── dsoftbus Session API 封装
         ↓
         ↓ 强依赖
         ↓
Phase 2: Graph Discovery (图发现与传播) ⭐ 关键基础设施
    ├── GraphCache (数据存储)
    │   ├── 节点注册
    │   ├── 端点注册
    │   ├── Service 注册 ← Phase 3 扩展
    │   └── 拓扑查询 API
    ├── IPC 协议 (跨进程)
    │   ├── librmw ↔ daemon
    │   ├── REGISTER/QUERY/NOTIFY
    │   └── Service 消息 ← Phase 3 扩展
    ├── DiscoveryManager (跨设备)
    │   ├── 7 种消息类型
    │   ├── Session 回调 ← 今日修复
    │   └── 自动传播 graph
    └── Daemon (权威模型)
         ↓
         ↓ 强依赖
         ↓
Phase 3: Service/Client RPC (RPC 增强) ← 当前 Phase
    ├── ServiceEnvelope (correlation)
    ├── ServiceTypeSupportSerializer
    ├── is_service_available ← 依赖 GraphCache + SessionManager
    ├── rmw_send/take_request/response
    └── request_id 生成器
         ↓
         ↓ 中等依赖 (需要 GraphCache 自动发现)
         ↓
Phase 4: 1:N 自动路由 (待开始)
    ├── GraphCache 订阅者列表
    ├── 动态 peer 发现
    └── 自动连接多个 Subscriber
```

---

## 依赖矩阵

| Phase | 依赖 Phase 1 | 依赖 Phase 2 | 依赖 Phase 3 | 可独立测试 |
|-------|------------|------------|------------|-----------|
| Phase 1 | - | ❌ | ❌ | ✅ 完全独立 |
| Phase 2 | ⭐⭐⭐ 强 | - | ❌ | ✅ 可独立 |
| Phase 3 | ⭐⭐ 中 | ⭐⭐⭐ 强 | - | ⚠️ 部分独立 |
| Phase 4 | ⭐⭐ 中 | ⭐⭐⭐ 强 | ⭐⭐ 中 | ❌ 依赖所有前置 |

**图例**:
- ⭐⭐⭐ 强依赖: 无此 Phase 完全无法工作
- ⭐⭐ 中等依赖: 核心功能受限，部分功能可用
- ⭐ 弱依赖: 仅优化或增强

---

## 功能可用性对比

### 场景 1: 仅 Phase 1 完成

| 功能 | 可用性 |
|------|--------|
| 单设备 Pub/Sub | ✅ 可用 |
| 跨设备 Pub/Sub | ✅ 可用 (需手动配置 PEER_ID) |
| Service/Client | ❌ 不可用 (无 GraphCache) |
| ros2 node list | ❌ 不可用 |
| ros2 topic list | ❌ 不可用 |

### 场景 2: Phase 1 + Phase 2 完成

| 功能 | 可用性 |
|------|--------|
| 单设备 Pub/Sub | ✅ 可用 |
| 跨设备 Pub/Sub | ✅ 可用 |
| Service/Client | ⚠️ 基础可用 (memcpy, 无 correlation) |
| ros2 node list | ✅ 可用 |
| ros2 topic list | ✅ 可用 |
| ros2 service list | ✅ 可用 |
| is_service_available | ⚠️ 部分可用 (仅 GraphCache 检查) |

### 场景 3: Phase 1 + Phase 2 + Phase 3 完成 ⭐

| 功能 | 可用性 |
|------|--------|
| 单设备 Pub/Sub | ✅ 完全可用 |
| 跨设备 Pub/Sub | ✅ 完全可用 |
| Service/Client | ✅ 完全可用 (CDR + correlation) |
| ros2 service call | ✅ 可用 |
| is_service_available | ✅ 完全可用 (双重检查) |
| 跨设备 Service call | ✅ 可用 (1:1, 需手动 PEER_ID) |

### 场景 4: Phase 1 + 2 + 3 + 4 完成 (目标)

| 功能 | 可用性 |
|------|--------|
| 所有上述功能 | ✅ 完全可用 |
| 1:N Pub/Sub | ✅ 自动路由 |
| 动态订阅者发现 | ✅ 自动 |
| 无需手动配置 PEER_ID | ✅ 自动 |

---

## 关键 API 依赖链

### is_service_available() 调用链

```
用户代码
    ↓
rmw_service_server_is_available()
    ↓
service_client_manager.cpp::is_service_available()
    ↓
┌──────────────────────────────────┐
│ GraphCache::count_services()      │ ← Phase 2.2 本地查询
│      ↓                            │
│ GraphCache::get_service_info()    │ ← Phase 3 扩展 API
│      ↓                            │
│ SessionManager::is_session_alive()│ ← Phase 3 新增
└──────────────────────────────────┘
    ↓
返回 true/false
```

**依赖组件**:
- Phase 2.2: GraphCache 数据存储
- Phase 2.5: IPC 协议传播远程 service 信息
- Phase 3: ServiceInfo.session_id 字段
- Phase 3: SessionManager::is_session_alive() 方法

### rmw_send_request() 调用链

```
用户代码
    ↓
rcl_send_request()
    ↓
rmw_send_request()
    ↓
┌──────────────────────────────────┐
│ service_typesupport_serializer    │ ← Phase 3
│      ↓                            │
│ ServiceEnvelope::create_request() │ ← Phase 3
│      ↓                            │
│ SessionManager::send_bytes()      │ ← Phase 1
│      ↓                            │
│ SendBytes(session_id, ...)        │ ← dsoftbus API
└──────────────────────────────────┘
```

**依赖组件**:
- Phase 1: SessionManager
- Phase 3: ServiceEnvelope (correlation)
- Phase 3: service_typesupport_serializer (CDR)

**Graph Discovery 的间接依赖**:
- is_service_available() 需要 GraphCache 确认 service 存在 (Phase 2)
- session_id 来自 GraphCache::get_service_info() (Phase 2 + Phase 3)

---

## 测试依赖分析

### Phase 3 测试需要的 Phase 2 功能

**本地测试 (单设备)**:
| Phase 3 测试 | Phase 2 需求 | 状态 |
|------------|-------------|------|
| ServiceEnvelope 序列化 | ❌ 不需要 | ✅ 可独立 |
| request_id 生成器 | ❌ 不需要 | ✅ 可独立 |
| Service 序列化 | ❌ 不需要 | ✅ 可独立 |
| GraphCache 本地注册 | ✅ 需要 | ✅ 可用 |
| is_session_alive | ✅ 需要 | ✅ 可用 |

**跨设备测试 (多设备)**:
| Phase 3 测试 | Phase 2 需求 | 状态 |
|------------|-------------|------|
| 远程 Service 发现 | ✅ DiscoveryManager | ⏸️ Session 不稳定 |
| is_service_available (远程) | ✅ IPC + Discovery | ⏸️ Session 不稳定 |
| 跨设备 Service call | ✅ 稳定 Session | ⏸️ Session 过早关闭 |

**阻断因素**: Phase 2 的 Session 过早关闭问题

---

## 优先级建议

### P0 (阻塞性) - 必须立即修复

**任务**: 修复 Phase 2 Session leader election
**原因**:
- Phase 3 跨设备测试完全阻断
- is_service_available (远程) 无法验证
- 影响 Phase 4 开发

**预计时间**: 2-3 小时
**影响范围**: Phase 2, Phase 3, Phase 4 所有跨设备功能

### P1 (重要) - Phase 2 完整验收

**任务**:
1. 验证 GraphCache 跨设备更新
2. 验证 IPC 协议完整性
3. 验证 Daemon 稳定性

**预计时间**: 2 小时

### P2 (增强) - Phase 3 完整验收

**任务**:
1. 跨设备 Service call 端到端测试
2. is_service_available 远程检查验证
3. 性能测试 (request_id 生成器)

**预计时间**: 2 小时

---

## 架构健康度评分

| 指标 | 评分 | 说明 |
|------|------|------|
| 层次清晰度 | ✅ 95/100 | Phase 分层明确，职责清晰 |
| 依赖合理性 | ✅ 90/100 | 单向依赖，无循环 |
| 测试隔离性 | ⚠️ 70/100 | Phase 3 本地测试可独立，跨设备测试依赖 Phase 2 |
| 向后兼容性 | ✅ 100/100 | Phase 3 扩展 Phase 2 数据结构，完全兼容 |
| 实现完整度 | ⚠️ 85/100 | 代码 100%，但 Phase 2 Session 稳定性待修复 |

**总体评分**: ⚠️ **87/100** (良好，有改进空间)

**关键风险**: Phase 2 Session 稳定性是 Phase 3 验收的阻塞因素

---

**分析人**: Claude Sonnet 4.5
**最后更新**: 2026-01-05 17:55 UTC
