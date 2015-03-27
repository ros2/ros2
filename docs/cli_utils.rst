The ``cli_utils`` Module
========================

This module provides functions and patterns for creating Command Line Interface (CLI) tools.

Common CLI Functions
--------------------

.. automodule:: osrf_pycommon.cli_utils.common
    :members:

The Verb Pattern
----------------

The verb pattern is a pattern where a single command aggregates multiple related commands by taking a required positional argument which is the "verb" for the action you want to perform.
For example, ``catkin build`` is an example of a ``command`` and ``verb`` pair, where ``catkin`` is the command and ``build`` is the verb.
In this example, the ``catkin`` command groups "actions" which are related to catkin together using verbs like ``build`` which will build a workspace of catkin packages.

Command Boilerplate
^^^^^^^^^^^^^^^^^^^

This is an example boilerplate of a command which will use verbs:

.. code-block:: python

    from __future__ import print_function

    import argparse
    import sys

    from osrf_pycommon.cli_utils.verb_pattern import create_subparsers
    from osrf_pycommon.cli_utils.verb_pattern import list_verbs
    from osrf_pycommon.cli_utils.verb_pattern import split_arguments_by_verb

    COMMAND_NAME = '<INSERT COMMAND NAME HERE>'

    VERBS_ENTRY_POINT = '{0}.verbs'.format(COMMAND_NAME)


    def main(sysargs=None):
        # Assign sysargs if not set
        sysargs = sys.argv[1:] if sysargs is None else sysargs

        # Create a top level parser
        parser = argparse.ArgumentParser(
            description="{0} command".format(COMMAND_NAME)
        )

        # Generate a list of verbs available
        verbs = list_verbs(VERBS_ENTRY_POINT)

        # Create the subparsers for each verb and collect the arg preprocessors
        argument_preprocessors, verb_subparsers = create_subparsers(
            parser,
            COMMAND_NAME,
            verbs,
            VERBS_ENTRY_POINT,
            sysargs,
        )

        # Determine the verb, splitting arguments into pre and post verb
        verb, pre_verb_args, post_verb_args = split_arguments_by_verb(sysargs)

        # Short circuit -h and --help
        if '-h' in pre_verb_args or '--help' in pre_verb_args:
            parser.print_help()
            sys.exit(0)

        # Error on no verb provided
        if verb is None:
            print(parser.format_usage())
            sys.exit("Error: No verb provided.")
        # Error on unknown verb provided
        if verb not in verbs:
            print(parser.format_usage())
            sys.exit("Error: Unknown verb '{0}' provided.".format(verb))

        # Short circuit -h and --help for verbs
        if '-h' in post_verb_args or '--help' in post_verb_args:
            verb_subparsers[verb].print_help()
            sys.exit(0)

        # First allow the verb's argument preprocessor to strip any args
        # and return any "extra" information it wants as a dict
        processed_post_verb_args, extras = \
            argument_preprocessors[verb](post_verb_args)
        # Then allow argparse to process the left over post-verb arguments along
        # with the pre-verb arguments and the verb itself
        args = parser.parse_args(pre_verb_args + [verb] + processed_post_verb_args)
        # Extend the argparse result with the extras from the preprocessor
        for key, value in extras.items():
            setattr(args, key, value)

        # Finally call the subparser's main function with the processed args
        # and the extras which the preprocessor may have returned
        sys.exit(args.main(args) or 0)

This function is mostly boilerplate in that it will likely not change much between commands of different types, but it would also be less transparent to have this function created for you.
If you are using this boilerplate to implement your command, then you should be careful to update ``COMMAND_NAME`` to reflect your command's name.

This line defines the ``entry_point`` group for your command's verbs:

.. code-block:: python

    VERBS_ENTRY_POINT = '{0}.verbs'.format(COMMAND_NAME)

In the case that your command is called ``foo`` then this would become ``foo.verbs``.
This name is important because it is how verbs for this command can be provided by your Python package or others.
For example, each verb for your command ``foo`` will need entry in the ``setup.py`` of its containing package, like this:

.. code-block:: python

    setup(
        ...
        entry_points={
            ...
            'foo.verbs': [
                'bar = foo.verbs.bar:entry_point_data',
            ],
        }
    )

You can see here that you are defining ``bar`` to be a an entry_point of type ``foo.verbs`` which in turn points to a module and reference ``foo.verbs.bar`` and ``entry_point_data``.
At run time this verb pattern will let your command lookup all things defined as ``foo.verbs`` and load up the reference to which they point.

Adding Verbs
^^^^^^^^^^^^

In order to add a verb to your command, a few things must happen.

First you must have an entry in the ``setup.py`` as described above.
This allows the command to find the ``entry_point`` for your verb at run time.
The ``entry_point`` for these verbs should point to a dictionary which describes the verb being added.

This is an example of an ``entry_point_data`` dictionary for a verb:

.. code-block:: python

    entry_point_data = dict(
        verb='build',
        description='Builds a workspace of packages',
        # Called for execution, given parsed arguments object
        main=main,
        # Called first to setup argparse, given argparse parser
        prepare_arguments=prepare_arguments,
        # Called after prepare_arguments, but before argparse.parse_args
        argument_preprocessor=argument_preprocessor,
    )

As you can see this dictionary describes the verb and gives references to functions which allow the command to describe the verb, hook into argparse parameter creation for the verb, and to execute the verb.
The ``verb``, ``description``, ``main``, and ``prepare_arguments`` keys of the dictionary are required, but the ``argument_preprocessor`` key is optional.

- ``verb``: This is the name of the verb, and is how the command knows which verb implementation to match to a verb on the command line.
- ``description``: This is used by the argument parsing to describe the verb in ``--help``.
- ``prepare_arguments``: This function gets called to allow the verb to setup it's own argparse options. This function should always take one parameter which is the :py:class:`argparse.ArgumentParser` for this verb, to which arguments can be added. It can optionally take a second parameter which are the current command line arguments. This is not always needed, but can be useful in some cases. This function should always return the parser.
- ``argument_preprocessor``: This function is optional, but allows your verb an opportunity to process the raw arguments before they are passed to argparse's ``parse_args`` function. This can be useful when argparse is not capable of processing the options correctly.
- ``main``: This is the implementation of the verb, it gets called last and is passed the parsed arguments. The return type of this function is used for ``sys.exit``, a return type of ``None`` is interpreted as ``0``.

Here is an invented example of ``main``, ``prepare_arguments``, and ``argument_preprocessor``:

.. code-block:: python

    def prepare_arguments(parser):
        parser.add_argument('--some-argument', action='store_true', default=False)
        return parser

    def argument_preprocessor(args):
        extras = {}

        if '-strange-argument' in args:
            args.remove('-strange-argument')
            extras['strange_argument'] = True

        return args, extras

    def main(options):
        print('--some-argument:', options.some_argument)
        print('-strange-argument:', options.strange_argument)
        if options.strange_argument:
            return 1
        return 0

The above example is simply to illustrate the signature of these functions and how they might be used.

Verb Pattern API
^^^^^^^^^^^^^^^^

.. automodule:: osrf_pycommon.cli_utils.verb_pattern
    :members:
