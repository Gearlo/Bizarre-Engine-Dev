#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>
//#include <MWindow.h>
#include <ULog.h>
//#include <MGameWinEvents.h>


#ifndef _PY_M_PHYSICS_PROPIERTIES_TYPE
#define _PY_M_PHYSICS_PROPIERTIES_TYPE

   
typedef struct {
    PyObject_HEAD
    BPhysicsProperties * phy = NULL;
} pyBPhysicsProperties;


static PyObject * pyBPhysicsProperties_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    BPhysicsProperties *self;
    self = (BPhysicsProperties *)type->tp_alloc(type, 0);
    if (self == NULL){
        Py_RETURN_NONE;
    }
    
    return (PyObject *)self;
    
}

static PyObject* pyBPhysicsProperties_getAngularDamping(pyBPhysicsProperties *self){
    return Py_BuildValue("f",self->phy->getAngularDamping());
}

static PyObject* pyBPhysicsProperties_getAngularFactor(pyBPhysicsProperties *self){
    return Py_BuildValue("f",self->phy->getAngularFactor());
}

static PyObject* pyBPhysicsProperties_getCollisionObjectId(pyBPhysicsProperties *self){
    return Py_BuildValue("I",self->phy->getCollisionObjectId());
}

static PyObject* pyBPhysicsProperties_getCollisionShape(pyBPhysicsProperties *self){
    U_COLLISION_SHAPE_TYPE shape = self->phy->getCollisionShape();
    switch(shape){
        case U_COLLISION_SHAPE_BOX:
            return Py_BuildValue("s","box");
            break;
        case U_COLLISION_SHAPE_SPHERE:
            return Py_BuildValue("s","sphere");
            break;
        case U_COLLISION_SHAPE_CONE:
            return Py_BuildValue("s","cone");
            break;
        case U_COLLISION_SHAPE_CAPSULE:
            return Py_BuildValue("s","capsule");
            break;
        case U_COLLISION_SHAPE_CYLINDER:
            return Py_BuildValue("s","cylinder");
            break;
        case U_COLLISION_SHAPE_CONVEX_HULL:
            return Py_BuildValue("s","convex_hull");
            break;
        case U_COLLISION_SHAPE_TRIANGLE_MESH:
            return Py_BuildValue("s","triangle_mesh"); 
            break;
    }
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_getFriction(pyBPhysicsProperties *self){
    return Py_BuildValue("f",self->phy->getFriction());
}

static PyObject* pyBPhysicsProperties_getLinearDamping(pyBPhysicsProperties *self){
    return Py_BuildValue("f",self->phy->getLinearDamping());
}

static PyObject* pyBPhysicsProperties_getLinearFactor(pyBPhysicsProperties *self){
    pyUVector3* factor = PyObject_New(pyUVector3, &pyUVector3_type);
    BVector3f* temp = self->phy->getLinearFactor();
    factor->vector = BVector3f(temp->x, temp->y, temp->z);
    return (PyObject*)factor;
}

static PyObject* pyBPhysicsProperties_getMass(pyBPhysicsProperties *self){
    return Py_BuildValue("f",self->phy->getMass());
}

static PyObject* pyBPhysicsProperties_getRestitution(pyBPhysicsProperties *self){
    return Py_BuildValue("f",self->phy->getRestitution());
}

static PyObject* pyBPhysicsProperties_getShapeId(pyBPhysicsProperties *self){
    return Py_BuildValue("I",self->phy->getShapeId());
}

static PyObject* pyBPhysicsProperties_isGhost(pyBPhysicsProperties *self){
    return Py_BuildValue("b",self->phy->isGhost());
}

static PyObject* pyBPhysicsProperties_setAngularDamping(pyBPhysicsProperties *self, PyObject* args){
    float value;
    if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setAngularDamping(<float>value)");
            return NULL;
    }
    self->phy->setAngularDamping(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setAngularFactor(pyBPhysicsProperties *self, PyObject* args){
    float value;
    if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setAngularFactor(<float>value)");
            return NULL;
    }
    self->phy->setAngularFactor(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setCollisionObjectId(pyBPhysicsProperties *self, PyObject* args){
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setCollisionObjectId(<int>value)");
            return NULL;
    }
    self->phy->setCollisionObjectId(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setCollisionShape(pyBPhysicsProperties* self,  PyObject* args)
    {
        char* text;
        if (!PyArg_ParseTuple(args, "s", &text)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setCollisionShape(<string>shapeName)");
            return NULL;   
        }
       
        if (strcmp("box", text) == 0){
            self->phy->setCollisionShape(U_COLLISION_SHAPE_BOX);
        }else if (strcmp("sphere", text) == 0){
            self->phy->setCollisionShape(U_COLLISION_SHAPE_SPHERE);
        }else if (strcmp("cone", text) == 0){
            self->phy->setCollisionShape(U_COLLISION_SHAPE_CONE);
        }else if (strcmp("capsule", text) == 0){
            self->phy->setCollisionShape(U_COLLISION_SHAPE_CAPSULE);
        }else if (strcmp("cylinder", text) == 0){
            self->phy->setCollisionShape(U_COLLISION_SHAPE_CYLINDER);
        }else if (strcmp("convex_hull", text) == 0){
            self->phy->setCollisionShape(U_COLLISION_SHAPE_CONVEX_HULL);
        }else if (strcmp("triangle_mesh", text) == 0){
            self->phy->setCollisionShape(U_COLLISION_SHAPE_TRIANGLE_MESH);
        }else{
            self->phy->setCollisionShape(U_COLLISION_SHAPE_BOX);
        }
        Py_RETURN_NONE;
    }

static PyObject* pyBPhysicsProperties_setFriction(pyBPhysicsProperties *self, PyObject* args){
    float value;
    if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setFriction(<float>value)");
            return NULL;
    }
    self->phy->setFriction(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setGhost(pyBPhysicsProperties *self, PyObject* args){
    bool value;
    if (!PyArg_ParseTuple(args, "b",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setGhost(<bool>ghost)");
            return NULL;
    }
    self->phy->setGhost(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setLinearDamping(pyBPhysicsProperties *self, PyObject* args){
    float value;
    if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setLinearDamping(<float>value)");
            return NULL;
    }
    self->phy->setLinearDamping(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setLinearFactor(pyBPhysicsProperties *self, PyObject* args){
    float x;
    float y;
    float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * factor;
        if (PyArg_ParseTuple(args, "O", &factor)){
            PyErr_Clear();
            self->phy->setLinearFactor(factor->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setLinearFactor(<float>x, <float>y, <float>z) or setLinearFactor(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        self->phy->setLinearFactor(BVector3f(x,y,z));
    }
        Py_RETURN_NONE; 
}

static PyObject* pyBPhysicsProperties_setMass(pyBPhysicsProperties *self, PyObject* args){
    float value;
    if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setMass(<float>value)");
            return NULL;
    }
    self->phy->setMass(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setRestitution(pyBPhysicsProperties *self, PyObject* args){
    float value;
    if (!PyArg_ParseTuple(args, "f",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setRestitution(<float>value)");
            return NULL;
    }
    self->phy->setRestitution(value);
    Py_RETURN_NONE;
}

static PyObject* pyBPhysicsProperties_setShapeId(pyBPhysicsProperties *self, PyObject* args){
    unsigned int value;
    if (!PyArg_ParseTuple(args, "I",&value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setShapeId(<int>value)");
            return NULL;
    }
    self->phy->setShapeId(value);
    Py_RETURN_NONE;
}

static PyMethodDef pyBPhysicsProperties_methods[] = {
    {   "getAngularDamping"      , (PyCFunction)pyBPhysicsProperties_getAngularDamping      , METH_NOARGS , ""},
    {   "getAngularFactor"       , (PyCFunction)pyBPhysicsProperties_getAngularFactor       , METH_NOARGS , ""},
    {   "getCollisionObjectId"   , (PyCFunction)pyBPhysicsProperties_getCollisionObjectId   , METH_NOARGS , ""},
    {   "getCollisionShape"      , (PyCFunction)pyBPhysicsProperties_getCollisionShape      , METH_NOARGS , ""},
    {   "getFriction"            , (PyCFunction)pyBPhysicsProperties_getFriction            , METH_NOARGS , ""},
    {   "getLinearDamping"       , (PyCFunction)pyBPhysicsProperties_getLinearDamping       , METH_NOARGS , ""},
    {   "getLinearFactor"        , (PyCFunction)pyBPhysicsProperties_getLinearFactor        , METH_NOARGS , ""},
    {   "getMass"                , (PyCFunction)pyBPhysicsProperties_getMass                , METH_NOARGS , ""},
    {   "getRestitution"         , (PyCFunction)pyBPhysicsProperties_getRestitution         , METH_NOARGS , ""},
    {   "getShapeId"             , (PyCFunction)pyBPhysicsProperties_getShapeId             , METH_NOARGS , ""},
    {   "isGhost"                , (PyCFunction)pyBPhysicsProperties_isGhost                , METH_NOARGS , ""},
    {   "setAngularDamping"      , (PyCFunction)pyBPhysicsProperties_setAngularDamping      , METH_VARARGS , ""},
    {   "setAngularFactor"       , (PyCFunction)pyBPhysicsProperties_setAngularFactor       , METH_VARARGS , ""},
    {   "setCollisionObjectId"   , (PyCFunction)pyBPhysicsProperties_setCollisionObjectId   , METH_VARARGS , ""},
    {   "setCollisionShape"      , (PyCFunction)pyBPhysicsProperties_setCollisionShape      , METH_VARARGS , ""},
    {   "setFriction"            , (PyCFunction)pyBPhysicsProperties_setFriction            , METH_VARARGS , ""},
    {   "setGhost"               , (PyCFunction)pyBPhysicsProperties_setGhost               , METH_VARARGS , ""},
    {   "setLinearDamping"       , (PyCFunction)pyBPhysicsProperties_setLinearDamping       , METH_VARARGS , ""},
    {   "setLinearFactor"        , (PyCFunction)pyBPhysicsProperties_setLinearFactor        , METH_VARARGS , ""},
    {   "setMass"                , (PyCFunction)pyBPhysicsProperties_setMass                , METH_VARARGS , ""},
    {   "setRestitution"         , (PyCFunction)pyBPhysicsProperties_setRestitution         , METH_VARARGS , ""},
    {   "setShapeId"             , (PyCFunction)pyBPhysicsProperties_setShapeId             , METH_VARARGS , ""},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyBPhysicsProperties_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BPhysicsProperties",
    sizeof(pyBPhysicsProperties),  /*tp_basicsize*/
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
    "BPhysicsProperties maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBPhysicsProperties_methods,        /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyBPhysicsProperties_new,             /* tp_new */

};
#endif