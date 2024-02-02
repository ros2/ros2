# psutil Debug builds for Windows

Needed for Windows "Debug" configuration.

Build instructions

```
git clone https://github.com/giampaolo/psutil
cd psutil
git checkout release-5.9.5
# Edit setup.py, comment out py_limited_api detection and set py_limited_api = {}
python_d setup.py build --debug
python_d setup.py bdist_wheel --skip-build
```

Upload the resulting wheel in `dist\`.
