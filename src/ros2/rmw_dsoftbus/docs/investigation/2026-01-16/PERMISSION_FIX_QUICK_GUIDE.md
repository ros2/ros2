# Quick Fix Guide: dsoftbus Permission Issue

## Problem
CreateSessionServer fails with -426442743 (PERMISSION_DENIED)

## Solution
PKG_NAME field does not support regex. Use empty string for wildcards.

## Quick Fix

### 1. Edit Permission JSON

File: `/system/etc/communication/softbus/softbus_trans_permission.json`

Change wildcard entry PKG_NAME from:
```
"PKG_NAME": ".*"
```

To:
```
"PKG_NAME": ""
```

### 2. Deploy to Device

```bash
# Mount system as read-write
hdc shell mount -o rw,remount /

# Send file
hdc file send local.json /system/etc/communication/softbus/softbus_trans_permission.json

# Reboot
hdc shell reboot
```

### 3. Verify

```bash
hdc shell 'cd /data/test && ./your_test_program'
```

Expected: CreateSessionServer returns 0

## Why This Works

Empty PKG_NAME bypasses package validation.
SESSION_NAME still validates with regex.
Permissions work for all package names.

## Reference Files

- Fixed JSON: `rmw_dsoftbus/config/softbus_trans_permission_fixed.json`
- Full report: `docs/investigation/2026-01-16/DEEP_INVESTIGATION_REPORT_2026_01_16.md`
- Summary: `docs/investigation/2026-01-16/PERMISSION_SOLUTION_SUMMARY.md`

---

Created: 2026-01-16
Status: Tested and verified on rk3588s devices
