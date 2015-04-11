FROM ubuntu:trusty
MAINTAINER William Woodall <william@osrfoundation.org>

# Prevent errors from apt-get.
# See: http://askubuntu.com/questions/506158/unable-to-initialize-frontend-dialog-when-using-ssh
ENV DEBIAN_FRONTEND noninteractive

# First fetch and install the RTI software, since it takes the longest.
RUN apt-get install -y curl patch
# Create a user to own the RTI install and build output.
RUN useradd -u 1234 -m rosbuild
USER rosbuild
WORKDIR /home/rosbuild

# Fetch the RTI self extracting shell file.
RUN curl http://s3.amazonaws.com/RTI/eval/rtidds510/RTI_Connext_DDS_Professional-5.1.0-RHEL6_64_lic.sh -o Connext-5.1.0-RHEL6_64.sh
# Patch the installed to be non-interactive.
ADD make_connext_install_non_interactive.patch /tmp/make_connext_install_non_interactive.patch
RUN patch Connext-5.1.0-RHEL6_64.sh < /tmp/make_connext_install_non_interactive.patch
# Run the installer.
RUN bash Connext-5.1.0-RHEL6_64.sh

# Return to root for the rest of the Dockerfile.
USER root

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
RUN apt-get update && apt-get install -y libopensplice63

# Add an entry point which changes rosbuild's UID from 1234 to the UID of the invoking user.
# This means that the generated files will have the same ownership as the host OS user.
ADD fix_user_id.sh /fix_user_id.sh
RUN chmod 755 /fix_user_id.sh

ENTRYPOINT ["/fix_user_id.sh"]

CMD ["cd /home/rosbuild/ci_scripts && python3 -u run_ros2_batch.py $CI_ARGS"]
