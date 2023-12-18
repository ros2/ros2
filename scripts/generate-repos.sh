#!/bin/sh

usage() {
  echo "$0 [OUTPUT_FILENAME]"

  echo "	Generate a spaceros repos file containing packages listed in spaceros-pkgs.txt"
  echo "	and their dependencies, excluding packages in excluded-pkgs.txt"
  echo "	Set the ROSDISTRO environment variable to change the target ROS distribution."
  echo "	By default it is 'humble'."
  exit 0
}

OUTFILE=${1:-ros2.repos}
ROSDISTRO=${ROSDISTRO:-humble}

GENERATE_CMD=rosinstall_generator
# Use the repos file format rather than rosinstall format.
GENERATE_CMD="$GENERATE_CMD --format repos"
# Set rosdistro. Overrideable with ROSDISTRO environment variable.
GENERATE_CMD="$GENERATE_CMD --rosdistro $ROSDISTRO"

# Include all dependencies
GENERATE_CMD="$GENERATE_CMD --deps"

# Use version tags of upstream repositories
GENERATE_CMD="$GENERATE_CMD --upstream"

# Exclude packages which we don't incorporate into Space ROS
excluded_pkgs=$(cat excluded-pkgs.txt)
GENERATE_CMD="$GENERATE_CMD --exclude $excluded_pkgs --"

# Use Space ROS packages as base package list
# This list should stay small, rosinstall_generator will resolve dependencies.
spaceros_pkgs=$(cat spaceros-pkgs.txt)
GENERATE_CMD="$GENERATE_CMD $spaceros_pkgs"

$GENERATE_CMD > $OUTFILE
