
//#include <MGameWinEvents.h>


#ifndef _PY_M_INPUT_TYPE
#define _PY_M_INPUT_TYPE

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>
//#include <MWindow.h>
#include <ULog.h>
   
typedef struct {
    PyObject_HEAD
    BInputContext * input = NULL;
} pyUwinputContext;


static PyObject * pyUwinputContext_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyUwinputContext *self;
    self = (pyUwinputContext *)type->tp_alloc(type, 0);
    if (self == NULL){
        Py_RETURN_NONE;
    }
    self->input = Bizarre::getInstance()->getInputContext();
    return (PyObject *)self;
    
}

static void pyUwinputContext_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

static PyObject* pyUwinputContext_isKeyPressed(pyUwinputContext* self, PyObject* args){
    char *key;
    if (!PyArg_ParseTuple(args, "s", &key)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: isKeyPressed(<string>key)");
        return NULL;
    }
    return Py_BuildValue("b",self->input->isKeyPressed(key));
}

static PyObject* pyUwinputContext_onKeyDown(pyUwinputContext* self, PyObject* args){
    char *key;
    if (!PyArg_ParseTuple(args, "s", &key)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: isKeyPressed(<string>key)");
        return NULL;
    }
    return Py_BuildValue("b",self->input->onKeyDown(key));
}

static PyObject* pyUwinputContext_onKeyUp(pyUwinputContext* self, PyObject* args){
    char *key;
    if (!PyArg_ParseTuple(args, "s", &key)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: isKeyPressed(<string>key)");
        return NULL;
    }
    return Py_BuildValue("b",self->input->onKeyUp(key));
}

static PyObject*  pyUwinputContext_getAxis(pyUwinputContext* self, PyObject* args){
    char *axis;
    if (!PyArg_ParseTuple(args, "s", &axis)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: isKeyPressed(<string>key)");
        return NULL;
    }
    return Py_BuildValue("f",self->input->getAxis(axis));
}


static PyMethodDef pyUwinputContext_methods[] = {
    {   "isKeyPressed"  , (PyCFunction)pyUwinputContext_isKeyPressed  , METH_VARARGS  , ""  },
    {   "getAxis"       , (PyCFunction)pyUwinputContext_getAxis       , METH_VARARGS  , ""  },
    {   "onKeyDown"     , (PyCFunction)pyUwinputContext_onKeyDown     , METH_VARARGS  , ""  },
    {   "onKeyUp"       , (PyCFunction)pyUwinputContext_onKeyUp       , METH_VARARGS  , ""  },
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyUwinputContext_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BInputContext",
    sizeof(pyUwinputContext),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyUwinputContext_dealloc,/*tp_dealloc*/
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
    "BInputContext maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyUwinputContext_methods,        /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyUwinputContext_new,             /* tp_new */

};
#endif