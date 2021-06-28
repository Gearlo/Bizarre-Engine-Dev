


#ifndef _pyBMesh
#define _pyBMesh
    
#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#include "pyBAnimProperties.h"

#include "pyBTexture.h"
#include "pyBMaterial.h"
#include "pyBArmature.h"
#include "pyBSubMesh.h"


    typedef struct {
        PyObject_HEAD
        BMesh* mesh;
    } pyBMesh;
      
    
    static PyObject * pyBMesh_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBMesh *self;
        self = (pyBMesh *)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
    }
    
    static int pyBMesh_init(pyBMesh *self, PyObject *args, PyObject *kwds)
    { 
        self->mesh = BMesh::getNew();
        return 0;
    }

    static void pyBMesh_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


    static PyObject* pyBMesh_addNewTexture(pyBMesh* self, PyObject* args)
    {
        pyBTextureRef* textureRef;

        if (!PyArg_ParseTuple(args, "O!", &pyBTextureRef_type, &textureRef ))
            return NULL;

        self->mesh->addNewTexture(textureRef->textureRef);
        
        Py_INCREF(Py_None);
        return Py_None; 
    }

    static PyObject* pyBMesh_allocAnimsProps(pyBMesh* self, PyObject* args)
    {
        unsigned int i;

        if (!PyArg_ParseTuple(args, "I", &i ))
            return NULL;

        self->mesh->allocAnimsProps(i);

        Py_INCREF(Py_None);
        return Py_None; 
    }


    static PyObject* pyBMesh_allocSubMeshs(pyBMesh* self, PyObject* args)
    {
        unsigned int i;

        if (!PyArg_ParseTuple(args, "I", &i ))
            return NULL;

        self->mesh->allocSubMeshs(i);

        Py_INCREF(Py_None);
        return Py_None; 
    }

    
    static PyObject* pyBMesh_allocTextures(pyBMesh* self, PyObject* args)
    {
        unsigned int i;

        if (!PyArg_ParseTuple(args, "I", &i ))
            return NULL;

        self->mesh->allocTextures(i);
        
        Py_INCREF(Py_None);
        return Py_None; 
    }


    static PyObject* pyBMesh_clearAnimsProps(pyBMesh* self){
        self->mesh->clearAnimsProps();Py_INCREF(Py_None);return Py_None; }


    static PyObject* pyBMesh_getArmature(pyBMesh* self)
    {    
        pyBArmature* arm = PyObject_New(pyBArmature, &pyBArmature_type);
        arm->armature = self->mesh->getArmature();  
        return (PyObject *)arm;
        
    }
    

    static PyObject* pyBMesh_getSubMesh(pyBMesh* self, PyObject* args)
    {
        unsigned int i;
        if (!PyArg_ParseTuple(args, "I", &i)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: getMaterial(<int>Id)");
            return NULL;
        }
    
        if( i < self->mesh->getSubMeshsNumber() ){
            pyBSubMesh* submesh = PyObject_New(pyBSubMesh, &pyBSubMesh_type);
            submesh->submesh = &self->mesh->getSubMeshs()[i];  
            return (PyObject *)submesh;
        }

        Py_INCREF(Py_None);
        return Py_None; 
    }
    

    static PyObject* pyBMesh_getTexture(pyBMesh* self, PyObject* args)
    {
        unsigned int value;
        if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: getTexture(<int>Id)");
            return NULL;
        }
    
        pyBTexture* tx = PyObject_New(pyBTexture, &pyBTexture_type);
        tx->texture = self->mesh->getTexture(value);  
        return (PyObject *)tx;
    }
    
    static PyObject* pyBMesh_getMaterialsNumber(pyBMesh* self){
        return Py_BuildValue("I",self->mesh->getMaterialsNumber());
        
    }
    

    static PyObject* pyBMesh_getSubMeshsNumber(pyBMesh* self){
        return Py_BuildValue("I",self->mesh->getSubMeshsNumber());
    }


    static PyObject* pyBMesh_getTexturesNumber(pyBMesh* self){
        return Py_BuildValue("I",self->mesh->getTexturesNumber());
    }
    


    static PyObject* pyBMesh_getAnimsPropsNumber(pyBMesh* self){
        return Py_BuildValue("I",self->mesh->getAnimsPropsNumber());
    }


    static PyObject* pyBMesh_getAnimProperties(pyBMesh* self, PyObject* args)
    {
        unsigned int i;

        if (!PyArg_ParseTuple(args, "I", &i ))
            return NULL;

        BAnimProperties * _animProps = self->mesh->getAnimProps(i);

        if(!_animProps){
            Py_INCREF(Py_None);
            return Py_None; 
        }
        
        pyBAnimProperties* animProps = PyObject_New(pyBAnimProperties, &pyBAnimProperties_type);
        animProps->animProps = _animProps;  
        return (PyObject *)animProps;
    }


    static PyMethodDef pyBMesh_methods[] = {
        {   "addNewTexture"           , (PyCFunction)pyBMesh_addNewTexture      , METH_VARARGS ,   ""},
        {   "allocAnimsProperties"    , (PyCFunction)pyBMesh_allocAnimsProps    , METH_VARARGS ,   ""},
        {   "allocSubMeshs"           , (PyCFunction)pyBMesh_allocSubMeshs      , METH_VARARGS ,   ""},
        {   "allocTextures"           , (PyCFunction)pyBMesh_allocTextures      , METH_VARARGS ,   ""},
        {   "clearAnimsProperties"    , (PyCFunction)pyBMesh_clearAnimsProps    , METH_NOARGS  ,   ""},
        {   "getArmature"        , (PyCFunction)pyBMesh_getArmature          , METH_NOARGS ,   ""},
       // {   "getMaterial"        , (PyCFunction)pyBMesh_getMaterial          , METH_VARARGS ,  ""},
        {   "getTexture"         , (PyCFunction)pyBMesh_getTexture           , METH_VARARGS ,  ""},
        {   "getSubMesh"         , (PyCFunction)pyBMesh_getSubMesh           , METH_VARARGS ,  ""},
       // {   "getMaterialsNumber" , (PyCFunction)pyBMesh_getMaterialsNumber   , METH_NOARGS ,   ""},
        {   "getSubMeshsNumber"  , (PyCFunction)pyBMesh_getSubMeshsNumber    , METH_NOARGS ,   ""},
        {   "getTexturesNumber"  , (PyCFunction)pyBMesh_getTexturesNumber    , METH_NOARGS ,   ""},
        {   "getAnimsPropertiesNumber", (PyCFunction)pyBMesh_getAnimsPropsNumber, METH_NOARGS  ,   ""},
        {   "getAnimProperties"       , (PyCFunction)pyBMesh_getAnimProperties  , METH_VARARGS ,   ""},
        {   NULL                      , NULL                                    , 0            , NULL} /* Sentinel */
    };
    
    
    static PyTypeObject pyBMesh_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BMesh",
    sizeof(pyBMesh),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBMesh_dealloc,/*tp_dealloc*/
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
    pyBMesh_methods,           /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)pyBMesh_init,   /* tp_init */
    0,                         /* tp_alloc */
    pyBMesh_new,             /* tp_new */

};
#endif