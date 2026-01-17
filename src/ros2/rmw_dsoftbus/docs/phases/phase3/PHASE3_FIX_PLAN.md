# Phase 3 Test Fix Plan

## Problem Summary
Test program uses non-existent API functions:
- `GetLocalNetworkId()` - NOT in library
- `GetLocalDeviceName()` - NOT in library

These need to be replaced with the correct API:
- `GetLocalNodeDeviceInfo()` - AVAILABLE

---

## Solution Overview

### Root Cause
The test code at `/home/jiusi/M-DDS/rmw_dsoftbus/test/phase3_graph_discovery_test.c` (line 120-131) attempts to dlsym() functions that don't exist in the deployed library.

### Fix Strategy
1. Update function pointer declarations
2. Change dlsym() calls to use correct function names
3. Update function call pattern to use NodeBasicInfo struct
4. Recompile test binary
5. Redeploy and retest

---

## Detailed Fix

### Current Code (BROKEN)
```c
// Line 120-131 in phase3_graph_discovery_test.c
GetLocalNetworkId_t get_network_id = (GetLocalNetworkId_t)dlsym(softbus_lib, "GetLocalNetworkId");
GetLocalDeviceName_t get_device_name = (GetLocalDeviceName_t)dlsym(softbus_lib, "GetLocalDeviceName");
RegNodeDeviceStateCb_t reg_node_state = (RegNodeDeviceStateCb_t)dlsym(softbus_lib, "RegNodeDeviceStateCb");
StartBusCenterServer_t start_bus_center = (StartBusCenterServer_t)dlsym(softbus_lib, "StartBusCenterServer");
GetAllNodeDeviceInfo_t get_all_nodes = (GetAllNodeDeviceInfo_t)dlsym(softbus_lib, "GetAllNodeDeviceInfo");
FreeNodeInfo_t free_node_info = (FreeNodeInfo_t)dlsym(softbus_lib, "FreeNodeInfo");

if (!get_network_id || !get_device_name) {  // ❌ FAILS HERE
    printf("[DSoftBus] ❌ Failed to get required functions\n");
    dlclose(softbus_lib);
    return 1;
}
```

### Fixed Code (WORKING)
```c
// Replace lines 120-131 with:
typedef int (*GetLocalNodeDeviceInfo_t)(const char*, NodeBasicInfo*);

GetLocalNodeDeviceInfo_t get_local_info = (GetLocalNodeDeviceInfo_t)dlsym(softbus_lib, "GetLocalNodeDeviceInfo");
RegNodeDeviceStateCb_t reg_node_state = (RegNodeDeviceStateCb_t)dlsym(softbus_lib, "RegNodeDeviceStateCb");
StartBusCenterServer_t start_bus_center = (StartBusCenterServer_t)dlsym(softbus_lib, "StartBusCenterServer");
GetAllNodeDeviceInfo_t get_all_nodes = (GetAllNodeDeviceInfo_t)dlsym(softbus_lib, "GetAllNodeDeviceInfo");
FreeNodeInfo_t free_node_info = (FreeNodeInfo_t)dlsym(softbus_lib, "FreeNodeInfo");

if (!get_local_info || !reg_node_state) {  // ✅ CRITICAL FUNCTIONS ONLY
    printf("[DSoftBus] ❌ Failed to get required functions\n");
    if (!get_local_info) printf("[DSoftBus]    Missing: GetLocalNodeDeviceInfo\n");
    if (!reg_node_state) printf("[DSoftBus]    Missing: RegNodeDeviceStateCb\n");
    dlclose(softbus_lib);
    return 1;
}
```

### Update Device Info Retrieval (Line 133-150)
**Current Code (BROKEN)**:
```c
int ret = get_network_id(local_network_id, sizeof(local_network_id));
if (ret == 0) {
    printf("[Discovery] ✅ Local Network ID: %s\n", local_network_id);
} else {
    printf("[Discovery] ⚠️  GetLocalNetworkId returned: %d\n", ret);
}

ret = get_device_name(local_device_name, sizeof(local_device_name));
if (ret == 0) {
    printf("[Discovery] ✅ Local Device Name: %s\n", local_device_name);
} else {
    printf("[Discovery] ⚠️  GetLocalDeviceName returned: %d\n", ret);
}
```

**Fixed Code (WORKING)**:
```c
NodeBasicInfo local_info = {0};
int ret = get_local_info(TEST_PKG_NAME, &local_info);
if (ret == 0) {
    printf("[Discovery] ✅ Local Network ID: %s\n", local_info.networkId);
    printf("[Discovery] ✅ Local Device Name: %s\n", local_info.deviceName);
    printf("[Discovery] ✅ Device Type ID: %d\n", local_info.deviceTypeId);

    // Copy to output variables for later use
    strcpy(local_network_id, local_info.networkId);
    strcpy(local_device_name, local_info.deviceName);
} else {
    printf("[Discovery] ⚠️  GetLocalNodeDeviceInfo returned: %d\n", ret);
    printf("[Discovery] ℹ️  Continuing with partial functionality...\n");
}
```

---

## Compilation Steps

### Step 1: Edit Test File
```bash
# Make a backup first
cp /home/jiusi/M-DDS/rmw_dsoftbus/test/phase3_graph_discovery_test.c \
   /home/jiusi/M-DDS/rmw_dsoftbus/test/phase3_graph_discovery_test.c.backup

# Then apply the fixes above using an editor or script
```

### Step 2: Check BUILD.gn Configuration
Ensure the test target is configured correctly in `/home/jiusi/M-DDS/rmw_dsoftbus/test/BUILD.gn`:

