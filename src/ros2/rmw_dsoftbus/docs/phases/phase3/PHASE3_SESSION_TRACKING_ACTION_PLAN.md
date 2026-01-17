# Phase 3 Session追踪问题 - 行动计划
**创建时间**: 2026-01-15
**优先级**: 高（阻塞Phase 3验收）
**相关PR**: Phase 3跨设备Session ID追踪修复

---

## 问题陈述

### 现象
Device 1 Server端测试程序成功创建Session Server，但无法接收任何incoming连接：
- ✅ Session Server创建成功
- ✅ 设备发现正常（发现Device 2/3）
- ✅ 权限配置正确
- ❌ **connectCnt=0** (没有接收到连接)
- ❌ **inbound=-1** (没有入站会话)
- ❌ **outbound=-1** (没有出站会话)

### 根本原因（初步分析）
根据Phase 2诊断报告，入站会话(inbound session)的Session ID追踪机制存在缺陷：
1. Client端OpenSession可能成功，但返回的sessionId与Server端记录的不一致
2. Server端的OnSessionOpened回调可能未被正确触发或记录
3. Session关联机制(关联outbound和inbound sessionId)失效

---

## 根本原因深入分析

### 场景对比分析

#### Phase 2成功场景 (Device 2 ↔ Device 3)
```
Device 2端:
- OpenSession(Device3_networkid, "test") → sessionId=X
- OnSessionOpened(sessionId=X) → 确认建立
- 发送消息成功

Device 3端:
- CreateSessionServer("test")
- OnSessionOpened(sessionId=Y) → 接收Device2的连接
- 收到消息 ✓
```

#### 当前失败场景 (Device 2 → Device 1)
```
Device 2端:
- OpenSession(Device1_networkid, "test") → sessionId=Z（假设成功）
- OnSessionOpened(sessionId=Z) → ？未知状态
- 消息发送状态：？

Device 1端:
- CreateSessionServer("test") → 成功
- OnSessionOpened(?) → NOT TRIGGERED (connectCnt仍为0)
- 消息接收：0条
```

### 根本缺陷推测

**缺陷1: Session ID映射缺失**
```
Client端的outbound sessionId (例如: sessionId=100)
     ↓
dsoftbus内部传输
     ↓
Server端的inbound sessionId应该是？
     ⚠️ 当前实现可能没有建立这个映射
```

**缺陷2: OnSessionOpened回调未触发或损坏**
```cpp
// Server期望这样被调用：
void OnSessionOpened(int sessionId, int result) {
    if (result == 0) {
        printf("Session %d opened\n", sessionId);  // 这行未执行
        recordSession(sessionId);
    }
}
```

**缺陷3: 入站会话追踪机制**
```cpp
// 当前实现可能缺少：
struct InboundSession {
    int sessionId;
    char peerId[MAX_NETWORKID_LEN];
    char sessionName[MAX_SESSION_NAME_LEN];
};
// 没有这样的数据结构来追踪入站会话
```

---

## 诊断路径 (按执行顺序)

### Phase 1: 收集Client端日志（第一步）

**目标**: 确认Client端OpenSession是否返回有效ID

**步骤**:
```bash
# 收集Device 2和Device 3上的Client日志
hdc -t ec29004133314d38433031a5544f3c00 shell 'cat /data/test/client*.log'
hdc -t DEVICE3_ID shell 'cat /data/test/client*.log'

# 查找关键信息：
# - OpenSession returned: [sessionId or error]
# - OnSessionOpened called with: [sessionId]
# - OnSessionClosed called with: [sessionId]
```

**预期结果**:
- 如果Client的OpenSession返回有效ID (>0)，则问题在Server接收端
- 如果Client的OpenSession返回-1或错误，则问题在Client端

### Phase 2: 验证networkId匹配（同步执行）

**目标**: 确认Client使用的device ID与Server发现的networkId一致

**步骤**:
```bash
# 获取Device 1的networkId (Server端)
hdc -t ec29004133314d38433031a522413c00 shell 'cat /data/test/server3.log | grep networkId'
# 预期输出：
# [0] networkId: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
# [1] networkId: ed35739d3925872e4510983ac67613f57b9dfabd274ffaf43919c7ec8a0f860c

# 获取Device 2/3的networkId
# 应该与Server发现的相匹配
hdc -t ec29004133314d38433031a5544f3c00 shell 'cat /data/test/client*.log | grep networkId'

# 关键检查：
# Client使用的peerId应该在Server发现的设备列表中
```

### Phase 3: 验证会话名称匹配（同步执行）

**目标**: 确认Client使用的sessionName与Server创建的完全相同

