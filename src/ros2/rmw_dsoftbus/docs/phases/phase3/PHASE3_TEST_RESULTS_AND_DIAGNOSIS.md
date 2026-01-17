# Phase 3 Single-Device Graph Discovery Test Results

**Date**: 2026-01-15
**Platform**: rk3588s (aarch64-ohos)
**Test Mode**: No stub, real dsoftbus API only

---

## Executive Summary

The Phase 3 test execution was initiated on two devices but **failed due to missing API functions** in the `libsoftbus_client.z.so` library. The test program attempted to use `GetLocalNetworkId` and `GetLocalDeviceName` functions which do not exist in the deployed library.

**Status**: FAILED (API Mismatch)
**Root Cause**: Incorrect function names for device info retrieval
**Impact**: Test program cannot proceed past library function resolution phase

---

## Test Execution Details

### Devices Tested
- **Device 1**: ec29004133314d38433031a522413c00
- **Device 2**: ec29004133314d38433031a5544f3c00

### Step 1: Device Reboot
- ✅ Both devices successfully rebooted
- ✅ Both devices came back online within 60 seconds
- System info verified: Linux 5.10.110, KaihongOS aarch64

### Step 2: Test Program Verification
- ✅ Device 1: Test program exists at `/data/test/phase3_graph_discovery_test` (23496 bytes, executable)
- ✅ Device 2: Test program exists at `/data/test/phase3_graph_discovery_test` (23496 bytes, executable)
- File timestamps: 2026-01-15 16:31

### Step 3: Test Execution
- ✅ Test program executed on Device 1
- ✅ Test program executed on Device 2
- Duration: ~0 seconds each (immediate failure)

---

## Test Output Analysis

### Device 1 Output
```
╔════════════════════════════════════════════════════════════╗
║   Phase 3 Single-Device Graph Discovery Test              ║
║   Platform: rk3588s (aarch64-ohos)                        ║
║   Mode: No stub, real dsoftbus API only                   ║
╚════════════════════════════════════════════════════════════╝

[DSoftBus] === Loading libsoftbus_client.z.so ===
[DSoftBus] ✅ Library loaded successfully
[DSoftBus] ❌ Failed to get required functions
```

### Device 2 Output
```
╔════════════════════════════════════════════════════════════╗
║   Phase 3 Single-Device Graph Discovery Test              ║
║   Platform: rk3588s (aarch64-ohos)                        ║
║   Mode: No stub, real dsoftbus API only                   ║
╚════════════════════════════════════════════════════════════╝

[DSoftBus] === Loading libsoftbus_client.z.so ===
[DSoftBus] ✅ Library loaded successfully
[DSoftBus] ❌ Failed to get required functions
```

**Observation**: Identical output on both devices. Test successfully loaded the library but failed at dlsym symbol resolution stage.

---

## Root Cause Analysis

### Symbol Investigation Results

#### Library File Properties
- **Path**: `/system/lib64/platformsdk/libsoftbus_client.z.so`
- **Size**: 819 KB
- **Type**: ELF 64-bit LSB shared object (arm64)
- **Permissions**: -rw-r--r-- (read-only)

#### Missing Functions

The test program attempted to resolve these symbols via dlsym():
1. **GetLocalNetworkId** - ❌ NOT FOUND
2. **GetLocalDeviceName** - ❌ NOT FOUND
3. **RegNodeDeviceStateCb** - ✅ FOUND
4. **StartBusCenterServer** - ✅ (likely present)

#### Available Functions

The following functions **DO exist** in the library:
```
RegNodeDeviceStateCb          (symbol confirmed)
RegNodeDeviceStateCbInner     (symbol confirmed)
UnregNodeDeviceStateCb        (symbol confirmed)
UnregNodeDeviceStateCbInner   (symbol confirmed)
CreateSessionServer           (symbol confirmed)
OpenSession                   (symbol confirmed)
ReCreateSessionServerToServer (symbol confirmed)
ServerIpcCreateSessionServer  (symbol confirmed)
```

