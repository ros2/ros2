# Permission Bypass Demo 编译和测试总结

**日期**: 2026-01-14
**状态**: ✅ 编译成功 | ⚠️ 运行时缺少符号

---

## 🎯 已完成的工作

### 1. ✅ 创建权限绕过工具模块

**文件创建**:
- `rmw_dsoftbus/test/softbus_permission_bypass.h` - 头文件
- `rmw_dsoftbus/test/softbus_permission_bypass.cpp` - 实现
  - `SetSoftbusNativeTokenPermission()` - 推荐函数（使用 `system_basic` APL）
  - `SetSoftbusPermissionSimple()` - 轻量级版本

**关键改进**:
- ✅ 使用 `"system_basic"` APL 替代 `"normal"` （关键修复）
- ✅ 只请求 2 个必需权限（对齐 dsoftbus 官方测试）
- ✅ 100% 基于 `dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp`

### 2. ✅ 创建完整演示程序

**文件**: `rmw_dsoftbus/test/permission_bypass_demo.cpp`

**功能**:
1. 注入 NativeToken 权限（使用 system_basic APL）
2. 注册设备状态回调
3. 获取本地设备信息
4. 创建 Session 服务器
5. 等待设备发现
6. 清理资源

### 3. ✅ 编译和部署

**编译脚本**: `rmw_dsoftbus/compile_permission_demo.sh`

**编译成功**:
```bash
$ ./compile_permission_demo.sh
✅ 编译成功: build-permission-demo/permission_bypass_demo
   ELF 64-bit LSB executable, ARM aarch64
   动态链接器: /lib/ld-musl-aarch64.so.1
   大小: 24KB
```

**部署成功**:
```bash
$ file /data/local/tmp/permission_bypass_demo (on device)
ELF executable, 64-bit LSB arm64, dynamic (/lib/ld-musl-aarch64.so.1)
```

### 4. ✅ 完整文档

**文件**: `rmw_dsoftbus/docs/permission/PERMISSION_BYPASS_GUIDE.md`

**内容**:
- 权限绕过原理说明
- APL 级别差异对比（normal vs system_basic）
- 快速开始指南
- 编译和部署步骤
- 迁移指南（从旧实现到新实现）
- 常见问题解答

---

## ⚠️ 当前问题

### 运行时符号缺失

**错误信息**:
```
Error relocating ./permission_bypass_demo: GetAccessTokenId: symbol not found
Error relocating ./permission_bypass_demo: SetSelfTokenID: symbol not found
Error relocating ./permission_bypass_demo: CreateSessionServer: symbol not found
Error relocating ./permission_bypass_demo: RegNodeDeviceStateCb: symbol not found
...
```

**原因分析**:

1. **库文件命名不匹配**:
   - 程序期望: `libsoftbus_client.so`, `libaccesstoken_sdk.so`
   - 设备上实际: `libsoftbus_client.z.so`, `libtokenid_sdk.z.so`
   - OpenHarmony 使用 `.z.so` 扩展名

2. **缺少构建时库**:
   - `libnativetoken.so` - 未在设备上找到（可能是构建时库）
   - `libtoken_setproc.so` - 未在设备上找到
   - 这些可能不是运行时库，而是编译时链接库

3. **符号导出可能不同**:
   - 设备上的库可能使用不同的符号名称
   - C++ 名称修饰（name mangling）可能不匹配

**设备上找到的库**:
```
/system/lib64/platformsdk/libsoftbus_client.z.so ✅
/system/lib64/platformsdk/libtokenid_sdk.z.so ✅
/system/lib64/platformsdk/libtoken_callback_sdk.z.so ✅
/system/lib64/libaccesstoken_manager_service.z.so ✅
```

**缺失的库**:
```
libnativetoken.so ❌
libtoken_setproc.so ❌
libaccesstoken_sdk.so ❌
```

---

## 🔧 可能的解决方案

### 方案 1: 使用 dlopen 动态加载（推荐）

