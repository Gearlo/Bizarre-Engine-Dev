#ifndef _PY_B_COMPOSITEDMODEL
#define _PY_B_COMPOSITEDMODEL

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>


#include "pyBObject3d.h"
#include "pyBPhysicsProperties.h"
#include "pyBMeshRef.h"
#include "pyBMesh.h"

    typedef struct {
        pyBObject3d obj;
        BOCompositedModel3dSubMesh * cSubMesh;
    } pyBOCompositedModel3dSubMesh;


    typedef struct {
        pyBObject3d obj;
        BOCompositedModel3d * cModel;
    } pyBOCompositedModel3d;


    static PyObject * pyBOCompositedModel3dSubMesh_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBOCompositedModel3d* self;
        self = (pyBOCompositedModel3d *)type->tp_alloc(type, 0);
        if (!self){
            Py_RETURN_NONE;
        }
        
        return (PyObject *)self;
    }

    static void pyBOCompositedModel3dSubMesh_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


    static PyObject* pyBOCompositedModel3dSubMesh_getEulerRotation(pyBOCompositedModel3dSubMesh* self)
    {
        pyUVector3* rotation = PyObject_New(pyUVector3, &pyUVector3_type);
        rotation->vector = self->cSubMesh->getEulerRotation();
        return (PyObject*)rotation;
    }

    static PyObject* pyBOCompositedModel3dSubMesh_getPhysicsSubMesh(pyBOCompositedModel3dSubMesh* self)
    {   
        if( !self->cSubMesh->getPhysicsSubMesh() ){
            Py_RETURN_NONE;
        }

        pyBSubMesh* submesh = PyObject_New(pyBSubMesh, &pyBSubMesh_type);
        submesh->submesh = self->cSubMesh->getPhysicsSubMesh();
        return (PyObject*)submesh;  
    }

    static PyObject* pyBOCompositedModel3dSubMesh_getPosition(pyBOCompositedModel3dSubMesh* self)
    {
        pyUVector3* position = PyObject_New(pyUVector3, &pyUVector3_type);
        position->vector = self->cSubMesh->getPosition();
        return (PyObject*)position;
    }

    static PyObject* pyBOCompositedModel3dSubMesh_getScale(pyBOCompositedModel3dSubMesh* self)
    {
        pyUVector3* scale = PyObject_New(pyUVector3, &pyUVector3_type);
        scale->vector = self->cSubMesh->getScale();
        return (PyObject*)scale;
    }

    static PyObject* pyBOCompositedModel3dSubMesh_getSubMesh(pyBOCompositedModel3dSubMesh* self)
    {
        pyBSubMesh* submesh = PyObject_New(pyBSubMesh, &pyBSubMesh_type);
        submesh->submesh = self->cSubMesh->getSubMesh();
        return (PyObject*)submesh;  
    }

    static PyObject* pyBOCompositedModel3dSubMesh_setEulerRotation(pyBOCompositedModel3dSubMesh* self, PyObject* args)
    {

        pyUVector3 * rotation;
        if (PyArg_ParseTuple(args, "O!", &pyUVector3_type, &rotation)){
            PyErr_Clear();
            self->cSubMesh->setEulerRotation(rotation->vector);
        }    
        
        Py_RETURN_NONE;
    }

    

    static PyObject* pyBOCompositedModel3dSubMesh_setPosition(pyBOCompositedModel3dSubMesh* self, PyObject* args)
    {

        pyUVector3 * position;
        if (PyArg_ParseTuple(args, "O!", &pyUVector3_type, &position)){
            PyErr_Clear();
            self->cSubMesh->setPosition(position->vector);
        }    
        
        Py_RETURN_NONE;
    }

    static PyObject* pyBOCompositedModel3dSubMesh_setScale(pyBOCompositedModel3dSubMesh* self, PyObject* args)
    {

        pyUVector3 * scale;
        if (PyArg_ParseTuple(args, "O!", &pyUVector3_type, &scale)){
            PyErr_Clear();
            self->cSubMesh->setScale(scale->vector);
        }    
        
        Py_RETURN_NONE;
    }

    static PyObject* pyBOCompositedModel3dSubMesh_setSubMesh(pyBOCompositedModel3dSubMesh* self, PyObject* args)
    {
        pyBSubMesh* submesh;

        if (PyArg_ParseTuple(args, "O!", &pyBSubMesh_type, &submesh )){
            return NULL;
        } 

        self->cSubMesh->setSubMesh( submesh->submesh );
        Py_RETURN_NONE;
    }

    static PyObject* pyBOCompositedModel3dSubMesh_setPhysicsSubMesh(pyBOCompositedModel3dSubMesh* self, PyObject* args)
    {
        pyBSubMesh* submesh;

        if (PyArg_ParseTuple(args, "O!", &pyBSubMesh_type, &submesh )){
            return NULL;
        } 

        self->cSubMesh->setPhysicsSubMesh( submesh->submesh );
        Py_RETURN_NONE;
    }


    static PyMethodDef pyBOCompositedModel3dSubMesh_methods[] = {
        {   "getEulerRotation"            , (PyCFunction)pyBOCompositedModel3dSubMesh_getEulerRotation  , METH_NOARGS , ""},
        {   "getPosition"                 , (PyCFunction)pyBOCompositedModel3dSubMesh_getPosition       , METH_NOARGS , ""},
        {   "getScale"                    , (PyCFunction)pyBOCompositedModel3dSubMesh_getScale          , METH_NOARGS , ""},
        {   "getSubMesh"                  , (PyCFunction)pyBOCompositedModel3dSubMesh_getSubMesh        , METH_NOARGS , ""},
        {   "getPhysicsSubMesh"           , (PyCFunction)pyBOCompositedModel3dSubMesh_getPhysicsSubMesh , METH_NOARGS , ""},
        {   "setEulerRotation"            , (PyCFunction)pyBOCompositedModel3dSubMesh_setEulerRotation  , METH_VARARGS, ""},
        {   "setPosition"                 , (PyCFunction)pyBOCompositedModel3dSubMesh_setPosition       , METH_VARARGS, ""},
        {   "setScale"                    , (PyCFunction)pyBOCompositedModel3dSubMesh_setScale          , METH_VARARGS, ""},
        {   "setSubMesh"                  , (PyCFunction)pyBOCompositedModel3dSubMesh_setSubMesh        , METH_VARARGS, ""},
        {   "setPhysicsSubMesh"           , (PyCFunction)pyBOCompositedModel3dSubMesh_setPhysicsSubMesh , METH_VARARGS, ""},
        {NULL, NULL, 0, NULL} /* Sentinel */
    };

    static PyTypeObject pyBOCompositedModel3dSubMesh_type = {
        PyObject_HEAD_INIT(NULL)
        0,
        "BOCompositedModel3dSubMesh",
        sizeof(pyBOCompositedModel3dSubMesh),       /*tp_basicsize*/
        0,                         /*tp_itemsize*/
        (destructor)pyBOCompositedModel3dSubMesh_dealloc,/*tp_dealloc*/
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
        "pyBOCompositedModel3dSubMesh object",   /* tp_doc */
        0,                         /* tp_traverse */
        0,                         /* tp_clear */
        0,                         /* tp_richcompare */
        0,                         /* tp_weaklistoffset */
        0,                         /* tp_iter */
        0,                         /* tp_iternext */
        pyBOCompositedModel3dSubMesh_methods,                         /* tp_methods */
        0,                         /* tp_members */
        0,                         /* tp_getset */
        0,                         /* tp_base */
        0,                         /* tp_dict */
        0,                         /* tp_descr_get */
        0,                         /* tp_descr_set */
        0,                         /* tp_dictoffset */
        0,                         /* tp_init */
        0,                         /* tp_alloc */
        pyBOCompositedModel3dSubMesh_new,              /* tp_new */

    };



    static PyObject* pyBOCompositedModel3d_addCompositeSubMesh(pyBOCompositedModel3d* self, PyObject* args){
        pyBSubMesh * subMesh;
        pyUVector3 * position;

        if (!PyArg_ParseTuple(args, "O!O!", &pyBSubMesh_type, &subMesh, &pyUVector3_type, &position )){
            return NULL;
        }
        
        pyBOCompositedModel3dSubMesh* cSubMesh = PyObject_New(pyBOCompositedModel3dSubMesh, &pyBOCompositedModel3dSubMesh_type);
        cSubMesh->cSubMesh = self->cModel->addCompositeSubMesh( subMesh->submesh, position->vector );
        return (PyObject*)cSubMesh;
    }


    static PyObject* pyBOCompositedModel3d_getCompositeSubMesh(pyBOCompositedModel3d* self, PyObject* args){
        unsigned int index;

        if (!PyArg_ParseTuple(args, "I", &index )){
            return NULL;
        }
        
        pyBOCompositedModel3dSubMesh* cSubMesh = PyObject_New(pyBOCompositedModel3dSubMesh, &pyBOCompositedModel3dSubMesh_type);
        cSubMesh->cSubMesh = self->cModel->getCompositeSubMesh( index );
        return (PyObject*)cSubMesh;
    }


    static PyObject* pyBOCompositedModel3d_bake(pyBOCompositedModel3d* self){
        self->cModel->bake();
        Py_RETURN_NONE;
    }
    

    static PyObject* pyBOCompositedModel3d_changeAnimation(pyBOCompositedModel3d* self, PyObject* args){
        unsigned int value;
        if (!PyArg_ParseTuple(args, "I",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: changeAnimation(<int>animationId)");
            return NULL;
        }
        self->cModel->changeAnimation(value);
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBOCompositedModel3d_createPhysicsProperties(pyBOCompositedModel3d* self)
    {
        pyBPhysicsProperties* phy = PyObject_New(pyBPhysicsProperties, &pyBPhysicsProperties_type);
        phy->phy = self->cModel->createPhysicsProperties();
        return (PyObject*)phy;
    }
    
    static PyObject* pyBOCompositedModel3d_deletePhysicsProperties(pyBOCompositedModel3d *self){
        self->cModel->deletePhysicsProperties();
        Py_RETURN_NONE;
        
    }
  
    static PyObject* pyBOCompositedModel3d_getAnimationId(pyBOCompositedModel3d *self){
        return Py_BuildValue("I",self->cModel->getAnimationId());
    }
    
    static PyObject* pyBOCompositedModel3d_getAnimationSpeed(pyBOCompositedModel3d *self){
        return Py_BuildValue("f",self->cModel->getAnimationSpeed());
    }
    
    static PyObject* pyBOCompositedModel3d_getCurrentFrame(pyBOCompositedModel3d *self){
        return Py_BuildValue("f",self->cModel->getCurrentFrame());
    }
    
    static PyObject* pyBOCompositedModel3d_getMesh(pyBOCompositedModel3d* self)
    {
        pyBMesh* msr = PyObject_New(pyBMesh, &pyBMesh_type);
        msr->mesh = self->cModel->getMesh();
        return (PyObject*)msr;  
    }
    
    static PyObject* pyBOCompositedModel3d_getMeshRef(pyBOCompositedModel3d* self)
    {
        pyBMeshRef* msr = PyObject_New(pyBMeshRef, &pyBMeshRef_type);
        msr->meshRef = self->cModel->getMeshRef();
        return (PyObject*)msr;  
    } 
    
    static PyObject* pyBOCompositedModel3d_getPhysicsProperties(pyBOCompositedModel3d* self)
    {
        pyBPhysicsProperties* phy = PyObject_New(pyBPhysicsProperties, &pyBPhysicsProperties_type);
        phy->phy = self->cModel->getPhysicsProperties();
        if(phy->phy){
            return (PyObject*)phy;
        }else{
            Py_RETURN_NONE;
        }
        
    }
    
    static PyObject* pyBOCompositedModel3d_isAnimationOver(pyBOCompositedModel3d *self){
        return Py_BuildValue("b",self->cModel->isAnimationOver());
    }
    
    static PyObject* pyBOCompositedModel3d_setAnimationSpeed(pyBOCompositedModel3d* self, PyObject* args){
        float value;
        if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setAnimationSpeed(<float>speed)");
            return NULL;
        }
        self->cModel->setAnimationSpeed(value);
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBOCompositedModel3d_setCurrentFrame(pyBOCompositedModel3d* self, PyObject* args){
        float value;
        if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setCurrentFrame(<float>value)");
            return NULL;
        }
        self->cModel->setCurrentFrame(value);
        Py_RETURN_NONE;
    }
    
    
    static PyObject* pyBOCompositedModel3d_setInvisible(pyBOCompositedModel3d* self, PyObject* args)
    {
        bool visible;
        if (!PyArg_ParseTuple(args, "b", &visible)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setInvisible(<bool>visible)");
            return NULL;  
        }else{
            self->cModel->setInvisible(visible);
        }
            Py_RETURN_NONE;    
        
    }
    
    
    
    static PyMethodDef pyBOCompositedModel3d_methods[] = {
        {   "addCompositeSubMesh"        , (PyCFunction)pyBOCompositedModel3d_addCompositeSubMesh      , METH_VARARGS, ""},
        {   "getCompositeSubMesh"        , (PyCFunction)pyBOCompositedModel3d_getCompositeSubMesh      , METH_VARARGS, ""},
        {   "bake"                       , (PyCFunction)pyBOCompositedModel3d_bake                     , METH_VARARGS, ""},
//        {   "changeAnimation"            , (PyCFunction)pyBOCompositedModel3d_changeAnimation          , METH_VARARGS, ""},
        {   "createPhysicsProperties"    , (PyCFunction)pyBOCompositedModel3d_createPhysicsProperties  , METH_NOARGS , ""},
        {   "deletePhysicsProperties"    , (PyCFunction)pyBOCompositedModel3d_deletePhysicsProperties  , METH_NOARGS , ""},
//        {   "getAnimationId"             , (PyCFunction)pyBOCompositedModel3d_getAnimationId           , METH_NOARGS , ""},
//        {   "getAnimationSpeed"          , (PyCFunction)pyBOCompositedModel3d_getAnimationSpeed        , METH_NOARGS , ""},
//        {   "getCurrentFrame"            , (PyCFunction)pyBOCompositedModel3d_getCurrentFrame          , METH_NOARGS , ""},
        {   "getMesh"                    , (PyCFunction)pyBOCompositedModel3d_getMesh                  , METH_NOARGS , ""},
        {   "getMeshRef"                 , (PyCFunction)pyBOCompositedModel3d_getMeshRef               , METH_NOARGS , ""},
        {   "getPhysicsProperties"       , (PyCFunction)pyBOCompositedModel3d_getPhysicsProperties     , METH_NOARGS , ""},
//        {   "isAnimationOver"            , (PyCFunction)pyBOCompositedModel3d_isAnimationOver          , METH_NOARGS , ""},
//        {   "setAnimationSpeed"          , (PyCFunction)pyBOCompositedModel3d_setAnimationSpeed        , METH_VARARGS, ""},
//        {   "setCurrentFrame"            , (PyCFunction)pyBOCompositedModel3d_setCurrentFrame          , METH_VARARGS, ""},
        {   "setInvisible"               , (PyCFunction)pyBOCompositedModel3d_setInvisible             , METH_VARARGS, ""},
        {NULL, NULL, 0, NULL} /* Sentinel */
    };


    

    static PyTypeObject pyBOCompositedModel3d_type = {
        PyObject_HEAD_INIT(NULL)
        0,
        "BOCompositedModel3d",
        sizeof(pyBOCompositedModel3d),        /*tp_basicsize*/
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
        "BOCompositedModel3d maratis object", /* tp_doc */
        0,                         /* tp_traverse */
        0,                         /* tp_clear */
        0,                         /* tp_richcompare */
        0,                         /* tp_weaklistoffset */
        0,                         /* tp_iter */
        0,                         /* tp_iternext */
        pyBOCompositedModel3d_methods,        /* tp_methods */
        0,                         /* tp_members */
        0,                         /* tp_getset */
        0,                         /* tp_base */
        0,                         /* tp_dict */
        0,                         /* tp_descr_get */
        0,                         /* tp_descr_set */
        0,                         /* tp_dictoffset */
        0,                         /* tp_init */
        0,                         /* tp_alloc */
        0,             /* tp_new */

    };
#endif