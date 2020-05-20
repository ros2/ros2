# Numpy Debug builds for Windows

Need for Windows "Debug" configuration.

## Build instructions


Install cython in debug configuration for building numpy.
```
git clone https://github.com/cython/cython
cd cython
git checkout 0.29.18
python_d setup.py build --debug
python_d setup.py bdist_wheel --skip-build
python_d -mpip install dist\cython*.whl.
```

```
git clone https://github.com/numpy/numpy
cd numpy
git checkout v1.18.4
python_d setup.py build --debug
python_d setup.py bdist_wheel --skip-build
```
