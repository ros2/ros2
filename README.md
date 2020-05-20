# Numpy Debug builds for Windows

Need for Windows "Debug" configuration.

## Build instructions


Install cython in debug configuration for building numpy.
This wheel does not need to be uploaded as it is not a runtime dependency.

```
python_d -m pip wheel --global-option build --global-option --debug cython
python_d -m pip install Cython*.whl
```

```
git clone https://github.com/numpy/numpy
cd numpy
git checkout v1.18.4
python_d setup.py build --debug
# Workaround for https://github.com/numpy/numpy/issues/16005
# Places build_src files in build directory so they are picked up by the bdist_wheel command.
python_d build_src -d build\lib.win-amd64-3.8-pydebug
python_d setup.py bdist_wheel --skip-build
```

Upload the resulting wheel in `dist\`.
