``osrf_pycommon``
=================

``osrf_pycommon`` is a python package which contains commonly used Python boilerplate code and patterns.
Things like ansi terminal coloring, capturing colored output from programs using subprocess, or even a simple logging system which provides some nice functionality over the built-in Python logging system.

The functionality provided here should be generic enough to be reused in arbitrary scenarios and should avoid bringing in dependencies which are not part of the standard Python library.
Where possible Windows and Linux/OS X should be supported, and where it cannot it should be gracefully degrading.
Code should be pure Python as well as Python 2 and Python 3 bilingual.

Contents:

.. toctree::
    :maxdepth: 2

    cli_utils
    process_utils
    terminal_color
    terminal_utils

Installing from Source
----------------------

Given that you have a copy of the source code, you can install ``osrf_pycommon`` like this:

.. code-block:: bash

    $ python setup.py install

.. note::

    If you are installing to a system Python you may need to use ``sudo``.

If you do not want to install ``osrf_pycommon`` into your system Python, or you don't have access to ``sudo``, then you can use a `virtualenv <https://virtualenv.pypa.io/>`_.

Hacking
-------

Because ``osrf_pycommon`` uses `setuptools <http://pythonhosted.org/setuptools/>`_ you can (and should) use the `develop <http://pythonhosted.org/setuptools/setuptools.html#development-mode>`_ feature:

.. code-block:: bash

    $ python setup.py develop

.. note::

    If you are developing against the system Python, you may need ``sudo``.

This will "install" ``osrf_pycommon`` to your Python path, but rather than copying the source files, it will instead place a marker file in the ``PYTHONPATH`` redirecting Python to your source directory.
This allows you to use it as if it were installed but where changes to the source code take immediate affect.

When you are done with develop mode you can (and should) undo it like this:

.. code-block:: bash

    $ python setup.py develop -u

.. note::

    If you are developing against the system Python, you may need ``sudo``.

That will "uninstall" the hooks into the ``PYTHONPATH`` which point to your source directory, but you should be wary that sometimes console scripts do not get removed from the bin folder.

Testing
-------

In order to run the tests you will need to install `nosetests <https://nose.readthedocs.org/>`_, `flake8 <https://flake8.readthedocs.org/>`_, and `Mock <http://www.voidspace.org.uk/python/mock/>`_.

Once you have installed those, then run ``nosetest`` in the root of the ``osrf_pycommon`` source directory:

.. code-block:: bash

    $ nosetests

Building the Documentation
--------------------------

In order to build the docs you will need to first install `Sphinx <http://sphinx-doc.org/>`_.

You can build the documentation by invoking the Sphinx provided make target in the ``docs`` folder:

.. code-block:: bash

    $ # In the docs folder
    $ make html
    $ open _build/html/index.html

Sometimes Sphinx does not pickup on changes to modules in packages which utilize the ``__all__`` mechanism, so on repeat builds you may need to clean the docs first:

.. code-block:: bash

    $ # In the docs folder
    $ make clean
    $ make html
    $ open _build/html/index.html
