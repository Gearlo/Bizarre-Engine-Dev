
#ifndef _pyBFontRef
#define _pyBFontRef

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

typedef struct {
    PyObject_HEAD
    BFontRef* fontRef;
} pyBFontRef;
    
    
static PyObject * pyBFontRef_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBFontRef *self;
    self = (pyBFontRef *)type->tp_alloc(type, 0);
    return (PyObject *)self; 
}

static void pyBFontRef_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

static PyObject* pyBFontRef_objectType_getter(pyBFontRef* self, void* closure)
{ return PyString_FromString("BFontRef");}


static PyGetSetDef pyBFontRef_getSet[] = {
    {(char*)"objectType"  , (getter) pyBFontRef_objectType_getter  , 0 , NULL, NULL},
    {NULL}
};
    
    
static PyTypeObject pyBFontRef_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BFontRef",
    sizeof(pyBFontRef),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBFontRef_dealloc,  /*tp_dealloc*/
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
    "BFontRef maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    0,                         /* tp_members */
    pyBFontRef_getSet,         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBFontRef_new,             /* tp_new */

};

#endif