# ROS2 OpenHarmony 移植设计文档

## 文档信息

- **版本**: 2.0
- **日期**: 2025-12-31
- **目标**: 将 ROS2 Jazzy 完整栈移植到 OpenHarmony (KaihongOS)
- **目标平台**: rk3588s (aarch64-linux-ohos)
- **构建系统**: GN (独立构建)
- **DDS实现**: FastDDS (eProsima)

---

## 1. 项目概述

### 1.1 目标

1. **完整ROS2栈移植**: rcl, rclcpp, rosidl 等核心包
2. **FastDDS移植**: 完整DDS协议栈，支持与标准ROS2互通
3. **独立GN构建**: 可单独编译部署，使用OHOS工具链

### 1.2 工作范围划分

| 工作内容 | 负责方 | 说明 |
|----------|--------|------|
| **ROS2基础库移植** | 本项目 | rcutils, rcpputils, rosidl, rcl, rclcpp |
| **FastDDS移植** | 本项目 | 完整DDS协议栈 |
| **rmw_fastrtps移植** | 本项目 | FastDDS的RMW适配层 |
| dsoftbus/rmw_dsoftbus | 另一团队 | OpenHarmony原生通信层 |

### 1.3 FastDDS功能需求

本项目需要移植的FastDDS功能模块：

| 功能模块 | 说明 | 优先级 |
|----------|------|--------|
| **RTPS协议** | Real-Time Publish-Subscribe协议，DDS底层传输 | P0 |
| **DDS协议** | OMG DDS规范核心实现 | P0 |
| **DDS-XTYPES** | 可扩展类型系统，动态类型支持 | P0 |
| **DCPS** | Data-Centric Publish-Subscribe API | P0 |
| **IDL接口** | 接口定义语言支持 | P0 |
| **Fast-CDR** | CDR序列化库 | P0 |
| **DDS Security** | DDS安全规范 (认证/加密/访问控制) | P1 |
| **DDS RPC** | 远程过程调用框架 | P1 |
| **DLRL** | Data Local Reconstruction Layer | P2 |
| **DDS-WEB** | Web服务接口 | P2 |
| **DDS OPC UA** | OPC UA架构支持 | P2 |

---

## 2. 整体架构

### 2.1 分层架构图

```
┌─────────────────────────────────────────────────────────────┐
│                    应用层 (Demo Nodes)                       │
│  demo_nodes_cpp, talker/listener, service examples          │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                  rclcpp (C++17 客户端库)                      │
│  Node, Publisher, Subscriber, Service, Executor             │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────┐
│                     rcl (C11 核心库)                         │
│  rcl_node, rcl_publisher, rcl_subscription, rcl_wait        │
└─────────────────────────────────────────────────────────────┘
                              ↓
┌──────────────────────┬──────────────────────────────────────┐
│  rmw_implementation  │         rosidl 类型系统              │
│  (运行时选择器)        │  rosidl_runtime_c/cpp               │
│                      │  rosidl_typesupport_fastrtps_*       │
└──────────┬───────────┴──────────────────────────────────────┘
           ↓
┌──────────────────────────────────────────────────────────────┐
│              rmw_fastrtps_cpp / rmw_fastrtps_dynamic_cpp     │
│                    (FastDDS RMW 适配层)                       │
└──────────────────────────────────────────────────────────────┘
                              ↓
┌──────────────────────────────────────────────────────────────┐
│                      FastDDS (eProsima)                       │
│  ┌─────────────┬─────────────┬─────────────┬───────────────┐ │
│  │  DDS Core   │  RTPS协议    │  DDS-XTYPES │  DDS Security │ │
│  │  (DCPS API) │  (传输层)    │  (动态类型)  │  (安全认证)   │ │
│  └─────────────┴─────────────┴─────────────┴───────────────┘ │
│  ┌─────────────┬─────────────┬─────────────┬───────────────┐ │
│  │  Fast-CDR   │  DDS RPC    │   IDL编译器  │  Discovery   │ │
│  │  (序列化)   │  (RPC框架)   │             │  (服务发现)   │ │
│  └─────────────┴─────────────┴─────────────┴───────────────┘ │
└──────────────────────────────────────────────────────────────┘
                              ↓
┌──────────────────────────────────────────────────────────────┐
│                    网络传输层 (UDP/TCP/SHM)                   │
└──────────────────────────────────────────────────────────────┘
```

### 2.2 目录结构

