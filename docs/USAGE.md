# Space ROS Docker Image and Earthly configuration

The Earthfile configuration in this directory facilitates builds of Space ROS from source code.
The generated container image is based on Ubuntu 22.04 (Jammy)

## Prerequisites

The following software is required to build the Space ROS Docker image:

- [Git](https://git-scm.com/downloads)
- [Docker](https://docs.docker.com/get-docker/)
- [Earthly](https://earthly.dev/get-earthly)

## Setup

The image is built using the [Earthly](https://earthly.dev/get-earthly) utility.
First, clone the Space ROS repository:

```bash
git clone https://github.com/space-ros/space-ros.git
cd space-ros
```

Make sure docker is running and the user has the necessary permissions to run docker commands.

Space ROS comes in different flavors, the following image variants are available:

 - `main-image`: The main image contains the ROS 2 core packages, including the ROS 2 client libraries, the ROS 2 command line tools, and the ROS 2 middleware implementations.
 - `dev-image`: The dev image contains the main image and additional tools for development, such as the ROS 2 build tools, the ROS 2 test tools, and the ROS 2 launch tools, as well as tooling for static code analysis.

Build the Space ROS Docker image by running the following command:

```bash
# To build a specific image variant, use the following command:
earthly +main-image
earthly +dev-image

# To build all image variants and artifacts, use the following command:
earthly +all
```

The build process will take about 30 minutes (or more), depending on the host computer.

## Usage

After building, check the newly-built images by running:

```bash
docker image list
```

The output will look something like the following, with the `main-image` tagged as `latest`:

```
$ docker image ls
REPOSITORY          TAG       IMAGE ID       CREATED         SIZE
osrf/space-ros      latest    18a3c6709c93   2 hours ago     1.37GB
osrf/space-ros      dev       ecf1761fc53e   2 hours ago     3.68GB
```

From here, we use the `osrf/space-ros:latest` image as an example.
Open a bash shell with:

```bash
docker run -it --rm osrf/space-ros:latest /bin/bash
```

You'll now be running inside the container and should see a prompt similar to this:

```
spaceros-user@d10d85c68f0e:~/$
```

The Space ROS setup tools are installed in `/opt/ros/spaceros/`.
`/opt/ros/spaceros/setup.bash` is sourced when launching or attaching to a container.
Run the `ros2` command line utility to make sure everything is working:

```
spaceros-user@d10d85c68f0e:~/$ ros2
usage: ros2 [-h] [--use-python-default-buffering] Call `ros2 <command> -h` for more detailed usage. ...

ros2 is an extensible command-line tool for ROS 2.

options:
  -h, --help            show this help message and exit
  --use-python-default-buffering
                        Do not force line buffering in stdout and instead use the python default buffering, which might be affected by
                        PYTHONUNBUFFERED/-u and depends on whatever stdout is interactive or not

Commands:
  action     Various action related sub-commands
  component  Various component related sub-commands
  daemon     Various daemon related sub-commands
  doctor     Check ROS setup and other potential issues
  interface  Show information about ROS interfaces
  launch     Run a launch file
  lifecycle  Various lifecycle related sub-commands
  multicast  Various multicast related sub-commands
  node       Various node related sub-commands
  param      Various param related sub-commands
  pkg        Various package related sub-commands
  run        Run a package specific executable
  service    Various service related sub-commands
  test       Run a ROS2 launch test
  topic      Various topic related sub-commands
  trace      Trace ROS 2 nodes to get information on their execution. The main 'trace' command requires user interaction; to trace non-interactively, use the 'start'/'stop'/'pause'/'resume' sub-commands
  wtf        Use `wtf` as alias to `doctor`

  Call `ros2 <command> -h` for more detailed usage.
```

Space ROS promotes building projects from source code, and more instructions can be found in the [Space ROS documentation](https://space.ros.org).


## SpaceROS for development

The `osrf/space-ros:dev` image is intended for development and contains additional tools for development, such as the ROS 2 build tools, the ROS 2 test tools, and the ROS 2 launch tools.

We provide a run script to start the Space ROS Docker container for development, which includes additional arguments for network sharing and graphics access,

```bash
./run.sh
```

This container will have all the tools necessary for building and testing ROS 2 packages.

### Preparing Space ROS sources

A manifest of the exact sources of Space ROS used to produce the current image is saved as `spaceros.repos` in the `/opt/ros/spaceros/scripts` directory.
Before rebuilding or testing, we must setup an equivalent colcon workspace.

```bash
mkdir -p ${HOME}/spaceros_ws/src
cd ${HOME}/spaceros_ws
vcs import src < "${SPACEROS_DIR}/scripts/spaceros.repos"
```

Additionally, out of the box the install is owned by `root`, modify the ownership prior to building:

```bash
sudo chown -R spaceros-user:spaceros-user "${SPACEROS_DIR}"
```

### Next Steps

1. To use IKOS follow the instructions in the [IKOS Integration](./IKOS.md) documentation.
2. To reproduce the build process, follow the instructions in the [Reproducible Builds](./REPRODUCIBLE.md) documentation.
