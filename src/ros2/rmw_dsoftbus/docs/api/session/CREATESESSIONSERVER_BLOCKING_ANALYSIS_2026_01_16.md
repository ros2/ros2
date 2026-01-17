# CreateSessionServer Blocking Issue - Root Cause Analysis

**日期**: 2026-01-16
**设备**: rk3588s Device 1 (ec29004133314d38433031a522413c00)
**问题**: CreateSessionServer 调用阻塞，程序hang住

---

## 问题现象

### 观察到的行为

运行 `phase3b_session_test server` 时：

```
[Test] === Creating Session Server ===
[Test] pkgName: com.huawei.ros2_rmw_dsoftbus
[Test] sessionName: com.huawei.ros2_rmw_dsoftbus.test
<< 程序在这里hang住，永不返回 >>
```

**预期行为**:
```
[Test] CreateSessionServer returned: 0
[Test] OK Session server created
```

### 日志证据

从 Device 1 的 hilog:
```
E C05700/CommSdk: [softbus_client_frame_manager.c:68] AddClientPkgName# check PkgNameInfo invalid.
E C05700/CommSdk: [softbus_client_frame_manager.c:117] ClientRegisterPkgName# AddClientPkgName failed. ret=-426442749
E C05a01/SoftBusManager: [ServiceSocketInit:168]create service socket faild, ret is -426442743.
I C05701/CommSvc: [softbus_server_stub.cpp:501] CreateSessionServerInner# enter
```

---

## 根本原因分析

### 1. 包名注册失败

**错误**: `AddClientPkgName# check PkgNameInfo invalid`

**错误码**: `-426442749` (0xE681E003)

这个错误表明：
- dsoftbus 客户端 SDK 在尝试注册包名时失败
- 包名信息验证未通过

### 2. Service Socket 创建失败

**错误**: `create service socket faild, ret is -426442743`

**错误码**: `-426442743` (0xE681E009)

这表明：
- IPC socket 创建失败
- 客户端无法与 softbus_server 建立通信

### 3. CreateSessionServer 进入服务端

```
I C05701/CommSvc: [softbus_server_stub.cpp:501] CreateSessionServerInner# enter
```

这表明：
- IPC 请求到达了 softbus_server
- 服务端开始处理 CreateSessionServer 请求
- **但是没有返回响应**

---

## 关键发现

### 发现 1: 配置文件已正确配置

`/system/etc/communication/softbus/softbus_trans_permission.json`:
```json
{
  "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.*",
  "REGEXP": "true",
  "APP_INFO": [
    {
      "TYPE": "native_app",
      "PKG_NAME": "com.huawei.ros2_rmw_dsoftbus",
      "ACTIONS": "create,open"
    }
  ]
}
```

- ✅ 包名正确: `com.huawei.ros2_rmw_dsoftbus`
- ✅ 会话名模式: `com.huawei.ros2_rmw_dsoftbus.*`
- ✅ 权限正确: `create,open`
- ✅ 文件修改时间: 2026-01-15 18:37
- ✅ softbus 重启后: 19:47:29

### 发现 2: softbus_server 正常运行

```
dsoftbus      4133     1 3 19:47:28 ?     00:08:34 softbus_server
```

- ✅ 进程存在
- ✅ PID 稳定
- ✅ CPU 使用正常

### 发现 3: Token 注入成功

```
[Token] OK GetAccessTokenId returned: 0x2805b74b
[Token] OK SetSelfTokenID succeeded
```

- ✅ Access Token 获取成功
- ✅ Token 设置成功
- ✅ 拥有必需权限

### 发现 4: dsoftbus 库加载成功

```
[DSoftBus] OK Loaded from: /system/lib64/platformsdk/libsoftbus_client.z.so
[DSoftBus] OK CreateSessionServer: 0x7fb6580168
```

- ✅ 库加载成功
- ✅ 符号解析成功
- ✅ 函数指针有效

---

## 根因推断

基于上述证据，最可能的根因是：

### 假设 1: IPC 阻塞（最可能）

