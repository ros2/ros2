# 为什么必须刷写system.img - 技术深度解析

**日期**: 2026-01-06
**关键结论**: 方案2必须刷写system.img，hdc file send不能替代

---

## 🎯 一句话核心

> **方案2不是"把程序拷到/system"，而是"让系统在启动时就认识你这个程序"**

系统"认识你"，只发生在：**build → image → flash → boot**

不发生在：`hdc file send`

---

## 📋 误判复盘

### 我之前的错误理解
```
GN集成 → build → hdc file send到/system/bin → 运行 → 验收
                      ↑
                  误判点：以为推送文件就够了
```

### 正确理解
```
GN集成 → build system.img → flash system分区 → boot → init启动 → 验收
                                    ↑
                              必须的步骤，不可绕过
```

---

## 🔍 技术深度剖析

### 问题1：AccessTokenKit的token注册不是运行时行为

我们要解决的链路（已100%确认）：

```
GetAccessTokenId()
  → AccessToken数据库
    → CalcPermType()
      → CreateSessionServer成功
```

**关键事实**：

> AccessToken数据库是在**系统构建+启动阶段**初始化的，
> 不是你拷个ELF进去就会更新的

如果只是：
```bash
hdc file send rmw_discovery_daemon /system/bin/
```

那么：
- ❌ 这个binary**不会自动注册token**
- ❌ `GetAccessTokenId()`拿不到system_app对应的合法token
- ❌ `CalcPermType()`仍然失败
- ❌ 错误码仍然是 `-426115004`

---

### 问题2：ohos_executable ≠ "编译方式"

`ohos_executable`的真正作用：

| 层面 | 作用 |
|------|-----|
| 编译层 | 生成ELF binary ✅ |
| **系统层** | **写入system image的组件描述** ✅ |
| **身份层** | **参与AccessToken生成** ✅ |
| **安全层** | **参与SELinux domain绑定** ✅ |
| **启动层** | **参与init启动与身份绑定** ✅ |

**关键**：后4项只在 **build system.img** 时生效！

---

### 问题3：系统组件注册链路

#### 正确的链路（必须刷系统）

```
1. 源码树集成
   foundation/communication/rmw_dsoftbus/
   ├── BUILD.gn (ohos_executable声明)
   └── bundle.json (组件元数据)

2. GN构建处理
   ./build.sh --product-name khd_rk3588s_sbc
   ↓
   读取bundle.json
   ↓
   将rmw_dsoftbus注册为系统组件
   ↓
   调用GetAccessTokenId()生成token
   ↓
   写入AccessToken数据库（在system.img中）

3. 生成system.img
   out/khd_rk3588s_sbc/packages/phone/images/system.img
   ├── /system/bin/rmw_discovery_daemon (binary)
   ├── /system/lib64/librmw_dsoftbus.so (library)
   └── 组件描述 + AccessToken数据库 (元数据)

4. 刷入设备
   fastboot flash system system.img
   ↓
   system分区被替换
   ↓
   包含了组件描述和token数据库

5. 系统启动
   kernel → init
   ↓
   读取组件配置（在system.img中）
   ↓
   启动rmw_discovery_daemon
   ↓
   设置正确的SELinux上下文: u:r:rmw_discovery:s0
   ↓
   daemon调用GetAccessTokenId()
   ↓
   从AccessToken数据库读取（成功！）
   ↓
   CalcPermType()返回SYSTEM_APP ✅
   ↓
   CreateSessionServer成功 ✅
```

#### 错误的链路（只用hdc file send）

```
1. hdc file send rmw_discovery_daemon /system/bin/
   ↓
   只是拷贝了binary文件
   ↓
   AccessToken数据库没有更新 ❌

2. 手动启动 rmw_discovery_daemon
   ↓
   进程以root身份运行（u:r:su:s0）
   ↓
   调用GetAccessTokenId()
   ↓
   AccessToken数据库中找不到记录 ❌
   ↓
   CalcPermType()返回异常值 ❌
   ↓
   CreateSessionServer失败 ❌
   ↓
   错误码: -426115004 (PEER_SESSION_NOT_CREATED)
```

---

## 🔬 AccessToken数据库的生成时机

### 数据库内容示例

假设刷写后，AccessToken数据库包含：

```
TokenID: 0x12345678
ProcessName: rmw_discovery_daemon
APL: system_core
Type: NATIVE_TOKEN
UID: 1024
GID: 1024
SeconContext: u:r:rmw_discovery:s0
```

### 这个数据库在哪生成？

**答案：在构建system.img时**

