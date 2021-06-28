

#ifndef _PYMTEXTUREREF
#define _PYMTEXTUREREF
    #include <Python.h>
    #include "structmember.h"

    #include <Bizarre.h>

    typedef struct {
        PyObject_HEAD
        BTextureRef* textureRef;
    } pyBTextureRef;  
    
    static PyObject * pyBTextureRef_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBTextureRef *self;
        self = (pyBTextureRef *)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
    }

    static void pyBTextureRef_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }
    
    
    static PyObject* pyBTextureRef_getFilename(pyBTextureRef* self)
    {
        return Py_BuildValue("s",self->textureRef->getFilename()); 
    }
    
    static PyObject* pyBTextureRef_getHeight(pyBTextureRef* self)
    {
        return Py_BuildValue("I",self->textureRef->getHeight()); 
    }
    
    static PyObject* pyBTextureRef_getWidth(pyBTextureRef* self)
    {
        return Py_BuildValue("I",self->textureRef->getWidth()); 
    }
    
    static PyObject * pyBTextureRef_update(pyBTextureRef* self)
    {
        self->textureRef->update();
        Py_RETURN_NONE;
    }

    static PyMethodDef pyBTextureRef_methods[] = {
        {   "getFilename"        , (PyCFunction)pyBTextureRef_getFilename          , METH_NOARGS , ""},
        {   "getHeight"          , (PyCFunction)pyBTextureRef_getHeight            , METH_NOARGS , ""},
        {   "getWidth"           , (PyCFunction)pyBTextureRef_getWidth             , METH_NOARGS , ""},
        {   "update"           , (PyCFunction)pyBTextureRef_update                 , METH_NOARGS , ""},
        {NULL, NULL, 0, NULL} /* Sentinel */
    };
    
    static PyTypeObject pyBTextureRef_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BTextureRef",
    sizeof(pyBTextureRef),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBTextureRef_dealloc, /*tp_dealloc*/
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
    "BTextureRef maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBTextureRef_methods,     /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBTextureRef_new,             /* tp_new */

};
    
#endif