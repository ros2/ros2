#!/usr/bin/env bash

# Runs the development docker image
# Requires:
#   docker
#   an X server

IMG_NAME=osrf/space-ros
TAG=dev

# Replace `/` with `_` to comply with docker container naming
# And append `_runtime`
CONTAINER_NAME="$(tr '/' '_' <<< "${IMG_NAME}")"

# Start the container
docker run \
  --rm \
  -it \
  --network host \
  --name ${CONTAINER_NAME} \
  -e DISPLAY \
  -e TERM \
  -e QT_X11_NO_MITSHM=1 \
  ${IMG_NAME}:${TAG} \
  bash
