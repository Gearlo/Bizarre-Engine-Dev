#ifndef _U_ANIM_PROPERTIES_H_
#define _U_ANIM_PROPERTIES_H_

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>   


typedef struct {
    PyObject_HEAD
    BAnimTransitionProperties* transitionProps;
} pyBAnimTransitionProperties;

static PyObject * pyBAnimTransitionProperties_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBAnimTransitionProperties *self;
    self = (pyBAnimTransitionProperties *)type->tp_alloc(type, 0);

    return (PyObject *)self;
}

static void pyBAnimTransitionProperties_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }
    

static PyObject * pyBAnimTransitionProperties_getNextAnim(pyBAnimTransitionProperties *self, void *closure)
{
    return Py_BuildValue("I",self->transitionProps->nextAnim);
}


static PyObject * pyBAnimTransitionProperties_getTransitionAnim(pyBAnimTransitionProperties *self, void *closure)
{
    return Py_BuildValue("I",self->transitionProps->transitionAnim);
}



static int pyBAnimTransitionProperties_setNextAnim(pyBAnimTransitionProperties *self, PyObject *value, void *closure){
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
    }

    if ( !PyInt_Check(value) ) {
        PyErr_SetString(PyExc_TypeError, "attribute type error");
        return -1;
    }

    long nextAniml = PyInt_AsLong(value);
    if( nextAniml > 0 )
        self->transitionProps->nextAnim = (unsigned int)nextAniml;
    else
    {
        PyErr_SetString(PyExc_TypeError, "attribute must be a positive number");
        return -1;
    }

    return 0;
}

static int pyBAnimTransitionProperties_setTransitionAnim(pyBAnimTransitionProperties *self, PyObject *value, void *closure){
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
    }

    if (! PyInt_Check(value) ) {
        PyErr_SetString(PyExc_TypeError, "attribute type error");
        return -1;
    }

    long transitionAniml = PyInt_AsLong(value);
    if( transitionAniml > 0 )
        self->transitionProps->transitionAnim = (unsigned int)transitionAniml;
    else
    {
        PyErr_SetString(PyExc_TypeError, "attribute must be a positive number");
        return -1;
    }

    return 0;
}

static PyGetSetDef pyBAnimTransitionProperties_getseters[] = {
    {(char*)"nextAnim", (getter)pyBAnimTransitionProperties_getNextAnim, (setter)pyBAnimTransitionProperties_setNextAnim,(char*)"", NULL},
    {(char*)"transitionAnim", (getter)pyBAnimTransitionProperties_getTransitionAnim, (setter)pyBAnimTransitionProperties_setTransitionAnim,(char*)"", NULL},
    {NULL}  /* Sentinel */
};


    
static PyTypeObject pyBAnimTransitionProperties_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BAnimTransitionProperties",
    sizeof(pyBAnimTransitionProperties),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBAnimTransitionProperties_dealloc, /*tp_dealloc*/
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
    "",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,       /* tp_methods */
    0,        /* tp_members */
    pyBAnimTransitionProperties_getseters,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBAnimTransitionProperties_new,             /* tp_new */
    };

////////////////////////////////////////////////////////////////////////


typedef struct {
    PyObject_HEAD
    BAnimProperties* animProps;
} pyBAnimProperties;

static PyObject * pyBAnimProperties_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBAnimProperties *self;
    self = (pyBAnimProperties *)type->tp_alloc(type, 0);

    return (PyObject *)self;
}

static void pyBAnimProperties_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }
    


static PyObject * pyBAnimProperties_getStart(pyBAnimProperties *self, void *closure)
{
    return Py_BuildValue("i",self->animProps->start);
}


static PyObject * pyBAnimProperties_getEnd(pyBAnimProperties *self, void *closure)
{
    return Py_BuildValue("i",self->animProps->end);
}


static PyObject * pyBAnimProperties_getLoops(pyBAnimProperties *self, void *closure)
{
    return Py_BuildValue("i",self->animProps->loops);
}

static PyObject * pyBAnimProperties_getAtTheEndAnim(pyBAnimProperties *self, void *closure)
{
    return Py_BuildValue("I",self->animProps->atTheEndAnim);
}

static PyObject * pyBAnimProperties_getAtTheEndDelayAnim(pyBAnimProperties *self, void *closure)
{
    return Py_BuildValue("d",self->animProps->atTheEndDelayAnim);
}   
    


static int pyBAnimProperties_setStart(pyBAnimProperties *self, PyObject *value, void *closure){
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
    }

    if (! PyInt_Check(value) ) {
        PyErr_SetString(PyExc_TypeError, "attribute type error");
        return -1;
    }

    self->animProps->start = (int)PyInt_AsLong(value);

    return 0;
}

static int pyBAnimProperties_setEnd(pyBAnimProperties *self, PyObject *value, void *closure){
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
    }

    if (! PyInt_Check(value) ) {
        PyErr_SetString(PyExc_TypeError, "attribute type error");
        return -1;
    }

    self->animProps->end = (int)PyInt_AsLong(value);

    return 0;
}

