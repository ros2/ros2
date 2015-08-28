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
          <defaultValue>false</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_USE_CONNEXT</name>
          <description>By setting this to True, the build will attempt to use RTI&apos;s DDS.
This is always in addition to OpenSplice.</description>
          <defaultValue>true</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_ISOLATED</name>
          <description>By setting this to True, the build will use the --isolated option.</description>
          <defaultValue>false</defaultValue>
        </hudson.model.BooleanParameterDefinition>
      </parameterDefinitions>
    </hudson.model.ParametersDefinitionProperty>
