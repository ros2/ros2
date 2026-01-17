#!/bin/bash
# RMW Discovery System Service Deployment Script
# Deploys daemon, init config, and token config to KaihongOS devices

set -e

# Configuration
DEVICE_ID="${1:-ec29004133314d38433031a522413c00}"
BUILD_DIR="$(cd "$(dirname "$0")" && pwd)"
DAEMON_BIN="$BUILD_DIR/rmw_discovery_daemon"
INIT_CFG="$BUILD_DIR/init/rmw_discovery.cfg"
TOKEN_CFG="$BUILD_DIR/token/native_token_config.json"

echo "========================================="
echo " RMW Discovery System Service Deployment"
echo "========================================="
echo ""
echo "Device ID: $DEVICE_ID"
echo "Build Directory: $BUILD_DIR"
echo ""

# Check if daemon binary exists
if [ ! -f "$DAEMON_BIN" ]; then
    echo "ERROR: Daemon binary not found: $DAEMON_BIN"
    echo "Please run 'make' first"
    exit 1
fi

echo "Step 1: Preparing deployment files..."
mkdir -p /mnt/c/tmp/rmw_service_deploy
cp "$DAEMON_BIN" /mnt/c/tmp/rmw_service_deploy/
cp "$INIT_CFG" /mnt/c/tmp/rmw_service_deploy/
cp "$TOKEN_CFG" /mnt/c/tmp/rmw_service_deploy/
echo "✓ Files prepared"
echo ""

echo "Step 2: Uploading files to device..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\rmw_service_deploy\rmw_discovery_daemon' '/data/local/tmp/'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\rmw_service_deploy\rmw_discovery.cfg' '/data/local/tmp/'"
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID file send 'C:\tmp\rmw_service_deploy\native_token_config.json' '/data/local/tmp/'"
echo "✓ Files uploaded"
echo ""

echo "Step 3: Installing to system partitions..."
echo "  Remounting /system as read-write..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mount -o remount,rw /system'" || echo "  (mount may fail if already rw)"

echo "  Installing daemon to /system/bin..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'cp /data/local/tmp/rmw_discovery_daemon /system/bin/ && chmod 755 /system/bin/rmw_discovery_daemon'"

echo "  Installing init config to /system/etc/init..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mkdir -p /system/etc/init && cp /data/local/tmp/rmw_discovery.cfg /system/etc/init/'"

echo "  Installing token config to /system/etc/token_sync..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'mkdir -p /system/etc/token_sync && cp /data/local/tmp/native_token_config.json /system/etc/token_sync/rmw_discovery_token.json'"

echo "  Syncing filesystem..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'sync'"
echo "✓ Installation complete"
echo ""

echo "Step 4: Verification..."
echo "  Checking installed files..."
powershell.exe -NoProfile -Command "hdc -t $DEVICE_ID shell 'ls -lh /system/bin/rmw_discovery_daemon /system/etc/init/rmw_discovery.cfg 2>&1'"
echo ""

echo "========================================="
echo " Deployment Complete!"
echo "========================================="
echo ""
echo "Next steps:"
echo ""
echo "  1. Reboot device to start service:"
echo "     powershell.exe -Command \"hdc -t $DEVICE_ID shell 'reboot'\""
echo ""
echo "  2. After reboot (wait 2 min), verify service is running:"
echo "     powershell.exe -Command \"hdc -t $DEVICE_ID shell 'ps -ef | grep rmw_discovery'\""
echo ""
echo "  3. Check service logs:"
echo "     powershell.exe -Command \"hdc -t $DEVICE_ID shell 'cat /data/log/rmw_discovery.log'\""
echo ""
echo "  4. Monitor hilog for Discovery activity:"
echo "     powershell.exe -Command \"hdc -t $DEVICE_ID shell 'hilog | grep DiscoveryManager'\""
echo ""
echo "Expected output after successful startup:"
echo "  [DiscoveryManager] SessionServer created: id=XXX"
echo "  [DiscoveryManager] Init complete: peers>=1"
echo ""
