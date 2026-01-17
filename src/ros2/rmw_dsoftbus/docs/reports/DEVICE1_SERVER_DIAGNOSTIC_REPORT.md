# 设备1 Server端诊断报告
**生成时间**: 2026-01-15
**诊断范围**: 设备1 (Device 1) 服务端日志、dsoftbus服务、网络配置、权限系统

---

## 执行摘要

设备1 Server端状态**正常**，所有基础组件运行良好：
- ✅ dsoftbus服务进程运行正常 (softbus_server PID=1067)
- ✅ 权限配置完整且正确
- ✅ 网络连接正常（IP: 192.168.11.192）
- ✅ Session Server创建成功
- ⚠️ **关键问题**: Server未接收到任何incoming连接（connectCnt=0）

---

## 诊断结果详情

### 1. Server端日志分析

#### 日志路径
- `/data/test/server3.log`（当前运行的服务器测试日志）

#### 关键发现

**成功初始化**:
```
[Test] === Creating Session Server ===
[Test] pkgName: com.huawei.ros2_rmw_dsoftbus
[Test] sessionName: com.huawei.ros2_rmw_dsoftbus.test
[Test] CreateSessionServer returned: 0
[Test] OK Session server created
```

**设备发现成功**:
```
[Test] === Listing Online Devices ===
[Test] Found 2 online device(s):
  [0] networkId: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
      deviceName: KaihongBoard-3588S
  [1] networkId: ed35739d3925872e4510983ac67613f57b9dfabd274ffaf43919c7ec8a0f860c
      deviceName: KaihongBoard-3588S
```

**关键问题 - 连接状态**:
```
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
[Test] Status: connectCnt=0, outbound=-1, inbound=-1
[Test] Timeout reached, exiting
```

**分析**:
- Session Server已成功创建
- 发现了2个在线设备（Device 2和Device 3的network_id）
- **但连接数始终为0** - 没有接收到任何incoming连接
- **outbound=-1和inbound=-1** 表示没有建立过任何连接会话

### 2. dsoftbus服务进程状态

#### 设备1
```
dsoftbus      1067     1 3 18:37:25 ?     00:00:29 softbus_server
```
- ✅ 进程运行中
- ✅ CPU使用率: 3%
- ✅ 已运行超过10分钟，状态稳定

#### 设备2
```
dsoftbus      1129     1 2 18:37:26 ?     00:00:23 softbus_server
```
- ✅ 进程运行中
- ✅ CPU使用率: 2%
- ✅ 状态正常

### 3. 网络连接验证

#### 设备1
```
IP Address: 192.168.11.192
Netmask: 255.255.254.0
RX packets: 13243 (正常)
TX packets: 12320 (正常)
```

#### 设备2
```
IP Address: 192.168.11.196
Netmask: 255.255.254.0
RX packets: 10889 (正常)
TX packets: 14600 (正常)
```

**结论**: 两个设备在同一网段，网络连接良好。

### 4. 权限配置验证

设备1和设备2的权限配置完全相同，都包含：

```json
[
  {
    "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.*",
    "REGEXP": "true",
    "DEVID": "NETWORKID",
    "SEC_LEVEL": "public",
    "APP_INFO": [
      {
        "TYPE": "native_app",
        "PKG_NAME": "com.huawei.ros2_rmw_dsoftbus",
        "ACTIONS": "create,open"
      }
    ]
  },
  {
    "SESSION_NAME": "com.softbus.graph.discovery",
    "REGEXP": "false",
    "DEVID": "NETWORKID",
    "SEC_LEVEL": "public",
    "APP_INFO": [
      {
        "TYPE": "native_app",
        "PKG_NAME": "*",
        "ACTIONS": "create,open"
      }
    ]
  }
]
```

✅ 权限配置正确，支持：
- `com.huawei.ros2_rmw_dsoftbus.*` 会话创建和打开
- `com.softbus.graph.discovery` 发现服务

---

## 问题根因分析

### 当前症状
Server端无法接收incoming连接，导致connectCnt=0

### 可能原因（按优先级）

#### 1. **Client端未成功建立连接**（最可能）
- Client的OpenSession调用可能失败或返回错误
- Client的deviceId/peerId设置可能不正确
- Client的sessionName可能与Server配置不匹配

**检查点**:
- [ ] Device 2/3上的Client端是否返回了有效的sessionId（非-1）?
- [ ] Client是否尝试发送数据？
- [ ] Client的deviceId是否与Server发现的networkId匹配？