```
/home/jiusi/M-DDS/
├── OpenHarmony/             # OpenHarmony源码和工具链
├── openharmony_prebuilts/   # 预编译工具链
├── ros2/                    # ROS2 Jazzy 源码
└── ohos_ros2/              # 新建：OHOS移植目录
    ├── BUILD.gn            # 顶层构建入口
    ├── bundle.json         # 组件配置
    ├── ohos.build          # 子系统配置
    ├── gn_templates/       # GN模板
    │   ├── ros2_library.gni
    │   ├── ros2_executable.gni
    │   └── rosidl_generator.gni
    ├── toolchain/          # 工具链配置
    │   └── aarch64-linux-ohos.gni
    ├── foundation/         # ROS2核心包
    │   ├── rcutils/
    │   ├── rcpputils/
    │   ├── rosidl/
    │   │   ├── rosidl_runtime_c/
    │   │   ├── rosidl_runtime_cpp/
    │   │   ├── rosidl_typesupport_interface/
    │   │   ├── rosidl_typesupport_c/
    │   │   ├── rosidl_typesupport_cpp/
    │   │   ├── rosidl_typesupport_introspection_c/
    │   │   ├── rosidl_typesupport_introspection_cpp/
    │   │   ├── rosidl_typesupport_fastrtps_c/
    │   │   └── rosidl_typesupport_fastrtps_cpp/
    │   ├── rmw/
    │   ├── rmw_implementation/
    │   ├── rmw_dds_common/
    │   ├── rmw_fastrtps/
    │   │   ├── rmw_fastrtps_shared_cpp/
    │   │   ├── rmw_fastrtps_cpp/
    │   │   └── rmw_fastrtps_dynamic_cpp/
    │   ├── rcl/
    │   └── rclcpp/
    ├── vendor/             # 第三方库
    │   ├── fastdds/        # FastDDS核心
    │   │   ├── fastrtps/   # DDS实现
    │   │   ├── fastcdr/    # CDR序列化
    │   │   └── foonathan_memory/ # 内存分配器
    │   ├── libyaml/
    │   └── tinyxml2/       # XML解析 (FastDDS配置)
    └── interfaces/         # 消息定义
        ├── builtin_interfaces/
        ├── rcl_interfaces/
        ├── std_msgs/
        └── std_srvs/
```

---

## 3. FastDDS 架构详解

### 3.1 FastDDS 组件结构

```
FastDDS
├── fastrtps/                    # DDS核心实现
│   ├── src/cpp/
│   │   ├── dds/                 # DDS API层 (DCPS)
│   │   │   ├── core/            # DomainParticipant, Entity
│   │   │   ├── domain/          # Domain管理
│   │   │   ├── publisher/       # Publisher, DataWriter
│   │   │   ├── subscriber/      # Subscriber, DataReader
│   │   │   ├── topic/           # Topic, ContentFilter
│   │   │   └── builtin/         # 内置话题
│   │   ├── rtps/                # RTPS协议层
│   │   │   ├── participant/     # RTPSParticipant
│   │   │   ├── writer/          # RTPSWriter
│   │   │   ├── reader/          # RTPSReader
│   │   │   ├── history/         # 历史缓存
│   │   │   ├── messages/        # RTPS消息
│   │   │   ├── network/         # 网络传输
│   │   │   └── builtin/         # 发现协议 (SPDP/SEDP)
│   │   ├── dynamic_types/       # DDS-XTYPES
│   │   ├── security/            # DDS Security
│   │   ├── xmlparser/           # XML配置解析
│   │   └── utils/               # 工具类
│   └── include/
│       ├── fastdds/             # 公共API
│       └── fastrtps/            # 兼容API
├── fastcdr/                     # CDR序列化库
│   ├── src/cpp/
│   │   ├── Cdr.cpp              # CDR编解码
│   │   ├── FastCdr.cpp          # 快速CDR
│   │   └── FastBuffer.cpp       # 缓冲区管理
│   └── include/fastcdr/
└── foonathan_memory/            # 内存分配器 (可选)
```

### 3.2 FastDDS 功能模块详解

#### 3.2.1 RTPS协议 (P0)

**位置**: `fastrtps/src/cpp/rtps/`

**核心组件**:
- **RTPSParticipant**: RTPS域参与者
- **RTPSWriter/RTPSReader**: 数据读写端点
- **SPDP/SEDP**: 简单参与者/端点发现协议
- **HistoryCache**: 数据历史缓存

**关键文件**:
```
rtps/participant/RTPSParticipantImpl.cpp
rtps/writer/RTPSWriter.cpp
rtps/reader/RTPSReader.cpp
rtps/builtin/discovery/participant/PDPSimple.cpp
rtps/builtin/discovery/endpoint/EDPSimple.cpp
rtps/messages/RTPSMessageCreator.cpp
rtps/network/NetworkFactory.cpp
```

#### 3.2.2 DDS协议 - DCPS (P0)

