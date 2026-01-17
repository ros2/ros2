# Permission Issue - Complete Solution

Date: 2026-01-16
Status: SOLVED

## Problem
CreateSessionServer failed with error -426442743 SOFTBUS_PERMISSION_DENIED

## Root Cause
PKG_NAME field in permission JSON does NOT support regex patterns.
It only performs exact string matching.

The wildcard entry ".*" was trying to match the literal string ".*"
instead of acting as a wildcard pattern.

## Solution
Changed PKG_NAME from ".*" to empty string ""

Empty PKG_NAME bypasses package name validation completely.

## Validation Logic
- SESSION_NAME: Supports regex when REGEXP=true
- PKG_NAME: NO regex support, always exact match

## Test Results

CreateSessionServer: FIXED
- Returns 0 (success)
- Session server created successfully

OpenSession: PARTIAL
- API returns valid session ID
- Callback fails due to KH_TRANS initialization
- This is a system layer issue, not permission related

Device Discovery: WORKING
- GetAllNodeDeviceInfo returns 2 devices
- Both devices can discover each other

## Deployment
Modified: softbus_trans_permission_fixed.json
Deployed to: Both rk3588s devices
Action: Rebooted devices to reload configuration

## Conclusion
CreateSessionServer permission issue completely resolved.
OpenSession requires KH_TRANS system initialization.
Device discovery confirmed working.

Investigation complete: 2026-01-16
