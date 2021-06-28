#ifndef _PY_U_SKIN_DATA_H_
#define _PY_U_SKIN_DATA_H_

#include "pyBSkinPoint.h"


typedef struct {
    PyObject_HEAD
    BSkinData* skindata;
} pyBSkinData;

static PyObject * pyBSkinData_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBSkinData *self;
    self = (pyBSkinData *)type->tp_alloc(type, 0);

    return (PyObject *)self;
}

static void pyBSkinData_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


static PyObject* pyBSkinData_allocPoints(pyBSkinData* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;


    return Py_BuildValue("I",self->skindata->allocPoints(i));
}

static PyObject* pyBSkinData_clearPoints(pyBSkinData* self){
    self->skindata->clearPoints();
    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSkinData_getPoint(pyBSkinData* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( i < self->skindata->getPointsNumber() ){
        BSkinPoint * _point = self->skindata->getPoint(i);

        pyBSkinPoint* point = PyObject_New(pyBSkinPoint, &pyBSkinPoint_type);
        point->point = _point;  
        return (PyObject *)point;
    }

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSkinData_getPointsNumber(pyBSkinData* self){
        return Py_BuildValue("I",self->skindata->getPointsNumber());
}

static PyMethodDef pyBSkinData_Methods[] = {
    {  "allocPoints"     ,   (PyCFunction)pyBSkinData_allocPoints         , METH_VARARGS   ,   ""   },
    {  "clearPoints"     ,   (PyCFunction)pyBSkinData_clearPoints         , METH_NOARGS    ,   ""   },
    {  "getPoint"        ,   (PyCFunction)pyBSkinData_getPoint            , METH_VARARGS   ,   ""   },
    {  "getPointsNumber" ,   (PyCFunction)pyBSkinData_getPointsNumber     , METH_NOARGS    ,   ""   },
    {NULL, NULL, 0, NULL} /* Sentinel */
};


static PyTypeObject pyBSkinData_type = {
PyObject_HEAD_INIT(NULL)
0,
"BSkinData",
sizeof(pyBSkinData),        /*tp_basicsize*/
0,                         /*tp_itemsize*/
(destructor)pyBSkinData_dealloc,/*tp_dealloc*/
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
pyBSkinData_Methods,       /* tp_methods */
0,        /* tp_members */
0,                         /* tp_getset */
0,                         /* tp_base */
0,                         /* tp_dict */
0,                         /* tp_descr_get */
0,                         /* tp_descr_set */
0,                         /* tp_dictoffset */
0,           /* tp_init */
0,                         /* tp_alloc */
pyBSkinData_new,             /* tp_new */
};



#endif