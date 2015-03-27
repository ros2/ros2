#!/bin/bash

set -o errexit
export PYTHONUNBUFFERED=1
WS_PATH=/home/rosbuild/ros2_ws

cd $WS_PATH

# Force a clean build
rm -rf build devel install

src/ament/ament_tools/scripts/ament.py build --build-tests
src/ament/ament_tools/scripts/ament.py test src || true
src/ament/ament_tools/scripts/ament.py test_results || true
