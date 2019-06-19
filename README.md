# cryptography Debug builds for Windows

## Building a Debug Wheel

Prerequisites:

1. [OpenSSL](https://slproweb.com/products/Win32OpenSSL.html)

In order to build a debug wheel, we first need to build a debug wheel for its dependency [cffi](https://cffi.readthedocs.io/en/latest/).

1. Install pip dependencies:

        pip install -U wheel setuptools six asn1crypto ipaddress enum34

1. Download and extract `cffi` source (v1.12.3):

        https://bitbucket.org/cffi/cffi/get/v1.12.3.zip

1. Change to the root of the `cffi` repo.

1. Build a debug wheel:

        python_d setup.py build --debug
        python_d setup.py bdist_wheel

1. Install the debug wheel:

        python_d -m pip install --force-reinstall dist\cffi-1.12.3-cp37-cp37dm-win_amd64.whl

Now we can build the debug wheel for `cryptography`.

1. Set environment variables for OpenSSL (assuming default installation directory). [Reference](https://cryptography.io/en/latest/installation/#building-cryptography-on-windows):

        set LIB=C:\OpenSSL-Win64\lib;%LIB%
        set INCLUDE=C:\OpenSSL-Win64\include;%INCLUDE%
        # This last line is needed if using OpenSSL version < 1.1.0
        set CRYPTOGRAPHY_WINDOWS_LINK_LEGACY_OPENSSL=True

1. Get `cryptography` source:

        git clone https://github.com/pyca/cryptography.git
        cd cryptography
        git checkout 2.7

1. Build wheel:

    python_d setup.py build --debug
    # Skip rebuilding, otherwise it will rebuild in release (not debug)
    python_d setup.py bdist_wheel --skip-build

The wheel can be found at `dist\cryptography-2.7-cp37-cp37dm-win_amd64.whl`.
