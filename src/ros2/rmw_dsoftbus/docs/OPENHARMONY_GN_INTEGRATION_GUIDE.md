---
doc_id: guide_gn_integration
category: rmw_dsoftbus设计文档
title: rmw_dsoftbus OpenHarmony GN 集成指南
description: 将 rmw_dsoftbus 集成到 OpenHarmony 源码树的详细步骤和 GN 配置方案
priority: HIGH
last_updated: 2026-01-06
tags: [GN集成, OpenHarmony, AccessToken, 系统集成]
use_cases:
  - 理解 rmw_dsoftbus 与 OpenHarmony 系统的集成方式
  - 学习 GN 配置和编译集成
  - 解决 AccessToken 注册问题
---

# rmw_dsoftbus OpenHarmony GN集成指南

**目标**: 将rmw_dsoftbus集成到OpenHarmony源码树，获得正确的AccessToken注册
**预期成功率**: 95%
**预计时间**: 1-2天

---

## 📁 第一步：目录结构规划

### 推荐位置
```
/home/jiusi/M-DDS/OpenHarmony/foundation/communication/rmw_dsoftbus/
```

### 完整目录结构
```
foundation/communication/rmw_dsoftbus/
├── BUILD.gn                    # 主构建文件
├── bundle.json                 # 组件元数据
├── README.md                   # 组件说明
├── README_zh.md                # 中文说明
├── rmw_dsoftbus.gni            # GN公共配置
│
├── include/                    # 公开头文件
│   └── rmw_dsoftbus/
│       ├── rmw_dsoftbus.h
│       ├── types.h
│       ├── discovery_manager.h
│       ├── graph_cache.h
│       └── session_manager.h
│
├── src/                        # 实现代码
│   ├── rmw_init.cpp
│   ├── rmw_node.cpp
│   ├── rmw_publisher.cpp
│   ├── rmw_subscription.cpp
│   ├── discovery_manager.cpp
│   ├── graph_cache.cpp
│   ├── session_manager.cpp
│   └── native_token.cpp
│
├── interfaces/                 # 内部接口（可选）
│   └── inner_api/
│       └── rmw_dsoftbus_inner.h
│
├── sa_profile/                 # SystemAbility配置（如作为SA）
│   ├── 9999.json              # SA ID配置
│   └── rmw_discovery.cfg      # init配置
│
├── test/                       # 测试代码
│   ├── unittest/
│   │   └── BUILD.gn
│   └── systemtest/
│       ├── BUILD.gn
│       └── discovery_test.cpp
│
└── services/                   # 系统服务（daemon）
    ├── BUILD.gn
    └── rmw_discovery_daemon/
        ├── src/
        │   └── main.cpp
        └── include/
            └── daemon.h
```

---

## 📝 第二步：核心文件编写

### 2.1 主BUILD.gn

**位置**: `foundation/communication/rmw_dsoftbus/BUILD.gn`

```gn
# Copyright (c) 2026 Kaihong. All rights reserved.

import("//build/ohos.gni")
import("rmw_dsoftbus.gni")

###############################################
# librmw_dsoftbus - 核心共享库
###############################################

ohos_shared_library("librmw_dsoftbus") {
  sources = [
    # Core RMW API
    "src/rmw_init.cpp",
    "src/rmw_node.cpp",
    "src/rmw_publisher.cpp",
    "src/rmw_subscription.cpp",
    "src/rmw_wait.cpp",
    "src/rmw_service.cpp",
    "src/rmw_client.cpp",
    "src/rmw_guard_condition.cpp",
    "src/rmw_get_info.cpp",
    "src/rmw_event.cpp",
    "src/rmw_qos.cpp",
    "src/rmw_serialize.cpp",

    # Session & Discovery
    "src/session_manager.cpp",
    "src/discovery_manager.cpp",
    "src/graph_cache.cpp",
    "src/service_client_manager.cpp",

    # Serialization
    "src/cdr_serializer.cpp",
    "src/qos_mapper.cpp",
    "src/rmw_typesupport_serializer.cpp",
    "src/service_typesupport_serializer.cpp",

    # Native Token (关键：系统构建会自动处理)
    "src/native_token.cpp",
  ]

  include_dirs = [
    "include",
    "//foundation/communication/dsoftbus/interfaces/kits/transport",
    "//foundation/communication/dsoftbus/interfaces/kits/discovery",
    "//foundation/communication/dsoftbus/interfaces/kits/common",
  ]

  public_configs = [ ":rmw_dsoftbus_public_config" ]

  deps = [
    "//foundation/communication/dsoftbus/sdk:softbus_client",
  ]

  external_deps = [
    "access_token:libaccesstoken_sdk",      # 关键：AccessToken注册
    "access_token:libnativetoken",          # 关键：NativeToken
    "access_token:libtoken_setproc",        # 关键：Token设置
    "c_utils:utils",
    "hilog:libhilog",
    "ipc:ipc_core",
  ]

  # 关键配置
  install_enable = true
  install_images = [ "system" ]
  module_install_dir = "lib64"

  part_name = "rmw_dsoftbus"
  subsystem_name = "communication"
}

config("rmw_dsoftbus_public_config") {
  include_dirs = [ "include" ]
}

###############################################
# rmw_discovery_daemon - 系统服务
###############################################

ohos_executable("rmw_discovery_daemon") {
  sources = [
    "services/rmw_discovery_daemon/src/main.cpp",
  ]

  include_dirs = [
    "include",
    "services/rmw_discovery_daemon/include",
  ]

  deps = [
    ":librmw_dsoftbus",
  ]

  external_deps = [
    "access_token:libaccesstoken_sdk",
    "access_token:libnativetoken",
    "access_token:libtoken_setproc",
    "hilog:libhilog",
    "init:libbegetutil",
  ]

  install_enable = true
  install_images = [ "system" ]
  module_install_dir = "bin"

  part_name = "rmw_dsoftbus"
  subsystem_name = "communication"
}

###############################################
# 测试目标
###############################################

group("rmw_dsoftbus_test") {
  testonly = true
  deps = [
    "test/unittest:unittest",
    "test/systemtest:systemtest",
  ]
}
```