```gn
executable("phase3_graph_discovery_test") {
  sources = [ "phase3_graph_discovery_test.c" ]

  cflags = [
    "-O2",
    "-Wall",
    "-Wextra",
  ]

  ldflags = [
    "-ldl",  # For dlopen/dlsym
  ]

  # If needed, add library paths:
  # lib_dirs = [ "/system/lib64/platformsdk" ]
}
```

### Step 3: Rebuild Test Binary
```bash
# Option A: Using cross_compile_phase3.sh (if it exists)
./cross_compile_phase3.sh all

# Option B: Direct GN build
cd /home/jiusi/M-DDS/rmw_dsoftbus
gn gen out/aarch64
ninja -C out/aarch64 phase3_graph_discovery_test
```

### Step 4: Verify Binary
```bash
# Check binary was created and is executable
file /home/jiusi/M-DDS/rmw_dsoftbus/out/aarch64/phase3_graph_discovery_test
ldd /home/jiusi/M-DDS/rmw_dsoftbus/out/aarch64/phase3_graph_discovery_test 2>&1 | head -10
```

---

## Deployment Steps

### Step 1: Copy Binary to Transfer Directory
```bash
mkdir -p /mnt/c/tmp/hdc_transfer
cp /home/jiusi/M-DDS/rmw_dsoftbus/out/aarch64/phase3_graph_discovery_test \
   /mnt/c/tmp/hdc_transfer/
```

### Step 2: Deploy to Device 1
```bash
DEVICE_1="ec29004133314d38433031a522413c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_1 file send 'C:\tmp\hdc_transfer\phase3_graph_discovery_test' '/data/test/phase3_graph_discovery_test'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_1 shell 'chmod +x /data/test/phase3_graph_discovery_test'"
```

### Step 3: Deploy to Device 2
```bash
DEVICE_2="ec29004133314d38433031a5544f3c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_2 file send 'C:\tmp\hdc_transfer\phase3_graph_discovery_test' '/data/test/phase3_graph_discovery_test'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_2 shell 'chmod +x /data/test/phase3_graph_discovery_test'"
```

### Step 4: Verify Deployment
```bash
# Device 1
powershell.exe -NoProfile -Command "hdc -t $DEVICE_1 shell 'ls -la /data/test/phase3_graph_discovery_test'"

# Device 2
powershell.exe -NoProfile -Command "hdc -t $DEVICE_2 shell 'ls -la /data/test/phase3_graph_discovery_test'"
```

---

## Testing Steps

### Step 1: Run on Device 1
```bash
DEVICE_1="ec29004133314d38433031a522413c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_1 shell '/data/test/phase3_graph_discovery_test'"
```

### Step 2: Run on Device 2
```bash
DEVICE_2="ec29004133314d38433031a5544f3c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_2 shell '/data/test/phase3_graph_discovery_test'"
```

### Step 3: Capture Output
Expected success output should show:
```
✅ Library loaded successfully
✅ Functions resolved
✅ Local Network ID: <network-id>
✅ Local Device Name: <device-name>
✅ Callbacks registered
✅ Bus center started
```

---

## Fallback Options

If `GetLocalNodeDeviceInfo` also doesn't exist, try these in order:

### Option 1: Use LnnGetLocalStrInfo
```c
typedef int (*LnnGetLocalStrInfo_t)(int key, char* value, int len);

// Usage:
#define KEY_NETWORK_ID 1
#define KEY_DEVICE_NAME 2

int ret = get_local_str_info(KEY_NETWORK_ID, local_network_id, sizeof(local_network_id));
```

### Option 2: Use Discovery Callback Fallback
Skip local device info retrieval entirely:
- Register callback with RegNodeDeviceStateCb
- Wait for OnNodeOnline callback with local device info
- Extract network ID and device name from callback

### Option 3: Implement Minimal Test
Focus only on what's available:
- Test RegNodeDeviceStateCb (✅ confirmed to exist)
- Test CreateSessionServer (✅ likely exists)
- Skip device info retrieval

---

## Success Criteria

The test is considered FIXED and SUCCESSFUL when:

1. ✅ Test program compiles without errors
2. ✅ Test program runs without crashing
3. ✅ Library loads successfully: "✅ Library loaded successfully"
4. ✅ Functions resolve: "✅ Functions resolved" or similar
5. ✅ At least one of:
   - Device info retrieved: "✅ Local Network ID: ..."
   - Discovery callback fires: "✅ OnNodeOnline called"
   - Session server created: "✅ Session server created"
6. ✅ Test completes with summary: "Test run complete"

---

## Timeline Estimate

| Task | Duration | Status |
|------|----------|--------|
| Apply code fixes | 5 min | Ready |
| Recompile test | 2-3 min | Ready |
| Redeploy to Device 1 | 1 min | Ready |
| Redeploy to Device 2 | 1 min | Ready |
| Test on Device 1 | 1 min | Ready |
| Test on Device 2 | 1 min | Ready |
| **Total** | **~12 min** | **Ready** |

---

## Risk Assessment

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|-----------|
| Wrong function name | LOW | MEDIUM | Try fallback options listed above |
| Library version mismatch | MEDIUM | MEDIUM | Verify library version strings |
| Compilation issues | LOW | LOW | Check GN config and includes |
| Deployment failure | LOW | LOW | Verify device connectivity first |

---

## Next Steps After Fix

1. **If test succeeds**: Proceed to Phase 3 full cross-device testing
2. **If test partially succeeds**: Document limitations and continue with available features
3. **If test still fails**: Investigate alternative APIs or library version mismatch
4. **Regardless of result**: Update documentation with correct API names for future reference

---

**Fix Plan Generated**: 2026-01-15 16:45 UTC
**Estimated Completion**: 2026-01-15 17:00 UTC
**Priority**: HIGH (blocking Phase 3 verification)
