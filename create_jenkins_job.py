#!/usr/bin/env python3

# Copyright 2015 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import os
import sys

try:
    import ros_buildfarm  # noqa
except ImportError:
    sys.exit("Could not import ros_buildfarm, please add to the PYTHONPATH.")

try:
    import jenkinsapi  # noqa
except ImportError:
    sys.exit("Could not import jenkinsapi, please install it with pip or apt-get.")

from ros_buildfarm.jenkins import configure_job
from ros_buildfarm.jenkins import connect

job_templates_dir = os.path.join(os.path.abspath(os.path.dirname(__file__)), 'job_templates')

with open(os.path.join(job_templates_dir, 'ros2_batch_ci_job.xml.template')) as f:
    job_template = f.read()

with open(os.path.join(job_templates_dir, 'ros2_batch_ci_launcher_job.xml.template')) as f:
    launcher_job_template = f.read()


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]
    parser = argparse.ArgumentParser(description="Creates the 'ros2_batch_ci_osx' job on Jenkins")
    parser.add_argument(
        '--jenkins-url', '-u', help="Url of the jenkins server to which the job should be added",
        required=True)
    parser.add_argument(
        '--ci-scripts-repository', default='git@github.com:ros2/ros2.git',
        help="repository from which ci scripts should be cloned"
    )
    parser.add_argument(
        '--ci-scripts-default-branch', default='ci_scripts',
        help="default branch of the ci scripts repository to get ci scripts from (this is a job parameter)"
    )
    args = parser.parse_args(argv)

    subs = {
        'ci_scripts_repository': args.ci_scripts_repository,
        'ci_scripts_default_branch': args.ci_scripts_default_branch,
        'use_connext_default': 'true',
        'use_whitespace_in_paths_default': 'false',
        'label_expression': None,
        'task_command': None,
        'git_submodule_extension': """
      <hudson.plugins.git.extensions.impl.SubmoduleOption>
        <disableSubmodules>false</disableSubmodules>
        <recursiveSubmodules>true</recursiveSubmodules>
        <trackingSubmodules>false</trackingSubmodules>
      </hudson.plugins.git.extensions.impl.SubmoduleOption>
""",
        'extra_git_repos': '',
        'ssh_agent_build_wrapper': """
    <com.cloudbees.jenkins.plugins.sshagent.SSHAgentBuildWrapper plugin="ssh-agent@1.5">
      <credentialIds>
        <string>1e7d4696-7fd4-4bc6-8c87-ebc7b6ce16e5</string>
      </credentialIds>
      <ignoreMissing>false</ignoreMissing>
    </com.cloudbees.jenkins.plugins.sshagent.SSHAgentBuildWrapper>
""",
    }

    jenkins = connect(args.jenkins_url)

    unix_common_logic = """\
export CI_ARGS="--do-venv --force-ansi-color"
if [ -n "${CI_BRANCH_TO_TEST+x}" ]; then
  export CI_ARGS="$CI_ARGS --test-branch $CI_BRANCH_TO_TEST"
fi
if [ "$CI_USE_WHITESPACE_IN_PATHS" = "true" ]; then
  export CI_ARGS="$CI_ARGS --white-space-in sourcespace buildspace installspace workspace"
fi
if [ "$CI_USE_CONNEXT" = "true" ]; then
  export CI_ARGS="$CI_ARGS --connext"
fi
if [ -n "${CI_ROS2_REPOS_URL+x}" ]; then
  export CI_ARGS="$CI_ARGS --repo-file-url $CI_ROS2_REPOS_URL"
fi

rm -rf workspace "work space"

"""

    os_configs = {
        'linux': {
            'label_expression': 'buildslave',
            'shell_type': 'Shell',
            'task_command': unix_common_logic + """\
docker build -t ros2_batch_ci linux_docker_resources
echo "Using args: $CI_ARGS"
docker run \\
       --privileged \\
       -e UID=`id -u` -e GID=`id -g` -e CI_ARGS="$CI_ARGS" \\
       -i \\
       -v `pwd`:/home/rosbuild/ci_scripts \\
       ros2_batch_ci
""",
        },
        'osx': {
            'label_expression': 'osx_slave',
            'shell_type': 'Shell',
            'task_command': unix_common_logic + """\
echo "Using args: $CI_ARGS"
/usr/local/bin/python3 -u run_ros2_batch.py $CI_ARGS
""",
        },
        'windows': {
            'label_expression': 'windows_slave_eatable_desktop',
            'shell_type': 'BatchFile',
            'task_command': """\
set "CI_ARGS=--force-ansi-color"
if "%CI_BRANCH_TO_TEST%" NEQ "" (
  set "CI_ARGS=%CI_ARGS% --test-branch %CI_BRANCH_TO_TEST%"
)
if "%CI_USE_WHITESPACE_IN_PATHS%" == "true" (
  set "CI_ARGS=%CI_ARGS% --white-space-in sourcespace buildspace installspace workspace"
)
if "%CI_USE_CONNEXT%" == "true" (
  set "CI_ARGS=%CI_ARGS% --connext"
)
if "%CI_ROS2_REPOS_URL%" NEQ "" (
  set "CI_ARGS=%CI_ARGS% --repo-file-url %CI_ROS2_REPOS_URL%"
)

rmdir /S /Q workspace "work space"

echo Using args: %CI_ARGS%
python -u run_ros2_batch.py %CI_ARGS%""",
            # Do not use the submodule extension on Windows since ssh-agent doesn't work.
            'git_submodule_extension': '',
            # Do not use the ssh-agent build wrapper on Windows since ssh-agent doesn't work.
            'ssh_agent_build_wrapper': '',
        },
    }

    # Send the os specific jobs
    for os_name, config in os_configs.items():
        job_name = 'ros2_batch_ci_' + os_name
        job_subs = dict(subs)
        for k in config:
            job_subs[k] = config[k]
        configure_job(jenkins, job_name, job_template.format(**job_subs))

    # Send the launch job
    launcher_job_subs = dict(subs)
    launcher_job_subs['label_expression'] = 'buildslave'
    configure_job(jenkins, 'ros2_batch_ci_launcher', launcher_job_template.format(**launcher_job_subs))


if __name__ == '__main__':
    main()
