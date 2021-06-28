
#ifndef _pyBImage
#define _pyBImage

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

typedef struct {
    PyObject_HEAD
    BImage image;
} pyBImage;
    
    
static PyObject * pyBImage_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBImage *self;
    self = (pyBImage *)type->tp_alloc(type, 0);
    return (PyObject *)self; 
}

static int pyBImage_init(pyBImage *self, PyObject *args, PyObject *kwds)
{  
    unsigned int width, height, components = 4u;
    static char *kwlist[] = {(char*)"width", (char*)"height", (char*)"components", NULL};
   
   if (! PyArg_ParseTupleAndKeywords(args, kwds, "II|I", kwlist, &width, &height, &components )){
       //PyErr_SetString(PyExc_AttributeError, "parameters is: BVector3f(<float>x, <float>y, <float>z)");
       //return NULL;
       return 0;
   } 

   self->image.create(M_UBYTE, width, height, components);
   
   return 0;
}


static void pyBImage_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


static PyObject* pyBImage_getHeight(pyBImage* self)
{
    return Py_BuildValue("I",self->image.getHeight() ); 
}

static PyObject* pyBImage_getWidth(pyBImage* self)
{
    return Py_BuildValue("I",self->image.getWidth() ); 
}


static PyObject* pyBImage_writePixel(pyBImage* self, PyObject* args)
{
    unsigned char pixel[4];
    unsigned int x,y;

    if ( PyArg_ParseTuple(args, "IIb|bbb", &x, &y, &pixel[0], &pixel[1], &pixel[2], &pixel[3]) ){
        self->image.writePixel( x, y , &pixel );
    }
    
    Py_RETURN_NONE;
}

static PyObject* pyBImage_readPixel(pyBImage* self, PyObject* args)
{
    unsigned char pixel[4];
    unsigned int x,y;

    if ( PyArg_ParseTuple(args, "II", &x, &y) ){
        self->image.readPixel( x, y , &pixel );

        PyObject* tuple = PyTuple_New( self->image.getComponents() );
        for(int i = 0; i < self->image.getComponents(); i++ )
            PyTuple_SetItem(tuple, i, PyInt_FromLong( (long)pixel[i] ) );

        return tuple;
    }
    
    Py_RETURN_NONE;
}

static PyMethodDef pyBImage_methods[] = {
    {   "getHeight"          , (PyCFunction)pyBImage_getHeight            , METH_NOARGS , ""},
    {   "getWidth"           , (PyCFunction)pyBImage_getWidth             , METH_NOARGS , ""},
    {   "writePixel"         , (PyCFunction)pyBImage_writePixel           , METH_VARARGS , ""},
    {   "readPixel"          , (PyCFunction)pyBImage_readPixel            , METH_VARARGS , ""},
    {NULL, NULL, 0, NULL} /* Sentinel */
};


static PyObject* pyBImage_objectType_getter(pyBImage* self, void* closure)
{ return PyString_FromString("BImage");}


static PyGetSetDef pyBImage_getSet[] = {
    {(char*)"objectType"  , (getter) pyBImage_objectType_getter  , 0 , NULL, NULL},
    {NULL}
};
    
    
static PyTypeObject pyBImage_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BImage",
    sizeof(pyBImage),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBImage_dealloc,  /*tp_dealloc*/
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
    pyBImage_methods,          /* tp_methods */
    0,                         /* tp_members */
    pyBImage_getSet,         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)pyBImage_init,    /* tp_init */
    0,                         /* tp_alloc */
    pyBImage_new,             /* tp_new */

};

#endif