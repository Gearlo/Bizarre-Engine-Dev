#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>
//#include <MWindow.h>
#include <ULog.h>
//#include <MGameWinEvents.h>


#ifndef _PY_M_PHYSICS_CONTEXT_TYPE
#define _PY_M_PHYSICS_CONTEXT_TYPE

   
typedef struct {
    PyObject_HEAD
    BPhysicsContext * phy = NULL;
} pyBPhysicsContext;


static PyObject * pyBPhysicsContext_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBPhysicsContext *self;
    self = (pyBPhysicsContext *)type->tp_alloc(type, 0);
    if (self == NULL){
        Py_RETURN_NONE;
    }
    self->phy = Bizarre::getInstance()->getPhysicsContext();
    return (PyObject *)self;
    
}

static PyObject* pyBPhysicsContext_activateObject(pyBPhysicsContext* self, PyObject* args)
    {
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: activateObject(<int>objectId)");
            return NULL;   
    }else{
        self->phy->activateObject(value);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBPhysicsContext_addCentralForce(pyBPhysicsContext* self, PyObject* args){
    float x;
    float y;
    float z;
    unsigned int id;
    if (!PyArg_ParseTuple(args, "I(fff)", &id , &x, &y, &z)){
        pyUVector3 * force;
        if (PyArg_ParseTuple(args, "IO",&id,  &force )){
            PyErr_Clear();
            self->phy->addCentralForce(id, force->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: addCentralForce( <int>ObjectId, (<float>x, <float>y, <float>z)) or addCentralForce(<int>ObjectId, <BVector3f>force)");
            return NULL;
        }
    }else{
        self->phy->addCentralForce(id, BVector3f(x,y,z));
    }
        Py_RETURN_NONE; 

}

static PyObject* pyBPhysicsContext_addTorque(pyBPhysicsContext* self, PyObject* args){
    float x;
    float y;
    float z;
    unsigned int id;
    if (!PyArg_ParseTuple(args, "I(fff)", &id , &x, &y, &z)){
        pyUVector3 * force;
        if (PyArg_ParseTuple(args, "IO",&id,  &force )){
            PyErr_Clear();
            self->phy->addTorque(id, force->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: addTorque( <int>ObjectId, (<float>x, <float>y, <float>z)) or addTorque(<int>ObjectId, <BVector3f>torque)");
            return NULL;
        }
    }else{
        self->phy->addTorque(id, BVector3f(x,y,z));
    }
        Py_RETURN_NONE;

}

static PyObject* pyBPhysicsContext_clearForces(pyBPhysicsContext* self, PyObject* args)
    {
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: clearForces(<int>objectId)");
            return NULL;   
    }else{
        self->phy->clearForces(value);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBPhysicsContext_deactivateObject(pyBPhysicsContext* self, PyObject* args)
    {
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: deactivateObject(<int>objectId)");
            return NULL;   
    }else{
        self->phy->deactivateObject(value);
    }
        Py_RETURN_NONE;  
}

static PyObject* pyBPhysicsContext_disableObjectKinematic(pyBPhysicsContext* self, PyObject* args)
    {
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: disableObjectKinematic(<int>objectId)");
            return NULL;   
    }else{
        self->phy->disableObjectKinematic(value);
    }
        Py_RETURN_NONE;
}

static PyObject* pyBPhysicsContext_enableObjectKinematic(pyBPhysicsContext* self, PyObject* args)
    {
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: enableObjectKinematic(<int>objectId)");
            return NULL;   
    }else{
        self->phy->enableObjectKinematic(value);
    }
        Py_RETURN_NONE;
}

static PyObject* pyBPhysicsContext_getCentralForce(pyBPhysicsContext* self, PyObject* args)
{
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: getCentralForce(<int>objectId)");
            return NULL;   
    }else{
        BVector3f * v;
        self->phy->getCentralForce(value, v);
        pyUVector3* v2 = PyObject_New(pyUVector3, &pyUVector3_type);
        v2->vector = BVector3f(v->x, v->y, v->z);
        return (PyObject*)v2;
    }
    
}

