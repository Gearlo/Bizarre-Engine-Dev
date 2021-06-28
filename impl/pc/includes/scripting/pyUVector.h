
#ifndef _PYMVECTOR
#define _PYMVECTOR

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>
#define PI 3.1415926543589793

/////////////////////////   BVector3f  ///////////////////////////////////
typedef struct {
    PyObject_HEAD
    BVector3f vector;
} pyUVector3;


static int pyUVector3_init(pyUVector3 *self, PyObject *args, PyObject *kwds)
{  
   self->vector = BVector3f();
   static char *kwlist[] = {(char*)"x", (char*)"y", (char*)"z", NULL};
   
   if (! PyArg_ParseTupleAndKeywords(args, kwds, "|fff", kwlist, &self->vector.x, &self->vector.y, &self->vector.z)){
       PyErr_SetString(PyExc_AttributeError, "parameters is: BVector3f(<float>x, <float>y, <float>z)");
       //return NULL;
   } 
   
   return 0;
}

static PyObject * pyUVector3_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyUVector3 *self;
    self = (pyUVector3 *)type->tp_alloc(type, 0);
    self->vector = BVector3f();
    return (PyObject *)self;
}

static void pyUVector3_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

static PyObject* pyUVector3_crossProduct(pyUVector3* self, PyObject* args);
static PyObject* pyUVector3_dotProduct(pyUVector3* self, PyObject* args);
static PyObject* pyUVector3_getLength(pyUVector3* self);
static PyObject* pyUVector3_getNormalized(pyUVector3* self);
static PyObject* pyUVector3_normalize(pyUVector3* self);
static PyObject* pyUVector3_sum(pyUVector3* self, PyObject* args);

static PyObject* pyUVector3_objectType_getter(pyUVector3 *self, void* closure)
{ return PyString_FromString("BVector3f");}


static PyGetSetDef pyUVector3_getSet[] = {
    {(char*)"objectType"  , (getter) pyUVector3_objectType_getter  , 0 , NULL, NULL},
    {NULL}
};

static PyMemberDef pyUVector3_members[] = {
    {(char*)"x", T_FLOAT, offsetof(pyUVector3, vector.x), 0,(char*)""},
    {(char*)"y", T_FLOAT, offsetof(pyUVector3, vector.y), 0,(char*)""},
    {(char*)"z", T_FLOAT, offsetof(pyUVector3, vector.z), 0,(char*)""},
    {NULL}  /* Sentinel */
};

static PyMethodDef pyUVector3_methods[] = {
     { (char*)"crossProduct"   , (PyCFunction)pyUVector3_crossProduct   , METH_VARARGS, (char*)""},
     { (char*)"dotProduct"     , (PyCFunction)pyUVector3_dotProduct     , METH_VARARGS, (char*)""},
     { (char*)"getLength"      , (PyCFunction)pyUVector3_getLength      , METH_NOARGS , (char*)""},
     { (char*)"getNormalized"  , (PyCFunction)pyUVector3_getNormalized  , METH_NOARGS , (char*)""},
     { (char*)"normalize"      , (PyCFunction)pyUVector3_normalize      , METH_NOARGS , (char*)""},
     { (char*)"add"            , (PyCFunction)pyUVector3_sum            , METH_VARARGS, (char*)""},
     {NULL}
};

static PyTypeObject pyUVector3_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BVector3f",
    sizeof(pyUVector3),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyUVector3_dealloc,        /*tp_dealloc*/
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
    "BVector3f maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyUVector3_methods,        /* tp_methods */
    pyUVector3_members,        /* tp_members */
    pyUVector3_getSet,         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)pyUVector3_init, /* tp_init */
    0,                         /* tp_alloc */
    pyUVector3_new,             /* tp_new */

};

static PyObject* pyUVector3_crossProduct(pyUVector3* self, PyObject* args)
{
    float x;
    float y;
    float z;
    pyUVector3* r = PyObject_New(pyUVector3, &pyUVector3_type);
    
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * v;
        if (PyArg_ParseTuple(args, "O", &v)){
            PyErr_Clear();
            r->vector = self->vector.crossProduct(v->vector);
            return (PyObject*)r;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: crossProduct(<float>x, <float>y, <float>z) or crossProduct(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        r->vector = self->vector.crossProduct(BVector3f(x,y,z));
        return (PyObject*)r;
    }      
}

static PyObject* pyUVector3_dotProduct(pyUVector3* self, PyObject* args)
{
    float x;
    float y;
    float z;
    
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * v;
        if (PyArg_ParseTuple(args, "O", &v)){
            PyErr_Clear();
            return Py_BuildValue("f", self->vector.dotProduct(v->vector));
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: dotProduct(<float>x, <float>y, <float>z) or dotProduct(<BVector3f>rotation)");
            return NULL;
        }
    }else{
        return Py_BuildValue("f", self->vector.dotProduct(BVector3f(x,y,z)));
    }      
}

