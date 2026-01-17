# OpenSession Callback 逐步测试指南

**必读**: 本教程将帮助您手动验证 OpenSession callback 是否正常工作

---

## 前置条件检查

### 1. 确认测试程序已部署

```bash
hdc -t ec29004133314d38433031a5544f3c00 shell 'ls -la /data/test/phase3b_session_test'
hdc -t ec29004133314d38433031a522413c00 shell 'ls -la /data/test/phase3b_session_test'
```

应该看到文件存在且可执行。

### 2. 确认权限配置已部署

```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cat /system/etc/communication/softbus/softbus_trans_permission.json | grep PKG_NAME'
```

应该看到包含空字符串的 PKG_NAME: `"PKG_NAME": ""`

---

## 测试步骤

### 步骤 1: 获取 Device 1 的 Network ID (关键!)

⚠️ **重要**: 必须从 Device 2 查询 Device 1 的 Network ID

**在任意终端执行**:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
```

**输出示例**:
```
[Test] Found 2 online device(s):
  [0] networkId: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
      deviceName: KaihongBoard-3588S
  [1] networkId: e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212
      deviceName: KaihongBoard-3588S
```

**操作**:
- 复制其中**第一个** networkId (很可能是 Device 1)
- 粘贴到记事本备用

**Network ID**: `6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3`

---

### 步骤 2: 打开两个终端窗口

**终端布局建议**:
```
┌─────────────────────┬─────────────────────┐
│                     │                     │
│   终端 1 (Server)   │   终端 2 (Client)   │
│   Device 1          │   Device 2          │
│                     │                     │
└─────────────────────┴─────────────────────┘
```

---

### 步骤 3: 在终端 1 启动 Server

**终端 1 执行**:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

**等待输出**:
```
[Token] === Injecting Access Token ===
[Token] OK GetAccessTokenId returned: 0x2803f800
...
[Test] === Creating Session Server ===
[Test] pkgName: com.huawei.ros2_rmw_dsoftbus
[Test] sessionName: com.huawei.ros2_rmw_dsoftbus.test
[Test] CreateSessionServer returned: 0    ← ✅ 必须是 0！
[Test] OK Session server created

[SERVER] Waiting for incoming connections...
[SERVER] Press Ctrl+C to exit
```

**确认**:
- ✅ 看到 `CreateSessionServer returned: 0`
- ✅ 看到 `Waiting for incoming connections`
- ✅ 终端保持运行状态

**⏰ 计时开始**: 从这时起，您有 **30 秒**时间运行 Client！

---

### 步骤 4: 在终端 2 运行 Client (< 30 秒内!)

**终端 2 执行**:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3'
```

⚠️ **替换 Network ID** 为步骤 1 复制的值！

**Client 输出**:
```
[Test] === Creating Session Server ===
[Test] CreateSessionServer returned: 0
[Test] OK Session server created

[CLIENT] === Listing Online Devices ===
[Test] Found 2 online device(s):
  ...

[Test] === Opening Session to Peer ===
[Test] peerNetworkId: 6ea1cecbc95eb2d290af...
[Test] OpenSession returned: 1    ← ✅ 必须 > 0
[Test] OK Session opened (ID=1), waiting for callback...

[Test] Waiting for session to connect (timeout=10 sec)...
```

---

### 步骤 5: 同时观察两个终端

#### 场景 A: 成功 ✅

**Client 终端 (终端 2) 显示**:
```
[Callback] OnSessionOpened: sessionId=1, result=0   ← 0 = 成功！
[OK] Session connected successfully

[Test] === Sending Test Messages ===
[SEND #1] Test message #1 from Device 2
[RESULT] SendBytes returned: 0   ← 0 = 成功！
[OK] Message sent (total: 1)

[SEND #2] Test message #2 from Device 2
[RESULT] SendBytes returned: 0
[OK] Message sent (total: 2)
...
```

**Server 终端 (终端 1) 显示**:
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
...
```

**✅ 测试成功！继续步骤 6**

#### 场景 B: 失败 ❌

**Client 终端显示**:
```
[Callback] OnSessionOpened: sessionId=1, result=-426115004  ← 失败！
[Callback] Session 1 failed to open: -426115004
[FAIL] Session did not connect in time
```

**Server 终端显示**:
```
[Test] Status: connectCnt=0, outbound=-1, inbound=-1   ← 没有连接
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
...
```

**❌ 测试失败，跳转到故障排查步骤**

---

## 步骤 6: 如果成功，记录结果

### 6.1 截图或复制输出

**Client 终端关键信息**:
- [ ] OnSessionOpened result=0
- [ ] SendBytes returned: 0 (每条消息)
- [ ] 消息发送成功

**Server 终端关键信息**:
- [ ] OnSessionOpened sessionId=X, result=0
- [ ] OnBytesReceived 收到每条消息
- [ ] 消息内容正确

### 6.2 保存到文件

**Client 输出**:
```bash
# 重新运行并保存
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <ID>' \
  > /home/jiusi/M-DDS/tests/logs/manual_test_client_success.txt 2>&1
