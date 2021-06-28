#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#ifndef _PY_M_OLIGHT
#define _PY_M_OLIGHT

#include "pyBObject3d.h"

    typedef struct {
        pyBObject3d obj;
    } pyBOLight;
   
    
    static PyObject* pyBOLight_castShadow(pyBOLight* self, PyObject* args)
    {
    bool shadow;
    if (!PyArg_ParseTuple(args, "b", &shadow)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: castShadow(<float>cast)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->castShadow(shadow);
    }
        Py_RETURN_NONE;
    }
    
    
    static PyObject* pyBOLight_getColor(pyBOLight* self)
    {
        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = ((BOLight *)self->obj.object)->getColor();
        return (PyObject*)color;
    }
    
    static PyObject* pyBOLight_getFinalColor(pyBOLight* self)
    {
        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = ((BOLight *)self->obj.object)->getFinalColor();
        return (PyObject*)color;
    }
    
    
    static PyObject* pyBOLight_getIntensity(pyBOLight* self)
    {
        return Py_BuildValue("f",((BOLight *)self->obj.object)->getIntensity());  
    }   
    
    static PyObject* pyBOLight_getRadius(pyBOLight* self)
    {
        return Py_BuildValue("f",((BOLight *)self->obj.object)->getRadius());  
    }
    
    static PyObject* pyBOLight_getShadowBias(pyBOLight* self)
    {
        return Py_BuildValue("f",((BOLight *)self->obj.object)->getShadowBias());  
    }
    
    static PyObject* pyBOLight_getShadowBlur(pyBOLight* self)
    {
        return Py_BuildValue("f",((BOLight *)self->obj.object)->getShadowBlur());  
    }
    
    static PyObject* pyBOLight_getShadowQuality(pyBOLight* self)
    {
        return Py_BuildValue("I",((BOLight *)self->obj.object)->getShadowQuality());  
    }
    
    static PyObject* pyBOLight_getSpotAngle(pyBOLight* self)
    {
        return Py_BuildValue("f",((BOLight *)self->obj.object)->getSpotAngle());  
    }
    
    static PyObject* pyBOLight_getSpotExponent(pyBOLight* self)
    {
        return Py_BuildValue("f",((BOLight *)self->obj.object)->getSpotExponent());  
    }
    
    static PyObject* pyBOLight_isCastingShadow(pyBOLight* self)
    {
        return Py_BuildValue("b",((BOLight *)self->obj.object)->isCastingShadow());
    }
    
    static PyObject* pyBOLight_setColor(pyBOLight* self, PyObject* args)
    {
    float r; float g; float b;
    if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)){
        pyUVector3 * color;
        if (PyArg_ParseTuple(args, "O", &color)){
            PyErr_Clear();
            ((BOLight *)self->obj.object)->setColor(color->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setColor(<float>r, <float>g, <float>b) or setColor(<BVector3f>color)");
            return NULL;
        }
    }else{
        ((BOLight *)self->obj.object)->setColor(BVector3f(r,g,b));
    }
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBOLight_setIntensity(pyBOLight* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setIntensity(<float>value)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->setIntensity(value);
    }
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBOLight_setRadius(pyBOLight* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setRadius(<float>value)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->setRadius(value);
    }
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBOLight_setShadowBias(pyBOLight* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setShadowBias(<float>value)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->setShadowBias(value);
    }
        Py_RETURN_NONE;       
    }  
    
    static PyObject* pyBOLight_setShadowBlur(pyBOLight* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setShadowBlur(<float>value)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->setShadowBlur(value);
    }
        Py_RETURN_NONE;       
    } 
    
    static PyObject* pyBOLight_setShadowQuality(pyBOLight* self, PyObject* args)
    {
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setShadowQuality(<int>value)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->setShadowQuality(value);
    }
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBOLight_setSpotAngle(pyBOLight* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setSpotAngle(<float>value)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->setSpotAngle(value);
    }
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBOLight_setSpotExponent(pyBOLight* self, PyObject* args)
    {
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setSpotExponent(<float>value)");
            return NULL;   
    }else{
        ((BOLight *)self->obj.object)->setSpotExponent(value);
    }
        Py_RETURN_NONE;       
    }
    
    
    
    static PyMethodDef pyBOLightMethods[] = {
       {  "castShadow"        ,        (PyCFunction)pyBOLight_castShadow           , METH_VARARGS    ,   ""   },
       {  "getColor"          ,        (PyCFunction)pyBOLight_getColor             , METH_NOARGS     ,   ""   },
       {  "getFinalColor"     ,        (PyCFunction)pyBOLight_getFinalColor        , METH_NOARGS     ,   ""   },
       {  "getIntensity"      ,        (PyCFunction)pyBOLight_getIntensity         , METH_NOARGS     ,   ""   },
       {  "getRadius"         ,        (PyCFunction)pyBOLight_getRadius            , METH_NOARGS     ,   ""   },
       {  "getShadowBias"     ,        (PyCFunction)pyBOLight_getShadowBias        , METH_NOARGS     ,   ""   },
       {  "getShadowBlur"     ,        (PyCFunction)pyBOLight_getShadowBlur        , METH_NOARGS     ,   ""   },
       {  "getShadowQuality"  ,        (PyCFunction)pyBOLight_getShadowQuality     , METH_NOARGS     ,   ""   },
       {  "getSpotAngle"      ,        (PyCFunction)pyBOLight_getSpotAngle         , METH_NOARGS     ,   ""   },
       {  "getSpotExponent"   ,        (PyCFunction)pyBOLight_getSpotExponent      , METH_NOARGS     ,   ""   },
       {  "isCastingShadow"   ,        (PyCFunction)pyBOLight_isCastingShadow      , METH_NOARGS     ,   ""   },
       {  "setColor"          ,        (PyCFunction)pyBOLight_setColor             , METH_VARARGS    ,   ""   },
       {  "setIntensity"      ,        (PyCFunction)pyBOLight_setIntensity         , METH_VARARGS    ,   ""   },
       {  "setRadius"         ,        (PyCFunction)pyBOLight_setRadius            , METH_VARARGS    ,   ""   },
       {  "setShadowBias"     ,        (PyCFunction)pyBOLight_setShadowBias        , METH_VARARGS    ,   ""   },
       {  "setShadowBlur"     ,        (PyCFunction)pyBOLight_setShadowBlur        , METH_VARARGS    ,   ""   },
       {  "setShadowQuality"  ,        (PyCFunction)pyBOLight_setShadowQuality     , METH_VARARGS    ,   ""   },
       {  "setSpotAngle"      ,        (PyCFunction)pyBOLight_setSpotAngle         , METH_VARARGS    ,   ""   },
       {  "setSpotExponent"   ,        (PyCFunction)pyBOLight_setSpotExponent      , METH_VARARGS    ,   ""   },
       {NULL, NULL, 0, NULL} /* Sentinel */
    };
    
    static PyTypeObject pyBOLight_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BOLight",
    sizeof(pyBOLight),         /*tp_basicsize*/
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
    "BOLight maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBOLightMethods,          /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */

};
#endif
