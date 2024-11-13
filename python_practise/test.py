import numpy as np
from cutils import py_equalv

a = np.arange(10).astype(float)
b = np.arange(10).astype(float)

print(py_equalv(a, b, 1e-2))

b[1] = 1.2

print(py_equalv(a, b, 1e-2))

b[1] = 1.002

print(py_equalv(a, b, 1e-2))

b[1] = 2

print(py_equalv(a, b, 1e-2))
