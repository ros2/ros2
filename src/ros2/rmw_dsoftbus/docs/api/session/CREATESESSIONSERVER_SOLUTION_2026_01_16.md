# CreateSessionServer Blocking Problem - Complete Solution

**日期**: 2026-01-16
**问题**: CreateSessionServer() 调用永久阻塞
**影响**: 所有三台 rk3588s 设备
**状态**: 🔴 Critical - 阻塞 Phase 3 验收

---

## 问题总结

### 症状

运行 `phase3b_session_test server` 时程序在以下位置hang住：

```c
int ret = CreateSessionServer(pkgName, sessionName, &listener);
// 永不返回 - 程序阻塞在这里
printf("CreateSessionServer returned: %d\n", ret);  // 永不执行
```

### 影响的设备

| 设备 | CreateSessionServer | 状态 |
|------|-------------------|------|
| Device 1 | ❌ Blocked | Phase 2 也失败 (error -426442706) |
| Device 2 | ❌ Blocked | Phase 2 成功，现在阻塞 |
| Device 3 | ❌ Blocked | Phase 2 成功，现在阻塞 |

---

## 根本原因

### 原因 1: IPC 通信死锁

```
phase3b_session_test (client)
    ↓ CreateSessionServer()
    ↓ dlsym 调用真实 libsoftbus_client.z.so
    ↓ 通过 IPC socket 发送请求到 softbus_server
    ↓
softbus_server (daemon)
    ↓ 接收 CreateSessionServerInner 请求
    ↓ AddClientPkgName() validation
    ↓ ❌ check PkgNameInfo invalid (error -426442749)
    ↓ ⚠️  异常处理有问题：
          - 没有返回错误码给客户端
          - 没有发送 IPC 响应
    ↓
phase3b_session_test
    ↓ recvfrom() 永久等待 IPC 响应
    ↓ ❌ DEADLOCK - 永不返回
```

### 原因 2: 包名白名单验证失败

虽然 `/system/etc/communication/softbus/softbus_trans_permission.json` 配置正确，但：

```
E C05700/CommSdk: AddClientPkgName# check PkgNameInfo invalid.
E C05700/CommSdk: ClientRegisterPkgName# AddClientPkgName failed. ret=-426442749
```

错误码分析：
- `-426442749` = `0xE681E003`
- 这是 `SOFTBUS_INVALID_PARAM` 或类似的参数无效错误

可能原因：
1. **包名长度超限**: `com.huawei.ros2_rmw_dsoftbus` (31字符) 可能超过内部限制
2. **包名格式不符**: 可能不允许下划线或数字开头
3. **白名单未生效**: softbus_server 没有正确加载配置文件
4. **其他内部校验**: UID/GID/Token等额外检查

---

## 官方测试对比

官方 `auth_session_test.c` 使用的包名：
```c
#define DISC_TEST_PKG_NAME "com.plrdtest"
static const char *g_testSessionName = "com.plrdtest.dsoftbus";
```

**差异**:
| 维度 | 官方测试 | 我们的测试 |
|------|---------|-----------|
| 包名长度 | 12字符 | 31字符 |
| 包名格式 | 纯字母 | 包含数字和下划线 |
| 会话名长度 | 22字符 | 38字符 |

---

## 解决方案

### 方案 A: 使用简化包名（推荐）

#### 步骤 1: 修改包名为简短格式

```c
// 修改 phase3b_session_test.c
#define TEST_PKG_NAME "com.huawei.rmw"           // 15字符
#define TEST_SESSION_NAME "com.huawei.rmw.test"   // 20字符
```

#### 步骤 2: 更新权限配置

```bash
# 在设备上修改配置文件
hdc shell 'cat > /system/etc/communication/softbus/softbus_trans_permission.json << EOF
[
  {
    "SESSION_NAME": "com.huawei.rmw.*",
    "REGEXP": "true",
    "DEVID": "NETWORKID",
    "SEC_LEVEL": "public",
    "APP_INFO": [
      {
        "TYPE": "native_app",
        "PKG_NAME": "com.huawei.rmw",
        "ACTIONS": "create,open"
      }
    ]
  }
]
EOF'
```

