# OpenSession Callback 手动验证教程

**目标**: 彻底验证 OpenSession callback 功能，确认 SendBytes 和 OnBytesReceived 正常工作
**时间**: 约 10 分钟
**要求**: 两个终端窗口

---

## 准备工作

### 设备信息

**Device 1 (Server)**:
- Device ID: `ec29004133314d38433031a5544f3c00`
- 角色: Session Server，等待连接
- 期望 Network ID: 需要从 Device 1 本地获取

**Device 2 (Client)**:
- Device ID: `ec29004133314d38433031a522413c00`
- 角色: 主动连接到 Device 1

### 测试程序

**位置**: 两台设备的 `/data/test/phase3b_session_test`

**功能**: 完整的 Session API 测试，包括：
- CreateSessionServer
- OpenSession
- SendBytes
- OnBytesReceived 回调

---

## 第一步：获取 Device 1 的正确 Network ID

### 1.1 打开第一个终端

连接到 Device 1:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell
```

### 1.2 获取本地 Network ID

在 Device 1 上执行:
```bash
cd /data/test
LD_LIBRARY_PATH=. ./phase3b_session_test list
```

**期待输出**:
```
[Test] Found 2 online device(s):
  [0] networkId: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
      deviceName: KaihongBoard-3588S
  [1] networkId: e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212
      deviceName: KaihongBoard-3588S
```

**重要**:
- 其中一个 networkId 是 Device 2 的
- 另一个 networkId 是**其他设备**的（可能是 Device 3）
- **我们需要从 Device 2 查询来确定 Device 1 的正确 Network ID**

### 1.3 正确方法：从 Device 2 查询 Device 1 的 Network ID

打开第二个终端，连接到 Device 2:
```bash
hdc -t ec29004133314d38433031a522413c00 shell
```

在 Device 2 上执行:
```bash
cd /data/test
LD_LIBRARY_PATH=. ./phase3b_session_test list
```

**输出中的 networkId**:
- 其中一个是 Device 1 的 ← **这个才是我们需要的！**
- 另一个是其他设备的

**记录 Device 1 的 Network ID** (复制下来，稍后使用)

---

## 第二步：启动 Server (Device 1)

### 2.1 在第一个终端 (Device 1)

如果之前已经进入 shell，执行:
```bash
cd /data/test
LD_LIBRARY_PATH=. ./phase3b_session_test server
```

如果是新终端:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

### 2.2 期待输出

```
==============================================================
  Phase 3B Session API Test
==============================================================

[Token] === Injecting Access Token ===
[Token] OK GetAccessTokenId returned: 0x2803f800
[Token] OK SetSelfTokenID succeeded

[DSoftBus] === Loading libsoftbus_client.z.so ===
[DSoftBus] OK Loaded from: /system/lib64/platformsdk/libsoftbus_client.z.so
[DSoftBus] OK CreateSessionServer: 0x7faadc0168
[DSoftBus] OK OpenSession: 0x7faadc0704
[DSoftBus] OK SendBytes: 0x7faadbf80c

[Test] === Creating Session Server ===
[Test] pkgName: com.huawei.ros2_rmw_dsoftbus
[Test] sessionName: com.huawei.ros2_rmw_dsoftbus.test
[Test] CreateSessionServer returned: 0          ← ✅ 必须看到这行！
[Test] OK Session server created

[SERVER] Waiting for incoming connections...
[SERVER] Press Ctrl+C to exit

[Test] === Listing Online Devices ===
[Test] Found 2 online device(s):
  ...

[Test] Status: connectCnt=0, outbound=-1, inbound=-1
```

### 2.3 确认 Server 就绪

**检查点**:
- ✅ `CreateSessionServer returned: 0`
- ✅ 显示 "Waiting for incoming connections"
- ✅ 每 5 秒显示一次 Status

**注意**: Server 会在 30 秒后超时退出，所以**必须在 30 秒内完成 Client 测试**

---

## 第三步：运行 Client (Device 2)

### 3.1 在第二个终端 (Device 2)

⏰ **重要**: Server 启动后，您有 30 秒时间运行此步骤

如果已在 Device 2 shell 中:
```bash
cd /data/test
LD_LIBRARY_PATH=. ./phase3b_session_test client <DEVICE1_NETWORK_ID>
```

替换 `<DEVICE1_NETWORK_ID>` 为步骤 1.3 记录的 Network ID

如果是新终端:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <DEVICE1_NETWORK_ID>'
```

