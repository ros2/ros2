# ROS2 Foundation 层移植计划 - rcutils & rosidl

## 执行摘要

本文档基于深度代码探索结果，制定 rcutils 和 rosidl 移植到 KaihongOS (rk3588s) 的详细计划。

**关键发现**：
- rcutils 已部分支持 OpenHarmony（`__OHOS__` 宏）
- rosidl 是解决跨设备 DDS 通信问题的关键（类型描述符生成）
- 移植工作主要是 GN 构建配置 + POSIX 兼容性验证

---

## 第一部分：rcutils 移植需求分析

### 1.1 基本信息

| 项目 | 详情 |
|------|------|
| **版本** | 6.7.5 |
| **代码量** | 9,779 行（24 个 .c 文件） |
| **语言** | C11 标准 |
| **依赖** | libatomic（原子操作库） |
| **现有平台** | Linux x86_64/aarch64, macOS, Windows |
| **OpenHarmony 支持** | 部分（process.c 已有 `__OHOS__` 分支） |

### 1.2 核心功能模块

```
rcutils 功能结构：
├── 内存管理 (allocator.c) - 可注入分配器
├── 日志系统 (logging.c - 49KB) - 三级日志 + TLS
├── 时间管理 (time.c + time_unix.c) - POSIX clock_gettime
├── 错误处理 (error_handling.c) - 线程本地错误状态
├── 动态库加载 (shared_library.c) - dlopen/dlsym
├── 文件系统 (filesystem.c) - POSIX getcwd/stat/dirent
├── 进程管理 (process.c) - ✓ 已支持 __OHOS__
├── 原子操作 (stdatomic_helper.h) - GCC atomic 内置
└── 数据结构 (string_array, hash_map 等) - 纯 C 实现
```

### 1.3 平台兼容性评估

| 模块 | POSIX 依赖 | OpenHarmony 支持 | 移植工作量 |
|------|-----------|-----------------|-----------|
| allocator.c | 无 | ✓ 完全兼容 | 0% |
| logging.c | stderr, TLS | ✓ 需验证 TLS | 5% |
| **time_unix.c** | clock_gettime() | ⚠️ 需验证 | 10% |
| error_handling.c | _Thread_local | ✓ C11 支持 | 0% |
| **shared_library.c** | dlopen/dlsym | ⚠️ 需验证路径 | 15% |
| **filesystem.c** | getcwd, stat, dirent | ⚠️ 需验证 | 10% |
| process.c | ✓ `__progname` | ✓ **已实现** | 0% |
| stdatomic_helper.h | GCC atomic | ✓ aarch64 支持 | 0% |
| 数据结构 | 无 | ✓ 完全兼容 | 0% |

**总体评估**：70% 代码无需修改，30% 需验证 POSIX 兼容性

### 1.4 已有 OpenHarmony 支持证据

**process.c:71-73** (已有 `__OHOS__` 分支):
```c
#elif defined __QNXNTO__ || defined __OHOS__
  extern char * __progname;  // OpenHarmony 提供的符号
  const char * appname = __progname;
```

**CHANGELOG 记录**:
```
Fix build on OpenHarmony (#395)
```

这表明 rcutils 团队已考虑过 OpenHarmony，移植基础良好。

### 1.5 关键验证点

**必须在 KaihongOS 上验证的系统调用**：

1. **时间函数** (time_unix.c):
   ```c
   clock_gettime(CLOCK_REALTIME, &ts);   // 系统时钟
   clock_gettime(CLOCK_MONOTONIC, &ts);  // 单调时钟
   ```

2. **动态库加载** (shared_library.c):
   ```c
   void *handle = dlopen("libfoo.so", RTLD_LAZY);
   void *symbol = dlsym(handle, "func_name");
   dlclose(handle);
   ```

3. **文件系统** (filesystem.c):
   ```c
   getcwd(buffer, size);
   stat(path, &st);
   DIR *dir = opendir(path);
   struct dirent *entry = readdir(dir);
   ```

4. **原子操作** (stdatomic_helper.h):
   ```c
   __atomic_load_8(ptr, __ATOMIC_SEQ_CST);
   __atomic_store_8(ptr, val, __ATOMIC_SEQ_CST);
   ```

### 1.6 rcutils 移植步骤

