<img src="/logos/spaceros_white_on_blue.png" alt="Space ROS Logo - White on Blue" width="700"/>

Documentation is at https://space.ros.org

# Contribution rules

See the [contributing guide](CONTRIBUTING.md) for details on how to contribute
to the Space ROS project.

# Release steps

### Update ros2.repos file
```
git clone https://github.com/space-ros/space-ros.git
cd space-ros
git checkout -b <release-id>
earthly build +repos-file
git add ros2.repos
git commit -m "Update repos file for <release-id> release"
```

### Testing

We include a target and run command for testing the release process and repo generation scripts.
To build and attach to the container:

```
earthly build +repos-test
docker run -it -v .:/root/user_ws:rw space-ros-release-test:latest
```