static PyObject* pyUVector3_getLength(pyUVector3* self)
{
    return Py_BuildValue("f",self->vector.getLength()); 
}

static PyObject* pyUVector3_getNormalized(pyUVector3* self)
{
    pyUVector3* vec = PyObject_New(pyUVector3, &pyUVector3_type);
    vec->vector = self->vector.getNormalized();
    return (PyObject*)vec;
} 

static PyObject* pyUVector3_normalize(pyUVector3* self)
{
    self->vector.normalize();
    Py_RETURN_NONE;
    
}

static PyObject* pyUVector3_sum(pyUVector3* self, PyObject* args)
{
    pyUVector3 * value;
    
    if (!PyArg_ParseTuple(args, "O!", &pyUVector3_type ,&value)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: sum(<BVector3f>rotation)");
        return NULL;
    }
    self->vector = self->vector + value->vector;
    Py_RETURN_NONE;
}



/////////////////// BVector2f ///////////////////////////////////////////////////

typedef struct {
    PyObject_HEAD
    BVector2f vector;
} pyUVector2;


static int pyUVector2_init(pyUVector2 *self, PyObject *args, PyObject *kwds)
{  
   static char *kwlist[] = {(char*)"x", (char*)"y", NULL};

   if (! PyArg_ParseTupleAndKeywords(args, kwds, "ff", kwlist, &self->vector.x, &self->vector.y)){
       PyErr_SetString(PyExc_AttributeError, "parameters is: BVector2f(<float>x, <float>y)");
       return 0;
   } 
   
   return 0;
}

static PyObject * pyUVector2_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyUVector2 *self;
    self = (pyUVector2 *)type->tp_alloc(type, 0);
    
    return (PyObject *)self;
}

static void pyUVector2_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


static PyObject* pyUVector2_getLength(pyUVector2* self)
{
    return Py_BuildValue("f",self->vector.getLength()); 
}



static PyMemberDef pyUVector2_members[] = {
    {(char*)"x", T_FLOAT, offsetof(pyUVector3, vector.x), 0,(char*)""},
    {(char*)"y", T_FLOAT, offsetof(pyUVector3, vector.y), 0,(char*)""},
    {NULL}
};

static PyMethodDef pyUVector2_methods[] = {
     { (char*)"getLength"   , (PyCFunction)pyUVector2_getLength   , METH_VARARGS, (char*)""},
     {NULL}
};

static PyTypeObject pyUVector2_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BVector2f",
    sizeof(pyUVector2),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    pyUVector2_dealloc,        /*tp_dealloc*/
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
    "BVector2f maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyUVector2_methods,        /* tp_methods */
    pyUVector2_members,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)pyUVector2_init, /* tp_init */
    0,                         /* tp_alloc */
    pyUVector2_new,             /* tp_new */

};


/////////////////// BVector4f ///////////////////////////////////////////////////

typedef struct {
    PyObject_HEAD
    BVector4f vector;
} pyUVector4;


static int pyUVector4_init(pyUVector4 *self, PyObject *args, PyObject *kwds)
{  
   static char *kwlist[] = {(char*)"x", (char*)"y", (char*)"z", (char*)"w", NULL};

   if (! PyArg_ParseTupleAndKeywords(args, kwds, "ffff", kwlist, &self->vector.x, &self->vector.y, &self->vector.w, &self->vector.w)){
       PyErr_SetString(PyExc_AttributeError, "parameters is: BVector4f(<float>x, <float>y, <float>z, <float>w)");
       return 0;
   } 
   
   return 0;
}

static PyObject * pyUVector4_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyUVector4 *self;
    self = (pyUVector4 *)type->tp_alloc(type, 0);
    
    return (PyObject *)self;
}

static void pyUVector4_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }




static PyMemberDef pyUVector4_members[] = {
    {(char*)"x", T_FLOAT, offsetof(pyUVector4, vector.x), 0,(char*)""},
    {(char*)"y", T_FLOAT, offsetof(pyUVector4, vector.y), 0,(char*)""},
    {(char*)"z", T_FLOAT, offsetof(pyUVector4, vector.z), 0,(char*)""},
    {(char*)"w", T_FLOAT, offsetof(pyUVector4, vector.w), 0,(char*)""},
    {NULL}
};

static PyMethodDef pyUVector4_methods[] = {
     //{ (char*)"getLength"   , (PyCFunction)pyUVector4_getLength   , METH_VARARGS, (char*)""},
     {NULL}
};

static PyTypeObject pyUVector4_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BVector4f",
    sizeof(pyUVector4),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    pyUVector4_dealloc,        /*tp_dealloc*/
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
    "BVector4f maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,        /* tp_methods */
    pyUVector4_members,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)pyUVector4_init, /* tp_init */
    0,                         /* tp_alloc */
    pyUVector4_new,             /* tp_new */

};
#endif