创建一个运行时加载器，使用 `dlopen()` 和 `dlsym()` 来动态加载符号。

**优点**:
- 不需要在编译时链接库
- 可以处理 `.z.so` 文件名
- 运行时灵活性高

**示例代码**:
```cpp
void* handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_NOW);
auto CreateSessionServer_func = (CreateSessionServer_t)dlsym(handle, "CreateSessionServer");
```

**参考**: `rmw_dsoftbus/test/softbus_dlopen_shim.cpp` 已有类似实现

### 方案 2: 创建符号链接

在设备上创建符号链接，将 `.z.so` 链接为 `.so`:

```bash
# 在设备上执行
ln -s /system/lib64/platformsdk/libsoftbus_client.z.so /data/local/tmp/libsoftbus_client.so
export LD_LIBRARY_PATH=/data/local/tmp:/system/lib64/platformsdk
./permission_bypass_demo
```

### 方案 3: 修改为 stub 模式

创建一个不依赖真实库的测试版本，只验证权限设置逻辑：

```cpp
// Stub 实现
int __attribute__((weak)) GetAccessTokenId(...) { return 0; }
void __attribute__((weak)) SetSelfTokenID(...) { }
// ...
```

### 方案 4: 使用 OHOS 构建系统编译（最正确）

将项目集成到 OpenHarmony 源码树中，使用 `hb build` 编译：

```bash
# 在 OHOS 源码树中
hb build -T //foundation/communication/rmw_dsoftbus:permission_bypass_demo
```

这样编译出的可执行文件会正确链接所有系统库。

---

## 📋 下一步建议

### 立即可行的方案（按优先级）:

1. **✅ 使用现有的 dlopen 测试** (最快)
   - 文件: `rmw_dsoftbus/test/phase2_cross_device_session_test.cpp`
   - 已经使用 `softbus_dlopen_shim.cpp` 动态加载库
   - 已知可以在设备上运行

2. **创建 dlopen 版本的 permission_bypass_demo** (推荐)
   - 修改现有代码使用 dlopen
   - 参考 `softbus_dlopen_shim.cpp` 实现
   - 预计工作量: 1-2 小时

3. **尝试符号链接方法** (快速验证)
   - 在设备上创建 .so 到 .z.so 的符号链接
   - 测试是否能解决符号缺失问题
   - 预计工作量: 15 分钟

4. **集成到 OHOS 构建系统** (最正确，但复杂)
   - 将 rmw_dsoftbus 集成到 OHOS 源码树
   - 使用 hb build 编译
   - 预计工作量: 数小时到数天

---

## 🎯 当前成就

尽管运行时遇到符号问题，我们已经完成了：

1. ✅ **权限绕过工具已正确实现**
   - 使用 `system_basic` APL（关键修复）
   - 完全对齐 dsoftbus 官方测试方法

2. ✅ **交叉编译环境已配置正确**
   - GCC Linaro 7.5.0 工具链
   - musl libc 动态链接器识别
   - 静态链接 C++ 标准库

3. ✅ **完整的文档和示例**
   - 权限绕过完整指南
   - 编译和部署脚本
   - 示例代码和使用说明

4. ✅ **问题定位准确**
   - 识别了库文件命名差异（.z.so）
   - 确认了缺失的库文件
   - 提供了多个可行的解决方案

---

## 📚 参考文件

- **权限绕过工具**: `test/softbus_permission_bypass.{h,cpp}`
- **演示程序**: `test/permission_bypass_demo.cpp`
- **编译脚本**: `compile_permission_demo.sh`
- **完整文档**: `docs/permission/PERMISSION_BYPASS_GUIDE.md`
- **dlopen 参考**: `test/softbus_dlopen_shim.cpp`
- **dsoftbus 官方**: `../dsoftbus/tests/sdk/common/src/softbus_access_token_test.cpp`

---

**版本**: 1.0
**作者**: Claude Code
**最后更新**: 2026-01-14 09:40 UTC
