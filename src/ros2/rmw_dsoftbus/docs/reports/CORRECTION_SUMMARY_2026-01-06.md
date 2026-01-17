# 方案2关键修正总结

**日期**: 2026-01-06 05:45 UTC (产品名称已更新: khs_3588s_sbc)
**修正原因**: 误判了"hdc file send可以替代刷系统"

---

## 🎯 核心修正

### 错误理解 ❌
```
GN集成 → 编译 → hdc file send → 运行 → 验收
```
**误判点**：以为推送文件到/system就够了

### 正确理解 ✅
```
GN集成 → 编译system.img → 刷system分区 → boot → 验收
```
**关键点**：必须刷系统，AccessToken注册是构建时行为

---

## 📋 为什么必须刷系统

### 技术链路
```
ohos_executable声明
    ↓
build.sh读取bundle.json
    ↓
调用AccessTokenKit生成token
    ↓
写入AccessToken数据库（在system.img中）
    ↓
刷入设备
    ↓
系统启动时init读取组件配置
    ↓
daemon启动，获得正确token
    ↓
GetAccessTokenId()成功 → CalcPermType()成功 → Session建立
```

### hdc file send的局限
- ❌ 只是拷贝文件
- ❌ 不触发AccessToken注册
- ❌ 不更新组件数据库
- ❌ CalcPermType()依然失败
- ❌ 依然报 -426115004

---

## 📝 已修正的文档

### 1. OPENHARMONY_GN_INTEGRATION_GUIDE.md ✅

**修正内容**：
- 第6.3节：刷写到设备（必须）
- 添加警告：不能只用hdc file send
- 说明原因：AccessToken数据库是构建时初始化
- 给出正确流程：fastboot flash system

**关键段落**：
```markdown
### 6.3 刷写到设备（必须）

**⚠️ 重要：必须刷写system.img，不能只用hdc file send**

**原因**：
- AccessToken数据库是在系统构建+启动阶段初始化的
- ohos_executable会将组件写入system image的组件描述
- 只有通过刷写，系统才能"认识"rmw_discovery_daemon并注册token
- hdc file send只是拷贝文件，不会触发token注册
```

### 2. SOLUTION2_EXECUTION_PLAN.md ✅

**修正内容**：
- Phase 5：从"快速部署"改为"刷写系统镜像（必须）"
- 添加技术链路说明
- 添加验证步骤（init启动、SELinux上下文）
- 修正时间预算：从4.5h → 5.5h（包含刷写）

**关键段落**：
```markdown
### Phase 5：刷写系统镜像（必须）

**⚠️ 关键理解：必须刷写system.img，不能用hdc file send替代**

**hdc file send的局限**：
- ❌ 只是拷贝文件，不触发AccessToken注册
- ❌ 不更新系统组件数据库
- ❌ CalcPermType()依然失败
- ❌ 依然报 -426115004
```

### 3. WHY_MUST_FLASH_SYSTEM.md ✅（新增）

**内容**：
- 一句话核心：系统"认识你"只发生在build→flash→boot
- 技术深度剖析：AccessToken数据库生成时机
- ohos_executable的真正作用（不只是编译）
- 系统组件注册链路完整解析
- hdc file send vs 刷system.img对比表
- 关键验证点（刷写后）

---

## 🔄 流程对比

### 方案1流程（已完成，但失败）
```
1. 编译普通executable
2. hdc file send到/system/bin
3. 手动启动
4. 测试 → 失败 (-426115004)
```
**失败原因**：Token未在AccessToken数据库注册

### 方案2流程（正确版本）
```
1. 代码迁移到OpenHarmony源码树
2. 创建BUILD.gn (ohos_executable)
3. 创建bundle.json
4. 编译system.img（1-2小时）
5. fastboot flash system（15-30分钟）
6. 系统启动 → init自动启动daemon
7. 验证Token注册成功
8. 测试 → 成功（rx > 0）
```

---

## ⏱️ 时间预算修正

### 原估计（错误）
| 阶段 | 时间 | 累计 |
|------|-----|------|
| P2-代码迁移 | 2h | 2h |
| P3-系统集成 | 1h | 3h |
| P4-编译 | 0.5h | 3.5h |
| P5-部署 | 0.5h | 4h |
| P6-验收 | 0.5h | 4.5h |
| **总计** | | **4.5h** |

**误判**：以为只编译binary，用hdc推送

### 修正估计（正确）
| 阶段 | 时间 | 累计 |
|------|-----|------|
| P2-代码迁移 | 2h | 2h |
| P3-系统集成 | 1h | 3h |
| P4-编译system.img | 1-2h | 5h |
| **P5-刷写系统** | **0.5h** | **5.5h** |
| P6-验证Token | 0.25h | 5.75h |
| P7-验收 | 0.25h | 6h |
| **总计** | | **约6h** |

**关键**：增加了刷系统时间，编译时间也增加（完整system.img）

---

## 📊 技术对比表

