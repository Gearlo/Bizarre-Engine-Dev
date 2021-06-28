

#ifndef _PY_M_MESH_REF
#define _PY_M_MESH_REF
#include "pyBMesh.h"

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>
#include "pyBMesh.h"

    typedef struct {
        PyObject_HEAD
        BMeshRef* meshRef;
    } pyBMeshRef;
    
    
    static PyObject * pyBMeshRef_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        pyBMeshRef *self;
        self = (pyBMeshRef *)type->tp_alloc(type, 0);
    
        return (PyObject *)self;
        
    }

    static void pyBMeshRef_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


    static int pyBMeshRef_init(pyBMeshRef *self, PyObject *args, PyObject *kwds)
    { 
        pyBMesh * mesh;
        const char * name = "";
        if( !PyArg_ParseTuple(args, "O!|s", &pyBMesh_type, &mesh, &name ) ){
            return 1;
        }
        
        self->meshRef = new BMeshRef(mesh->mesh, name);

        return 0;
    }
    

    static PyObject* pyBMeshRef_getMesh(pyBMeshRef* self)
    {
        pyBMesh* msr = PyObject_New(pyBMesh, &pyBMesh_type);
        msr->mesh = self->meshRef->getMesh();
        return (PyObject*)msr;  
    }
    
    static PyMethodDef pyBMeshRef_methods[] = {
     {"getMesh", (PyCFunction)pyBMeshRef_getMesh, METH_NOARGS, ""},
     {NULL}
    };
    
static PyTypeObject pyBMeshRef_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BMeshRef",
    sizeof(pyBMeshRef),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBMeshRef_dealloc,/*tp_dealloc*/
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
    "BMeshRef maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBMeshRef_methods,        /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)pyBMeshRef_init,           /* tp_init */
    0,                         /* tp_alloc */
    pyBMeshRef_new,             /* tp_new */

};

#endif