**位置**: `fastrtps/src/cpp/dds/`

**核心组件**:
- **DomainParticipant**: DDS域参与者
- **Publisher/Subscriber**: 发布/订阅者
- **DataWriter/DataReader**: 数据读写器
- **Topic/ContentFilteredTopic**: 话题管理

**关键文件**:
```
dds/domain/DomainParticipantImpl.cpp
dds/publisher/PublisherImpl.cpp
dds/subscriber/SubscriberImpl.cpp
dds/publisher/DataWriterImpl.cpp
dds/subscriber/DataReaderImpl.cpp
dds/topic/TopicImpl.cpp
```

#### 3.2.3 DDS-XTYPES (P0)

**位置**: `fastrtps/src/cpp/dynamic_types/`

**功能**: 运行时动态类型构建和操作

**核心组件**:
- **DynamicTypeBuilder**: 动态类型构建器
- **DynamicType**: 动态类型定义
- **DynamicData**: 动态数据实例
- **TypeObject**: 类型对象表示

**关键文件**:
```
dynamic_types/DynamicTypeBuilderFactory.cpp
dynamic_types/DynamicType.cpp
dynamic_types/DynamicData.cpp
dynamic_types/TypeObjectFactory.cpp
dynamic_types/DynamicPubSubType.cpp
```

#### 3.2.4 DDS Security (P1)

**位置**: `fastrtps/src/cpp/security/`

**功能**: 身份认证、访问控制、加密

**核心组件**:
- **Authentication**: 身份认证插件
- **AccessControl**: 访问控制插件
- **Cryptography**: 加密插件

**依赖**: OpenSSL (需移植或使用OHOS替代)

**关键文件**:
```
security/authentication/PKIDH.cpp
security/accesscontrol/Permissions.cpp
security/cryptography/AESGCMGMAC.cpp
```

#### 3.2.5 Fast-CDR (P0)

**位置**: `fastcdr/`

**功能**: Common Data Representation 序列化

**核心类**:
- **Cdr**: 标准CDR编解码
- **FastCdr**: 优化的FastCDR编解码
- **FastBuffer**: 高效缓冲区管理

**关键文件**:
```
fastcdr/src/cpp/Cdr.cpp
fastcdr/src/cpp/FastCdr.cpp
fastcdr/src/cpp/FastBuffer.cpp
```

#### 3.2.6 IDL接口 (P0)

**位置**: `fastrtpsgen/` (代码生成器)

**功能**: IDL到C++代码生成

**工具**: `fastrtpsgen` (Java工具，在主机运行)

**生成文件**:
- `<Type>.h/.cxx` - 类型定义
- `<Type>PubSubTypes.h/.cxx` - 发布订阅类型
- `<Type>TypeObject.h/.cxx` - 类型对象 (XTYPES)

#### 3.2.7 DDS RPC (P1)

**位置**: `fastrtps/src/cpp/dds/rpc/` (如果有)

**功能**: 基于DDS的RPC框架

**注**: FastDDS原生RPC支持有限，可通过rosidl_typesupport实现

---

## 4. 依赖关系

### 4.1 FastDDS依赖图

```
FastDDS (fastrtps)
  ├─→ Fast-CDR (序列化)
  ├─→ foonathan_memory (内存分配，可选)
  ├─→ tinyxml2 (XML配置解析)
  ├─→ asio (网络IO，header-only)
  └─→ OpenSSL (安全功能，可选)
```

### 4.2 ROS2 + FastDDS 依赖图

```
rclcpp
  ├─→ rcl
  │    ├─→ rmw_implementation
  │    │    └─→ rmw_fastrtps_cpp
  │    │         ├─→ rmw_fastrtps_shared_cpp
  │    │         │    ├─→ rmw_dds_common
  │    │         │    ├─→ fastrtps (FastDDS)
  │    │         │    │    ├─→ fastcdr
  │    │         │    │    └─→ tinyxml2
  │    │         │    └─→ rosidl_typesupport_fastrtps_cpp
  │    │         └─→ rmw
  │    ├─→ rcl_logging_noop
  │    ├─→ rcl_yaml_param_parser (→ libyaml)
  │    └─→ rcl_interfaces
  ├─→ rosidl_typesupport_cpp
  └─→ rcpputils
```

### 4.3 完整包列表

#### Layer 0: 第三方依赖 (5个)

| 包名 | 说明 | 来源 |
|------|------|------|
| fastcdr | CDR序列化 | eProsima |
| tinyxml2 | XML解析 | tinyxml2 |
| asio | 网络IO (header-only) | Boost/standalone |
| libyaml | YAML解析 | yaml.org |
| foonathan_memory | 内存分配 (可选) | foonathan |

