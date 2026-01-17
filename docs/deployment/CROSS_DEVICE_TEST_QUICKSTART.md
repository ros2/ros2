# Cross-Device RMW DSoftbus Testing - Quick Start Guide

**Deployment Date**: 2026-01-17
**Status**: ✅ All files deployed successfully

## Device Information

| Aspect | Device 1 | Device 2 |
|--------|----------|----------|
| **HDC ID** | `ec29004133314d38433031a522413c00` | `ec29004133314d38433031a5544f3c00` |
| **WiFi IP** | 192.168.11.192 | 192.168.11.196 |
| **MAC Address** | 1c:79:2d:df:f4:26 | 1c:79:2d:df:f4:78 |
| **IPv6** | fe80::1e79:2dff:fedf:f426/64 | fe80::1e79:2dff:fedf:f478/64 |
| **Role** | Publisher (talker) | Subscriber (listener) |

## Deployed Files

Both devices have identical deployments:

```
/system/lib64/platformsdk/librmw_dsoftbus.so  (2.7M) - RMW implementation library
/data/local/tmp/minimal_talker                (41K)  - Publisher test binary
/data/local/tmp/minimal_listener              (43K)  - Subscriber test binary
```

## Network Connectivity

- ✅ Both devices on same WiFi subnet (192.168.11.0/23)
- ✅ Network is directly routable (no NAT)
- ✅ IPv6 link-local addresses available for fallback
- ✅ Docker bridge (172.17.0.1/16) available on both

## Quick Test Commands

### 1. Verify Deployment

```bash
# Check librmw_dsoftbus.so on Device 1
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'ls -lh /system/lib64/platformsdk/librmw_dsoftbus.so'"

# Check librmw_dsoftbus.so on Device 2
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'ls -lh /system/lib64/platformsdk/librmw_dsoftbus.so'"

# Check test binaries
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'ls -lh /data/local/tmp/minimal_*'"
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'ls -lh /data/local/tmp/minimal_*'"
```

### 2. Test Network Connectivity

```bash
# Device 1 ping Device 2
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'ping -c 3 192.168.11.196'"

# Device 2 ping Device 1
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'ping -c 3 192.168.11.192'"
```

### 3. Run Cross-Device Test

**Terminal 1 - Start Publisher on Device 1:**

```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'export LD_LIBRARY_PATH=/system/lib64/platformsdk:/system/lib64:\$LD_LIBRARY_PATH && export RMW_IMPLEMENTATION=rmw_dsoftbus_cpp && /data/local/tmp/minimal_talker'"
```

**Terminal 2 - Start Subscriber on Device 2:**

```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'export LD_LIBRARY_PATH=/system/lib64/platformsdk:/system/lib64:\$LD_LIBRARY_PATH && export RMW_IMPLEMENTATION=rmw_dsoftbus_cpp && /data/local/tmp/minimal_listener'"
```

**Terminal 3 - Monitor Logs on Device 1:**

```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'hilog | grep -E \"rmw|dsoftbus|talker|ROS2\"'"
```

**Terminal 4 - Monitor Logs on Device 2:**

```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'hilog | grep -E \"rmw|dsoftbus|listener|ROS2\"'"
```

## Expected Test Output

### On Device 1 (minimal_talker):
```
Publishing message: Hello, ROS2 on KaihongOS! [0]
Publishing message: Hello, ROS2 on KaihongOS! [1]
Publishing message: Hello, ROS2 on KaihongOS! [2]
...
```

### On Device 2 (minimal_listener):
```
Received message: Hello, ROS2 on KaihongOS! [0]
Received message: Hello, ROS2 on KaihongOS! [1]
Received message: Hello, ROS2 on KaihongOS! [2]
...
```

## Environment Variables

The test commands above already include:
- `LD_LIBRARY_PATH=/system/lib64/platformsdk:/system/lib64:$LD_LIBRARY_PATH` - Library search path
- `RMW_IMPLEMENTATION=rmw_dsoftbus_cpp` - RMW implementation selection

## Troubleshooting

### Issue: Library not found
```
Solution: Verify LD_LIBRARY_PATH includes /system/lib64/platformsdk
Command: powershell.exe -NoProfile -Command "hdc -t <DEVICE_ID> shell 'echo \$LD_LIBRARY_PATH'"
```

### Issue: RMW implementation not found
```
Solution: Make sure RMW_IMPLEMENTATION=rmw_dsoftbus_cpp is set
Alternative: Check if librmw_implementation.so can find librmw_dsoftbus.so
```

### Issue: No communication between devices
```
Checklist:
1. Both devices on same WiFi: ping 192.168.11.196 from Device 1
2. dsoftbus service running: ps aux | grep softbus
3. Check permissions: cat /system/etc/communication/softbus/softbus_trans_permission.json
4. Check kernel firewall: iptables -L -n
5. View detailed logs: hilog | grep -E "softbus|dsoftbus|RMW"
```

### Issue: Slow message delivery
```
Solution: Check network latency and dsoftbus thread status
Commands:
  - Device 1: ping -c 5 192.168.11.196 | tail
  - Both: cat /proc/net/dev (check packet loss)
  - Both: ps aux | grep softbus (verify service health)
```

## File Locations Summary

| File | Device 1 | Device 2 | Status |
|------|----------|----------|--------|
| librmw_dsoftbus.so | /system/lib64/platformsdk/ | /system/lib64/platformsdk/ | ✅ |
| minimal_talker | /data/local/tmp/ | /data/local/tmp/ | ✅ |
| minimal_listener | /data/local/tmp/ | /data/local/tmp/ | ✅ |

## Next Steps

1. **Run basic connectivity tests** (ping between devices)
2. **Verify dsoftbus service** is running on both devices
3. **Start minimal_talker** on Device 1
4. **Start minimal_listener** on Device 2
5. **Monitor logs** to verify message exchange
6. **Collect test results** for validation

## Reference Documents

- **DEPLOYMENT_2026_01_17.md** - Detailed deployment log
- **docs/01_部署和验证/DEPLOYMENT_FINAL_SUMMARY_2026_01_05.md** - Previous deployment experience
- **docs/02_dsoftbus诊断体系/README_dsoftbus诊断文档索引.md** - Troubleshooting guide

## Additional Commands

### Get system information
```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'uname -a'"
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'uname -a'"
```

### Check dsoftbus status
```bash
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'ps aux | grep softbus_server'"
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a5544f3c00 shell 'ps aux | grep softbus_server'"
```

### View full system logs
```bash
# Clear logs
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'hilog -c'"

# Run test
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell '/data/local/tmp/minimal_talker'"

# Collect logs
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 shell 'hilog > /data/local/tmp/device1_test.log 2>&1 &'"
powershell.exe -NoProfile -Command "hdc -t ec29004133314d38433031a522413c00 file recv '/data/local/tmp/device1_test.log' 'C:\\tmp\\hdc_transfer\\'"
```

---

**Last Updated**: 2026-01-17
**Ready for Cross-Device Testing**: ✅ YES
