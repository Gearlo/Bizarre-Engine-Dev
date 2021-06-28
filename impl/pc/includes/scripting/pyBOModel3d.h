
#ifndef _PY_M_OENTITY
#define _PY_M_OENTITY

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>


#include "pyBObject3d.h"
#include "pyBPhysicsProperties.h"
#include "pyBMeshRef.h"
#include "pyBMesh.h"

    typedef struct {
        pyBObject3d obj;
        BOModel3d * model;
    } pyBOModel3d;
    
    
    static PyObject* pyBOModel3d_changeAnimation(pyBOModel3d* self, PyObject* args){
        unsigned int value;
        if (!PyArg_ParseTuple(args, "I",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: changeAnimation(<int>animationId)");
            return NULL;
        }
        self->model->changeAnimation(value);
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBOModel3d_createPhysicsProperties(pyBOModel3d* self)
    {
        pyBPhysicsProperties* phy = PyObject_New(pyBPhysicsProperties, &pyBPhysicsProperties_type);
        phy->phy = self->model->createPhysicsProperties();
        return (PyObject*)phy;
    }
    
    static PyObject* pyBOModel3d_deletePhysicsProperties(pyBOModel3d *self){
        self->model->deletePhysicsProperties();
        Py_RETURN_NONE;
        
    }
  
    static PyObject* pyBOModel3d_getAnimationId(pyBOModel3d *self){
        return Py_BuildValue("I",self->model->getAnimationId());
    }
    
    static PyObject* pyBOModel3d_getAnimationSpeed(pyBOModel3d *self){
        return Py_BuildValue("f",self->model->getAnimationSpeed());
    }
    
    static PyObject* pyBOModel3d_getCurrentFrame(pyBOModel3d *self){
        return Py_BuildValue("f",self->model->getCurrentFrame());
    }
    
    static PyObject* pyBOModel3d_getMesh(pyBOModel3d* self)
    {
        pyBMesh* msr = PyObject_New(pyBMesh, &pyBMesh_type);
        msr->mesh = self->model->getMesh();
        return (PyObject*)msr;  
    }
    
    static PyObject* pyBOModel3d_getMeshRef(pyBOModel3d* self)
    {
        pyBMeshRef* msr = PyObject_New(pyBMeshRef, &pyBMeshRef_type);
        msr->meshRef = self->model->getMeshRef();
        return (PyObject*)msr;  
    } 
    
    static PyObject* pyBOModel3d_getPhysicsProperties(pyBOModel3d* self)
    {
        pyBPhysicsProperties* phy = PyObject_New(pyBPhysicsProperties, &pyBPhysicsProperties_type);
        phy->phy = self->model->getPhysicsProperties();
        if(phy->phy){
            return (PyObject*)phy;
        }else{
            Py_RETURN_NONE;
        }
        
    }
    
    static PyObject* pyBOModel3d_isAnimationOver(pyBOModel3d *self){
        return Py_BuildValue("b",self->model->isAnimationOver());
    }
    
    static PyObject* pyBOModel3d_setAnimationSpeed(pyBOModel3d* self, PyObject* args){
        float value;
        if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setAnimationSpeed(<float>speed)");
            return NULL;
        }
        self->model->setAnimationSpeed(value);
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBOModel3d_setCurrentFrame(pyBOModel3d* self, PyObject* args){
        float value;
        if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setCurrentFrame(<float>value)");
            return NULL;
        }
        self->model->setCurrentFrame(value);
        Py_RETURN_NONE;
    }
    
    
    static PyObject* pyBOModel3d_setMeshRef(pyBOModel3d* self, PyObject* args)
    {
        pyBMeshRef* fr;
        if (PyArg_ParseTuple(args, "O", &fr)){
            self->model->setMeshRef(fr->meshRef);
            Py_RETURN_NONE;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setMeshRef(<BMeshRef>meshRef)");
            return NULL;
        } 
    }
    
    static PyObject* pyBOModel3d_setInvisible(pyBOModel3d* self, PyObject* args)
    {
        bool visible;
        if (!PyArg_ParseTuple(args, "b", &visible)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setInvisible(<bool>visible)");
            return NULL;  
        }else{
            self->model->setInvisible(visible);
        }
            Py_RETURN_NONE;    
        
    }
    
    static PyMethodDef pyBOModel3d_methods[] = {
        {   "changeAnimation"            , (PyCFunction)pyBOModel3d_changeAnimation          , METH_VARARGS, ""},
        {   "createPhysicsProperties"    , (PyCFunction)pyBOModel3d_createPhysicsProperties  , METH_NOARGS, ""},
        {   "deletePhysicsProperties"    , (PyCFunction)pyBOModel3d_deletePhysicsProperties  , METH_NOARGS, ""},
        {   "getAnimationId"             , (PyCFunction)pyBOModel3d_getAnimationId           , METH_NOARGS, ""},
        {   "getAnimationSpeed"          , (PyCFunction)pyBOModel3d_getAnimationSpeed        , METH_NOARGS, ""},
        {   "getCurrentFrame"            , (PyCFunction)pyBOModel3d_getCurrentFrame          , METH_NOARGS, ""},
        {   "getMesh"                    , (PyCFunction)pyBOModel3d_getMesh                  , METH_NOARGS, ""},
        {   "getMeshRef"                 , (PyCFunction)pyBOModel3d_getMeshRef               , METH_NOARGS, ""},
        {   "getPhysicsProperties"       , (PyCFunction)pyBOModel3d_getPhysicsProperties     , METH_NOARGS, ""},
        {   "isAnimationOver"            , (PyCFunction)pyBOModel3d_isAnimationOver          , METH_NOARGS, ""},
        {   "setAnimationSpeed"          , (PyCFunction)pyBOModel3d_setAnimationSpeed        , METH_VARARGS, ""},
        {   "setCurrentFrame"            , (PyCFunction)pyBOModel3d_setCurrentFrame          , METH_VARARGS, ""},
        {   "setInvisible"               , (PyCFunction)pyBOModel3d_setInvisible             , METH_VARARGS, ""},
        {   "setMeshRef"                 , (PyCFunction)pyBOModel3d_setMeshRef               , METH_VARARGS, ""},
        {NULL, NULL, 0, NULL} /* Sentinel */
    };

    
    static PyTypeObject pyBOModel3d_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BOModel3d",
    sizeof(pyBOModel3d),        /*tp_basicsize*/
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
    "BOModel3d maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBOModel3d_methods,        /* tp_methods */
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