#### Layer 1: ROS2基础库 (5个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rcutils | 无 | C工具库 |
| rcpputils | rcutils | C++工具库 |
| rosidl_typesupport_interface | 无 | 类型接口 |
| ament_index_cpp | rcpputils | 包索引 |
| tracetools | rcutils | 追踪 (可选) |

#### Layer 2: 类型系统 (12个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rosidl_runtime_c | rcutils | C类型运行时 |
| rosidl_runtime_cpp | rosidl_runtime_c | C++类型运行时 |
| rosidl_typesupport_introspection_c | rosidl_runtime_c | C内省 |
| rosidl_typesupport_introspection_cpp | rosidl_runtime_cpp | C++内省 |
| rosidl_typesupport_c | introspection_c | C类型调度 |
| rosidl_typesupport_cpp | introspection_cpp | C++类型调度 |
| rosidl_typesupport_fastrtps_c | fastcdr | FastRTPS C类型 |
| rosidl_typesupport_fastrtps_cpp | fastcdr | FastRTPS C++类型 |
| rosidl_dynamic_typesupport | rosidl_* | 动态类型 |
| builtin_interfaces | rosidl_* | Time/Duration |
| rcl_interfaces | rosidl_* | RCL接口 |
| std_msgs | rosidl_* | 标准消息 |

#### Layer 3: FastDDS (1个大包)

| 包名 | 依赖 | 说明 |
|------|------|------|
| fastrtps | fastcdr, tinyxml2, asio | FastDDS核心 |

#### Layer 4: RMW层 (5个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rmw | rcutils, rosidl_runtime_c | 中间件接口 |
| rmw_dds_common | rmw, rosidl_* | DDS公共功能 |
| rmw_fastrtps_shared_cpp | rmw_dds_common, fastrtps | 共享实现 |
| rmw_fastrtps_cpp | rmw_fastrtps_shared_cpp | FastDDS静态类型 |
| rmw_implementation | rmw | 运行时选择 |

#### Layer 5: 客户端库 (4个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rcl_logging_interface | rcutils | 日志接口 |
| rcl_logging_noop | logging_interface | 空日志 |
| rcl_yaml_param_parser | rcutils, libyaml | 参数解析 |
| rcl | rmw_impl, rosidl_* | C客户端 |

#### Layer 6: 高级客户端 (2个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rclcpp | rcl, rosidl_* | C++客户端 |
| std_srvs | rosidl_* | 标准服务 |

---

## 5. 编译工具链

### 5.1 工具链配置

**Clang 15.0.4** (OpenHarmony预编译):
```
路径: /home/jiusi/M-DDS/OpenHarmony/prebuilts/clang/ohos/linux-x86_64/llvm/
编译器: bin/clang, bin/clang++
链接器: bin/lld
目标三元组: aarch64-linux-ohos
```

### 5.2 关键编译选项

```gn
# C编译选项
cflags_c = [
  "-std=c11",
  "-D_GNU_SOURCE",
  "--target=aarch64-linux-ohos",
  "-fPIC",
]

# C++编译选项 (FastDDS需要C++14/17)
cflags_cc = [
  "-std=c++17",
  "--target=aarch64-linux-ohos",
  "-stdlib=libc++",
  "-fPIC",
  "-fexceptions",  # FastDDS需要异常
  "-frtti",        # FastDDS需要RTTI
]

# 链接选项
ldflags = [
  "-fuse-ld=lld",
  "--target=aarch64-linux-ohos",
  "-stdlib=libc++",
]
```

### 5.3 FastDDS特定编译选项

```gn
# FastDDS定义
fastdds_defines = [
  "FASTRTPS_NO_LIB",           # 不自动链接库
  "ASIO_STANDALONE",            # 独立asio
  "ASIO_DISABLE_VISIBILITY",    # 禁用符号可见性
  "_ENABLE_ATOMIC_ALIGNMENT_FIX", # 原子对齐修复
]

# 禁用可选功能 (简化移植)
fastdds_disabled_features = [
  "SHM_TRANSPORT_DISABLED",     # 共享内存 (先禁用)
  "SQLITE3_SUPPORT_DISABLED",   # SQLite持久化
]

# 启用功能
fastdds_enabled_features = [
  "HAVE_CXX17",
  "HAVE_STRICT_REALTIME",
]
```

---

## 6. 分阶段实施计划

### Phase 1: 基础库移植 (4周)

**目标**: rcutils/rcpputils + Fast-CDR 在 OpenHarmony 运行

| 周 | 任务 | 交付物 |
|----|------|--------|
| 1 | 创建项目结构，编写GN模板 | ohos_ros2/ 目录 |
| 2 | 移植 rcutils, rcpputils | BUILD.gn + 测试 |
| 3 | 移植 Fast-CDR | fastcdr BUILD.gn |
| 4 | 部署验证 | 开发板运行测试 |

