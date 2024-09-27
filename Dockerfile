ARG FROM_IMAGE=osrf/ros2:devel
FROM $FROM_IMAGE

# set environment
ARG ROS_DISTRO=rolling
ENV ROS_DISTRO=$ROS_DISTRO
ENV ROS_VERSION=2 \
    ROS_PYTHON_VERSION=3

# clone source
COPY ./ros2.repos /opt/ros2_ws
RUN vcs import src < ros2.repos

# install dependencies
RUN apt-get update && rosdep install -y \
    --from-paths src \
    --ignore-src \
    --skip-keys " \
        fastcdr \
        rti-connext-dds-6.0.1 \
        urdfdom_headers" \
        && rm -rf /var/lib/apt/lists/*

# # build source
# RUN colcon \
#     build \
#     --cmake-args --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Debug

# setup entrypoint
COPY ./ros_entrypoint.sh /

ENV RMW_IMPLEMENTATION="rmw_zenoh_cpp"

ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["bash"]
