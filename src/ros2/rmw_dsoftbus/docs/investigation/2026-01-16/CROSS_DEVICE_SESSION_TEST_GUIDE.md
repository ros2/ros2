# 跨设备 Session 消息发送测试指南

**日期**: 2026-01-16
**目标**: 验证标准 Session API 的跨设备消息传输功能

---

## 测试准备

### 已验证的功能 ✅

| API | Device 1 | Device 2 | 状态 |
|-----|----------|----------|------|
| CreateSessionServer | ✅ 成功 | ✅ 成功 | 返回 0 |
| OpenSession (API) | ✅ 成功 | ✅ 成功 | 返回有效 sessionId |
| GetAllNodeDeviceInfo | ✅ 2 台设备 | ✅ 2 台设备 | 发现成功 |

### 待验证的功能 ⏸️

| API | 预期行为 | 待验证 |
|-----|---------|--------|
| SendBytes | 发送数据到对端 | 是否成功传输 |
| OnBytesReceived | 接收回调触发 | 是否收到数据 |
| 跨设备通信 | 双向消息传递 | 完整流程 |

---

## 测试方案

### 方案 A: 使用现有测试程序 (推荐)

**程序**: `phase3b_session_test` (已部署到两台设备)

**PKG_NAME**: `com.huawei.ros2_rmw_dsoftbus`
**SESSION_NAME**: `com.huawei.ros2_rmw_dsoftbus.test`

**步骤**:

1. **Device 1 (Server端)**:
   ```bash
   hdc -t ec29004133314d38433031a5544f3c00 shell \
     'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
   ```
   期待输出:
   ```
   [Test] CreateSessionServer returned: 0
   [Test] OK Session server created
   [SERVER] Waiting for incoming connections...
   ```

2. **获取 Device 1 的 Network ID**:
   从 Device 2 查询:
   ```bash
   hdc -t ec29004133314d38433031a522413c00 shell \
     'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
   ```
   输出中的其中一个 networkId 就是 Device 1

3. **Device 2 (Client端)**:
   ```bash
   hdc -t ec29004133314d38433031a522413c00 shell \
     'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <NETWORK_ID>'
   ```
   替换 <NETWORK_ID> 为 Device 1 的 network ID

4. **观察结果**:
   - Client: 查看 OpenSession 返回值和 SendBytes 返回值
   - Server: 查看 OnSessionOpened 和 OnBytesReceived 回调
   - 分析 hilog 确认底层传输

---

### 方案 B: 使用新的快速测试程序

**程序**: `quick_session_test` (已编译和部署)

**PKG_NAME**: `com.huawei.ros2_rmw_dsoftbus`
**SESSION_NAME**: `com.huawei.ros2_rmw_dsoftbus.complete_test`

**步骤**:

1. **Device 1 启动 Server**:
   ```bash
   # 在后台运行，输出到文件
   hdc -t ec29004133314d38433031a5544f3c00 shell \
     'cd /data/test && ./quick_session_test server > server_log.txt 2>&1 &'

   # 等待 2 秒
   sleep 2

   # 检查启动状态
   hdc -t ec29004133314d38433031a5544f3c00 shell \
     'head -25 /data/test/server_log.txt'
   ```

2. **Device 2 运行 Client**:
   ```bash
   hdc -t ec29004133314d38433031a522413c00 shell \
     'cd /data/test && ./quick_session_test client <NETWORK_ID>'
   ```

3. **检查 Server 接收结果**:
   ```bash
   hdc -t ec29004133314d38433031a5544f3c00 shell \
     'cat /data/test/server_log.txt | grep -A 2 OnBytesReceived'
   ```

---

## 已知问题和解决方案

### 问题 1: OnSessionOpened 回调失败

**症状**:
```
[Test] OpenSession returned: 1
[Callback] OnSessionOpened: result=-426115004
Error: [KH_TRANS] not init
```

**原因**: KH_TRANS 传输层未初始化

**影响**:
- ❌ OnSessionOpened 回调收到失败状态
- ✅ OpenSession API 返回有效 sessionId
- ❓ SendBytes 可能仍然工作 (需验证)

**测试重点**:
即使回调失败，SendBytes 可能仍然可以传输数据到底层 Socket。

### 问题 2: 程序执行权限

**症状**: `/bin/sh: ./program: Permission denied`

**解决**:
```bash
hdc shell 'chmod 777 /data/test/quick_session_test'
```

### 问题 3: 动态链接器找不到文件

**症状**: `/bin/sh: ./program: No such file or directory`

**原因**: ELF 文件使用了 `/lib/ld-linux-aarch64.so.1` 但设备上可能在不同路径

**解决方案**:
1. 使用设备上已有的测试程序 (phase3b_session_test)
2. 或使用系统 linker: `/system/bin/linker64 /data/test/program`

---

## 预期测试结果

### 场景 1: 回调正常工作 (理想情况)

