# 手动跨设备测试指南

**日期**: 2026-01-16
**目的**: 验证 CreateSessionServer 和 OpenSession 在真实设备上的功能
**测试程序**: `phase3c_simple_pkg` (简化包名版本)

---

## 前提条件

### ✅ 已完成

1. Device 2 权限配置已更新并重启
2. CreateSessionServer 在 Device 2 上验证成功
3. 测试程序已部署到两台设备

### ⚠️ 已知问题

- Device 1: softbus Session Server 模块未初始化 (无法作为服务器)
- 但 Device 1 可能可以作为客户端使用

---

## 测试步骤

### 步骤 1: 在 Device 2 上启动服务器

```bash
# 通过 HDC 连接到 Device 2
hdc -t ec29004133314d38433031a5544f3c00 shell

# 进入测试目录
cd /data/local/tmp

# 运行服务器模式（会等待60秒）
./phase3c_simple_pkg server
```

**预期输出**:
```
[Test] CreateSessionServer returned: 0
[Test] OK Session server created
[Test] === SERVER MODE ===
[Test] Waiting for incoming connections...
[Test] Found 2 online device(s):
  [0] networkId: <some_long_id>
      deviceName: KaihongBoard-3588S
  [1] networkId: <another_long_id>
      deviceName: KaihongBoard-3588S
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
...
```

**记录**: 将看到的 networkId[0] 和 networkId[1] 复制下来

---

### 步骤 2: 获取 Device 2 的 networkId

有两个方法：

#### 方法 A: 从 Device 1 的发现列表

在**另一个终端**中：
```bash
hdc -t ec29004133314d38433031a522413c00 shell

cd /data/local/tmp

# 运行快速发现
timeout 10 ./phase3c_simple_pkg server
```

查看输出中的 networkId 列表。其中应该包含 Device 2 的 networkId。

#### 方法 B: 使用进程排除法

- Device 2 发现的 networkId[0] 和 [1] 中
- 其中一个是 Device 1
- 另一个是其他设备或者没有对应
- **猜测**: 选择其中一个尝试连接

---

### 步骤 3: 在 Device 1 上运行客户端

假设我们从步骤1中获得 Device 2 发现的 networkId[1] 是:
```
b8299263633ca4b91349dbd7c721a75a5a0b1f78eaea5789bc3911c5369a67aa
```

并且我们猜测这是 Device 1 的 networkId。

那么 Device 1 应该连接到 networkId[0]:
```
6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
```

在 Device 1 上运行：
```bash
hdc -t ec29004133314d38433031a522413c00 shell

cd /data/local/tmp

# 运行客户端模式
./phase3c_simple_pkg client 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
```

**预期输出**:
```
[Test] === CLIENT MODE ===
[Test] Opening session to peer...
[Test] OpenSession returned: <sessionId>
[Callback] OnSessionOpened: sessionId=<id>, result=0
[Test] ✅ Session opened successfully!
[Test] Sending test message...
[Test] SendBytes: 0
[Callback] OnBytesReceived: <response from server>
```

---

### 步骤 4: 观察服务器端的反应

在 Device 2 的服务器终端，应该看到：
```
[Callback] OnSessionOpened: sessionId=<id>, result=0
[Callback] Session details:
  - sessionId: <id>
  - side: SERVER (inbound)
  - peerNetworkId: b8299263633ca4b91349dbd7c721a75a5a0b1f78eaea5789bc3911c5369a67aa
  - peerSessionName: com.huawei.rmw.test
[Callback] Inbound session <id> accepted!
[Test] Status: connectCnt=1, outbound=-1, inbound=<id>

[Callback] SERVER bytes received: sessionId=<id>, len=<len>, data="<message>"
```

---

## 成功标准

### CreateSessionServer ✅
- [x] 返回 0 (SOFTBUS_OK)
- [x] 不阻塞
- [x] Session server 成功创建

### OpenSession ⏸️
- [ ] 返回有效 sessionId (>= 0)
- [ ] OnSessionOpened 回调被触发
- [ ] result == 0 (成功)

### Data Transfer ⏸️
- [ ] SendBytes 返回 0
- [ ] OnBytesReceived 回调被触发
- [ ] 数据内容正确

### Bidirectional ⏸️
- [ ] Server → Client 消息传输
- [ ] Client → Server 消息传输
- [ ] 双向 connectCnt 更新正确

---

## 故障排除

### Q: 客户端 OpenSession 返回 -1

**可能原因**:
- peerNetworkId 不正确（不是服务器的 networkId）
- 服务器未运行
- 网络问题

**解决**:
- 验证 networkId 是从服务器的发现列表中获取的
- 确认服务器进程在运行: `ps -ef | grep phase3c`
- 检查两台设备是否在同一网络

### Q: OnSessionOpened 未被触发

**可能原因**:
- 回调注册失败
- IPC 通信问题

**解决**:
- 检查 hilog: `hilog -x | grep OnSessionOpened`
- 验证回调函数签名正确

### Q: connectCnt 仍为 0

**可能原因**:
- Session ID 追踪问题（之前发现的 Issue #2）
- OnSessionOpened 返回了非零值（拒绝连接）

**解决**:
- 确保 OnSessionOpened 返回 0
- 添加日志确认回调被调用

---

## 快速参考

### 设备 ID
```
Device 1: ec29004133314d38433031a522413c00
Device 2: ec29004133314d38433031a5544f3c00
```

### 包名配置
```
PKG_NAME: com.huawei.rmw
SESSION_NAME: com.huawei.rmw.test
```

### 测试程序位置
```
Device 1: /data/local/tmp/phase3c_simple_pkg
Device 2: /data/local/tmp/phase3c_simple_pkg
```

### 日志位置
```
Device 2 Server: /data/srv.log (或 /data/server.log)
Device 1 Client: /data/cli.log (或 /data/client.log)
```

---

## 预期时间线

- **手动测试**: 15分钟
- **验证通信**: 10分钟
- **调试问题**: 30分钟（如有）
- **文档记录**: 15分钟

**总计**: 约1小时

---

**下一步**: 人工在设备上手动执行测试，避免自动化脚本的复杂性
