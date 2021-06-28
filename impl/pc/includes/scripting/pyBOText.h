#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#include <string.h>
#include <cstdlib>
#include <iostream>

#ifndef _PY_M_OTEXT
#define _PY_M_OTEXT

    #include "pyBObject3d.h"

    typedef struct {
        pyBObject3d obj;
    } pyBOText;
    
    static PyObject* pyBOText_getAlign(pyBOText* self)
    {
      const char* returnValue; 
      U_ALIGN_MODES align = ((BOText *)self->obj.object)->getAlign();
      if (align == U_ALIGN_LEFT){
          returnValue = "left";
      }else if (align == U_ALIGN_CENTER){
          returnValue = "center";
      }else{
          returnValue = "right";
      }
      return Py_BuildValue("s", returnValue);
    }
    
    static PyObject* pyBOText_getColor(pyBOText* self)
    {
        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = ((BOText *)self->obj.object)->getColor();
        return (PyObject*)color;
    } 
    
    static PyObject* pyBOText_getFontRef(pyBOText* self)
    {
        pyBFontRef* fr = PyObject_New(pyBFontRef, &pyBFontRef_type);
        fr->fontRef = ((BOText *)self->obj.object)->getFontRef();
        return (PyObject*)fr;  
    } 
    
    static PyObject* pyBOText_getSize(pyBOText* self)
    {
        return Py_BuildValue("f",((BOText *)self->obj.object)->getSize());  
    }
    
    static PyObject* pyBOText_getText(pyBOText* self)
    {
        return Py_BuildValue("s",((BOText *)self->obj.object)->getText());  
    }
    
    static PyObject* pyBOText_setAlign(pyBOText* self,  PyObject* args)
    {
        char* text;
        if (!PyArg_ParseTuple(args, "s", &text)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setAlign(<string>align)");
            return NULL;   
        }
       
        if (strcmp("center", text) == 0){
            ((BOText *)self->obj.object)->setAlign(U_ALIGN_CENTER);
        }else if (strcmp("right", text) == 0){
            ((BOText *)self->obj.object)->setAlign(U_ALIGN_RIGHT);
        }else{
            ((BOText *)self->obj.object)->setAlign(U_ALIGN_LEFT);
        }
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBOText_setColor(pyBOText* self, PyObject* args)
    {
    float r; float g; float b;
    if (!PyArg_ParseTuple(args, "fff", &r, &g, &b)){
        pyUVector3 * color;
        if (PyArg_ParseTuple(args, "O", &color)){
            PyErr_Clear();
            ((BOText *)self->obj.object)->setColor(color->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setColor(<float>r, <float>g, <float>b) or setColor(<BVector3f>color)");
            return NULL;
        }
    }else{
        ((BOText *)self->obj.object)->setColor(BVector3f(r,g,b));
    }
        Py_RETURN_NONE;
    }
    
    static PyObject* pyBOText_setFontRef(pyBOText* self, PyObject* args)
    {
        pyBFontRef* fr;
        if (PyArg_ParseTuple(args, "O", &fr)){
            ((BOText *)self->obj.object)->setFontRef(fr->fontRef);
            Py_RETURN_NONE;
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setFontRef(<BFontRef>fontRef)");
            return NULL;
        }              
    }
   
    static PyObject* pyBOText_setText(pyBOText* self, PyObject* args)
    {
        char* text;
        if (!PyArg_ParseTuple(args, "s", &text)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setText(<string>text)");
            return NULL;   
        }
        //std::cout << text << std::endl;
        ((BOText*)self->obj.object)->setText(text);
    
        Py_RETURN_NONE;       
    }
    
    static PyObject* pyBOText_setSize(pyBOText* self, PyObject* args)
    {
        float size;
        if (!PyArg_ParseTuple(args, "f", &size)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: setSize(<float>size)");
            return NULL;   
        }
        ((BOText*)self->obj.object)->setSize(size);
        //((BOText*)self->obj.object)->setAlign()
        Py_RETURN_NONE;       
    }

    static PyMethodDef pyBOText_methods[] = {
        {        "getAlign"   ,    (PyCFunction)pyBOText_getAlign             , METH_NOARGS     ,   ""   },
        {        "getColor"   ,    (PyCFunction)pyBOText_getColor             , METH_NOARGS     ,   ""   },
        {        "getFontRef" ,    (PyCFunction)pyBOText_getFontRef           , METH_NOARGS     ,   ""   },
        {        "getSize"    ,    (PyCFunction)pyBOText_getSize              , METH_NOARGS     ,   ""   },
        {        "getText"    ,    (PyCFunction)pyBOText_getText              , METH_NOARGS     ,   ""   },
        {        "setAlign"   ,    (PyCFunction)pyBOText_setAlign             , METH_VARARGS    ,   ""   },
        {        "setColor"   ,    (PyCFunction)pyBOText_setColor             , METH_VARARGS    ,   ""   },
        {        "setFontRef" ,    (PyCFunction)pyBOText_setFontRef           , METH_VARARGS    ,   ""   },
        {        "setSize"    ,    (PyCFunction)pyBOText_setSize              , METH_VARARGS    ,   ""   },
        {        "setText"    ,    (PyCFunction)pyBOText_setText              , METH_VARARGS    ,   ""   },
        {           NULL      ,                       NULL                    , 0               ,  NULL  } /* Sentinel */
    };
    
    static PyTypeObject pyBOText_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BOText",
    sizeof(pyBOText),          /*tp_basicsize*/
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
    "BOText maratis object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBOText_methods,          /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    0,             /* tp_new */

    };
#endif