**里程碑**:
- [ ] rcutils 编译通过并测试
- [ ] Fast-CDR 序列化测试通过
- [ ] 开发板运行基础测试

### Phase 2: 类型系统 (3周)

**目标**: rosidl完整类型系统 + FastRTPS类型支持

| 周 | 任务 | 交付物 |
|----|------|--------|
| 5 | rosidl_runtime_c/cpp | 类型运行时库 |
| 6 | rosidl_typesupport_* (内省) | 类型支持库 |
| 7 | rosidl_typesupport_fastrtps_* | FastRTPS类型支持 |

**里程碑**:
- [ ] rosidl_runtime_c/cpp 编译通过
- [ ] builtin_interfaces 消息生成
- [ ] FastRTPS类型支持测试

### Phase 3: FastDDS核心移植 (6周)

**目标**: FastDDS RTPS + DCPS 功能可用

| 周 | 任务 | 交付物 |
|----|------|--------|
| 8-9 | tinyxml2, asio 移植 | 依赖库 BUILD.gn |
| 10-11 | FastDDS RTPS层 | RTPS协议库 |
| 12-13 | FastDDS DDS层 (DCPS) | DDS API库 |

**里程碑**:
- [ ] FastDDS 编译通过
- [ ] RTPS发现协议测试
- [ ] DDS Participant创建测试

### Phase 4: DDS-XTYPES + 高级功能 (3周)

**目标**: DDS-XTYPES动态类型支持

| 周 | 任务 | 交付物 |
|----|------|--------|
| 14 | DDS-XTYPES | 动态类型库 |
| 15 | DDS配置/QoS | XML配置解析 |
| 16 | DDS RPC框架 | RPC测试 |

**里程碑**:
- [ ] 动态类型构建测试
- [ ] QoS策略配置测试
- [ ] RPC调用测试

### Phase 5: RMW层移植 (3周)

**目标**: rmw_fastrtps 完整可用

| 周 | 任务 | 交付物 |
|----|------|--------|
| 17 | rmw, rmw_dds_common | RMW接口库 |
| 18 | rmw_fastrtps_shared_cpp | FastRTPS共享层 |
| 19 | rmw_fastrtps_cpp | FastRTPS RMW |

**里程碑**:
- [ ] rmw接口实现完整
- [ ] rmw_fastrtps_cpp加载测试
- [ ] RMW发布/订阅测试

### Phase 6: 客户端库 (4周)

**目标**: rcl + rclcpp 完整可用

| 周 | 任务 | 交付物 |
|----|------|--------|
| 20 | rcl_interfaces, rcl_logging | 接口和日志 |
| 21-22 | rcl 核心 | rcl BUILD.gn |
| 23 | rclcpp | rclcpp BUILD.gn |

**里程碑**:
- [ ] rcl_init 成功
- [ ] rcl_node 创建成功
- [ ] rclcpp::Node 测试通过

### Phase 7: 集成测试 (2周)

**目标**: 完整ROS2节点运行 + 跨平台互通

| 周 | 任务 | 交付物 |
|----|------|--------|
| 24 | talker/listener Demo | Demo程序 |
| 25 | 跨平台互通测试 | 测试报告 |

**里程碑**:
- [ ] OHOS talker/listener 运行
- [ ] OHOS ↔ Linux ROS2 互通
- [ ] 性能基准测试

### Phase 8: DDS Security (可选, 4周)

**目标**: DDS安全功能

| 周 | 任务 | 交付物 |
|----|------|--------|
| 26-27 | OpenSSL/mbedTLS 移植 | 加密库 |
| 28-29 | DDS Security插件 | 安全认证 |

---

## 7. FastDDS BUILD.gn 设计

### 7.1 Fast-CDR BUILD.gn

```gn
# ohos_ros2/vendor/fastdds/fastcdr/BUILD.gn

import("//ohos_ros2/gn_templates/ros2_library.gni")

ros2_shared_library("fastcdr") {
  sources = [
    "src/cpp/Cdr.cpp",
    "src/cpp/CdrSizeCalculator.cpp",
    "src/cpp/FastBuffer.cpp",
    "src/cpp/FastCdr.cpp",
  ]

  include_dirs = [
    "include",
    "src/cpp",
  ]

  defines = [
    "FASTCDR_DYN_LINK",
  ]

  cflags_cc = [ "-std=c++17" ]

  output_name = "libfastcdr"
}
```

### 7.2 FastDDS BUILD.gn (简化版)