### 2.2 rmw_dsoftbus.gni

**位置**: `foundation/communication/rmw_dsoftbus/rmw_dsoftbus.gni`

```gn
# rmw_dsoftbus common configurations

rmw_dsoftbus_path = "//foundation/communication/rmw_dsoftbus"

rmw_dsoftbus_include_dirs = [
  "${rmw_dsoftbus_path}/include",
]

rmw_dsoftbus_cflags_cc = [
  "-std=c++17",
  "-Wall",
  "-Wextra",
  "-fPIC",
]
```

### 2.3 bundle.json

**位置**: `foundation/communication/rmw_dsoftbus/bundle.json`

```json
{
  "name": "@ohos/rmw_dsoftbus",
  "description": "ROS2 RMW implementation over OpenHarmony dsoftbus",
  "version": "4.0",
  "license": "Apache License 2.0",
  "publishAs": "code-segment",
  "segment": {
    "destPath": "foundation/communication/rmw_dsoftbus"
  },
  "dirs": {},
  "scripts": {},
  "component": {
    "name": "rmw_dsoftbus",
    "subsystem": "communication",
    "syscap": [],
    "features": [],
    "adapted_system_type": [ "standard" ],
    "rom": "2000KB",
    "ram": "~4096KB",
    "deps": {
      "components": [
        "dsoftbus",
        "access_token",
        "c_utils",
        "hilog",
        "ipc"
      ],
      "third_party": []
    },
    "build": {
      "sub_component": [
        "//foundation/communication/rmw_dsoftbus:librmw_dsoftbus",
        "//foundation/communication/rmw_dsoftbus:rmw_discovery_daemon"
      ],
      "inner_kits": [
        {
          "name": "//foundation/communication/rmw_dsoftbus:librmw_dsoftbus",
          "header": {
            "header_files": [
              "rmw_dsoftbus.h",
              "types.h"
            ],
            "header_base": "//foundation/communication/rmw_dsoftbus/include"
          }
        }
      ],
      "test": [
        "//foundation/communication/rmw_dsoftbus:rmw_dsoftbus_test"
      ]
    }
  }
}
```

---

## 🔑 第三步：Native Token注册（关键）

### 3.1 修改 src/native_token.cpp

**当前代码**（使用ioctl，不被系统识别）：
```cpp
void NativeToken::initialize() {
  uint64_t token_id = 671361873;  // 硬编码
  int ret = SetSelfTokenID(token_id);
  // ioctl写入，但AccessTokenKit数据库不认
}
```