```
Client Process (phase3b_session_test)
    ↓ dlsym CreateSessionServer
    ↓ call CreateSessionServer()
    ↓ IPC call to softbus_server
    ↓
softbus_server receives CreateSessionServerInner
    ↓ AddClientPkgName validation
    ↓ ❌ check PkgNameInfo invalid
    ↓
    ? 没有返回错误，也没有返回成功
    ? IPC 响应丢失或阻塞
    ↓
Client Process 永久等待 IPC 响应
```

### 假设 2: 包名白名单检查失败后的异常处理

虽然配置文件正确，但可能：
- dsoftbus 内部有另一个白名单或黑名单
- 包名格式检查有额外规则（例如长度限制）
- 需要特定的 UID/GID

### 假设 3: 进程间权限问题

- 测试进程以 `root` 运行
- softbus_server 以 `dsoftbus` 用户运行
- IPC 权限检查可能失败

---

## 诊断计划

### 方法 1: 使用 strace 追踪系统调用

```bash
# 在设备上运行
hdc shell 'cd /data/local/tmp && strace -f -e trace=connect,sendto,recvfrom ./phase3b_session_test server'
```

这将显示 IPC 通信的系统调用，确定阻塞点。

### 方法 2: 检查 softbus IPC socket

```bash
# 检查 softbus socket
hdc shell 'ls -l /dev/unix/socket/ | grep softbus'
hdc shell 'netstat -an | grep softbus'
```

### 方法 3: 使用官方测试程序对比

```bash
# 查找 OpenHarmony 自带的 dsoftbus 测试程序
hdc shell 'find /system -name "*auth_session*" -o -name "*softbus*test*"'

# 运行官方测试看是否成功
```

### 方法 4: 简化测试 - 最小复现

创建最小的 C 程序只调用 CreateSessionServer：
```c
#include <dlfcn.h>
#include <stdio.h>

typedef int (*CreateSessionServer_t)(const char*, const char*, void*);

int main() {
    void *h = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW);
    CreateSessionServer_t func = dlsym(h, "CreateSessionServer");

    printf("Calling CreateSessionServer...\n");
    int ret = func("test.pkg", "test.session", NULL);
    printf("Returned: %d\n", ret);

    return 0;
}
```

---

## 可能的修复方案

### 方案 1: 修改包名格式

尝试更短或更简单的包名：
```
com.huawei.ros2_rmw_dsoftbus → com.huawei.rmw
com.huawei.ros2 → com.test
```

### 方案 2: 使用 HAP 应用方式

参考文档提到，native 进程可能需要特殊处理。尝试：
- 创建一个 HAP 应用
- 在 HAP 中调用 dsoftbus API

### 方案 3: 检查并修复 UID/GID

```bash
# 以 dsoftbus 用户运行测试
hdc shell 'su dsoftbus -c "cd /data/local/tmp && ./phase3b_session_test server"'
```

### 方案 4: 使用异步方式

如果 CreateSessionServer 是异步的，可能需要：
- 调用后立即返回
- 通过回调获取结果
- 不应该阻塞等待

---

## 下一步行动

### 优先级 1: 使用 strace 确定阻塞点

```bash
hdc -t ec29004133314d38433031a522413c00 shell \
  'cd /data/local/tmp && timeout 10 strace -f -e trace=all ./phase3b_session_test server 2>&1 | tail -100'
```

### 优先级 2: 查找并运行官方测试

```bash
# 查找官方测试
hdc shell 'find /system -name "*session*test*" 2>/dev/null'

# 如果找到，运行并对比行为
```

### 优先级 3: 简化包名测试

修改配置文件使用简单包名：
```json
{
  "PKG_NAME": "test"
}
```

重启设备并测试。

---

## 参考资料

- **Phase 2 成功报告**: `PHASE2_CROSS_DEVICE_TEST_RESULTS.md`
- **Phase 3 行动计划**: `PHASE3_SESSION_TRACKING_ACTION_PLAN.md`
- **设备诊断报告**: `DEVICE1_SERVER_DIAGNOSTIC_REPORT.md`
- **权限系统指南**: `OPENHARMONY_PERMISSION_SYSTEM_GUIDE.md`

---

**状态**: 🔴 阻塞中
**下一步**: 使用 strace 追踪系统调用
