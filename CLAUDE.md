# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **ROS2 to KaihongOS (OpenHarmony) port** project that ports the Robot Operating System 2 to run natively on KaihongOS (ARM64 aarch64) running on rk3588s development boards. The project has two parallel tracks:

- **Track 1: ROS2 Source Migration** - Porting ROS2 components (Foundation, RCL, RCLCPP) using GN build system
- **Track 2: rmw_dsoftbus Development** - Implementing a custom ROS2 middleware (RMW) layer based on OpenHarmony's dsoftbus (inter-process communication framework)

### Current State (2026-01-05)

**Track 1 (ROS2 Migration):**
- Foundation layer: ✅ Complete (rcutils, rcpputils, rosidl_runtime_c, etc.)
- RCL layer: ✅ Compilation complete, 52/52 RMW tests passing
- RCLCPP layer: 🔄 Talker end-to-end validation complete (20/20 messages verified)

**Track 2 (rmw_dsoftbus):**
- Phase 1 (Session-based Pub/Sub): ✅ Complete
- Phase 2 (Graph Discovery): ✅ Code complete (Hardware verification pending device access)
- Phase 3+ (Service/Client, 1:N routing): ⏸️ Pending
- **Overall completion: 85%** (P0 features 100%, Graph Discovery 100% code-complete)

### Key Technical Achievement

Successfully implemented **zero-DDS ROS2** (Clean RMW) - a minimal ROS2 middleware that runs without FastDDS/CycloneDDS dependencies, demonstrated end-to-end with Talker running on real KaihongOS hardware (rk3588s ARM64).

## Build System & Commands

### GN Build System (Primary)

