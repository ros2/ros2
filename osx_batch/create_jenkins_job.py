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
    this_dir = os.path.abspath(os.path.dirname(__file__))
    sys.path.insert(0, os.path.join(this_dir, '..', '..', 'ros_buildfarm'))
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
      <projectUrl>https://github.com/ros2/ros2/</projectUrl>
    </com.coravy.hudson.plugins.github.GithubProjectProperty>
    <jenkins.advancedqueue.AdvancedQueueSorterJobProperty plugin="PrioritySorter@2.9">
      <useJobPriority>false</useJobPriority>
      <priority>-1</priority>
    </jenkins.advancedqueue.AdvancedQueueSorterJobProperty>
    <org.jenkinsci.plugins.requeuejob.RequeueJobProperty plugin="jobrequeue@1.0">
      <requeueJob>false</requeueJob>
    </org.jenkinsci.plugins.requeuejob.RequeueJobProperty>
  </properties>
  <scm class="hudson.plugins.git.GitSCM" plugin="git@2.3.4">
    <configVersion>2</configVersion>
    <userRemoteConfigs>
      <hudson.plugins.git.UserRemoteConfig>
        <url>https://github.com/ros2/ros2.git</url>
      </hudson.plugins.git.UserRemoteConfig>
    </userRemoteConfigs>
    <branches>
      <hudson.plugins.git.BranchSpec>
        <name>*/ci_scripts</name>
      </hudson.plugins.git.BranchSpec>
    </branches>
    <doGenerateSubmoduleConfigurations>false</doGenerateSubmoduleConfigurations>
    <browser class="hudson.plugins.git.browser.GithubWeb">
      <url></url>
    </browser>
    <submoduleCfg class="list"/>
    <extensions/>
  </scm>
  <assignedNode>osx_slave</assignedNode>
  <canRoam>false</canRoam>
  <disabled>false</disabled>
  <blockBuildWhenDownstreamBuilding>false</blockBuildWhenDownstreamBuilding>
  <blockBuildWhenUpstreamBuilding>false</blockBuildWhenUpstreamBuilding>
  <triggers/>
  <concurrentBuild>false</concurrentBuild>
  <builders>
    <hudson.tasks.Shell>
      <command>/usr/local/bin/python3 -u osx_batch/osx_batch_build.py</command>
    </hudson.tasks.Shell>
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
    args = parser.parse_args(argv)

    # TODO(wjwwood): template in emails and other stuff using the expand_template command.
    job_config = job_template

    jenkins = connect(args.jenkins_url)

    job_name = 'ros2_batch_ci_osx'
    configure_job(jenkins, job_name, job_config)


if __name__ == '__main__':
    main()