#### 2. **Session ID追踪机制有缺陷**
- 根据Phase 2测试报告，入站会话(inbound session)的ID追踪存在问题
- Server可能接收到了连接但未正确记录sessionId

**检查点**:
- [ ] 入站会话的sessionId与出站会话的sessionId是否互相关联？
- [ ] Server是否有内部会话表用于追踪inbound连接？

#### 3. **dsoftbus通道建立问题**
- OnSessionOpened回调可能未被触发
- OpenSession返回的sessionId可能与Server记录的不一致

**检查点**:
- [ ] Client的OnSessionOpened回调是否被调用？
- [ ] Server和Client对同一session的sessionId理解是否一致？

#### 4. **权限或安全验证**
- 虽然权限配置正确，但运行时验证可能有问题
- 可能需要设备认证（但目前未配置）

---

## 推荐行动方案

### 立即行动（高优先级）

1. **收集Client端日志**
```bash
# Device 2/3上运行的Client测试程序，查看其输出日志
hdc -t DEVICE2_ID shell 'cat /data/test/client*.log'
hdc -t DEVICE3_ID shell 'cat /data/test/client*.log'
```

2. **检查Client返回的sessionId**
- Client端OpenSession是否返回有效ID (>0)?
- 如果返回-1，意味着连接失败

3. **验证device Network ID匹配**
```bash
# Server端获取自己的network_id
hdc -t DEVICE1_ID shell '/data/test/get_network_id'

# Client端获取对端device ID
# 应与Server发现的networkId一致
```

4. **启用详细日志追踪**
- 修改测试程序添加每次OpenSession的日志记录
- 记录返回的sessionId和错误码
- 追踪OnSessionOpened/Closed回调是否被触发

### 深入调查（中优先级）

5. **验证Session回调机制**
- Server的OnSessionOpened回调是否被触发？
- 如果被触发，返回的sessionId是多少？
- 这个sessionId是否与后续的inbound=-1匹配？

6. **检查序列化数据路径**
- 确认SendBytes发送的数据是否到达对端
- 检查接收侧是否有OnBytesReceived回调

7. **检查dsoftbus内部状态**
```bash
# 如果系统提供了诊断工具
hdc -t DEVICE1_ID shell 'softbus_tool --status'
hdc -t DEVICE1_ID shell 'softbus_tool --session-list'
```

---

## 对比参考：Phase 2测试vs当前状态

### Phase 2成功建立的连接要素
- Device 2 ↔ Device 3 Session建立成功
- 双向发现成功
- 消息传输成功

### 当前失败的点
- Device 1作为Server角色时，无法接收Client连接
- 可能与Server作为被动接收方角色有关

**假设**: Phase 2测试中，Device 2和Device 3都主动发起OpenSession，而当前Server端期望被动接收。这可能暴露了Session建立的方向性问题。

---

## 文件清单

| 文件/路径 | 状态 | 备注 |
|---------|------|------|
| `/system/lib64/platformsdk/libsoftbus_client.z.so` | ✅ 已加载 | dlopen调用成功 |
| `/system/etc/communication/softbus/softbus_trans_permission.json` | ✅ 正确 | 权限配置完整 |
| `/data/test/server3.log` | ✅ 存在 | Server端日志完整 |
| Client端日志 | ❓ 待检查 | 需要从Device 2/3收集 |
| dsoftbus系统日志 | ⚠️ 无直接日志 | 可通过hilog查看实时日志 |

---

## 建议下一步

1. **并行收集**:
   - [ ] Client端日志（Device 2和Device 3）
   - [ ] OpenSession的返回值和错误码
   - [ ] OnSessionOpened回调的触发情况

2. **实时追踪**:
   - [ ] 添加更详细的日志输出到Client代码
   - [ ] 记录每次dsoftbus API调用的参数和返回值

3. **对比测试**:
   - [ ] 尝试Device 2→Device 1 OpenSession
   - [ ] 对比Device 2↔Device 3通信（已知可行）
   - [ ] 找出差异点

4. **文档更新**:
   - [ ] 根据新的诊断信息更新Phase 3测试计划
   - [ ] 记录Session ID追踪的具体实现细节

---

## 联系信息

此诊断报告由自动化诊断工具生成。
如需实时调试，请查看:
- `/data/test/server3.log` - Server端日志
- 各Device的Client端日志
- 系统hilog实时输出

**预计问题解决时间**: 需要收集Client端日志后评估
