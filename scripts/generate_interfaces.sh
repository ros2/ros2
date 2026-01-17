#!/bin/bash
# Copyright (c) 2024 ROS2 KaihongOS Port Project
# Convenient shell wrapper for generate_ros2_interfaces.py

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PYTHON_SCRIPT="$SCRIPT_DIR/generate_ros2_interfaces.py"

# Check if Python script exists
if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "Error: $PYTHON_SCRIPT not found" >&2
    exit 1
fi

# Run the Python script
exec python3 "$PYTHON_SCRIPT" "$@"
