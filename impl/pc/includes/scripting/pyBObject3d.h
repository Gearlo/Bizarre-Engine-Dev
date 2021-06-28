

#ifndef _PYMOBJECT
#define _PYMOBJECT

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#include "pyUVector.h"

//#define PI 3.14159265359

typedef struct {
    PyObject_HEAD
    BObject3d * object = NULL;
} pyBObject3d;   

static PyObject * pyBObject3d_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBObject3d* self;
    self = (pyBObject3d *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        /// INICIALIZACION AQUI
    }else{
        Py_RETURN_NONE;
    }
    
    return (PyObject *)self;
}


static void pyBObject3d_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


static PyObject* pyBObject3d_addAxisAngleRotation(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    float value;
    if (!PyArg_ParseTuple(args, "(fff)f", &x, &y, &z, &value)){
        pyUVector3 * rot;
        if (PyArg_ParseTuple(args, "Of", &rot, &value)){
            PyErr_Clear();
            self->object->addAxisAngleRotation(rot->vector, value);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: addAxisAngleRotation((<float>x, <float>y, <float>z), <float>angle) or addAxisAngleRotation(<BVector3f>rotation, <float>angle)");
            return NULL;
        }
    }else{
        self->object->addAxisAngleRotation(BVector3f(x,y,z), value);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBObject3d_getEulerRotation(pyBObject3d* self)
{
    pyUVector3* rot = PyObject_New(pyUVector3, &pyUVector3_type);
    rot->vector = self->object->getEulerRotation();
    return (PyObject*)rot;
}

static PyObject* pyBObject3d_getInversePosition(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * v;
        if (PyArg_ParseTuple(args, "O", &v)){
            PyErr_Clear();
        scl->vector = self->object->getInversePosition(v->vector);
        return (PyObject*)scl;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: getInversePosition(<float>x, <float>y, <float>z) or getInversePosition(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        scl->vector = self->object->getInversePosition(BVector3f(x,y,z));
        return (PyObject*)scl;
    }      
}

static PyObject* pyBObject3d_getInverseRotatedVector(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * v;
        if (PyArg_ParseTuple(args, "O", &v)){
            PyErr_Clear();
        scl->vector = self->object->getInverseRotatedVector(v->vector);
        return (PyObject*)scl;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: getInverseRotatedVector(<float>x, <float>y, <float>z) or getInverseRotatedVector(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        scl->vector = self->object->getInverseRotatedVector(BVector3f(x,y,z));
        return (PyObject*)scl;
    }      
}

static PyObject* pyBObject3d_getRotatedVector(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * v;
        if (PyArg_ParseTuple(args, "O", &v)){
            PyErr_Clear();
        scl->vector = self->object->getRotatedVector(v->vector);
        return (PyObject*)scl;
        }else{
            return NULL;
        }
    }else{
        scl->vector = self->object->getRotatedVector(BVector3f(x,y,z));
        return (PyObject*)scl;
    }      
}

static PyObject* pyBObject3d_getName(pyBObject3d* self)
{
    return Py_BuildValue("s",self->object->getName());
}


static PyObject* pyBObject3d_getPosition(pyBObject3d* self)
{
    pyUVector3* pos = PyObject_New(pyUVector3, &pyUVector3_type);
    pos->vector = self->object->getPosition();
    return (PyObject*)pos;
}


static PyObject* pyBObject3d_getScale(pyBObject3d* self)
{
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    scl->vector = self->object->getScale();
    return (PyObject*)scl;
}

static PyObject* pyBObject3d_getTransformedPosition(pyBObject3d* self)
{
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    scl->vector = self->object->getTransformedPosition();
    return (PyObject*)scl;
}

static PyObject* pyBObject3d_getTransformedRotation(pyBObject3d* self)
{
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    scl->vector = self->object->getTransformedRotation();
    return (PyObject*)scl;
}

static PyObject* pyBObject3d_getTransformedScale(pyBObject3d* self)
{
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    scl->vector = self->object->getTransformedScale();
    return (PyObject*)scl;
}


static PyObject* pyBObject3d_getTransformedVector(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    pyUVector3* scl = PyObject_New(pyUVector3, &pyUVector3_type);
    
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * v;
        if (PyArg_ParseTuple(args, "O", &v)){
            PyErr_Clear();
        scl->vector = self->object->getTransformedVector(v->vector);
        return (PyObject*)scl;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: getTransformedVector(<float>x, <float>y, <float>z) or getTransformedVector(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        scl->vector = self->object->getTransformedVector(BVector3f(x,y,z));
        return (PyObject*)scl;
    }      
}


static PyObject* pyBObject3d_isVisible(pyBObject3d* self)
{
    return Py_BuildValue("b",self->object->isVisible());  
}

static PyObject* pyBObject3d_isActive(pyBObject3d* self)
{
    return Py_BuildValue("b",self->object->isActive());
}


static PyObject* pyBObject3d_setActive(pyBObject3d* self, PyObject* args)
{
    bool active;
    if (!PyArg_ParseTuple(args, "b", &active)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setActive(<bool>active)");
        return NULL;  
    }else{
        self->object->setActive(active);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBObject3d_setAxisAngleRotation(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    float value;
    if (!PyArg_ParseTuple(args, "(fff)f", &x, &y, &z, &value)){
        pyUVector3 * rot;
        if (PyArg_ParseTuple(args, "Of", &rot, &value)){
            PyErr_Clear();
            self->object->setAxisAngleRotation(rot->vector, value);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setAxisAngleRotation((<float>x, <float>y, <float>z), <float>angle) or setAxisAngleRotation(<BVector3f>rotation, <float>angle)");
            return NULL;
        }
    }else{
        self->object->setAxisAngleRotation(BVector3f(x,y,z), value);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBObject3d_setEulerRotation(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * rot;
        if (PyArg_ParseTuple(args, "O", &rot)){
            PyErr_Clear();
            self->object->setEulerRotation(rot->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setEulerRotation(<float>x, <float>y, <float>z) or setEulerRotation(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        self->object->setEulerRotation(BVector3f(x,y,z));
    }
        Py_RETURN_NONE;       
}


static PyObject* pyBObject3d_setName(pyBObject3d* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setName(<string>Name)");
        return NULL;  
    }else{
        self->object->setName(name);
    }
        Py_RETURN_NONE;
        
}


static PyObject* pyBObject3d_setPosition(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * pos;
        if (PyArg_ParseTuple(args, "O", &pos)){
            PyErr_Clear();
            self->object->setPosition(pos->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setPosition(<float>x, <float>y, <float>z) or setEulerRotation(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        self->object->setPosition(BVector3f(x,y,z));
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBObject3d_setScale(pyBObject3d* self, PyObject* args)
{
    float x;
    float y;
    float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * scl;
        if (PyArg_ParseTuple(args, "O", &scl)){
            PyErr_Clear();
            self->object->setScale(scl->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setScale(<float>x, <float>y, <float>z) or setEulerRotation(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        self->object->setScale(BVector3f(x,y,z));
    }
        Py_RETURN_NONE;
}

static PyObject* pyBObject3d_setVisible(pyBObject3d* self, PyObject* args)
{
    bool visible;
    if (!PyArg_ParseTuple(args, "b", &visible)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setVisible(<bool>visible)");
        return NULL;  
    }else{
        self->object->setVisible(visible);
    }
        Py_RETURN_NONE;    
        
}

static PyObject* pyBObject3d_load(pyBObject3d* self)
{
    self->object->load();
    Py_RETURN_NONE;
}



static PyMethodDef pyBObject3d_methods[] = {
    {     "addAxisAngleRotation"  ,    (PyCFunction)pyBObject3d_addAxisAngleRotation     , METH_VARARGS     ,   ""   },
    {      "getEulerRotation"     ,    (PyCFunction)pyBObject3d_getEulerRotation         , METH_NOARGS      ,   ""   },
    {   "getInverseRotatedVector" ,    (PyCFunction)pyBObject3d_getInverseRotatedVector  , METH_VARARGS     ,   ""   },
    {     "getInversePosition"    ,    (PyCFunction)pyBObject3d_getInversePosition       , METH_VARARGS     ,   ""   },
    {         "getName"           ,    (PyCFunction)pyBObject3d_getName                  , METH_NOARGS      ,   ""   },
    {       "getPosition"         ,    (PyCFunction)pyBObject3d_getPosition              , METH_NOARGS      ,   ""   },
    {        "getScale"           ,    (PyCFunction)pyBObject3d_getScale                 , METH_NOARGS      ,   ""   },
    {     "getRotatedVector"      ,    (PyCFunction)pyBObject3d_getRotatedVector         , METH_VARARGS     ,   ""   },
    {   "getTransformedPosition"  ,    (PyCFunction)pyBObject3d_getTransformedPosition   , METH_NOARGS      ,   ""   },
    {   "getTransformedRotation"  ,    (PyCFunction)pyBObject3d_getTransformedRotation   , METH_NOARGS      ,   ""   },
    {     "getTransformedScale"   ,    (PyCFunction)pyBObject3d_getTransformedScale      , METH_NOARGS      ,   ""   },
    {     "getTransformedVector"  ,    (PyCFunction)pyBObject3d_getTransformedVector     , METH_VARARGS     ,   ""   },
    {        "isActive"           ,    (PyCFunction)pyBObject3d_isActive                 , METH_NOARGS      ,   ""   },
    {        "isVisible"          ,    (PyCFunction)pyBObject3d_isVisible                , METH_NOARGS      ,   ""   },
    {        "setActive"          ,    (PyCFunction)pyBObject3d_setActive                , METH_VARARGS     ,   ""   },
    {     "setAxisAngleRotation"  ,    (PyCFunction)pyBObject3d_setAxisAngleRotation     , METH_VARARGS     ,   ""   },
    {     "setEulerRotation"      ,    (PyCFunction)pyBObject3d_setEulerRotation         , METH_VARARGS     ,   ""   },
    {         "setName"           ,    (PyCFunction)pyBObject3d_setName                  , METH_VARARGS     ,   ""   },
    {        "setPosition"        ,    (PyCFunction)pyBObject3d_setPosition              , METH_VARARGS     ,   ""   },
    {         "setScale"          ,    (PyCFunction)pyBObject3d_setScale                 , METH_VARARGS     ,   ""   },
    {        "setVisible"         ,    (PyCFunction)pyBObject3d_setVisible               , METH_VARARGS     ,   ""   },
    {          "load"             ,    (PyCFunction)pyBObject3d_load                     , METH_NOARGS      ,   ""   },
    {           NULL              ,                       NULL                           , 0                ,  NULL  } /* Sentinel */
};


static PyTypeObject pyBObject3d_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BObject3d",
    sizeof(pyBObject3d),       /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBObject3d_dealloc,/*tp_dealloc*/
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
    "BObject3d maratis object",   /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBObject3d_methods,                         /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyBObject3d_new,              /* tp_new */

};
#endif