### Symbol Naming Mismatch

The library uses different API names than what the test expects:

| Expected API | Actual API | Status |
|-------------|-----------|--------|
| `GetLocalNetworkId()` | Unknown or Different Name | Missing |
| `GetLocalDeviceName()` | Unknown or Different Name | Missing |
| `GetLocalNodeDeviceInfo()` | Potentially Available | Not Tested |

Based on OpenHarmony dsoftbus source code analysis, the correct function is likely:
- **`GetLocalNodeDeviceInfo(const char* pkgName, NodeBasicInfo* info)`** - More likely to exist

---

## Diagnostic Findings

### 1. Test Program Issue
**File**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/phase3_graph_discovery_test.c`

**Problem**: The test uses incorrect function names for device info retrieval.

**Code (Line 120-131)**:
```c
GetLocalNetworkId_t get_network_id = (GetLocalNetworkId_t)dlsym(softbus_lib, "GetLocalNetworkId");
GetLocalDeviceName_t get_device_name = (GetLocalDeviceName_t)dlsym(softbus_lib, "GetLocalDeviceName");
...
if (!get_network_id || !get_device_name) {
    printf("[DSoftBus] ❌ Failed to get required functions\n");
    dlclose(softbus_lib);
    return 1;
}
```

**Solution**: Replace with:
```c
typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);
GetLocalNodeDeviceInfo_t get_local_info = (GetLocalNodeDeviceInfo_t)dlsym(softbus_lib, "GetLocalNodeDeviceInfo");

if (!get_local_info) {
    printf("[DSoftBus] ❌ Failed to get required functions\n");
    dlclose(softbus_lib);
    return 1;
}

// Then use:
NodeBasicInfo local_info = {0};
int ret = get_local_info("com.huawei.ros2_rmw_dsoftbus", &local_info);
```

### 2. Library Discrepancy
The deployed `libsoftbus_client.z.so` appears to be from a different version or build configuration than what the test expects. The library has:
- ✅ Session/discovery callbacks working (RegNodeDeviceStateCb found)
- ❌ Device info functions missing (GetLocalNetworkId/Name not found)

### 3. Documentation Gap
The reference code at `/home/jiusi/M-DDS/rmw_dsoftbus/test/get_network_id.cpp` shows the correct API:
- Uses `GetLocalNodeDeviceInfo()` instead
- Still marked as weak symbol, indicating uncertainty

---

## Required Corrections

### Priority 1: Fix Test Program

**File to Update**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/phase3_graph_discovery_test.c`

**Changes**:
1. Replace `GetLocalNetworkId` with `GetLocalNodeDeviceInfo`
2. Replace `GetLocalDeviceName` with `GetLocalNodeDeviceInfo`
3. Update struct usage to NodeBasicInfo

**Alternative Approaches**:
A. Try `LnnGetLocalStrInfo()` - generic local info getter
B. Try `GetDeviceInfo()` - alternative name variant
C. Add fallback to use callbacks-based discovery instead

### Priority 2: Verify Library Version

Check if the library on device matches expected dsoftbus version:
```bash
hdc -t DEVICE_ID shell 'strings /system/lib64/platformsdk/libsoftbus_client.z.so | grep -i version'
```

### Priority 3: Update Documentation

Update Phase 3 test documentation to reflect:
- Correct API names
- Dependencies on specific dsoftbus version
- Fallback strategies

---

## Recommended Next Steps

### Immediate Actions
1. **Fix Test Program**: Update `phase3_graph_discovery_test.c` to use `GetLocalNodeDeviceInfo()`
2. **Recompile**: Run cross_compile_phase3.sh to rebuild test binary
3. **Redeploy**: Send updated test binary to both devices
4. **Retest**: Execute on both devices and capture full output

