
#ifndef _PY_M_SCENE_TYPE
#define _PY_M_SCENE_TYPE
    #include <Python.h>
    #include "structmember.h"

    #include <Bizarre.h>

    #include "pyBObject3d.h"
    #include "pyBOCamera.h"
    #include "pyBOCompositedModel3d.h"
    #include "pyBOModel3d.h"
    #include "pyBOLight.h"
    #include "pyBOSprite.h"
    #include "pyBMeshRef.h"
    #include "pyBFontRef.h"
    #include "pyBOText.h"
    #include "pyBSoundRef.h"
    #include "pyBOSound.h"
 
typedef struct {
    PyObject_HEAD
    BScene * scene = NULL;
} pyBScene;
 
static PyObject* pyBScene_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBScene* self;
    self = (pyBScene *)type->tp_alloc(type, 0);
    if (self == NULL)
    {
        
        Py_RETURN_NONE;
    }
    
    return (PyObject *)self;
}

static void pyBScene_dealloc(PyObject *obj){
    Py_TYPE(obj)->tp_free(obj);     
}

static PyObject* pyBScene_addNewCamera(pyBScene* self)
{
    pyBOCamera* cam = PyObject_New(pyBOCamera, &pyBOCamera_type);
    cam->obj.object = ((BObject3d*)self->scene->addNewCamera());
    return (PyObject *)cam;
}

static PyObject* pyBScene_addNewCompositedModel(pyBScene* self, PyObject* args)
{    
    pyBOCompositedModel3d* cModel = PyObject_New(pyBOCompositedModel3d, &pyBOCompositedModel3d_type);
    cModel->cModel = self->scene->addNewCompositedModel();
    cModel->obj.object = (BObject3d*)cModel->cModel;

    return (PyObject *)cModel;  
}

static PyObject* pyBScene_addNewModel(pyBScene* self, PyObject* args)
{
    pyBMeshRef * mesh;
    pyBMeshRef * physicsMesh = NULL;
    if (!PyArg_ParseTuple(args, "O!|O!", &pyBMeshRef_type, &mesh, &pyBMeshRef_type, &physicsMesh )){
        PyErr_SetString(PyExc_AttributeError, "parameters is: addNewModel(<BMeshRef>meshRef)");
        return NULL;
    }
    
    if( !physicsMesh ) physicsMesh = mesh;
    pyBOModel3d* model = PyObject_New(pyBOModel3d, &pyBOModel3d_type);
    model->model = self->scene->addNewModel(mesh->meshRef, physicsMesh->meshRef);
    model->obj.object = (BObject3d*)model->model;

    return (PyObject *)model;  
}


static PyObject* pyBScene_addNewSprite(pyBScene* self, PyObject* args)
{

    pyBTextureRef * texture;
    float width = 0.1f;
    bool centered = false;

    if (!PyArg_ParseTuple(args, "O!|fb", &pyBTextureRef_type, &texture, &width, &centered )){
        PyErr_SetString(PyExc_AttributeError, "parameters errors");
        return NULL;
    }
    
    pyBOSprite* sprite = PyObject_New(pyBOSprite, &pyBOSprite_type);
    sprite->obj.object = (BObject3d*)self->scene->addNewSprite( texture->textureRef, width, centered);  

    Py_INCREF(sprite);
    return (PyObject *)sprite;  
}

static PyObject* pyBScene_addNewLight(pyBScene* self)
{
    pyBOLight* lgt = PyObject_New(pyBOLight, &pyBOLight_type);
    lgt->obj.object = ((BObject3d*)self->scene->addNewLight());
    return (PyObject *)lgt;
}

static PyObject* pyBScene_addNewSound(pyBScene* self, PyObject* args)
{
    pyBSoundRef * soundRef;
    if (!PyArg_ParseTuple(args, "O!", &pyBSoundRef_type, &soundRef)){
            return NULL;
    }
    
    pyBOSound* sound = PyObject_New(pyBOSound, &pyBOSound_type);
    sound->obj.object = (BObject3d*)self->scene->addNewSound(soundRef->soundRef);
    return (PyObject *)sound;
}

