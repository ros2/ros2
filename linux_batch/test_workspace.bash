#!/bin/bash

set -o errexit
export PYTHONUNBUFFERED=1
# Fetch the sources to build
WS_PATH=$1
echo "testing workspace $1"

if [ ! -d $WS_PATH ]; then
  echo "Invalid workspace directory: $WS_PATH"
  exit 1
fi

python create_dockerfile.py Dockerfile.template docker_context/Dockerfile
docker build -t ros2_test docker_context
docker run -it -v $WS_PATH:/home/rosbuild/ros2_ws ros2_test /tmp/test_workspace.bash
