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

import os

from ..batch_job import BatchJob
from ..util import log
from ..util import warn


class LinuxBatchJob(BatchJob):
    def __init__(self, args):
        self.args = args
        # The BatchJob constructor will set self.run and self.python
        BatchJob.__init__(self)

    def pre(self):
        os.environ['ROS_DOMAIN_ID'] = '108'

    def show_env(self):
        # Show the env
        self.run(['export'], shell=True)
        # Show what pip has
        self.run(['"%s"' % self.python, '-m', 'pip', 'freeze'], shell=True)

    def setup_env(self):
        connext_env_file = None
        # this block is only relevant if it is not using the custom Debian package
        # but the installed official packages
        if self.args.connext:
            # Try to find the connext env file and source it
            connext_env_file = os.path.join(
                os.path.expanduser('~'), 'rti_connext_dds-5.2.0', 'resource', 'scripts',
                'rtisetenv_x64Linux3.xgcc4.6.3.bash')
            if not os.path.exists(connext_env_file):
                warn("Asked to use Connext but the RTI env was not found at '{0}'".format(
                    connext_env_file))
                connext_env_file = None
        # There is nothing extra to be done for OpenSplice

        ros1_setup_file = None
        if self.args.ros1_path:
            # Try to find the setup file and source it
            ros1_setup_file = os.path.join(self.args.ros1_path, 'setup.sh')
            if not os.path.exists(ros1_setup_file):
                warn("Asked to use ROS 1 but the setup file was not found at '{0}'".format(
                    ros1_setup_file))
                ros1_setup_file = None

        current_run = self.run

        def with_vendors(cmd, **kwargs):
            # Ensure shell is on since we're using &&
            kwargs['shell'] = True
            # Extend the environment if needed.
            env = kwargs.setdefault('env', dict(os.environ))
            if self.args.disable_connext_static:
                env["CONNEXT_STATIC_DISABLE"] = '1'
            if self.args.disable_connext_dynamic:
                env["CONNEXT_DYNAMIC_DISABLE"] = '1'
            # If the connext file is there, source it.
            if connext_env_file is not None:
                cmd = ['.', '"%s"' % connext_env_file, '&&'] + cmd
                log('(RTI)')
            if ros1_setup_file:
                cmd = ['.', '"%s"' % ros1_setup_file, '&&'] + cmd
                log('(ROS1)')
            # Pass along to the original runner
            return current_run(cmd, **kwargs)

        # Push the custom runner
        self.push_run(with_vendors)
