#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include <numpy/ndarraytypes.h>
#include <numpy/arrayscalars.h>
#include <numpy/ufuncobject.h>

double mysquare(double x)
{
    return x*x;
}


static PyObject* mypydemo_square(PyObject* self, PyObject* args)
{
    double x;
    if (!PyArg_ParseTuple(args, "d", &x))
        return NULL;

    double s = mysquare(x);

    return PyFloat_FromDouble(s);
}


void mysquarev(double* y, const double* x, const size_t n)
{
    for (size_t i=0; i<n; ++i)
        y[i] = x[i]*x[i];
}

static PyObject* mypydemo_squarev(PyObject* self, PyObject* args)
{
    Py_ssize_t nargs = PyTuple_Size(args);
    if (nargs < 0) return NULL;
    else if (nargs != 1)
        return PyErr_Format(PyExc_RuntimeError, "expected 1 argument");  // returns NULL

    PyObject* args0 = PyTuple_GetItem(args, 0);  // returns a borrowed reference, don't Py_DECREF (see below)
    if (!args0) return NULL;

    if (!PyArray_Check(args0))
        return PyErr_Format(PyExc_RuntimeError, "expected a numpy array");

    // option 1: ensure dtype double contiguous array (preferred)
    if (PyArray_TYPE((const PyArrayObject*)args0) != NPY_DOUBLE
        || !PyArray_IS_C_CONTIGUOUS((const PyArrayObject*)args0)) {
        return PyErr_Format(PyExc_RuntimeError, "expected a contiguous numpy array of the dtype double");
    }

    // option 2: convert to double-typed contiguous if needed
    // but the user won't know a conversion occurred...
    // args0 = PyArray_FromAny(args0, PyArray_DescrFromType(NPY_DOUBLE),
    //    1, 1, NPY_ARRAY_C_CONTIGUOUS, NULL);

    const double* x = PyArray_DATA((const PyArrayObject*)args0);
    Py_ssize_t n = PyArray_SIZE((const PyArrayObject*)args0);

    PyObject* retval = PyArray_SimpleNew(1, &n, NPY_DOUBLE);
    double* y = PyArray_DATA((const PyArrayObject*)retval);

    mysquarev(y, x, n);  // modifies y in place

    //Py_DECREF(args0);  // if using PyArray_FromAny

    return retval;
}


// a global variable - method list
static PyMethodDef mypydemo_methods[] = {
    {"square",  mypydemo_square, METH_VARARGS, "Square a given value."},
    {"squarev",  mypydemo_squarev, METH_VARARGS, "Square a given vector."},
    {NULL, NULL, 0, NULL}  // sentinel
};


// a global variable - module info
static struct PyModuleDef mypydemo_module = {
    PyModuleDef_HEAD_INIT,
    "mypydemo",  // module name
    NULL,        // module docstring
    -1,          // the module keeps state in global variables
    mypydemo_methods
};


// PyInit_modulename returns a module
PyMODINIT_FUNC /* PyObject* etc. */ PyInit_mypydemo()
{
    import_array();   //!!!!!!!!!!!!!!!!!!!!!

    return PyModule_Create(&mypydemo_module);  // returns a module
}