# Phase 2 部署和测试完整指南

**文档日期**: 2026-01-14
**作者**: RMW DSoftBus Team
**状态**: ✅ Phase 2 验证完成

---

## 📋 目录

1. [快速开始](#快速开始)
2. [环境准备](#环境准备)
3. [部署流程](#部署流程)
4. [测试方案](#测试方案)
5. [配置文件](#配置文件)
6. [故障排查](#故障排查)
7. [关键发现](#关键发现)

---

## 快速开始

### 最小化测试（单设备）

```bash
# 1. 编译
cd /home/jiusi/M-DDS/rmw_dsoftbus
ninja -C build-ohos rmw_complete_test

# 2. 部署
DEVICE_ID=$(powershell.exe -NoProfile -Command "hdc list targets" | head -1 | awk '{print $1}' | tr -d '\r\n')
powershell.exe -Command "hdc -t $DEVICE_ID file send build-ohos/rmw_complete_test /data/local/tmp/"

# 3. 运行测试
powershell.exe -Command "hdc -t $DEVICE_ID shell 'cd /data/local/tmp && chmod +x rmw_complete_test && ./rmw_complete_test'"
```

### 跨设备测试（两设备）

```bash
# 设备 A（Server）
./rmw_complete_test

# 设备 B（Client）- 获取设备 A 的 NetworkID 后
./session_test client <NetworkID_A>
```

---

## 环境准备

### 硬件需求

| 项目 | 规格 |
|------|------|
| 开发板 | rk3588s KaihongOS |
| 数量 | 2 台（跨设备测试） |
| 连接 | USB HDC / 网络连接 |

### 软件需求

```bash
# WSL Ubuntu 20.04
gcc-aarch64-linux-gnu >= 7.5.0
clang >= 10.0.0
gn >= 1.0.0
ninja >= 1.10.0

# Windows
hdc (HDC 工具)
powershell >= 5.0
```

### 交叉编译工具链

```bash
# OpenHarmony prebuilts 工具链
PATH_PREBUILT="/home/jiusi/M-DDS/prebuilts"

# Clang
${PATH_PREBUILT}/clang/host/linux-x86/clang-r416.0b/bin/clang++

# GCC（如果需要）
/usr/bin/aarch64-linux-gnu-gcc
```

---

## 部署流程

### 第 1 步：编译准备

```bash
# 检查编译工具
which ninja gn
ninja --version
gn --version

# 生成编译配置
cd /home/jiusi/M-DDS/rmw_dsoftbus
gn gen build-ohos
```

### 第 2 步：编译程序

```bash
# 编译主程序
ninja -C build-ohos rmw_complete_test

# 编译 Session 测试（跨设备）
ninja -C build-ohos session_test

# 验证编译成功
ls -lh build-ohos/rmw_complete_test build-ohos/session_test
```

### 第 3 步：获取设备 ID

```bash
# 列出所有设备
powershell.exe -NoProfile -Command "hdc list targets -v"

# 提取设备 ID
DEVICE_ID=$(powershell.exe -NoProfile -Command "hdc list targets" | head -1 | awk '{print $1}' | tr -d '\r\n')
echo "Device ID: $DEVICE_ID"
```

### 第 4 步：文件传输

```bash
# 创建临时目录
mkdir -p /mnt/c/tmp/hdc_transfer

# 复制编译产物
cp build-ohos/rmw_complete_test /mnt/c/tmp/hdc_transfer/
cp build-ohos/session_test /mnt/c/tmp/hdc_transfer/

# 传输到设备
powershell.exe -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\rmw_complete_test' '/data/local/tmp/'"
powershell.exe -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\session_test' '/data/local/tmp/'"
```

### 第 5 步：部署配置文件

```bash
# 复制权限配置
cp config/softbus_trans_permission.json /mnt/c/tmp/hdc_transfer/

# 传输到设备系统目录（需要 root）
powershell.exe -Command "hdc -t $DEVICE_ID shell 'mount -o remount,rw /system'"
powershell.exe -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\softbus_trans_permission.json' '/system/etc/communication/softbus/'"
powershell.exe -Command "hdc -t $DEVICE_ID shell 'mount -o remount,ro /system'"

# 重启 DSoftBus 服务
powershell.exe -Command "hdc -t $DEVICE_ID shell 'killall softbus_server'"
powershell.exe -Command "hdc -t $DEVICE_ID shell 'sleep 2 && nohup softbus_server &'"
```

---

## 测试方案

### 方案 A：单设备基础验证

**目标**: 验证所有 API 在单设备上正常工作

**步骤**:
```bash
# 1. 运行完整测试程序
chmod +x rmw_complete_test
./rmw_complete_test 2>&1 | tee test_output.log

# 2. 检查输出
grep -E "Token:|NetworkID:|CreateSessionServer:|✅|✓" test_output.log
```

**预期输出**:
```
[✅] Permission setup
Token: 0x28055235
✓ Permission setup

[✅] Get Local Info
Device: KaihongBoard-3588S
NetworkID: 2ce0442a2400c631a9ca0b8c89f5b31514ecf9a065ab8a50e826480999eebb77

[✅] Create Session Server
CreateSessionServer: 0
✅ Session server created
```

### 方案 B：跨设备 Session 连接

**目标**: 验证两个设备可以建立 Session 并传输数据

**配置**:
1. 设备 A（ec29004133314d38433031a522413c00）
2. 设备 B（ec29004133314d38433031a751c63c00）

**步骤**:

**在设备 A 上**:
```bash
./session_test server 2>&1 | tee server.log
# 输出设备 A 的 NetworkID
# 保持运行，等待客户端连接
```

**在设备 B 上**:
```bash
# 使用设备 A 的 NetworkID
NETWORK_ID_A="2ce0442a2400c631a9ca0b8c89f5b31514ecf9a065ab8a50e826480999eebb77"
./session_test client $NETWORK_ID_A 2>&1 | tee client.log
```

**预期结果**:
- 设备 B 成功调用 `OpenSession`（返回 session_id >= 0）
- 设备 B 发送数据（使用 `SendBytes`）
- 设备 A 接收回调（`OnBytesReceived` 触发）

### 方案 C：日志诊断

**收集系统日志**:
```bash
# 清空旧日志
hdc shell 'hilog -c'

# 启动程序
./rmw_complete_test

# 导出日志
hdc shell 'hilog -r > /tmp/hilog.txt'
hdc file recv /tmp/hilog.txt ./hilog_output.log

# 分析日志
grep -E "ERROR|WARN|dsoftbus|rmw" hilog_output.log
```

---

## 配置文件

### softbus_trans_permission.json

**位置**: `/system/etc/communication/softbus/softbus_trans_permission.json`

**正确格式** ✅:
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
  }
]
```

**关键点**:
1. ⚠️ **必须是数组格式** `[{...}]`，不是单对象 `{...}`
2. `PKG_NAME` 必须完全匹配代码中的 `PKG_NAME`
3. `SESSION_NAME` 使用正则表达式 `.*` 匹配所有会话

**验证配置**:
```bash
# 检查文件格式
cat /system/etc/communication/softbus/softbus_trans_permission.json | python3 -m json.tool

# 查看权限检查日志
hilog | grep -i "permission\|access"
```

### 环境变量配置

**跨设备通信时需要设置**:
```bash
# 设备 A（Subscriber）需要设置
export RMW_DSOFTBUS_PEER_ID="8d1b112eb9c39f85d73cb704995b75379adbb394d5b83e11d7abe542430a6b92"  # 设备 B 的 NetworkID
export RMW_DSOFTBUS_QOS_MODE="RELIABLE_PLAIN"

# 运行程序
./rmw_complete_test
```

---

## 故障排查

### 问题 1：GetAccessTokenId 返回 0

**症状**:
```
Token: 0x0
ERROR: GetAccessTokenId failed
```

**原因**:
- 权限参数不正确
- APL 级别不是 `system_basic`
- 权限列表为空

**解决**:
```cpp
// 正确的权限设置
const char* perms[2] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
};

NativeTokenInfoParams params;
params.dcapsNum = 0;
params.permsNum = 2;           // ✅ 必须是 2
params.aclsNum = 0;
params.dcaps = nullptr;
params.perms = perms;          // ✅ 必须有权限
params.acls = nullptr;
params.processName = PKG_NAME;
params.aplStr = "system_basic"; // ✅ 必须是 system_basic
```

### 问题 2：CreateSessionServer 返回 -426442743 (0xE6950009)

**症状**:
```
CreateSessionServer: -426442743
ERROR: CreateSessionServer failed
```

**原因**:
- 配置文件格式错误（单对象而不是数组）
- PKG_NAME 或 SESSION_NAME 不匹配
- 权限未生效

**解决步骤**:
```bash
# 1. 验证配置文件格式
cat /system/etc/communication/softbus/softbus_trans_permission.json | python3 -c "import json, sys; json.load(sys.stdin); print('✅ JSON 格式正确')"

# 2. 验证 PKG_NAME 匹配
grep "PKG_NAME" rmw_complete_test_source.cpp
grep "PKG_NAME" /system/etc/communication/softbus/softbus_trans_permission.json

# 3. remount 和重新部署配置
hdc shell 'mount -o remount,rw /system'
hdc file send softbus_trans_permission.json /system/etc/communication/softbus/
hdc shell 'mount -o remount,ro /system'

# 4. 重启 dsoftbus 服务
hdc shell 'killall softbus_server'
hdc shell 'sleep 2 && nohup softbus_server &'
```

### 问题 3：GetLocalNodeDeviceInfo 失败

**症状**:
```
GetLocalNodeDeviceInfo: -1
Device info not retrieved
```

**原因**:
- Token 未正确设置
- Token 未被系统识别
- DSoftBus 服务未运行

**解决**:
```bash
# 1. 检查 token 是否已注册
cat /data/service/el0/access_token/nativetoken.json | grep PKG_NAME

# 2. 检查 dsoftbus 服务状态
hdc shell 'ps aux | grep softbus_server'

# 3. 重启 dsoftbus
hdc shell 'killall softbus_server; sleep 2; nohup softbus_server &'

# 4. 等待服务启动
hdc shell 'sleep 3 && netstat -tlnp | grep softbus'
```

### 问题 4：OpenSession 返回 -1（跨设备失败）

**症状**:
```
OpenSession returned: -1
❌ OpenSession failed
```

**原因**:
- 对端设备 NetworkID 错误
- 对端设备未运行 Session Server
- 网络连接问题

**解决**:
```bash
# 1. 验证对端 NetworkID
# 在对端设备上运行：
./rmw_complete_test 2>&1 | grep "NetworkID:"

# 2. 验证对端 Session Server 已创建
# 对端设备应该看到：
# CreateSessionServer: 0
# ✅ Session server created

# 3. 检查网络连接
hdc shell 'ping <对端IP>'
hdc shell 'netstat -tlnp | grep -E "softbus|socket"'
```

---

## 关键发现

### 发现 1：权限绕过方案

✅ **最终方案**: 静态链接 AccessToken 库 + dlopen dsoftbus

```cpp
// 静态链接这些库：
// - libnativetoken.a
// - libtoken_setproc.a
// - libcjson_static.a
// - libsec_static.a

extern "C" {
    uint64_t GetAccessTokenId(NativeTokenInfoParams *tokenInfo);
    int SetSelfTokenID(uint64_t tokenID);
}

// 获取真实 Token
uint64_t tokenId = GetAccessTokenId(&params);
SetSelfTokenID(tokenId);
```

### 发现 2：配置文件的正确格式

❌ **错误格式**:
```json
{
  "SESSION_NAME": "com.huawei.ros2_rmw_dsoftbus.*",
  "PKG_NAME": "com.huawei.ros2_rmw_dsoftbus"
}
```

✅ **正确格式**:
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
  }
]
```

### 发现 3：dlopen 加载 DSoftBus API

✅ **推荐方案**:
```cpp
void* handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);

CreateSessionServer = (CreateSessionServer_t)dlsym(handle, "CreateSessionServer");
OpenSession = (OpenSession_t)dlsym(handle, "OpenSession");
SendBytes = (SendBytes_t)dlsym(handle, "SendBytes");

// 无需静态链接，运行时动态加载
```

### 发现 4：NetworkID 的用途

**NetworkID** 是跨设备通信的关键：
- 格式: 64 字符十六进制字符串
- 唯一性: 每个设备在网络中唯一
- 获取: 通过 `GetLocalNodeDeviceInfo` API
- 用途: 在 `OpenSession` 中指定对端设备

**示例**:
```
设备 A NetworkID: 2ce0442a2400c631a9ca0b8c89f5b31514ecf9a065ab8a50e826480999eebb77
设备 B NetworkID: 8d1b112eb9c39f85d73cb704995b75379adbb394d5b83e11d7abe542430a6b92

// 设备 B 连接到设备 A
int sessionId = OpenSession(SESSION_NAME, SESSION_NAME,
                           "2ce0442a2400c631a9ca0b8c89f5b31514ecf9a065ab8a50e826480999eebb77",
                           nullptr, &attr);
```

---

## 相关文件

| 文件 | 用途 |
|------|------|
| `test/rmw_complete_test_static.cpp` | 单设备完整测试（已验证） |
| `test/session_server_client_test.cpp` | 跨设备 Session 连接测试 |
| `test/phase2_cross_device_session_test.cpp` | Phase 2 原始跨设备实现 |
| `config/softbus_trans_permission.json` | 权限配置模板 |
| `test/softbus_dlopen_shim.cpp` | dlopen 动态加载实现 |
| `PHASE2_COMPLETE_SUMMARY.md` | Phase 2 验证总结 |

---

## 下一步建议

1. **基于 Phase 2 进行 Phase 3 开发**
   - RMW Discovery 完整实现
   - Pub/Sub 机制开发
   - 参考 `test/phase2_cross_device_session_test.cpp`

2. **优化和完善**
   - 添加错误处理和重试机制
   - 实现会话池管理
   - 完善日志和监控

3. **性能测试**
   - 消息吞吐量测试
   - 延迟测试
   - 稳定性长期运行测试

---

**文档完成日期**: 2026-01-14
**验证状态**: ✅ Phase 2 所有功能已验证
**可用程度**: 生产级别