static int pyBAnimProperties_setLoops(pyBAnimProperties *self, PyObject *value, void *closure){
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
    }

    if (! PyInt_Check(value) ) {
        PyErr_SetString(PyExc_TypeError, "attribute type error");
        return -1;
    }

    self->animProps->loops = (int)PyInt_AsLong(value);

    return 0;
}


static int pyBAnimProperties_setAtTheEndAnim(pyBAnimProperties *self, PyObject *value, void *closure){
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
    }

    if (! PyInt_Check(value) ) {
        PyErr_SetString(PyExc_TypeError, "attribute type error");
        return -1;
    }

    long atTheEndAniml = PyInt_AsLong(value);
    if( atTheEndAniml > 0 )
        self->animProps->atTheEndAnim = (unsigned int)atTheEndAniml;
    else
    {
        PyErr_SetString(PyExc_TypeError, "attribute must be a positive number");
        return -1;
    }

    return 0;
}


static int pyBAnimProperties_setAtTheEndDelayAnim(pyBAnimProperties *self, PyObject *value, void *closure){
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
    }

    if (! PyFloat_Check(value) ) {
        PyErr_SetString(PyExc_TypeError, "attribute type error");
        return -1;
    }

    self->animProps->atTheEndDelayAnim = PyFloat_AsDouble(value);

    return 0;
}


static PyGetSetDef pyBAnimProperties_getseters[] = {
    {(char*)"start", (getter)pyBAnimProperties_getStart, (setter)pyBAnimProperties_setStart,(char*)"", NULL},
    {(char*)"end", (getter)pyBAnimProperties_getEnd, (setter)pyBAnimProperties_setEnd,(char*)"", NULL},
    {(char*)"loops", (getter)pyBAnimProperties_getLoops, (setter)pyBAnimProperties_setLoops,(char*)"", NULL},
    {(char*)"atTheEndAnim", (getter)pyBAnimProperties_getAtTheEndAnim, (setter)pyBAnimProperties_setAtTheEndAnim,(char*)"", NULL},
    {(char*)"atTheEndDelayAnim", (getter)pyBAnimProperties_getAtTheEndDelayAnim, (setter)pyBAnimProperties_setAtTheEndDelayAnim,(char*)"", NULL},
    {NULL}  /* Sentinel */
};




static PyObject* pyBAnimProperties_allocTransitions(pyBAnimProperties* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->animProps->allocTransitions(i);

    Py_INCREF(Py_None);
    return Py_None; 
}


static PyObject* pyBAnimProperties_getTransitionsNumber(pyBAnimProperties* self){
    return Py_BuildValue( "I",self->animProps->getTransitionsNumber() );
}


static PyObject* pyBAnimProperties_getTransition(pyBAnimProperties* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->animProps->getTransition(i) ){
        
        pyBAnimTransitionProperties* transition = PyObject_New(pyBAnimTransitionProperties, &pyBAnimTransitionProperties_type);
        transition->transitionProps = self->animProps->getTransition(i);
        return (PyObject *)transition;
    }

    Py_INCREF(Py_None);
    return Py_None; 
}


static PyObject* pyBAnimProperties_setTransition(pyBAnimProperties* self, PyObject* args)
{
    unsigned int i;
    unsigned int indice;

    unsigned int transNumber;
    animation nextAnim; 
    animation transitionAnim;


    if (!PyArg_ParseTuple(args, "III", &transNumber, &nextAnim, &transitionAnim))
        return NULL;

    self->animProps->setTransition( transNumber, nextAnim, transitionAnim );


    Py_INCREF(Py_None);
    return Py_None; 
}


static PyMethodDef pyBAnimProperties_methods[] = {
    {   "allocTransitions"     , (PyCFunction)pyBAnimProperties_allocTransitions      , METH_VARARGS ,  ""},
    {   "getTransitionsNumber" , (PyCFunction)pyBAnimProperties_getTransitionsNumber  , METH_NOARGS  ,  ""},
    {   "getTransition"        , (PyCFunction)pyBAnimProperties_getTransition         , METH_VARARGS ,  ""},
    {   "setTransition"        , (PyCFunction)pyBAnimProperties_setTransition         , METH_VARARGS ,  ""},
    {   NULL                   , NULL                                                 , 0            , NULL} /* Sentinel */
};

static PyTypeObject pyBAnimProperties_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BAnimProperties",
    sizeof(pyBAnimProperties),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBAnimProperties_dealloc, /*tp_dealloc*/
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
    "",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBAnimProperties_methods,       /* tp_methods */
    0,        /* tp_members */
    pyBAnimProperties_getseters,/* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,           /* tp_init */
    0,                         /* tp_alloc */
    pyBAnimProperties_new,             /* tp_new */
    };



#endif