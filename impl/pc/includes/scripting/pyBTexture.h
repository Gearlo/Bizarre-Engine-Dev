

#ifndef _PY_M_TEXTURE
#define _PY_M_TEXTURE

    #include <Python.h>
    #include "structmember.h"

    #include <Bizarre.h>

    #include "pyUVector.h"
    #include "pyBTextureRef.h"

    typedef struct {
        PyObject_HEAD
        BTexture* texture;
    } pyBTexture;  
    
    static PyObject * pyBTexture_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBTexture *self;
        self = (pyBTexture *)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
       
    }
    
    static PyObject* pyBTexture_getTexRotate(pyBTexture* self)
    {
        return Py_BuildValue("f",self->texture->getTexRotate()); 
    }
    
    static PyObject* pyBTexture_getTexScale(pyBTexture* self)
    {
        pyUVector2* color = PyObject_New(pyUVector2, &pyUVector2_type);
        color->vector = self->texture->getTexScale();
        return (PyObject*)color;
        //self->texture->();
    }
    
    static PyObject* pyBTexture_getTextureRef(pyBTexture* self)
    {
        pyBTextureRef* msr = PyObject_New(pyBTextureRef, &pyBTextureRef_type);
        msr->textureRef = self->texture->getTextureRef();
        return (PyObject*)msr;  
    } 
    
    static PyObject* pyBTexture_getTexTranslate(pyBTexture* self)
    {
        pyUVector2* color = PyObject_New(pyUVector2, &pyUVector2_type);
        color->vector = self->texture->getTexTranslate();
        return (PyObject*)color;
    }
    
    static PyObject* pyBTexture_setTexRotate(pyBTexture* self, PyObject* args)
    {
        float r;
        if (!PyArg_ParseTuple(args, "f", &r)){
                PyErr_SetString(PyExc_AttributeError, "parameters is: setTexRotate(<float>rotation)");
                return NULL;         
        }else{
            self->texture->setTexRotate(r);
        }
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBTexture_setTexScale(pyBTexture* self, PyObject* args)
    {
        float x;
        float y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)){
            pyUVector2 * v;
            if (PyArg_ParseTuple(args, "O", &v)){
                PyErr_Clear();
                self->texture->setTexScale(v->vector);
            }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: setTexScale(<float>x, <float>y) or setTexScale(<BVector2f>scale)");
                return NULL;
            }
        }else{
            self->texture->setTexScale(BVector2f(x,y));
        }
        Py_RETURN_NONE;       
    } 
    
        static PyObject* pyBTexture_setTextureRef(pyBTexture* self, PyObject* args)
    {
        pyBTextureRef* tr;
        if (PyArg_ParseTuple(args, "O", &tr)){
            self->texture->setTextureRef(tr->textureRef);
            Py_RETURN_NONE;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setMeshRef(<BMeshRef>meshRef)");
            return NULL;
        } 
    }
    
    static PyObject* pyBTexture_setTexTranslate(pyBTexture* self, PyObject* args)
    {
        float x;
        float y;
        if (!PyArg_ParseTuple(args, "ff", &x, &y)){
            pyUVector2 * v;
            if (PyArg_ParseTuple(args, "O", &v)){
                PyErr_Clear();
                self->texture->setTexTranslate(v->vector);
            }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: setTexTranslate(<float>x, <float>y) or setTexTranslate(<BVector2f>traslation)");
                return NULL;
            }
        }else{
            self->texture->setTexTranslate(BVector2f(x,y));
        }
        Py_RETURN_NONE;       
    } 
    
    static PyMethodDef pyBTexture_methods[] = {
        {   "getTexRotate"      , (PyCFunction)pyBTexture_getTexRotate        , METH_NOARGS , ""},
        {   "getTexScale"       , (PyCFunction)pyBTexture_getTexScale         , METH_NOARGS , ""},
        {   "getTextureRef"     , (PyCFunction)pyBTexture_getTextureRef       , METH_NOARGS , ""},
        {   "getTexTranslate"   , (PyCFunction)pyBTexture_getTexTranslate     , METH_NOARGS , ""},
        {   "setTexRotate"      , (PyCFunction)pyBTexture_setTexRotate        , METH_VARARGS , ""},
        {   "setTexScale"       , (PyCFunction)pyBTexture_setTexScale         , METH_VARARGS , ""},
        {   "setTextureRef"     , (PyCFunction)pyBTexture_setTextureRef       , METH_VARARGS , ""},
        {   "setTexTranslate"   , (PyCFunction)pyBTexture_setTexTranslate     , METH_VARARGS , ""},
        {NULL, NULL, 0, NULL} /* Sentinel */
    };
    
    static PyTypeObject pyBTexture_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BTexture",
    sizeof(pyBTexture),        /*tp_basicsize*/
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
    "BTexture maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBTexture_methods,        /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBTexture_new,             /* tp_new */

};
    
#endif