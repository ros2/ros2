# netifaces Debug builds for Windows

## Building a Debug Wheel

We can build the debug wheel for `netifaces`:

        python_d -m pip wheel --global-option build --global-option --debug netifaces

The wheel can be found at `netifaces-0.10.9-cp37-cp37dm-win_amd64.whl`.
