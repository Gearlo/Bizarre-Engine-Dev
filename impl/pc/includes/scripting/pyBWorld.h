#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#include "pyBScene.h"
#include "pyBMeshRef.h"
//#include "pyBSoundRef.cpp"
#include "pyBFontRef.h"




#ifndef _PY_M_world_TYPE
#define _PY_M_world_TYPE

//#include <bizarre/core/BGlobalVars.h>
 
typedef struct {
    PyObject_HEAD
    BWorld * world = NULL;
} pyBWorld;



static PyObject * pyBWorld_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    
    pyBWorld* self;
    self = (pyBWorld *)type->tp_alloc(type, 0);
    if (self == NULL)
    {
        Py_RETURN_NONE;
    }
    self->world = Bizarre::getInstance()->getWorld();

    return (PyObject *)self;
}

static void pyBWorld_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


static PyObject* pyBWorld_addNewScene(pyBWorld* self)
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->addNewScene();
    return (PyObject *)sc;
}

static PyObject* pyBWorld_addNewScene2d(pyBWorld* self)
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->addNewScene2d();
    return (PyObject *)sc;
}


static PyObject* pyBWorld_addNewSceneToLayer(pyBWorld* self, PyObject* args)
{
    unsigned int layer;
    if (!PyArg_ParseTuple(args, "I", &layer)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: addNewSceneToLayer(<int>layers)");
        return NULL;
    }

    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->addNewSceneToLayer( (BSceneLayer)layer );
    return (PyObject *)sc;
}


static PyObject* pyBWorld_addNewScene2dToLayer(pyBWorld* self, PyObject* args)
{
    unsigned int layer;
    if (!PyArg_ParseTuple(args, "I", &layer)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: addNewSceneToLayer(<int>layers)");
        return NULL;
    }

    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->addNewScene2dToLayer( (BSceneLayer)layer );
    return (PyObject *)sc;
}


static PyObject* pyBWorld_clearScenes(pyBWorld* self)
{
    self->world->clearScenes();
    Py_RETURN_NONE;
}

static PyObject* pyBWorld_deleteScene(pyBWorld* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: deleteScene(<int>sceneIndex)");
        return NULL;
    }
    
    self->world->deleteScene(index);
    Py_RETURN_NONE;
}

static PyObject* pyBWorld_getCurrentScene(pyBWorld* self)
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->getCurrentScene();
    return (PyObject *)sc;
}

static PyObject* pyBWorld_getCurrentSceneId(pyBWorld* self)
{
    return Py_BuildValue("I", self->world->getCurrentSceneId());
}

static PyObject* pyBWorld_getSceneByIndex(pyBWorld* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByIndex(<int>objectIndex)");
        return NULL;
    }
    
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->getSceneByIndex(index);
    return (PyObject *)sc;    
}


static PyObject* pyBWorld_getSceneByLayer(pyBWorld* self, PyObject* args) // poder devolver un BScene2d en caso de la escena lo sea
{
    unsigned int layer;
    if (!PyArg_ParseTuple(args, "I", &layer)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByLayer(<int>layer)");
        return NULL;
    }
    
    BScene* scene = self->world->getSceneByLayer( (BSceneLayer)layer );
    if ( !scene ){ Py_RETURN_NONE; }


    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = scene;
    return (PyObject *)sc;    
}

static PyObject* pyBWorld_getSceneByName(pyBWorld* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByName(<string>name)");
        return NULL;
    }
    
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->getSceneByName(name);
    return (PyObject *)sc;
}


static PyObject* pyBWorld_getSceneLayersNumber(pyBWorld* self)
{
    return Py_BuildValue("I", self->world->getSceneLayersNumber());
}

static PyObject* pyBWorld_getScenesNumber(pyBWorld* self)
{
    return Py_BuildValue("I", self->world->getScenesNumber());
}



static PyObject* pyBWorld_setCurrentSceneId(pyBWorld* self, PyObject* args) // ¿Es necesario aun?
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setCurrentSceneId(<int>sceneIndex)");
        return NULL;
    }
    
    self->world->setCurrentSceneId(index);
    Py_RETURN_NONE;

}









static PyObject* pyBWorld_getGuiScene(pyBWorld* self) // eliminar
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->getGuiScene();
    return (PyObject *)sc;
}

static PyObject* pyBWorld_getSkyScene(pyBWorld* self) // eliminar
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->getSkyScene();
    return (PyObject *)sc;
}

static PyObject* pyBWorld_getWorldScene(pyBWorld* self) // eliminar
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->world->getWorldScene();
    return (PyObject *)sc;
}


static PyMethodDef BWorld_methods[] = {
    {    "addNewScene"         , (PyCFunction)pyBWorld_addNewScene        , METH_NOARGS  , ""},
    {    "addNewScene2d"       , (PyCFunction)pyBWorld_addNewScene2d      , METH_NOARGS  , ""},
    {    "addNewSceneToLayer"  , (PyCFunction)pyBWorld_addNewSceneToLayer , METH_NOARGS  , ""},
    {    "addNewScene2dToLayer", (PyCFunction)pyBWorld_addNewScene2dToLayer , METH_NOARGS  , ""},
    {    "clearScenes"         , (PyCFunction)pyBWorld_clearScenes        , METH_NOARGS  , ""},
    {    "deleteScene"         , (PyCFunction)pyBWorld_deleteScene        , METH_VARARGS , ""},
    {    "getCurrentScene"     , (PyCFunction)pyBWorld_getCurrentScene    , METH_NOARGS  , ""},
    {    "getCurrentSceneId"   , (PyCFunction)pyBWorld_getCurrentSceneId  , METH_NOARGS  , ""},
    {    "getSceneByIndex"     , (PyCFunction)pyBWorld_getSceneByIndex    , METH_VARARGS , ""},
    {    "getSceneByName"      , (PyCFunction)pyBWorld_getSceneByName     , METH_VARARGS , ""},
    {    "getSceneLayersNumber", (PyCFunction)pyBWorld_getSceneLayersNumber, METH_NOARGS , ""},
    {    "getScenesNumber"     , (PyCFunction)pyBWorld_getScenesNumber    , METH_NOARGS  , ""},
    {    "setCurrentSceneId"   , (PyCFunction)pyBWorld_setCurrentSceneId  , METH_VARARGS , ""},
    {    "getGuiScene"         , (PyCFunction)pyBWorld_getGuiScene        , METH_NOARGS , ""},
    {    "getWorldScene"       , (PyCFunction)pyBWorld_getWorldScene      , METH_NOARGS , ""},
    {    "getSkyScene"         , (PyCFunction)pyBWorld_getSkyScene        , METH_NOARGS , ""},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyBWorld_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BWorld",
    sizeof(pyBWorld),         /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBWorld_dealloc,/*tp_dealloc*/
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
    "",   /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    BWorld_methods,           /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,            /* tp_init */
    0,                         /* tp_alloc */
    pyBWorld_new,             /* tp_new */

};
#endif