#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#ifndef _PY_M_OCAMERA
#define _PY_M_OCAMERA

#include "pyBObject3d.h"

    typedef struct {
        pyBObject3d obj;
    } pyBOCamera;
   
    
    
    
#include <cstdlib>
#include <iostream>    

static PyObject* pyBOCamera_enable(pyBOCamera* self)
{
    ((BOCamera *)self->obj.object)->enable();
    Py_RETURN_NONE;
}
    
static void pyBOCamera_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

static PyObject* pyBOCamera_enableFog(pyBOCamera* self, PyObject* args)
{
    bool enable;
    if (!PyArg_ParseTuple(args, "b", &enable)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: enableFog(<bool>enable)");
        return NULL;

    }else{
        ((BOCamera *)self->obj.object)->enableFog(enable);
    }
    
        Py_RETURN_NONE;       
}
    
static PyObject* pyBOCamera_enableOrtho(pyBOCamera* self, PyObject* args)
{
    bool enable;
    if (!PyArg_ParseTuple(args, "b", &enable)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: enableOrtho(<bool>enable)");
        return NULL;

    }else{
        ((BOCamera *)self->obj.object)->enableOrtho(enable);
    }
        Py_RETURN_NONE;       
}


static PyObject* pyBOCamera_getFogDistance(pyBOCamera* self)
{
    return Py_BuildValue("f",((BOCamera *)self->obj.object)->getFogDistance()); 
}

static PyObject* pyBOCamera_getFov(pyBOCamera* self)
{
    return Py_BuildValue("f",((BOCamera *)self->obj.object)->getFov());  
}

static PyObject* pyBOCamera_getClearColor(pyBOCamera* self)
{
    pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
    color->vector = ((BOCamera *)self->obj.object)->getClearColor();
    return (PyObject*)color;
} 

static PyObject* pyBOCamera_getClippingFar(pyBOCamera* self)
{
    return Py_BuildValue("f",((BOCamera *)self->obj.object)->getClippingFar());  
}

static PyObject* pyBOCamera_getClippingNear(pyBOCamera* self)
{
    return Py_BuildValue("f",((BOCamera *)self->obj.object)->getClippingNear());  
}

static PyObject* pyBOCamera_getProjectedPoint(pyBOCamera* self, PyObject* args)
{
    pyUVector3* point = PyObject_New(pyUVector3, &pyUVector3_type);
    float x; float y; float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * in;
        if (PyArg_ParseTuple(args, "O", &in)){
            PyErr_Clear();
            point->vector = ((BOCamera *)self->obj.object)->getProjectedPoint(in->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: getProjectedPoint(<float>x, <float>y, <float>z) or getProjectedPoint(<BVector3f>point)");
            return NULL;
        }
    }else{
        point->vector = ((BOCamera *)self->obj.object)->getProjectedPoint(BVector3f(x,y,z));
    }
    return (PyObject*)point;
    
} 

static PyObject* pyBOCamera_getUnProjectedPoint(pyBOCamera* self, PyObject* args)
{
    pyUVector3* point = PyObject_New(pyUVector3, &pyUVector3_type);
    float x; float y; float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * in;
        if (PyArg_ParseTuple(args, "O", &in)){
            PyErr_Clear();
            point->vector = ((BOCamera *)self->obj.object)->getUnProjectedPoint(in->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: getUnProjectedPoint(<float>x, <float>y, <float>z) or getUnProjectedPoint(<BVector3f>point)");
            return NULL;
        }
    }else{
        point->vector = ((BOCamera *)self->obj.object)->getUnProjectedPoint(BVector3f(x,y,z));
    }
    return (PyObject*)point;
} 


static PyObject* pyBOCamera_getRelativeDisplace(pyBOCamera*  self, PyObject* args){
     BVector3f position;
     BVector3f displace;
     
    if (!PyArg_ParseTuple(args, "(fff)(ff)", &position.x, &position.y, &position.z, &displace.x, &displace.y  )){
        pyUVector3 * pyPosition;
        pyUVector2 * pyDisplace;
        if (PyArg_ParseTuple(args, "O!O!", &pyUVector3_type, &pyPosition, &pyUVector3_type, &pyDisplace)){
            PyErr_Clear();
            //shift = pos->vector;
            position = pyPosition->vector;
            displace = pyDisplace->vector;
        }else{
            return NULL;
        }
    }
     
    pyUVector2* relative = PyObject_New(pyUVector2, &pyUVector2_type);
    relative->vector = ((BOCamera *)self->obj.object)->getRelativeDisplace( position, displace );
    
    return (PyObject*)relative;
}

static PyObject* pyBOCamera_hasFog(pyBOCamera* self)
{
    return Py_BuildValue("b",((BOCamera *)self->obj.object)->hasFog());  
}

