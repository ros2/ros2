#!/bin/bash

set -e

# Function to display usage information
usage() {
    echo "Generate .repos file with list of SpaceROS repositories to clone"
    echo "Usage: $0 --packages PACKAGES --outfile OUTFILE [--excluded-packages EXCLUDED_PACKAGES] [--repos REPOS] [--rosdistro ROSDISTRO] [--upstream UPSTREAM] [--exclude-installed EXCLUDE_INSTALLED]"
    echo "  --outfile                   The output file"
    echo "  --packages                  File containing a list of ROS packages to include"
    echo "  --repos                     File containing a list of ROS repos to use."
    echo "                              Use as alternative to 'packages', rosinstall can generate .repos file from list of repos instead of list of packages"
    echo "  --excluded-packages         File containing a list of packages to exclude [optional] "
    echo "  --rosdistro                 ROS2 distribution (default: jazzy)"
    echo "  --upstream                  Specify whether to use version tags of upstream repositories (default: true)"
    echo "  --exclude-installed         Whether to exclude already installed packages from .repos file. Installed workspaces must be sourced to make it work (default: true)"
    echo "  -h, --help                  Display this help and exit"
    exit 1
}

# Initialize variables with default values
rosdistro="jazzy"
packages=""
outfile=""
excluded_packages=""
repos=""
upstream="true"
exclude_installed="true"
if ! ARGS=$(getopt -o h -l help,packages:,outfile:,excluded-packages:,repos:,rosdistro:,upstream:,exclude-installed: -n "$0" -- "$@"); then
    usage
fi
eval set -- "$ARGS"

# Parse command-line arguments
while true; do
    case "$1" in
        -h|--help )
            usage
        ;;
        --packages )
            # remove whitespace
            packages=$(echo "$2" | xargs)
            shift 2
        ;;
        --outfile )
            outfile=$2
            shift 2
        ;;
        --excluded-packages )
            # remove whitespace
            excluded_packages=$(echo "$2" | xargs)
            shift 2
        ;;
        --repos )
            # remove whitespace
            repos=$(echo "$2" | xargs)
            shift 2
        ;;
        --rosdistro )
            rosdistro=$2
            shift 2
        ;;
        --upstream )
            upstream=$2
            shift 2
        ;;
        --exclude-installed )
            exclude_installed=$2
            shift 2
        ;;
        -- )
            shift
            break
        ;;
        * )
            echo "Invalid argument!"
            usage
        ;;
    esac
done

# Check if all required arguments are provided
if [ -z "${packages}" ] && [ -z "${repos}" ]; then
    echo "Error: Either packages or repos (or both) have to be specified"
    usage
fi

if [ -z "${outfile}" ]; then
    echo "Error: Required argument outfile missing"
    usage
fi

# Define the command for generating rosinstall
GENERATE_CMD=rosinstall_generator

# Use the repos file format rather than rosinstall format.
GENERATE_CMD="${GENERATE_CMD} --format repos"

# Set rosdistro.
GENERATE_CMD="${GENERATE_CMD} --rosdistro ${rosdistro}"

# Include all dependencies
GENERATE_CMD="${GENERATE_CMD} --deps"

# Use version tags of upstream repositories
if [ "$upstream" = "true" ]; then
    GENERATE_CMD="${GENERATE_CMD} --upstream"
fi

# Exclude packages which we do not want to incorporate into Space ROS
excluded_pkgs=$(cat "${excluded_packages}")
if [ "$exclude_installed" = "true" ]; then
    # paths to packages are stored in AMENT_PREFIX_PATH,
    # however rosinstall_generator expects ROS_PACKAGE_PATH variable to be set
    export ROS_PACKAGE_PATH=${AMENT_PREFIX_PATH}
    GENERATE_CMD="${GENERATE_CMD} --exclude ${excluded_pkgs} RPP"
else
    GENERATE_CMD="${GENERATE_CMD} --exclude ${excluded_pkgs}"
fi

# include additional repos along specified packages'
if [ -n "${repos}" ]; then
    space_ros_repos=$(cat "${repos}")
    GENERATE_CMD="${GENERATE_CMD} --repos ${space_ros_repos}"
fi

if [ -n "${packages}" ]; then
    spaceros_pkgs=$(cat "${packages}")
    GENERATE_CMD="${GENERATE_CMD} -- ${spaceros_pkgs}"
fi

echo "Generating .repos file with command:"
echo "${GENERATE_CMD}"

# Generate rosinstall file
${GENERATE_CMD} > "${outfile}"

echo "rosinstall file generated: ${outfile}"
