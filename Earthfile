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
VERSION 0.6
FROM ubuntu:jammy

# Defaulting to ROS 2 humble
ARG ROS_DISTRO="humble"

setup:
  # Disable prompting during package installation
  ARG DEBIAN_FRONTEND=noninteractive
  ARG ROS_DISTRO

  # TODO - the `setup` step will be merged with the `setup` step in spaceros docker Earthfile
  # This variable will then act as a single source of truth.
  ENV ROS_DISTRO ${ROS_DISTRO}

  # The following commands are based on the source install for ROS 2 Rolling Ridley.
  # See: https://docs.ros.org/en/ros2_documentation/rolling/Installation/Ubuntu-Development-Setup.html
  # The main variation is getting Space ROS sources instead of the Rolling sources.

  # Set the locale
  RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      apt-get update && \
      apt-get install -y locales
  RUN locale-gen en_US en_US.UTF-8
  RUN update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
  ENV LANG=en_US.UTF-8

  # Add the ROS 2 apt repository
  RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      apt-get update && \
      apt-get install -y \
        curl \
        gnupg \
        lsb-release \
        software-properties-common
  RUN add-apt-repository universe
  RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
  RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

  # Install required software development tools and ROS tools (and vim included for convenience)
  RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      apt-get update && \
      apt-get install -y \
        bison \
        build-essential \
        cmake \
        git \
        python3-colcon-common-extensions \
        python3-flake8 \
        python3-flake8-blind-except \
        python3-flake8-builtins \
        python3-flake8-class-newline \
        python3-flake8-comprehensions \
        python3-flake8-deprecated \
        python3-flake8-docstrings \
        python3-flake8-import-order \
        python3-flake8-quotes \
        python3-pip \
        python3-pytest \
        python3-pytest-cov \
        python3-pytest-repeat \
        python3-pytest-rerunfailures \
        python3-rosdep \
        python3-rosinstall-generator \
        python3-setuptools \
        python3-vcstool \
        wget \
        vim

  # Define the username and key variables
  ENV USERNAME spaceros-user
  ENV HOME_DIR=/home/${USERNAME}
  ENV SPACEROS_DIR=/opt/spaceros

  # Create the spaceros directory
  RUN mkdir --mode=777 -p ${SPACEROS_DIR}

  # Create a spaceros user
  RUN useradd -m ${USERNAME} && \
    echo "${USERNAME}:${USERNAME}" | chpasswd && \
    usermod --shell /bin/bash ${USERNAME} && \
    usermod -aG sudo ${USERNAME} && \
    mkdir -p /etc/sudoers.d && \
    echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/${USERNAME} && \
    chmod 0440 /etc/sudoers.d/${USERNAME}
  USER ${USERNAME}
  WORKDIR ${SPACEROS_DIR}

  # Update the OpenGL version
  RUN sudo add-apt-repository ppa:kisak/kisak-mesa
  RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      sudo apt update && sudo apt upgrade -y

  # Create install location and copy in relevant scripts
  COPY --chown ${USERNAME}:${USERNAME} --dir docker/scripts/ ${SPACEROS_DIR}

repos-file:
  FROM +setup
  COPY excluded-pkgs.txt ./
  COPY spaceros-pkgs.txt ./
  COPY spaceros.repos ./
  RUN --no-cache sh scripts/generate-repos.sh \
                 --outfile ros2.repos \
                 --packages spaceros-pkgs.txt \
                 --excluded-packages excluded-pkgs.txt \
                 --rosdistro ${ROS_DISTRO}
  RUN --no-cache python3 scripts/merge-repos.py ros2.repos spaceros.repos -o output.repos
  SAVE ARTIFACT output.repos AS LOCAL ros2.repos

spaceros-artifacts:
  # we must run it in a separate container, so that downstream tasks can be cached if vcs file does not change
  FROM +setup
  USER ${USERNAME}
  WORKDIR ${SPACEROS_DIR}

  COPY ros2.repos ./
  COPY excluded-pkgs.txt ./

  # we run vcstool inside this task, because some packages in `ros2.repos` are not pinned and otherwise
  # earthly won't pull latest changes
  RUN mkdir src
  RUN vcs import --shallow --retry 3 --input ros2.repos src
  RUN vcs export --exact src > exact.repos

  SAVE ARTIFACT ros2.repos
  SAVE ARTIFACT exact.repos # `ros2.repos`, but with pinned versions (e.g. SHAs instead of branches)
  SAVE ARTIFACT excluded-pkgs.txt