static PyObject* pyBOCamera_isOrtho(pyBOCamera* self)
{
    return Py_BuildValue("b",((BOCamera *)self->obj.object)->isOrtho());  
}


static PyObject* pyBOCamera_lookAt(pyBOCamera* self, PyObject* args)
{   
    
    BVector3f target;
    if (!PyArg_ParseTuple(args, "fff", &target.x, &target.y, &target.z)){
        pyUVector3 * pos;
        if (PyArg_ParseTuple(args, "O", &pos)){
            PyErr_Clear();
            target = pos->vector;
        }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: lookAt(<float>x, <float>y, <float>z) or lookAt(<BVector3f>targetPosition)");
                return NULL;
        }
    }
    
    BVector3f directionalVector = self->obj.object->getPosition() - target;
    BVector3f directionXY = directionalVector;
    directionXY.z = 0.0f;
    directionXY.normalize();
        
    BVector3f directionXYZ = directionalVector;
    directionXYZ.normalize();

    float Hangle = (180.0f * acos(directionXY.x))/PI;
    if(directionXY.y < 0.0f){ Hangle = 360.0f - Hangle; }
     
    float Vangle = (180.0f * acos(directionXYZ.z))/PI;
    
    self->obj.object->setEulerRotation(BVector3f(Vangle, 0.0f, Hangle + 90.0f));
    Py_RETURN_NONE;       
}


static PyObject* pyBOCamera_orbit(pyBOCamera* self, PyObject* args){
    
    BVector3f center;
    float angleShift;
    
    if (!PyArg_ParseTuple(args, "(fff)f", &center.x, &center.y, &center.z, &angleShift)){
        pyUVector3 centertmp;
        if (PyArg_ParseTuple(args, "O", &centertmp, &angleShift)){
            PyErr_Clear();
            center = centertmp.vector;
        }else{
                PyErr_SetString(PyExc_AttributeError, "parameters is: lookAt(<float>x, <float>y, <float>z) or lookAt(<BVector3f>targetPosition)");
                return NULL;
        }
        
    }
    

    BVector3f positionVector = self->obj.object->getPosition() - center;
    BVector3f finalPosition = BVector3f(0.0f, 0.0f, self->obj.object->getPosition().z);
    positionVector.z = 0.0f;
    float magnitude = positionVector.getLength();
    positionVector.normalize();
    
    float angle = acos(positionVector.x);
    if(positionVector.y < 0.0f)
        angle = 2*PI - angle;
    angle = angle + ( angleShift * PI/ 180.0f);
    finalPosition.x = cos(angle) * magnitude + center.x;
    finalPosition.y = sin(angle) * magnitude + center.y;
    self->obj.object->setPosition(finalPosition);
    
    Py_RETURN_NONE;
}


static PyObject* pyBOCamera_relativeHorizontalRotation(pyBOCamera* self, PyObject* args)
{
    
    BVector3f target_position;
    float target_localRotation = 0.0f;
    
    if (!PyArg_ParseTuple(args, "(fff)|f", &target_position.x, &target_position.y, &target_position.z, &target_localRotation)){
        pyUVector2 * position;
        if (PyArg_ParseTuple(args, "O|f", &position, &target_localRotation)){
            PyErr_Clear();
            target_position = position->vector;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: relativeHorizontalRotation((<float>x, <float>y, <float>z),<float>rotation ) or relativeHorizontalRotation(<BVector3f>position, <float>rotation )");
            return NULL;
        }
    }

    
    BVector3f relativeDirectionVector = target_position - self->obj.object->getPosition();
    relativeDirectionVector.z = 0.0f;
    relativeDirectionVector.normalize();
    
    float cameraAngle = acos(relativeDirectionVector.x);
    if(relativeDirectionVector.y < 0.0f){ cameraAngle = 2.0f*PI - cameraAngle; }
    
    pyUVector3* rotationVector = PyObject_New(pyUVector3, &pyUVector3_type);
    rotationVector->vector = BVector3f(0.0f, 0.0f, (180.0f*cameraAngle)/PI + target_localRotation);
    return (PyObject*)rotationVector;          
}


static PyObject* pyBOCamera_setClearColor(pyBOCamera* self, PyObject* args)
{
    float r; float g; float b;
    if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)){
        pyUVector3 * color;
        if (PyArg_ParseTuple(args, "O", &color)){
            PyErr_Clear();
            ((BOCamera *)self->obj.object)->setClearColor(color->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setClearColor(<float>r, <float>g, <float>b) or setClearColor(<BVector3f>color)");
            return NULL;
        }
    }else{
        ((BOCamera *)self->obj.object)->setClearColor(BVector3f(r,g,b));
    }
        Py_RETURN_NONE;       
}
    