### 3.2 期待输出

```
[Test] === Creating Session Server ===
[Test] CreateSessionServer returned: 0
[Test] OK Session server created

[CLIENT] === Listing Online Devices ===
[Test] Found 2 online device(s):
  ...

[Test] === Opening Session to Peer ===
[Test] peerNetworkId: 6ea1cecbc95eb2d290af...
[Test] OpenSession returned: 1              ← ✅ 返回 sessionId

[Test] Waiting for session to connect (timeout=10 sec)...
[Callback] OnSessionOpened: sessionId=1, result=???  ← 关键！
```

---

## 第四步：观察和判断

### 4.1 成功的标志 ✅

**在 Client 终端看到**:
```
[Callback] OnSessionOpened: sessionId=1, result=0   ← 0 = 成功！
[Test] OK Session connected successfully

[Test] === Sending Test Messages ===
[Send] Test message #1
[RESULT] SendBytes returned: 0   ← 0 = 成功！
[Send] Test message #2
[RESULT] SendBytes returned: 0
...
```

**在 Server 终端看到**:
```
[Callback] OnSessionOpened: sessionId=X, result=0   ← Server 收到连接
[SERVER] Inbound session established

[Callback] OnBytesReceived: sessionId=X, len=Y
[DATA] Test message #1   ← Server 收到消息！
[Callback] OnBytesReceived: sessionId=X, len=Y
[DATA] Test message #2
...
```

**判断**: ✅ **OpenSession callback 完全成功！可以继续开发！**

### 4.2 部分成功的标志 ⚠️

**在 Client 终端看到**:
```
[Callback] OnSessionOpened: sessionId=1, result=-426115004  ← 仍然失败
[FAIL] Session did not connect in time
```

**在 Server 终端看到**:
```
[Test] Status: connectCnt=0, outbound=-1, inbound=-1  ← 没有收到连接
```

**可能原因**:
1. Network ID 不正确
2. Server 刚好在重启间隙
3. sessionName 查找失败（dsoftbus 内部问题）

**下一步**:
- 检查使用的 Network ID 是否正确
- 尝试多次（Server 会自动重启）
- 或调查 sessionName 匹配逻辑

### 4.3 失败的标志 ❌

**Client 终端**:
```
[Test] CreateSessionServer returned: -426442743  ← 权限错误（不应该出现）
```

**或**:
```
[Test] OpenSession returned: -1  ← API 失败
```

**原因**: 配置问题，需要检查权限 JSON

---

## 第五步：抓取完整 hilog（可选）

### 5.1 在测试过程中

**另开一个终端抓取 Device 1 hilog**:
```bash
powershell.exe -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'hilog -x' > C:\tmp\device1_live_hilog.txt"
```

**另开一个终端抓取 Device 2 hilog**:
```bash
powershell.exe -Command "hdc -t ec29004133314d38433031a522413c00 shell 'hilog -x' > C:\tmp\device2_live_hilog.txt"
```

### 5.2 测试后保存到本地

```bash
cp /mnt/c/tmp/device1_live_hilog.txt /home/jiusi/M-DDS/tests/logs/
cp /mnt/c/tmp/device2_live_hilog.txt /home/jiusi/M-DDS/tests/logs/
```

---

## 第六步：分析结果

### 6.1 如果 OnSessionOpened 成功 (result=0) ✅

**验证点**:
- [x] Server: CreateSessionServer 返回 0
- [x] Client: OpenSession 返回有效 sessionId
- [x] Client: OnSessionOpened result=0
- [x] Client: SendBytes 返回 0
- [x] Server: OnBytesReceived 收到消息

**结论**: ✅ **Session API 完全可用，可以开始 Phase 3 开发**

### 6.2 如果 OnSessionOpened 失败 (result=-426115004) ⚠️

**检查清单**:

1. **Server 是否真的在运行？**
   ```bash
   # 在第三个终端检查
   hdc -t ec29004133314d38433031a5544f3c00 shell 'ps | grep phase3b'
   ```
   应该看到 PID

2. **Network ID 是否正确？**
   - 确认从 Device 2 查询到的 Device 1 network ID
   - 不是从 Device 1 查询到的其他设备 ID

3. **时序是否正确？**
   - Server 启动后 30 秒内运行 Client
   - 或使用 Background Agent 的自动重启 Server

