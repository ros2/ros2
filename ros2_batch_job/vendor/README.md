This folder contains external projects which are needed to run this batch CI script.
The external projects are pulled in using `git-subtree` which allows this script to use a known version of the external projects rather than being potentially impacted by changes made to those projects which are being tested.
The Python projects, for example `orsf_pycommon`, are pulled in and updated manually using `git-subtree`.
The vendor folders are inserted to the front of the path manually to make sure this version of the projects are used.

#### Updating the subtree

The external project is in the vendor folder and is imported using subtree.
This import can be updated by following these steps:

1. From the root of the git repository run:

```
$ git remote -v
```

1. If the upstream (e.g. `https://github.com/osrf/osrf_pycommon.git`) is already remote use that remote name. Otherwise add it as a remote like so (using `osrf_pycommon` as an example):

```
$ git remote add osrf_pycommon_upstream https://github.com/osrf/osrf_pycommon.git
```

1. Now run the update command:

```
$ git subtree pull -P ros2_batch_job/vendor/osrf_pycommon --squash osrf_pycommon_upstream master
```

#### Pushing changes upstream

You can also push to the upstream after first doing a pull as described above:

```
$ git subtree push -P ros2_batch_job/vendor/osrf_pycommon osrf_pycommon_upstream master
```