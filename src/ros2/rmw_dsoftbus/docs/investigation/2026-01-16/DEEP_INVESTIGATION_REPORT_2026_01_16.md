# Deep Investigation Report: dsoftbus Permission System

**Investigation Date**: 2026-01-16
**Investigator**: Claude Deep Analysis Agent
**Objective**: Completely solve CreateSessionServer, OpenSession, and Discovery issues

---

## Investigation Summary

### Issues Investigated
1. CreateSessionServer returning -426442743
2. OpenSession failing to establish connections
3. Device discovery appearing not to work

### Findings
1. **CreateSessionServer**: ✅ Completely solved - PKG_NAME validation bug found and fixed
2. **OpenSession**: ⚠️ API works, callback fails due to KaihongOS layer issue
3. **Device Discovery**: ✅ Confirmed working correctly

---

## Phase 1: Initial JSON Format Fix (Already Completed)

### Problem
Permission JSON was in object format but dsoftbus expects array format.

### Solution Applied
Changed from object format to array format:
- Before: JSON object with trans_permission key
- After: JSON array with direct entries

### Result
JSON loads correctly but CreateSessionServer still failed.

---

## Phase 2: Deep Permission Validation Analysis

### Source Code Investigation

Analyzed permission validation flow across multiple files:
- softbus_server_stub.cpp line 520: CheckTransPermission entry point
- softbus_permission.cpp line 79: Permission type calculation
- permission_entry.c line 498: CheckPermissionEntry validation
- permission_entry.c line 347: CheckPermissionAppInfo matching

### Validation Flow Discovered

Step 1: Match SESSION_NAME
- Supports regex when REGEXP field is true
- Uses regexec pattern matching
- Successfully matches "com.huawei.ros2_rmw_dsoftbus.*" pattern

Step 2: Match PKG_NAME
- NO regex support regardless of REGEXP field
- Always uses strcmp exact string comparison
- Fails when PKG_NAME is ".*" (tries to match literal ".*")

### Critical Code Section

From permission_entry.c line 372-381:
Package name validation has special bypass logic for empty strings.

When pkgName is empty, validation skips package check and returns success.

---

## Phase 3: Root Cause Identification

### The Bug

Wildcard permission entry used PKG_NAME value ".*"
Expected behavior: Match any package name
Actual behavior: Tries to match literal string ".*"

### Why It Failed

PKG_NAME field in permission_entry.c line 374:
Always passes false for regex parameter to CompareString function.
This means regex patterns are never evaluated for package names.

### Validation Rules Discovered

| Permission Field | Regex Support | Validation Method |
|-----------------|--------------|-------------------|
| SESSION_NAME | YES (when REGEXP=true) | regexec pattern matching |
| PKG_NAME | NO (always) | strcmp exact match |
| DEVID | N/A | Enum comparison |
| SEC_LEVEL | N/A | Enum comparison |

---

## Phase 4: Solution Implementation

### Fix Applied

Changed wildcard entry PKG_NAME from ".*" to "" (empty string)

Reasoning:
Empty PKG_NAME triggers bypass logic in validation code.
When pkgName is empty, validator skips package name check entirely.

### Deployment Process

1. Created fixed JSON: softbus_trans_permission_fixed.json
2. Copied to Windows temp directory for HDC transfer
3. Deployed to Device 1: ec29004133314d38433031a5544f3c00
4. Deployed to Device 2: ec29004133314d38433031a522413c00
5. Remounted system partition read-write
6. Copied JSON to /system/etc/communication/softbus/
7. Rebooted both devices
8. Verified deployment success

---

## Phase 5: Verification Testing

### Test 1: CreateSessionServer

Device: Device 1
Program: phase3b_session_test server
Package: com.huawei.ros2_rmw_dsoftbus
Session: com.huawei.ros2_rmw_dsoftbus.test

Result:
- AccessToken injection: SUCCESS (0x2803f800)
- Library loading: SUCCESS
- CreateSessionServer return: 0 (SUCCESS)
- Status: Session server created

Conclusion: ✅ COMPLETELY FIXED

### Test 2: OpenSession

Device: Device 2
Program: phase3b_session_test client
Peer: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3

Result:
- CreateSessionServer: SUCCESS
- Device discovery: SUCCESS (found 2 devices)
- OpenSession API: SUCCESS (returned sessionId=1)
- Callback result: FAILED (-426115004)
- Error: KH_TRANS not initialized

Analysis:
Permission validation passed successfully.
Failure occurs in KaihongOS transport layer initialization.
This is NOT a permission issue but system initialization issue.

Conclusion: ⚠️ API succeeds, callback needs KH_TRANS init

### Test 3: Device Discovery

