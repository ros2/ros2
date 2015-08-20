FROM ubuntu:trusty
MAINTAINER William Woodall <william@osrfoundation.org>

# Prevent errors from apt-get.
# See: http://askubuntu.com/questions/506158/unable-to-initialize-frontend-dialog-when-using-ssh
ENV DEBIAN_FRONTEND noninteractive

# Get curl for fetching the repo keys.
RUN apt-get install -y curl

# Add the ROS repositories to the apt sources list.
RUN echo "deb http://54.183.65.232/ubuntu/testing/ `lsb_release -cs` main" > /etc/apt/sources.list.d/ros-latest.list
RUN curl --silent http://54.183.65.232/repos.key | sudo apt-key add -

# Add the OSRF repositories to the apt sources list.
RUN echo "deb http://packages.osrfoundation.org/gazebo/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-latest.list
RUN curl --silent http://packages.osrfoundation.org/gazebo.key | sudo apt-key add -

# Install some development tools.
RUN apt-get update && apt-get install -y build-essential cmake pkg-config python3-empy python3-setuptools python3-vcstool

# Install build and test dependencies of ROS 2 packages.
RUN apt-get update && apt-get install -y clang-format-3.4 cppcheck git libgtest-dev pyflakes python3-coverage python3-mock python3-nose python3-pep8 uncrustify

# Install and self update pip/setuptools to the latest version.
RUN apt-get update && apt-get install -y python3-pip
RUN pip3 install -U setuptools pip virtualenv

# Install the OpenSplice binary from the OSRF repositories.
RUN apt-get update && apt-get install -y libopensplice64
# Update default domain id
RUN sed -i "s/<Id>0<\/Id>/<Id>108<\/Id>/" /usr/etc/opensplice/config/ospl.xml

# Install the RTI dependencies
RUN apt-get update && apt-get install -y default-jre-headless

# Add and install the RTI binaries we made.
ADD rticonnextdds-src/librticonnextdds52_5.2.0-1_amd64.deb /tmp/librticonnextdds52_5.2.0-1_amd64.deb
ADD rticonnextdds-src/librticonnextdds52-dev_5.2.0-1_amd64.deb /tmp/librticonnextdds52-dev_5.2.0-1_amd64.deb                                
ADD rticonnextdds-src/rticonnextdds-tools_5.2.0-1_amd64.deb /tmp/rticonnextdds-tools_5.2.0-1_amd64.deb

# Install OpenCV
RUN apt-get update && apt-get install -y libopencv-dev

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