static PyObject* pyBPhysicsContext_getTorque(pyBPhysicsContext* self, PyObject* args)
{
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: getTorque(<int>objectId)");
            return NULL;   
    }else{
        BVector3f * v;
        self->phy->getTorque(value, v);
        pyUVector3* v2 = PyObject_New(pyUVector3, &pyUVector3_type);
        v2->vector = BVector3f(v->x, v->y, v->z);
        return (PyObject*)v2;
    }
    
}

static PyObject* pyBPhysicsContext_isObjectsCollision(pyBPhysicsContext* self, PyObject* args)
{
    unsigned int id_1; unsigned int id_2; 
    if (!PyArg_ParseTuple(args, "II", &id_1, &id_2)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: isObjectsCollision(<int>objectId1, <int>objectId2)");
            return NULL;   
    }else{
        return Py_BuildValue("b",self->phy->isObjectsCollision(id_1 , id_2));
    }
}


static PyObject* pyBPhysicsContext_setObjectAngularFactor(pyBPhysicsContext* self, PyObject* args)
{
    
    
    unsigned int Id ;float factor;
    if (!PyArg_ParseTuple(args, "If", &Id, &factor)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setObjectAngularFactor(<int>objectId, <float>factor)");
    }else{
        self->phy->setObjectAngularFactor(Id, factor);
    }
        Py_RETURN_NONE;
}


static PyObject* pyBPhysicsContext_setSimulationQuality(pyBPhysicsContext* self, PyObject* args)
    {
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setSimulationQuality(<int>quality)");
            return NULL;   
    }else{
        self->phy->setSimulationQuality(value);
    }
        Py_RETURN_NONE;
}

static PyObject* pyBPhysicsContext_setWorldGravity(pyBPhysicsContext* self, PyObject* args)
{
    float x; float y; float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * g;
        if (PyArg_ParseTuple(args, "O", &g)){
            PyErr_Clear();
            self->phy->setWorldGravity(g->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setWorldGravity(<float>r, <float>g, <float>b) or setWorldGravity(<BVector3f>color)");
            return NULL;
        }
    }else{
       self->phy->setWorldGravity(BVector3f(x,y,z)); 
    }
        Py_RETURN_NONE;
}


static PyMethodDef pyBPhysicsContext_methods[] = {
    {   "activateObject"         , (PyCFunction)pyBPhysicsContext_activateObject           , METH_VARARGS , ""},
    {   "addCentralForce"        , (PyCFunction)pyBPhysicsContext_addCentralForce          , METH_VARARGS , ""},
    {   "addTorque"              , (PyCFunction)pyBPhysicsContext_addTorque                , METH_VARARGS , ""},
    {   "clearForces"            , (PyCFunction)pyBPhysicsContext_clearForces              , METH_VARARGS , ""},
    {   "deactivateObject"       , (PyCFunction)pyBPhysicsContext_deactivateObject         , METH_VARARGS , ""},
    {   "disableObjectKinematic" , (PyCFunction)pyBPhysicsContext_disableObjectKinematic   , METH_VARARGS , ""},
    {   "enableObjectKinematic"  , (PyCFunction)pyBPhysicsContext_enableObjectKinematic    , METH_VARARGS , ""},
    {   "getCentralForce"        , (PyCFunction)pyBPhysicsContext_getCentralForce          , METH_VARARGS , ""},
    {   "getTorque"              , (PyCFunction)pyBPhysicsContext_getTorque                , METH_VARARGS , ""},
    {   "isObjectsCollision"     , (PyCFunction)pyBPhysicsContext_isObjectsCollision       , METH_VARARGS , ""},
    {   "setObjectAngularFactor"   , (PyCFunction)pyBPhysicsContext_setObjectAngularFactor     , METH_VARARGS , ""},
    {   "setSimulationQuality"   , (PyCFunction)pyBPhysicsContext_setSimulationQuality     , METH_VARARGS , ""},
    {   "setWorldGravity"        , (PyCFunction)pyBPhysicsContext_setWorldGravity          , METH_VARARGS , ""},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyBPhysicsContext_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BPhysicsContext",
    sizeof(pyBPhysicsContext),  /*tp_basicsize*/
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
    "BPhysicsContext maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBPhysicsContext_methods,        /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyBPhysicsContext_new,             /* tp_new */

};
#endif