**阶段 1：准备** (1 天)
- [x] 探索代码库结构
- [ ] 创建 `/ros2/src/ros2/rcutils/BUILD.gn`
- [ ] 映射 CMake 选项到 GN 配置

**阶段 2：构建** (2 天)
- [ ] 配置源文件列表（24 个 .c 文件）
- [ ] 配置编译选项（`-fPIC -Wall -Wextra -D_GNU_SOURCE`）
- [ ] 链接 libatomic（aarch64 需要）
- [ ] 生成 `logging_macros.h`（EmPy 模板）

**阶段 3：验证** (1 天)
- [ ] 编译通过
- [ ] 在开发板运行基础测试（时间、内存、日志）
- [ ] 验证 dlopen 可用性
- [ ] 确认原子操作正常

---

## 第二部分：rosidl 移植需求分析

### 2.1 基本信息

| 项目 | 详情 |
|------|------|
| **包数量** | 18 个子包 |
| **核心语言** | Python (代码生成) + C (运行时) |
| **关键依赖** | rcutils, python3-empy, lark-parser |
| **作用** | 从 .idl/.msg/.srv 生成 C/C++ 类型支持代码 |
| **优先级** | **HIGH** - 解决跨设备通信问题的关键 |

### 2.2 架构层次

```
rosidl 三层架构：
┌─────────────────────────────────────────────────┐
│ Layer 1: Code Generation (构建时)              │
│  - rosidl_parser (IDL → AST)                   │
│  - rosidl_generator_c (AST → C 代码)           │
│  - rosidl_generator_type_description (类型哈希) │
└─────────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────────┐
│ Layer 2: Type Support (运行时库)               │
│  - rosidl_runtime_c (C 运行时支持)              │
│  - rosidl_typesupport_interface (接口定义)      │
└─────────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────────┐
│ Layer 3: Introspection (动态内省)              │
│  - rosidl_typesupport_introspection_c          │
│  - 提供字段级元数据（offset, type_id, size）    │
└─────────────────────────────────────────────────┘
```

### 2.3 与跨设备 DDS 问题的关联

**问题根源**：手动编写的 topic descriptor 缺少 rosidl 生成的完整元数据

**rosidl 生成的完整 descriptor 包含**：
1. **类型哈希** (SHA256) - 验证消息类型兼容性
2. **字段元数据** - offset, type_id, size
3. **初始化函数** - init_function, fini_function
4. **内省信息** - MessageMembers 结构体

**当前 rmw_dsoftbus 缺失**：
```c
// ✓ 已有（手动 mock）
typedef struct rosidl_message_type_support_t {
    const char * typesupport_identifier;
    const void * data;
    // ...
} rosidl_message_type_support_t;

// ✗ 缺失（需要 rosidl 生成）
const rosidl_typesupport_introspection_c__MessageMembers * members =
    (const rosidl_typesupport_introspection_c__MessageMembers *)(
        type_support->data
    );
```

### 2.4 移植优先级排序

| 包 | 优先级 | 移植类型 | 依赖 | 工作量 |
|----|--------|---------|------|--------|
| **rosidl_runtime_c** | P0 | 运行时库 | rcutils | 中 |
| **rosidl_typesupport_interface** | P0 | 头文件 | 无 | 低 |
| **rosidl_typesupport_introspection_c** | P1 | 运行时库 + 生成器 | rosidl_runtime_c | 高 |
| rosidl_parser | P2 | 构建工具 | lark-parser | 低（Python） |
| rosidl_generator_c | P2 | 构建工具 | rosidl_parser | 中 |
| rosidl_cmake | P2 | 构建集成 | 无 | 中 |
| rosidl_generator_type_description | P3 | 类型哈希 | rosidl_parser | 低 |

**P0（立即需要）**：解决当前编译/链接错误
**P1（核心功能）**：解决跨设备通信问题
**P2（完整支持）**：支持自定义消息类型
**P3（增强功能）**：类型兼容性验证

### 2.5 rosidl_runtime_c 详细分析