The project uses **GN** (Google's build system) for cross-compilation targeting aarch64-linux-ohos.

**Build Root File:** `/ros2/BUILD.gn` (90 lines)

**Configuration:** `/ros2/.gn` (7 lines) specifies:
- Target OS: ohos
- Target CPU: arm64
- Buildconfig: `//build_config/BUILDCONFIG.gn`

### Quick Build Commands

```bash
# Build entire default target (Foundation + RCL + rmw_dsoftbus + demos)
gn gen out/Default
ninja -C out/Default

# Build specific targets
ninja -C out/Default //src/ros2/rcl/rcl:rcl              # RCL library
ninja -C out/Default //src/ros2/rmw_dsoftbus:rmw_dsoftbus_cpp  # RMW middleware
ninja -C out/Default //demo_cpp:talker                   # Talker demo

# Build tests
ninja -C out/Default tests
```

### Build Output Structure

```
out/Default/
├── librcutils.so              # Core C utilities
├── librcl.so                  # ROS Client Library (359KB)
├── librmw_dsoftbus_cpp.so    # Custom RMW middleware (123-253KB)
├── librcpputils.so            # C++ utilities
├── librosidl_runtime_c.so     # Type runtime support
├── talker                     # Publisher demo
├── listener                   # Subscriber demo
└── gen/                       # Generated files
    ├── builtin_interfaces/    # Time, Duration types
    ├── std_msgs/              # Standard message types
    ├── geometry_msgs/         # Geometry types
    └── sensor_msgs/           # Sensor types (21 total interface packages)
```

### Cross-Compilation Details

**Compiler:** OpenHarmony clang toolchain
- Location: `/home/jiusi/M-DDS/OpenHarmony/prebuilts/clang/ohos/linux-x86_64/llvm/bin/clang`
- Target: aarch64-linux-ohos
- Sysroot: `/home/jiusi/M-DDS/OpenHarmony/prebuilts/ohos-sdk/linux/11/native/sysroot`

**Key Configuration:**
- Weak symbols for dsoftbus APIs (real libsoftbus_client.so at runtime)
- Static C++ runtime (libc++_static) to avoid ABI conflicts
- CMake + GN dual support for different components

### Manual Compilation Scripts

For direct compilation without GN (useful for isolated testing):

```bash
# Build RCL test
./build_rcl_test.sh

# Build RMW direct test (Clean RMW testing)
./build_rmw_direct_test.sh

# Deploy and test
./deploy_step_a2.sh
./run_foundation_tests.sh
```

## Code Architecture & Structure

### Layer Organization

```
User Application Code
         ↓
RCLCPP Layer (C++ API) - src/ros2/rclcpp/
    ↓           ↓            ↓
rclcpp    rclcpp_action  rclcpp_lifecycle
         ↓
RCL Layer (C API) - src/ros2/rcl/
    ↓              ↓               ↓
rcl         rcl_action      rcl_lifecycle
         ↓
RMW Interface (Abstract) - src/ros2/rmw/
    ↓
rmw_dsoftbus Implementation (Custom) - src/ros2/rmw_dsoftbus/
    ↓
OpenHarmony dsoftbus Backend
    ↓
Kernel IPC / Network Layer
```

### Core Components

**Foundation Layer** (src/ros2/):
- `rcutils/` - C utilities (memory, string, logging)
- `rcpputils/` - C++ utilities (containers, smart pointers)
- `rosidl_*` - Type support and introspection

**Middleware Layer** (src/ros2/):
- `rmw/` - RMW interface definition (abstract)
- `rcl/` - ROS Client Library (depends on RMW)
- `rmw_dds_common/` - DDS-specific utilities

**rmw_dsoftbus Implementation** (src/ros2/rmw_dsoftbus/):
- `include/rmw_dsoftbus/` - Public headers
  - `session_manager.h` - Session lifecycle management (380 lines)
  - `types.h` - Data structures
  - `qos_mapper.h` - QoS policy mapping
- `src/` - Implementation
  - `rmw_init.cpp` - Middleware initialization
  - `rmw_publisher.cpp` - Publication implementation
  - `rmw_subscription.cpp` - Subscription implementation
  - `rmw_node.cpp` - Node management
  - `rmw_wait.cpp` - Wait set (select-based)
  - `rmw_guard_condition.cpp` - Event signaling
  - `rmw_service.cpp` - RPC service (stub Phase 2)
  - `rmw_client.cpp` - RPC client (stub Phase 2)
  - `session_manager.cpp` - Core session management (300 lines)
  - `dsoftbus_stubs.cpp` - Weak symbol implementations for cross-compilation
  - `rmw_typesupport_serializer.cpp` - CDR serialization (675 lines, Phase 2.1)
  - `graph_*.cpp` - Graph discovery (Phase 2 complete)

**Interface Packages** (generated/):
21 ROS2 standard message/service packages:
- builtin_interfaces, std_msgs, geometry_msgs, sensor_msgs, etc.
- Generated from `.idl` files via rosidl_generator_c

### Key Architectural Decisions

1. **Session-based Design** (Phase 1)
   - Single backend focused on OpenHarmony dsoftbus
   - Publisher: Active (OpenSession → SendBytes)
   - Subscriber: Passive (CreateSessionServer → OnBytesReceived callback)
   - Deleted: TransportController + 3-backend abstraction (~4,400 LOC removed)

2. **Serialization System** (Phase 2.1)
   - GenericCDRSerializer: Universal serializer for all ROS2 types
   - Based on rosidl_typesupport_introspection_c (runtime reflection)
   - Supports nested messages, strings, dynamic arrays
   - Replaces per-type manual serialization

3. **Graph Discovery** (Phase 2.5)
   - Multi-layer architecture:
     - In-process: GraphCache + guard condition trigger loop
     - Inter-process: Unix Domain Socket IPC protocol (64-byte header + TLV)
     - Cross-device: dsoftbus Discovery Protocol v3.1 (97-byte header, 7 message types)
   - Daemon authority model: Single daemon process manages network topology

4. **Type System**
   - Introspection-based type runtime (not codegen-based)
   - Supports arbitrary ROS2 message structures
   - Generic serialization without per-message handwritten code

### Important Files for Development

**Configuration:**
- `.gn` - GN build system root config
- `BUILD.gn` - Root target definitions
- `.claude/cicd_config.json` - CI/CD automation rules (if present)
- `build_config/BUILDCONFIG.gn` - Build settings

**RMW Implementation:**
- `src/ros2/rmw_dsoftbus/include/rmw_dsoftbus/session_manager.h` - Session API
- `src/ros2/rmw_dsoftbus/src/rmw_*.cpp` - RMW API implementations
- `src/ros2/rmw_dsoftbus/BUILD.gn` - rmw_dsoftbus build target

**Tests:**
- `test/` - Test programs
  - `foundation_test/` - ROS2 foundation validation
  - `rcl_test/` - RCL layer validation
  - `minimal_rcl/` - Minimal RCL pub/sub
  - `cross_device/` - Multi-device communication

**Demos:**
- `demo_cpp/` - C++ talker/listener
  - `src/talker.cpp` - Publisher (hand-written CDR serialization)
  - `src/listener.cpp` - Subscriber

## Development Workflow

### When to Use `/feature-dev` (7-stage workflow)

**Default for:** New features, new problems, new requirements
- Requirement clarification → Code exploration → Architecture design → Implementation → Testing → Code review → Summary

Use this when the task is non-trivial or involves multiple files/architectural decisions.

### RMW API Implementation Pattern

When adding/fixing RMW APIs:

1. **Check interface definition:** `src/ros2/rmw/rmw/include/rmw/` (abstract)
2. **Implement in rmw_dsoftbus:** `src/ros2/rmw_dsoftbus/src/rmw_*.cpp`
3. **Register SessionManager hooks** if needed (e.g., on_subscription_init, on_publisher_destroy)
4. **Update tests:** Add test cases in `test/` directory
5. **Verify compilation:** `ninja -C out/Default //src/ros2/rmw_dsoftbus:rmw_dsoftbus_cpp`

### Common Development Tasks

**Add a new RMW API:**
```bash
# 1. Define skeleton in src/ros2/rmw_dsoftbus/src/
# 2. Build to check for errors
ninja -C out/Default //src/ros2/rmw_dsoftbus:rmw_dsoftbus_cpp

# 3. Test with existing test suite
ninja -C out/Default tests
```

**Test on hardware (rk3588s):**
```bash
# Deploy libraries
./deploy_step_a2.sh

# Run test via HDC (from WSL, use powershell.exe)
DEVICE_ID=$(powershell.exe -NoProfile -Command "hdc list targets" | head -1 | awk '{print $1}' | tr -d '\r\n')
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell './system/lib64/talker'"
```

**Debug type serialization issues:**
Check `rmw_typesupport_serializer.cpp` (GenericCDRSerializer) for:
- Type introspection walking logic
- Memory allocation for strings/arrays
- CDR byte order conversions
- Nested message recursion

## Important Constraints & Environment

### WSL Ubuntu 20.04 Environment

- Host: WSL Ubuntu 20.04 (Windows)
- Target: rk3588s (ARM64 aarch64) running KaihongOS
- Cross-compilation: OpenHarmony SDK clang toolchain

### HDC Tool Access (Device Deployment)

HDC (HarmonyOS Device Connector) is installed on Windows only.

**⚠️ Critical:** All HDC commands must be called via `powershell.exe` from WSL:

```bash
# ❌ WRONG (will fail)
hdc shell 'ls'

# ✅ CORRECT
powershell.exe -NoProfile -Command "hdc shell 'ls'"

# Multi-device: specify with -t
DEVICE_ID=$(powershell.exe -Command "hdc list targets" | head -1 | awk '{print $1}' | tr -d '\r\n')
powershell.exe -Command "hdc -t $DEVICE_ID file send 'C:\local\file.so' '/system/lib64/'"
```

### File Transfer Paths

File transfer requires routing through `/mnt/c/` (WSL mount of C:\ drive):

```bash
# WSL → C:\ → Device
mkdir -p /mnt/c/tmp/hdc_transfer
cp /home/user/librmw.so /mnt/c/tmp/hdc_transfer/
powershell.exe -Command "hdc file send 'C:\tmp\hdc_transfer\librmw.so' '/system/lib64/'"
```

### Device Configuration

**RMW Environment Variables** (set on device):
```bash
export RMW_IMPLEMENTATION=rmw_dsoftbus_cpp      # Use custom middleware
export RMW_DSOFTBUS_PEER_ID="<network_id>"    # For Publisher (device B)
export RMW_DSOFTBUS_QOS_MODE=RELIABLE_PLAIN    # Optional: logging mode
```

**Permission Configuration:**
Must install `/system/etc/communication/softbus/softbus_trans_permission.json` on device (template: `src/ros2/rmw_dsoftbus/config/`).

## Testing & Validation

### Test Categories

**Foundation Tests** - Validate ROS2 foundation libraries:
```bash
ninja -C out/Default //test/foundation_test:foundation_tests
```

**RCL Tests** - Validate ROS Client Library:
```bash
ninja -C out/Default //test/rcl_test:test_rcl_basic
```

**RMW Verification** - Validate middleware (52 tests):
```bash
# Built as part of default
./out/Default/rmw_verify_test
```

**Integration Tests** - End-to-end Talker/Listener:
```bash
ninja -C out/Default //demo_cpp:talker //demo_cpp:listener
./out/Default/talker &
./out/Default/listener
```

### Hardware Validation (rk3588s)

**Deployment:**
```bash
./deploy_step_a2.sh  # Comprehensive deployment script
```

**Talker Test (100% message delivery):**
- Runs 20 iterations of std_msgs/String publication
- Verifies CDR serialization format
- Confirms UDP transport delivery
- Expected: 20/20 success ✅

### Known Test Passing Status

- Foundation layer: 5/5 tests (rcutils, rcpputils, rosidl_runtime_c, etc.)
- RCL layer: 52/52 RMW verification tests
- Graph Discovery: Code complete, hardware verification pending
- Talker demo: 20/20 messages delivered on rk3588s

## Progress Tracking & Documentation

### Active Documentation

Check these for current status:

**Latest Reports:**
- `CLEAN_RMW_SUCCESS_REPORT.md` - Most recent validation (2026-01-03)
- `PHASE2_FINAL_STATUS.md` - Graph Discovery completion status
- `docs/progress.md` - Auto-updated progress log (if hooked)

**Architecture Documents:**
- `docs/RMW_DSOFTBUS_GAP_ANALYSIS.md` - Feature completeness analysis
- `docs/RMW_DSOFTBUS_DESIGN_REQUIREMENTS.md` - Architecture requirements
- `docs/OPENHARMONY_PORTING_GUIDE.md` - General OHOS porting guide (1588 lines)

**Phase-specific:**
- Phase 1 (Session): `rmw_dsoftbus/SESSION_RMW_REFACTORING_COMPLETE.md`
- Phase 2 (Graph): `PHASE2_FINAL_STATUS.md`, `PHASE2_GRAPH_DISCOVERY_COMPLETE.md`

### Code Metrics

Current codebase size:
- rmw_dsoftbus: ~9,000 LOC (Session-based, -30% from 13,000 before Phase 1)
- Generated interfaces: 21 packages (std_msgs, geometry_msgs, etc.)
- RCL layer: 359KB compiled
- Full ROS2 stack: 2.5 MB on device

## Troubleshooting Guide

### Common Issues

**Issue: Compilation fails with missing rmw API**
- Check: Is it in `src/ros2/rmw/rmw/include/rmw/*.h`?
- If missing: Need to stub in rmw_dsoftbus (return RMW_RET_UNSUPPORTED for Phase 2 features)

**Issue: Type serialization errors (ret=11)**
- Check: `rmw_typesupport_serializer.cpp` (GenericCDRSerializer)
- Verify: Type introspection is finding all fields
- Debug: Enable logging in `rmw_publish`/`rmw_take`

**Issue: Device connection refused**
- Check: Device permissions (HDC connect-key) - use powershell.exe
- Check: RMW environment variables set on device
- Check: dsoftbus permission file deployed to `/system/etc/`

**Issue: Graph Discovery returns empty**
- Status: Phase 2 code complete, hardware verification pending
- Workaround: Phase 2.1 onwards provides fallback APIs

## Key Dependencies & Tools

- **GN build system**: Google's meta-build system (Ninja generator)
- **OpenHarmony SDK**: Clang 15.0.4 toolchain
- **dsoftbus**: OpenHarmony's inter-process communication framework
- **Rosidl**: ROS interface definition language (IDL) code generator
- **CMake**: Alternative build system (for some components)

## When to Delegate to Specialist Agents

Per project CLAUDE.md instructions:

| Condition | Agent |
|-----------|-------|
| dsoftbus/Session/device discovery questions | dsoftbus-expert |
| rmw_dsoftbus code implementation/debugging | rmw-expert |
| BUILD.gn/GN/ninja compilation errors | gn-build-expert |
| HDC/device deployment/board operations | hdc-controller |
| Test execution/hardware validation | test-executor |

Always prefer delegating to specialists rather than attempting cross-domain work yourself.

## Useful Commands Quick Reference

```bash
# Build commands
gn gen out/Default                          # Initialize build
ninja -C out/Default                        # Build default target
ninja -C out/Default -t clean               # Clean build
ninja -C out/Default -d keepdeps -v        # Verbose with dependencies

# Inspect targets
gn ls out/Default //src/ros2/rmw_dsoftbus  # List available targets
gn desc out/Default //src/ros2/rmw_dsoftbus:rmw_dsoftbus_cpp  # Describe target

# Test/Deploy
./deploy_step_a2.sh                         # Full deployment pipeline
./build_rcl_test.sh                         # Build RCL test
./build_rmw_direct_test.sh                  # Build RMW direct test

# HDC operations (from WSL)
powershell.exe -NoProfile -Command "hdc list targets"  # List devices
powershell.exe -Command "hdc -t <ID> shell 'command'" # Remote shell
powershell.exe -Command "hdc -t <ID> file send 'local' 'remote'"  # File transfer
```

## Future Development Priorities

Based on gap analysis (Phase 3+):

1. **Phase 3**: Service/Client RPC enhancement (8 hours)
   - File: `src/ros2/rmw_dsoftbus/src/rmw_service.cpp` (currently stub)
   - Goal: Support ros2 service call commands

2. **Phase 4**: 1:N automatic routing (8 hours)
   - Goal: Publisher automatically discovers multiple subscribers

3. **Phase 5**: QoS event monitoring (4 hours)
   - Goal: Deadline/Liveliness timer callbacks

Target: 95% rmw_fastrtps API parity (currently 85%).