### Extended Verification
```bash
# On each device, verify available APIs:
strings /system/lib64/platformsdk/libsoftbus_client.z.so | grep -E "^Get|^Lnn" | sort | uniq

# Try running with LD_DEBUG to see dlopen/dlsym calls:
hdc -t DEVICE_ID shell 'LD_DEBUG=symbols /data/test/phase3_graph_discovery_test 2>&1'
```

### Alternative Test Strategy
If `GetLocalNodeDeviceInfo` also fails, implement fallback:
1. Skip local device info retrieval
2. Focus on discovery callback testing (RegNodeDeviceStateCb)
3. Test cross-device discovery when both devices are online

---

## Symbol Resolution Debugging

### What We Know Works
- dlopen() successfully loads `/system/lib64/platformsdk/libsoftbus_client.z.so`
- Library is valid ELF 64-bit ARM64 shared object
- RegNodeDeviceStateCb symbol resolves successfully

### What Failed
- `GetLocalNetworkId` - dlsym() returned NULL
- `GetLocalDeviceName` - dlsym() returned NULL

### dlerror() Output
The test program did not output dlerror() details for individual dlsym failures. Recommend adding:
```c
const char* error = dlerror();
printf("[DSoftBus] dlsym error: %s\n", error ? error : "unknown");
```

---

## Test Environment Status

### Device 1: ec29004133314d38433031a522413c00
- ✅ Online and responsive
- ✅ Test binary deployed
- ✅ System stable (5.10.110 kernel)
- ✅ dsoftbus library available
- ❌ API mismatch detected

### Device 2: ec29004133314d38433031a5544f3c00
- ✅ Online and responsive
- ✅ Test binary deployed
- ✅ System stable (5.10.110 kernel)
- ✅ dsoftbus library available
- ❌ API mismatch detected

### Library Consistency
Both devices have identical library:
- Same path: `/system/lib64/platformsdk/libsoftbus_client.z.so`
- Same size: 819 KB
- Same timestamp: 2026-01-14 13:40
- Indicates synchronized deployment from same build

---

## Data Tables

### Test Execution Summary
| Metric | Value |
|--------|-------|
| Devices Tested | 2 |
| Test Programs Deployed | 2 |
| Successful Library Loads | 2 |
| Failed Symbol Resolutions | 2 |
| Test Duration (Device 1) | 0s |
| Test Duration (Device 2) | 0s |
| Overall Test Result | FAILED |

### Failure Classification
| Category | Count | Severity |
|----------|-------|----------|
| Library Not Found | 0 | - |
| Symbol Resolution Errors | 2 | HIGH |
| Runtime Errors | 0 | - |
| Permission Denials | 0 | - |
| **Total Issues** | **2** | **HIGH** |

---

## Attachments

### Full Test Outputs

**Device 1 Complete Output** (725 bytes):
```
See /tmp/phase3_results/device1_output.txt
```

**Device 2 Complete Output** (725 bytes):
```
See /tmp/phase3_results/device2_output.txt
```

### Symbol Analysis Files
- `/tmp/symbol_diagnosis/device1_lib_check.txt` - Library presence check
- `/tmp/symbol_diagnosis/device1_symbols.txt` - Available symbols
- `/tmp/symbol_diagnosis/device1_file_type.txt` - ELF file type info

---

## Conclusion

The Phase 3 Single-Device Graph Discovery test **failed due to API mismatch** between the test program and the deployed dsoftbus library. The issue is **fixable** with the following changes:

1. Update function names in test program (GetLocalNetworkId → GetLocalNodeDeviceInfo)
2. Recompile and redeploy test binary
3. Re-execute tests

The underlying dsoftbus library appears functional and has necessary symbols for callback registration and session management. Once the API mismatch is corrected, the test should proceed to the actual discovery and session creation phases.

**Estimated Fix Time**: 15-20 minutes
**Risk Level**: LOW (software-only fix)
**Next Phase**: Re-test with corrected API calls

---

**Report Generated**: 2026-01-15 16:40 UTC
**Test Duration**: ~5 minutes total
**Status**: Ready for remediation