**Client 端**:
```
[Test] OpenSession returned: 1
[Callback] OnSessionOpened: sessionId=1, result=0  ← 成功
[SEND] Test message #1
[RESULT] SendBytes returned: 0  ← 成功
```

**Server 端**:
```
[CALLBACK] OnSessionOpened: sessionId=2, result=0  ← 收到连接
[CALLBACK] OnBytesReceived: sessionId=2, len=22
[DATA] Test message #1  ← 收到消息
```

### 场景 2: 回调失败但数据传输成功 (KH_TRANS 未初始化)

**Client 端**:
```
[Test] OpenSession returned: 1  ← API 成功
[Callback] OnSessionOpened: result=-426115004  ← 回调失败
[SEND] Test message #1
[RESULT] SendBytes returned: 0  ← 可能成功
```

**Server 端**:
```
[CALLBACK] OnSessionOpened: result=-426115004  ← 回调失败
[CALLBACK] OnBytesReceived: sessionId=?, len=22  ← 可能收到
[DATA] Test message #1  ← 数据可能到达
```

### 场景 3: Session 完全失败

**Client 端**:
```
[Test] OpenSession returned: -1  ← API 失败
```

**原因分析**:
- 权限配置错误
- 对端 Session Server 未启动
- Network ID 错误

---

## 测试检查清单

### Server 端 (Device 1)

- [ ] CreateSessionServer 返回 0
- [ ] 程序保持运行，等待连接
- [ ] OnSessionOpened 回调被触发
- [ ] OnBytesReceived 回调被触发
- [ ] 收到的数据内容正确

### Client 端 (Device 2)

- [ ] 发现了 Device 1 (GetAllNodeDeviceInfo)
- [ ] CreateSessionServer 返回 0 (本地也需要)
- [ ] OpenSession 返回有效 sessionId (> 0)
- [ ] SendBytes 返回 0 (成功)
- [ ] 没有连接超时或错误

### hilog 分析

- [ ] 没有 PERMISSION_DENIED 错误
- [ ] 看到 TransOpenSession 日志
- [ ] 看到 TCP/Auth 连接建立
- [ ] 没有 KH_TRANS 之外的错误

---

## 手动测试步骤 (推荐)

由于程序同步控制的复杂性，建议手动执行测试：

### 步骤 1: 启动 Server

在 Device 1 的终端运行:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell
cd /data/test
LD_LIBRARY_PATH=. ./phase3b_session_test server
```

保持此终端打开。

### 步骤 2: 获取 Network ID

在新终端查询:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
```

记录其中一个 networkId (可能是 Device 1 的)。

### 步骤 3: 运行 Client

在 Device 2 终端运行:
```bash
hdc -t ec29004133314d38433031a522413c00 shell
cd /data/test
LD_LIBRARY_PATH=. ./phase3b_session_test client <NETWORK_ID>
```

### 步骤 4: 观察输出

**观察 Server 终端**:
- 是否显示 OnSessionOpened?
- 是否显示 OnBytesReceived?
- 收到的消息内容是什么?

**观察 Client 终端**:
- OpenSession 返回值是多少?
- SendBytes 返回值是多少?
- 是否报告发送成功?

---

## 测试程序对比

### phase3b_session_test

**优点**:
- 完整的 Session 测试流程
- 支持 server/client/list 模式
- 详细的日志输出
- 已验证 CreateSessionServer 成功

**缺点**:
- OnSessionOpened 回调失败 (KH_TRANS 问题)
- 需要手动输入 network ID

### quick_session_test

**优点**:
- 简化的测试流程
- 自动发送 5 条测试消息
- 清晰的成功/失败判断

**缺点**:
- 新程序，可能有动态链接问题
- 同样会遇到 KH_TRANS 回调问题

---

## 关键测试点

### 1. CreateSessionServer ✅

**已验证**: 两台设备都返回 0

### 2. OpenSession API ✅

**已验证**: 返回有效 sessionId

### 3. OnSessionOpened 回调 ❌

**已知问题**: KH_TRANS 未初始化导致回调失败

**不影响**: 底层 Session 可能已建立

### 4. SendBytes → OnBytesReceived ❓

**待验证**: 关键测试点！

**验证方法**:
- Client 调用 SendBytes
- 检查返回值
- Server 端查看 OnBytesReceived 是否触发
- 分析 hilog 查看底层传输日志

---

## 预期发现

### 最可能的结果 (基于已有测试)

**CreateSessionServer**: ✅ 成功
**OpenSession API**: ✅ 返回 sessionId
**OnSessionOpened 回调**: ❌ 失败 (-426115004)
**SendBytes**: ❓ 返回值未知
**OnBytesReceived**: ❓ 是否触发未知

### 需要确认的问题

1. **SendBytes 是否真的发送了数据?**
   - 返回 0 表示成功
   - 但数据是否到达对端?

2. **Server 端是否收到数据?**
   - OnBytesReceived 是否被调用?
   - 还是因为 KH_TRANS 问题数据被丢弃?