**步骤**:
```bash
# Server端的sessionName
hdc -t ec29004133314d38433031a522413c00 shell 'cat /data/test/server3.log | grep sessionName'
# 预期: com.huawei.ros2_rmw_dsoftbus.test

# Client端使用的sessionName
hdc -t ec29004133314d38433031a5544f3c00 shell 'cat /data/test/client*.log | grep OpenSession'

# 验证：两者必须完全相同（包括大小写和点号）
```

### Phase 4: 追踪OnSessionOpened回调（关键）

**目标**: 确认Server的OnSessionOpened回调是否被触发

**步骤**:
```cpp
// 修改rmw_dsoftbus/src/listener_test.cpp
// 或相应的Server代码

static void OnSessionOpened(int sessionId, int result) {
    printf("[TRACE] OnSessionOpened called:\n");
    printf("[TRACE]   sessionId: %d\n", sessionId);
    printf("[TRACE]   result: %d (0=success, <0=error)\n", result);
    fflush(stdout);

    if (result == SOFTBUS_OK) {
        printf("[TRACE] Connection established successfully\n");
        // 记录这个sessionId
        inbound_sessions[inbound_count++] = sessionId;
    } else {
        printf("[TRACE] Connection failed with error: %d\n", result);
    }
}
```

**执行**:
```bash
# 编译修改后的Server程序
cd /home/jiusi/M-DDS/rmw_dsoftbus
gn gen out/rk3588s
ninja -C out/rk3588s
```

**部署**:
```bash
mkdir -p /mnt/c/tmp/hdc_transfer
cp out/rk3588s/listener_test /mnt/c/tmp/hdc_transfer/
powershell.exe -Command "hdc -t $DEVICE1 file send 'C:\tmp\hdc_transfer\listener_test' '/data/local/tmp/listener_test'"
```

**运行和观察**:
```bash
# Server端
hdc -t ec29004133314d38433031a522413c00 shell '/data/local/tmp/listener_test'

# Client端(另一个终端)
hdc -t ec29004133314d38433031a5544f3c00 shell '/data/local/tmp/talker_test'

# 观察Server端的TRACE输出
# 如果看到 "OnSessionOpened called"，说明回调被触发
# 如果没看到，说明回调未被触发 → dsoftbus服务未将连接事件通知Server
```

### Phase 5: Session ID追踪验证（核心诊断）

**目标**: 确认入站会话的sessionId是否被正确记录

**修改测试程序**:
```cpp
// 在rmw_dsoftbus/src/listener_test.cpp中添加

struct SessionTracker {
    int sessionId;
    char peerId[256];
    int isInbound;
    long long openTime;
};

static SessionTracker g_sessions[MAX_SESSIONS];
static int g_sessionCount = 0;

static void OnSessionOpened(int sessionId, int result) {
    printf("[SESSION_TRACK] OnSessionOpened:\n");
    printf("[SESSION_TRACK]   sessionId=%d, result=%d\n", sessionId, result);

    if (result == 0 && g_sessionCount < MAX_SESSIONS) {
        g_sessions[g_sessionCount].sessionId = sessionId;
        g_sessions[g_sessionCount].isInbound = 1;  // 来自对端的连接
        g_sessions[g_sessionCount].openTime = GetCurrentTimeMs();
        g_sessionCount++;

        printf("[SESSION_TRACK] Total tracked sessions: %d\n", g_sessionCount);
    }
}

// 在主循环中定期打印
void PrintSessionStatus() {
    printf("\n[SESSION_STATUS] Current sessions:\n");
    for (int i = 0; i < g_sessionCount; i++) {
        printf("[SESSION_STATUS]   [%d] id=%d, inbound=%d\n",
               i, g_sessions[i].sessionId, g_sessions[i].isInbound);
    }
}
```

---

## 信息收集清单

### 必须收集的信息

| 信息项 | 来源 | 优先级 | 检查点 |
|--------|------|--------|--------|
| Client OpenSession返回值 | Device 2/3日志 | 🔴 高 | 返回有效ID > 0? |
| Server OnSessionOpened触发 | Device 1日志 | 🔴 高 | 回调被调用? |
| networkId匹配 | Server和Client日志 | 🔴 高 | ID一致? |
| sessionName匹配 | Server和Client日志 | 🔴 高 | 名称完全相同? |
| inbound sessionId | Device 1日志 | 🔴 高 | 有具体值? |
| outbound sessionId | Device 2/3日志 | 🟡 中 | 与inbound对应? |
| 消息发送尝试 | Device 2/3日志 | 🟡 中 | SendBytes被调用? |
| 消息接收 | Device 1日志 | 🟡 中 | OnBytesReceived被调用? |

---

## 实施步骤 (建议执行顺序)

### 今天 (2026-01-15)

1. **[10分钟]** 收集Client端日志
   ```bash
   # 执行诊断命令收集Device 2/3的日志
   # 查找: "OpenSession returned", "OnSessionOpened called"
   ```

