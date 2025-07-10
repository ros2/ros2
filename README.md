<img src="/logos/spaceros_white_on_blue.png" alt="Space ROS Logo - White on Blue" width="700"/>

Documentation is at https://space.ros.org.

For information on compiling the base Space ROS image see the [usage instructions](./docs/USAGE.md).

For information on the release process refere to the [release docs](./docs/RELEASE.md).


## Building the Space ROS image

1. Install [Earthly](https://earthly.dev/get-earthly/) (v0.8.0 or later).
2. You can build the Space ROS image using the following command:

```bash
# To build the base Space ROS image
earthly +main-image

# To build the dev Space ROS image
earthly +dev-image
```

## Contribution rules

See the [contributing guide](https://github.com/space-ros/.github/blob/master/CONTRIBUTING.md) for details on how to contribute
to the Space ROS project.
