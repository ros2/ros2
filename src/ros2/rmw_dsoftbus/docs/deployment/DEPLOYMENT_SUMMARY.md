# Graph Discovery Test Deployment Summary

## Compilation Details

**Date**: 2026-01-16 09:17 UTC
**Source File**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/graph_discovery_test.c`
**Output Binary**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/graph_discovery_test`
**Binary Size**: 194 KB (197,688 bytes)
**Architecture**: ARM aarch64 (ELF 64-bit LSB shared object)
**Toolchain**: `aarch64-linux-gnu-gcc` version 9.4.0

### Compilation Command

```bash
cd /home/jiusi/M-DDS/rmw_dsoftbus/test

aarch64-linux-gnu-gcc \
  -o graph_discovery_test \
  graph_discovery_test.c \
  -I/home/jiusi/M-DDS/base/security/access_token/interfaces/innerkits/nativetoken/include \
  -I/home/jiusi/M-DDS/base/security/access_token/interfaces/innerkits/token_setproc/include \
  /home/jiusi/M-DDS/rmw_dsoftbus/ohos_static_libs/libnativetoken.a \
  /home/jiusi/M-DDS/rmw_dsoftbus/ohos_static_libs/libtoken_setproc.a \
  /home/jiusi/M-DDS/rmw_dsoftbus/ohos_static_libs/libcjson_static.a \
  /home/jiusi/M-DDS/rmw_dsoftbus/ohos_static_libs/libsec_static.a \
  -ldl \
  -lpthread \
  -static-libgcc \
  -Wl,-rpath,/system/lib64
```

### Static Libraries Linked

1. **libnativetoken.a** - OpenHarmony native token permission system
2. **libtoken_setproc.a** - Token process setting utilities
3. **libcjson_static.a** - cJSON parser for JSON operations
4. **libsec_static.a** - Secure string functions (strcpy_s, vsnprintf_s, etc.)

### Dynamic Dependencies

- **libdl.so** - Dynamic loading for dsoftbus library
- **libpthread.so** - Threading support
- **libsoftbus_client.z.so** - Runtime loaded via dlopen from `/system/lib64/platformsdk/`

## Deployment Details

### Device Information

| Device | Network ID | Connection | Status |
|--------|-----------|------------|--------|
| Device 1 | `ec29004133314d38433031a522413c00` | USB | Connected |
| Device 2 | `ec29004133314d38433031a5544f3c00` | USB | Connected |

### Deployment Locations

**Target Path**: `/data/local/tmp/graph_discovery_test`

**Device 1 Deployment**:
- Transfer time: 23 ms
- Transfer rate: 8595.13 kB/s
- Permissions: `-rwxr-xr-x` (executable)
- Owner: root:root

**Device 2 Deployment**:
- Transfer time: 14 ms
- Transfer rate: 14120.57 kB/s
- Permissions: `-rwxr-xr-x` (executable)
- Owner: root:root

### Deployment Commands

```bash
# Copy to Windows transfer directory
mkdir -p /mnt/c/tmp/hdc_transfer
cp /home/jiusi/M-DDS/rmw_dsoftbus/test/graph_discovery_test /mnt/c/tmp/hdc_transfer/

# Deploy to Device 1
DEVICE1="ec29004133314d38433031a522413c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 file send 'C:\tmp\hdc_transfer\graph_discovery_test' '/data/local/tmp/graph_discovery_test'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell chmod +x /data/local/tmp/graph_discovery_test"

# Deploy to Device 2
DEVICE2="ec29004133314d38433031a5544f3c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 file send 'C:\tmp\hdc_transfer\graph_discovery_test' '/data/local/tmp/graph_discovery_test'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell chmod +x /data/local/tmp/graph_discovery_test"
```

## Test Execution Guide

### Server Mode (Device 1)

```bash
DEVICE1="ec29004133314d38433031a522413c00"
powershell.exe -NoProfile -Command "hdc -t $DEVICE1 shell cd /data/local/tmp '&&' ./graph_discovery_test server"
```

