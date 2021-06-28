#ifndef _PY_U_DISPLAY_H_
#define _PY_U_DISPLAY_H_

#include <Bizarre.h>

#include <Python.h>
#include "structmember.h"

#include "pyBMaterial.h"

   typedef struct {
        PyObject_HEAD
        BDisplay * display;
    } pyBDisplay;
      
    
    static PyObject * pyBDisplay_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBDisplay *self;
        self = (pyBDisplay *)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
    }
    

    static void pyBDisplay_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


    /*static PyObject* pyBDisplay_getArmature(pyBDisplay* self)
    {    
        pyBArmature* arm = PyObject_New(pyBArmature, &pyBArmature_type);
        arm->armature = self->mesh->getArmature();  
        return (PyObject *)arm;
        
    }
    
    
    static PyObject* pyBDisplay_getTexturesNumber(pyBDisplay* self){
        return Py_BuildValue("I",self->mesh->getTexturesNumber());
    }
    
*/

    static PyObject* pyBDisplay_getPrimitiveType(pyBDisplay* self){
        return Py_BuildValue("i",(int)self->display->getPrimitiveType());
    }

    static PyObject* pyBDisplay_getBegin(pyBDisplay* self){
        return Py_BuildValue("I",self->display->getBegin());
    }

    static PyObject* pyBDisplay_getSize(pyBDisplay* self){
        return Py_BuildValue("I",self->display->getSize());
    }



    static PyObject* pyBDisplay_getMaterial(pyBDisplay* self)
    {    
        pyBMaterial* material = PyObject_New(pyBMaterial, &pyBMaterial_type);
        material->material = self->display->getMaterial();  
        return (PyObject *)material;
        
    }

    static PyObject* pyBDisplay_setMaterial(pyBDisplay* self, PyObject* args)
    {
        pyBMaterial* material;

        if (!PyArg_ParseTuple(args, "O!", &material, &pyBMaterial_type ))
            return NULL;

        self->display->setMaterial(material->material);

        Py_INCREF(Py_None);
        return Py_None; 
    }


    static PyObject* pyBDisplay_getCullMode(pyBDisplay* self){
        return Py_BuildValue("I",(int)self->display->getCullMode());
    }

    static PyObject* pyBDisplay_setCullMode(pyBDisplay* self, PyObject* args)
    {
        int type;

        if (!PyArg_ParseTuple(args, "i", &type ))
            return NULL;

        self->display->setCullMode((U_CULL_MODES)type );

        Py_INCREF(Py_None);
        return Py_None; 
    }


    static PyObject* pyBDisplay_setVisibility(pyBDisplay* self, PyObject* args)
    {
        bool visible;

        if (!PyArg_ParseTuple(args, "b", &visible ))
            return NULL;

        self->display->setVisibility(visible);

        Py_INCREF(Py_None);
        return Py_None; 
    }

    static PyObject* pyBDisplay_isVisible(pyBDisplay* self){
        return Py_BuildValue("b",self->display->isVisible());
    }

    static PyMethodDef pyBDisplay_methods[] = {
        {   "getPrimitiveType"   , (PyCFunction)pyBDisplay_getPrimitiveType  , METH_NOARGS ,    ""},
        {   "getBegin"           , (PyCFunction)pyBDisplay_getBegin          , METH_NOARGS ,    ""},
        {   "getSize"            , (PyCFunction)pyBDisplay_getSize           , METH_NOARGS ,    ""},
        {   "getMaterial"        , (PyCFunction)pyBDisplay_getMaterial       , METH_NOARGS ,    ""},
        {   "setMaterial"        , (PyCFunction)pyBDisplay_setMaterial       , METH_VARARGS ,    ""},
        {   "getCullMode"        , (PyCFunction)pyBDisplay_getCullMode       , METH_NOARGS ,    ""},
        {   "setCullMode"        , (PyCFunction)pyBDisplay_setCullMode       , METH_VARARGS ,   ""},
        {   "setVisibility"      , (PyCFunction)pyBDisplay_setVisibility     , METH_VARARGS ,   ""},
        {   "isVisible"          , (PyCFunction)pyBDisplay_isVisible         , METH_NOARGS ,     ""},
        {   NULL                 , NULL                                      , 0            , NULL} /* Sentinel */
    };
    
    
    static PyTypeObject pyBDisplay_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BDisplay",
    sizeof(pyBDisplay),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBDisplay_dealloc,/*tp_dealloc*/
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
    "BMesh maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBDisplay_methods,           /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyBDisplay_new,             /* tp_new */

};

#endif