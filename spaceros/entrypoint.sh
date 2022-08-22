#!/bin/bash
set -e

# Setup the Space ROS environment
source "/home/spaceros-user/src/spaceros/install/setup.bash"
exec "$@"
