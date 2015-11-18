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
          <description>By setting this to True, the build will attempt to use RTI&apos;s Connext.</description>
          <defaultValue>@(use_connext_default)</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_DISABLE_CONNEXT_STATIC</name>
          <description>By setting this to True, the build will disable the Connext static rmw implementation.</description>
          <defaultValue>@(disable_connext_static_default)</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_DISABLE_CONNEXT_DYNAMIC</name>
          <description>By setting this to True, the build will disable the Connext dynamic rmw implementation.</description>
          <defaultValue>@(disable_connext_dynamic_default)</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_USE_OPENSPLICE</name>
          <description>By setting this to True, the build will attempt to use PrismTech&apos;s OpenSplice. On Linux and OS X OpenSplice is always being used despite the setting of this checkbox.</description>
          <defaultValue>@(use_opensplice_default)</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.BooleanParameterDefinition>
          <name>CI_ISOLATED</name>
          <description>By setting this to True, the build will use the --isolated option.</description>
          <defaultValue>true</defaultValue>
        </hudson.model.BooleanParameterDefinition>
        <hudson.model.StringParameterDefinition>
          <name>CI_AMENT_ARGS</name>
          <description>Additional arguments passed to ament.</description>
          <defaultValue>@(ament_args_default)</defaultValue>
        </hudson.model.StringParameterDefinition>
      </parameterDefinitions>
    </hudson.model.ParametersDefinitionProperty>