```gn
# ohos_ros2/vendor/fastdds/fastrtps/BUILD.gn

import("//ohos_ros2/gn_templates/ros2_library.gni")

config("fastdds_config") {
  include_dirs = [
    "include",
    "src/cpp",
    "//ohos_ros2/vendor/fastdds/fastcdr/include",
    "//ohos_ros2/vendor/asio/include",
    "//ohos_ros2/vendor/tinyxml2",
  ]

  defines = [
    "FASTRTPS_DYN_LINK",
    "ASIO_STANDALONE",
    "ASIO_DISABLE_VISIBILITY",
    "HAVE_CXX17",
  ]

  cflags_cc = [
    "-std=c++17",
    "-fexceptions",
    "-frtti",
  ]
}

# RTPS协议层
source_set("fastdds_rtps") {
  sources = [
    # Participant
    "src/cpp/rtps/participant/RTPSParticipant.cpp",
    "src/cpp/rtps/participant/RTPSParticipantImpl.cpp",
    # Writer/Reader
    "src/cpp/rtps/writer/RTPSWriter.cpp",
    "src/cpp/rtps/writer/StatefulWriter.cpp",
    "src/cpp/rtps/writer/StatelessWriter.cpp",
    "src/cpp/rtps/reader/RTPSReader.cpp",
    "src/cpp/rtps/reader/StatefulReader.cpp",
    "src/cpp/rtps/reader/StatelessReader.cpp",
    # History
    "src/cpp/rtps/history/History.cpp",
    "src/cpp/rtps/history/WriterHistory.cpp",
    "src/cpp/rtps/history/ReaderHistory.cpp",
    # Discovery
    "src/cpp/rtps/builtin/discovery/participant/PDPSimple.cpp",
    "src/cpp/rtps/builtin/discovery/endpoint/EDPSimple.cpp",
    "src/cpp/rtps/builtin/discovery/endpoint/EDPStatic.cpp",
    # Network
    "src/cpp/rtps/network/NetworkFactory.cpp",
    "src/cpp/rtps/transport/UDPTransportInterface.cpp",
    "src/cpp/rtps/transport/UDPv4Transport.cpp",
    "src/cpp/rtps/transport/TCPTransportInterface.cpp",
    # Messages
    "src/cpp/rtps/messages/RTPSMessageCreator.cpp",
    "src/cpp/rtps/messages/RTPSMessageGroup.cpp",
    # ... 更多源文件
  ]

  public_configs = [ ":fastdds_config" ]

  deps = [
    "//ohos_ros2/vendor/fastdds/fastcdr:fastcdr",
    "//ohos_ros2/vendor/tinyxml2:tinyxml2",
  ]
}

# DDS API层 (DCPS)
source_set("fastdds_dds") {
  sources = [
    # Domain
    "src/cpp/dds/domain/DomainParticipant.cpp",
    "src/cpp/dds/domain/DomainParticipantImpl.cpp",
    "src/cpp/dds/domain/DomainParticipantFactory.cpp",
    # Publisher
    "src/cpp/dds/publisher/Publisher.cpp",
    "src/cpp/dds/publisher/PublisherImpl.cpp",
    "src/cpp/dds/publisher/DataWriter.cpp",
    "src/cpp/dds/publisher/DataWriterImpl.cpp",
    # Subscriber
    "src/cpp/dds/subscriber/Subscriber.cpp",
    "src/cpp/dds/subscriber/SubscriberImpl.cpp",
    "src/cpp/dds/subscriber/DataReader.cpp",
    "src/cpp/dds/subscriber/DataReaderImpl.cpp",
    # Topic
    "src/cpp/dds/topic/Topic.cpp",
    "src/cpp/dds/topic/TopicImpl.cpp",
    "src/cpp/dds/topic/TypeSupport.cpp",
    # QoS
    "src/cpp/dds/topic/qos/TopicQos.cpp",
    "src/cpp/dds/publisher/qos/DataWriterQos.cpp",
    "src/cpp/dds/subscriber/qos/DataReaderQos.cpp",
    # ... 更多源文件
  ]

  public_configs = [ ":fastdds_config" ]

  deps = [ ":fastdds_rtps" ]
}

# DDS-XTYPES (动态类型)
source_set("fastdds_xtypes") {
  sources = [
    "src/cpp/dynamic_types/DynamicType.cpp",
    "src/cpp/dynamic_types/DynamicTypeBuilder.cpp",
    "src/cpp/dynamic_types/DynamicTypeBuilderFactory.cpp",
    "src/cpp/dynamic_types/DynamicData.cpp",
    "src/cpp/dynamic_types/DynamicDataFactory.cpp",
    "src/cpp/dynamic_types/DynamicPubSubType.cpp",
    "src/cpp/dynamic_types/TypeObjectFactory.cpp",
    # ... 更多源文件
  ]

  public_configs = [ ":fastdds_config" ]

  deps = [ ":fastdds_dds" ]
}

# 完整FastDDS库
ros2_shared_library("fastrtps") {
  deps = [
    ":fastdds_rtps",
    ":fastdds_dds",
    ":fastdds_xtypes",
  ]

  libs = [
    "pthread",
    "dl",
  ]

  output_name = "libfastrtps"
}
```

