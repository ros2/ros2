# OpenSession Callback 快速测试清单

⏱️ **总时间**: 5 分钟
🎯 **目标**: 验证 OnSessionOpened callback result=0

---

## 准备（1 分钟）

### 打开两个终端窗口

**终端 1**: 准备运行 Server (Device 1)
**终端 2**: 准备运行 Client (Device 2)

---

## 执行（4 分钟）

### 1️⃣ 获取 Network ID (30 秒)

**任意终端执行**:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
```

**复制第一个 networkId**: `6ea1cecbc95eb2d290af...`

---

### 2️⃣ 启动 Server (10 秒)

**终端 1 执行**:
```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

**等待看到**:
```
[Test] CreateSessionServer returned: 0   ← ✅
[SERVER] Waiting for incoming connections...   ← ✅
```

⏰ **计时开始**: 30 秒倒计时

---

### 3️⃣ 运行 Client (20 秒内!)

**终端 2 执行**:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <粘贴Network_ID>'
```

---

### 4️⃣ 观察结果 (实时)

#### 看 Client 终端 (终端 2):

**成功** ✅:
```
[Callback] OnSessionOpened: sessionId=1, result=0
[RESULT] SendBytes returned: 0
```

**失败** ❌:
```
[Callback] OnSessionOpened: sessionId=1, result=-426115004
```

#### 看 Server 终端 (终端 1):

**成功** ✅:
```
[Callback] OnSessionOpened: sessionId=X, result=0
[Callback] OnBytesReceived: data=Test message #1
```

**失败** ❌:
```
[Test] Status: connectCnt=0   (没有变化)
```

---

## 结果

### ✅ 如果看到 result=0

**恭喜！Session API 完全可用！**

继续验证:
- [x] SendBytes 返回 0
- [x] OnBytesReceived 收到消息
- [x] 消息内容正确

**下一步**: 开始 Phase 3 rmw_dsoftbus 实现

---

### ❌ 如果仍然 result=-426115004

**可能原因**:
1. Network ID 不正确
2. Server 超时（超过 30 秒）
3. sessionName 查找失败

**下一步**:
- 检查 Network ID
- 更快运行 Client (< 15 秒)
- 或查看详细教程排查

---

## 命令速查

```bash
# Device IDs
DEVICE1="ec29004133314d38433031a5544f3c00"
DEVICE2="ec29004133314d38433031a522413c00"

# 1. List devices
hdc -t $DEVICE2 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'

# 2. Server (终端 1)
hdc -t $DEVICE1 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'

# 3. Client (终端 2, < 30秒内)
hdc -t $DEVICE2 shell 'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <NETWORK_ID>'
```

---

**快速开始**: 按顺序执行 1️⃣ 2️⃣ 3️⃣ 4️⃣
**关键**: 30 秒时间窗口
**成功标志**: OnSessionOpened result=0
