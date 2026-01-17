# ROS2 依赖分析报告

## 文档信息

- **日期**: 2025-12-31
- **分析目标**: ROS2 Jazzy 源码依赖关系
- **源码路径**: /home/jiusi/M-DDS/ros2/

---

## 1. 核心包依赖图谱

### 1.1 纵向分层架构

```
┌─────────────────────────────────────────────────────────────┐
│  应用层 (Application Layer)                                  │
│  - ros2 demos, turtlesim, etc.                              │
└─────────────────────────────────────────────────────────────┘
                        ↓
┌─────────────────────────────────────────────────────────────┐
│  客户端库层 (Client Libraries)                               │
│  - rclcpp (C++)                                             │
│  - rclpy (Python) - 不在本次范围                             │
└─────────────────────────────────────────────────────────────┘
                        ↓
┌─────────────────────────────────────────────────────────────┐
│  RCL层 (ROS Client Library)                                 │
│  - rcl (C core library)                                     │
│  - rcl_action, rcl_lifecycle                                │
└─────────────────────────────────────────────────────────────┘
                        ↓
┌─────────────────────────────────────────────────────────────┐
│  RMW层 (ROS Middleware Interface)                           │
│  - rmw (interface)                                          │
│  - rmw_implementation (runtime selector)                    │
└─────────────────────────────────────────────────────────────┘
                        ↓
┌─────────────────────────────────────────────────────────────┐
│  RMW实现层 (RMW Implementations)                             │
│  - rmw_dsoftbus ← **您的实现**                               │
│  - rmw_fastrtps_cpp (FastDDS)                               │
│  - rmw_cyclonedds_cpp (CycloneDDS)                          │
└─────────────────────────────────────────────────────────────┘
                        ↓
┌─────────────────────────────────────────────────────────────┐
│  DDS/通信层 (Communication Layer)                            │
│  - dsoftbus ← **OpenHarmony**                               │
│  - FastDDS (eProsima)                                       │
│  - CycloneDDS (Eclipse)                                     │
└─────────────────────────────────────────────────────────────┘
```

### 1.2 横向辅助系统

```
┌─────────────────┐  ┌──────────────────┐  ┌─────────────────┐
│  类型系统        │  │  工具库           │  │  日志系统        │
│  rosidl_*       │  │  rcutils         │  │  rcl_logging_*  │
│                 │  │  rcpputils       │  │                 │
│  - runtime_c    │  │  ament_index     │  │  - interface    │
│  - typesupport  │  │                  │  │  - spdlog       │
│  - generator    │  │                  │  │  - noop         │
└─────────────────┘  └──────────────────┘  └─────────────────┘
```

---

## 2. 详细包分析

### 2.1 rmw (v7.3.2) - 中间件接口

**位置**: `/home/jiusi/M-DDS/ros2/src/ros2/rmw/rmw`

**语言**: C (C99)

**直接依赖**:
- `rcutils` - C工具库
- `rosidl_runtime_c` - 类型支持运行时
- `rosidl_dynamic_typesupport` - 动态类型支持

**核心源文件** (28个):
```
allocators.c
convert_rcutils_ret_to_rmw_ret.c
discovery_options.c
event.c
init.c
init_options.c
message_sequence.c
names_and_types.c
network_flow_endpoint.c
network_flow_endpoint_array.c
publisher_options.c
qos_string_conversions.c
sanity_checks.c
security_options.c
subscription_content_filter_options.c
subscription_options.c
time.c
topic_endpoint_info.c
topic_endpoint_info_array.c
types.c
validate_full_topic_name.c
validate_namespace.c
validate_node_name.c
```

**关键头文件**:
```
include/rmw/rmw.h           # 主接口
include/rmw/types.h         # 数据结构
include/rmw/ret_types.h     # 返回值类型
include/rmw/qos_profiles.h  # QoS配置
```

### 2.2 rcl (v9.2.8) - C客户端库

**位置**: `/home/jiusi/M-DDS/ros2/src/ros2/rcl/rcl`

**语言**: C11 + C++17

**直接依赖**:
- `libyaml_vendor` - YAML解析
- `rcl_interfaces` - 标准接口
- `rcl_logging_interface` + `rcl_logging_spdlog` - 日志
- `rcl_yaml_param_parser` - 参数解析
- `rcutils` - C工具库
- `rmw_implementation` - 中间件实现
- `rosidl_runtime_c` - 类型运行时
- `service_msgs`, `type_description_interfaces` - 消息定义
- `tracetools` - 追踪工具
- `yaml` - YAML库