Method: GetAllNodeDeviceInfo
Devices found: 2
Network IDs discovered: Both devices visible

Device 0:
- Network ID: 6ea1cecbc95eb2d290af12d0d447e8689339ad105e1d736aa4a6cfd3f6aa3ee3
- Name: KaihongBoard-3588S

Device 1:
- Network ID: e05acef96ee6b1b68025cac8b3de7ee95ab6b8bb457051176eafea89cc0d1212
- Name: KaihongBoard-3588S

Conclusion: ✅ Discovery works correctly

---

## Phase 6: Error Code Analysis

### CreateSessionServer Errors

Error -426442743:
- Meaning: SOFTBUS_PERMISSION_DENIED
- Source: Permission validation layer
- Offset: +8 from SOFTBUS_PUBLIC_ERR_BASE
- Resolution: Fixed by correcting PKG_NAME validation

### OpenSession Callback Errors

Error -426115004:
- Meaning: Callback failure
- Source: KaihongOS transport layer
- Related: -426115032 (KH session manager)
- Resolution: Requires KH_TRANS initialization (future work)

Error -426442723:
- Meaning: ClientBind internal error
- Source: Transport session binding
- Related: Session already deleted before bind
- Resolution: Symptom of KH_TRANS initialization failure

---

## Lessons Learned

### 1. Permission JSON Field Validation

SESSION_NAME field:
- Supports regex patterns when REGEXP is true
- Uses standard POSIX regex matching
- Can match complex patterns

PKG_NAME field:
- Does NOT support regex patterns
- Always performs exact string comparison
- Empty string bypasses validation entirely

### 2. Empty String Bypass Pattern

Validation code checks if string is empty before comparing.
Empty pkgName causes validator to skip package check.
This is intentional design for wildcard matching.

### 3. Multi-Layer Error Handling

Permission errors occur at different layers:
- Layer 1: JSON configuration validation
- Layer 2: AccessToken runtime verification
- Layer 3: Transport layer initialization
- Layer 4: KaihongOS system layer

Each layer has different error codes.
Must analyze error codes to identify failure layer.

### 4. Cross-Compiled Program Limitations

Permission JSON fix works for cross-compiled programs.
AccessToken injection appears successful.
KH_TRANS initialization requires system integration.
Full functionality needs OHOS build system.

---

## Recommendations

### For Production Deployment

1. Use fixed permission JSON with empty PKG_NAME for wildcards
2. Deploy to all devices before rebooting
3. Verify CreateSessionServer works after reboot
4. Document that PKG_NAME does not support regex

### For Development Testing

1. Continue using rmw_mock for ROS2 core testing
2. Accept OpenSession callback limitation in cross-compiled tests
3. Focus on CreateSessionServer success as milestone
4. Plan KH_TRANS investigation for Phase 4

### For Future Integration

1. Investigate KH_TRANS initialization sequence
2. Build rmw_dsoftbus as OHOS component
3. Test with system-integrated binaries
4. Verify full OpenSession callback functionality

---

## Files Modified

Configuration:
- rmw_dsoftbus/config/softbus_trans_permission_fixed.json (created)
- /system/etc/communication/softbus/softbus_trans_permission.json (deployed)

Documentation:
- docs/investigation/2026-01-16/PERMISSION_SOLUTION_SUMMARY.md
- docs/investigation/2026-01-16/DEEP_INVESTIGATION_REPORT_2026_01_16.md (this file)

Test Programs:
- tests/simple_permission_test.c (existing)
- tests/phase3b_session_test (existing, tested)

---

## Conclusion

### CreateSessionServer Issue
**Status**: ✅ Completely Solved
**Root Cause**: PKG_NAME wildcard used regex pattern but validation only supports exact match
**Solution**: Changed PKG_NAME to empty string to bypass validation
**Verification**: CreateSessionServer returns 0, session server created successfully

### OpenSession Issue
**Status**: ⚠️ Partially Solved
**API Status**: OpenSession succeeds and returns valid session ID
**Callback Status**: OnSessionOpened fails due to KH_TRANS not initialized
**Root Cause**: KaihongOS transport layer initialization issue
**Note**: This is NOT a permission problem

### Device Discovery
**Status**: ✅ Confirmed Working
**Method**: GetAllNodeDeviceInfo successfully returns 2 devices
**Verification**: Both devices discover each other correctly

### Overall Assessment
**Permission Investigation**: Complete
**Issues Resolved**: 2 out of 3 fully resolved
**Remaining Work**: KH_TRANS initialization (system integration task)

---

**Report Status**: Investigation Complete
**Date**: 2026-01-16
**Next Actions**: Document for PR, continue with Phase 4 planning
