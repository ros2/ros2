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

"""API for implementing commands and verbs which used the verb pattern."""

import pkg_resources
import inspect


def call_prepare_arguments(func, parser, sysargs=None):
    """Call a prepare_arguments function with the correct number of parameters.

    The ``prepare_arguments`` function of a verb can either take one parameter,
    ``parser``, or two parameters ``parser`` and ``args``, where ``args`` are
    the current arguments being processed.

    :param func: Callable ``prepare_arguments`` function.
    :type func: Callabe
    :param parser: parser which is always passed to the function
    :type parser: :py:class:`argparse.ArgumentParser`
    :param sysargs: arguments to optionally pass to the function, if needed
    :type sysargs: list
    :returns: return value of function or the parser if the function
        returns None.
    :rtype: :py:class:`argparse.ArgumentParser`
    :raises: ValueError if a function with the wrong number of parameters
        is given
    """
    func_args = [parser]
    # If the provided function takes two arguments and args were given
    # also give the args to the function
    arguments = inspect.getargspec(func)[0]
    if arguments[0] == 'self':
        del arguments[0]
    if len(arguments) not in [1, 2]:
        raise ValueError("Given function '{0}' must have one or two "
                         "parameters (excluding self), but got '{1}' "
                         "parameters: '{2}'"
                         .format(func.__name__,
                                 len(arguments),
                                 ', '.join(inspect.getargspec(func)[0])))
    if len(arguments) == 2:
        func_args.append(sysargs or [])
    return func(*func_args) or parser


def create_subparsers(parser, cmd_name, verbs, group, sysargs, title=None):
    """Creates argparse subparsers for each verb which can be discovered.

    Using the ``verbs`` parameter, the availble verbs are iterated through.
    For each verb a subparser is created for it using the ``parser`` parameter.
    The ``cmd_name`` is used to fill the title and description of the
    ``add_subparsers`` function call.
    The ``group`` parameter is used with each verb to load the verb's
    ``description``, ``prepare_arguments`` function, and the verb's
    ``argument_preprocessors`` if available.
    Each verb's ``prepare_arguments`` function is called, allowing them to
    add arguments.
    Finally a list of ``argument_preprocessors`` functions and verb subparsers
    are returned, one for each verb.

    :param parser: parser for this command
    :type parser: :py:class:`argparse.ArgumentParser`
    :param str cmd_name: name of the command to which the verbs are being added
    :param list verbs: list of verbs (by name as a string)
    :param str group: name of the ``entry_point`` group for the verbs
    :param list sysargs: list of system arguments
    :param str title: optional custom title for the command
    :returns: tuple of argument_preprocessors and verb subparsers
    :rtype: tuple
    """
    metavar = '[' + ' | '.join(verbs) + ']'
    subparser = parser.add_subparsers(
        title=title or '{0} command'.format(cmd_name),
        metavar=metavar,
        description='Call `{0} {1} -h` for help on a each verb.'.format(
            cmd_name, metavar),
        dest='verb'
    )

    argument_preprocessors = {}
    verb_subparsers = {}

    for verb in verbs:
        desc = load_verb_description(verb, group)
        cmd_parser = subparser.add_parser(
            desc['verb'], description=desc['description'])
        cmd_parser = call_prepare_arguments(
            desc['prepare_arguments'],
            cmd_parser,
            sysargs,
        )

        cmd_parser.set_defaults(main=desc['main'])

        if 'argument_preprocessor' in desc:
            argument_preprocessors[verb] = desc['argument_preprocessor']
        else:
            argument_preprocessors[verb] = default_argument_preprocessor
        verb_subparsers[verb] = cmd_parser

    return argument_preprocessors, verb_subparsers


def default_argument_preprocessor(args):
    """Return unmodifed args and an empty dict for extras"""
    extras = {}
    return args, extras


def list_verbs(group):
    """List verbs available for a given ``entry_point`` group.

    :param str group: ``entry_point`` group name for the verbs to list
    :returns: list of verb names for the given ``entry_point`` group
    :rtype: list of str
    """
    verbs = []
    for entry_point in pkg_resources.iter_entry_points(group=group):
        verbs.append(entry_point.name)
    return verbs


def load_verb_description(verb_name, group):
    """Load description of a verb in a given group by name.

    :param str verb_name: name of the verb to load, as a string
    :param str group: ``entry_point`` group name which the verb is in
    :returns: verb description
    :rtype: dict
    """
    for entry_point in pkg_resources.iter_entry_points(group=group):
        if entry_point.name == verb_name:
            return entry_point.load()


def split_arguments_by_verb(arguments):
    """Split arguments by verb.

    Given a list of arguments (list of strings), the verb, the pre verb
    arguments, and the post verb arugments are returned.

    For example:

    .. code-block:: python

        >>> args = ['--command-arg1', 'verb', '--verb-arg1', '--verb-arg2']
        >>> split_arguments_by_verb(args)
        ('verb', ['--command-arg1'], ['--verb-arg1', '--verb-arg2'])

    :param list arguments: list of system arguments
    :returns: the verb (str), pre verb args (list), and post verb args (list)
    :rtype: tuple
    """
    verb = None
    pre_verb_args = []
    post_verb_args = []
    for index, arg in enumerate(arguments):
        # If the arg does not start with a `-` then it is a positional argument
        # The first positional argument must be the verb
        if not arg.startswith('-'):
            verb = arg
            post_verb_args = arguments[index + 1:]
            break
        # Otherwise it is a pre-verb option
        pre_verb_args.append(arg)
    return verb, pre_verb_args, post_verb_args
