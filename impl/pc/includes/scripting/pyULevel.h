#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>

#include "pyBScene.h"
#include "pyBMeshRef.h"
//#include "pyBSoundRef.cpp"
#include "pyBFontRef.h"




#ifndef _PY_M_LEVEL_TYPE
#define _PY_M_LEVEL_TYPE

//#include <bizarre/core/BGlobalVars.h>
 
typedef struct {
    PyObject_HEAD
    BAssetsManager * level = NULL;
} pyBAssetsManager;



static PyObject * pyBAssetsManager_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    
    pyBAssetsManager* self;
    self = (pyBAssetsManager *)type->tp_alloc(type, 0);
    if (self == NULL)
    {
        Py_RETURN_NONE;
    }
     
    return (PyObject *)self;
}

static PyObject* pyBAssetsManager_clear(pyBAssetsManager* self)
{
    self->level->clear();
    Py_RETURN_NONE;
}


/*static PyObject* pyBAssetsManager_addNewScene(pyBAssetsManager* self)
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->level->addNewScene();
    return (PyObject *)sc;
}


static PyObject* pyBAssetsManager_clearScenes(pyBAssetsManager* self)
{
    self->level->clearScenes();
    Py_RETURN_NONE;
}

static PyObject* pyBAssetsManager_deleteScene(pyBAssetsManager* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: deleteScene(<int>sceneIndex)");
        return NULL;
    }
    
    self->level->deleteScene(index);
    Py_RETURN_NONE;
}

static PyObject* pyBAssetsManager_getCurrentScene(pyBAssetsManager* self)
{
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->level->getCurrentScene();
    return (PyObject *)sc;
}

static PyObject* pyBAssetsManager_getCurrentSceneId(pyBAssetsManager* self)
{
    return Py_BuildValue("I", self->level->getCurrentSceneId());
}

static PyObject* pyBAssetsManager_getSceneByIndex(pyBAssetsManager* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByIndex(<int>objectIndex)");
        return NULL;
    }
    
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->level->getSceneByIndex(index);
    return (PyObject *)sc;    
}

static PyObject* pyBAssetsManager_getSceneByName(pyBAssetsManager* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByName(<string>name)");
        return NULL;
    }
    
    pyBScene* sc = PyObject_New(pyBScene, &pyBScene_type);
    sc->scene = self->level->getSceneByName(name);
    return (PyObject *)sc;
}


static PyObject* pyBAssetsManager_getScenesNumber(pyBAssetsManager* self)
{
    return Py_BuildValue("I", self->level->getScenesNumber());
}
*/

static PyObject* pyBAssetsManager_loadFont(pyBAssetsManager* self, PyObject* args)
{
    char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: loadFont(<string>absolutePath)");
        return NULL;
    }
    
    pyBFontRef* f = PyObject_New(pyBFontRef, &pyBFontRef_type);
    f->fontRef = self->level->loadFont(filename);
    return (PyObject *)f;    
}


static PyObject* pyBAssetsManager_loadMesh(pyBAssetsManager* self, PyObject* args)
{
    char* filename; bool preload = true;
    if (!PyArg_ParseTuple(args, "s|b", &filename, &preload)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByIndex(<int>absolutePath)");
        return NULL;
    }
    
    pyBMeshRef* ms = PyObject_New(pyBMeshRef, &pyBMeshRef_type);
    
    //char file[500];
    //getGlobalFilename(file, globalInfo::getInstance()->getWorkingDirectory(), filename);
    
    //ms->meshRef = self->level->loadMesh( file, preload);
    ms->meshRef = self->level->loadMesh(filename, preload);
    
   



    return (PyObject *)ms;
    
}

static PyObject* pyBAssetsManager_loadTexture(pyBAssetsManager* self, PyObject* args)
{
    char* filename; bool mipmap = true; bool preload = true;
    if (!PyArg_ParseTuple(args, "s|bb", &filename, &mipmap, &preload)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByIndex(<int>absolutePath)");
        return NULL;
    }
    
    pyBTextureRef* tx = PyObject_New(pyBTextureRef, &pyBTextureRef_type);
    tx->textureRef = self->level->loadTexture(filename, mipmap, preload);
    return (PyObject *)tx;
}

//static PyObject* pyBAssetsManager_loadSound(pyBAssetsManager* self, PyObject* args)
//{
//    char* filename; bool preload = true;
//    if (!PyArg_ParseTuple(args, "s|b", &filename, &preload)){
//        PyErr_SetString(PyExc_AttributeError, "parameters is: loadSound(<int>absolutePath)");
//        return NULL;
//    }
//    
//    pyBSoundRef* s = PyObject_New(pyBSoundRef, &pyBSoundRef_type);
//    s->soundRef = self->level->loadSound(filename, preload);
//    return (PyObject *)s;    
//}



/*static PyObject* pyBAssetsManager_setCurrentSceneId(pyBAssetsManager* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setCurrentSceneId(<int>sceneIndex)");
        return NULL;
    }
    
    self->level->setCurrentSceneId(index);
    Py_RETURN_NONE;

}*/


static PyMethodDef BAssetsManager_methods[] = {
//    {    "addNewScene"       , (PyCFunction)pyBAssetsManager_addNewScene        , METH_NOARGS  , ""},
    {    "clear"             , (PyCFunction)pyBAssetsManager_clear              , METH_NOARGS  , ""},
//    {    "clearScenes"       , (PyCFunction)pyBAssetsManager_clearScenes        , METH_NOARGS  , ""},
//    {    "deleteScene"       , (PyCFunction)pyBAssetsManager_deleteScene        , METH_VARARGS , ""},
//    {    "getCurrentScene"   , (PyCFunction)pyBAssetsManager_getCurrentScene    , METH_NOARGS  , ""},
//    {    "getCurrentSceneId" , (PyCFunction)pyBAssetsManager_getCurrentSceneId  , METH_NOARGS  , ""},
//    {    "getSceneByIndex"   , (PyCFunction)pyBAssetsManager_getSceneByIndex    , METH_VARARGS  , ""},
//    {    "getSceneByName"    , (PyCFunction)pyBAssetsManager_getSceneByName     , METH_VARARGS  , ""},
 //   {    "getScenesNumber"   , (PyCFunction)pyBAssetsManager_getScenesNumber    , METH_NOARGS  , ""},
    {    "loadFont"          , (PyCFunction)pyBAssetsManager_loadFont           , METH_VARARGS , ""},
    {    "loadMesh"          , (PyCFunction)pyBAssetsManager_loadMesh           , METH_VARARGS , ""},
    {    "loadTexture"       , (PyCFunction)pyBAssetsManager_loadTexture        , METH_VARARGS , ""},
  //{    "loadSound"         , (PyCFunction)pyBAssetsManager_loadSound          , METH_VARARGS , ""},
//    {    "setCurrentSceneId" , (PyCFunction)pyBAssetsManager_setCurrentSceneId  , METH_VARARGS , ""},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyBAssetsManager_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BAssetsManager",
    sizeof(pyBAssetsManager),         /*tp_basicsize*/
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
    "BAssetsManager maratis object",   /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    BAssetsManager_methods,           /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,            /* tp_init */
    0,                         /* tp_alloc */
    pyBAssetsManager_new,             /* tp_new */

};
#endif