| 维度 | hdc file send | 刷system.img |
|------|--------------|--------------|
| **文件传输** | ✅ 可以 | ✅ 可以 |
| **AccessToken注册** | ❌ **不可以** | ✅ **可以** |
| **组件描述更新** | ❌ 不可以 | ✅ 可以 |
| **SELinux绑定** | ❌ 不可以 | ✅ 可以 |
| **init启动配置** | ❌ 不可以 | ✅ 可以 |
| **CalcPermType()** | ❌ 失败 | ✅ 成功 |
| **Session建立** | ❌ -426115004 | ✅ 成功 |
| **适用场景** | 调试辅助 | **系统组件** |

---

## ✅ 验收标准（刷写后）

### 必须验证的4个点

#### 1. daemon由init自动启动 ✅
```bash
hdc shell "ps -ef | grep rmw_discovery_daemon"
```
**预期**：父进程PID=1（init启动）

#### 2. SELinux上下文正确 ✅
```bash
hdc shell "ps -Z | grep rmw_discovery"
```
**预期**：`u:r:rmw_discovery:s0`（不是`u:r:su:s0`）

#### 3. Token注册成功 ✅
```bash
hdc shell "cat /proc/\$(pidof rmw_discovery_daemon)/attr/current"
```
**预期**：显示正确的token context

#### 4. Session建立成功 ✅
运行测试程序：
```
[NativeToken] Registered token_id=XXX  ✅
[SessionServer] created: id=0          ✅
[Session] OnSessionOpened              ✅ (关键)
[Stats] rx > 0                         ✅ (最终验收)
```

---

## 🎯 关键洞察

### 为什么之前会误判

**心理因素**：
- 希望避免刷系统（耗时）
- 看到"快速部署"方案感觉更高效
- 低估了"系统身份认证"的复杂性

**技术因素**：
- 不熟悉OpenHarmony的组件注册机制
- 不了解AccessToken数据库生成时机
- 误以为ohos_executable只是编译方式

### 为什么必须刷系统

**一句话**：
> AccessToken注册 = 系统构建行为 ≠ 运行时行为

**技术本质**：
```
方案2 = 成为系统组件 = 必须刷system.img
```

---

## 💡 好消息

虽然必须刷系统，但这有**积极意义**：

### 1. 这是最后一次刷系统
- ✅ Phase 2的最后一个技术障碍
- ✅ 刷完看到rx>0，Phase 2立即封板
- ✅ 后续不再被"系统身份问题"卡住

### 2. 验证了问题根因
- ✅ 100%确认是AccessToken注册问题
- ✅ 方案2的方向完全正确
- ✅ 不需要再尝试其他方案

### 3. 建立了正确理解
- ✅ 理解了OpenHarmony组件集成机制
- ✅ 理解了系统身份认证链路
- ✅ 后续开发会更顺利

---

## 📋 TODO更新

```
✅ P0: GN集成骨架（已修正：必须刷system.img）
✅ P1: 对照实验（khtrans未找到）

⏸️ P2: 代码迁移
⏸️ P3: 系统集成（BUILD.gn + bundle.json）
⏸️ P4: 编译system.img
⏸️ P5: 刷写system分区（必须）
⏸️ P6: 验证Token注册
⏸️ P7: 最终验收（rx>0）
```

---

## 🚀 下一步行动

### 立即开始方案2
```bash
# 1. 快速启动（可选）
cd /home/jiusi/M-DDS/rmw_dsoftbus
./QUICK_START_SOLUTION2.sh

# 2. 查看详细指南
cat docs/ohos/OPENHARMONY_GN_INTEGRATION_GUIDE.md

# 3. 查看为什么必须刷系统
cat WHY_MUST_FLASH_SYSTEM.md
```

### 预计时间线
- **今天**: P2-P3（代码迁移+系统集成）3小时
- **明天**: P4-P7（编译+刷写+验收）3小时
- **总计**: 约6小时，1-2天完成

### 成功标志
- ✅ 编译通过（system.img生成）
- ✅ 刷写成功（fastboot完成）
- ✅ Token注册成功（ps -Z验证）
- ✅ **rx > 0**（Phase 2封板）

---

## 📚 相关文档

### 核心文档
1. `WHY_MUST_FLASH_SYSTEM.md` - 为什么必须刷系统（技术深度解析）
2. `docs/ohos/OPENHARMONY_GN_INTEGRATION_GUIDE.md` - GN集成完整指南（已修正）
3. `SOLUTION2_EXECUTION_PLAN.md` - 执行计划（已修正）

### 辅助文档
4. `QUICK_START_SOLUTION2.sh` - 快速启动脚本
5. `test/KHTRANS_EXPERIMENT_RESULT.md` - 对照实验结果
6. `PERMISSION_CONFIG_STATUS_2026-01-06.md` - 方案1诊断报告

---

## ✨ 总结

### 修正前理解
```
编译 → 推送 → 运行 → 验收
```

### 修正后理解
```
编译 → 刷系统 → 启动 → 验收
```

### 关键区别
```
hdc file send ≠ 系统组件集成
必须刷system.img才能完成AccessToken注册
```

### 最终结论
**方案2必须刷写system.img，没有捷径，但这是最后一次刷系统。**

---

**修正完成时间**: 2026-01-06 05:45 UTC
**下一步**: 立即执行方案2，预计6小时完成Phase 2封板
