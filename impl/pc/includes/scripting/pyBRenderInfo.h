#ifndef _PY_B_RENDER_INFO
#define _PY_B_RENDER_INFO

#include <Python.h>
#include "structmember.h"

#include <BCore.h>

typedef struct {
    PyObject_HEAD
    BRenderInfo* renderInfo;
} pyBRenderInfo;


static PyObject * pyBRenderInfo_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBRenderInfo *self;
    self = (pyBRenderInfo*)type->tp_alloc(type, 0);
    self->renderInfo = BRenderInfo::getInstance();

    return (PyObject *)self;
}

static PyObject* pyBRenderInfo_changeRenderer(pyBRenderInfo* self, PyObject* args)
{
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name))
            return NULL;   
    
    self->renderInfo->changeRenderer( name );

    Py_RETURN_NONE;       
}

static PyObject* pyBRenderInfo_disableTextureFilter(pyBRenderInfo* self, PyObject* args)
{
    bool value;
    if (!PyArg_ParseTuple(args, "b", &value))
            return NULL;   
    
    self->renderInfo->disabledTextureFilter = value;

    Py_RETURN_NONE;       
}

static PyObject* pyBRenderInfo_disableTextureCompression(pyBRenderInfo* self, PyObject* args)
{
    bool value;
    if (!PyArg_ParseTuple(args, "b", &value))
            return NULL;   
    
    self->renderInfo->disableTextureCompression = value;

    Py_RETURN_NONE;       
}


static PyObject* pyBRenderInfo_getFps(pyBRenderInfo* self)
{
    return Py_BuildValue("I", self->renderInfo->fps );
}

static PyMethodDef pyBRenderInfoMethods[] = {
       {  "changeRenderer"           ,  (PyCFunction)pyBRenderInfo_changeRenderer           , METH_VARARGS  ,   ""   },
       {  "disableTextureFilter"     ,  (PyCFunction)pyBRenderInfo_disableTextureFilter     , METH_VARARGS    ,   ""   },
       {  "disableTextureCompression",  (PyCFunction)pyBRenderInfo_disableTextureCompression, METH_VARARGS    ,   ""   },
       {  "getFps"                   ,  (PyCFunction)pyBRenderInfo_getFps                   , METH_NOARGS  ,   ""   },
       {NULL, NULL, 0, NULL} /* Sentinel */
    };


static PyTypeObject pyBRenderInfo_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BRenderInfo",
    sizeof(pyBRenderInfo),        /*tp_basicsize*/
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
    "BRenderInfo",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBRenderInfoMethods,      /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBRenderInfo_new,             /* tp_new */

};

#endif