**目录结构**：
```
rosidl_runtime_c/
├── include/rosidl_runtime_c/
│   ├── message_type_support_struct.h  ✓ 已 mock
│   ├── service_type_support_struct.h  ✓ 已 mock
│   ├── primitives_sequence.h          ✗ 缺失
│   ├── string.h                       ✗ 缺失
│   ├── string_functions.h             ✗ 缺失
│   ├── u16string.h                    ✗ 缺失
│   ├── sequence_bound.h               ✗ 缺失
│   └── type_description/              ✗ 整个目录缺失
│       ├── type_description__struct.h
│       ├── type_description__functions.h
│       ├── type_hash.h
│       └── ...
└── src/
    ├── string.c                       # 字符串操作
    ├── u16string.c                    # UTF-16 字符串
    ├── primitives_sequence.c          # 序列操作
    └── type_description__functions.c  # 类型描述函数
```

**当前 rmw_dsoftbus mock 状态**：
```
rmw_dsoftbus/mock_includes/rosidl_runtime_c/
├── message_type_support_struct.h  (56 行) ✓
└── service_type_support_struct.h  (22 行) ✓

缺失：
- 动态字符串/序列支持（String, Sequence）
- 类型描述结构体（TypeDescription）
- 字段类型枚举（FieldTypes）
```

### 2.6 rosidl_typesupport_introspection_c 关键定义

**MessageMembers 结构体** (核心内省数据):
```c
typedef struct rosidl_typesupport_introspection_c__MessageMembers_s {
    const char * message_namespace_;     // "std_msgs__msg"
    const char * message_name_;          // "String"
    uint32_t member_count_;              // 字段数量
    size_t size_of_;                     // sizeof(std_msgs__msg__String)
    const rosidl_typesupport_introspection_c__MessageMember * members_;
    void (* init_function)(void *, enum rosidl_runtime_c__message_initialization);
    void (* fini_function)(void *);
} rosidl_typesupport_introspection_c__MessageMembers;
```

**MessageMember 结构体** (单字段元数据):
```c
typedef struct rosidl_typesupport_introspection_c__MessageMember_s {
    const char * name_;                  // 字段名
    uint32_t type_id_;                   // ROS_TYPE_UINT32 等
    uint32_t string_upper_bound_;        // 字符串最大长度
    const rosidl_message_type_support_t * members_;  // 嵌套消息
    bool is_array_;                      // 是否数组
    uint32_t array_size_;                // 固定数组大小
    bool is_upper_bound_;                // 是否有上界
    uint32_t offset_;                    // 字段偏移量
    void * default_value_;               // 默认值
    size_t (* size_function)(const void *);  // 动态大小计算
    // ...
} rosidl_typesupport_introspection_c__MessageMember;
```

**字段类型枚举**：
```c
enum {
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT = 1,
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE = 2,
    // ... (18 种类型)
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING = 16,
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE = 18,
};
```

### 2.7 rosidl 移植步骤

**阶段 1：运行时库** (3 天) - P0
- [ ] 移植 rosidl_runtime_c
  - [ ] 创建 BUILD.gn
  - [ ] 编译字符串/序列函数
  - [ ] 补充缺失的头文件 mock
- [ ] 移植 rosidl_typesupport_interface
  - [ ] 纯头文件，直接复制

**阶段 2：内省支持** (5 天) - P1
- [ ] 移植 rosidl_typesupport_introspection_c
  - [ ] 定义 MessageMembers/MessageMember 结构
  - [ ] 实现字段类型枚举
  - [ ] 为标准消息类型手动创建内省数据（临时方案）

**阶段 3：代码生成** (7 天) - P2
- [ ] 移植 rosidl_parser（Python，无需修改）
- [ ] 移植 rosidl_generator_c
  - [ ] 创建 GN action 调用 Python 生成器
  - [ ] 配置 EmPy 模板路径
  - [ ] 测试生成简单消息类型
- [ ] 集成到构建系统
  - [ ] 定义 GN template: `rosidl_generate_interfaces()`

**阶段 4：类型哈希** (2 天) - P3
- [ ] 移植 rosidl_generator_type_description
- [ ] 实现类型哈希计算
- [ ] 集成到 rmw_dsoftbus

---

## 第三部分：集成计划

### 3.1 依赖关系图

