#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#ifndef PYBGame_H
#define PYBGame_H


typedef struct {
    PyObject_HEAD
} pyBGame;
    
    
static PyObject * pyBGame_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBGame *self;
    self = (pyBGame *)type->tp_alloc(type, 0);   
    return (PyObject *)self;
}

static PyObject * pyBGame_begin(pyBGame * self)
{
    Py_RETURN_NONE;
}

static PyObject * pyBGame_update(pyBGame * self)
{
    Py_RETURN_NONE;
}

static PyObject * pyBGame_end(pyBGame * self)
{
    Py_RETURN_NONE;
}
    
static PyMethodDef pyBGame_methods[] = {
    {   "onBegin"   , (PyCFunction)pyBGame_begin  , METH_NOARGS  , ""  },
    {   "onUpdate"    , (PyCFunction)pyBGame_update , METH_NOARGS  , ""  },
    {   "onEnd"     , (PyCFunction)pyBGame_end    , METH_NOARGS  , ""  },
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyBGame_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BGame",
    sizeof(pyBGame),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT |  Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBGame_methods,           /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBGame_new,             /* tp_new */

};


#endif /* PYBGame_H */

