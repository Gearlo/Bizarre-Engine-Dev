#ifndef __PY_U_SUB_MESH_H_
#define __PY_U_SUB_MESH_H_

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#include "pyBDisplay.h"
#include "pyBSkinData.h"
#include "pyUVector.h"


typedef struct {
    PyObject_HEAD
    BSubMesh* submesh;
} pyBSubMesh;


static PyObject * pyBSubMesh_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBSubMesh *self;
    self = (pyBSubMesh *)type->tp_alloc(type, 0);

    return (PyObject *)self;
}

static int pyBSubMesh_init(pyBSubMesh *self, PyObject *args, PyObject *kwds)
{ 
    self->submesh = new BSubMesh();
    return 0;
}

static void pyBSubMesh_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


static PyObject* pyBSubMesh_allocColors(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->submesh->allocColors(i);

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_allocDisplays(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->submesh->allocDisplays(i);

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_allocIndices(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    int type;

    if (!PyArg_ParseTuple(args, "Ii", &i, &type ))
        return NULL;

    self->submesh->allocIndices(i, (U_TYPES)type );

    Py_INCREF(Py_None);
    return Py_None; 
}



static PyObject* pyBSubMesh_allocVertices(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->submesh->allocVertices(i);

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_allocNormals(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->submesh->allocNormals(i);
    
    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_allocTangents(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->submesh->allocTangents(i);

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_allocTexCoords(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    self->submesh->allocTexCoords(i);

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_addNewDisplay(pyBSubMesh* self, PyObject* args)
{
    int primitiveTypes;
    unsigned int begin;
    unsigned int size;

    if (!PyArg_ParseTuple(args, "iII", &primitiveTypes, &begin, &size ))
        return NULL;

    BDisplay * _display = self->submesh->addNewDisplay((U_PRIMITIVE_TYPES)primitiveTypes, begin, size);

    if(!_display){
        Py_INCREF(Py_None);
        return Py_None; 
    }
    
    pyBDisplay* display = PyObject_New(pyBDisplay, &pyBDisplay_type);
    display->display = _display;  
    return (PyObject *)display;
}

static PyObject* pyBSubMesh_clearColors(pyBSubMesh* self){
    self->submesh->clearColors(); Py_INCREF(Py_None); return Py_None; }

static PyObject* pyBSubMesh_clearDisplays(pyBSubMesh* self){
    self->submesh->clearDisplays(); Py_INCREF(Py_None);return Py_None; }

static PyObject* pyBSubMesh_clearIndices(pyBSubMesh* self){
    self->submesh->clearIndices();Py_INCREF(Py_None);return Py_None; }

static PyObject* pyBSubMesh_clearMapChannelOffset(pyBSubMesh* self){
    self->submesh->clearMapChannelOffset();Py_INCREF(Py_None);return Py_None; }

static PyObject* pyBSubMesh_clearMorphingData(pyBSubMesh* self){
    self->submesh->clearMorphingData();Py_INCREF(Py_None);return Py_None; }

static PyObject* pyBSubMesh_clearNormals(pyBSubMesh* self){
    self->submesh->clearNormals();Py_INCREF(Py_None);return Py_None; }

static PyObject* pyBSubMesh_clearSkinData(pyBSubMesh* self){
    self->submesh->clearSkinData();Py_INCREF(Py_None);return Py_None; }

static PyObject* pyBSubMesh_clearTangents(pyBSubMesh* self){
    self->submesh->clearTangents();Py_INCREF(Py_None);return Py_None; }

static PyObject* pyBSubMesh_clearTexCoords(pyBSubMesh* self){
    self->submesh->clearTexCoords();Py_INCREF(Py_None);return Py_None; }


static PyObject* pyBSubMesh_createSkinData(pyBSubMesh* self)
{
    BSkinData * _skindata = self->submesh->createSkinData();

    if(!_skindata){
        Py_INCREF(Py_None);
        return Py_None; 
    }
    
    pyBSkinData* skindata = PyObject_New(pyBSkinData, &pyBSkinData_type);
    skindata->skindata = _skindata;  
    return (PyObject *)skindata;
}

static PyObject* pyBSubMesh_getColorsNumber(pyBSubMesh* self){
        return Py_BuildValue("I",self->submesh->getColorsSize());
}

static PyObject* pyBSubMesh_getDisplaysNumber(pyBSubMesh* self){
        return Py_BuildValue("I",self->submesh->getDisplaysNumber());
}

static PyObject* pyBSubMesh_getVerticesNumber(pyBSubMesh* self){
        return Py_BuildValue("I",self->submesh->getVerticesSize());
}

static PyObject* pyBSubMesh_getNormalsNumber(pyBSubMesh* self){
        return Py_BuildValue("I",self->submesh->getNormalsSize());
}

static PyObject* pyBSubMesh_getTangetsNumber(pyBSubMesh* self){
        return Py_BuildValue("I",self->submesh->getTangentsSize());
}

static PyObject* pyBSubMesh_getUVsNumber(pyBSubMesh* self){
        return Py_BuildValue("I",self->submesh->getTexCoordsSize());
}

static PyObject* pyBSubMesh_getIndicesNumber(pyBSubMesh* self){
        return Py_BuildValue("I",self->submesh->getIndicesSize());
}

/*
static PyObject* pyBSubMesh_getColor(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->submesh->getColors() && i < self->submesh->getVerticesSize() ){
        BVector3f _color = self->submesh->getColors()[i];

        pyUVector3* color = PyObject_New(pyUVector3, &pyUVector3_type);
        color->vector = _color;  
        return (PyObject *)color;
    }

    Py_INCREF(Py_None);
    return Py_None; 
}
*/


static PyObject* pyBSubMesh_getDisplay(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    BDisplay * _display = self->submesh->getDisplay(i);

    if(!_display){
        Py_INCREF(Py_None);
        return Py_None; 
    }
    
    pyBDisplay* display = PyObject_New(pyBDisplay, &pyBDisplay_type);
    display->display = _display;  
    return (PyObject *)display;
}


static PyObject* pyBSubMesh_getIndice(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->submesh->getIndices() && i < self->submesh->getIndicesSize() ){
        switch(self->submesh->getIndicesType()){
            case U_USHORT:
                return Py_BuildValue("H", ((unsigned short *)self->submesh->getIndices())[i] );
                //break;

            case U_UINT:
            default:
                return Py_BuildValue("I", ((unsigned int *)self->submesh->getIndices())[i] );
                //break;
        }
    }

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_getNormal(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->submesh->getNormals() && i < self->submesh->getNormalsSize() ){
        BVector3f _normal = self->submesh->getNormals()[i];

        pyUVector3* normal = PyObject_New(pyUVector3, &pyUVector3_type);
        normal->vector = _normal;  
        return (PyObject *)normal;
    }

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_getSkinData(pyBSubMesh* self)
{
    BSkinData * _skindata = self->submesh->getSkinData();

    if(!_skindata){
        Py_INCREF(Py_None);
        return Py_None; 
    }
    
    pyBSkinData* skindata = PyObject_New(pyBSkinData, &pyBSkinData_type);
    skindata->skindata = _skindata;  
    return (PyObject *)skindata;
}

static PyObject* pyBSubMesh_getTangent(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->submesh->getTangents() && i < self->submesh->getTangentsSize() ){
        BVector3f _tangent = self->submesh->getTangents()[i];

        pyUVector3* tangent = PyObject_New(pyUVector3, &pyUVector3_type);
        tangent->vector = _tangent;  
        return (PyObject *)tangent;
    }

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_getTexCoord(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->submesh->getTexCoords() && i < self->submesh->getTexCoordsSize() ){
        BVector3f _uv = self->submesh->getTexCoords()[i];

        pyUVector3* uv = PyObject_New(pyUVector3, &pyUVector3_type);
        uv->vector = _uv;  
        return (PyObject *)uv;
    }

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_getVertex(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    //pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "I", &i ))
        return NULL;

    if( self->submesh->getVertices() && i < self->submesh->getVerticesSize() ){
        BVector3f _vertex = self->submesh->getVertices()[i];

        pyUVector3* vertex = PyObject_New(pyUVector3, &pyUVector3_type);
        vertex->vector = _vertex;  
        return (PyObject *)vertex;
    }

    Py_INCREF(Py_None);
    return Py_None; 
}

/*
static PyObject* pyBSubMesh_setColor(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    pyUVector3 * color;

    if (!PyArg_ParseTuple(args, "IO!", &i, &pyUVector3_type, &color))
        return NULL;

    if( self->submesh->getColors() && i < self->submesh->getVerticesSize() )
        self->submesh->getColors()[i] = color->vector;

    Py_INCREF(Py_None);
    return Py_None; 
}
*/

static PyObject* pyBSubMesh_setVertex(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    pyUVector3 * vertex;

    if (!PyArg_ParseTuple(args, "IO!", &i, &pyUVector3_type, &vertex))
        return NULL;

    if( self->submesh->getVertices() && i < self->submesh->getVerticesSize() )
        self->submesh->getVertices()[i] = vertex->vector;

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_setNormal(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    pyUVector3 * normal;

    if (!PyArg_ParseTuple(args, "IO!", &i, &pyUVector3_type, &normal))
        return NULL;

    if( self->submesh->getNormals() && i < self->submesh->getNormalsSize() )
        self->submesh->getNormals()[i] = normal->vector;

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_setTangent(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    pyUVector3 * tanget;

    if (!PyArg_ParseTuple(args, "IO!", &i, &pyUVector3_type, &tanget))
        return NULL;

    if( self->submesh->getTangents() && i < self->submesh->getTangentsSize() )
        self->submesh->getTangents()[i] = tanget->vector;

    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_setTexCoord(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    pyUVector2 * texCoord;

    if (!PyArg_ParseTuple(args, "IO!", &i, &pyUVector3_type, &texCoord))
        return NULL;

    if( self->submesh->getTexCoords() && i < self->submesh->getTexCoordsSize() )
        self->submesh->getTexCoords()[i] = texCoord->vector;


    Py_INCREF(Py_None);
    return Py_None; 
}

static PyObject* pyBSubMesh_setIndice(pyBSubMesh* self, PyObject* args)
{
    unsigned int i;
    unsigned int indice;

    if (!PyArg_ParseTuple(args, "II", &i, &indice))
        return NULL;

    if( i < self->submesh->getIndicesSize() ){

        switch(self->submesh->getIndicesType()){
            case U_USHORT:{
                unsigned short * indices = (unsigned short *)self->submesh->getIndices();
                indices[i] = (unsigned short)indice;
            }break;

            case U_UINT:
            default:{
                unsigned int * indices = (unsigned int *)self->submesh->getIndices();
                indices[i] = (unsigned int)indice;
            }break;
        }
    }
    
    Py_INCREF(Py_None);
    return Py_None; 
}

static PyMethodDef pyBSubMesh_methods[] = {
    {   "addNewDisplay"     , (PyCFunction)pyBSubMesh_addNewDisplay      , METH_VARARGS ,  ""},
    {   "allocColors"       , (PyCFunction)pyBSubMesh_allocColors        , METH_VARARGS ,  ""},
    {   "allocDisplays"     , (PyCFunction)pyBSubMesh_allocDisplays      , METH_VARARGS ,  ""},
    {   "allocNormals"      , (PyCFunction)pyBSubMesh_allocNormals       , METH_VARARGS ,  ""},
    {   "allocIndices"      , (PyCFunction)pyBSubMesh_allocIndices       , METH_VARARGS ,  ""},
    {   "allocTangents"     , (PyCFunction)pyBSubMesh_allocTangents      , METH_VARARGS ,  ""},
    {   "allocTexCoords"    , (PyCFunction)pyBSubMesh_allocTexCoords     , METH_VARARGS ,  ""},
    {   "allocVertices"     , (PyCFunction)pyBSubMesh_allocVertices      , METH_VARARGS ,  ""},
    {   "clearColors"       , (PyCFunction)pyBSubMesh_clearColors        , METH_NOARGS  ,  ""},
    {   "clearDisplays"     , (PyCFunction)pyBSubMesh_clearDisplays      , METH_NOARGS  ,  ""},
    {   "clearIndices"      , (PyCFunction)pyBSubMesh_clearIndices       , METH_NOARGS  ,  ""},
    {   "clearMapChannelOffset", (PyCFunction)pyBSubMesh_clearMapChannelOffset, METH_NOARGS, ""},
    {   "clearNormals"      , (PyCFunction)pyBSubMesh_clearMorphingData       , METH_NOARGS  ,  ""},
    {   "clearNormals"      , (PyCFunction)pyBSubMesh_clearNormals       , METH_NOARGS  ,  ""},
    {   "clearSkinData"     , (PyCFunction)pyBSubMesh_clearSkinData      , METH_NOARGS  ,  ""},
    {   "clearTangents "    , (PyCFunction)pyBSubMesh_clearTangents      , METH_NOARGS  ,  ""},
    {   "clearTexCoords"    , (PyCFunction)pyBSubMesh_clearTexCoords     , METH_NOARGS  ,  ""},
    {   "createSkinData"    , (PyCFunction)pyBSubMesh_createSkinData     , METH_NOARGS  ,  ""},
//    {   "getColor"          , (PyCFunction)pyBSubMesh_getColor           , METH_VARARGS ,   ""},
    {   "getColorsNumber"   , (PyCFunction)pyBSubMesh_getColorsNumber    , METH_NOARGS  ,   ""},
    {   "getDisplay"        , (PyCFunction)pyBSubMesh_getDisplay         , METH_VARARGS ,   ""},
    {   "getDisplaysNumber" , (PyCFunction)pyBSubMesh_getDisplaysNumber  , METH_NOARGS  ,   ""},
    {   "getVertex"         , (PyCFunction)pyBSubMesh_getVertex          , METH_VARARGS ,   ""},
    {   "getVerticesNumber" , (PyCFunction)pyBSubMesh_getVerticesNumber  , METH_NOARGS  ,   ""},
    {   "getNormalsNumber"  , (PyCFunction)pyBSubMesh_getNormalsNumber   , METH_NOARGS  ,   ""},
    {   "getNormal"         , (PyCFunction)pyBSubMesh_getNormal          , METH_VARARGS ,   ""},
    {   "getSkinData"       , (PyCFunction)pyBSubMesh_getSkinData        , METH_NOARGS  ,   ""},
    {   "getTangetsNumber"  , (PyCFunction)pyBSubMesh_getTangetsNumber   , METH_NOARGS  ,   ""},
    {   "getTangent"        , (PyCFunction)pyBSubMesh_getTangent         , METH_VARARGS ,   ""},
    {   "getTexCoordsNumber", (PyCFunction)pyBSubMesh_getUVsNumber       , METH_NOARGS  ,   ""},
    {   "getTexCoord"       , (PyCFunction)pyBSubMesh_getTexCoord        , METH_VARARGS ,   ""},
    {   "getIndice"         , (PyCFunction)pyBSubMesh_getIndice          , METH_VARARGS ,   ""},
    {   "getIndicesNumber"  , (PyCFunction)pyBSubMesh_getIndicesNumber   , METH_NOARGS  ,   ""},
 //   {   "setColor"          , (PyCFunction)pyBSubMesh_setColor           , METH_VARARGS ,  ""},
    {   "setVertex"         , (PyCFunction)pyBSubMesh_setVertex          , METH_VARARGS ,  ""},
    {   "setNormal"         , (PyCFunction)pyBSubMesh_setNormal          , METH_VARARGS ,  ""},
    {   "setTangent"        , (PyCFunction)pyBSubMesh_setTangent         , METH_VARARGS ,  ""},
    {   "setTexCoord"       , (PyCFunction)pyBSubMesh_setTexCoord        , METH_VARARGS ,  ""},
    {   "setIndice"         , (PyCFunction)pyBSubMesh_setIndice          , METH_VARARGS ,  ""},
    {   NULL                , NULL                                       , 0            , NULL} /* Sentinel */
};

static PyTypeObject pyBSubMesh_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BSubMesh",
    sizeof(pyBSubMesh),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBSubMesh_dealloc, /*tp_dealloc*/
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
    pyBSubMesh_methods,           /* tp_methods */
    0,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)pyBSubMesh_init,           /* tp_init */
    0,                         /* tp_alloc */
    pyBSubMesh_new,             /* tp_new */

};

#endif