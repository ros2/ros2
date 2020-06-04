#/bin/bash -ex

rosinstall_generator --upstream-development $(cat quality_level.txt | tr '\r\n' ' ') $(cat coverate_packages_list.txt) --rosdistro=foxy --deps --repos system_tests rmw_cyclonedds rmw_connext
