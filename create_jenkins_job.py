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

job_template = """\
<?xml version='1.0' encoding='UTF-8'?>
<project>
  <actions/>
  <description></description>
  <keepDependencies>false</keepDependencies>
  <properties>
    <com.coravy.hudson.plugins.github.GithubProjectProperty plugin="github@1.10">
      <projectUrl>{ci_scripts_repository}</projectUrl>
    </com.coravy.hudson.plugins.github.GithubProjectProperty>
    <jenkins.advancedqueue.AdvancedQueueSorterJobProperty plugin="PrioritySorter@2.9">
      <useJobPriority>false</useJobPriority>
      <priority>65</priority>
    </jenkins.advancedqueue.AdvancedQueueSorterJobProperty>
    <hudson.model.ParametersDefinitionProperty>
      <parameterDefinitions>
        <hudson.model.StringParameterDefinition>
          <name>CI_BRANCH_TO_TEST</name>
          <description>Branch to test across the ros2 repositories which have it.
For example, if you have a few repositories with the &apos;feature&apos; branch.
Then you can set this to &apos;feature&apos;.
The repositories with the &apos;feature&apos; branch will be changed to that branch.
Other repositories will stay on the default branch, usually &apos;master&apos;.
To use the default branch on all repositories, use an empty string.</description>
          <defaultValue></defaultValue>
        </hudson.model.StringParameterDefinition>
        <hudson.model.StringParameterDefinition>
          <name>CI_SCRIPTS_BRANCH</name>
          <description>Branch of ros2/ros2 repository from which to get the ci scripts.</description>
          <defaultValue>ci_scripts</defaultValue>
        </hudson.model.StringParameterDefinition>
        <hudson.model.StringParameterDefinition>
          <name>CI_ROS2_REPOS_URL</name>
          <description></description>
          <defaultValue></defaultValue>
        </hudson.model.StringParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_USE_WHITESPACE_IN_PATHS</name>
          <description>By setting this to True white space will be inserted into the paths.
The paths include the workspace, plus the source, build and install spaces.
This tests the robustness to whitespace being within the different paths.</description>
          <defaultValue>{use_whitespace_in_paths_default}</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_USE_CONNEXT</name>
          <description>By setting this to True, the build will attempt to use RTI&apos;s DDS.
This is always in addition to OpenSplice.</description>
          <defaultValue>{use_connext_default}</defaultValue>
        </hudson.model.BooleanParameterDefinition>
      </parameterDefinitions>
    </hudson.model.ParametersDefinitionProperty>
    <org.jenkinsci.plugins.requeuejob.RequeueJobProperty plugin="jobrequeue@1.0">
      <requeueJob>true</requeueJob>
    </org.jenkinsci.plugins.requeuejob.RequeueJobProperty>
  </properties>
  <scm class="hudson.plugins.git.GitSCM" plugin="git@2.3.4">
    <configVersion>2</configVersion>
    <userRemoteConfigs>
      <hudson.plugins.git.UserRemoteConfig>
        <url>{ci_scripts_repository}</url>
      </hudson.plugins.git.UserRemoteConfig>{extra_git_repos}
    </userRemoteConfigs>
    <branches>
      <hudson.plugins.git.BranchSpec>
        <name>refs/heads/${{CI_SCRIPTS_BRANCH}}</name>
      </hudson.plugins.git.BranchSpec>
    </branches>
    <doGenerateSubmoduleConfigurations>false</doGenerateSubmoduleConfigurations>
    <browser class="hudson.plugins.git.browser.GithubWeb">
      <url></url>
    </browser>
    <submoduleCfg class="list"/>
    <extensions>{extensions}
    </extensions>
  </scm>
  <assignedNode>{label_expression}</assignedNode>
  <canRoam>false</canRoam>
  <disabled>false</disabled>
  <blockBuildWhenDownstreamBuilding>false</blockBuildWhenDownstreamBuilding>
  <blockBuildWhenUpstreamBuilding>false</blockBuildWhenUpstreamBuilding>
  <triggers/>
  <concurrentBuild>false</concurrentBuild>
  <builders>
    <hudson.tasks.{shell_type}>
      <command>{task_command}</command>
    </hudson.tasks.{shell_type}>
  </builders>
  <publishers>
    <xunit plugin="xunit@1.93">
      <types>
        <GoogleTestType>
          <pattern>workspace/build/*/test_results/**/*.xml</pattern>
          <skipNoTestFiles>false</skipNoTestFiles>
          <failIfNotNew>true</failIfNotNew>
          <deleteOutputFiles>true</deleteOutputFiles>
          <stopProcessingIfError>true</stopProcessingIfError>
        </GoogleTestType>
      </types>
      <thresholds>
        <org.jenkinsci.plugins.xunit.threshold.FailedThreshold>
          <unstableThreshold>0</unstableThreshold>
          <unstableNewThreshold></unstableNewThreshold>
          <failureThreshold></failureThreshold>
          <failureNewThreshold></failureNewThreshold>
        </org.jenkinsci.plugins.xunit.threshold.FailedThreshold>
        <org.jenkinsci.plugins.xunit.threshold.SkippedThreshold>
          <unstableThreshold>0</unstableThreshold>
          <unstableNewThreshold></unstableNewThreshold>
          <failureThreshold></failureThreshold>
          <failureNewThreshold></failureNewThreshold>
        </org.jenkinsci.plugins.xunit.threshold.SkippedThreshold>
      </thresholds>
      <thresholdMode>1</thresholdMode>
      <extraConfiguration>
        <testTimeMargin>3000</testTimeMargin>
      </extraConfiguration>
    </xunit>
  </publishers>
  <buildWrappers>
    <hudson.plugins.ansicolor.AnsiColorBuildWrapper plugin="ansicolor@0.4.1">
      <colorMapName>xterm</colorMapName>
    </hudson.plugins.ansicolor.AnsiColorBuildWrapper>
  </buildWrappers>
</project>
"""


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]
    parser = argparse.ArgumentParser(description="Creates the 'ros2_batch_ci_osx' job on Jenkins")
    parser.add_argument(
        '--jenkins-url', '-u', help="Url of the jenkins server to which the job should be added",
        required=True)
    parser.add_argument(
        '--ci-scripts-repository', default='https://github.com/ros2/ros2.git',
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
        'extensions': '',
        'extra_git_repos': '',
    }

    jenkins = connect(args.jenkins_url)

    os_configs = {
        'linux': {
            'label_expression': 'buildslave',
            'shell_type': 'Shell',
            'extensions': """
      <hudson.plugins.git.extensions.impl.SubmoduleOption>
        <disableSubmodules>false</disableSubmodules>
        <recursiveSubmodules>true</recursiveSubmodules>
        <trackingSubmodules>false</trackingSubmodules>
      </hudson.plugins.git.extensions.impl.SubmoduleOption>
""",
            'extra_git_repos': """
      <hudson.plugins.git.UserRemoteConfig>
        <url>git@github.com:osrf/rticonnextdds-messaging.git</url>
        <credentialsId>4a4a7bac-b1a5-4092-ba50-88cc4e08cd8d</credentialsId>
      </hudson.plugins.git.UserRemoteConfig>
""",
            'task_command': """\
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

docker build -t ros2_batch_ci linux_docker_resources
echo "Using args: $CI_ARGS"
docker run \\
       -e UID=`id -u` -e GID=`id -g` -e CI_ARGS="$CI_ARGS" \\
       -i \\
       -v `pwd`:/home/rosbuild/ci_scripts \\
       ros2_batch_ci
""",
        },
        'osx': {
            'label_expression': 'osx_slave',
            'shell_type': 'Shell',
            'task_command': """\
export CI_ARGS=--do-venv
if [ -n "${CI_BRANCH_TO_TEST+x}" ]; then
  export CI_ARGS="$CI_ARGS --test-branch $CI_BRANCH_TO_TEST"
fi
if [ "$CI_USE_WHITESPACE_IN_PATHS" == "true" ]; then
  export CI_ARGS="$CI_ARGS --white-space-in sourcespace buildspace installspace workspace"
fi
if [ "$CI_USE_CONNEXT" == "true" ]; then
  export CI_ARGS="$CI_ARGS --connext"
fi
if [ -n "${CI_ROS2_REPOS_URL+x}" ]; then
  export CI_ARGS="$CI_ARGS --repo-file-url $CI_ROS2_REPOS_URL"
fi

rm -rf workspace "work space"

echo "Using args: $CI_ARGS"
/usr/local/bin/python3 -u run_ros2_batch.py $CI_ARGS
""",
            # TODO(wjwwood): remove next line when ros2/ros2#31 is fixed.
            'use_connext_default': 'false',
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
        },
    }

    for os, config in os_configs.items():
        job_name = 'ros2_batch_ci_test_' + os
        job_subs = dict(subs)
        for k in config:
            job_subs[k] = config[k]
        configure_job(jenkins, job_name, job_template.format(**job_subs))


if __name__ == '__main__':
    main()