### 7.3 rmw_fastrtps_cpp BUILD.gn

```gn
# ohos_ros2/foundation/rmw_fastrtps/rmw_fastrtps_cpp/BUILD.gn

import("//ohos_ros2/gn_templates/ros2_library.gni")

ros2_shared_library("rmw_fastrtps_cpp") {
  sources = [
    "src/identifier.cpp",
    "src/init_rmw_context_impl.cpp",
    "src/publisher.cpp",
    "src/subscription.cpp",
    "src/rmw_client.cpp",
    "src/rmw_service.cpp",
    "src/rmw_event.cpp",
    "src/rmw_get_topic_endpoint_info.cpp",
    "src/rmw_guard_condition.cpp",
    "src/rmw_node.cpp",
    "src/rmw_wait.cpp",
    # ... 更多源文件
  ]

  include_dirs = [
    "include",
  ]

  deps = [
    "//ohos_ros2/foundation/rmw:rmw",
    "//ohos_ros2/foundation/rmw_dds_common:rmw_dds_common",
    "//ohos_ros2/foundation/rmw_fastrtps/rmw_fastrtps_shared_cpp:rmw_fastrtps_shared_cpp",
    "//ohos_ros2/foundation/rosidl/rosidl_typesupport_fastrtps_cpp:rosidl_typesupport_fastrtps_cpp",
    "//ohos_ros2/vendor/fastdds/fastrtps:fastrtps",
  ]

  defines = [
    "RMW_FASTRTPS_CPP_BUILDING_DLL",
  ]

  output_name = "librmw_fastrtps_cpp"
}
```

---

## 8. 技术风险与应对

### 8.1 高风险项

| 风险 | 影响 | 概率 | 应对策略 |
|------|------|------|----------|
| FastDDS代码量大 | 延期 | 高 | 分模块移植，先RTPS后DDS |
| asio兼容性 | 网络不通 | 中 | 使用standalone asio，测试socket API |
| C++异常/RTTI | 编译失败 | 中 | 确保编译选项正确，测试libc++兼容 |
| 线程模型差异 | 死锁/崩溃 | 中 | 详细测试pthread，使用OHOS线程API |

### 8.2 中风险项

| 风险 | 影响 | 概率 | 应对策略 |
|------|------|------|----------|
| DDS Security依赖OpenSSL | 安全功能不可用 | 中 | 先禁用，后期移植mbedTLS |
| 共享内存传输 | 性能下降 | 低 | 先用UDP/TCP，后期添加SHM |
| XML配置解析 | 配置不生效 | 低 | 简化配置，硬编码默认值 |
| musl libc兼容 | 运行时错误 | 中 | 预先测试POSIX API |

### 8.3 FastDDS移植注意事项

1. **线程模型**:
   - FastDDS使用大量线程 (接收线程、事件线程、发现线程)
   - 确保pthread在OHOS上正常工作
   - 注意线程优先级和调度策略

2. **网络传输**:
   - 优先移植UDP传输 (UDPv4Transport)
   - TCP传输复杂度更高，后期添加
   - 测试多播发现功能

3. **内存管理**:
   - FastDDS默认使用foonathan_memory
   - 可先禁用，使用标准分配器
   - 后期优化内存性能

4. **XML配置**:
   - FastDDS依赖XML配置QoS
   - tinyxml2移植相对简单
   - 也可硬编码默认QoS

---

## 9. 测试计划

### 9.1 单元测试

| 模块 | 测试内容 | 覆盖率目标 |
|------|----------|------------|
| Fast-CDR | 序列化/反序列化 | 90% |
| FastDDS RTPS | 消息编解码、历史缓存 | 70% |
| FastDDS DDS | Participant/Writer/Reader | 70% |
| DDS-XTYPES | 动态类型构建 | 60% |
| rmw_fastrtps | RMW接口 | 80% |
| rcl | 节点、发布、订阅 | 70% |
| rclcpp | C++ API | 60% |

### 9.2 集成测试

| 测试场景 | 验证内容 |
|----------|----------|
| 单设备Pub/Sub | 同设备talker/listener |
| 跨设备Pub/Sub | 两块开发板通信 |
| Service调用 | 请求/响应模式 |
| QoS策略 | Reliability, Durability, History |
| 发现协议 | SPDP/SEDP自动发现 |

