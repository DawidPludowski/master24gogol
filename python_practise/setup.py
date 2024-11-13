import os

import numpy as np
from setuptools import Extension, setup

module = Extension(
    "cutils",
    sources=["cutils.c"],
    include_dirs=[np.get_include()],
    define_macros=[("NPY_NO_DEPRECATED_API", "NPY_1_7_API_VERSION")],
)

setup(name="cutils", ext_modules=[module])


# python3 setup.py build
# python3 setup.py install
