#include <Python.h>
#include "structmember.h"


#ifndef _PY_BOSprite_H
#define _PY_BOSprite_H

#include "pyBObject3d.h"
#include "pyBFontRef.h"

typedef struct {
        pyBObject3d obj;
} pyBOSprite;

    
static PyObject* pyBOSprite_addText(pyBOSprite* self, PyObject* args){
    unsigned int tile;

    pyBFontRef * fontRef;
    char* text = (char*)"";

    if (!PyArg_ParseTuple(args, "O!|s" , &pyBFontRef_type, &fontRef, &text )){
        //PyErr_SetString(PyExc_AttributeError, "parameters error");
        return NULL;
    }
    //((BOSprite*)self->obj.object)->addText(fontRef, text);
    
    return Py_BuildValue("I", ((BOSprite*)self->obj.object)->addText(fontRef->fontRef, text) );
}


static PyObject* pyBOSprite_setColor(pyBOSprite* self, PyObject* args)
{
    pyUVector3 * color;
    if (!PyArg_ParseTuple(args, "O!", &pyUVector3_type, &color)){
        //PyErr_SetString(PyExc_AttributeError, "parameters is: setTextSize(<float>Name)");
        return NULL;  
    }else{
        ((BOSprite*)self->obj.object)->setColor( color->vector );
    }
    Py_INCREF(Py_None);
    return Py_None;    
}


static PyObject* pyBOSprite_setRotationType(pyBOSprite* self, PyObject* args){
    int type;
    if (!PyArg_ParseTuple(args, "i",&type)){
        PyErr_SetString(PyExc_AttributeError, "parameters error");
        return NULL;
    }
    ((BOSprite*)self->obj.object)->setRotationType( (BSpriteRotate)type );
    
    Py_INCREF(Py_None);
    return Py_None;
}




static PyObject* pyBOSprite_setText(pyBOSprite* self, PyObject* args)
{
    char* name;
    unsigned int id = 0u;
    
    if (!PyArg_ParseTuple(args, "s|I", &name, &id )){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setText(<string>Name, <integer>id)");
        return NULL;  
    }else{
        ((BOSprite*)self->obj.object)->setText(name, id);
    }
    Py_INCREF(Py_None);
    return Py_None;    
}

static PyObject* pyBOSprite_setTextHAling(pyBOSprite* self, PyObject* args)
{
    int align;
    unsigned int id = 0u;
    
    if (!PyArg_ParseTuple(args, "i|I", &align, &id)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setTextHAling(<gui_align>aling, <integer>id )");
        return NULL;  
    }else{
        ((BOSprite*)self->obj.object)->setHAling( (gui_align)align, id );

    }
    Py_INCREF(Py_None);
    return Py_None; 
}


