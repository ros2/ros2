FROM ubuntu:xenial
MAINTAINER William Woodall <william@osrfoundation.org>
ARG PLATFORM=x86

# Prevent errors from apt-get.
# See: http://askubuntu.com/questions/506158/unable-to-initialize-frontend-dialog-when-using-ssh
ENV DEBIAN_FRONTEND noninteractive

RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8

RUN apt-get update && apt-get install -y lsb-release
RUN apt-get update && apt-get install -y sudo

# Get curl for fetching the repo keys.
RUN apt-get update && apt-get install -y curl

# Get https transport for APT.
RUN apt-get update && apt-get install -y apt-transport-https

# Add the ROS repositories to the apt sources list.
RUN echo "deb http://repositories.ros.org/ubuntu/testing/ `lsb_release -cs` main" > /etc/apt/sources.list.d/ros-latest.list
RUN curl --silent http://repositories.ros.org/repos.key | apt-key add -

# Add the OSRF repositories to the apt sources list.
RUN echo "deb http://packages.osrfoundation.org/gazebo/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-latest.list
RUN curl --silent http://packages.osrfoundation.org/gazebo.key | apt-key add -

# Add the Git-LFS repository.
RUN echo "platform: ${PLATFORM}"
RUN if test ${PLATFORM} = x86; then echo "deb https://packagecloud.io/github/git-lfs/ubuntu/ `lsb_release -cs` main" > /etc/apt/sources.list.d/github_git-lfs.list; fi
RUN if test ${PLATFORM} = x86; then curl --silent https://packagecloud.io/gpg.key | apt-key add -; fi

# Install some development tools.
RUN apt-get update && apt-get install -y build-essential ccache cmake pkg-config python3-empy python3-setuptools python3-vcstool

# Install build and test dependencies of ROS 2 packages.
RUN apt-get update && apt-get install -y clang-format-3.8 cppcheck git pydocstyle pyflakes python3-coverage python3-mock python3-nose python3-pep8 uncrustify

# Install and self update pip/setuptools to the latest version.
RUN apt-get update && apt-get install -y python3-pip
RUN pip3 install -U setuptools pip virtualenv

# Install coverage build dependencies.
RUN apt-get update && apt-get install -y gcovr

# Install the OpenSplice binary from the OSRF repositories.
RUN apt-get update && apt-get install -y libopensplice64
# Update default domain id.
RUN sed -i "s/<Id>0<\/Id>/<Id>108<\/Id>/" /usr/etc/opensplice/config/ospl.xml

# Install the RTI dependencies.
RUN if test ${PLATFORM} = x86; then apt-get update && apt-get install -y default-jre-headless; fi

# Install dependencies for RTI web binaries install script.
RUN pip3 install pexpect

# Get and install the RTI web binaries.
RUN wget -q http://s3.amazonaws.com/RTI/Bundles/5.2.3/Evaluation/rti_connext_dds-5.2.3-eval-x64Linux3gcc4.8.2.run -O /tmp/rti-installer.run && chmod +x /tmp/rti-installer.run
ADD rti_web_binaries_install_script.py /tmp/rti_web_binaries_install_script.py

# Setup the RTI license file.
ADD rti_license.dat /tmp/rti_license.dat
RUN cp /tmp/rti_license.dat ~/rti_license.dat
ENV RTI_LICENSE_FILE=~/rti_license.dat

# Add and install the RTI binaries we made.
ADD rticonnextdds-src/librticonnextdds52_5.2.3-1_amd64.deb /tmp/librticonnextdds52_5.2.3-1_amd64.deb
ADD rticonnextdds-src/librticonnextdds52-dev_5.2.3-1_amd64.deb /tmp/librticonnextdds52-dev_5.2.3-1_amd64.deb
ADD rticonnextdds-src/rticonnextdds-tools_5.2.3-1_amd64.deb /tmp/rticonnextdds-tools_5.2.3-1_amd64.deb

# Install the eProsima dependencies.
RUN apt-get update && apt-get install -y libboost-chrono-dev libboost-date-time-dev libboost-program-options-dev libboost-regex-dev libboost-system-dev libboost-thread-dev valgrind

# Install OpenCV.
RUN apt-get update && apt-get install -y libopencv-dev

# Install Git-LFS.
RUN if test ${PLATFORM} = x86; then apt-get update && apt-get install -y git-lfs; fi

# Install Python3 development files.
RUN apt-get update && apt-get install -y python3-dev

# Create a user to own the build output.
RUN useradd -u 1234 -m rosbuild
RUN sudo -H -u rosbuild -- git config --global user.email "jenkins@ci.ros2.org"
RUN sudo -H -u rosbuild -- git config --global user.name "Jenkins ROS 2"
RUN echo 'rosbuild ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
WORKDIR /home/rosbuild

# Add an entry point which changes rosbuild's UID from 1234 to the UID of the invoking user.
# This means that the generated files will have the same ownership as the host OS user.
ADD entry_point.sh /entry_point.sh
RUN chmod 755 /entry_point.sh

ENTRYPOINT ["/entry_point.sh"]

CMD ["python3 -u run_ros2_batch.py $CI_ARGS"]
