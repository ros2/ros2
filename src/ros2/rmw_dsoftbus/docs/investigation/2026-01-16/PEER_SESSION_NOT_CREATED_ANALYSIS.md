# SOFTBUS_TRANS_PEER_SESSION_NOT_CREATED 问题分析和解决

**日期**: 2026-01-16
**错误码**: -426115004
**错误名**: SOFTBUS_TRANS_PEER_SESSION_NOT_CREATED

---

## 问题分析

### 错误码定义

**来源**: `foundation/communication/dsoftbus/interfaces/kits/common/softbus_error_code.h`

**计算**:
```
SOFTBUS_TRANS_ERR_BASE = -426115071
SOFTBUS_TRANS_PEER_SESSION_NOT_CREATED = SOFTBUS_TRANS_ERR_BASE + 67
                                        = -426115071 + 67
                                        = -426115004
```

### 错误含义

**对端没有注册或找不到对应的 Session Server**

触发场景（从源码分析）:
1. `GetPkgNameBySessionName` 失败
2. `GetUidAndPidBySessionName` 失败
3. 对端进程未执行 CreateSessionServer
4. 对端进程已退出导致注册丢失
5. sessionName 拼写不一致

**代码位置**:
- 代理通道握手: `core/transmission/trans_channel/proxy/src/softbus_proxychannel_manager.c`
- UDP 握手: `core/transmission/trans_channel/udp_negotiation/src/trans_udp_negotiation.c`
- TCP Direct 握手: `core/transmission/trans_channel/tcp_direct/src/trans_tcp_direct_message.c`

---

## 在我们测试中的具体表现

### 测试场景

**Device 1 (Server)**:
```
CreateSessionServer("com.huawei.ros2_rmw_dsoftbus",
                   "com.huawei.ros2_rmw_dsoftbus.test", &listener)
→ 返回 0 (成功)
→ 等待连接...
→ [问题] 30 秒超时后自动退出
→ RemoveSessionServer() 被调用
→ Session Server 注册被移除
```

**Device 2 (Client)**:
```
OpenSession("com.huawei.ros2_rmw_dsoftbus.test",
           "com.huawei.ros2_rmw_dsoftbus.test",
           networkId, "", &attr)
→ API 返回 sessionId=1
→ [问题] 此时 Device 1 的 Server 已经退出
→ 回调收到 -426115004 (PEER_SESSION_NOT_CREATED)
```

### 时序问题

```
时间轴:
  0s   Device 1: CreateSessionServer (成功)
  0s   Device 1: Server 开始等待...
  ...
  30s  Device 1: 超时，退出
  30s  Device 1: RemoveSessionServer
  ...
  35s  Device 2: OpenSession (尝试连接)
  35s  Device 2: 错误！Server 已经不存在了
  35s  回调: -426115004 (PEER_SESSION_NOT_CREATED)
```

**根本原因**: **Server 进程超时退出导致 Session Server 注册丢失**

---

## 解决方案

### 方案 1: 持久化 Server (推荐) ✅

**修改**: 让 Server 无限等待，不要超时退出

**实现**: `tests/persistent_session_test.c`

关键修改:
```c
// 旧代码 (有超时):
for (int i = 0; i < MAX_WAIT_COUNT; i++) {
    sleep(1);
    if (g_connected) break;
}
if (!g_connected) {
    // 超时退出
    RemoveSessionServer(...);
    return;
}

// 新代码 (无超时):
while (g_running) {  // 直到 Ctrl+C
    sleep(5);
    printf("Server running...\n");
}
```

**优点**:
- ✅ Server 持续运行，Client 随时可连接
- ✅ 符合实际应用场景（ROS2 节点持续运行）
- ✅ 容易测试和调试

### 方案 2: 快速同步测试

**流程**:
1. 启动 Server (后台运行)
2. 立即检查 Server 是否成功创建
3. 在 Server 超时前运行 Client
4. 快速完成测试

**Shell 脚本示例**:
```bash
# 启动 Server
hdc shell 'cd /data/test && (./phase3b_session_test server &)' &
sleep 3

# 立即运行 Client
hdc shell 'cd /data/test && ./phase3b_session_test client <NETWORK_ID>'
```

**缺点**:
- ⚠️ 时序敏感，容易失败
- ⚠️ 难以调试

### 方案 3: 手动双终端测试 (最可靠) ⭐

**流程**:
1. 终端 A: 启动 Server，保持运行
2. 终端 B: 运行 Client
3. 同时观察两端输出

**优点**:
- ✅ 可以同时观察两端
- ✅ 容易判断成功/失败
- ✅ 实时看到回调触发

---

## 解决步骤

### 步骤 1: 使用持久化 Server

**程序**: `persistent_session_test` (已创建并部署)

