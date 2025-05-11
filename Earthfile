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
VERSION 0.8

ARG --global IMAGE_NAME="osrf/space-ros"
ARG --global IMAGE_TAG="latest"
ARG --global USERNAME="spaceros-user"
ARG --global HOME="/home/${USERNAME}"
ARG --global WORKSPACE_DIR="/workspace"
ARG --global SKIP_BUILD_TEST=true

###############################################################################
### Target Configurations
# Targets are the main entry points for the Earthfile. They are the commands
# that can be run by the user. The `all` target is the default target that is
# run when no target is specified.
###############################################################################
all:
  # Order preserved for build
  BUILD +main-image
  BUILD +dev-image

main-image:
  BUILD +image --IMAGE_VARIANT=${IMAGE_TAG}

dev-image:
  BUILD +image --IMAGE_VARIANT=dev

###############################################################################
### PreInstallation Stage
# This stage is responsible for setting up the base image with the necessary
# dependencies required for the subsequent stages.
###############################################################################
pre-installation:
  FROM ubuntu:noble

  ENV DEBIAN_FRONTEND=noninteractive
  ENV ROS_DISTRO="jazzy"
  ENV SPACEROS_DIR="/opt/spaceros"
  ENV HOME=${HOME}
  WORKDIR ${WORKSPACE_DIR}

  # Set the locale
  RUN --mount=type=cache,mode=0777,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,mode=0777,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      apt-get update && \
      apt-get install -y locales
  RUN locale-gen en_US en_US.UTF-8
  RUN update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
  ENV LANG=en_US.UTF-8

  # The following commands are based on the source install for ROS 2 Rolling Ridley.
  # See: https://docs.ros.org/en/ros2_documentation/rolling/Installation/Ubuntu-Development-Setup.html
  # The main variation is getting Space ROS sources instead of the Rolling sources.

  # Add the ROS 2 apt repository
  RUN --mount=type=cache,mode=0777,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,mode=0777,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      apt-get install -y \
        curl \
        git \
        cmake \
        build-essential \
        bison \
        wget \
        gnupg \
        lsb-release \
        python3-pip \
        python3-setuptools \
        software-properties-common
  RUN add-apt-repository universe
  RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
  RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null \
    && apt update

###############################################################################
### Setup Stage
# This stage is responsible for setting up the ROS 2 workspace and the required
# dependencies for the workspace.
###############################################################################
setup:
  FROM +pre-installation
  # Install required software development tools and ROS tools (and vim included for convenience)
  RUN apt-get install -y python3-rosinstall-generator

  COPY scripts ./
  COPY excluded-pkgs.txt spaceros-pkgs.txt spaceros.repos ./

  # This is a fresh image, so we do not need to exclude installed packages.
  ENV AMENT_PREFIX_PATH=${SPACEROS_DIR}
  RUN sh generate-repos.sh \
                 --outfile ros2.repos \
                 --packages spaceros-pkgs.txt \
                 --excluded-packages excluded-pkgs.txt \
                 --rosdistro ${ROS_DISTRO}
  RUN  python3 merge-repos.py ros2.repos spaceros.repos -o output.repos
  SAVE ARTIFACT output.repos AS LOCAL ros2.repos

###############################################################################
### IKOS Installation
# This stage is responsible for installing IKOS and its dependencies.
# This will be used for static analysis of the ROS 2 workspace during build
# test and development.
###############################################################################
ikos-install:
  FROM +pre-installation

  RUN --mount=type=cache,mode=0777,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,mode=0777,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      apt-get update && apt-get install --yes \
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
      clang-14 \
      ros-dev-tools

  RUN git clone -b v3.5 --depth 1 https://github.com/NASA-SW-VnV/ikos.git
  RUN cd ikos \
      && mkdir build \
      && cd build \
      && cmake \
      -DCMAKE_CXX_STANDARD=17 \
      -DCMAKE_CXX_STANDARD_REQUIRED=ON \
      -DCMAKE_INSTALL_PREFIX="/opt/ikos" \
      -DCMAKE_BUILD_TYPE="Release" \
      -DLLVM_CONFIG_EXECUTABLE="/usr/lib/llvm-14/bin/llvm-config" \
      .. \
      && make -j$(nproc) \
      && make install
  ENV PATH="/opt/ikos/bin/:$PATH"
  RUN rm -rf ikos

  SAVE ARTIFACT /opt/ikos AS LOCAL ikos

ADD_IKOS:
  FUNCTION
    RUN --mount=type=cache,mode=0777,target=/var/cache/apt,sharing=locked,id=cache_apt_cache \
      --mount=type=cache,mode=0777,target=/var/lib/apt,sharing=locked,id=lib_apt_cache \
      apt-get install --yes gcc \
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
      clang-14 \
      ros-dev-tools

    COPY +ikos-install/ikos /opt/ikos
    ENV PATH="/opt/ikos/bin/:$PATH"

