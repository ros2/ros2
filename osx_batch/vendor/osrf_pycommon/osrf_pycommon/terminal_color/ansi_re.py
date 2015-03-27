# Copyright 2014 Open Source Robotics Foundation, Inc.
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

"""Provides regular expresion functions for matching ansi escape sequences."""

import re

_ansi_re = re.compile(r'\033\[\d{1,2}[m]')
_ansi_re_group = re.compile(r'(\033\[\d{1,2}[m])')


def split_by_ansi_escape_sequence(string, include_delimeters=False):
    """
    Splits a string into a list using any ansi escape sequence as a delimeter.

    :param string: string to be split
    :type string: str
    :param include_delimeters: If True include matched escape sequences in
        the list (default: False)
    :type include_delimeters: bool
    :returns: list of strings, split from original string by escape sequences
    :rtype: list
    """
    global _ansi_re, _ansi_re_group
    if include_delimeters:
        return _ansi_re_group.split(string)
    return _ansi_re.split(string)


def remove_ansi_escape_senquences(string):
    """
    Removes any ansi escape sequences found in the given string and returns it.
    """
    global _ansi_re
    return _ansi_re.sub('', string)
