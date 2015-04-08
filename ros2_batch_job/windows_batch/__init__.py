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
import shutil

from ..batch_job import BatchJob
from ..util import info
from ..util import warn


class WindowsBatchJob(BatchJob):
    def __init__(self, args):
        self.args = args
        # The BatchJob constructor will set self.run and self.python
        BatchJob.__init__(self)

    def pre(self):
        pass

    def show_env(self):
        # Show the env
        self.run(['set'], shell=True)
        # Show what pip has
        self.run([self.python, '-m', 'pip', 'freeze'])

    def setup_env(self):
        # Try to find the connext env file and source it
        connext_env_file = None
        if self.args.connext:
            pf_x86 = os.environ.get('ProgramFiles(x86)', "C:\\Program Files (x86)\\")
            connext_env_file = os.path.join(pf_x86, 'RTI', 'rti_set_env_5.1.0.bat')
            if not os.path.exists(connext_env_file):
                warn("Asked to use Connext but the RTI env was not found at '{0}'".format(
                    connext_env_file))
                connext_env_file = None

        # Try to find the OpenSplice env file
        opensplice_env_file = os.path.join(
            os.path.abspath(os.sep), 'dev', 'opensplice', 'HDE', 'x86_64.win64')
        if not os.path.exists(opensplice_env_file):
            warn("Asked to use OpenSplice but the env file was not found at '{0}'".format(
                opensplice_env_file))
            opensplice_env_file = None

        # Generate the env file
        if os.path.exists('env.bat'):
            shutil.rmtree('env.bat')
        with open('env.bat', 'w') as f:
            f.write("@echo off" + os.linesep)
            f.write(
                'call '
                '"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat" '
                'amd64' + os.linesep)
            if connext_env_file is not None:
                f.write('call "%s"%s' % (connext_env_file, os.linesep))
            if opensplice_env_file is not None:
                f.write('call "%s"%s' % (opensplice_env_file, os.linesep))
            f.write("%*" + os.linesep)
            f.write("if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%" + os.linesep)

        # Show the result
        info("Contents of 'env.bat':")
        with open('env.bat', 'r') as f:
            print(f.read())
        current_run = self.run

        def with_vendors(cmd, **kwargs):
            # Ensure shell is on since we're using &&
            kwargs['shell'] = True
            # Use the env file to call the commands
            cmd = ['env.bat'] + cmd
            # Pass along to the original runner
            return current_run(cmd, **kwargs)

        # Push the custom runner
        self.push_run(with_vendors)
