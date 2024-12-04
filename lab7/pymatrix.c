/*

// check if array
// check if real

int PyArray_IS_C_CONTIGUOUS(PyArrayObject* arr); // c-style
int PyArray_IS_F_CONTIGUOUS(PyArrayObject* arr); // c-fortran

int PyArray_NDIM(PyArrayObject* arr); // 2
npy_intp* PyArray_SHAPE(PyArrayObject* arr); // n, m
npy_intp* PyArray_STRIDES(PyArrayObject* arr); // not relevant for us

*/

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include <numpy/ndarraytypes.h>
#include <numpy/arrayscalars.h>
#include <numpy/ufuncobject.h>

#include <stdio.h>

void mmc(const double* A, const double* B, const int n, const int p, const int m, double* out)
{
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < m; col++) {
            out[row * m + col] = 0;
            for (size_t comdim = 0; comdim < p; comdim++) {
                out[row * m + col] += A[row * p + comdim] * B[comdim * m + col];
            }
        }
    }
}

static PyObject* mm(PyObject* self, PyObject* args)
{
    Py_ssize_t nargs = PyTuple_Size(args);
    if (nargs < 0) return NULL;
    else if (nargs != 2)
        return PyErr_Format(PyExc_RuntimeError, "expected 2 argument");  // returns NULL

    PyObject* args0 = PyTuple_GetItem(args, 0);  // returns a borrowed reference, don't Py_DECREF (see below)
    if (!args0) return NULL;

    PyObject* args1 = PyTuple_GetItem(args, 1);  // returns a borrowed reference, don't Py_DECREF (see below)
    if (!args1) return NULL;

    if (!PyArray_Check(args0) || !PyArray_Check(args1))
        return PyErr_Format(PyExc_RuntimeError, "expected a numpy array");

    if (PyArray_TYPE((const PyArrayObject*)args0) != NPY_DOUBLE
        || !PyArray_IS_C_CONTIGUOUS((const PyArrayObject*)args0)
        || PyArray_TYPE((const PyArrayObject*)args1) != NPY_DOUBLE
        || !PyArray_IS_C_CONTIGUOUS((const PyArrayObject*)args1) ) {
        return PyErr_Format(PyExc_RuntimeError, "expected a contiguous numpy array of the dtype double");
    }

    const double* A = PyArray_DATA((const PyArrayObject*)args0);
    const double* B = PyArray_DATA((const PyArrayObject*)args1);

    npy_intp* na = PyArray_SHAPE((PyArrayObject*) args0);
    npy_intp* nb = PyArray_SHAPE((PyArrayObject*) args1);

    if (na[1] != nb[0])
        return PyErr_Format(PyExc_RuntimeError, "bad shapes");

    npy_intp* nc = malloc(2*sizeof(npy_intp)); 
    nc[0] = na[0];
    nc[1] = nb[1];

    PyObject* out = PyArray_SimpleNew(2, nc, NPY_DOUBLE);
    double* C = PyArray_DATA((const PyArrayObject*)out);

    mmc(A, B, na[0], na[1], nb[1], C);  // modifies C in place

    return out;
}


// a global variable - method list
static PyMethodDef aadsds_methods[] = {
    {"dot", mm, METH_VARARGS, "Matrix multiplication."},
    {NULL, NULL, 0, NULL}  // sentinel
};


// a global variable - module info
static struct PyModuleDef aadsds_module = {
    PyModuleDef_HEAD_INIT,
    "aadsds",   // module name
    NULL,        // module docstring
    -1,          // the module keeps state in global variables
    aadsds_methods
};


// PyInit_modulename returns a module
PyMODINIT_FUNC /* PyObject* etc. */ PyInit_aadsds()
{
    import_array();   //!!!!!!!!!!!!!!!!!!!!!

    return PyModule_Create(&aadsds_module);  // returns a module
}