**特点**:
- Server 无限等待（无超时）
- 清晰的日志输出
- 自动回复收到的消息

### 步骤 2: 测试流程

**终端 1 (启动 Server)**:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && chmod +x persistent_session_test && \
   LD_LIBRARY_PATH=. ./persistent_session_test server'
```

保持此终端打开，观察:
- CreateSessionServer 是否返回 0
- Server 是否显示 "PERSISTENT MODE - NO TIMEOUT"
- 是否持续显示 "Running..."

**终端 2 (运行 Client)**:
```bash
# 先获取 Device 1 的 network ID
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./persistent_session_test list'

# 然后运行 Client
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./persistent_session_test client <NETWORK_ID>'
```

观察:
- OpenSession 返回值
- SendBytes 返回值
- 是否收到错误 -426115004

**终端 1 (观察 Server)**:
- 是否显示 OnSessionOpened 回调?
- 是否显示 OnBytesReceived 回调?
- 接收到的消息内容是否正确?

### 步骤 3: 验证成功标志

**完全成功** ✅:
```
Server:
  [CALLBACK] OnSessionOpened: sessionId=2, result=0
  [CALLBACK] OnBytesReceived: Test message #1

Client:
  [RESULT] OpenSession returned: 1
  [RESULT] SendBytes returned: 0
```

**API 成功但回调失败** ⚠️:
```
Server:
  [CALLBACK] OnSessionOpened: result=-426115004  (但 Server 仍在运行)
  [CALLBACK] OnBytesReceived: ...  (可能仍收到数据)

Client:
  [RESULT] OpenSession returned: 1  (sessionId 有效)
  [RESULT] SendBytes returned: 0  (发送成功)
```

**Server 已退出** ❌:
```
Client:
  [RESULT] SendBytes returned: -426115004
  [HINT] Error -426115004 means peer session not created
```

---

## 检查清单

### Server 端检查 ✓

- [ ] CreateSessionServer 返回 0
- [ ] Server 进程保持运行（无超时退出）
- [ ] 日志显示 "Waiting for connections"
- [ ] 没有 "Removing session server" 日志

### Client 端检查 ✓

- [ ] 使用正确的 peer network ID
- [ ] sessionName 与 Server 完全一致
- [ ] OpenSession 返回正数（sessionId）
- [ ] SendBytes 不返回 -426115004

### sessionName 一致性检查 ✓

Server:
```c
CreateSessionServer("com.huawei.ros2_rmw_dsoftbus",
                   "com.huawei.ros2_rmw_dsoftbus.complete_test", ...)
```

Client:
```c
OpenSession("com.huawei.ros2_rmw_dsoftbus.complete_test",  // mySessionName
           "com.huawei.ros2_rmw_dsoftbus.complete_test",  // peerSessionName
           networkId, ...)
```

确保两端 sessionName **完全一致**（大小写、拼写）

---

## hilog 诊断

### 正常情况的日志

**Server 端**:
```
ClientAddSessionServer# sessionName=*plete_test, pkgName=com.huawei.ros2
TransOpenSession# trans server opensession
StartVerifySession# ok
```

**Client 端**:
```
TransOpenSession# trans client opensession
OpenAuthSession# session opened successfully
OnSessionOpened# sessionId=X, result=0
```

### 错误情况的日志 (PEER_SESSION_NOT_CREATED)

**Server 端**:
```
(无日志 - Server 已退出)
```

**Client 端**:
```
TransTdcOnChannelOpenFailed# peer session not created
OnSessionOpened# result=-426115004
```

### hilog 查询命令

```bash
# Server 端
hdc shell 'hilog -x | grep -E "ClientAddSessionServer|CreateSessionServer"'

# Client 端
hdc shell 'hilog -x | grep -E "OpenSession|PEER_SESSION|426115004"'

# 查看完整传输日志
hdc shell 'hilog -x | grep -E "TransSdk|TransCtrl"'
```

---

## 总结

### 根本问题

❌ **Server 超时退出** → Session Server 注册被移除 → Client 连接时找不到对端 → 错误 -426115004

### 解决方案

✅ **使用持久化 Server**:
- 无超时机制
- 持续运行直到手动停止
- Client 可以随时连接

### 测试工具

已部署:
- `persistent_session_test` - 持久化 Server 测试程序
- 两台设备都已部署
- 可以立即开始测试

### 下一步

**立即执行**:
1. 启动 persistent_session_test server (保持运行)
2. 运行 persistent_session_test client
3. 观察是否还有 -426115004 错误
4. 验证 SendBytes → OnBytesReceived 流程

---

**问题根源**: Server 超时退出
**解决方案**: 持久化 Server
**测试就绪**: 工具已部署，可以立即测试
