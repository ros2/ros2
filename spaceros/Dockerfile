# Copyright 2021 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# A Docker configuration script to build the Space ROS image.
#
# The script provides the following build arguments:
#
#   VCS_REF     - The git revision of the Space ROS source code (no default value).
#   VERSION     - The version of Space ROS (default: "preview")
#   WORKSPACE   - The location for the Space ROS source code in the container (default: /root/src/spaceros_ws)

FROM nvidia/cudagl:11.4.1-devel-ubuntu20.04

ARG VCS_REF
ARG VERSION="preview"
ARG WORKSPACE=/root/src/spaceros_ws
ARG REPOS_FILE_URL="https://raw.githubusercontent.com/space-ros/space-ros/main/ros2.repos"

# LABEL the image
LABEL org.label-schema.schema-version="1.0"
LABEL org.label-schema.name="Space ROS"
LABEL org.label-schema.description="Preview version of the Space ROS platform"
LABEL org.label-schema.vendor="Open Robotics"
LABEL org.label-schema.version=${VERSION}
LABEL org.label-schema.url="https://github.com/space-ros"
LABEL org.label-schema.vcs-url="https://github.com/space-ros/docker-images"
LABEL org.label-schema.vcs-ref=${VCS_REF}

# Disable prompting during package installation
ARG DEBIAN_FRONTEND=noninteractive

# The following commands are based on the source install for ROS 2 Rolling Ridley.
# See: https://docs.ros.org/en/ros2_documentation/rolling/Installation/Ubuntu-Development-Setup.html
# The main variation is getting Space ROS sources instead of the Rolling sources.

# Update the Ubuntu software repository
RUN apt-get update

# Set the locale
RUN apt-get install -y locales
RUN locale-gen en_US en_US.UTF-8
RUN update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG=en_US.UTF-8

# Add the ROS 2 apt repository
RUN apt-get install -y software-properties-common
RUN add-apt-repository universe
RUN apt-get update && apt-get install -y curl gnupg lsb-release
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Install required software development tools and ROS tools (and vim included for convenience)
RUN apt-get update && apt-get install -y \
  bison \
  build-essential \
  cmake \
  git \
  python3-colcon-common-extensions \
  python3-flake8 \
  python3-pip \
  python3-pytest-cov \
  python3-rosdep \
  python3-setuptools \
  python3-vcstool \
  wget \
  vim

# Install the required pip packages
RUN python3 -m pip install -U \
  flake8-blind-except \
  flake8-builtins \
  flake8-class-newline \
  flake8-comprehensions \
  flake8-deprecated \
  flake8-docstrings \
  flake8-import-order \
  flake8-quotes \
  pytest-repeat \
  pytest-rerunfailures \
  pytest \
  setuptools

# Get the Space ROS source code
RUN mkdir -p ${WORKSPACE}/src
WORKDIR ${WORKSPACE}
ADD ${REPOS_FILE_URL} ros2.repos
RUN vcs import src < ros2.repos

# Install system dependencies
RUN rosdep init && rosdep update
RUN rosdep install --from-paths src --ignore-src --rosdistro rolling -y --skip-keys "console_bridge fastcdr fastrtps rti-connext-dds-5.3.1 urdfdom_headers rmw_connextdds ros_testing rmw_connextdds rmw_fastrtps_cpp rmw_fastrtps_dynamic_cpp composition demo_nodes_py lifecycle rosidl_typesupport_fastrtps_cpp rosidl_typesupport_fastrtps_c ikos"

# Build the code in the workspace
RUN colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Install dependencies needed by IKOS
RUN apt-get install -y \
  clang-9 \
  cmake \
  g++ \
  gcc \
  libboost-dev \
  libboost-filesystem-dev \
  libboost-test-dev \
  libboost-thread-dev \
  libedit-dev \
  libgmp-dev \
  libsqlite3-dev \
  libtbb-dev \
  llvm-9 \
  llvm-9-dev \
  llvm-9-tools \
  python3 \
  python3-pygments \
  zlib1g-dev

# Get the IKOS source and build it
WORKDIR /root/src
RUN git clone https://github.com/NASA-SW-VnV/ikos.git && cd ikos && git checkout 8b0bab34846b72777cca2a60d473282971806cfc
ENV PYTHONPATH "$PYTHONPATH:/root/src/ikos/install/lib/python3.8/site-packages"
RUN mkdir ikos/build && cd ikos/build && cmake .. -DLLVM_CONFIG_EXECUTABLE=/usr/bin/llvm-config-9 --no-warn-unused-cli && make && make install
ENV PATH "$PATH:/root/src/ikos/install/bin"
ENV IKOS_SCAN_NOTIFIER_FILES "yes"

# The above installation doesn't install the IKOS egg file, so do it manually (https://github.com/NASA-SW-VnV/ikos/issues/185)
RUN cd /root/src/ikos/install/lib/python3.8/site-packages && python3 /usr/lib/python3/dist-packages/easy_install.py ./ikos-3.0-py3.8.egg

# Set up the entrypoint
WORKDIR ${WORKSPACE}
COPY ./ros_entrypoint.sh /
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["bash"]
