#ifndef _PY_B_SYSTEM_CONTEXT
#define _PY_B_SYSTEM_CONTEXT


#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>
//#include <MWindow.h>
#include <ULog.h>
//#include <MGameWinEvents.h>


#include "pyUVector.h"   

typedef struct {
    PyObject_HEAD
    BSystemContext * system = NULL;
} pyBSystemContext;


static PyObject * pyBSystemContext_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBSystemContext *self;
    self = (pyBSystemContext *)type->tp_alloc(type, 0);
    if (self == NULL){
        Py_RETURN_NONE;
    }
    
    self->system = Bizarre::getInstance()->getSystemContext();
    return (PyObject *)self;
    
}

static void pyBSystemContext_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

static PyObject* pyBSystemContext_getScreenSize(pyBSystemContext* self, PyObject* args){
    unsigned int width,height;
    self->system->getScreenSize(&width,&height);
    return Py_BuildValue("II",width,height);
}

static PyObject* pyBSystemContext_hideCursor(pyBSystemContext* self, PyObject* args){
    self->system->hideCursor();
    Py_RETURN_NONE;
}

static PyObject* pyBSystemContext_setCursorPosition(pyBSystemContext* self, PyObject* args){
    int x,y;
    if (!PyArg_ParseTuple(args, "ii", &x,&y)){
         PyErr_SetString(PyExc_AttributeError, "parameters is: setCursorPosition(<int>x, <int>y)");
         return NULL;
    }
    
    self->system->setCursorPosition(x,y);
    Py_RETURN_NONE;
}

static PyObject* pyBSystemContext_getWorkingDirectory(pyBSystemContext* self, PyObject* args){
    return Py_BuildValue("s", self->system->getWorkingDirectory() );
}

static PyObject* pyBSystemContext_showCursor(pyBSystemContext* self, PyObject* args){
    self->system->showCursor();
    Py_RETURN_NONE;
}


static PyMethodDef pyBSystemContext_methods[] = {
    {   "getScreenSize"      , (PyCFunction)pyBSystemContext_getScreenSize      , METH_NOARGS  , ""  },
    {   "getWorkingDirectory", (PyCFunction)pyBSystemContext_getWorkingDirectory, METH_NOARGS  , ""  },
    {   "hideCursor"         , (PyCFunction)pyBSystemContext_hideCursor         , METH_NOARGS  , ""  },
    {   "setCursorPosition"  , (PyCFunction)pyBSystemContext_setCursorPosition  , METH_VARARGS , ""  },
    {   "showCursor"         , (PyCFunction)pyBSystemContext_showCursor         , METH_NOARGS  , ""  },
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyBSystemContext_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BSystemContext",
    sizeof(pyBSystemContext),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBSystemContext_dealloc,/*tp_dealloc*/
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
    pyBSystemContext_methods,        /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyBSystemContext_new,             /* tp_new */

};
#endif