```
┌─────────────┐
│  rcutils    │ ← 基础依赖（必须先完成）
└──────┬──────┘
       │
       ↓
┌──────────────────────┐
│ rosidl_runtime_c     │ ← P0 优先级
│ rosidl_typesupport_* │
└──────┬───────────────┘
       │
       ↓
┌──────────────────────┐
│ rosidl_generator_c   │ ← P2 优先级
│ rosidl_parser        │
└──────┬───────────────┘
       │
       ↓
┌──────────────────────┐
│  rmw_dsoftbus        │ ← 最终集成
│  (使用完整类型支持)   │
└──────────────────────┘
```

### 3.2 GN 构建结构规划

**新增文件**：
```
ros2/src/ros2/
├── rcutils/
│   └── BUILD.gn          # 新建 - rcutils 库构建
├── rosidl/
│   ├── rosidl_runtime_c/
│   │   └── BUILD.gn      # 新建 - 运行时库
│   ├── rosidl_typesupport_interface/
│   │   └── BUILD.gn      # 新建 - 头文件库
│   ├── rosidl_typesupport_introspection_c/
│   │   └── BUILD.gn      # 新建 - 内省库
│   └── rosidl_generator_c/
│       └── BUILD.gn      # 新建 - 代码生成 action
└── BUILD.gn              # 修改 - 添加新依赖
```

**依赖声明示例**：
```gn
# ros2/src/ros2/rcutils/BUILD.gn
shared_library("rcutils") {
  sources = [
    "src/allocator.c",
    "src/logging.c",
    # ... 24 个源文件
  ]

  include_dirs = [ "include" ]

  configs += [ "//build/config:posix" ]

  if (target_cpu == "arm64") {
    libs = [ "atomic" ]  # aarch64 需要
  }

  defines = [ "_GNU_SOURCE" ]  # POSIX 扩展
}

# ros2/src/ros2/rosidl/rosidl_runtime_c/BUILD.gn
shared_library("rosidl_runtime_c") {
  sources = [
    "src/string.c",
    "src/u16string.c",
    "src/primitives_sequence.c",
    "src/type_description__functions.c",
  ]

  public_deps = [ "//ros2/src/ros2/rcutils:rcutils" ]

  include_dirs = [ "include" ]
}
```

### 3.3 rmw_dsoftbus 集成改动

**需要修改的文件**：
```
rmw_dsoftbus/
├── BUILD.gn               # 添加 rcutils/rosidl 依赖
├── mock_includes/         # 逐步移除 mock，使用真实头文件
├── src/rmw_publisher.cpp  # 使用 get_type_description_func()
└── src/rmw_subscription.cpp  # 验证类型哈希
```

**集成示例代码**：
```c
// rmw_dsoftbus/src/rmw_publisher.cpp (修改)
rmw_ret_t rmw_publish(const rmw_publisher_t * publisher, const void * ros_message) {
    // 获取类型描述
    const rosidl_message_type_support_t * ts = publisher->type_support;

    // 获取内省数据
    const rosidl_typesupport_introspection_c__MessageMembers * members =
        (const rosidl_typesupport_introspection_c__MessageMembers *)ts->data;

    // 使用内省数据进行 CDR 序列化
    for (uint32_t i = 0; i < members->member_count_; ++i) {
        const auto & member = members->members_[i];
        void * field_ptr = (uint8_t *)ros_message + member.offset_;

        // 根据 type_id_ 序列化字段
        switch (member.type_id_) {
            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
                serialize_uint32(buffer, *(uint32_t *)field_ptr);
                break;
            // ...
        }
    }

    // 发送序列化数据
    SendBytes(session_id, buffer, buffer_size);
}
```

---

## 第四部分：时间线与风险

### 4.1 预计时间线

| 阶段 | 任务 | 预计时间 | 关键产出 |
|------|------|---------|---------|
| **Week 1** | rcutils 移植 | 4 天 | librcutils.so |
| **Week 1** | rosidl_runtime_c 移植 | 3 天 | librosidl_runtime_c.so |
| **Week 2** | rosidl_typesupport_* 移植 | 5 天 | 内省支持库 |
| **Week 2** | 基础集成测试 | 2 天 | rmw_dsoftbus 编译通过 |
| **Week 3** | rosidl_generator_c 移植 | 7 天 | 代码生成工具链 |
| **Week 4** | 端到端测试 | 5 天 | 跨设备 pub/sub 成功 |
| **Week 4** | 文档与优化 | 2 天 | 移植文档 |