4. **hilog 分析**:
   查找关键信息:
   ```bash
   grep "TransCreateSessionServer" device1_live_hilog.txt
   grep "TransOpenSession" device2_live_hilog.txt
   grep "426115004" device2_live_hilog.txt
   ```

---

## 快速测试脚本（自动化版本）

创建文件 `quick_manual_test.sh`:

```bash
#!/bin/bash

DEVICE1="ec29004133314d38433031a5544f3c00"
DEVICE2="ec29004133314d38433031a522413c00"

echo "=========================================="
echo "Step 1: 获取 Device 1 的 Network ID"
echo "=========================================="
echo "请在 Device 2 上查询:"
echo ""
hdc -t $DEVICE2 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
echo ""
echo "请记录 Device 1 的 networkId，然后按 Enter 继续..."
read

echo ""
echo "请输入 Device 1 的 Network ID:"
read DEVICE1_NETWORK_ID

echo ""
echo "=========================================="
echo "Step 2: 启动 Server (Device 1)"
echo "=========================================="
echo "正在启动 Server..."
echo "请观察下面的输出，确保看到:"
echo "  [Test] CreateSessionServer returned: 0"
echo "  [SERVER] Waiting for incoming connections..."
echo ""
echo "Server 将在 30 秒后超时，请在看到 'Waiting for connections' 后"
echo "立即按 Ctrl+C，然后在另一个终端运行 Client"
echo ""
echo "按 Enter 启动 Server..."
read

# 这里需要手动 Ctrl+C 来在另一个终端运行 Client
hdc -t $DEVICE1 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

---

## 详细步骤（推荐方式）

### 准备阶段

1. 打开**两个终端窗口**，并排放置
2. 准备好 Device 1 和 Device 2 的 ID

### 执行阶段

#### 终端 1 - 持续观察模式

**命令**:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

**观察点**:
```
等待看到:
  ✅ [Test] CreateSessionServer returned: 0
  ✅ [SERVER] Waiting for incoming connections...
  ✅ [Test] Status: connectCnt=0 (开始倒计时)

然后保持观察，等待 Client 连接
```

#### 终端 2 - 等待就绪后执行

**步骤**:

1. **首先获取 Device 1 的 Network ID**:
   ```bash
   hdc -t ec29004133314d38433031a522413c00 shell \
     'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
   ```
   复制其中一个 networkId（这是 Device 1 的）

2. **等待终端 1 显示 "Waiting for connections"**

3. **立即运行 Client** (必须在 30 秒内):
   ```bash
   hdc -t ec29004133314d38433031a522413c00 shell \
     'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <DEVICE1_NETWORK_ID>'
   ```

   替换 `<DEVICE1_NETWORK_ID>` 为刚才复制的 networkId

---

## 观察和记录

### 在 Client 终端（终端 2）观察

**关键输出**:
```
[Test] CreateSessionServer returned: 0   ← 必须成功
[Test] OpenSession returned: 1           ← 必须 > 0
[Test] Waiting for session to connect...

[Callback] OnSessionOpened: sessionId=1, result=?   ← 核心！
```

**判断标准**:

**成功** ✅:
```
[Callback] OnSessionOpened: sessionId=1, result=0   ← 0 = 成功！
[OK] Session connected successfully