3. **底层 Socket 是否建立?**
   - hilog 是否显示 TCP 连接?
   - 是否有数据传输日志?

---

## 下一步行动建议

### 立即执行

1. **手动测试** (最可靠):
   - 两个终端分别连接两台设备
   - 同时观察 server 和 client 输出
   - 确认消息是否真的传输

2. **hilog 分析**:
   - 监控 TransSdk 模块日志
   - 查找 SendBytes / OnBytesReceived 调用
   - 确认底层传输状态

### 可选方案

如果 SendBytes 因 KH_TRANS 问题无法工作:

1. **研究 KH_TRANS 初始化**:
   - 查找 KhSessionManagerInit 调用
   - 了解初始化流程
   - 尝试手动初始化

2. **使用替代方案**:
   - 考虑使用 Socket API 直接通信
   - 或等待 Phase 4 系统集成

---

## 测试脚本示例

### 完整测试流程 (需要两个终端)

**终端 1 (Device 1 Server)**:
```bash
DEVICE1="ec29004133314d38433031a5544f3c00"

# 启动 server
hdc -t $DEVICE1 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'

# 观察输出，等待 client 连接
```

**终端 2 (Device 2 Client)**:
```bash
DEVICE2="ec29004133314d38433031a522413c00"

# 获取 Device 1 的 network ID
hdc -t $DEVICE2 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'

# 记录 network ID，然后运行 client
DEVICE1_NET_ID="<从 list 输出复制>"
hdc -t $DEVICE2 shell \
  "cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client $DEVICE1_NET_ID"

# 观察消息发送和回调结果
```

### 自动化测试脚本 (单终端)

```bash
#!/bin/bash

DEVICE1="ec29004133314d38433031a5544f3c00"
DEVICE2="ec29004133314d38433031a522413c00"

echo "=== Step 1: Start Server on Device 1 ==="
hdc -t $DEVICE1 shell 'pkill -f phase3b_session_test'
hdc -t $DEVICE1 shell \
  'cd /data/test && (LD_LIBRARY_PATH=. ./phase3b_session_test server > /data/test/server.log 2>&1 &)'

sleep 5
echo "Server started"

echo ""
echo "=== Step 2: Check Server Status ==="
hdc -t $DEVICE1 shell 'head -30 /data/test/server.log'

echo ""
echo "=== Step 3: Get Network ID from Device 2 ==="
hdc -t $DEVICE2 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list' | \
  grep networkId | head -1

echo ""
echo "=== Step 4: Run Client on Device 2 ==="
echo "Please run manually:"
echo "  hdc -t $DEVICE2 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <NETWORK_ID>'"

echo ""
echo "=== Step 5: Check Server Log for Received Messages ==="
echo "After client completes, run:"
echo "  hdc -t $DEVICE1 shell 'cat /data/test/server.log'"
```

---

## 测试判断标准

### 完全成功 ✅

- CreateSessionServer 返回 0
- OpenSession 返回有效 sessionId
- OnSessionOpened 回调 result=0
- SendBytes 返回 0
- OnBytesReceived 收到正确数据

### 部分成功 ⚠️

- CreateSessionServer 返回 0 ✅
- OpenSession 返回有效 sessionId ✅
- OnSessionOpened 回调失败 (-426115004) ❌
- SendBytes 返回 0 或非0 ❓
- OnBytesReceived 可能收到或收不到 ❓

### 完全失败 ❌

- CreateSessionServer 失败
- OpenSession 返回负数
- SendBytes 返回错误

---

## 当前测试状态

### 已完成的测试 ✅

1. **CreateSessionServer**: 两台设备都成功
2. **设备发现**: GetAllNodeDeviceInfo 返回 2 台设备
3. **OpenSession API**: 返回有效 sessionId

### 待完成的测试 ⏸️

1. **SendBytes 实际传输**: 数据是否到达对端?
2. **OnBytesReceived**: Server 是否收到回调?
3. **完整的端到端通信**: 消息从 Client 到 Server 的完整流程

### 测试建议

**最可靠的验证方法**:
1. 使用两个独立的 SSH/HDC 连接
2. 同时观察两端输出
3. 手动控制测试流程
4. 通过 hilog 分析底层行为

**自动化测试的挑战**:
- 进程同步困难
- 回调可能不触发
- 需要多终端协作

---

## 后续计划

### 如果 SendBytes 工作

继续 Phase 3 开发:
- 实现 rmw_publish 使用 SendBytes
- 实现 rmw_subscription 使用 OnBytesReceived
- 测试 ROS2 talker/listener

### 如果 SendBytes 不工作

需要调查:
- KH_TRANS 初始化方法
- 或考虑 Phase 4 系统集成
- 或使用 Socket API 替代方案

---

**文档创建**: 2026-01-16
**状态**: 测试指南完成，等待手动执行测试
**测试程序**: phase3b_session_test, quick_session_test 已部署