**代码路径**（OpenHarmony源码）：
```
base/security/access_token/
├── services/tokensyncmanager/  (token管理服务)
└── interfaces/innerkits/        (GetAccessTokenId API)

构建流程：
1. build.sh读取bundle.json
2. 调用access_token组件
3. 根据ohos_executable的NativeTokenInfoParams生成token
4. 写入数据库文件（打包进system.img）
```

### 为什么hdc file send不触发数据库更新？

因为：
- 数据库是**只读文件**（在/system分区）
- 只能在**构建时**生成
- **运行时**不可修改
- hdc file send只是拷贝binary，不触发构建流程

---

## 🚨 什么时候"真的可以不刷系统"？

**只有一种情况**：

> 你的当前ROM本身已经包含了
> 一个**通过GN构建、已注册native/system token的SoftBus测试程序**
> 而你只是"复用它的身份运行自己的代码"

这在我们的环境下**不成立**，因为：
- ✅ 已验证：普通ELF + root + permissive → 不被承认
- ✅ 已验证：JSON权限 → 不解决token
- ✅ khtrans_native_test未找到 → 无法复用

我们现在做的方案2，本质就是：
**"把自己变成ROM里的系统组件"**

而ROM里的东西，**不刷是进不去的**。

---

## 📊 hdc file send vs 刷system.img对比

| 维度 | hdc file send | 刷system.img |
|------|--------------|--------------|
| **文件传输** | ✅ 可以 | ✅ 可以 |
| **AccessToken注册** | ❌ **不可以** | ✅ **可以** |
| **组件描述更新** | ❌ 不可以 | ✅ 可以 |
| **SELinux domain绑定** | ❌ 不可以 | ✅ 可以 |
| **init启动配置** | ❌ 不可以 | ✅ 可以 |
| **CalcPermType()成功** | ❌ 失败 | ✅ 成功 |
| **Session建立** | ❌ -426115004 | ✅ 成功 |
| **适用场景** | 调试辅助文件 | **系统组件集成** |

---

## 🎯 正确的验收流程

### ❌ 错误流程（我之前的理解）
```
1. 编译 → 生成binary
2. hdc file send → 推送到/system/bin
3. hdc shell rmw_discovery_daemon → 手动启动
4. 测试 → 期望Session建立 ❌
```

**结果**：依然失败，因为token未注册

### ✅ 正确流程
```
1. 代码迁移到OpenHarmony源码树
2. 编译 → 生成system.img（包含token数据库）
3. fastboot flash system → 刷入设备
4. reboot → 系统启动，init自动启动daemon
5. 验证 → ps -Z显示正确上下文 ✅
6. 测试 → Session建立成功 ✅
```

---

## 🔑 关键验证点（刷写后）

### 验证1：daemon由init自动启动
```bash
hdc shell "ps -ef | grep rmw_discovery_daemon"
```
**预期**：
```
softbus  1234  1  ...  rmw_discovery_daemon
```
**关键**：父进程PID=1（init启动），不是手动启动

### 验证2：SELinux上下文正确
```bash
hdc shell "ps -Z | grep rmw_discovery"
```
**预期**：
```
u:r:rmw_discovery:s0  ...  rmw_discovery_daemon
```
**不是**：`u:r:su:s0`（root）

### 验证3：Token可查询
```bash
hdc shell "cat /proc/\$(pidof rmw_discovery_daemon)/attr/current"
```
**预期**：显示正确的token context

### 验证4：CalcPermType成功
运行测试程序，应该看到：
```
[NativeToken] Registered token_id=XXX (verify=XXX)  ✅
[DiscoveryManager] SessionServer created: id=0      ✅
[Session] OnSessionOpened callback                  ✅ (关键)
[Stats] rx > 0                                      ✅ (最终验收)
```

---

## 💡 为什么这是"最后一次刷"

好消息：
- ✅ 这是Phase 2的最后一个技术障碍
- ✅ 刷完只要看到一次**rx > 0**，Phase 2就封板
- ✅ 后面Phase 3再也不会被"系统身份问题"卡住
- ✅ 后续迭代只需要更新代码，不需要反复刷系统

**你现在已经走到系统软件工程的边界了**，
这一步跨过去，后面会非常顺。

---

## 📝 总结

### 技术本质
```
AccessToken注册 = 系统构建行为 ≠ 运行时行为
```

### 正确理解
```
方案2 = 成为系统组件 = 必须刷system.img
```

### 操作要点
```
build → system.img → flash → boot → 验证
```

### 验收标准
```
1. daemon由init启动 ✅
2. SELinux上下文正确 ✅
3. Token注册成功 ✅
4. Session建立成功 ✅
5. rx > 0 ✅
```

---

**结论**：必须刷写system.img，没有捷径，但这是最后一次。

**下一步**：执行完整的方案2流程，刷写系统，验收封板。
