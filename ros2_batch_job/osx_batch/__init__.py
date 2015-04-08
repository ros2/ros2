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


class OSXBatchJob(BatchJob):
    def __init__(self, args):
        self.args = args
        # The BatchJob constructor will set self.run and self.python
        BatchJob.__init__(self)

    def pre(self):
        # Prepend the PATH with `/usr/local/bin` for global Homebrew binaries.
        os.environ['PATH'] = "/usr/local/bin" + os.pathsep + os.environ.get('PATH', '')

    def show_env(self):
        # Show the env
        self.run(['export'], shell=True)
        # Show what brew has
        self.run(['brew', 'list'])
        # Show what pip has
        self.run([self.python, '-m', 'pip', 'freeze'])

    def setup_env(self):
        connext_env_file = None
        if self.args.connext:
            # Try to find the connext env file and source it
            connext_env_file = os.path.join(os.path.expanduser('~'), 'RTI', 'rti_set_bash_5.1.0')
            if not os.path.exists(connext_env_file):
                warn("Asked to use Connext but the RTI env was not found at '{0}'".format(
                    connext_env_file))
                connext_env_file = None
        # There is nothing extra to be done for OpenSplice
        current_run = self.run

        def with_vendors(cmd, **kwargs):
            # Ensure shell is on since we're using &&
            kwargs['shell'] = True
            # If the connext file is there, source it.
            if connext_env_file is not None:
                cmd = ['source', '"%s"' % connext_env_file, '&&'] + cmd
                log('(RTI)')
            # Pass along to the original runner
            return current_run(cmd, **kwargs)

        # Push the custom runner
        self.push_run(with_vendors)
