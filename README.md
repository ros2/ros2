# typed_ast for Windows Debug

The `typed_ast` debug wheel was built with the following instructions:

        git clone https://github.com/python/typed_ast.git
        cd typed_ast
        git checkout 1.4.0

Then, modify `typed_ast\ast3\Parser\parser.c` and `typed_ast\ast27\Parser\parser.c` to remove the use of `Py_DebugFlag`:

```diff
-#ifdef Py_DEBUG
-extern int Py_DebugFlag;
-#define D(x) if (!Py_DebugFlag); else x
-#else
+// #ifdef Py_DEBUG
+// extern int Py_DebugFlag;
+// #define D(x) if (!Py_DebugFlag); else x
+// #else
 #define D(x)
-#endif
+// #endif
```

This avoids a linker error (not sure how else to avoid it).

Finally, build the wheel:

        python_d setup.py build --debug
        python_d setup.py bdist_wheel --skip-build

Then the wheel is found at `dist/typed_ast-1.4.0-cp37-cp37dm-win_amd64.whl`.
