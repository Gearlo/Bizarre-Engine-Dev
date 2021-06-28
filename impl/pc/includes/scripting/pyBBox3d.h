// #ifndef _PYBBOX3D
// #define _PYBBOX3D

// #include <Python.h>
// #include "structmember.h"

// #include <Bizarre.h>
// #include "pyUVector.h"

// typedef struct {
//     PyObject_HEAD
//     BBox3d * box;
// } pyBBox3d;

// static PyObject * pyBBox3d_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
// {
//     pyBBox3d *self;
//     self = (pyBBox3d *)type->tp_alloc(type, 0);
//     return (PyObject *)self;
// }

// static void pyBBox3d_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

// static int pyBBox3d_init(pyBBox3d *self, PyObject *args, PyObject *kwds)
// {  
//     static char *kwlist[] = {(char*)"min", (char*)"max", NULL};
   
//     PyObject *min = NULL, *max = NULL;
//     if (! PyArg_ParseTupleAndKeywords(args, kwds, "|O!O!", kwlist, &pyUVector3_type, &min, &pyUVector3_type, &max)){
//         //PyErr_SetString(PyExc_AttributeError, "parameters is: BVector3f(<float>x, <float>y, <float>z)");
//         return 1;
//     }

//     self->box = new BBox3d();
//     if(min)
//         self->box->min = ( (pyUVector3*)min )->vector;
    
//     if(max)
//         self->box->max = ( (pyUVector3*)max )->vector;

//    return 0;
// }

// static PyObject* pyBBox3d_isInCollisionWith(pyUVector3* self, PyObject* args);

// static PyObject* pyBBox3d_initFromPoints(pyBBox3d* self, PyObject* args)
// {
//     PyObject * value;
    
//     if (!PyArg_ParseTuple(args, "O!", &PyList_Type ,&value)){
//         PyErr_SetString(PyExc_AttributeError, "");
//         return NULL;
//     }
//     //BVector3f * points = 
//     //return Py_BuildValue("b", self->box->isInCollisionWith( value->box ) );
// }

// static PyMethodDef pyBBox3d_methods[] = {
//      { (char*)"isInCollisionWith"   , (PyCFunction)pyBBox3d_isInCollisionWith , METH_VARARGS, (char*)""},
//      { (char*)"initFromPoints"      , (PyCFunction)pyBBox3d_initFromPoints    , METH_VARARGS, (char*)""},
//      {NULL}
// };


// static PyTypeObject pyBBox3d_type = {
//     PyObject_HEAD_INIT(NULL)
//     0,
//     "BBox3d",
//     sizeof(pyBBox3d),        /*tp_basicsize*/
//     0,                         /*tp_itemsize*/
//     (destructor)pyBBox3d_dealloc,        /*tp_dealloc*/
//     0,                         /*tp_print*/
//     0,                         /*tp_getattr*/
//     0,                         /*tp_setattr*/
//     0,                         /*tp_compare*/
//     0,                         /*tp_repr*/
//     0,                         /*tp_as_number*/
//     0,                         /*tp_as_sequence*/
//     0,                         /*tp_as_mapping*/
//     0,                         /*tp_hash */
//     0,                         /*tp_call*/
//     0,                         /*tp_str*/
//     0,                         /*tp_getattro*/
//     0,                         /*tp_setattro*/
//     0,                         /*tp_as_buffer*/
//     Py_TPFLAGS_DEFAULT |  Py_TPFLAGS_BASETYPE, /*tp_flags*/
//     "BVector3f maratis object",           /* tp_doc */
//     0,                         /* tp_traverse */
//     0,                         /* tp_clear */
//     0,                         /* tp_richcompare */
//     0,                         /* tp_weaklistoffset */
//     0,                         /* tp_iter */
//     0,                         /* tp_iternext */
//     pyBBox3d_methods,          /* tp_methods */
//     0,        /* tp_members */
//     0,         /* tp_getset */
//     0,                         /* tp_base */
//     0,                         /* tp_dict */
//     0,                         /* tp_descr_get */
//     0,                         /* tp_descr_set */
//     0,                         /* tp_dictoffset */
//     (initproc)pyBBox3d_init, /* tp_init */
//     0,                         /* tp_alloc */
//     pyBBox3d_new,             /* tp_new */
// };


// static PyObject* pyBBox3d_isInCollisionWith(pyBBox3d* self, PyObject* args)
// {
//     pyBBox3d * value;
    
//     if (!PyArg_ParseTuple(args, "O!", &pyBBox3d_type ,&value)){
//         PyErr_SetString(PyExc_AttributeError, "parameters is: sum(<BVector3f>rotation)");
//         return NULL;
//     }
//     return Py_BuildValue("b", self->box->isInCollisionWith( value->box ) );
// }

// #endif