**修改为**（使用AccessTokenKit正确注册）：
```cpp
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

using namespace OHOS::Security::AccessToken;

void NativeToken::initialize() {
  // 定义Native Token参数
  NativeTokenInfoParams infoParams = {
    .dcapsNum = 0,
    .permsNum = 0,
    .aclsNum = 0,
    .dcaps = nullptr,
    .perms = nullptr,
    .acls = nullptr,
    .processName = "rmw_discovery_daemon",  // 进程名
    .aplStr = "system_core",                 // APL等级
  };

  // 获取Token ID（系统会在AccessTokenKit数据库中注册）
  uint64_t token_id = GetAccessTokenId(&infoParams);

  // 设置到当前进程
  int ret = SetSelfTokenID(token_id);

  if (ret == 0) {
    // 验证注册成功
    uint64_t verify_token = GetSelfTokenID();
    fprintf(stderr, "[NativeToken] Registered token_id=%llu (verify=%llu)\n",
            token_id, verify_token);
  } else {
    fprintf(stderr, "[NativeToken] Failed to set token: %d\n", ret);
  }
}
```

**关键点**：
- `GetAccessTokenId()` 会在系统AccessTokenKit数据库中注册token
- `processName` 必须与可执行文件名一致
- `aplStr = "system_core"` 表示系统核心应用等级

---

## 🚀 第四步：系统集成配置

### 4.1 init配置文件

**位置**: `foundation/communication/rmw_dsoftbus/sa_profile/rmw_discovery.cfg`

```json
{
  "services": [
    {
      "name": "rmw_discovery_daemon",
      "path": ["/system/bin/rmw_discovery_daemon"],
      "uid": "softbus",
      "gid": ["softbus", "shell"],
      "secon": "u:r:rmw_discovery:s0",
      "permission": [
        "ohos.permission.DISTRIBUTED_DATASYNC"
      ],
      "ondemand": true,
      "start-mode": "condition",
      "once": true
    }
  ]
}
```

### 4.2 SELinux策略

**位置**: `base/security/selinux_adapter/sepolicy/ohos_policy/communication/rmw_dsoftbus/`

**文件**: `rmw_discovery.te`
```selinux
type rmw_discovery, sadomain, domain;
type rmw_discovery_exec, exec_attr, file_attr, system_file_attr;

# 允许访问softbus
allow rmw_discovery softbus_server:binder { call transfer };
allow rmw_discovery softbus_server:unix_stream_socket { connectto };

# 允许TCP通信
allow rmw_discovery self:tcp_socket { create connect read write shutdown };
allow rmw_discovery softbus_server:tcp_socket { read write shutdown };

# 允许访问配置文件
allow rmw_discovery softbus_trans_permission_file:file { read open };

# 允许日志
allow rmw_discovery hilog_param:file { read open };
```

---

## 🔧 第五步：修改全局配置

### 5.1 添加到subsystem配置

**文件**: `build/subsystem_config.json`

找到 `"communication"` 子系统，添加：
```json
{
  "subsystem": "communication",
  "components": [
    {
      "component": "dsoftbus",
      "features": []
    },
    {
      "component": "rmw_dsoftbus",        // 新增
      "features": []
    }
  ]
}
```

### 5.2 添加到产品配置

**文件**: `productdefine/common/products/khs_3588s_sbc.json`

在 `"subsystems"` 数组中找到 `"communication"`，添加：
```json
{
  "subsystem": "communication",
  "components": [
    {
      "component": "dsoftbus",
      "features": []
    },
    {
      "component": "rmw_dsoftbus",        // 新增
      "features": []
    }
  ]
}
```

---

## 🏗️ 第六步：编译与部署

### 6.1 编译单个组件
```bash
cd /home/jiusi/M-DDS/OpenHarmony

# 编译rmw_dsoftbus（使用正确的产品名）
./build.sh --product-name khs_3588s_sbc --build-target rmw_dsoftbus --ccache

# 输出路径
ls -lh out/khs_3588s_sbc/communication/rmw_dsoftbus/
# librmw_dsoftbus.so
# rmw_discovery_daemon
```

### 6.2 编译完整镜像
```bash
# 完整编译（包含rmw_dsoftbus）
./build.sh --product-name khs_3588s_sbc --ccache

# 输出
ls -lh out/khs_3588s_sbc/packages/phone/images/
# system.img
# vendor.img
# userdata.img
```

### 6.3 刷写到设备（必须）

**⚠️ 重要：必须刷写system.img，不能只用hdc file send**

**原因**：
- AccessToken数据库是在系统构建+启动阶段初始化的
- ohos_executable会将组件写入system image的组件描述
- 只有通过刷写，系统才能"认识"rmw_discovery_daemon并注册token
- hdc file send只是拷贝文件，**不会触发token注册**

```bash
# 必须：刷写system分区
fastboot flash system out/khs_3588s_sbc/packages/phone/images/system.img
fastboot reboot

# 或者：刷写完整镜像（更安全）
cd out/khs_3588s_sbc/packages/phone/images/
fastboot flash system system.img
fastboot flash vendor vendor.img
fastboot flash userdata userdata.img
fastboot reboot
```

