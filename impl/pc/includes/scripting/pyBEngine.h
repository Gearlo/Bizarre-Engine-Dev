/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pyBEngine.h
 * Author: ariel
 *
 * Created on 10 de octubre de 2018, 10:04 PM
 */

#ifndef pyBEngine_H
#define pyBEngine_H

#include "pyBArmature.h"
#include "pyBAssetsManager.h"
#include "pyBDisplay.h"
#include "pyBFontRef.h"
#include "pyBGame.h"
#include "pyBImage.h"
#include "pyBInputContext.h"
#include "pyBMaterial.h"
#include "pyBSubMesh.h"
#include "pyBMesh.h"
#include "pyBMeshRef.h"
#include "pyBOBone.h"
#include "pyBOCamera.h"
#include "pyBOLight.h"
#include "pyBOSound.h"
#include "pyBOSprite.h"
#include "pyBOText.h"
#include "pyBObject3d.h"
//#include "pyBPackageManager.h"
#include "pyBPhysicsContext.h"
#include "pyBPhysicsProperties.h"
#include "pyBRenderInfo.h"
#include "pyBScene.h"
#include "pyBSoundRef.h"
#include "pyBSystemContext.h"
#include "pyBTexture.h"
#include "pyBTextureRef.h"
#include "pyUVector.h"
#include "pyBWorld.h"


//#include <BScriptGame.h>

typedef struct {
    PyObject_HEAD
    Bizarre * engine = NULL;
} pyBEngine;

static PyObject* pyBEngine_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBEngine *self;
    self = (pyBEngine *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->engine = Bizarre::getInstance();
    }else{
        Py_RETURN_NONE;
    }
    
    return (PyObject *)self;
    //self->engine->getPackageManager()
    
}

static void pyBEngine_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

/*static PyObject* Bizarre_loadlevel(pyBEngine* self, PyObject* args)
{
    char * filePath;
    if (!PyArg_ParseTuple(args, "s", &filePath)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: loadlevel(<string>absolutePath)");
        return NULL;
    }
    
    return Py_BuildValue("b",self->engine->loadLevel(filePath));
}*/

static PyObject* Bizarre_getAssetsManager(pyBEngine* self)
{
    pyBAssetsManager* assetsManager = PyObject_New(pyBAssetsManager, &pyBAssetsManager_type);
    assetsManager->level = self->engine->getAssetsManager();

    return (PyObject *)assetsManager;    
}

static PyObject* Bizarre_getInputContext(pyBEngine* self)
{
    pyUwinputContext* in = PyObject_New(pyUwinputContext, &pyUwinputContext_type);
    in->input = self->engine->getInputContext();
    return (PyObject *)in;    
}


/*static PyObject* Bizarre_getPackageManager(pyBEngine* self)
{
    pyBPackageManager* pm = PyObject_New(pyBPackageManager, &pyBPackageManager_type);
    pm->packageManager = self->engine->getPackageManager();
    return (PyObject *)pm;    
}*/


static PyObject* Bizarre_getPhysicsContext(pyBEngine* self)
{
    pyBPhysicsContext* in = PyObject_New(pyBPhysicsContext, &pyBPhysicsContext_type);
    in->phy = self->engine->getPhysicsContext();
    return (PyObject *)in;    
}


static PyObject* Bizarre_getRenderInfo(pyBEngine* self)
{
    pyBRenderInfo* renderInfo = PyObject_New(pyBRenderInfo, &pyBRenderInfo_type);
    renderInfo->renderInfo = BRenderInfo::getInstance();
    return (PyObject *)renderInfo;    
}


static PyObject* Bizarre_getSystemContext(pyBEngine* self)
{
    pyBSystemContext* sys = PyObject_New(pyBSystemContext, &pyBSystemContext_type);
    sys->system = self->engine->getSystemContext();
    return (PyObject *)sys;    
}

static PyObject* Bizarre_getWorld(pyBEngine* self)
{
    pyBWorld* world = PyObject_New(pyBWorld, &pyBWorld_type);
    world->world = self->engine->getWorld();
    return (PyObject *)world;    
}


static PyObject* Bizarre_start(pyBEngine* self, PyObject *args, PyObject *kwds)
{
    //pyBWorld* world = PyObject_New(pyBWorld, &pyBWorld_type);
    //world->level = self->engine->getWorld();
    //return (PyObject *)world;
    static char *kwlist[] = {(char*)"window_width", 
                             (char*)"window_height", 
                             (char*)"window_fullscreen", 
                             (char*)"window_title",
                             (char*)"renderer_name",
                             (char*)"game", NULL};    

    BStartConfig config;
    BScript* pyGame;

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|IIbssO", kwlist, &config.window_width, 
                                                                  &config.window_height, 
                                                                  &config.window_fullscreen,
                                                                  &config.window_title,
                                                                  &config.renderer_name,
                                                                  &pyGame)){
       PyErr_SetString(PyExc_AttributeError, "Param Err on start");
    }

    //Py_INCREF(pyGame);
    BGame * game = new BGame();
    game->setScript( pyGame );
    config.game = game;
    Bizarre::getInstance()->start(config);
    Py_RETURN_NONE;
}


static PyObject* Bizarre_changeGame(pyBEngine* self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {(char*)"newGame", 
                             (char*)"restartScenes", 
                             (char*)"restartAssets", NULL}; 
    
    PyObject* pyGame;
    bool restartScenes   = true;
    bool restartAssets   = true;
    bool restartScripting = false;

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "O|bb", kwlist,&pyGame, 
                                                                  &restartScenes, 
                                                                  &restartAssets)){
       //PyErr_SetString(PyExc_AttributeError, "Param Err on start");
       return NULL;
    }

    
    Bizarre* engine = Bizarre::getInstance();
    
    Py_INCREF(pyGame);
    BGame * game = new BGame();
    game->setScript( pyGame );
    engine->setGame(game, restartScenes, restartAssets );

    Py_RETURN_NONE;
}

static PyMethodDef Bizarre_methods[] = {
    //,
    {   "setGame"        , (PyCFunction)Bizarre_changeGame               , METH_KEYWORDS, ""},
    {   "getAssetsManager"  , (PyCFunction)Bizarre_getAssetsManager         , METH_VARARGS , ""},
    {   "getInputContext"   , (PyCFunction)Bizarre_getInputContext          , METH_NOARGS  , ""},
//    {   "getPackageManager" , (PyCFunction)Bizarre_getPackageManager      , METH_NOARGS  , ""},
    {   "getRenderInfo"     , (PyCFunction)Bizarre_getRenderInfo            , METH_NOARGS  , ""},
    {   "getPhysicsContext" , (PyCFunction)Bizarre_getPhysicsContext        , METH_NOARGS  , ""},
    {   "getSystemContext"  , (PyCFunction)Bizarre_getSystemContext         , METH_NOARGS  , ""},
    {   "getWorld"          , (PyCFunction)Bizarre_getWorld                 , METH_NOARGS  , ""},
    {   "start"             , (PyCFunction)Bizarre_start                    , METH_KEYWORDS, ""},
    {NULL, NULL, 0, NULL} /* Sentinel */
};


static PyTypeObject pyBEngine_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "Bizarre",
    sizeof(pyBEngine),         /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBEngine_dealloc,/*tp_dealloc*/
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
    Bizarre_methods,           /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,            /* tp_init */
    0,                         /* tp_alloc */
    pyBEngine_new,             /* tp_new */

};

#endif /* pyBEngine_H */