###############################################################################
### Sources Stage
# This stage is responsible for fetching the ROS 2 workspace sources.
###############################################################################
sources:
  FROM +setup

  RUN apt install -y python3-vcstool \
    && mkdir src -p \
    && vcs import --retry 3 src < output.repos \
    && vcs export --exact src > exact.repos

  # Save artifacts to be  used
  SAVE ARTIFACT exact.repos
  SAVE ARTIFACT src

###############################################################################
### Rosdep Stage
# This stage is responsible for installing the system dependencies required
# for the ROS 2 workspace.
###############################################################################
rosdep:
  FROM +pre-installation

  # Rosdep updates
  RUN apt-get install -y python3-rosdep \
    && rosdep init \
    && rosdep update

  # Copy Repos file
  COPY +sources/src ./src
  COPY excluded-pkgs.txt excluded-deps.txt ./

  # Install system package dependencies using rosdep
  RUN rosdep install -y \
        --from-paths src --ignore-src \
        --simulate \
        --rosdistro ${ROS_DISTRO} \
        # `urdfdom_headers` is cloned from source, however rosdep can't find it.
        # It is because package.xml manifest is missing. See: https://github.com/ros/urdfdom_headers
        # Additionally, IKOS must be excluded as per: https://github.com/space-ros/docker/issues/99
        --skip-keys "$(tr '\n' ' ' < 'excluded-pkgs.txt') urdfdom_headers ikos" > rosdeps.txt

  # Process rosdeps.txt to a shell script
  RUN touch rosdeps.sh \
        && echo "#!/bin/bash" > rosdeps.sh \
        && echo "apt-get update" >> rosdeps.sh \
        && echo "apt-get install -y \\" >> rosdeps.sh \
        && grep -v -F -f excluded-deps.txt rosdeps.txt | sed 's/^/  /' >> rosdeps.sh \
        && chmod +x rosdeps.sh

  # The generated shell script is used by the prepare-image stage prior to building the image
  # saving build time by not having to install dependencies again.
  SAVE ARTIFACT rosdeps.sh

###############################################################################
### Build Stage
# This stage is responsible for building the ROS 2 workspace.
###############################################################################
build:
  FROM +rosdep

  # Uncrustify Vendor has vcstool as a dependency
  RUN apt install -y python3-vcstool
  RUN bash rosdeps.sh
  RUN mkdir -p ${SPACEROS_DIR} \
    && apt install -y python3-colcon-common-extensions \
    && colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DCMAKE_CXX_FLAGS="--param ggc-min-expand=20" \
        --no-warn-unused-cli --install-base ${SPACEROS_DIR}  --merge-install

  SAVE ARTIFACT ${SPACEROS_DIR}

###############################################################################
### Build Test Stage
# This stage is responsible for running the tests on the ROS 2 workspace.
###############################################################################
build-test:
  FROM +build

  # Install dependencies for testing
  RUN apt install -y python3-flake8 \
      python3-pydocstyle \
      clang-tidy \
      graphviz \
      uncrustify \
      python3-pycodestyle \
      cppcheck \
      python3-nose \
      google-mock \
      pydocstyle \
      python3-pytest \
      python3-pytest-timeout \
      python3-pytest-mock \
      python3-pytest-cov \
      python3-matplotlib \
      pyflakes3 \
      python3-mypy \
      python3-argcomplete
  RUN pip3 install pytest-rerunfailures \
      pytest-cov \
      pytest-repeat \
      mypy \
      argcomplete --break-system-packages

  RUN . ${SPACEROS_DIR}/setup.sh && \
      colcon test \
        --merge-install \
        --retest-until-pass 2 \
        --packages-skip ament_lint \
        --ctest-args -LE "(ikos|xfail)" \
        --ctest-args "--output-on-failure" \
        --pytest-args -m "not xfail" \
        --pytest-args "--disable-warnings" \
        --install-base ${SPACEROS_DIR}

  # Create tar ball of the logs directory
  RUN tar -cjf build_test_results.tar.bz2 log

  SAVE ARTIFACT /workspace/build_test_results.tar.bz2 AS LOCAL build_test_results.tar.bz2

###############################################################################
### Image Stage
# This stage is responsible for creating the final image with the ROS 2
# workspace. The image is saved only if the build-test stage is successful.
###############################################################################
prepare-image:
  FROM +pre-installation

  # Add missing dependencies
  RUN apt update \
    && apt install -y libspdlog-dev \
      python3-numpy \
      tzdata \
      sudo \
      ros-dev-tools
  RUN pip3 install pyyaml \
      lark \
      packaging \
      netifaces \
      catkin_pkg \
      psutil --break-system-packages

  # Prepare the image
  RUN mkdir -p ${SPACEROS_DIR}
  COPY +rosdep/rosdeps.sh ${SPACEROS_DIR}/rosdeps.sh
  RUN bash ${SPACEROS_DIR}/rosdeps.sh

