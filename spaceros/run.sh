#!/usr/bin/env bash

# Runs a docker container with the image created by build.bash
# Requires:
#   docker
#   an X server
#   rocker


ROCKER_ARGS="--devices /dev/dri/ --dev-helpers --x11 --user-override-name spaceros-user --network host"

IMG_NAME=osrf/space-ros

# Replace `/` with `_` to comply with docker container naming
# And append `_runtime`
CONTAINER_NAME="$(tr '/' '_' <<< "$IMG_NAME")"
ROCKER_ARGS="${ROCKER_ARGS} --name $CONTAINER_NAME"
echo "Using image <$IMG_NAME> to start container <$CONTAINER_NAME>"

# Start the container
rocker ${ROCKER_ARGS} $IMG_NAME
