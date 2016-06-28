# ROS 2 CI Infrastructure

This branch of the ros2/ros2 repository contains all of the scripts and resources for running batch CI jobs of ROS 2 repositories on a Jenkins build farm.

## Setting up on a Jenkins build farm

You can run the `create_jenkins_job.py` Python3 script to create the jobs on your Jenkins build farm.
This assumes you have a Jenkins build farm with at least one Linux slave, OS X slave, and Windows slave.
However, even if you do not have the slaves setup yet, you can create the jobs.

Before you run the script to create the jobs, you'll need to setup your environment according to this document:

https://github.com/ros-infrastructure/ros_buildfarm/blob/master/doc/environment.rst

This document will tell you what dependencies to install/setup like `jenkinsapi` and `ros_buildfarm`, as well as tell you how to setup authentication for Jenkins so that the script can login into your Jenkins build farm.

Once you've setup your environment, run this:

```
$ python3 create_jenkins_job.py --jenkins-url http://jenkins.example.com
```

The above will contact the Jenkins master at the provided url and try to authenticate.
If successful, it will create three jobs:

- ros2_batch_ci_linux
- ros2_batch_ci_osx
- ros2_batch_ci_windows

These three jobs are very similar, with minor changes for the differences in the operating systems.

You can also change the default location from which these CI scripts are pulled with options `--ci-scripts-repository` and `--ci-scripts-default-branch`.
They allow you to change the default location from which to get the CI scripts, which is useful if you have forked ros2/ros2.
The defaults are `git@github.com:ros2/ros2.git` and `ci_scripts` respectively.
The branch can be changed when running the job (it's a job parameter) to make it easy to test changes to the CI scripts using a branch on the main repository.

## Adjusting batch CI jobs

The jobs will be mostly setup, but you may need to adjust some settings for your farm.

First you'll need to look at each job configuration and make sure that the 'Label Expression' for the 'Restrict where this project can be run' option matches some build slave label or build slave name for the operating system.
For example, the default value for this in the Windows job is 'windows_slave_eatable_desktop' because we (OSRF) run a Jenkins slave on a desktop in the office and this is its name.
Your Windows slave may be named differently and you'll need to update the label to match your slave or the job will not run.

Another thing to check is the credentials settings.
The RTI binaries are provided by a git submodule which points to a private GitHub repository.
You'll need to setup at least one ssh key in the Jenkins Credentials plugin and add the public part of that key as a deploy key on the private GitHub repository, currently https://github.com/osrf/rticonnextdds-src.
Then on each job you'll want to make sure that this key is selected in two places.
First under the 'Source Code Management' section, there is a 'Credentials' drop down box under the 'Repositories' section.
Select the appropriate ssh key from that list.
Second, under the 'SSH Agent' option, select the same ssh key from the drop down list called 'Credentials'.
Note this option will not be there for Windows because I could not get the ssh-agent to work on Windows correctly and it is not needed anyways.

## Setup CMake Warning Parsing

For CMake warnings to be parsed by the Warnings plugin you need to add a global configuration, see: https://github.com/ros2/ros2/pull/248#issuecomment-228885779

## Using the batch CI jobs

Each of the batch CI jobs have the same set of parameters.
The parameters have their own descriptions, but the main one to look at is the `CI_BRANCH_TO_TEST` parameter.
It allows you to select a branch name across all of the ROS 2 repositories which should be tested.
Repositories which have this branch will be switched to it, others will be left on the default branch, usually `master`.

### Notes about the Windows Slave

I had trouble setting up the ssh-agent on Windows, so I disabled the submodule init on Windows which removes the need for cloning from private repositories and there removes the need for ssh keys and the ssh agent.
The private submodule is still pulled on OS X and Linux.