**总计**：约 4 周（28 天）

### 4.2 技术风险

| 风险 | 概率 | 影响 | 缓解措施 |
|------|------|------|---------|
| POSIX API 不完全兼容 | 中 | 高 | 提前编写验证测试 |
| 原子操作库链接失败 | 低 | 中 | 准备替代实现 |
| EmPy 模板生成失败 | 低 | 高 | 手动创建类型支持（临时） |
| GN 构建配置复杂 | 中 | 中 | 参考现有 BUILD.gn |
| 跨设备类型验证仍失败 | 低 | 高 | 回退到静态类型定义 |

### 4.3 里程碑检查点

**Milestone 1** (Week 1 结束):
- [ ] rcutils 编译通过
- [ ] 在开发板运行 rcutils 测试
- [ ] rosidl_runtime_c 编译通过

**Milestone 2** (Week 2 结束):
- [ ] rmw_dsoftbus 链接真实 rcutils/rosidl
- [ ] 移除大部分 mock 头文件
- [ ] 简单类型消息发布成功

**Milestone 3** (Week 3 结束):
- [ ] rosidl_generator_c 可生成代码
- [ ] 自定义消息类型编译通过
- [ ] 内省数据正确生成

**Milestone 4** (Week 4 结束):
- [ ] 跨设备 pub/sub 测试成功（多消息）
- [ ] 类型哈希验证工作
- [ ] 移植文档完成

---

## 第五部分：下一步行动

### 5.1 立即执行（今天）

1. **创建 rcutils BUILD.gn**
   - 列出 24 个源文件
   - 配置编译选项
   - 添加 libatomic 依赖

2. **验证 POSIX 兼容性**
   - 编写简单测试程序
   - 验证 clock_gettime, dlopen, getcwd
   - 在开发板运行

3. **创建 rosidl_runtime_c BUILD.gn**
   - 列出源文件
   - 依赖 rcutils
   - 配置头文件路径

### 5.2 本周目标

- [ ] rcutils 编译通过并部署到开发板
- [ ] rosidl_runtime_c 编译通过
- [ ] 更新 rmw_dsoftbus 依赖配置
- [ ] 运行基础功能测试

### 5.3 成功标准

**短期成功** (本周):
- rcutils 和 rosidl_runtime_c 在开发板正常运行
- rmw_dsoftbus 能链接真实库（不再依赖 mock）

**中期成功** (2 周):
- 内省数据正确生成
- 简单消息类型的 pub/sub 成功

**最终成功** (4 周):
- 跨设备 DDS 通信稳定
- 支持自定义消息类型
- 类型兼容性验证工作

---

## 附录：关键文件清单

### A. rcutils 源文件列表

```
src/allocator.c, src/array_list.c, src/char_array.c,
src/cmdline_parser.c, src/env.c, src/error_handling.c,
src/filesystem.c, src/find.c, src/format_string.c,
src/hash_map.c, src/logging.c, src/process.c,
src/qsort.c, src/repl_str.c, src/sha256.c,
src/shared_library.c, src/snprintf.c, src/split.c,
src/strcasecmp.c, src/strdup.c, src/strerror.c,
src/string_array.c, src/string_map.c,
src/time.c, src/time_unix.c
```

### B. rosidl_runtime_c 源文件列表

```
src/string.c
src/u16string.c
src/primitives_sequence.c
src/type_description__functions.c
src/type_description/field.c
src/type_description/field__functions.c
src/type_description/individual_type_description.c
src/type_description/individual_type_description__functions.c
src/type_description/type_description.c
src/type_description/type_description__functions.c
src/type_description/type_source.c
src/type_description/type_source__functions.c
```

### C. 需要 mock 的关键头文件

```
rosidl_runtime_c/
├── primitives_sequence.h          # 序列类型定义
├── string.h                       # 字符串类型
├── string_functions.h             # 字符串操作
└── type_description/              # 类型描述（完整目录）

rosidl_typesupport_introspection_c/
├── message_introspection.h        # MessageMembers 定义
├── field_types.h                  # 字段类型枚举
└── identifier.h                   # 类型支持标识符
```

---

**文档版本**: 1.0
**创建日期**: 2026-01-01
**作者**: Claude Code Agent
**项目**: ROS2 KaihongOS 移植
