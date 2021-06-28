
#ifndef _PY_M_MATERIAL
#define _PY_M_MATERIAL

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>   

    typedef struct {
        PyObject_HEAD
        BMaterial* material;
    } pyBMaterial;

    static PyObject * pyBMaterial_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBMaterial *self;
        self = (pyBMaterial *)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
    }
    
    static PyObject* pyBMaterial_getBlendMode(pyBMaterial* self, PyObject* args){
        M_BLENDING_MODES bm = self->material->getBlendMode();
        switch(bm){
            case M_BLENDING_NONE:
                return Py_BuildValue("s","none"); break; 
            case M_BLENDING_ALPHA:
                return Py_BuildValue("s","alpha"); break; 
            case M_BLENDING_ADD:
                return Py_BuildValue("s","add"); break;
            case M_BLENDING_SUB:
                return Py_BuildValue("s","sub"); break;
            case M_BLENDING_LIGHT:
                return Py_BuildValue("s","light"); break;
            case M_BLENDING_PRODUCT:
                return Py_BuildValue("s","product"); break;  
        }
        Py_RETURN_NONE; 
    }
    
    static PyObject* pyBMaterial_getCustomColor(pyBMaterial* self)
    {
        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = self->material->getCustomColor();
        return (PyObject*)color;
    }
    
    static PyObject* pyBMaterial_getOpacity(pyBMaterial* self)
    {
        return Py_BuildValue("f",self->material->getOpacity());
    }
    
    static PyObject* pyBMaterial_getShininess(pyBMaterial* self)
    {
        return Py_BuildValue("f",self->material->getShininess());
    }
    
    static PyObject* pyBMaterial_getDiffuse(pyBMaterial* self)
    {
        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = self->material->getDiffuse();
        return (PyObject*)color;
    }
    
    static PyObject* pyBMaterial_getEmit(pyBMaterial* self)
    {
        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = self->material->getEmit();
        return (PyObject*)color;
    }
    
    static PyObject* pyBMaterial_getSpecular(pyBMaterial* self)
    {
        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = self->material->getSpecular();
        return (PyObject*)color;
    }
    
    //TODO: cambiar los textos en al argumento por constantes
    static PyObject* pyBMaterial_setBlendMode(pyBMaterial* self, PyObject* args)
    {
    char* text;
    if (!PyArg_ParseTuple(args, "s", &text)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setBlendMode(<string>blendModeName)");
            return NULL;   
    }else{
        if (strcmp("none", text) == 0){
            self->material->setBlendMode(M_BLENDING_NONE);
        } else if (strcmp("alpha", text) == 0){
            self->material->setBlendMode(M_BLENDING_ALPHA);
        } else if (strcmp("add", text) == 0){
            self->material->setBlendMode(M_BLENDING_ADD);
        } else if (strcmp("sub", text) == 0){
            self->material->setBlendMode(M_BLENDING_SUB);
        } else if (strcmp("light", text) == 0){
            self->material->setBlendMode(M_BLENDING_LIGHT);
        } else if (strcmp("product", text) == 0){
            self->material->setBlendMode(M_BLENDING_PRODUCT);
        }  
    }
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBMaterial_setCustomColor(pyBMaterial* self, PyObject* args)
    {
        float r; float g; float b;
        if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)){
            pyUVector3 * color;
            if (PyArg_ParseTuple(args, "O", &color)){
                PyErr_Clear();
                self->material->setCustomColor(color->vector);
            }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: setCustomColor(<float>r, <float>g, <float>b) or setCustomColor(<BVector3f>color)");
                return NULL;
            }
        }else{
           self->material->setCustomColor(BVector3f(r,g,b));
        }
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBMaterial_setCustomValue(pyBMaterial* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setCustomValue(<float>value)");
            return NULL;   
    }else{
        self->material->setCustomValue(value);
    }
        Py_RETURN_NONE;   
    }
    
    static PyObject* pyBMaterial_setDiffuse(pyBMaterial* self, PyObject* args)
    {
        float r; float g; float b;
        if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)){
            pyUVector3 * color;
            if (PyArg_ParseTuple(args, "O", &color)){
                PyErr_Clear();
                self->material->setDiffuse(color->vector);
            }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: setDiffuse(<float>r, <float>g, <float>b) or setDiffuse(<BVector3f>color)");
                return NULL;
            }
        }else{
           self->material->setDiffuse(BVector3f(r,g,b));
        }
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBMaterial_setEmit(pyBMaterial* self, PyObject* args)
    {
        float r; float g; float b;
        if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)){
            pyUVector3 * color;
            if (PyArg_ParseTuple(args, "O", &color)){
                PyErr_Clear();
                self->material->setEmit(color->vector);
            }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: setEmit(<float>r, <float>g, <float>b) or setEmit(<BVector3f>color)");
                return NULL;
            }
        }else{
           self->material->setEmit(BVector3f(r,g,b));
        }
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBMaterial_setOpacity(pyBMaterial* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setOpacity(<float>value)");
            return NULL;   
    }else{
        self->material->setOpacity(value);
    }
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBMaterial_setShininess(pyBMaterial* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setShininess(<float>value)");
            return NULL;   
    }else{
        self->material->setShininess(value);
    }
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBMaterial_setSpecular(pyBMaterial* self, PyObject* args)
    {
        float r; float g; float b;
        if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)){
            pyUVector3 * color;
            if (PyArg_ParseTuple(args, "O", &color)){
                PyErr_Clear();
                self->material->setSpecular(color->vector);
            }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: setSpecular(<float>r, <float>g, <float>b) or setSpecular(<BVector3f>color)");
                return NULL;
            }
        }else{
           self->material->setSpecular(BVector3f(r,g,b));
           
        }
        Py_RETURN_NONE;
    }
    
    static PyMethodDef pyBMaterial_Methods[] = {
       {  "getBlendMode"        ,   (PyCFunction)pyBMaterial_getBlendMode         , METH_NOARGS    ,   ""   },
       {  "getCustomColor"      ,   (PyCFunction)pyBMaterial_getCustomColor       , METH_NOARGS    ,   ""   },
       {  "getOpacity"          ,   (PyCFunction)pyBMaterial_getOpacity           , METH_NOARGS    ,   ""   },
       {  "getShininess"        ,   (PyCFunction)pyBMaterial_getShininess         , METH_NOARGS    ,   ""   },
       {  "getDiffuse"          ,   (PyCFunction)pyBMaterial_getDiffuse           , METH_NOARGS    ,   ""   },
       {  "getEmit"             ,   (PyCFunction)pyBMaterial_getEmit              , METH_NOARGS    ,   ""   },
       {  "getSpecular"         ,   (PyCFunction)pyBMaterial_getSpecular          , METH_NOARGS    ,   ""   },
       {  "setBlendMode"        ,   (PyCFunction)pyBMaterial_setBlendMode         , METH_VARARGS    ,   ""   },
       {  "setCustomColor"      ,   (PyCFunction)pyBMaterial_setCustomColor       , METH_VARARGS    ,   ""   },
       {  "setCustomValue"      ,   (PyCFunction)pyBMaterial_setCustomValue       , METH_NOARGS    ,   ""   },
       {  "setOpacity"          ,   (PyCFunction)pyBMaterial_setOpacity           , METH_VARARGS    ,   ""   },
       {  "setShininess"        ,   (PyCFunction)pyBMaterial_setShininess         , METH_VARARGS    ,   ""   },
       {  "setDiffuse"          ,   (PyCFunction)pyBMaterial_setDiffuse           , METH_VARARGS    ,   ""   },
       {  "setEmit"             ,   (PyCFunction)pyBMaterial_setEmit              , METH_VARARGS    ,   ""   },
       {  "setSpecular"         ,   (PyCFunction)pyBMaterial_setSpecular          , METH_VARARGS    ,   ""   },
       {NULL, NULL, 0, NULL} /* Sentinel */
    };
    
    
    static PyTypeObject pyBMaterial_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BMaterial",
    sizeof(pyBMaterial),        /*tp_basicsize*/
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
    "BMaterial maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBMaterial_Methods,       /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBMaterial_new,             /* tp_new */
    };
#endif