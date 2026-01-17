# rmw_dsoftbus Configuration Files

## softbus_trans_permission.json

This file configures dsoftbus session permissions for rmw_dsoftbus.

### Installation

Copy to target device:
```bash
# On KaihongOS/OpenHarmony device
adb push softbus_trans_permission.json /system/etc/communication/softbus/
adb shell chmod 644 /system/etc/communication/softbus/softbus_trans_permission.json
adb shell reboot
```

### Configuration Fields

- **SESSION_NAME**: Pattern matching session names (supports wildcards)
- **REGEXP**: Enable regex pattern matching
- **DEVID**: Device ID type (NETWORKID, UUID, UDID)
- **SEC_LEVEL**: Security level (public, private, protected)
- **APP_INFO**: Application permission list
  - **TYPE**: Application type (native_app, system_app, normal_app)
  - **PKG_NAME**: Package name (must match RMW_DSOFTBUS_PACKAGE_NAME)
  - **ACTIONS**: Allowed operations (create, open)

### Troubleshooting

If you see error `-426442743` (SOFTBUS_PERMISSION_DENIED):
1. Verify package name matches in both files
2. Check file exists at correct path
3. Ensure proper file permissions (644)
4. Reboot device after installation