### Client Mode (Device 2)

First, get the network ID of Device 1 from the server output, then:

```bash
DEVICE2="ec29004133314d38433031a5544f3c00"
PEER_NETWORK_ID="<network_id_from_device1>"
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell cd /data/local/tmp '&&' ./graph_discovery_test client $PEER_NETWORK_ID"
```

### Auto-Discovery Mode

The test can automatically discover and select a peer:

```bash
# On Device 2 (will auto-discover Device 1)
powershell.exe -NoProfile -Command "hdc -t $DEVICE2 shell cd /data/local/tmp '&&' ./graph_discovery_test client"
```

## Test Features

### Dynamic Library Loading

The test uses `dlopen()` to load dsoftbus library at runtime:
- **Library Path**: `/system/lib64/platformsdk/libsoftbus_client.z.so`
- **Flags**: `RTLD_NOW | RTLD_GLOBAL`
- **Functions Loaded**:
  - `CreateSessionServer`
  - `RemoveSessionServer`
  - `OpenSession`
  - `CloseSession`
  - `SendBytes`
  - `GetAllNodeDeviceInfo`
  - `GetLocalNodeDeviceInfo`
  - `FreeNodeInfo`

### Permission Management

The test automatically sets required OHOS permissions:
- `ohos.permission.DISTRIBUTED_DATASYNC`
- `ohos.permission.DISTRIBUTED_SOFTBUS_CENTER`

**APL Level**: `system_basic`
**Package Name**: `rmw_dsoftbus`
**Session Name**: `rmw_dsoftbus.graph`

### Session Configuration

- **Data Type**: `TYPE_BYTES`
- **Link Type**: `LINK_TYPE_WIFI_WLAN_2G`
- **Stream Type**: `RAW_STREAM`
- **Group**: `defaultGroup`

## Verification Steps

1. **Check binary exists and is executable**:
   ```bash
   powershell.exe -NoProfile -Command "hdc -t <DEVICE_ID> shell ls -lh /data/local/tmp/graph_discovery_test"
   ```

2. **Verify library can be loaded**:
   The test will print:
   ```
   [INFO] Loading dsoftbus library from: /system/lib64/platformsdk/libsoftbus_client.z.so
   [INFO] dsoftbus library loaded successfully
   ```

3. **Check device discovery**:
   ```
   [INFO] Getting discovered devices...
   [INFO] Found N device(s):
     [0] DeviceName (NetworkID: ...)
   ```

4. **Monitor session establishment**:
   ```
   [CB] OnSessionOpened: sessionId=X, result=0
   ```

5. **Verify data transfer**:
   ```
   [CB] OnBytesReceived: sessionId=X, len=Y, data=...
   ```

## Expected Output

### Server Mode Output

```
==============================================
Graph Discovery & Session Test
PKG_NAME: rmw_dsoftbus
SESSION_NAME: rmw_dsoftbus.graph
==============================================

[INFO] Setting permissions...
[INFO] GetAccessTokenId: tokenId=0x...
[INFO] SetSelfTokenID: ret=0
[INFO] Loading dsoftbus library from: /system/lib64/platformsdk/libsoftbus_client.z.so
[INFO] dsoftbus library loaded successfully
  CreateSessionServer: 0x...
  OpenSession: 0x...
  GetAllNodeDeviceInfo: 0x...
[INFO] Local device: DeviceName (NetworkID: ...)
[INFO] Getting discovered devices...
[INFO] Found 1 device(s):
  [0] OtherDevice (NetworkID: ...)

========== SERVER MODE ==========
PKG_NAME: rmw_dsoftbus
SESSION_NAME: rmw_dsoftbus.graph
[SERVER] RemoveSessionServer (cleanup): ret=...
[SERVER] CreateSessionServer: ret=0
[SERVER] Waiting for connections (60 seconds)...
[CB] OnSessionOpened: sessionId=1, result=0
[CB] OnBytesReceived: sessionId=1, len=35, data=Hello from com.huawei.rmw client!
[SERVER] Data received successfully!
[SERVER] Server stopped.

[DONE] Exit code: 0
```

