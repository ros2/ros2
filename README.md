# LXML Debug builds for Windows

Needed for Windows "Debug" configuration.

Build instructions

Checkout lxml

git clone https://github.com/lxml/lxml
cd lxml
git checkout lxml-4.5.1
python_d setup.py build --debug --static-deps
# Without --skip-build the bdist_wheel command will rebuild in Release configuration.
python_d setup.py bdist_wheel --skip-build

Upload the resulting wheel in `dist\`. 