static PyObject* pyBScene_addNewText(pyBScene* self, PyObject* args)
{
    pyBFontRef * font;
    if (!PyArg_ParseTuple(args, "O", &font)){
            PyErr_SetString(PyExc_AttributeError, "parameters is: addNewText(<BFontRef>fontRef)");
            return NULL;
    }
    
    pyBOText* en = PyObject_New(pyBOText, &pyBOText_type);
    en->obj.object = (BObject3d*)self->scene->addNewText(font->fontRef);
    //((BOText*)en->obj.object)->setColor(BVector3f(1.0f,1.0f,1.0f));
    return (PyObject *)en;
    
}

static PyObject* pyBScene_deleteObject(pyBScene* self, PyObject* args)
{
    pyBObject3d* obj;
    if (!PyArg_ParseTuple(args, "O", &obj)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: deleteObject(<BObject3d>object)");
        return NULL;
    }
     
    self->scene->deleteObject(obj->object);
    Py_RETURN_NONE;   
}

static PyObject* pyBScene_getCurrentCamera(pyBScene* self)
{
    BOCamera * temp = self->scene->getCurrentCamera();
    if (temp){
        pyBOCamera* cam = PyObject_New(pyBOCamera, &pyBOCamera_type);
        cam->obj.object = (BObject3d*)temp;
        return (PyObject*)cam;
    }else{
        Py_RETURN_NONE;
    }
}

static PyObject* pyBScene_getCameraByIndex(pyBScene* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getLightByIndex(<int>objectIndex)");
        return NULL;
    }
    
    if(index < self->scene->getObjectsNumber()){
        pyBOCamera* obj = PyObject_New(pyBOCamera, &pyBOCamera_type);
        obj->obj.object = (BObject3d*)self->scene->getCameraByIndex(index);
        return (PyObject *)obj;  
    }else{
        Py_RETURN_NONE;
    }     
}

static PyObject* pyBScene_getCameraByName(pyBScene* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getCameraByName(<string>cameraName)");
        return NULL;
    }
    
    pyBOCamera* obj = PyObject_New(pyBOCamera, &pyBOCamera_type);
    obj->obj.object = (BObject3d*)self->scene->getCameraByName(name);
    if(!obj->obj.object){
        Py_RETURN_NONE;
    }else{
        return (PyObject *)obj;
    }   
}

static PyObject* pyBScene_getCamerasNumber(pyBScene* self)
{
    return Py_BuildValue("I",self->scene->getCamerasNumber());
}

static PyObject* pyBScene_getModelByIndex(pyBScene* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getModelByIndex(<int>objectIndex)");
        return NULL;
    }
    
    if(index < self->scene->getObjectsNumber()){
        pyBOLight* obj = PyObject_New(pyBOLight, &pyBOLight_type);
        obj->obj.object = (BObject3d*)self->scene->getModelByIndex(index);
        return (PyObject *)obj;  
    }else{
        Py_RETURN_NONE;
    }     
}

static PyObject* pyBScene_getModelByName(pyBScene* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getModelByName(<string>objectName)");
        return NULL;
    }
    
    pyBOLight* obj = PyObject_New(pyBOLight, &pyBOLight_type);
    obj->obj.object = (BObject3d*)self->scene->getModelByName(name);
    if(!obj->obj.object){
        Py_RETURN_NONE;
    }else{
        return (PyObject *)obj;
    }   
}

static PyObject* pyBScene_getEntitiesNumber(pyBScene* self)
{
    return Py_BuildValue("I",self->scene->getEntitiesNumber());
}

static PyObject* pyBScene_getGravity(pyBScene* self)
{
        pyUVector3* g = PyObject_New(pyUVector3, &pyUVector3_type);
        g->vector = self->scene->getGravity();
        return (PyObject*)g;
}

static PyObject* pyBScene_getLightByIndex(pyBScene* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getLightByIndex(<int>objectIndex)");
        return NULL;
    }
    
    if(index < self->scene->getObjectsNumber()){
        pyBOLight* obj = PyObject_New(pyBOLight, &pyBOLight_type);
        obj->obj.object = (BObject3d*)self->scene->getLightByIndex(index);
        return (PyObject *)obj;  
    }else{
        Py_RETURN_NONE;
    }     
}

static PyObject* pyBScene_getLightByName(pyBScene* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getLightByName(<string>objectName)");
        return NULL;
    }
    
    pyBOLight* obj = PyObject_New(pyBOLight, &pyBOLight_type);
    obj->obj.object = (BObject3d*)self->scene->getLightByName(name);
    if(!obj->obj.object){
        Py_RETURN_NONE;
    }else{
        return (PyObject *)obj;
    }   
}

