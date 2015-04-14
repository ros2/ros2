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
RUN apt-get update && apt-get install -y build-essential cmake python3-empy python3-setuptools python3-vcstool

# Install build and test dependencies of ROS 2 packages.
RUN apt-get update && apt-get install -y git python3-nose python3-coverage python3-pep8 pyflakes python3-mock libgtest-dev cppcheck clang-format-3.4 uncrustify

# Install and self update pip/setuptools to the latest version.
RUN apt-get update && apt-get install -y python3-pip
RUN pip3 install -U setuptools pip virtualenv

# Install the OpenSplice binary from the OSRF repositories.
RUN apt-get update && apt-get install -y libopensplice64

# Add and install the RTI binaries we made.
ADD rticonnextdds-messaging/librticonnextdds51_5.1.0-2_amd64.deb /tmp/librticonnextdds51_5.1.0-2_amd64.deb
RUN dpkg -i /tmp/librticonnextdds51_5.1.0-2_amd64.deb
ADD rticonnextdds-messaging/librticonnextdds51-dev_5.1.0-2_amd64.deb /tmp/librticonnextdds51-dev_5.1.0-2_amd64.deb
RUN dpkg -i /tmp/librticonnextdds51-dev_5.1.0-2_amd64.deb
ADD rticonnextdds-messaging/librticonnextdds-messaging51_5.1.0-2_amd64.deb /tmp/librticonnextdds-messaging51_5.1.0-2_amd64.deb
RUN dpkg -i /tmp/librticonnextdds-messaging51_5.1.0-2_amd64.deb
ADD rticonnextdds-messaging/librticonnextdds-messaging51-dev_5.1.0-2_amd64.deb /tmp/librticonnextdds-messaging51-dev_5.1.0-2_amd64.deb
RUN dpkg -i /tmp/librticonnextdds-messaging51-dev_5.1.0-2_amd64.deb

# Create a user to own the build output.
RUN useradd -u 1234 -m rosbuild
WORKDIR /home/rosbuild

# Add an entry point which changes rosbuild's UID from 1234 to the UID of the invoking user.
# This means that the generated files will have the same ownership as the host OS user.
ADD fix_user_id.sh /fix_user_id.sh
RUN chmod 755 /fix_user_id.sh

ENTRYPOINT ["/fix_user_id.sh"]

CMD ["cd /home/rosbuild/ci_scripts && python3 -u run_ros2_batch.py $CI_ARGS"]
