#!/bin/bash

set -o errexit
export PYTHONUNBUFFERED=1

WS_PATH=/home/rosbuild/ros2_ws
mkdir -p $WS_PATH/src

curl --silent https://raw.githubusercontent.com/ros2/examples/master/ros2.repos -o $WS_PATH/ros2.repos
vcs import $WS_PATH/src < $WS_PATH/ros2.repos


cd $WS_PATH

# Force a clean build
echo "removing build and install directories in $WS_PATH"
rm -rf build install

src/ament/ament_tools/scripts/ament.py build --build-tests
src/ament/ament_tools/scripts/ament.py test src || true
src/ament/ament_tools/scripts/ament.py test_results || true
