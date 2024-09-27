# SHELL := /bin/bash
# .DEFAULT_GOAL := local

docker_autorun_flags = -t --rm -it --network=host --privileged --name ros2_zenoh
docker_local_flags = $(docker_base_flags) --env="DISPLAY" -v $(HOME)/.Xauthority:/root/.Xauthority:rw -v /tmp/.X11-unix:/tmp/.X11-unix

docker_dirs = -v $(PWD)/build:/opt/ros2_ws/build:rw -v $(PWD)/install:/opt/ros2_ws/install:rw

local:
	docker build -t ros2_zenoh -f Dockerfile .
	mkdir -p install build
	# chown -R $(USER):$(USER) install build

local-compile:
	docker run $(docker_autorun_flags) $(docker_local_flags) $(docker_dirs) ros2_zenoh:latest colcon build --merge-install --event-handlers console_direct+ --cmake-args --no-warn-unused-cli -DCMAKE_BUILD_TYPE=Debug --packages-up-to rclcpp test_communication test_rclcpp rmw_zenoh_cpp ros2cli ros2run

local-test:
	docker exec ros2_zenoh colcon test --merge-install --event-handlers console_direct+ --packages-select rclcpp --ctest-args -R zenoh

local-run:
	docker run $(docker_autorun_flags) $(docker_local_flags) $(docker_dirs) ros2_zenoh:latest bash

local-join-run:
	docker exec -it ros2_zenoh bash

run-daemon:
	docker run $(docker_autorun_flags) $(docker_local_flags) $(docker_dirs) ros2_zenoh:latest bash -c "source /opt/ros2_ws/install/setup.bash && ros2 run rmw_zenoh_cpp rmw_zenohd"