static PyObject* pyBScene_getLightsNumber(pyBScene* self)
{
    return Py_BuildValue("I",self->scene->getLightsNumber());
}

static PyObject* pyBScene_getName(pyBScene* self)
{
    return Py_BuildValue("s",self->scene->getName());
}

static PyObject* pyBScene_getObjectByIndex(pyBScene* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getObjectByIndex(<int>objectIndex)");
        return NULL;
    }
    
    if(index < self->scene->getObjectsNumber()){
        pyBObject3d* obj = PyObject_New(pyBObject3d, &pyBObject3d_type);
        obj->object = self->scene->getObjectByIndex(index);
        return (PyObject *)obj;  
    }else{
        Py_RETURN_NONE;
        
    }
      
}

static PyObject* pyBScene_getObjectByName(pyBScene* self, PyObject* args)
{
    char * name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getObjectByName(<string>objectName)");
        return NULL;
    }
    
    pyBObject3d* obj = PyObject_New(pyBObject3d, &pyBObject3d_type);
    obj->object = self->scene->getObjectByName(name);
    if(!obj->object){
        Py_RETURN_NONE;
    }else{
        return (PyObject *)obj;
    }
    
       
}

static PyObject* pyBScene_getObjectsNumber(pyBScene* self)
{
    return Py_BuildValue("I",self->scene->getObjectsNumber());
}

static PyObject* pyBScene_getTextByIndex(pyBScene* self, PyObject* args)
{
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getTextByIndex(<int>objectIndex)");
        return NULL;
    }
    
    if(index < self->scene->getObjectsNumber()){
        pyBOText* obj = PyObject_New(pyBOText, &pyBOText_type);
        obj->obj.object = (BObject3d*)self->scene->getTextByIndex(index);
        return (PyObject *)obj;  
    }else{
        Py_RETURN_NONE;
        
    }
      
}

static PyObject* pyBScene_getTextByName(pyBScene* self, PyObject* args)
{
    char * name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getTextByName(<string>objectName)");
        return NULL;
    }
    
    pyBOText* obj = PyObject_New(pyBOText, &pyBOText_type);
    obj->obj.object = (BObject3d*)self->scene->getTextByName(name);
    if(!obj->obj.object){
        Py_RETURN_NONE;
    }else{
        return (PyObject *)obj;
    }
    
       
}

static PyObject* pyBScene_getTextsNumber(pyBScene* self)
{
    return Py_BuildValue("I",self->scene->getTextsNumber());
}


static PyObject* pyBScene_prepareCollisionObject(pyBScene* self, PyObject* args)
{
    pyBOLight * entity;
    if (!PyArg_ParseTuple(args, "O", &entity)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: prepareCollisionObject(<MOEntiy>entity)");
    }else{
        self->scene->prepareCollisionObject((BOModel3d *)entity->obj.object);
    }
        Py_RETURN_NONE;
}

static PyObject* pyBScene_prepareCollisionShape(pyBScene* self, PyObject* args)
{
    pyBOLight * entity;
    if (!PyArg_ParseTuple(args, "O", &entity)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: prepareCollisionShape(<MOEntiy>entity)");
    }else{
        self->scene->prepareCollisionShape((BOModel3d *)entity->obj.object);
    }
        Py_RETURN_NONE;
}

static PyObject* pyBScene_prepareConstraints(pyBScene* self, PyObject* args)
{
    pyBOLight * entity;
    if (!PyArg_ParseTuple(args, "O", &entity)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: prepareCollisionShape(<MOEntiy>entity)");
    }else{
        self->scene->prepareConstraints((BOModel3d *)entity->obj.object);
    }
        Py_RETURN_NONE;
}

static PyObject* pyBScene_setGravity(pyBScene* self, PyObject* args)
{
    float x; float y; float z;
    if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)){
        pyUVector3 * g;
        if (PyArg_ParseTuple(args, "O", &g)){
            PyErr_Clear();
            self->scene->setGravity(g->vector);
        }else{
            PyErr_SetString(PyExc_AttributeError, "parameters is: setGravity(<float>r, <float>g, <float>b) or setGravity(<BVector3f>color)");
            return NULL;
        }
    }else{
       self->scene->setGravity(BVector3f(x,y,z)); 
    }
        Py_RETURN_NONE;
}

static PyObject* pyBScene_setName(pyBScene* self, PyObject* args)
{
    char* name;
    if (!PyArg_ParseTuple(args, "s", &name)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: setName(<string>Name)");
        return NULL;  
    }else{
        self->scene->setName(name);
    }
        Py_RETURN_NONE;
        
}