**验证系统是否识别组件**：
```bash
# 重启后检查
hdc shell "ps -Z | grep rmw_discovery"
# 应该看到正确的SELinux上下文: u:r:rmw_discovery:s0

# 检查init是否启动了daemon
hdc shell "ps -ef | grep rmw_discovery_daemon"
```

---

## ✅ 第七步：验证Token注册

### 7.1 启动daemon
```bash
hdc shell "rmw_discovery_daemon &"
```

### 7.2 检查Token注册
```bash
# 查看进程Token
hdc shell "ps -Z | grep rmw_discovery"
# 应该显示: u:r:rmw_discovery:s0 而不是 u:r:su:s0

# 查看Token ID
hdc shell "cat /proc/$(pidof rmw_discovery_daemon)/attr/current"
# 应该显示正确的token context
```

### 7.3 验证权限检查
```bash
# 运行测试程序
hdc shell "/data/local/tmp/discovery_final_test"

# 应该看到：
# [NativeToken] Registered token_id=XXX (verify=XXX)  ✅
# [DiscoveryManager] SessionServer created: id=0      ✅
# [Discovery Callback] Session opened successfully    ✅ (关键)
```

---

## 🎯 成功标志

| 检查项 | 预期结果 | 当前状态（方案1） | 方案2预期 |
|-------|---------|----------------|----------|
| Token注册 | AccessTokenKit数据库有记录 | ❌ ioctl硬写 | ✅ 系统注册 |
| CalcPermType() | 返回SYSTEM_APP | ❌ 返回异常 | ✅ 正确返回 |
| SessionServer创建 | 成功 | ✅ 成功 | ✅ 成功 |
| Session建立 | OnSessionOpened回调 | ❌ failed -426115004 | ✅ 成功 |
| **rx消息** | **rx > 0** | **❌ rx=0** | **✅ rx>0** |
| SELinux上下文 | u:r:rmw_discovery:s0 | ❌ u:r:su:s0 | ✅ 正确domain |

---

## 📋 迁移检查清单

### 代码迁移
- [ ] 复制 `src/`, `include/` 到新位置
- [ ] 创建 `BUILD.gn`（使用ohos模板）
- [ ] 创建 `bundle.json`
- [ ] 修改 `native_token.cpp`（使用AccessTokenKit）

### 系统配置
- [ ] 添加到 `subsystem_config.json`
- [ ] 添加到产品配置 `rk3588.json`
- [ ] 创建 init配置 `.cfg`
- [ ] 创建 SELinux策略 `.te`

### 编译验证
- [ ] 单组件编译通过
- [ ] 完整镜像编译通过
- [ ] 刷写到设备成功

### 功能验证
- [ ] daemon启动成功
- [ ] Token注册验证（SELinux上下文正确）
- [ ] SessionServer创建成功
- [ ] **Session建立成功（关键）**
- [ ] **rx > 0（最终验收）**

---

## 🚨 常见问题与解决

### Q1: 编译时找不到 `access_token` 模块
**A**: 确认 `external_deps` 写法正确：
```gn
external_deps = [
  "access_token:libaccesstoken_sdk",  # 注意冒号和库名
]
```

### Q2: init启动daemon失败
**A**: 检查 `.cfg` 文件：
- `uid/gid` 是否正确
- `path` 是否匹配可执行文件路径
- SELinux上下文是否定义

### Q3: Token注册成功但Session依然失败
**A**: 检查权限JSON中的 `PKG_NAME`：
- 必须与 `NativeTokenInfoParams.processName` 一致
- 建议使用可执行文件名：`rmw_discovery_daemon`

---

## 📚 参考资料

- OpenHarmony构建系统文档: `docs/zh-cn/device-dev/subsystems/subsys-build-all.md`
- AccessToken开发指南: `docs/zh-cn/application-dev/security/accesstoken-guidelines.md`
- dsoftbus集成示例: `foundation/communication/dsoftbus/`
- SELinux策略编写: `base/security/selinux_adapter/README.md`

---

**预计完成时间**: 1-2天（包括编译、刷写、测试）
**成功率**: 95%（遵循官方集成流程）
**关键收益**: 获得正确的AccessToken注册，Phase 2真正完成

---

**下一步行动**:
1. 创建目录结构
2. 编写BUILD.gn和bundle.json
3. 修改native_token.cpp
4. 编译验证
5. 刷写测试
6. **验收标准: rx > 0**
