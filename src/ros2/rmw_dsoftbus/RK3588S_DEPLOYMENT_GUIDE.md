# RK3588S 开发板部署指南

**项目**: rmw_dsoftbus - ROS2 KaihongOS 移植
**目标平台**: rk3588s KaihongOS (aarch64-linux-ohos)
**编译工具链**: OpenHarmony SDK Clang 15.0.4
**最后更新**: 2026-01-15

---

## 📋 目录

1. [环境准备](#1-环境准备)
2. [工具链安装](#2-工具链安装)
3. [交叉编译](#3-交叉编译)
4. [部署到设备](#4-部署到设备)
5. [运行测试](#5-运行测试)
6. [故障排查](#6-故障排查)
7. [高级配置](#7-高级配置)

---

## 1. 环境准备

### 1.1 系统要求

**主机系统**: WSL Ubuntu 20.04 (或原生 Linux)
**开发板**: rk3588s KaihongOS (OpenHarmony 4.x)
**通信方式**: HDC (HarmonyOS Device Connector) via Windows

### 1.2 目录结构

```
/home/jiusi/M-DDS/
├── rmw_dsoftbus/              # 本项目源码
│   ├── src/                   # C++ 源文件
│   ├── include/               # 头文件
│   ├── test/                  # 测试程序
│   ├── cross_compile_ohos.sh  # 交叉编译脚本
│   └── BUILD.gn               # GN 构建配置 (备用)
├── openharmony_prebuilts/     # OpenHarmony 工具链
│   ├── clang_linux-x86_64-81cdec-20240308/  # OHOS Clang 15.0.4
│   └── gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/  # Sysroot
└── ohos_sdk/                  # (可选) 完整 OHOS SDK
```

### 1.3 必需工具

```bash
# 安装基础开发工具
sudo apt update
sudo apt install -y build-essential git cmake wget curl

# 检查是否已安装 HDC (Windows 端)
# HDC 通常随 DevEco Studio 安装
# 路径: C:\Users\<Username>\AppData\Local\OpenHarmony\Sdk\<version>\toolchains\
```

---

## 2. 工具链安装

### 2.1 下载 OpenHarmony 工具链

**OHOS Clang 15.0.4** (约 800 MB):

```bash
cd /home/jiusi/M-DDS/openharmony_prebuilts

# 如果已有工具链，跳过此步骤
# 否则从 OpenHarmony 官网下载:
# https://repo.huaweicloud.com/openharmony/os/

# 解压工具链
tar -xzf clang_linux-x86_64-81cdec-20240308.tar.gz
```

**GCC Linaro Sysroot** (约 200 MB):

```bash
cd /home/jiusi/M-DDS/openharmony_prebuilts

# 下载 GCC Linaro 7.5.0
wget https://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/aarch64-linux-gnu/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu.tar.xz

# 解压
tar -xf gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu.tar.xz
```

### 2.2 验证工具链

```bash
# 检查 Clang 版本
/home/jiusi/M-DDS/openharmony_prebuilts/clang_linux-x86_64-81cdec-20240308/bin/aarch64-unknown-linux-ohos-clang --version

# 预期输出:
# clang version 15.0.4
# Target: aarch64-unknown-linux-ohos
```

### 2.3 设置环境变量 (可选)

```bash
# 添加到 ~/.bashrc
export OHOS_CLANG=/home/jiusi/M-DDS/openharmony_prebuilts/clang_linux-x86_64-81cdec-20240308
export GCC_LINARO=/home/jiusi/M-DDS/openharmony_prebuilts/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu
export PATH=${OHOS_CLANG}/bin:${PATH}
```

---

## 3. 交叉编译

### 3.1 使用自动化脚本 (推荐)

**方法 A: 完整编译**

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus

# 完整编译（库 + 测试程序）
./cross_compile_ohos.sh all
```

**方法 B: 仅编译库**

```bash
./cross_compile_ohos.sh
```

**方法 C: 清理重新编译**

```bash
./cross_compile_ohos.sh clean
./cross_compile_ohos.sh all
```

### 3.2 编译输出

**成功输出示例**:

```
==========================================
rmw_dsoftbus Cross-Compilation for aarch64-ohos
==========================================
Toolchain: /home/jiusi/M-DDS/openharmony_prebuilts/clang_linux-x86_64-81cdec-20240308
Sysroot: /home/jiusi/M-DDS/openharmony_prebuilts/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/aarch64-linux-gnu/libc
Build Dir: /home/jiusi/M-DDS/rmw_dsoftbus/build_aarch64
Mode: all

[Check] Verifying OHOS SDK toolchain...
[OK] Toolchain verified
clang version 15.0.4

[Setup] Creating build directory...
[OK] Build directory created

[Compile] Building librmw_dsoftbus.so...
  Compiling: src/rmw_allocation.cpp
  Compiling: src/rmw_client.cpp
  ...
  Linking: librmw_dsoftbus.so.0.1.0
[OK] Library built successfully
-rwxr-xr-x 1 jiusi jiusi 5.5M Jan 15 05:06 librmw_dsoftbus.so.0.1.0

[Compile] Building service_rpc_real_test...
[OK] Test binary built successfully
-rwxr-xr-x 1 jiusi jiusi 65K Jan 15 05:06 service_rpc_real_test

==========================================
Build Summary
==========================================
Library:
/home/jiusi/M-DDS/rmw_dsoftbus/build_aarch64/lib/librmw_dsoftbus.so.0.1.0: ELF 64-bit LSB shared object, ARM aarch64

Test Binary:
/home/jiusi/M-DDS/rmw_dsoftbus/build_aarch64/bin/service_rpc_real_test: ELF 64-bit LSB shared object, ARM aarch64

[✅] Cross-compilation complete!
```

### 3.3 产物说明

| 文件 | 路径 | 大小 | 说明 |
|------|------|------|------|
| **主库** | `build_aarch64/lib/librmw_dsoftbus.so.0.1.0` | ~5.5 MB | RMW DSoftBus 实现库 |
| 符号链接 | `build_aarch64/lib/librmw_dsoftbus.so.0` | - | 指向 .0.1.0 |
| 符号链接 | `build_aarch64/lib/librmw_dsoftbus.so` | - | 指向 .0 |
| **测试程序** | `build_aarch64/bin/service_rpc_real_test` | ~65 KB | Service/Client RPC 测试 |

### 3.4 编译选项说明

**编译器**: OHOS Clang 15.0.4
```bash
CC = aarch64-unknown-linux-ohos-clang
CXX = aarch64-unknown-linux-ohos-clang++
```

**关键编译标志**:
```bash
-std=c++17              # C++17 标准
-fPIC                   # 位置无关代码（共享库必需）
-fvisibility=default    # 导出所有符号（重要！）
-O2                     # 优化级别2
-g                      # 保留调试信息
--sysroot=...           # 指定系统根目录
-Wl,-rpath,/system/lib64  # 运行时库搜索路径
```

**链接库**:
```bash
-lpthread   # POSIX 线程库
-ldl        # 动态加载库（dlopen）
-lc++       # C++ 标准库
```

---

## 4. 部署到设备

### 4.1 设备准备

**检查设备连接** (Windows PowerShell):

```powershell
# 列出所有连接的设备
hdc list targets

# 预期输出:
# ec29004133314d38433031a5544f3c00    device
# ec29004133314d38433031a751c63c00    device
```

**获取设备 Network ID** (用于跨设备通信):

```powershell
# 获取设备 Network ID
hdc -t ec29004133314d38433031a5544f3c00 shell "bm dump -n | grep network"

# 或使用自定义工具
hdc -t <device_id> shell "cd /data/test && ./get_network_id"
```

### 4.2 创建部署目录

**在设备上创建测试目录**:

```powershell
# Windows PowerShell
hdc -t ec29004133314d38433031a5544f3c00 shell "mkdir -p /data/test"
```

或 **通过 WSL** (推荐):

```bash
# WSL Ubuntu
DEVICE_ID="ec29004133314d38433031a5544f3c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mkdir -p /data/test'"
```

### 4.3 文件传输 (WSL → Windows → 设备)

**重要**: WSL 路径对 HDC 不可见，必须经过 `/mnt/c/` 中转！

#### 步骤 1: 复制到 Windows 临时目录

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus

# 创建 Windows 临时目录
mkdir -p /mnt/c/tmp/hdc_transfer

# 复制编译产物到 Windows 临时目录
cp build_aarch64/lib/librmw_dsoftbus.so.0.1.0 /mnt/c/tmp/hdc_transfer/
cp build_aarch64/bin/service_rpc_real_test /mnt/c/tmp/hdc_transfer/

# 设置可执行权限
chmod +x /mnt/c/tmp/hdc_transfer/service_rpc_real_test
```

#### 步骤 2: 使用 HDC 传输到设备

```bash
# 获取设备 ID
DEVICE_ID=$(powershell.exe -NoProfile -Command "hdc list targets" | grep device | head -1 | awk '{print $1}' | tr -d '\r\n')

echo "Deploying to device: $DEVICE_ID"

# 传输库文件
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0' '/data/test/'"

# 传输测试程序
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\service_rpc_real_test' '/data/test/'"

# 设置可执行权限
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'chmod +x /data/test/service_rpc_real_test'"
```

### 4.4 验证部署

```bash
# 检查文件是否存在
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ls -lh /data/test/'"

# 预期输出:
# -rwxr-xr-x 1 root root 5.4M Jan 15 05:06 librmw_dsoftbus.so.0.1.0
# -rwxr-xr-x 1 root root  65K Jan 15 05:06 service_rpc_real_test
```

### 4.5 自动化部署脚本

创建 `deploy_to_device.sh`:

```bash
#!/bin/bash
# 自动化部署脚本

set -e

DEVICE_ID="${1:-ec29004133314d38433031a5544f3c00}"
BUILD_DIR="build_aarch64"
TEMP_DIR="/mnt/c/tmp/hdc_transfer"
DEVICE_DIR="/data/test"

echo "=== 部署到设备 $DEVICE_ID ==="

# 1. 复制到 Windows 临时目录
echo "[1/3] 复制文件到 Windows 临时目录..."
mkdir -p "$TEMP_DIR"
cp "$BUILD_DIR/lib/librmw_dsoftbus.so.0.1.0" "$TEMP_DIR/"
cp "$BUILD_DIR/bin/service_rpc_real_test" "$TEMP_DIR/"
chmod +x "$TEMP_DIR/service_rpc_real_test"

# 2. 传输到设备
echo "[2/3] 传输文件到设备..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0' '$DEVICE_DIR/'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\hdc_transfer\service_rpc_real_test' '$DEVICE_DIR/'"

# 3. 设置权限
echo "[3/3] 设置文件权限..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'chmod +x $DEVICE_DIR/service_rpc_real_test'"

# 4. 验证
echo "=== 部署完成 ==="
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ls -lh $DEVICE_DIR/'"
```

**使用方法**:

```bash
chmod +x deploy_to_device.sh
./deploy_to_device.sh <device_id>
```

---

## 5. 运行测试

### 5.1 单设备功能测试

**测试 1: 验证库加载和权限配置**

```bash
DEVICE_ID="ec29004133314d38433031a5544f3c00"

# 运行服务端（监听模式）
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./service_rpc_real_test service'"
```

**预期输出**:

```
[NativeToken API] ✅ AVAILABLE
[rmw_dsoftbus] InitializeNativeToken: acquired tokenId=671437365
[rmw_dsoftbus] InitializeNativeToken: SetSelfTokenID() succeeded
[rmw_dsoftbus] InitializeNativeToken: ReloadNativeTokenInfo() succeeded

[SoftBus Shim] Successfully loaded /system/lib64/platformsdk/libsoftbus_client.z.so
[SoftBus Shim] Loaded symbol: GetLocalNodeDeviceInfo
[SoftBus Shim] Loaded symbol: CreateSessionServer
[SoftBus Shim] Loaded symbol: OpenSession
[SoftBus Shim] Loaded symbol: SendBytes

[SERVER] MyNetworkId: ce4d74479be13baf6014ae79765f21817820131812980a16bf0564609463f4f0

CreateSessionServer# ok: ret=0  ✅

[SERVER] Waiting for client connections...
```

**关键成功指标**:
- ✅ NativeToken API 可用
- ✅ Token ID 获取成功 (非 0)
- ✅ DSoftBus 库加载成功 (`libsoftbus_client.z.so`)
- ✅ CreateSessionServer 返回 0

### 5.2 跨设备 RPC 测试

**前置条件**: 需要 2 台 rk3588s 设备

**设备配置**:
```bash
DEVICE1_ID="ec29004133314d38433031a5544f3c00"  # 服务端
DEVICE2_ID="ec29004133314d38433031a751c63c00"  # 客户端
DEVICE1_NETWORK_ID="ce4d74479be13baf6014ae79765f21817820131812980a16bf0564609463f4f0"
```

#### 步骤 1: 启动服务端 (设备 1)

**终端 1**:
```bash
powershell.exe -NoProfile -Command "hdc -t $DEVICE1_ID shell 'cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./service_rpc_real_test service'"
```

**等待输出**:
```
[SERVER] Waiting for client connections...
```

#### 步骤 2: 启动客户端 (设备 2)

**终端 2**:
```bash
powershell.exe -NoProfile -Command "hdc -t $DEVICE2_ID shell 'cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./service_rpc_real_test client $DEVICE1_NETWORK_ID'"
```

#### 预期交互流程

**客户端输出**:
```
[CLIENT] Target NetworkId: ce4d74479be13baf6014ae79765f21817820131812980a16bf0564609463f4f0

OpenSession to ce4d7447... succeeded: session_id=1  ✅

[CLIENT] Sending REQUEST: id=12345, data="Hello Service"
REQUEST sent: ret=26  ✅

[CLIENT] Received RESPONSE: id=12345, status=0, data="Hello Client"
✅ SUCCESS: Client RPC test passed!
```

**服务端输出**:
```
OnSessionOpened: sessionId=1, result=0  ✅

[SERVER] Received REQUEST: id=12345, data="Hello Service"
[SERVER] Sending RESPONSE: id=12345, status=0, data="Hello Client"
RESPONSE sent: ret=26  ✅
```

**验收标准**:
- ✅ OpenSession 返回有效 session_id (> 0)
- ✅ OnSessionOpened 回调触发 (result=0)
- ✅ 客户端成功发送 REQUEST
- ✅ 服务端成功接收 REQUEST
- ✅ 服务端成功发送 RESPONSE
- ✅ 客户端成功接收 RESPONSE

### 5.3 查看系统日志

**实时查看 hilog**:

```bash
# 过滤 DSoftBus 相关日志
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'hilog | grep -E \"(SoftBus|rmw_dsoftbus|CreateSession|OpenSession)\"'"
```

**查看 Session 创建日志**:

```bash
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'hilog | grep CreateSessionServer'"
```

**预期关键日志**:
```
I C05740/TransSdk: [client_trans_session_service.c:141] CreateSessionServer# ok: ret=0
I C05740/TransSdk: [client_trans_session_service.c:113] CreateSessionServer# pkgName=com.huawei.ros2_rmw_dsoftbus
I C05743/TransCtrl: [trans_session_manager.c:171] TransSessionServerAddItem# add sessionName = com.huawei.ros2_rmw_dsoftbus.test
```

---

## 6. 故障排查

### 6.1 编译错误

#### 问题 1: 找不到 Clang 编译器

**错误信息**:
```
[ERROR] Clang compiler not found: /home/jiusi/M-DDS/openharmony_prebuilts/...
```

**解决方案**:
```bash
# 检查工具链路径
ls /home/jiusi/M-DDS/openharmony_prebuilts/

# 确保路径正确
vim cross_compile_ohos.sh
# 修改 TOOLCHAIN_ROOT 变量
```

#### 问题 2: Sysroot 找不到

**错误信息**:
```
fatal error: 'features.h' file not found
```

**解决方案**:
```bash
# 检查 sysroot 路径
ls /home/jiusi/M-DDS/openharmony_prebuilts/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/aarch64-linux-gnu/libc/

# 确保包含 /usr/include 目录
ls /home/jiusi/M-DDS/openharmony_prebuilts/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/aarch64-linux-gnu/libc/usr/include/features.h
```

#### 问题 3: 链接错误 - 未定义的符号

**错误信息**:
```
ld.lld: error: undefined symbol: std::__h::mutex::lock()
```

**原因**: 未链接 C++ 标准库

**解决方案**:
```bash
# 在链接命令中添加 -lc++
${CXX} ${LDFLAGS} ... -lc++ -lpthread -ldl
```

### 6.2 部署错误

#### 问题 1: HDC 连接失败

**错误信息**:
```
[Fail][E000004]:The communication channel is being established
```

**解决方案**:
```powershell
# 1. 检查 USB 连接
# 2. 重启 HDC 服务
hdc kill
hdc start

# 3. 重新连接设备
hdc list targets
```

#### 问题 2: 文件传输失败 - 路径错误

**错误信息**:
```
[Fail][E000002]:File send failed
```

**原因**: WSL 路径在 Windows HDC 中不可见

**解决方案**:
```bash
# ❌ 错误方式
hdc file send /home/jiusi/M-DDS/rmw_dsoftbus/build_aarch64/lib/librmw_dsoftbus.so.0.1.0 /data/test/

# ✅ 正确方式（经过 /mnt/c 中转）
cp build_aarch64/lib/librmw_dsoftbus.so.0.1.0 /mnt/c/tmp/hdc_transfer/
powershell.exe -Command "hdc file send 'C:\tmp\hdc_transfer\librmw_dsoftbus.so.0.1.0' '/data/test/'"
```

### 6.3 运行时错误

#### 问题 1: CreateSessionServer 失败 (-426442706)

**错误输出**:
```
CreateSessionServer failed: -426442706
```

**原因**:
1. DSoftBus 服务未响应
2. 权限配置错误
3. NativeToken 注入失败

**解决方案**:

```bash
# 1. 检查 DSoftBus 服务状态
powershell.exe -Command "hdc -t $DEVICE_ID shell 'ps -ef | grep softbus'"

# 2. 重启 DSoftBus 服务
powershell.exe -Command "hdc -t $DEVICE_ID shell 'killall softbus_server && softbus_server &'"

# 3. 检查 NativeToken 日志
# 确保看到:
# [rmw_dsoftbus] InitializeNativeToken: acquired tokenId=<non-zero>
# [rmw_dsoftbus] InitializeNativeToken: SetSelfTokenID() succeeded

# 4. 验证 APL 配置
# 检查 src/native_token.cpp:301
# 必须是: .aplStr = "system_basic"  // 不是 "system_core"!
```

#### 问题 2: OpenSession 失败

**错误输出**:
```
OpenSession failed: -1
```

**原因**:
1. Peer Network ID 错误
2. 设备不在同一网络
3. CreateSessionServer 未成功

**解决方案**:

```bash
# 1. 验证 Network ID
powershell.exe -Command "hdc -t $DEVICE_ID shell 'bm dump -n | grep network'"

# 2. 检查设备在线状态
powershell.exe -Command "hdc -t $DEVICE_ID shell './get_all_devices'"

# 3. 确保服务端先启动
# 先启动 service, 再启动 client
```

#### 问题 3: 库加载失败

**错误输出**:
```
error while loading shared libraries: librmw_dsoftbus.so.0: cannot open shared object file
```

**原因**: 库搜索路径未设置

**解决方案**:

```bash
# ❌ 错误方式
./service_rpc_real_test service

# ✅ 正确方式（设置 LD_LIBRARY_PATH）
LD_LIBRARY_PATH=/system/lib64:/data/test ./service_rpc_real_test service

# 或将库复制到系统目录
powershell.exe -Command "hdc -t $DEVICE_ID shell 'cp /data/test/librmw_dsoftbus.so.0.1.0 /system/lib64/'"
powershell.exe -Command "hdc -t $DEVICE_ID shell 'ln -sf /system/lib64/librmw_dsoftbus.so.0.1.0 /system/lib64/librmw_dsoftbus.so.0'"
```

#### 问题 4: DSoftBus 库加载失败

**错误输出**:
```
[SoftBus Shim] Failed to load /system/lib64/platformsdk/libsoftbus_client.z.so
```

**原因**: DSoftBus 客户端库不存在或路径错误

**解决方案**:

```bash
# 检查 DSoftBus 库是否存在
powershell.exe -Command "hdc -t $DEVICE_ID shell 'ls -l /system/lib64/platformsdk/libsoftbus_client.z.so'"

# 如果不存在，可能是 KaihongOS 版本问题
# 尝试搜索:
powershell.exe -Command "hdc -t $DEVICE_ID shell 'find /system -name \"*softbus*.so\"'"

# 更新 dlopen 路径 (在 src/dsoftbus_stubs.cpp 或测试代码中)
```

---

## 7. 高级配置

### 7.1 权限配置详解

**关键文件**: `src/native_token.cpp` (lines 280-304)

**正确配置** (基于 Phase 2 成功验证):

```cpp
const char* perms[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER"
    // 不需要 ACCESS_SERVICE_DM
};

NativeTokenInfoParams params = {
    .dcapsNum = 0,
    .permsNum = 2,      // 仅 2 个权限
    .aclsNum = 0,       // 不需要 ACLs
    .dcaps = nullptr,
    .perms = perms,
    .acls = nullptr,    // 不需要 ACLs
    .processName = process_name,
    .aplStr = "system_basic",  // 必须是 system_basic！
};
```

**错误配置示例**:

```cpp
// ❌ 错误 1: APL 级别错误
.aplStr = "system_core",  // 应该是 "system_basic"

// ❌ 错误 2: 额外权限
const char* perms[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC",
    "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER",
    "ohos.permission.ACCESS_SERVICE_DM"  // 不需要
};

// ❌ 错误 3: 额外 ACLs
const char* acls[] = {
    "ohos.permission.DISTRIBUTED_DATASYNC"  // 不需要
};
.aclsNum = 1,
.acls = acls,
```

**验证方法**:

```bash
# 查看代码中的 APL 配置
grep -A5 "aplStr" src/native_token.cpp

# 确保输出包含:
# .aplStr = "system_basic",
```

### 7.2 编译优化选项

**调试版本** (保留完整调试信息):

```bash
# 修改 cross_compile_ohos.sh
CFLAGS="-O0 -g3 -Wall -Wextra -fPIC --sysroot=${SYSROOT}"
CXXFLAGS="${CFLAGS} -std=c++17 -fvisibility=default"
```

**发布版本** (优化性能):

```bash
CFLAGS="-O3 -DNDEBUG -fPIC --sysroot=${SYSROOT}"
CXXFLAGS="${CFLAGS} -std=c++17 -fvisibility=default"
# 移除 -g 标志
```

**最小体积版本**:

```bash
CFLAGS="-Os -fPIC --sysroot=${SYSROOT}"
LDFLAGS="${LDFLAGS} -Wl,--strip-all"  # 去除所有符号
```

### 7.3 多设备批量部署

创建 `deploy_multi_devices.sh`:

```bash
#!/bin/bash
# 批量部署到多台设备

DEVICES=(
    "ec29004133314d38433031a5544f3c00"
    "ec29004133314d38433031a751c63c00"
    "ec29004133314d38433031a522413c00"
)

for DEVICE in "${DEVICES[@]}"; do
    echo "=== 部署到设备 $DEVICE ==="
    ./deploy_to_device.sh "$DEVICE"
    echo ""
done

echo "✅ 所有设备部署完成"
```

### 7.4 GN 构建系统集成 (备用)

如果需要集成到 OpenHarmony 源码树编译:

**文件**: `BUILD.gn`

```gn
import("//build/ohos.gni")

ohos_shared_library("rmw_dsoftbus") {
  sources = [
    "src/rmw_allocation.cpp",
    "src/rmw_client.cpp",
    # ... (完整源文件列表)
  ]

  include_dirs = [
    "include",
    "//foundation/communication/dsoftbus/interfaces/kits/transport",
  ]

  deps = [
    "//foundation/communication/dsoftbus/sdk:softbus_client",
  ]

  external_deps = [
    "access_token:libaccesstoken_sdk",
    "access_token:libnativetoken",
    "access_token:libtoken_setproc",
  ]

  part_name = "ros2_rmw_dsoftbus"
  subsystem_name = "ros2"
}
```

**编译命令**:

```bash
# 在 OpenHarmony 源码根目录
./build.sh --product-name rk3588 --ccache --build-target ros2_rmw_dsoftbus
```

---

## 附录 A: 快速参考

### 常用命令速查表

| 任务 | 命令 |
|------|------|
| **编译** | `./cross_compile_ohos.sh all` |
| **清理** | `./cross_compile_ohos.sh clean` |
| **部署** | `./deploy_to_device.sh <device_id>` |
| **运行服务端** | `hdc -t <id> shell 'cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./service_rpc_real_test service'` |
| **运行客户端** | `hdc -t <id> shell 'cd /data/test && LD_LIBRARY_PATH=/system/lib64 ./service_rpc_real_test client <peer_id>'` |
| **查看日志** | `hdc -t <id> shell 'hilog \| grep SoftBus'` |
| **列出设备** | `powershell.exe -Command "hdc list targets"` |
| **检查文件** | `hdc -t <id> shell 'ls -lh /data/test/'` |

### 关键文件路径

| 文件 | 路径 |
|------|------|
| 交叉编译脚本 | `cross_compile_ohos.sh` |
| 编译产物（库） | `build_aarch64/lib/librmw_dsoftbus.so.0.1.0` |
| 编译产物（测试） | `build_aarch64/bin/service_rpc_real_test` |
| 权限配置代码 | `src/native_token.cpp` lines 280-304 |
| DSoftBus Stubs | `src/dsoftbus_stubs.cpp` |
| GN 构建配置 | `BUILD.gn` |

### 设备路径

| 目录/文件 | 路径 | 说明 |
|----------|------|------|
| 部署目录 | `/data/test/` | 测试程序和库 |
| 系统库目录 | `/system/lib64/` | 系统共享库 |
| DSoftBus 库 | `/system/lib64/platformsdk/libsoftbus_client.z.so` | DSoftBus 客户端库 |
| 日志 | `hilog` | 系统日志工具 |

---

## 附录 B: 版本历史

| 版本 | 日期 | 变更 |
|------|------|------|
| 1.0 | 2026-01-15 | 初始版本，完整部署教程 |
| | | - 基于 cross_compile_ohos.sh 脚本 |
| | | - 包含权限配置修复 (system_basic) |
| | | - 添加 WSL → Windows → 设备路径说明 |
| | | - 添加故障排查章节 |

---

## 附录 C: 参考文档

### 内部文档

- `SESSION_SUCCESS_HISTORY.md` - Phase 2 成功案例汇总
- `PERMISSION_AUDIT_REPORT_2026-01-15.md` - 权限配置审核
- `PERMISSION_FIX_VERIFICATION_2026-01-15.md` - 权限修复验证
- `.claude/CODE_GENERATION_LOG.md` - 代码生成记录
- `test/PHASE2_CROSS_DEVICE_TEST_RESULTS.md` - Phase 2 测试结果

### 外部参考

- [OpenHarmony 官方文档](https://docs.openharmony.cn/)
- [DSoftBus 开发指南](https://gitee.com/openharmony/communication_dsoftbus)
- [ROS2 官方文档](https://docs.ros.org/en/humble/)
- [GCC Linaro 工具链](https://releases.linaro.org/components/toolchain/)

---

**文档创建**: 2026-01-15
**最后更新**: 2026-01-15
**维护者**: Claude Code
**状态**: ✅ 已验证（基于 Phase 2 成功案例）