static PyObject* pyBOSprite_setTextVAling(pyBOSprite* self, PyObject* args)
{
    int align;
    unsigned int id = 0u;
    
    if (!PyArg_ParseTuple(args, "i|I", &align, &id)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setTextVAling(<gui_align>aling, <integer>id )");
        return NULL;  
    }else{
        ((BOSprite*)self->obj.object)->setVAling( (gui_align)align, id );

    }
    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBOSprite_setTextColor(pyBOSprite* self, PyObject* args)
{
    pyUVector4 * color;
    unsigned int id = 0u;
    if (!PyArg_ParseTuple(args, "O!|I", &pyUVector4_type, &color , &id)){
        //PyErr_SetString(PyExc_AttributeError, "parameters is: setTextSize(<float>Name)");
        return NULL;  
    }else{
        ((BOSprite*)self->obj.object)->setTextColor( color->vector,id );
    }
    Py_INCREF(Py_None);
    return Py_None;    
}

static PyObject* pyBOSprite_setTextPositionOffset(pyBOSprite* self, PyObject* args)
{
    float x;
    float y = .0f;
    float z = .0f;
    unsigned int id = 0u;
    if (!PyArg_ParseTuple(args, "f|ffI", &x, &y, &z, &id)){
        pyUVector3 * pos;
        if (PyArg_ParseTuple(args, "O!|I", &pyUVector3_type, &pos, &id)){
            PyErr_Clear();
            ((BOSprite*)self->obj.object)->setTextPositionOffset(pos->vector, id);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setTextPositionOffset(<float>x, <float>y, <float>z) or setTextPositionOffset(<MVector3>rotation)");
            return NULL;
        }
    }else{
        ((BOSprite*)self->obj.object)->setTextPositionOffset(BVector3f(x,y,z), id);
    }
    Py_INCREF(Py_None);
    return Py_None;      
}

static PyObject* pyBOSprite_setTextSize(pyBOSprite* self, PyObject* args)
{
    float size;
    unsigned int id = 0u;
    if (!PyArg_ParseTuple(args, "f|I", &size, &id)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setTextSize(<float>Name)");
        return NULL;  
    }else{
        ((BOSprite*)self->obj.object)->setTextSize( size,id );
    }
    Py_INCREF(Py_None);
    return Py_None;    
}


static PyObject* pyBOSprite_setTilesNumber(pyBOSprite* self, PyObject* args){
    unsigned int M,N;
    if (!PyArg_ParseTuple(args, "II",&M, &N)){
        PyErr_SetString(PyExc_AttributeError, "parameters error");
        return NULL;
    }
    ((BOSprite*)self->obj.object)->setTilesNumber(M, N);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBOSprite_setTile(pyBOSprite* self, PyObject* args){
    unsigned int tile;
    if (!PyArg_ParseTuple(args, "I",&tile)){
        PyErr_SetString(PyExc_AttributeError, "parameters error");
        return NULL;
    }
    ((BOSprite*)self->obj.object)->setTile(tile);
    
    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject* pyBOSprite_getColor(pyBOSprite* self)
{
    pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
    color->vector = ((BOSprite*)self->obj.object)->getColor();

    Py_INCREF(color);
    return (PyObject*)color;
}

static PyObject* pyBOSprite_getTilesNumber(pyBOSprite* self)
{
    return Py_BuildValue("I",((BOSprite*)self->obj.object)->getTilesNumber()  );
}

static PyObject* pyBOSprite_getRotationType(pyBOSprite* self)
{
    return Py_BuildValue("i",((BOSprite*)self->obj.object)->getRotationType()  );
}


static PyMethodDef pyBOSprite_methods[] = {
    {   "addText"            , (PyCFunction)pyBOSprite_addText              , METH_VARARGS, ""},
    {   "getColor"           , (PyCFunction)pyBOSprite_getColor             , METH_VARARGS, ""},
    {   "getRotationType"    , (PyCFunction)pyBOSprite_getRotationType      , METH_NOARGS , ""},
    {   "getTilesNumber"     , (PyCFunction)pyBOSprite_getTilesNumber       , METH_NOARGS , ""},
    {   "setColor"           , (PyCFunction)pyBOSprite_setColor             , METH_VARARGS, ""},
    {   "setRotationType"    , (PyCFunction)pyBOSprite_setRotationType      , METH_VARARGS , ""},
    {   "setText"            , (PyCFunction)pyBOSprite_setText              , METH_VARARGS, ""},
    {   "setTextColor"       , (PyCFunction)pyBOSprite_setTextColor         , METH_VARARGS, ""},
    {   "setTextHAlign"      , (PyCFunction)pyBOSprite_setTextHAling        , METH_VARARGS, ""},
    {   "setTextVAlign"      , (PyCFunction)pyBOSprite_setTextVAling        , METH_VARARGS, ""},
    {   "setTextPositionOffset",(PyCFunction)pyBOSprite_setTextPositionOffset, METH_VARARGS, ""},
    {   "setTextSize"        , (PyCFunction)pyBOSprite_setTextSize          , METH_VARARGS, ""},
    {   "setTilesNumber"     , (PyCFunction)pyBOSprite_setTilesNumber       , METH_VARARGS, ""},
    {   "setTile"            , (PyCFunction)pyBOSprite_setTile              , METH_VARARGS, ""},
    
    {NULL, NULL, 0, NULL} /* Sentinel */
};


static PyTypeObject pyBOSprite_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BOSprite",
    sizeof(pyBOSprite),        /*tp_basicsize*/
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
    "BOSprite Bizarre object",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBOSprite_methods,        /* tp_methods */
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

//PyTypeObject* ppyBOSprite_type = &pyBOSprite_type;

//PyTypeObject* ppyBOSprite_type =  &pyBOSprite_type;

#endif