**核心源文件** (38个):
```
arguments.c
client.c
common.c
context.c
discovery_options.c
domain_id.c
dynamic_message_type_support.c
event.c
expand_topic_name.c
graph.c
guard_condition.c
init.c
init_options.c
lexer.c
lexer_lookahead.c
localhost.c
logging.c
logging_rosout.c
network_flow_endpoints.c
node.c
node_options.c
node_resolve_name.c
publisher.c
remap.c
security.c
service.c
service_event_publisher.c
subscription.c
time.c
timer.c
type_hash.c
validate_enclave_name.c
validate_topic_name.c
wait.c
```

### 2.3 rclcpp (v28.1.15) - C++客户端库

**位置**: `/home/jiusi/M-DDS/ros2/src/ros2/rclcpp/rclcpp`

**语言**: C++17

**直接依赖**:
- `ament_index_cpp` - 索引
- `builtin_interfaces`, `rcl_interfaces`, `rosgraph_msgs`, `statistics_msgs` - 消息
- `libstatistics_collector` - 统计收集
- `rcl` - C客户端库
- `rcl_logging_interface`, `rcl_yaml_param_parser` - 日志/参数
- `rcpputils`, `rcutils` - 工具库
- `rmw` - 中间件接口
- `rosidl_dynamic_typesupport` - 动态类型
- `rosidl_runtime_c/cpp` - 类型运行时
- `rosidl_typesupport_c/cpp` - 类型支持
- `tracetools` - 追踪

**核心功能模块** (100+ 源文件):
```
executors/
  - multi_threaded_executor.cpp
  - single_threaded_executor.cpp
  - static_executor_entities_collector.cpp
  - events_executor.cpp

node_interfaces/
  - node_base.cpp
  - node_clock.cpp
  - node_graph.cpp
  - node_logging.cpp
  - node_parameters.cpp
  - node_services.cpp
  - node_timers.cpp
  - node_topics.cpp

动态类型支持:
  - dynamic_typesupport/dynamic_message.cpp
  - dynamic_typesupport/dynamic_message_type_builder.cpp

进程内通信:
  - intra_process_manager.cpp

通用发布/订阅:
  - generic_publisher.cpp
  - generic_subscription.cpp
```

### 2.4 rcutils (v6.7.5) - 基础工具库

**位置**: `/home/jiusi/M-DDS/ros2/src/ros2/rcutils`

**语言**: C11 + C++17

**系统依赖**:
- `libatomic` - 原子操作
- Python3 + empy - 代码生成

**平台特定代码**:
```
# Windows特定 (132处)
检测宏: WIN32, _WIN32, __WIN32__, MSVC, _MSC_VER
主要文件: time_win32.c, shared_library.c, filesystem.c

# Unix/Linux特定 (23处)
检测宏: __linux__, __unix__, __APPLE__, __MACH__
主要文件: time_unix.c, process.c

# 移动/嵌入式 (10处)
检测宏: ANDROID, __ANDROID__, __QNX__, __QNXNTO__
```

**关键功能模块**:
```
内存分配: allocator.c, allocator_memory_strategy.c
错误处理: error_handling.c, error_handling_helpers.c
日志系统: logging.c, logging_macros.h
环境变量: env.c
文件系统: filesystem.c
共享库: shared_library.c
时间管理: time.c, time_unix.c (Unix), time_win32.c (Windows)
字符串工具: strdup.c, strerror.c, snprintf.c
数据结构: array_list.c, hash_map.c, string_array.c, string_map.c
```

---

## 3. 类型系统详解

### 3.1 rosidl_runtime_c (v4.6.7)

**位置**: `/home/jiusi/M-DDS/ros2/src/ros2/rosidl/rosidl_runtime_c`

**功能**: 提供C语言的类型定义、初始化、清理宏

**关键头文件**:
```
include/rosidl_runtime_c/
  - message_type_support_struct.h  # 消息类型支持结构
  - service_type_support_struct.h  # 服务类型支持结构
  - string.h                       # 字符串类型
  - primitives_sequence.h          # 基本类型序列
  - sequence.h                     # 通用序列
  - string_functions.h             # 字符串操作函数
```

### 3.2 rosidl_typesupport_c (v3.2.2)

**位置**: `/home/jiusi/M-DDS/ros2/src/ros2/rosidl_typesupport/rosidl_typesupport_c`

**语言**: C11 + C++17