### Client Mode Output

```
==============================================
Graph Discovery & Session Test
PKG_NAME: rmw_dsoftbus
SESSION_NAME: rmw_dsoftbus.graph
==============================================

[INFO] Setting permissions...
[INFO] GetAccessTokenId: tokenId=0x...
[INFO] SetSelfTokenID: ret=0
[INFO] Loading dsoftbus library from: /system/lib64/platformsdk/libsoftbus_client.z.so
[INFO] dsoftbus library loaded successfully
  CreateSessionServer: 0x...
  OpenSession: 0x...
  GetAllNodeDeviceInfo: 0x...
[INFO] Local device: DeviceName (NetworkID: ...)
[INFO] Getting discovered devices...
[INFO] Found 1 device(s):
  [0] ServerDevice (NetworkID: ...)
[INFO] Auto-selected peer: ServerDevice (...)

========== CLIENT MODE ==========
PKG_NAME: rmw_dsoftbus
SESSION_NAME: rmw_dsoftbus.graph
Peer NetworkID: ...
[CLIENT] RemoveSessionServer (cleanup): ret=...
[CLIENT] CreateSessionServer: ret=0
[CLIENT] Opening session to peer...
[CLIENT] OpenSession: sessionId=2
[CLIENT] Waiting for session to open...
[CB] OnSessionOpened: sessionId=2, result=0
[CLIENT] Sending: Hello from com.huawei.rmw client!
[CLIENT] SendBytes: ret=0
[CLIENT] Client stopped.

[DONE] Exit code: 0
```

## Troubleshooting

### Library Loading Failure

**Error**: `dlopen failed: cannot open shared object file`

**Solution**:
1. Check library exists: `ls -la /system/lib64/platformsdk/libsoftbus_client.z.so`
2. Verify LD_LIBRARY_PATH includes `/system/lib64`
3. Check SELinux permissions (if enabled)

### Permission Errors

**Error**: CreateSessionServer returns error code

**Solution**:
1. Verify permission configuration file exists:
   ```bash
   cat /system/etc/communication/softbus/softbus_trans_permission.json
   ```
2. Check that `rmw_dsoftbus` is listed with proper permissions
3. Restart the device if permission file was just updated

### Session Opening Failure

**Error**: OpenSession returns negative session ID

**Solution**:
1. Verify peer network ID is correct
2. Check that both devices are on same network
3. Ensure dsoftbus daemon is running on both devices
4. Check hilog for detailed error messages:
   ```bash
   hilog | grep -i softbus
   ```

### Device Discovery Issues

**Error**: `Found 0 device(s)`

**Solution**:
1. Ensure devices are paired/trusted
2. Check wifi/network connectivity
3. Verify distributed hardware service is running
4. Restart dsoftbus service:
   ```bash
   kill -9 $(pidof softbus_server)
   # Service will auto-restart
   ```

## Related Documentation

- **Source Code**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/graph_discovery_test.c`
- **Build Guide**: `/home/jiusi/M-DDS/docs/OHOS_GN_BUILD_GUIDE.md`
- **Permission Guide**: `/home/jiusi/M-DDS/docs/02_dsoftbus诊断体系/权限配置教程.md`
- **Phase 2 Test Results**: `/home/jiusi/M-DDS/rmw_dsoftbus/test/PHASE2_CROSS_DEVICE_TEST_RESULTS.md`

## Next Steps

1. **Run Cross-Device Test**: Execute server on Device 1 and client on Device 2
2. **Monitor Logs**: Use `hilog` to monitor dsoftbus operations
3. **Validate Discovery**: Verify both devices can discover each other
4. **Test Message Transfer**: Confirm bidirectional data exchange
5. **Performance Testing**: Measure latency and throughput

---

**Compiled by**: Claude Code (OpenHarmony Build Expert)
**Timestamp**: 2026-01-16 09:17 UTC