### 9.3 互通测试

| 测试场景 | 设备配置 | 预期结果 |
|----------|----------|----------|
| OHOS ↔ OHOS | 两块rk3588s | FastDDS直接通信 |
| OHOS ↔ Linux | 开发板 + PC | DDS协议互通 |
| OHOS ↔ Windows | 开发板 + PC | DDS协议互通 |
| 混合组网 | 3+设备 | 多节点发现和通信 |

---

## 10. 参考资源

### 10.1 关键代码路径

```
# FastDDS源码
/home/jiusi/M-DDS/ros2/src/eProsima/Fast-DDS/

# Fast-CDR源码
/home/jiusi/M-DDS/ros2/src/eProsima/Fast-CDR/

# rmw_fastrtps源码
/home/jiusi/M-DDS/ros2/src/ros2/rmw_fastrtps/

# rosidl_typesupport_fastrtps源码
/home/jiusi/M-DDS/ros2/src/ros2/rosidl_typesupport_fastrtps/

# ROS2核心包
/home/jiusi/M-DDS/ros2/src/ros2/rcl/
/home/jiusi/M-DDS/ros2/src/ros2/rclcpp/
```

### 10.2 文档链接

- [FastDDS官方文档](https://fast-dds.docs.eprosima.com/)
- [FastDDS GitHub](https://github.com/eProsima/Fast-DDS)
- [ROS2 Jazzy文档](https://docs.ros.org/en/jazzy/)
- [OMG DDS规范](https://www.omg.org/spec/DDS/)
- [OpenHarmony GN构建指南](https://gitee.com/openharmony/docs/blob/master/zh-cn/device-dev/subsystems/subsys-build-gn-coding-style-and-best-practice.md)

---

## 附录A: 包版本清单

| 包名 | 版本 | 来源 |
|------|------|------|
| fastrtps (FastDDS) | 2.14.x | ros2/src/eProsima/Fast-DDS |
| fastcdr | 2.2.x | ros2/src/eProsima/Fast-CDR |
| rmw_fastrtps_cpp | 8.4.x | ros2/src/ros2/rmw_fastrtps |
| rmw | 7.3.x | ros2/src/ros2/rmw |
| rcl | 9.2.x | ros2/src/ros2/rcl |
| rclcpp | 28.1.x | ros2/src/ros2/rclcpp |
| rcutils | 6.7.x | ros2/src/ros2/rcutils |
| rosidl_runtime_c | 4.6.x | ros2/src/ros2/rosidl |

---

## 附录B: 编译命令参考

```bash
# 配置GN
gn gen out/rk3588s --args='target_cpu="arm64" is_debug=false'

# 编译Fast-CDR
ninja -C out/rk3588s vendor/fastdds/fastcdr:fastcdr

# 编译FastDDS
ninja -C out/rk3588s vendor/fastdds/fastrtps:fastrtps

# 编译rmw_fastrtps
ninja -C out/rk3588s foundation/rmw_fastrtps/rmw_fastrtps_cpp:rmw_fastrtps_cpp

# 编译全部ROS2
ninja -C out/rk3588s ohos_ros2:ros2

# 部署到开发板
powershell.exe -Command "hdc file send out/rk3588s/lib/libfastrtps.z.so /system/lib64/"
powershell.exe -Command "hdc file send out/rk3588s/lib/librmw_fastrtps_cpp.z.so /system/lib64/"
```

---

## 附录C: FastDDS功能模块对照表

| 需求功能 | FastDDS模块 | 文件位置 | 优先级 |
|----------|-------------|----------|--------|
| RTPS协议 | rtps/* | fastrtps/src/cpp/rtps/ | P0 |
| DDS协议 | dds/* | fastrtps/src/cpp/dds/ | P0 |
| DDS-XTYPES | dynamic_types/* | fastrtps/src/cpp/dynamic_types/ | P0 |
| DCPS | dds/domain, dds/pub, dds/sub | fastrtps/src/cpp/dds/ | P0 |
| IDL接口 | fastrtpsgen | 主机工具 | P0 |
| Fast-CDR | fastcdr | fastcdr/src/cpp/ | P0 |
| DDS Security | security/* | fastrtps/src/cpp/security/ | P1 |
| DDS RPC | 通过rmw_fastrtps | rmw_fastrtps_cpp | P1 |
| DLRL | 未原生支持 | 需自定义实现 | P2 |
| DDS-WEB | 未原生支持 | 需自定义实现 | P2 |
| DDS OPC UA | 未原生支持 | 需第三方库 | P2 |

---

**文档结束**