static PyObject* pyBOCamera_setClippingFar(pyBOCamera* self, PyObject* args)
{
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setClippingFar(<float>value)");
            return NULL;   
    }else{
        ((BOCamera *)self->obj.object)->setClippingFar(value);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBOCamera_setClippingNear(pyBOCamera* self, PyObject* args)
{
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setClippingNear(<float>value)");
            return NULL;   
    }else{
        ((BOCamera *)self->obj.object)->setClippingNear(value);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBOCamera_setFogDistance(pyBOCamera* self, PyObject* args)
{
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setFogDistance(<float>value)");
            return NULL;   
    }else{
        ((BOCamera *)self->obj.object)->setFogDistance(value);
    }
        Py_RETURN_NONE;       
}

static PyObject* pyBOCamera_setFov(pyBOCamera* self, PyObject* args)
{
    float value;
    if (!PyArg_ParseTuple(args, "f", &value)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setFov(<float>value)");
            return NULL;   
    }else{
        ((BOCamera *)self->obj.object)->setFov(value);
    }
        Py_RETURN_NONE;       
}




static PyMethodDef pyBOCamera_methods[] = {
    {            "enable"       ,        (PyCFunction)pyBOCamera_enable              , METH_VARARGS     ,   ""   },
    {          "enableFog"      ,        (PyCFunction)pyBOCamera_enableFog           , METH_VARARGS     ,   ""   },
    {         "enableOrtho"     ,        (PyCFunction)pyBOCamera_enableOrtho         , METH_VARARGS     ,   ""   },
    {        "getClearColor"    ,        (PyCFunction)pyBOCamera_getClearColor       , METH_NOARGS      ,   ""   },
    {        "getClippingFar"   ,        (PyCFunction)pyBOCamera_getClippingFar      , METH_NOARGS      ,   ""   },
    {       "getClippingNear"   ,        (PyCFunction)pyBOCamera_getClippingNear     , METH_NOARGS      ,   ""   },
    {        "getFogDistance"   ,        (PyCFunction)pyBOCamera_getFogDistance      , METH_NOARGS      ,   ""   },
    {           "getFov"        ,        (PyCFunction)pyBOCamera_getFov              , METH_NOARGS      ,   ""   },
    {     "getUnProjectedPoint" ,        (PyCFunction)pyBOCamera_getUnProjectedPoint , METH_VARARGS     ,   ""   },
    {      "getProjectedPoint"  ,        (PyCFunction)pyBOCamera_getProjectedPoint   , METH_VARARGS     ,   ""   },
    {    "getRelativeDisplace"  ,        (PyCFunction)pyBOCamera_getRelativeDisplace , METH_VARARGS  , ""    },
    //{         "getSceneLayer"   ,        (PyCFunction)pyBOCamera_getSceneLayer       , METH_NOARGS      ,   ""   },
    {           "hasFog"        ,        (PyCFunction)pyBOCamera_hasFog              , METH_NOARGS      ,   ""   },
    {           "isOrtho"       ,        (PyCFunction)pyBOCamera_isOrtho             , METH_NOARGS      ,   ""   },
    {           "lookAt"        ,        (PyCFunction)pyBOCamera_lookAt              , METH_VARARGS     ,   ""   },
    {           "orbit"         ,        (PyCFunction)pyBOCamera_orbit               , METH_VARARGS     ,   ""   },
    { "relativeHorizontalRotation" ,     (PyCFunction)pyBOCamera_relativeHorizontalRotation , METH_VARARGS     ,   ""   },
    {        "setClearColor"    ,        (PyCFunction)pyBOCamera_setClearColor       , METH_VARARGS     ,   ""   },
    {        "setClippingFar"   ,        (PyCFunction)pyBOCamera_setClippingFar      , METH_VARARGS     ,   ""   },
    {       "setClippingNear"   ,        (PyCFunction)pyBOCamera_setClippingNear     , METH_VARARGS     ,   ""   },
    {       "setFogDistance"    ,        (PyCFunction)pyBOCamera_setFogDistance      , METH_VARARGS     ,   ""   },
    {           "setFov"        ,        (PyCFunction)pyBOCamera_setFov              , METH_VARARGS     ,   ""   },
    //{        "setSceneLayer"    ,        (PyCFunction)pyBOCamera_setSceneLayer       , METH_VARARGS     ,   ""   },
    {           NULL            ,                      NULL                          ,       0          , NULL   } /* Sentinel */
};    
    
static PyTypeObject pyBOCamera_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BOCamera",
    sizeof(pyBOCamera),        /*tp_basicsize*/
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
    "BOCamera maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBOCamera_methods,                  /* tp_methods */
    0,        /* tp_members */
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