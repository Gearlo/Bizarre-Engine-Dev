#ifndef _PY_U_SKIN_POINT_H_
#define _PY_U_SKIN_POINT_H_

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

typedef struct {
    PyObject_HEAD
    BSkinPoint* point;
} pyBSkinPoint;

static PyObject * pyBSkinPoint_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBSkinPoint *self;
    self = (pyBSkinPoint *)type->tp_alloc(type, 0);

    return (PyObject *)self;
}

static void pyBSkinPoint_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }




static PyObject* pyBSkinPoint_allocateBonesLinks(pyBSkinPoint* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->point->allocateBonesLinks(i);

    Py_INCREF(Py_None);
    return Py_None; 
}


static PyObject* pyBSkinPoint_clearBonesLinks(pyBSkinPoint* self){
    self->point->clearBonesLinks();
    Py_INCREF(Py_None);
    return Py_None; 
}


static PyObject* pyBSkinPoint_getBonesNumber(pyBSkinPoint* self){
        return Py_BuildValue("I",self->point->getBonesNumber());
}

static PyObject* pyBSkinPoint_getBoneId(pyBSkinPoint* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->point->getBonesIds() && i < self->point->getBonesNumber() )
         return Py_BuildValue("H",self->point->getBonesIds()[i]);
    

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSkinPoint_setBoneId(pyBSkinPoint* self, PyObject* args)
{
    unsigned int i;
    unsigned short id;

    if (!PyArg_ParseTuple(args, "IH", &i, &id ))
        return NULL;

    if( self->point->getBonesIds() && i < self->point->getBonesNumber() )
         self->point->getBonesIds()[i] = id;
    

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSkinPoint_getBoneWeight(pyBSkinPoint* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->point->getBonesIds() && i < self->point->getBonesNumber() )
         return Py_BuildValue("H",self->point->getBonesWeights()[i]);
    

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSkinPoint_setBoneWeight(pyBSkinPoint* self, PyObject* args)
{
    unsigned int i;
    float weight;

    if (!PyArg_ParseTuple(args, "If", &i, &weight ))
        return NULL;

    if( self->point->getBonesIds() && i < self->point->getBonesNumber() )
         self->point->getBonesWeights()[i] = weight;

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSkinPoint_getVertexId(pyBSkinPoint* self){
        return Py_BuildValue("I",self->point->getVertexId());
}

static PyObject* pyBSkinPoint_setVertexId(pyBSkinPoint* self, PyObject* args)
{
    unsigned int i;
    unsigned short id;

    if (!PyArg_ParseTuple(args, "II", &i, &id ))
        return NULL;

    self->point->setVertexId( id );
    

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyMethodDef pyBSkinPoint_Methods[] = {
    {  "allocateBonesLinks" ,   (PyCFunction)pyBSkinPoint_allocateBonesLinks      , METH_VARARGS,   ""   },
    {  "clearBonesLinks "   ,   (PyCFunction)pyBSkinPoint_clearBonesLinks         , METH_NOARGS,    ""   },
    {  "getBoneId"          ,   (PyCFunction)pyBSkinPoint_getBoneId               , METH_VARARGS,   ""   },
    {  "getBonesNumber"     ,   (PyCFunction)pyBSkinPoint_getBonesNumber          , METH_NOARGS,    ""   },
    {  "getBoneWeight"      ,   (PyCFunction)pyBSkinPoint_getBoneWeight           , METH_VARARGS,   ""   },
    {  "getVertexId"        ,   (PyCFunction)pyBSkinPoint_getVertexId             , METH_VARARGS,   ""   },
    {  "setBoneId"          ,   (PyCFunction)pyBSkinPoint_setBoneId               , METH_VARARGS,   ""   },
    {  "setBoneWeight"      ,   (PyCFunction)pyBSkinPoint_setBoneWeight           , METH_VARARGS,   ""   },
    {  "setVertexId"        ,   (PyCFunction)pyBSkinPoint_setVertexId             , METH_VARARGS,   ""   },
    {NULL, NULL, 0, NULL} /* Sentinel */
};


static PyTypeObject pyBSkinPoint_type = {
PyObject_HEAD_INIT(NULL)
0,
"BSkinPoint",
sizeof(pyBSkinPoint),        /*tp_basicsize*/
0,                         /*tp_itemsize*/
(destructor)pyBSkinPoint_dealloc,/*tp_dealloc*/
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
"maratis object",           /* tp_doc */
0,                         /* tp_traverse */
0,                         /* tp_clear */
0,                         /* tp_richcompare */
0,                         /* tp_weaklistoffset */
0,                         /* tp_iter */
0,                         /* tp_iternext */
pyBSkinPoint_Methods,       /* tp_methods */
0,        /* tp_members */
0,                         /* tp_getset */
0,                         /* tp_base */
0,                         /* tp_dict */
0,                         /* tp_descr_get */
0,                         /* tp_descr_set */
0,                         /* tp_dictoffset */
0,           /* tp_init */
0,                         /* tp_alloc */
pyBSkinPoint_new,             /* tp_new */
};


#endif