# Space ROS Docker Image

The Dockerfile in this directory builds Space ROS from source code.

## Building the Docker Image

To include drivers for NVIDIA GPUs, the Space ROS docker image is based on the NVIDIA CudaGL development image, version 11.4.1, which is, in turn, based on Ubuntu 20.04.

To build the docker image, run:

```
$ ./build-image.sh
```

The build process will take about 20 or 30 minutes, depending on the host computer.

## Running the Space ROS Docker Image in a Container

After building the image, you can see the newly-built image by running:

```
$ docker image list
```

The output will look something like this:

```
$ docker image list
REPOSITORY              TAG                        IMAGE ID       CREATED        SIZE
openrobotics/spaceros   latest                     629b13cf7b74   1 hour ago     7.8GB
nvidia/cudagl           11.4.1-devel-ubuntu20.04   336416dfcbba   1 day ago      5.35GB
```

The new image is named **openrobotics/spaceros:latest**.

To run the resulting image in a container, run:

```
$ docker run -it openrobotics/spaceros
```

You can also run using the image ID. In this case, the image ID is *629b13cf7b74* (each build will result in a different image ID), so the following command will run the same image:

```
$ docker run -it 629b13cf7b74
```

Upon startup, the container automatically runs the ros_entrypoint.sh script, which sources the Space ROS environment file (setup.bash). You'll now be running inside the container and should see a prompt similar to this:

```
root@d10d85c68f0e:/root/src/spaceros_ws# 
```

At this point, you can run the 'ros2' command line utility to make sure everything is working OK:

```
root@d10d85c68f0e:/root/src/spaceros_ws# ros2
usage: ros2 [-h] [--use-python-default-buffering] Call `ros2 <command> -h` for more detailed usage. ...

ros2 is an extensible command-line tool for ROS 2.

optional arguments:
  -h, --help            show this help message and exit
  --use-python-default-buffering
                        Do not force line buffering in stdout and instead use the python default buffering, which might be affected by PYTHONUNBUFFERED/-u and depends on whatever stdout is interactive or not

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
  topic      Various topic related sub-commands
  trace      Trace ROS nodes to get information on their execution
  wtf        Use `wtf` as alias to `doctor`

  Call `ros2 <command> -h` for more detailed usage.
```

## Running the Space ROS Unit Tests

The Space ROS unit tests are not built as part of the Docker image build. To run the unit tests in the container, execute the following command from the top of the Space ROS workspace:

```
root@d10d85c68f0e:/root/src/spaceros_ws# colcon test
```

The tests include running the static analysis tools clang_tidy and cppcheck (which has the MISRA 2012 add-on enabled).

You can use colcon's --packages-select option to run a subset of packages. For example, to run tests only for the rcpputils package and display the output directly to the console (as well as saving it to a log file), you can run:

```
root@d10d85c68f0e:/root/src/spaceros_ws# colcon test --event-handlers console_direct+ --packages-select rcpputils
```

## Viewing Test Output

 The output from the tests are stored in XUnit XML files, named *\<tool-name\>*.xunit.xml. After running the unit tests, you can scan the build directory for the various *\*.xunit.xml* files.

 For example, a clang_tidy.xunit.xml file looks like this:

```xml
<xml version="1.0" encoding="UTF-8"?>
<testsuite
  name="rmw.clang_tidy"
  tests="21"
  errors="0"
  failures="0"
  time="1.248"
>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/allocators.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/convert_rcutils_ret_to_rmw_ret.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/event.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/init.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/init_options.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/message_sequence.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/names_and_types.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/network_flow_endpoint.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/network_flow_endpoint_array.c"
    classname="rmw.clang_tidy"/>
  <testcase
    name="/root/src/spaceros_ws/src/rmw/rmw/src/publisher_options.c"
    classname="rmw.clang_tidy"/>

<etc>    
...

```

## Connecting Another Terminal to a Running Docker Container

Sometimes it may be convenient to attach additional terminals to a running Docker container.

With the Space ROS Docker container running, open a second host terminal and then run the following command to determine the container ID:

```
$ docker container list
```

The output will look something like this:

```
CONTAINER ID   IMAGE                   COMMAND                  CREATED          STATUS          PORTS     NAMES
d10d85c68f0e   openrobotics/spaceros   "/ros_entrypoint.sh …"   28 minutes ago   Up 28 minutes             inspiring_moser
```

The container ID in this case, is *d10d85c68f0e*. So, run the following command in the host terminal:

```
docker exec -it d10d85c68f0e /bin/bash --init-file "install/setup.bash"
```

You will then be at a prompt in the same running container.

In place of the container ID, you can also use the automatically-generated container name ("inspiring_moser" in this case).

## Running an IKOS Scan

In the docker container, the IKOS executables are provided on the PATH at /root/src/ikos/install/bin.
To run an IKOS scan on all of the Space ROS source (which will take a very long time), run the following command at the root of the Space ROS workspace:

```
root@d10d85c68f0e:/root/src/spaceros_ws# CC="ikos-scan-cc" CXX="ikos-scan-c++" LD="ikos-scan-cc" colcon build --build-base build_ikos --install-base install_ikos --cmake-args -DSECURITY=ON -DINSTALL_EXAMPLES=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON --no-warn-unused-cli
```

To run an IKOS scan on a specific package, such as rcpputils in this case, use the *--packages-select* option, as follows:

```
root@d10d85c68f0e:/root/src/spaceros_ws# CC="ikos-scan-cc" CXX="ikos-scan-c++" LD="ikos-scan-cc" colcon build --build-base build_ikos --install-base install_ikos --packages-select rcpputils --cmake-args -DSECURITY=ON -DINSTALL_EXAMPLES=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON --no-warn-unused-cli
```

The build output is put in the **build_ikos** subdirectory, per the *--build-base* option.

## Generating IKOS Results

To generate results for IKOS you can use the **ament_ikos** utility, which performs an IKOS analysis on the files previously compiled in the previous step. 
The utility takes one argument which is the directory to scan recursively for the generated IKOS marker files. 
For example, to generate results for all of the IKOS analysis files in the build_ikos subdirectory, execute the following command:

```
root@d10d85c68f0e:/root/src/spaceros_ws# ament_ikos build_ikos
```
