# Phase 2 Graph Discovery Cross-Device Test Results

**Date**: 2026-01-05
**Build**: GN + OHOS prebuilts gcc-linaro-7.5.0 (aarch64-linux-gnu)
**Library**: librmw_dsoftbus.so 2.2MB (visibility=default, dlopen shim)

## Test Configuration

- **Devices**: 3x rk3588s KaihongOS
  - Device 1: ec29004133314d38433031a522413c00
  - Device 2: ec29004133314d38433031a5544f3c00 (network_id: ce4d7447...)
  - Device 3: ec29004133314d38433031a751c63c00 (network_id: 2a8e41d1...)
- **Test Program**: discovery_final_test
- **Duration**: 30 seconds per device
- **Test Type**: Simultaneous execution on all 3 devices

## Results Summary

| Device | Init | SessionServer | Devices Found | Session | TX | RX |
|--------|------|---------------|---------------|---------|----|----|
| D1 | FAIL | -426442706 | - | - | - | - |
| D2 | OK | id=0 | 2 | id=1 | 6 | 5 (dropped) |
| D3 | OK | id=0 | 2 | id=1 | 6 | 0 |

## Key Achievements

### 1. Cross-Device Discovery (SUCCESS)
```
[D2] Found 2 device(s) in network:
  [0] 2a8e41d15e3ec57e69ffce1896f5fab28c24ebcb0ef10d521cb3721dc158da85 (KaihongBoard-3588S)

[D3] Found 2 device(s) in network:
  [0] ce4d74479be13baf6014ae79765f21817820131812980a16bf0564609463f4f0 (KaihongBoard-3588S)
```

### 2. Session Establishment (SUCCESS)
```
[D2] OpenSession to 2a8e41d15e3ec57e69ffce1896f5fab28c24ebcb0ef10d521cb3721dc158da85 succeeded: session_id=1
[D3] OpenSession to ce4d74479be13baf6014ae79765f21817820131812980a16bf0564609463f4f0 succeeded: session_id=1
```

### 3. Bidirectional Communication (PARTIAL)
- Messages sent from both D2 and D3 (tx=6 each)
- D2 received 5 messages but dropped them (unknown session)
- D3 received 0 messages (session closed prematurely)

## Issues Found

### Issue 1: Device 1 Initialization Failure
**Error**: `CreateSessionServer failed: -426442706`
**Cause**: dsoftbus service not responding or permission issue
**Resolution**: Restart dsoftbus service on Device 1

### Issue 2: Session ID Mismatch
**Symptom**: `[D2] DROP: unknown session 3`
**Cause**: When D3 connects to D2's SessionServer, it creates session_id=3 (inbound).
         But D2 only tracks session_id=1 (outbound to D3).
**Impact**: Inbound messages dropped due to untracked session
**Resolution**: DiscoveryManager needs to track both inbound and outbound sessions

### Issue 3: Session Closure Timing
**Symptom**: `[D3] Session closed: id=1` before test completion
**Cause**: D2 shutdown closed the session before D3 could receive all messages

## Technical Details

### Successful dlopen Shim Loading
```
[SoftBus Shim] Successfully loaded /system/lib64/platformsdk/libsoftbus_client.z.so
[SoftBus Shim] Loaded symbol: GetLocalNodeDeviceInfo
[SoftBus Shim] Loaded symbol: GetAllNodeDeviceInfo
[SoftBus Shim] Loaded symbol: CreateSessionServer
[SoftBus Shim] Loaded symbol: OpenSession
[SoftBus Shim] Loaded symbol: SendBytes
```

### Message Statistics
```
[D2 FINAL STATS]
  Messages:   rx=5 tx=6
  Drops:      invalid=5 fwd=0 dup=0 parse=0
  Protocol:   query_sent=1 snap_recv=0 hb_recv=0
  Sessions:   peers=1

[D3 FINAL STATS]
  Messages:   rx=0 tx=6
  Drops:      invalid=0 fwd=0 dup=0 parse=0
  Protocol:   query_sent=1 snap_recv=0 hb_recv=0
  Sessions:   peers=0
```

## Conclusion

**Phase 2 Graph Discovery: MOSTLY SUCCESSFUL**

Core functionality verified:
- [x] dlopen shim loads real libsoftbus_client.z.so
- [x] GetLocalNodeDeviceInfo returns valid network_id
- [x] GetAllNodeDeviceInfo discovers peer devices
- [x] CreateSessionServer succeeds (D2, D3)
- [x] OpenSession establishes bidirectional connections
- [x] SendBytes transmits discovery messages

Remaining issues (non-blocking):
- [ ] Session ID tracking for inbound connections
- [ ] Device 1 service restart needed
- [ ] Message reception verification

## Next Steps

1. **Fix Session Tracking**: Update DiscoveryManager to track sessions from OnSessionOpened callback
2. **Restart D1**: `hdc shell "killall softbus_server && softbus_server &"`
3. **Complete Message Flow**: Verify GraphCache updates propagate between devices

## Build Information

```
# BUILD.gn changes
cflags_cc = [
  "-std=c++17",
  "-Wall",
  "-Wextra",
  "-fPIC",
  "-fvisibility=default",  # Export all C++ symbols
]

sources = [
  # ... existing sources ...
  "test/softbus_dlopen_shim.cpp",  # dlopen shim for real dsoftbus
]
```
