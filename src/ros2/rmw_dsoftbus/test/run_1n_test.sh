#!/bin/bash
#
# 1:N Routing Test Runner
#

D1=$(powershell.exe -Command "hdc list targets" | head -1 | tr -d '\r\n')
D2=$(powershell.exe -Command "hdc list targets" | sed -n '2p' | tr -d '\r\n')

echo "════════════════════════════════════════════════════════════"
echo "  RMW DSoftBus 1:N Routing Test"
echo "════════════════════════════════════════════════════════════"
echo ""
echo "Device 1 (Publisher): $D1"
echo "Device 2 (Subscriber): $D2"
echo ""

# Clean up any previous instances
echo "Cleaning up previous instances..."
powershell.exe -Command "hdc -t $D1 shell 'killall rmw_pubsub_real_test 2>/dev/null'" 2>/dev/null
powershell.exe -Command "hdc -t $D2 shell 'killall rmw_pubsub_real_test 2>/dev/null'" 2>/dev/null
sleep 1

# Start Subscriber on Device 2
echo ""
echo "[1/2] Starting Subscriber on Device 2..."
echo "Command: /data/test/rmw_pubsub_real_test --mode=sub1 --topic=/test"
echo ""

powershell.exe -Command "hdc -t $D2 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=sub1 --topic=/test'" > subscriber_output.txt 2>&1 &
SUB_PID=$!

echo "Subscriber started in background (PID: $SUB_PID)"
echo "Waiting 5 seconds for subscriber to initialize..."
sleep 5

# Start Publisher on Device 1
echo ""
echo "[2/2] Starting Publisher on Device 1..."
echo "Command: /data/test/rmw_pubsub_real_test --mode=pub --topic=/test --count=20"
echo ""

powershell.exe -Command "hdc -t $D1 shell 'LD_LIBRARY_PATH=/data:/system/lib64 /data/test/rmw_pubsub_real_test --mode=pub --topic=/test --count=20'" 2>&1 | tee publisher_output.txt

echo ""
echo "════════════════════════════════════════════════════════════"
echo "  Publisher completed"
echo "════════════════════════════════════════════════════════════"
echo ""

# Wait for subscriber to finish
echo "Waiting for subscriber to collect messages (10s)..."
sleep 10

# Kill subscriber
kill $SUB_PID 2>/dev/null

echo ""
echo "════════════════════════════════════════════════════════════"
echo "  Test Results"
echo "════════════════════════════════════════════════════════════"
echo ""
echo "Publisher output:"
grep -E "Published|message" publisher_output.txt | tail -5
echo ""
echo "Subscriber output:"
grep -E "Received|Statistics" subscriber_output.txt | tail -10
echo ""
echo "Full logs saved to:"
echo "  - publisher_output.txt"
echo "  - subscriber_output.txt"
