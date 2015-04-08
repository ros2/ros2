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

"""Commonly used, CLI related functions."""

import re


def extract_jobs_flags(arguments):
    """Extracts make job flags from a list of other make flags, i.e. -j8 -l8

    The input arguments are given as a string separated by whitespace.
    Make job flags are matched and removed from the arguments, and the Make
    job flags and what is left over from the input arguments are returned.

    If no job flags are encountered, then an empty string is returned as the
    first element of the returned tuple.

    Examples:

    .. code-block:: python

        >> extract_jobs_flags('-j8 -l8')
        ('-j8 -l8', '')
        >> extract_jobs_flags('-j8 ')
        ('-j8', ' ')
        >> extract_jobs_flags('target -j8 -l8 --some-option')
        ('-j8 -l8', 'target --some-option')
        >> extract_jobs_flags('target --some-option')
        ('', 'target --some-option')

    :param str arguments: string of space separated arguments which may or
        may not contain make job flags
    :returns: tuple of make jobs flags as a space separated string and
        leftover arguments as a space separated string
    :rtype: tuple
    """
    regex = (
        r'(?:^|\s)(-?(?:j|l)(?:\s*[0-9]+|\s|$))'
        r'|'
        r'(?:^|\s)((?:--)?(?:jobs|load-average)(?:(?:=|\s+)[0-9]+|(?:\s|$)))'
    )
    matches = []
    leftover = ''
    last_match_end = 0
    for match in re.finditer(regex, arguments) or []:
        matches.append(match.groups()[0] or match.groups()[1])
        leftover += arguments[last_match_end:match.start()]
        last_match_end = match.end()
    leftover += arguments[last_match_end:]
    return ' '.join([m.strip() for m in matches]), leftover


def extract_argument_group(args, delimiting_option):
    """Extract a group of arguments from a list of arguments using a delimiter.

    Here is an example:

    .. code-block:: python

        >>> extract_argument_group(['foo', '--args', 'bar', '--baz'], '--args')
        (['foo'], ['bar', '--baz'])

    The group can always be ended using the double hyphen ``--``.
    In order to pass a double hyphen as arguments, use three hyphens ``---``.
    Any set of hyphens encountered after the delimiter, and up to ``--``, which
    have three or more hyphens and are isolated, will be captured and reduced
    by one hyphen.

    For example:

    .. code-block:: python

        >> extract_argument_group(['foo',
                                   '--args', 'bar', '--baz', '---', '--',
                                   '--foo-option'], '--args')
        (['foo', '--foo-option'], ['bar', '--baz', '--'])

    In the result the ``--`` comes from the ``---`` in the input.
    The ``--args`` and the corresponding ``--`` are removed entirely.

    The delimiter and ``--`` terminator combination can also happen multiple
    times, in which case the bodies of arguments are combined and returned in
    the order they appeared.

    For example:

    .. code-block:: python

        >> extract_argument_group(['foo',
                                   '--args', 'ping', '--',
                                   'bar',
                                   '--args', 'pong', '--',
                                   'baz',
                                   '--args', '--'], '--args')
        (['foo', 'bar', 'baz'], ['ping', 'pong'])

    Note: ``--`` cannot be used as the ``delimiting_option``.

    :param list args: list of strings which are ordered arguments.
    :param str delimiting_option: option which denotes where to split the args.
    :returns: tuple of arguments before and after the delimiter.
    :rtype: tuple
    :raises: ValueError if the delimiting_option is ``--``.
    """
    if delimiting_option == '--':
        raise ValueError("Cannot use '--' as the delimiter")
    if delimiting_option not in args:
        return args, []
    trimmed_args = args
    extracted_args = []
    # Loop through all arguments extracting groups of arguments
    while True:
        try:
            next_delimeter = trimmed_args.index(delimiting_option)
        except ValueError:
            # No delimeter's left in the arguments, stop looking
            break
        # Capture and remove args after the delimeter
        tail = trimmed_args[next_delimeter + 1:]
        trimmed_args = trimmed_args[:next_delimeter]
        # Look for a terminator, '--'
        next_terminator = None
        try:
            next_terminator = tail.index('--')
        except ValueError:
            pass
        if next_terminator is None:
            # No terminator, put all args in extracted_args and stop looking
            extracted_args.extend(tail)
            break
        else:
            # Terminator foud, put args up, but not including terminator
            # in extracted_args
            extracted_args.extend(tail[:next_terminator])
            # And put arguments after the terminator back in trimmed_args
            # then continue looking for additional delimeters
            trimmed_args.extend(tail[next_terminator + 1:])
    # Iterate through extracted args and shorted tokens with 3+ -'s only
    for i, token in enumerate(extracted_args):
        # '--' should have been removed from extracted_args in the above loop
        assert token != '--', "this shouldn't happen"
        # Skip single hyphens
        if token == '-':
            continue
        # Check for non-hyphen characters
        if [c for c in token if c != '-']:
            # contains something other than -, continue
            continue
        # Must be only hyphens with more than two, Shorted by one -
        extracted_args[i] = token[1:]
    return trimmed_args, extracted_args
