# OpenCV builds for Windows

See [the ROS 2 wiki](https://github.com/ros2/ros2/wiki/Windows-Development-Setup#install-a-binary-distribution-of-opencv) for installation instructions.


## For ROS2 Dashing and current development

* Visual Studio 2019: https://github.com/ros2/ros2/releases/download/opencv-archives/opencv-3.4.6-vc16.VS2019.zip
* Visual Studio 2017: https://github.com/ros2/ros2/releases/download/opencv-archives/opencv-3.4.6-vc15.VS2017.zip

## For ROS2 Crystal Clemmys Patch Release >= 4

* Visual Studio 2017: https://github.com/ros2/ros2/releases/download/opencv-archives/opencv-3.4.6-vc15.VS2017.zip

Note: This reduces number of CI configurations that OpenRobotics has to maintain.

## For ROS 2 Bouncy Bolson and Crystal Clemmys Patch Release < 4

* Visual Studio 2017: https://github.com/ros2/ros2/releases/download/opencv-archives/opencv-3.4.1-vc15.VS2017.zip


## For ROS 2 Ardent Apalone and earlier

* Visual Studio 2015: https://github.com/ros2/ros2/releases/download/release-beta2/opencv-2.4.13.2-vc14.VS2015.zip
* Visual Studio 2017: https://github.com/ros2/ros2/releases/download/release-beta1/opencv-2.4.13.2-vc15update.zip


# Creating OpenCV builds for Windows

Warning: If doing this in a VM, be aware that the OpenCV build will take approximate 10GB, so be sure there is enough free space to complete the operation.

1. Download corresponding release version zip file from: https://github.com/opencv/opencv/releases
   * For example: https://github.com/opencv/opencv/archive/3.4.6.zip 
2. Extract OpenCV source code to a suitable location (e.g. C:\dev\opencv-3.4.6)
3. For VS2019, install CMake 3.14.1 via Chocolatey with either: `choco install -y cmake` or `choco upgrade -y cmake`
4. From `x64 Native Tools Command Prompt for VSxxxx` (in Start Menu, installed with Visual Studio)
   * Note: Native Tools Command Prompt version must match the version that you intend to build for.

For VS2019 (`x64 Native Tools Command Prompt for VS2019`)
```
cd C:\dev\opencv-3.4.6
mkdir build2
cd build2
# Make sure to use the version installed via Chocolately
"C:\Program Files\CMake\bin\cmake.exe" -G"Visual Studio 16 2019" ..
# Build Debug Configuration
"C:\Program Files\CMake\bin\cmake.exe" --build . --config Debug --target INSTALL
# Build Release Configuration
"C:\Program Files\CMake\bin\cmake.exe" --build . --config Release --target INSTALL
```

For VS2017 (`x64 Native Tools Command Prompt for VS2017`)
```
cd C:\dev\opencv-3.4.6
mkdir build2
cd build2
# Make sure to use the version installed via Chocolately
"C:\Program Files\CMake\bin\cmake.exe" -G"Visual Studio 15 2017 Win64" ..
# Build Debug Configuration
"C:\Program Files\CMake\bin\cmake.exe" --build . --config Debug --target INSTALL
# Build Release Configuration
"C:\Program Files\CMake\bin\cmake.exe" --build . --config Release --target INSTALL
```

5. The results of the build will be available in the `build\install` directory 
   * For example: `C:\dev\opencv-3.4.6\build\install`
6. (For distribution only) Rename the resulting install directory to `opencv` and zip it.
7. (For distribution only) Rename the resulting zip file with the format `opencv-<opencv_version>-vc<vc_version>.VS<vs_year>.zip`
    * For example: `opencv-3.4.6-vc16.VS2019.zip` or `opencv-3.4.6-vc15.VS2017.zip`
