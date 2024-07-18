<img src="/logos/spaceros_white_on_blue.png" alt="Space ROS Logo - White on Blue" width="700"/>

Documentation is at https://space.ros.org.

For information on compiling the base Space ROS image see the [README](./spaceros/README.md).

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
