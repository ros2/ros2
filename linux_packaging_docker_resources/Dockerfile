FROM ubuntu:xenial
MAINTAINER Dirk Thomas <dthomas@osrfoundation.org>

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
RUN echo "deb https://packagecloud.io/github/git-lfs/ubuntu/ `lsb_release -cs` main" > /etc/apt/sources.list.d/github_git-lfs.list
RUN curl --silent https://packagecloud.io/gpg.key | apt-key add -

# Install some development tools.
RUN apt-get update && apt-get install -y build-essential ccache cmake pkg-config python3-empy python3-setuptools python3-vcstool

# Install build and test dependencies of ROS 2 packages.
RUN apt-get update && apt-get install -y clang-format-3.8 cppcheck git pydocstyle pyflakes python3-coverage python3-mock python3-nose python3-pep8 uncrustify

# Install and self update pip/setuptools to the latest version.
RUN apt-get update && apt-get install -y python3-pip
RUN pip3 install -U setuptools pip virtualenv

# Install the OpenSplice binary from the OSRF repositories.
RUN apt-get update && apt-get install -y libopensplice64

# Install OpenCV.
RUN apt-get update && apt-get install -y libopencv-dev

# Install Git-LFS.
RUN apt-get update && apt-get install -y git-lfs

# automatic invalidation once every day.
RUN echo "@today_str"

# Install build and test dependencies of ROS 2 packages.
RUN apt-get update && apt-get install -y python-rospkg ros-indigo-catkin ros-indigo-common-msgs ros-indigo-roscpp ros-indigo-rosmsg

# TODO hack to fix rosbag until official packages are available with the real fix.
RUN sed -i 's/import roslz4//' /opt/ros/indigo/lib/python2.7/dist-packages/rosbag/bag.py

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

CMD ["python3 -u run_ros2_packaging.py $CI_ARGS"]
