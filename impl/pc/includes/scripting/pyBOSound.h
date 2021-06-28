

#ifndef _PY_M_OSOUND
#define _PY_M_OSOUND

    #include <Python.h>
    #include "structmember.h"

    #include <BEngine.h>

    #include "pyBObject3d.h"

    typedef struct {
        pyBObject3d obj;
    } pyBOSound;
  


    static PyObject* pyBOSound_setGain(pyBOSound* self, PyObject* args)
    {
        float value;
        if (!PyArg_ParseTuple(args, "f", &value))
                return NULL;   
        
        ((BOSound*)self->obj.object)->setGain(value);
    
        Py_RETURN_NONE;       
    }

    static PyObject* pyBOSound_setLooping(pyBOSound* self, PyObject* args)
    {
        bool value;
        if (!PyArg_ParseTuple(args, "b", &value))
                return NULL;   
        
        ((BOSound*)self->obj.object)->setLooping(value);
    
        Py_RETURN_NONE;       
    }

    static PyObject* pyBOSound_setPitch(pyBOSound* self, PyObject* args)
    {
        float value;
        if (!PyArg_ParseTuple(args, "f", &value))
                return NULL;   
        
        ((BOSound*)self->obj.object)->setPitch(value);
    
        Py_RETURN_NONE;       
    }

    static PyObject* pyBOSound_setRelative(pyBOSound* self, PyObject* args)
    {
        bool value;
        if (!PyArg_ParseTuple(args, "b", &value))
                return NULL;   
        
        ((BOSound*)self->obj.object)->setRelative(value);
    
        Py_RETURN_NONE;       
    }

    static PyObject* pyBOSound_setRadius(pyBOSound* self, PyObject* args)
    {
        float value;
        if (!PyArg_ParseTuple(args, "f", &value))
                return NULL;   
        
        ((BOSound*)self->obj.object)->setRadius(value);
    
        Py_RETURN_NONE;       
    }

    static PyObject* pyBOSound_setRolloff(pyBOSound* self, PyObject* args)
    {
        float value;
        if (!PyArg_ParseTuple(args, "f", &value))
                return NULL;   
        
        ((BOSound*)self->obj.object)->setRolloff(value);
    
        Py_RETURN_NONE;       
    }

    static PyObject* pyBOSound_isPlaying(pyBOSound* self)
    {
        return Py_BuildValue("b",((BOSound*)self->obj.object)->isPlaying());
    }

    static PyObject* pyBOSound_isRelative(pyBOSound* self)
    {
        return Py_BuildValue("b",((BOSound*)self->obj.object)->isRelative());
    }

    static PyObject* pyBOSound_isLooping(pyBOSound* self)
    {
        return Py_BuildValue("b",((BOSound*)self->obj.object)->isLooping());
    }


    static PyObject* pyBOSound_getPitch(pyBOSound* self)
    {
        return Py_BuildValue("f",((BOSound*)self->obj.object)->getPitch());
    }

    static PyObject* pyBOSound_getGain(pyBOSound* self)
    {
        return Py_BuildValue("f",((BOSound*)self->obj.object)->getGain());
    }

    static PyObject* pyBOSound_getRadius(pyBOSound* self)
    {
        return Py_BuildValue("f",((BOSound*)self->obj.object)->getRadius());
    }

    static PyObject* pyBOSound_getRolloff(pyBOSound* self)
    {
        return Py_BuildValue("f",((BOSound*)self->obj.object)->getRolloff());
    }



    static PyObject* pyBOSound_play(pyBOSound* self)
    {
        ((BOSound*)self->obj.object)->play();
        Py_RETURN_NONE;
    }

    static PyObject* pyBOSound_pause(pyBOSound* self)
    {
        ((BOSound*)self->obj.object)->play();
        Py_RETURN_NONE;
    }

    static PyObject* pyBOSound_stop(pyBOSound* self)
    {
        ((BOSound*)self->obj.object)->play();
        Py_RETURN_NONE;
    }

    


    static PyMethodDef pyBOSoundMethods[] = {
       {  "setRelative" ,        (PyCFunction)pyBOSound_setRelative   , METH_VARARGS   ,   ""   },
       {  "setLooping"  ,        (PyCFunction)pyBOSound_setLooping    , METH_VARARGS   ,   ""   },
       {  "setPitch"    ,        (PyCFunction)pyBOSound_setPitch      , METH_VARARGS   ,   ""   },
       {  "setGain"     ,        (PyCFunction)pyBOSound_setGain       , METH_VARARGS   ,   ""   },
       {  "setRadius"   ,        (PyCFunction)pyBOSound_setRadius     , METH_VARARGS   ,   ""   },
       {  "setRolloff"  ,        (PyCFunction)pyBOSound_setRolloff    , METH_VARARGS   ,   ""   },
       {  "isPlaying"   ,        (PyCFunction)pyBOSound_isPlaying     , METH_NOARGS    ,   ""   },
       {  "isRelative"  ,        (PyCFunction)pyBOSound_isRelative    , METH_NOARGS    ,   ""   },
       {  "isLooping"   ,        (PyCFunction)pyBOSound_isLooping     , METH_NOARGS    ,   ""   },
       {  "getPitch"    ,        (PyCFunction)pyBOSound_getPitch      , METH_NOARGS    ,   ""   },
       {  "getGain"     ,        (PyCFunction)pyBOSound_getGain       , METH_NOARGS    ,   ""   },
       {  "getRadius"   ,        (PyCFunction)pyBOSound_getRadius     , METH_NOARGS    ,   ""   },
       {  "getRolloff"  ,        (PyCFunction)pyBOSound_getRolloff    , METH_NOARGS    ,   ""   },
       {  "play"        ,        (PyCFunction)pyBOSound_play          , METH_NOARGS    ,   ""   },
       {  "pause"       ,        (PyCFunction)pyBOSound_pause         , METH_NOARGS    ,   ""   },
       {  "stop"        ,        (PyCFunction)pyBOSound_stop          , METH_NOARGS    ,   ""   },
       {NULL, NULL, 0, NULL} /* Sentinel */
    };
  
    static PyTypeObject pyBOSound_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BOSound",
    sizeof(pyBOSound),          /*tp_basicsize*/
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
    "BOSound object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBOSoundMethods,                  /* tp_methods */
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