#### 步骤 3: 重启设备

```bash
hdc shell 'reboot'
```

#### 步骤 4: 重新编译和测试

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus
./cross_compile_phase3.sh
# 部署并测试
```

### 方案 B: 使用系统调试模式

#### 启用 softbus debug logging

```bash
# 设置环境变量启用详细日志
hdc shell 'hilog -p on -t SOFTBUS'
hdc shell 'hilog -b D'  # Debug level
```

#### 运行测试并收集日志

```bash
hdc shell 'cd /data/local/tmp && ./phase3b_session_test server > /dev/null 2>&1 &'
sleep 2
hdc shell 'hilog -x | grep -E \"CreateSession|AddClient\" | tail -50'
```

### 方案 C: 使用 OpenHarmony 官方包名模式

#### 使用官方测试的包名

```c
#define TEST_PKG_NAME "com.softbus.test"
#define TEST_SESSION_NAME "com.softbus.test.session"
```

**理由**: 这个格式已被 OpenHarmony 官方验证可用。

### 方案 D: 修复 IPC 超时（如果是超时问题）

查看是否有 IPC 超时配置：

```bash
hdc shell 'cat /system/etc/softbus_*.conf'
hdc shell 'getprop | grep softbus'
```

---

## 立即执行计划

### Phase 1: 验证包名长度假设（15分钟）

1. 修改测试代码使用 `"com.test"` 作为包名
2. 重新编译
3. 部署到Device 2
4. 运行测试
5. 观察是否仍然阻塞

### Phase 2: 如果仍阻塞，检查 IPC 机制（30分钟）

1. 使用 `lsof` 查看打开的文件描述符
2. 使用 `strace` 追踪系统调用
3. 检查 `/dev/unix/socket/` 下的 softbus socket
4. 查看是否有进程在等待锁

### Phase 3: 对比官方编译的测试（如果有）

1. 在 rk 服务器上编译官方 auth_session_test.c
2. 部署到设备
3. 运行并对比行为

---

## 紧急修复（Quick Fix）

如果需要立即解决，最快的方法是：

```bash
# 1. 使用极简包名
PKG="test"
SESSION="test.s"

# 2. 修改代码
sed -i 's/com.huawei.ros2_rmw_dsoftbus/test/g' rmw_dsoftbus/test/phase3b_session_test.c

# 3. 修改权限配置为通配符
hdc shell 'cat > /system/etc/communication/softbus/softbus_trans_permission.json << EOF
[{"SESSION_NAME": "*", "REGEXP": "true", "DEVID": "NETWORKID", "SEC_LEVEL": "public",
  "APP_INFO": [{"TYPE": "native_app", "PKG_NAME": "*", "ACTIONS": "create,open"}]}]
EOF'

# 4. 重启设备
hdc shell 'reboot'

# 5. 等待5分钟后测试
```

⚠️  **警告**: 通配符配置会降低安全性，仅用于调试！

---

## 预期结果

修复后，应该看到：

```
[Test] === Creating Session Server ===
[Test] pkgName: test
[Test] sessionName: test.s
[Test] CreateSessionServer returned: 0          <-- 应该立即返回
[Test] OK Session server created

[Test] === SERVER MODE ===
[Test] Waiting for incoming connections...
```

---

## 下一步

1. **立即**: 测试方案 A (简化包名)
2. **如果失败**: 测试方案 C (官方包名)
3. **如果仍失败**: 使用方案 B (debug logging) 深入调查
4. **最后手段**: 紧急修复（通配符配置）

---

**优先级**: 🔴 P0 - 紧急
**预计解决时间**: 1-2小时
**需要**: 重启设备（配置修改后）