sources:
  FROM +setup
  COPY +spaceros-artifacts/ros2.repos ros2.repos
  COPY +spaceros-artifacts/excluded-pkgs.txt excluded-pkgs.txt
  COPY +spaceros-artifacts/exact.repos exact.repos
  RUN mkdir src
  RUN vcs import --shallow --retry 3 --input exact.repos src
  SAVE ARTIFACT src AS LOCAL src

vcs-exact:
  COPY +spaceros-artifacts/${SPACEROS_DIR}/exact.repos exact.repos
  SAVE ARTIFACT exact.repos AS LOCAL exact.repos

rosdep:
  FROM +sources
  COPY src src/

  # Install system package dependencies using rosdep
  RUN sudo rosdep init && rosdep update
  RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      sudo apt-get update && \
      rosdep update && \
      rosdep install -y \
        --from-paths src --ignore-src \
        --rosdistro ${ROS_DISTRO} \
        # `urdfdom_headers` is cloned from source, however rosdep can't find it.
        # It is because package.xml manifest is missing. See: https://github.com/ros/urdfdom_headers
        # Additionally, IKOS must be excluded as per: https://github.com/space-ros/docker/issues/99
        --skip-keys "$(tr '\n' ' ' < 'excluded-pkgs.txt') urdfdom_headers ikos"
  RUN rm excluded-pkgs.txt

  RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      sudo apt-get update && \
      sudo apt-get install --yes \
        gcc \
        g++ \
        cmake \
        libgmp-dev \
        libboost-dev \
        libboost-filesystem-dev \
        libboost-thread-dev \
        libboost-test-dev \
        libsqlite3-dev \
        libtbb-dev \
        libz-dev \
        libedit-dev \
        python3 \
        python3-pip \
        python3-venv \
        llvm-14 \
        llvm-14-dev \
        llvm-14-tools \
        clang-14

  WORKDIR ${SPACEROS_DIR}
  RUN git clone -b v3.2 --depth 1 https://github.com/NASA-SW-VnV/ikos.git
  WORKDIR ${SPACEROS_DIR}/ikos
  RUN mkdir build
  WORKDIR ${SPACEROS_DIR}/ikos/build
  RUN cmake \
        -DCMAKE_INSTALL_PREFIX="/opt/ikos" \
        -DCMAKE_BUILD_TYPE="Debug" \
        -DLLVM_CONFIG_EXECUTABLE="/usr/lib/llvm-14/bin/llvm-config" \
        ..
  RUN make
  RUN sudo make install
  ENV PATH="/opt/ikos/bin/:$PATH"
  WORKDIR ${SPACEROS_DIR}
  RUN sudo rm -rf ikos/

build:
  FROM +rosdep
  RUN colcon build \
        --cmake-args \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        --no-warn-unused-cli
  COPY +spaceros-artifacts/exact.repos install/exact.repos
  SAVE ARTIFACT install AS LOCAL install

build-testing:
  FROM +rosdep
  RUN colcon build \
      --cmake-args \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      --no-warn-unused-cli
  RUN . install/setup.sh && \
      colcon test \
        --retest-until-pass 2 \
        --ctest-args -LE "(ikos|xfail)" \
        --pytest-args -m "not xfail"
  RUN . install/setup.sh && \
      ros2 run process_sarif make_build_archive
  COPY +spaceros-artifacts/exact.repos install/exact.repos
  SAVE ARTIFACT log/build_results_archives/build_results_*.tar.bz2 AS LOCAL log/build_results_archives/
  SAVE ARTIFACT install AS LOCAL install

image:
  FROM +rosdep
  ARG VCS_REF
  ARG tag='latest'

  # Specify the docker image metadata
  LABEL org.label-schema.schema-version="1.0"
  LABEL org.label-schema.name="Space ROS"
  LABEL org.label-schema.description="Preview version of the Space ROS platform"
  LABEL org.label-schema.vendor="Open Robotics"
  LABEL org.label-schema.url="https://github.com/space-ros"
  LABEL org.label-schema.vcs-url="https://github.com/space-ros/docker-images"
  LABEL org.label-schema.vcs-ref=${VCS_REF}

  COPY +build/install ${SPACEROS_DIR}/install
  COPY +spaceros-artifacts/exact.repos ${SPACEROS_DIR}/exact.repos
  RUN rm -r src

  WORKDIR ${HOME_DIR}
  COPY docker/entrypoint.sh /ros_entrypoint.sh
  ENTRYPOINT ["/ros_entrypoint.sh"]
  CMD ["bash"]
  SAVE IMAGE --push osrf/space-ros:latest osrf/space-ros:$tag