[SEND #1] Test message #1 from Device 2
[RESULT] SendBytes returned: 0   ← 0 = 成功！
[SEND #2] Test message #2 from Device 2
[RESULT] SendBytes returned: 0
...
```

**失败** ❌:
```
[Callback] OnSessionOpened: sessionId=1, result=-426115004
[FAIL] Session did not connect in time
```

### 在 Server 终端（终端 1）观察

**成功的标志** ✅:
```
[Callback] OnSessionOpened: sessionId=2, result=0   ← Server 收到连接！
[SERVER] Inbound session established: sessionId=2

[Callback] OnBytesReceived #1:
  sessionId: 2
  length: 28 bytes
  data: Test message #1 from Device 2   ← 收到消息！

[Callback] OnBytesReceived #2:
  sessionId: 2
  length: 28 bytes
  data: Test message #2 from Device 2

[SERVER] Sending reply: Server received message #1
[SERVER] SendBytes returned: 0   ← Server 也能发送！
```

**失败的标志** ❌:
```
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
(持续显示，没有变化)
...
[Test] Timeout reached, exiting   ← 30 秒后超时
```

---

## 常见问题和解决

### Q1: Server 很快就超时退出了

**原因**: 30 秒超时机制

**解决**:
1. 重新运行 Server
2. 更快地运行 Client（< 20 秒内）
3. 或使用 Background Agent 的自动重启 Server

### Q2: Client 显示 "OpenSession returned: -1"

**原因**: Network ID 错误或 Server 未运行

**解决**:
1. 确认使用正确的 Network ID (从 Device 2 查询得到的)
2. 确认 Server 正在运行 (ps 命令检查)

### Q3: OnSessionOpened 一直返回 -426115004

**可能原因**:
1. Network ID 不正确
2. sessionName 不匹配
3. Server 在 Client 连接时刚好重启

**调试方法**:
```bash
# 在 Server 端检查
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'hilog -x | grep -E "TransCreateSessionServer|sessionName" | tail -10'

# 在 Client 端检查
hdc -t ec29004133314d38433031a522413c00 shell \
  'hilog -x | grep -E "TransOpenSession|OpenSession|426115004" | tail -10'
```

### Q4: 想要更多调试时间

**方案 1**: 使用 Background Agent 的自动重启 Server
- Server 每 60 秒重启
- 可以多次尝试 Client 测试

**方案 2**: 修改测试程序源码
- 移除 30 秒超时限制
- 需要找到源码并重新编译

---

## 成功验证的标准

### 必须确认的点 ✓

- [x] Server: CreateSessionServer 返回 0
- [x] Client: CreateSessionServer 返回 0
- [x] Client: OpenSession 返回有效 sessionId (> 0)
- [x] Client: OnSessionOpened callback result=0 (成功)
- [x] Client: SendBytes 返回 0
- [x] Server: OnSessionOpened callback 收到连接
- [x] Server: OnBytesReceived 收到消息
- [x] 消息内容正确

### 如果全部通过 ✅

**结论**: Session API 完全可用，包括:
- CreateSessionServer ✅
- OpenSession ✅
- SendBytes ✅
- OnBytesReceived ✅

**下一步**: 开始 Phase 3 rmw_dsoftbus 实现

### 如果 OnSessionOpened 仍然失败 ⚠️

**可以做的**:
1. 分析完整的 hilog (已保存到 logs/)
2. 调试 sessionName 查找逻辑
3. 或先用 rmw_mock 继续 ROS2 开发，Phase 4 再深入调试

---

## 测试记录模板

### 测试日期: ________

**Device 1 Network ID**: ______________________________

**测试结果**:

Server 端:
- [ ] CreateSessionServer: 返回 ___
- [ ] OnSessionOpened: sessionId=___, result=___
- [ ] OnBytesReceived: 收到 ___ 条消息

Client 端:
- [ ] CreateSessionServer: 返回 ___
- [ ] OpenSession: 返回 ___
- [ ] OnSessionOpened: sessionId=___, result=___
- [ ] SendBytes #1: 返回 ___
- [ ] SendBytes #2: 返回 ___

**结论**: ___________________________________________

---

## 备用测试方法：使用 Background Agent 的自动重启 Server

### 优点
- Server 自动重启，持续可用
- 可以多次尝试 Client 测试
- 不需要严格的时序控制

### 步骤

1. **确认 Background Agent Server 正在运行**:
   ```bash
   hdc -t ec29004133314d38433031a5544f3c00 shell 'ps | grep phase3b'
   ```
   应该看到进程

2. **直接运行 Client** (无需启动 Server):
   ```bash
   hdc -t ec29004133314d38433031a522413c00 shell \
     'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <NETWORK_ID>'
   ```

3. **如果仍失败，等待 Server 重启后再试** (每 60 秒一个周期)

---

## 快速参考卡

### Device IDs
```
Device 1: ec29004133314d38433031a5544f3c00
Device 2: ec29004133314d38433031a522413c00
```

### 终端 1 命令
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

### 终端 2 命令
```bash
# 1. 获取 Network ID
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'

# 2. 运行 Client (< 30 秒内)
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <NETWORK_ID>'
```

### 成功标志
```
Client: [Callback] OnSessionOpened: result=0
Client: [RESULT] SendBytes returned: 0
Server: [Callback] OnBytesReceived: data=Test message #1
```

---

**教程创建**: 2026-01-16
**目标**: 手动验证 OpenSession callback 完整功能
**时间**: 约 10 分钟
**关键**: 两个终端，30 秒时间窗口
