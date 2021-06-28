

#ifndef _PYMARMATURE
#define _PYMARMATURE
    #include <Python.h>
    #include "structmember.h"

    #include <Bizarre.h>

    #include "pyBOBone.h"

    typedef struct {
        PyObject_HEAD
        BArmature* armature;
    } pyBArmature;
    
    static PyObject * pyBArmature_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBArmature *self;
        self = (pyBArmature *)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
        
    }
    
    static PyObject* pyBArmature_getBone(pyBArmature* self, PyObject* args)
    {
        unsigned int value;
        if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: getBone(<int>Id)");
            return NULL;
        }
    
        pyBOBone* b = PyObject_New(pyBOBone, &pyBOBone_type);
        b->obj.object = (BObject3d*)self->armature->getBone(value); 
        return (PyObject *)b;
    }
 
    static PyObject* pyBArmature_getBoneByName(pyBArmature* self, PyObject* args)
    {
        char* value;
        if (!PyArg_ParseTuple(args, "s", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: getBoneByName(<string>boneName)");
            return NULL;
        }
    
        pyBOBone* b = PyObject_New(pyBOBone, &pyBOBone_type);
        b->obj.object = (BObject3d*)self->armature->getBoneByName(value); 
        return (PyObject *)b;
    }
    
    static PyObject* pyBArmature_getBonesNumber(pyBArmature* self){
        return Py_BuildValue("I",self->armature->getBonesNumber());
    }
    
    static PyMethodDef pyBArmature_methods[] = {
     {   "getBone"         , (PyCFunction)pyBArmature_getBone        , METH_VARARGS, ""},
     {   "getBoneByName"   , (PyCFunction)pyBArmature_getBoneByName  , METH_VARARGS, ""},
     {   "getBonesNumber"  , (PyCFunction)pyBArmature_getBonesNumber , METH_NOARGS, ""},
     {NULL}
    };
    
    
    static PyTypeObject pyBArmature_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BArmature",
    sizeof(pyBArmature),        /*tp_basicsize*/
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
    "BArmature maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBArmature_methods,       /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBArmature_new,             /* tp_new */

};
    
#endif