static PyMethodDef pyBScene_methods[] = {
    {    "addNewCamera"          , (PyCFunction)pyBScene_addNewCamera           , METH_NOARGS  , ""    },
    {    "addNewCompositedModel" , (PyCFunction)pyBScene_addNewCompositedModel  , METH_NOARGS  , ""    },
    {    "addNewModel"           , (PyCFunction)pyBScene_addNewModel            , METH_VARARGS , ""    },
    {    "addNewLight"           , (PyCFunction)pyBScene_addNewLight            , METH_NOARGS  , ""    },
    {    "addNewSound"           , (PyCFunction)pyBScene_addNewSound            , METH_VARARGS , ""    },
    {    "addNewSprite"          , (PyCFunction)pyBScene_addNewSprite           , METH_VARARGS , ""    },
    {    "addNewText"            , (PyCFunction)pyBScene_addNewText             , METH_VARARGS , ""    },
    {    "deleteObject"          , (PyCFunction)pyBScene_deleteObject           , METH_VARARGS , ""    },
    {    "getCameraByIndex"      , (PyCFunction)pyBScene_getCameraByIndex       , METH_VARARGS , ""    },
    {    "getCameraByName"       , (PyCFunction)pyBScene_getCameraByName        , METH_VARARGS , ""    },
    {    "getCamerasNumber"      , (PyCFunction)pyBScene_getCamerasNumber       , METH_VARARGS , ""    },
    {    "getCurrentCamera"      , (PyCFunction)pyBScene_getCurrentCamera       , METH_NOARGS  , ""    },
    {    "getModelByIndex"       , (PyCFunction)pyBScene_getModelByIndex        , METH_VARARGS , ""    },
    {    "getModelByName"        , (PyCFunction)pyBScene_getModelByName         , METH_VARARGS , ""    },
    {    "getEntitiesNumber"     , (PyCFunction)pyBScene_getEntitiesNumber      , METH_NOARGS  , ""    },
    {    "getGravity"            , (PyCFunction)pyBScene_getGravity             , METH_NOARGS  , ""    },
    {    "getLightByIndex"       , (PyCFunction)pyBScene_getLightByIndex        , METH_VARARGS , ""    },
    {    "getLightsNumber"       , (PyCFunction)pyBScene_getLightsNumber        , METH_NOARGS  , ""    },
    {    "getLightByName"        , (PyCFunction)pyBScene_getLightByName         , METH_VARARGS , ""    },
    {    "getName"               , (PyCFunction)pyBScene_getName                , METH_NOARGS  , ""    },
    {    "getObjectByIndex"      , (PyCFunction)pyBScene_getObjectByIndex       , METH_VARARGS , ""    },
    {    "getObjectByName"       , (PyCFunction)pyBScene_getObjectByName        , METH_VARARGS , ""    },
    {    "getObjectsNumber"      , (PyCFunction)pyBScene_getObjectsNumber       , METH_NOARGS  , ""    },
    {    "getTextByIndex"        , (PyCFunction)pyBScene_getTextByIndex         , METH_VARARGS , ""    },
    {    "getTextByName"         , (PyCFunction)pyBScene_getTextByName          , METH_VARARGS , ""    },
    {    "getTextsNumber"        , (PyCFunction)pyBScene_getTextsNumber         , METH_NOARGS  , ""    },
    {    "prepareCollisionObject", (PyCFunction)pyBScene_prepareCollisionObject , METH_VARARGS , ""    },
    {    "prepareCollisionShape" , (PyCFunction)pyBScene_prepareCollisionShape  , METH_VARARGS , ""    },
    {    "prepareConstraints"    , (PyCFunction)pyBScene_prepareConstraints     , METH_VARARGS , ""    },
    {    "setGravity"            , (PyCFunction)pyBScene_setGravity             , METH_VARARGS , ""    },
    {    "setName"               , (PyCFunction)pyBScene_setName                , METH_NOARGS  , ""    },
    {    NULL                    ,  NULL                                        , 0            , NULL  } /* Sentinel */
};

static PyTypeObject pyBScene_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BScene",
    sizeof(pyBScene),         /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBScene_dealloc,/*tp_dealloc*/
    0,                          /*tp_print*/
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
    "BScene maratis object",   /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    pyBScene_methods,          /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyBScene_new,              /* tp_new */

};
#endif