```

**Server 输出**: 复制终端内容到文件

---

## 故障排查

### 如果仍然看到 -426115004

#### 排查 1: 确认 Network ID

**问题**: 使用了错误的 Network ID

**验证方法**:
```bash
# 在 Device 1 上获取本地 Network ID
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./get_network_id'
```

如果没有这个程序，从 Device 2 的 list 输出中确认。

#### 排查 2: 检查 Server 是否真的在运行

**在第三个终端检查**:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell 'ps | grep phase3b'
```

应该看到进程。如果没有，说明 Server 已退出（超时），需要重启。

#### 排查 3: 检查时序

**Server 运行时间**:
```
Server 启动后显示 6 次 Status (每 5 秒一次)
6 × 5 = 30 秒后超时
```

**Client 运行时机**:
- ✅ 在前 20 秒内运行 Client
- ❌ 超过 25 秒运行可能来不及

#### 排查 4: 查看实时 hilog

**Device 1 (Server)**:
```bash
# 在第三个终端实时监控
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'hilog -x | grep -E "TransCreate|TransOpen|Session|426115004"'
```

**Device 2 (Client)**:
```bash
# 在第四个终端实时监控
hdc -t ec29004133314d38433031a522413c00 shell \
  'hilog -x | grep -E "TransOpen|Session|426115004"'
```

---

## 多次尝试策略

### 方法 1: 利用 Background Agent 自动重启

**当前状态**: Background Agent (acb02fb) 正在让 Server 自动重启

**步骤**:
```bash
# 1. 确认 Server 正在运行
hdc -t ec29004133314d38433031a5544f3c00 shell 'ps | grep phase3b'

# 2. 如果有进程，立即运行 Client
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <ID>'

# 3. 如果失败，等待 60 秒后 Server 重启，再次尝试
```

### 方法 2: 快速重复测试

```bash
#!/bin/bash
# 快速重复脚本

DEVICE1="ec29004133314d38433031a5544f3c00"
DEVICE2="ec29004133314d38433031a522413c00"
NETWORK_ID="<填入正确的ID>"

for i in {1..3}; do
    echo "=== 尝试 $i/3 ==="

    # 启动 Server
    hdc -t $DEVICE1 shell \
      'pkill -f phase3b; cd /data/test && (LD_LIBRARY_PATH=. ./phase3b_session_test server &)' &

    # 等待 8 秒让 Server 初始化
    sleep 8

    # 运行 Client
    hdc -t $DEVICE2 shell \
      "cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client $NETWORK_ID"

    # 检查结果
    if grep -q "result=0" last_output.txt; then
        echo "✅ 成功！"
        break
    fi

    # 等待下次尝试
    sleep 5
done
```

---

## 预期的成功标志

### Client 端必须看到

```
✅ [Test] CreateSessionServer returned: 0
✅ [Test] OpenSession returned: 1 (或其他正数)
✅ [Callback] OnSessionOpened: sessionId=1, result=0    ← 最关键！
✅ [RESULT] SendBytes returned: 0
✅ [OK] Message sent
```

### Server 端必须看到

```
✅ [Test] CreateSessionServer returned: 0
✅ [Callback] OnSessionOpened: sessionId=X, result=0    ← 收到连接
✅ [Callback] OnBytesReceived: data=Test message #1    ← 收到数据
```

---

## 如果成功，后续测试

### 验证双向通信

**Server 端也可以发送**:
- Server 在收到消息后会自动回复
- Client 应该收到 "Server received your message" 的回复
- 查看 Client 的 OnBytesReceived 回调

### 验证多条消息

测试程序会发送多条消息，观察:
- 每条消息的 SendBytes 返回值
- Server 是否收到所有消息
- 消息顺序是否正确

---

## 完整测试命令（复制粘贴）

### 终端 1 (Device 1 Server)

```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

### 终端 2 (Device 2 Client)

等待终端 1 显示 "Waiting for connections" 后，立即执行:

```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3'
```

---

## 测试清单

测试执行前:
- [ ] 两个终端已打开
- [ ] Device 1 Network ID 已确认
- [ ] 测试程序已部署
- [ ] 权限配置已部署

测试执行中:
- [ ] 终端 1: Server 成功启动
- [ ] 终端 1: 显示 "Waiting for connections"
- [ ] 终端 2: 在 30 秒内运行 Client
- [ ] 终端 2: OpenSession 返回正数
- [ ] 同时观察两个终端的输出

测试结果记录:
- [ ] OnSessionOpened callback result = ___
- [ ] SendBytes 返回值 = ___
- [ ] OnBytesReceived 是否触发: ___
- [ ] 消息内容是否正确: ___

---

## 结果判定

### ✅ 完全成功

**条件**:
- OnSessionOpened result=0 (两端都是)
- SendBytes 返回 0
- OnBytesReceived 收到正确消息

**结论**: Session API 完全可用，可以开始 Phase 3 开发

### ⚠️ 部分成功

**条件**:
- CreateSessionServer 成功
- OpenSession 返回 sessionId
- 但 OnSessionOpened result=-426115004

**结论**: 需要深入调试，或先用其他方案继续开发

### ❌ 完全失败

**条件**:
- CreateSessionServer 失败
- 或 OpenSession 返回负数

**结论**: 检查配置和权限

---

**教程完成**: 2026-01-16
**预计时间**: 5-10 分钟
**关键**: 30 秒时间窗口内完成 Client 测试