2. **[10分钟]** 验证deviceId和sessionName
   ```bash
   # 对比Server和Client的日志
   # 确认ID和名称完全匹配
   ```

3. **[5分钟]** 编写诊断报告
   ```bash
   # 基于上述信息，确定问题所在
   # 是Client问题还是Server问题还是双向问题
   ```

### 明天 (如果需要深入调查)

4. **[30分钟]** 添加追踪日志
   ```bash
   # 修改rmw_dsoftbus源码添加详细的TRACE输出
   # 编译和部署新版本
   ```

5. **[20分钟]** 运行新版本测试
   ```bash
   # 同步运行Server和Client
   # 观察OnSessionOpened是否被触发
   # 记录具体的sessionId值
   ```

6. **[30分钟]** 分析结果
   ```bash
   # 根据TRACE输出，确定缺陷位置
   # 修复Session ID映射或回调机制
   ```

---

## 可能的修复方案

### 如果是Client端问题 (OpenSession失败)

**症状**: Client的OpenSession返回-1或错误码

**修复**:
```cpp
// 检查rmw_dsoftbus/src/publisher.cpp中的open_session实现
// 1. 验证peerId是否有效
// 2. 验证sessionName是否与权限配置匹配
// 3. 添加错误码日志
```

### 如果是Server端回调问题 (OnSessionOpened未触发)

**症状**: Server的OnSessionOpened回调从未被调用

**修复**:
```cpp
// 检查rmw_dsoftbus/src/listener.cpp中的OnSessionOpened注册
// 1. 回调函数地址是否正确传递给dsoftbus
// 2. 回调函数签名是否与期望一致
// 3. 是否需要手动轮询而不是回调
```

### 如果是Session ID映射问题 (ID不匹配)

**症状**: Client的outbound sessionId与Server的inbound sessionId不同

**修复**:
```cpp
// 在rmw_dsoftbus中添加Session ID映射表
struct SessionMapping {
    int outbound_sessionId;  // Client端的sessionId
    int inbound_sessionId;   // Server端的sessionId
    char peerId[256];
};

// 在OnSessionOpened中建立映射
// 在SendBytes/OnBytesReceived中使用正确的ID
```

---

## 测试验证计划

### 验证1: 单方向连接 (Client→Server)
```
Device 2/3 → Device 1
预期: OnSessionOpened被触发, connectCnt > 0
```

### 验证2: 双向通信
```
Device 1 Server创建OpenSession回连到Device 2
预期: 双向sessionId都被正确记录
```

### 验证3: 消息传输
```
建立连接后，通过SendBytes传输数据
预期: 两端都能接收到消息
```

### 验证4: 连接关闭
```
一端关闭连接，另一端接收OnSessionClosed
预期: connectCnt正确减少, sessionId被清理
```

---

## 文件清单

| 文件 | 位置 | 修改 | 优先级 |
|------|------|------|--------|
| `rmw_dsoftbus/src/listener_test.cpp` | Phase 3测试 | 添加TRACE | 高 |
| `rmw_dsoftbus/src/talker_test.cpp` | Phase 3测试 | 添加日志 | 高 |
| `rmw_dsoftbus/src/listener.cpp` | 核心实现 | 修复回调 | 高 |
| `rmw_dsoftbus/src/publisher.cpp` | 核心实现 | 验证ID | 中 |
| `PHASE3_SESSION_TRACKING_ACTION_PLAN.md` | 本文档 | 跟踪进度 | 中 |
| `DEVICE1_SERVER_DIAGNOSTIC_REPORT.md` | 诊断 | 参考 | 中 |

---

## 进度跟踪

### 状态记录

```
[2026-01-15 初始诊断]
- ✅ Server端基础组件正常
- ✅ 权限配置正确
- ❌ 连接无法建立
- 📋 待收集Client日志

[2026-01-15 待执行]
- [ ] 收集Client端日志
- [ ] 验证deviceId/sessionName匹配
- [ ] 确定问题根因
- [ ] 实施修复方案
```

---

## 参考链接

- **诊断报告**: `DEVICE1_SERVER_DIAGNOSTIC_REPORT.md`
- **Phase 2文档**: `rmw_dsoftbus/test/PHASE2_CROSS_DEVICE_TEST_RESULTS.md`
- **Phase 3设计**: `rmw_dsoftbus/docs/design/RMW_DSOFTBUS_DESIGN_REQUIREMENTS.md`
- **权限系统**: `OPENHARMONY_PERMISSION_SYSTEM_GUIDE.md`

---

## 问题跟踪ID

**Issue**: Phase 3 Session ID追踪缺陷
**Project**: rmw_dsoftbus
**Branch**: master (Phase 3)
**Est. Fix Time**: 4-6小时（包括诊断、修复、测试）

