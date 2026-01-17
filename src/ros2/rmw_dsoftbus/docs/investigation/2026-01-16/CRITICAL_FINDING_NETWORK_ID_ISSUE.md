# 关键发现：Network ID 错误导致测试失败

**日期**: 2026-01-16
**重大发现**: 一直使用错误的 Network ID！

---

## 问题分析

### 新的错误码：-426442706

**Client 测试输出**:
```
[Test] OpenSession returned: -426442706   ← 新错误！
[Test] FAIL OpenSession failed with error code: -426442706
```

**这不是之前的 -426115004！**

### 设备发现不一致

**Client 端看到的设备** (Device 2 视角):
```
[Test] Found 1 online device(s):
  [0] networkId: e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212
```

**但 Client 尝试连接的是**:
```
[Test] peerNetworkId: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
```

**问题**: ❌ **这个 Network ID 不在发现列表中！**

### Server 端看到的设备 (Device 1 视角)

**第一次**:
```
[Test] Found 2 online device(s):
  [0] networkId: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
  [1] networkId: 63ab5c23c0cfb1b2e864f5a879b16dc1f22c073dac6d096f9606a969e93c99f7
```

**第二次**:
```
[Test] Found 1 online device(s):
  [0] networkId: 63ab5c23c0cfb1b2e864f5a879b16dc1f22c073dac6d096f9606a969e93c99f7
```

**观察**: 设备发现结果不稳定

---

## 根本问题

### 错误的 Network ID

我们一直使用的 Network ID:
```
6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
```

**这个 ID 的真相**:
- ❌ **不是 Device 1 的 network ID**
- ❌ **不在 Device 2 的发现列表中**
- ❌ 可能是 Device 3 或已离线设备的 ID

**正确的 Device 1 Network ID**（从 Device 2 视角）:
```
e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212
```

这才是 Device 2 实际看到的在线设备！

---

## 错误码 -426442706 含义

这个错误码表示:
- 找不到目标设备
- Network ID 无效或设备不在线
- 可能是 SOFTBUS_TRANS_DEVICE_NOT_FOUND

**与 -426115004 的区别**:
- -426115004: 设备在线，但 Session Server 未注册
- -426442706: 设备根本找不到（Network ID 错误）

---

## 解决方案

### 正确的测试命令

**步骤 1: 在 Device 2 上查询 Device 1**

Client 设备查询在线设备:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
```

**使用输出中看到的 networkId**（不是之前记录的旧 ID）

当前看到的是:
```
e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212
```

**步骤 2: Server (终端 1)**

```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

**步骤 3: Client (终端 2, < 30秒内)**

使用**正确的** Network ID:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212'
```

---

## 为什么之前一直失败

### 时间线回顾

所有之前的测试都使用了错误的 Network ID:
```
6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
```

**这个 ID**:
- 可能是 Device 3 的
- 或者是之前测试时的某个设备（已离线）
- Device 2 根本看不到这个设备

**导致**:
- OpenSession 找不到目标设备
- 返回错误（-426442706 或 -426115004）
- 无法建立连接

---

## 设备发现不稳定的原因

### 观察到的现象

**有时看到 2 台设备**:
```
[0] 6ea1cecbc95eb2d290af...
[1] 63ab5c23c0cfb1b2e864f...
```

**有时只看到 1 台设备**:
```
[0] 63ab5c23c0cfb1b2e864f...
```

**或**:
```
[0] e05acef96ee6b1b68025...
```

**可能原因**:
1. **三台设备**: Device 1, Device 2, Device 3（偶尔在线/离线）
2. **网络不稳定**: 设备间的 dsoftbus 发现有延迟
3. **缓存问题**: 设备发现缓存未及时更新

### 正确的做法

**每次测试前**:
1. 在 Device 2 上 list，看到哪些设备
2. 使用**当前看到的** networkId
3. 不使用之前记录的旧 ID

---

## 正确的手动测试流程

### 修正后的步骤

#### 1. 实时查询 Network ID（每次测试前都要查）

```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
```

**记录看到的所有 networkId**

#### 2. 启动 Server (终端 1)

```bash
hdc -t ec29004133314d38433031a5544f3c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test server'
```

等待看到 "Waiting for connections"

#### 3. 再次查询确认 (可选)

在另一个终端快速查询，确认 Device 1 是否在线:
```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
```

如果看到新的设备（之前没看到的），那个就是 Device 1！

#### 4. 运行 Client (终端 2, 使用实时查到的 ID)

```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test client <刚才查到的ID>'
```

---

## 预期结果（使用正确 Network ID）

### 如果使用正确的 Network ID

**Client**:
```
[Test] OpenSession returned: 1   ← 正数！不再是 -426442706
[Callback] OnSessionOpened: sessionId=1, result=?
```

result 可能是:
- `0` = 成功 ✅
- `-426115004` = Server 超时问题（需要更快的时序）

### 如果仍然是错误的 Network ID

**Client**:
```
[Test] OpenSession returned: -426442706   ← 设备找不到
```

---

## 设备映射推测

### 当前三台设备的可能映射

| Device | 设备 ID | Network ID (推测) |
|--------|---------|------------------|
| Device 1 | ec29004133314d38433031a5544f3c00 | e05acef96ee6b1b68025... (当前在线) |
| Device 2 | ec29004133314d38433031a522413c00 | 63ab5c23c0cfb1b2e864... (当前在线) |
| Device 3? | 未知 | 6ea1cecbc95eb2d290af... (可能离线) |

**建议**: 实时查询，不依赖固定的 Network ID

---

## 下一步行动

### 立即执行

1. **在 Device 2 上实时查询**:
   ```bash
   hdc -t ec29004133314d38433031a522413c00 shell \
     'cd /data/test && LD_LIBRARY_PATH=. ./phase3b_session_test list'
   ```

2. **记录看到的 networkId**

3. **启动 Server** (终端 1)

4. **使用刚才查到的 networkId 运行 Client** (终端 2)

### 预期改进

使用正确的 Network ID 后:
- ✅ OpenSession 应该返回正数（不再是 -426442706）
- 可能会返回 -426115004（Server 超时问题，但至少设备找到了）
- 或返回 0 / 正数（成功建立 Session）

---

**关键发现**: Network ID 一直用错了！
**解决方案**: 每次测试前实时查询
**下一步**: 使用正确 ID 重新测试
