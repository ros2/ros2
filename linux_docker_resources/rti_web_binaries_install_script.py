# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse

import pexpect


def install_connext(installer_path, install_directory):
    child = pexpect.spawn(installer_path + ' --mode text', encoding='utf8')

    try:
        keep_agreeing = True
        while(keep_agreeing):
            result_index = child.expect([
                'Installation Directory.*?:',
                'Press \[Enter\] to continue:',
                'Do you accept this license\? \[y/n\]: '])
            if result_index == 0:
                keep_agreeing = False
            else:
                child.sendline('y')

        child.sendline(install_directory)
        child.expect_exact('Do you want to continue? [Y/n]:')
        child.sendline('y')
        result_index = child.expect_exact([
            'Create an RTI Launcher shortcut on the Desktop [y/N]: ', pexpect.EOF], timeout=120)
        if result_index == 0:
            child.sendline('n')
            child.expect(pexpect.EOF)

    except (pexpect.TIMEOUT, pexpect.EOF):
        raise RuntimeError(
            'Unexpected output while installing Connext. Last 100 chars received from installer: ' +
            '\n' + child.before)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('installer_path')
    parser.add_argument('install_directory')

    args = parser.parse_args()
    install_connext(args.installer_path, args.install_directory)