**功能**: 运行时加载类型支持库，支持动态切换

**核心源文件**:
```
identifier.c
message_type_support_dispatch.cpp
service_type_support_dispatch.cpp
```

### 3.3 rosidl_typesupport_introspection_c (v4.6.7)

**位置**: `/home/jiusi/M-DDS/ros2/src/ros2/rosidl/rosidl_typesupport_introspection_c`

**功能**: 为动态消息构建生成内省元数据

**依赖**:
- `rosidl_generator_c` - C代码生成器
- `rosidl_parser`, `rosidl_pycommon` - Python解析工具

---

## 4. 第三方依赖

### 4.1 DDS中间件实现

#### Fast-CDR (v2.2.6)
```
位置: /home/jiusi/M-DDS/ros2/src/eProsima/Fast-CDR
构建系统: 纯CMake (非ament)
功能: CDR序列化库 (OMG标准)
依赖: 无外部依赖
状态: rmw_dsoftbus 已集成
```

#### rmw_fastrtps_cpp (v8.4.3)
```
位置: /home/jiusi/M-DDS/ros2/src/ros2/rmw_fastrtps/rmw_fastrtps_cpp
依赖:
  - fastcdr, fastrtps - eProsima库
  - rmw_dds_common - DDS通用功能
  - rmw_fastrtps_shared_cpp - 共享实现
  - rosidl_dynamic_typesupport_fastrtps - 动态类型
  - rosidl_typesupport_fastrtps_c/cpp - 静态类型
```

#### CycloneDDS
```
位置: /home/jiusi/M-DDS/ros2/src/eclipse-cyclonedds/cyclonedds
构建系统: CMake
依赖: iceoryx_binding_c (共享内存, 可选)
```

#### rmw_cyclonedds_cpp (v2.2.3)
```
位置: /home/jiusi/M-DDS/ros2/src/ros2/rmw_cyclonedds/rmw_cyclonedds_cpp
依赖:
  - cyclonedds - DDS核心
  - iceoryx_binding_c - 零拷贝传输
  - rmw_dds_common - DDS通用
  - rosidl_typesupport_introspection_c/cpp - 内省类型 (无静态代码生成)
```

### 4.2 其他第三方库

| 库名 | 用途 | 备注 |
|------|------|------|
| libyaml | YAML解析 | 参数文件 |
| spdlog | 日志实现 | 可用noop替代 |
| iceoryx | 共享内存通信 | 可选 |

---

## 5. 编译选项汇总

### 5.1 C/C++标准

| 包 | C标准 | C++标准 | 说明 |
|---|---|---|---|
| rmw | C99 | C++17 | 核心C接口 |
| rcl | C11 | C++17 | 混合C/C++ |
| rclcpp | - | C++17 (必需) | 纯C++ |
| rcutils | C11 | C++17 | 基础工具 |
| rosidl_* | C11 | C++17 | 类型支持 |

### 5.2 编译警告

**通用** (GCC/Clang):
```
-Wall -Wextra -Wpedantic -Wconversion -Wno-sign-conversion
```

**C++特定** (rclcpp):
```
-Wnon-virtual-dtor -Woverloaded-virtual
```

### 5.3 关键定义

| 宏定义 | 用途 |
|--------|------|
| `_GNU_SOURCE` | GNU libc扩展 (Linux) |
| `RCUTILS_ENABLE_FAULT_INJECTION` | 故障注入测试 |
| `RCL_BUILDING_DLL` | Windows DLL导出 |
| `DEFAULT_RMW_IMPLEMENTATION` | 默认中间件实现 |

---

## 6. 最小化移植包列表

### 6.1 Layer 0 - Vendor依赖 (6个)

| 包名 | 说明 |
|------|------|
| Fast-CDR | CDR序列化 |
| libyaml | YAML解析 |
| spdlog (可选) | 日志实现 |

### 6.2 Layer 1 - 基础库 (5个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rcutils | 无 | C工具库 |
| rcpputils | rcutils | C++工具库 |
| rosidl_typesupport_interface | 无 | 类型接口 |

