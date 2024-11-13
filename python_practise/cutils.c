#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include <numpy/ndarraytypes.h>
#include <numpy/arrayscalars.h>
#include <numpy/ufuncobject.h>

#include <math.h>
#include <stdio.h>

// Your name:  ...TODO....
// Student ID: ...TODO....

void equalv(const double* x,
             const double* y,
             double* out, 
             const double prec,
             const size_t len) {

    for (int i = 0; i < len; i++) {
        out[i] = fabs(x[i] - y[i]) < prec ? 1.0 : 0.0;
    }
    printf("%f", prec);
}

void tilev(const double* x,
            double* out,
            const size_t len,
            const size_t times) {

    for (int i = 0; i < times; i++) {
        for (int j = 0; j < len; j++) {
            out[i*len + j] = x[j];
        }
    }

}

static PyObject* py_tilev(PyObject* self, PyObject* args)
{
    Py_ssize_t nargs = PyTuple_Size(args);
    if (nargs < 0) return NULL;
    else if (nargs != 2) 
        return PyErr_Format(PyExc_RuntimeError, "Exptected 2 arguments");

    PyObject* x_py = PyTuple_GetItem(args, 0);
    PyObject* times_py = PyTuple_GetItem(args, 1);

    if (!PyLong_Check(times_py)) {
        PyErr_SetString(PyExc_TypeError, "times should be int");
        return NULL;
    }

    int times = PyLong_AsLong(times_py);

    if (!PyArray_Check(x_py)) 
        return PyErr_Format(PyExc_RuntimeError, "x must be ndarray");

    PyArrayObject* x_arr = (PyArrayObject*) x_py;

    if (PyArray_TYPE(x_arr) != NPY_DOUBLE || !PyArray_IS_C_CONTIGUOUS(x_arr))
        return PyErr_Format(PyExc_RuntimeError, "blabla");

    double* x = PyArray_DATA(x_arr);

    Py_ssize_t n = PyArray_SIZE(x_arr);

    Py_ssize_t nn = n * times;

    PyObject* out = PyArray_SimpleNew(1, &nn, NPY_DOUBLE);
    double* z = PyArray_DATA((const PyArrayObject*) out);

    tilev(x, z, n, times);

    return out;
}

/*
 check args size -> PyTuple_Size(args);
 fetch args to objs -> PyTuple_GetItem(args, 0);
 check types:
    * scalars -> PyFloat_Check
    * np -> PyArray_Check(x_py), PyArray_TYPE() != NPY_DOUBLE, PyArray_IS_C_CONTIGUOUS
    * errors -> return PyErr_Format(PyExc_TypeError/runtimeError, "communicate")
cast to c:
    * scalars -> PyFloat_AsDouble
    * numpy -> PyArray_DATA(), PyArray_SIZE
run algorithm
return arr
*/


static PyObject* py_equalv(PyObject* self, PyObject* args)
{
    Py_ssize_t nargs = PyTuple_Size(args);
    if (nargs < 0) return NULL;
    else if (nargs != 3) 
        return PyErr_Format(PyExc_RuntimeError, "Expected 3 arguments");

    PyObject* x_py = PyTuple_GetItem(args, 0);
    PyObject* y_py = PyTuple_GetItem(args, 1);
    PyObject* prec_py = PyTuple_GetItem(args, 2);

    if (!PyFloat_Check(prec_py)) {
        PyErr_SetString(PyExc_TypeError, "A float is required");
        return NULL;
    }
    double prec = PyFloat_AsDouble(prec_py);

    if (!PyArray_Check(x_py) || !PyArray_Check(y_py))
        return PyErr_Format(PyExc_RuntimeError, "expected x and y to be numpy array");

    if (PyArray_TYPE((const PyArrayObject*)x_py) != NPY_DOUBLE
        || !PyArray_IS_C_CONTIGUOUS((const PyArrayObject*)x_py)) {
        return PyErr_Format(PyExc_RuntimeError, "expected x to be contiguous numpy array of the dtype double");
    }

    if (PyArray_TYPE((const PyArrayObject*)y_py) != NPY_DOUBLE
        || !PyArray_IS_C_CONTIGUOUS((const PyArrayObject*)y_py)) {
        return PyErr_Format(PyExc_RuntimeError, "expected x to be contiguous numpy array of the dtype double");
    }

    const double* x = PyArray_DATA((const PyArrayObject*) x_py);
    const double* y = PyArray_DATA((const PyArrayObject*) y_py);

    Py_ssize_t nx = PyArray_SIZE((const PyArrayObject*)x_py);
    Py_ssize_t ny = PyArray_SIZE((const PyArrayObject*)y_py);

    if (nx != ny) {
        return PyErr_Format(PyExc_RuntimeError, "x and y needs to be of the same size");
    }

    PyObject* out = PyArray_SimpleNew(1, &nx, NPY_DOUBLE);
    double* z = PyArray_DATA((const PyArrayObject*) out);

    equalv(x, y, z, prec, nx);

    return out;

}


// a global variable - method list
static PyMethodDef mypydemo_methods[] = {
    {"py_tilev", py_tilev, METH_VARARGS, "..."},
    {"py_equalv",  py_equalv, METH_VARARGS, "......"},
    {NULL, NULL, 0, NULL}  // sentinel
};


// a global variable - module info
static struct PyModuleDef cutils_module = {
    PyModuleDef_HEAD_INIT,
    "cutils",    // module name
    NULL,        // module docstring
    -1,          // the module keeps state in global variables
    mypydemo_methods
};


PyMODINIT_FUNC PyInit_cutils()
{
    PyObject* m = PyModule_Create(&cutils_module);
    if (!m) return NULL;

    import_array();

    return m;
}