###############################################################################
### Prepare Image Stage
# This stage is responsible for preparing the image with the ROS 2 workspace.
# The image is saved only if the build-test stage is successful.
###############################################################################
image:
  ARG --required IMAGE_VARIANT
  FROM +prepare-image

  COPY +build/spaceros ${SPACEROS_DIR}
  COPY +sources/exact.repos ${SPACEROS_DIR}/scripts/spaceros.repos
  COPY scripts/generate-repos.sh scripts/merge-repos.py ${SPACEROS_DIR}/scripts/
  RUN chmod +x ${SPACEROS_DIR}/scripts/generate-repos.sh ${SPACEROS_DIR}/scripts/merge-repos.py \
    && mv ${SPACEROS_DIR}/rosdeps.sh ${SPACEROS_DIR}/scripts/rosdeps.sh

  # Post Installation
  DO +POST_INSTALLATION --IMAGE_VARIANT=${IMAGE_VARIANT}

  # Clear Apt and Pip cache
  RUN rm -rf /var/lib/apt/lists/* /tmp/pip-reqs /var/cache/apt/archives \
    && apt-get clean \
    && pip cache purge

  # Add user and group
  RUN useradd -m -s /bin/bash ${USERNAME} \
    && chown -R ${USERNAME}:${USERNAME} ${SPACEROS_DIR}/scripts \
    && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME}
  RUN echo "source ${SPACEROS_DIR}/setup.bash" >> ${HOME}/.bashrc

  RUN chown -R ${USERNAME}:${USERNAME} ${HOME}

  USER ${USERNAME}
  WORKDIR ${HOME}

  # Only save image if build-test is successful
  IF [ "${SKIP_BUILD_TEST}" = "true" ]
    SAVE IMAGE ${IMAGE_NAME}:${IMAGE_VARIANT}
  ELSE
    BUILD +build-test
    SAVE IMAGE ${IMAGE_NAME}:${IMAGE_VARIANT}
  END

###############################################################################
### Post Installation Stage
# This stage is responsible for cleaning up the workspace and installing
# additional dependencies based on the image variant.
###############################################################################
POST_INSTALLATION:
  FUNCTION
  ARG --required IMAGE_VARIANT

  # Remove workspace if image variant is core or dev
  RUN rm -rf ${WORKSPACE_DIR}

  # If Dev, install IKOS and excluded dependencies
  IF [ "${IMAGE_VARIANT}" = "dev" ]
    DO +ADD_IKOS

    COPY excluded-deps.txt ./
    RUN apt install -y $(grep -v '^#' excluded-deps.txt) \
      && rm -rf excluded-deps.txt
  END

###############################################################################
### Push Image Stage for main image
# This stage is responsible for pushing the core image to the registry.
###############################################################################
push-main-image:
  # This can be overridden with a blank string to prevent pushing to the registry.
  ARG --required VCS_REF

  FROM +image --IMAGE_VARIANT=${IMAGE_TAG}

  LABEL org.label-schema.schema-version="1.0"
  LABEL org.label-schema.name="Space ROS - Core/Main"
  LABEL org.label-schema.description="Core version of the Space ROS platform"
  LABEL org.label-schema.vendor="Open Robotics"
  LABEL org.label-schema.url="https://github.com/space-ros"
  LABEL org.label-schema.vcs-url="https://github.com/space-ros/space-ros"
  LABEL org.label-schema.vcs-ref=${VCS_REF}

  SAVE IMAGE --push ${IMAGE_NAME}:${IMAGE_TAG}

###############################################################################
### Push Image Stage for dev image
# This stage is responsible for pushing the dev image to the registry.
###############################################################################
push-dev-image:
  # This can be overridden with a blank string to prevent pushing to the registry.
  ARG --required VCS_REF

  FROM +image --IMAGE_VARIANT=dev

  LABEL org.label-schema.schema-version="1.0"
  LABEL org.label-schema.name="Space ROS - Dev"
  LABEL org.label-schema.description="Dev version of the Space ROS platform"
  LABEL org.label-schema.vendor="Open Robotics"
  LABEL org.label-schema.url="https://github.com/space-ros"
  LABEL org.label-schema.vcs-url="https://github.com/space-ros/space-ros"
  LABEL org.label-schema.vcs-ref=${VCS_REF}

  SAVE IMAGE --push ${IMAGE_NAME}:dev
