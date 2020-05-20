# typed_ast for Windows Debug

The `typed_ast` debug wheel was built with the following instructions:

Clone typed_ast and checkout 1.4.1 with a bugfix commit from https://github.com/python/typed_ast/pull/131

        git clone https://github.com/python/typed_ast.git
        cd typed_ast 
        git checkout cccbae430e8d8c45a554211fdadfa45eac6687cc 

Build the wheel:

        python_d setup.py build --debug
        python_d setup.py bdist_wheel --skip-build

Upload the resulting wheel in `dist\`.