### 6.3 Layer 2 - 类型系统 (12个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rosidl_runtime_c | rcutils | C类型运行时 |
| rosidl_runtime_cpp | rosidl_runtime_c | C++类型运行时 |
| rosidl_typesupport_introspection_c | rosidl_runtime_c | C内省 |
| rosidl_typesupport_introspection_cpp | rosidl_runtime_cpp | C++内省 |
| rosidl_typesupport_c | introspection_c | C类型调度 |
| rosidl_typesupport_cpp | introspection_cpp | C++类型调度 |
| rosidl_dynamic_typesupport | rosidl_* | 动态类型 |
| builtin_interfaces | rosidl_* | Time/Duration |
| rcl_interfaces | rosidl_* | RCL接口 |
| type_description_interfaces | rosidl_* | 类型描述 |
| service_msgs | rosidl_* | 服务消息 |
| std_msgs | rosidl_* | 标准消息 |

### 6.4 Layer 3 - RMW层 (4个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rmw | rcutils, rosidl_runtime_c | 中间件接口 |
| rmw_implementation | rmw | 运行时选择 |
| rmw_dsoftbus | rmw | dsoftbus实现 |
| tracetools | rcutils | 追踪 (可选) |

### 6.5 Layer 4 - 客户端库 (8个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rcl_logging_interface | rcutils | 日志接口 |
| rcl_logging_noop | logging_interface | 空日志 |
| rcl_yaml_param_parser | rcutils, libyaml | 参数解析 |
| ament_index_cpp | rcpputils | 包索引 |
| rcl | rmw_impl, rosidl_* | C客户端 |

### 6.6 Layer 5 - 高级客户端 (7个)

| 包名 | 依赖 | 说明 |
|------|------|------|
| rclcpp | rcl, rosidl_* | C++客户端 |
| libstatistics_collector | rcpputils | 统计 (可选) |
| rosgraph_msgs | rosidl_* | 图消息 |
| statistics_msgs | rosidl_* | 统计消息 |

---

## 7. 移植优先级排序

### 7.1 第一批 (P0 - 必需)

```
rcutils → rcpputils → rosidl_runtime_c → rmw → rcl → rclcpp
```

### 7.2 第二批 (P1 - 重要)

```
rosidl_typesupport_* → builtin_interfaces → rcl_interfaces → std_msgs
```

### 7.3 第三批 (P2 - 增强)

```
CycloneDDS → rmw_cyclonedds_cpp → rmw_dds_common
```

---

## 8. 关键文件清单

### 8.1 必读接口文件

| 文件 | 说明 |
|------|------|
| `ros2/src/ros2/rmw/rmw/include/rmw/rmw.h` | RMW核心接口 |
| `ros2/src/ros2/rmw/rmw/include/rmw/types.h` | RMW数据结构 |
| `ros2/src/ros2/rcl/rcl/include/rcl/rcl.h` | RCL主入口 |
| `ros2/src/ros2/rcl/rcl/include/rcl/node.h` | 节点接口 |
| `ros2/src/ros2/rcl/rcl/include/rcl/publisher.h` | 发布者接口 |
| `ros2/src/ros2/rcl/rcl/include/rcl/subscription.h` | 订阅者接口 |

### 8.2 参考CMakeLists.txt

| 文件 | 说明 |
|------|------|
| `ros2/src/ros2/rmw/rmw/CMakeLists.txt` | RMW构建 |
| `ros2/src/ros2/rcl/rcl/CMakeLists.txt` | RCL构建 |
| `ros2/src/ros2/rclcpp/rclcpp/CMakeLists.txt` | RCLCPP构建 |
| `ros2/src/ros2/rcutils/CMakeLists.txt` | rcutils构建 |

### 8.3 现有实现参考

| 文件 | 说明 |
|------|------|
| `rmw_dsoftbus/src/dsoftbus_adapter.cpp` | dsoftbus适配 |
| `rmw_dsoftbus/BUILD.gn` | GN构建示例 |
| `rmw_dsoftbus/DSOFTBUS_STATUS.md` | 实现状态 |

---

## 附录: 包版本汇总

| 包名 | 版本 | 类型 |
|------|------|------|
| rmw | 7.3.2 | Core |
| rmw_implementation | 2.15.6 | Core |
| rcl | 9.2.8 | Core |
| rclcpp | 28.1.15 | Core |
| rcutils | 6.7.5 | Utility |
| rcpputils | 2.11.3 | Utility |
| rosidl_runtime_c | 4.6.7 | Type System |
| rosidl_typesupport_c | 3.2.2 | Type System |
| rosidl_typesupport_introspection_c | 4.6.7 | Type System |
| fastcdr | 2.2.6 | Third-party |
| rmw_fastrtps_cpp | 8.4.3 | RMW Impl |
| rmw_cyclonedds_cpp | 2.2.3 | RMW Impl |

---

**文档结束**
