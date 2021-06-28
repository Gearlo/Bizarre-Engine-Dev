#ifndef _PY_M_SOUND_REF
#define _PY_M_SOUND_REF

    #include <Python.h>
    #include "structmember.h"

    #include <BEngine.h>

    typedef struct {
        PyObject_HEAD
        BSoundRef* soundRef;
    } pyBSoundRef;
    
    
    static PyObject * pyBSoundRef_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBSoundRef *self;
        self = (pyBSoundRef*)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
    }
    
static PyTypeObject pyBSoundRef_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BSoundRef",
    sizeof(pyBSoundRef),        /*tp_basicsize*/
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
    "BSoundRef",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBSoundRef_new,             /* tp_new */

};

#endif