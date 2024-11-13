#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include <numpy/ndarraytypes.h>
#include <numpy/arrayscalars.h>
#include <numpy/ufuncobject.h>

// Your name:  ...TODO....
// Student ID: ...TODO....


static PyObject* todo_rename(PyObject* self, PyObject* args)
{
    // TODO....
    // have you written your name and ID above? (DELME)
    return NULL;
}


// a global variable - method list
static PyMethodDef mypydemo_methods[] = {
    {"todo_rename",  todo_rename, METH_VARARGS, "TODO: docstring..."},
    // have you written your name and ID above? (DELME)
    {NULL, NULL, 0, NULL}  // sentinel
};


// a global variable - module info
static struct PyModuleDef mypydemo_module = {
    PyModuleDef_HEAD_INIT,
    "aadsds",    // module name
    NULL,        // module docstring
    -1,          // the module keeps state in global variables
    mypydemo_methods
};


PyMODINIT_FUNC PyInit_mypydemo()
{
    PyObject* m = PyModule_Create(&mypydemo_module);
    if (!m) return NULL;

    import_array();

    return m;
}
