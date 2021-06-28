
#ifndef _PY_M_LEVEL_TYPE
#define _PY_M_LEVEL_TYPE

#include <Python.h>
#include "structmember.h"

#include <Bizarre.h>


#include "pyBScene.h"
#include "pyBMeshRef.h"
#include "pyBSoundRef.h"
#include "pyBFontRef.h"
#include "pyBImage.h"
//#include "pyBPackageManager.h"

typedef struct {
    PyObject_HEAD
    BPackage package;
} pyBPackage;


static PyObject * pyBPackage_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    pyBPackage *self;
    self = (pyBPackage *)type->tp_alloc(type, 0);
    if (self == NULL){
        Py_RETURN_NONE;
    }
    
    return (PyObject *)self;
}

static void pyBPackage_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }


static PyTypeObject pyBPackage_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BPackage",
    sizeof(pyBPackage),         /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBPackage_dealloc,/*tp_dealloc*/
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
    "",                        /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    pyBPackage_new,             /* tp_new */

};

//////////////

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

static void pyBAssetsManager_dealloc(PyObject *obj){ Py_TYPE(obj)->tp_free(obj); }

static PyObject* pyBAssetsManager_clear(pyBAssetsManager* self)
{
    self->level->clear();
    Py_RETURN_NONE;
}

static PyObject* pyBAssetsManager_createMesh(pyBAssetsManager* self, PyObject *args, PyObject *kwds)
{

    BAssetsManager * assetsManager = Bizarre::getInstance()->getAssetsManager(); 
    static char *kwlist[] = {(char*)"subMeshes",(char*)"textureRefs",(char*)"materials", NULL};    
    
    // python objects
    PyObject* subMeshsList;
    PyObject* textureRefs = NULL;
    PyObject* materials = NULL;

    // meshs objects
    unsigned int subMeshNumber;
    BMesh * newMesh;

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "O!|O!O!", kwlist, &PyList_Type, &subMeshsList, &PyList_Type, &textureRefs, &PyList_Type, &materials ))
        { PyErr_SetString(PyExc_AttributeError, "Param Err"); Py_RETURN_NONE; }

    //if ( !PyList_CheckExact(subMeshsList) )
    //    { PyErr_SetString(PyExc_AttributeError, "subMeshs is not a list"); Py_RETURN_NONE; }    


    subMeshNumber = PyList_GET_SIZE( subMeshsList );

    newMesh = BMesh::getNew();
    newMesh->clear();
    
    // TODO: QUitar las comprobaciones de lista

    // Textures
    if( textureRefs ){
        
        unsigned int textureRefsNumber = PyList_GET_SIZE( textureRefs );
        newMesh->allocTextures(textureRefsNumber);
        for ( int i = 0; i < textureRefsNumber; i++){
            PyObject * textureRefPyO = PyList_GET_ITEM( textureRefs, i );

            if(PyObject_TypeCheck( textureRefPyO, &pyBTextureRef_type ) > 0)
                newMesh->addNewTexture( ((pyBTextureRef*)textureRefPyO)->textureRef );
            else
                newMesh->addNewTexture( assetsManager->getDefaultTexture(DEFAULT_TEX_NO_TEXTURE) );
        }
    }else{
        newMesh->allocTextures(1);
        newMesh->addNewTexture( assetsManager->getDefaultTexture(DEFAULT_TEX_NO_TEXTURE) );    
    }

    for ( int i = 0; i < newMesh->getTexturesNumber(); i++){
        BTexture* texture = newMesh->getTexture(i);

        texture->setUWrapMode(M_WRAP_REPEAT);
        texture->setVWrapMode(M_WRAP_REPEAT);
            
        texture->setTexTranslate( BVector2f(0.0f,0.0f) );
        texture->setTexScale( BVector2f(1.f, 1.f) );
        texture->setTexRotate(0.0f);
    }

    //Materials
    if( materials && PyList_CheckExact(materials) ){
        
        unsigned int materialsNumber = PyList_GET_SIZE( materials );
        newMesh->allocMaterials(materialsNumber);
        for ( int i = 0; i < materialsNumber; i++){
            PyObject * materialPyO = PyList_GET_ITEM( materials, i );
            
            if( PyObject_TypeCheck( materialPyO, &pyBMaterial_type ) > 0){
                newMesh->addNewMaterial( ((pyBMaterial*)materialPyO)->material );
            }else{
                newMesh->addNewMaterial();
            }
        }
    }else{
        newMesh->allocMaterials(1);
        BMaterial * material = newMesh->addNewMaterial();
        material->setType(1);

        material->setOpacity(1.f);
        material->setShininess(.0f);
        material->setCustomValue(.0f);
        material->setDiffuse(BVector3f(1.0f, 1.0f, 1.0f));
        material->setSpecular(BVector3f());
        material->setEmit(BVector3f(1.0f, 1.0f, 1.0f));
        material->setCustomColor(BVector3f());
            
        material->setBlendMode(M_BLENDING_NONE);

        material->allocTexturesPass(1);
        material->addTexturePass( newMesh->getTexture(0u), M_TEX_COMBINE_REPLACE, 0u ); // <---------   
    }

    newMesh->getBoundingBox()->min = BVector3f( -1.0, -1.0, .0 );
    newMesh->getBoundingBox()->max = BVector3f(  1.0,  1.0, .0 );

    BSubMesh * subMeshs = newMesh->allocSubMeshs( subMeshNumber );

    PyObject* verticesKey =  PyString_FromString("vertices");
    PyObject* normalsKey  =  PyString_FromString("normals");
    PyObject* tangentsKey =  PyString_FromString("tangents");
    PyObject* texCoordsKey=  PyString_FromString("texCoords");
    PyObject* indicesKey  =  PyString_FromString("indices");
    PyObject* displaysKey  =  PyString_FromString("displays");

    for ( int i = 0; i < subMeshNumber; i++){
        PyObject * subMeshDict = PyList_GET_ITEM( subMeshsList, i );
        if ( !PyDict_CheckExact(subMeshDict) )
            { PyErr_SetString(PyExc_AttributeError, "subMesh is not a dict"); Py_RETURN_NONE; }    
        
        PyObject* verticesList = PyDict_GetItem(subMeshDict, verticesKey );
        PyObject* normalsList  = PyDict_GetItem(subMeshDict, normalsKey  );
        PyObject* tangentsList = PyDict_GetItem(subMeshDict, tangentsKey );
        PyObject* texCoordsList= PyDict_GetItem(subMeshDict, texCoordsKey);
        PyObject* indicesList  = PyDict_GetItem(subMeshDict, indicesKey  );
        PyObject* displaysList = PyDict_GetItem(subMeshDict, displaysKey );

        unsigned int verticesNumber;
        unsigned int indicesNumber;
        if( verticesList ){
            verticesNumber = PyList_GET_SIZE( verticesList );
            BVector3f * vertices = subMeshs[i].allocVertices( verticesNumber );
            
            for ( int j = 0; j < verticesNumber; j++){
                PyObject * vertexPyO = PyList_GET_ITEM( verticesList, j );
                if( PyObject_TypeCheck( vertexPyO, &pyUVector3_type) > 0 )
                    vertices[j] = ( (pyUVector3*)vertexPyO )->vector;
                else
                    vertices[j] = BVector3f();
            }
        }

        if( normalsList ){
            unsigned int normalsNumber = PyList_GET_SIZE( normalsList );
            BVector3f * normals = subMeshs[i].allocNormals( normalsNumber );
            
            for ( int j = 0; j < normalsNumber; j++){
                PyObject * normalPyO = PyList_GET_ITEM( normalsList, j );
                if( PyObject_TypeCheck( normalPyO, &pyUVector3_type) > 0 )
                    normals[j] = ( (pyUVector3*)normalPyO )->vector;
                else
                    normals[j] = BVector3f();
            }
        }

        if( tangentsList ){
            unsigned int tangentsNumber = PyList_GET_SIZE( tangentsList );
            BVector3f * tangents = subMeshs[i].allocTangents( tangentsNumber );
            
            for ( int j = 0; j < tangentsNumber; j++){
                PyObject * tangetPyO = PyList_GET_ITEM( tangentsList, j );
                if( PyObject_TypeCheck( tangetPyO, &pyUVector3_type) > 0 )
                    tangents[j] = ( (pyUVector3*)tangetPyO )->vector;
                else
                    tangents[j] = BVector3f();
            }
        }

        if( texCoordsList ){
            unsigned int texCoordsNumber = PyList_GET_SIZE( texCoordsList );
            BVector2f * texCoords = subMeshs[i].allocTexCoords( texCoordsNumber );
            
            for ( int j = 0; j < texCoordsNumber; j++){
                PyObject * texCoordPyO = PyList_GET_ITEM( texCoordsList, j );
                if( PyObject_TypeCheck( texCoordPyO, &pyUVector2_type) > 0 )
                    texCoords[j] = ( (pyUVector2*)texCoordPyO )->vector;
                else
                    texCoords[j] = BVector3f();
            }
        }

        if( indicesList ){
            indicesNumber = PyList_GET_SIZE( indicesList );
            
            U_TYPES indicesType;
            if( verticesNumber > 65000u )
                indicesType = U_UINT;
            else
                indicesType = U_USHORT;

            void * indices = subMeshs[i].allocIndices( indicesNumber, indicesType );


            for ( int j = 0; j < indicesNumber; j++){
                PyObject * indicePyO = PyList_GET_ITEM( indicesList, j );
                
                long indice;
                if( PyNumber_Check( indicePyO ) > 0 )
                    indice = PyLong_AsLong( indicePyO );
                else
                    indice = 0u;
                
                switch(indicesType){
                    case U_UINT:
                        ( (unsigned int *)indices )[j] = (unsigned int)indice;
                    
                    case U_USHORT:
                    default:
                        ( (unsigned short *)indices )[j] = (unsigned short)indice;
                };
            }
        }

    
        subMeshs[i].getBoundingBox()->initFromPoints( subMeshs[i].getVertices(), subMeshs[i].getVerticesSize() );

        if( displaysList ){
            unsigned int displaysNumber = PyList_GET_SIZE( displaysList );
            subMeshs[i].allocDisplays( displaysNumber );

            for ( int j = 0; j < displaysNumber; j++){
                PyObject * displayPyO = PyList_GET_ITEM( displaysList, j );
                if( PyObject_TypeCheck(displayPyO, &pyBDisplay_type) > 0 )
                    subMeshs[i].addNewDisplay(  ( (pyBDisplay*)displayPyO )->display  );
            }
        }else{
            subMeshs[i].allocDisplays(1);
            unsigned int begin = 0u, size = indicesNumber;
            BDisplay * display = subMeshs[i].addNewDisplay(U_PRIMITIVE_TRIANGLES, begin, size);
            display->setMaterial( newMesh->getMaterial(0u) );
            display->setCullMode(U_CULL_BACK);
        }

        if(! subMeshs[i].getTangents())
			generateTangents( &subMeshs[i] );
    }

    //std::cout << "---->" << std::endl;
    BVector3f * boxPoints = new BVector3f[ newMesh->getSubMeshsNumber() * 2 ];
    for( int i = 0; i < newMesh->getSubMeshsNumber(); i++ ){
        boxPoints[ i ] = subMeshs[i*2].getBoundingBox()->min;
        boxPoints[i+1] = subMeshs[i*2].getBoundingBox()->max;
    }
    newMesh->getBoundingBox()->initFromPoints( boxPoints, newMesh->getSubMeshsNumber() * 2);

    pyBMesh* msr = PyObject_New(pyBMesh, &pyBMesh_type);
    msr->mesh = newMesh;
    return (PyObject*)msr;
}


static PyObject* pyBAssetsManager_createTexture(pyBAssetsManager* self, PyObject *args, PyObject *kwds)
{
    char* name;
    pyBImage * image;

    if (!PyArg_ParseTuple(args, "sO!", &name, &pyBImage_type, &image)){
        //PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByIndex(<int>absolutePath)");
        return NULL;
    }
    
    pyBTextureRef* tx = PyObject_New(pyBTextureRef, &pyBTextureRef_type);
    tx->textureRef = self->level->createTextureFromImage( name, &image->image );
    return (PyObject *)tx;
}


static PyObject* pyBAssetsManager_loadFont(pyBAssetsManager* self, PyObject* args)
{
    char* filename;
    int location = ON_WORKING_DIR;

    if (!PyArg_ParseTuple(args, "s|i", &filename, &location)){
        return NULL;
    }

    pyBFontRef* fontRef = PyObject_New(pyBFontRef, &pyBFontRef_type);
    fontRef->fontRef = self->level->loadFont(filename, (BAssetLocation)location);
    //Py_INCREF(fontRef);
    return (PyObject *)fontRef;    
}


static PyObject* pyBAssetsManager_loadMesh(pyBAssetsManager* self, PyObject* args)
{
    char* filename; 
    int location = ON_WORKING_DIR;
    bool preload = true;
    

    if (!PyArg_ParseTuple(args, "s|ib", &filename, &location, &preload)){
        PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByIndex(<int>absolutePath)");
        return NULL;
    }
    
    pyBMeshRef* ms = PyObject_New(pyBMeshRef, &pyBMeshRef_type);
    
    //char file[500];
    //getGlobalFilename(file, globalInfo::getInstance()->getWorkingDirectory(), filename);
    
    //ms->meshRef = self->level->loadMesh( file, preload);
    ms->meshRef = self->level->loadMesh(filename, (BAssetLocation)location, preload);
    
   

    return (PyObject *)ms;
    
}

static PyObject* pyBAssetsManager_loadPackage(pyBAssetsManager* self, PyObject* args){
    char* filename;
    int location = ON_WORKING_DIR;

    if (!PyArg_ParseTuple(args, "s|i", &filename, &location)){
         return NULL;
    }
    
    char fullFilename[256];
    self->level->getGlobalFilename(filename, fullFilename, (BAssetLocation)location);

    BPackage package = Bizarre::getInstance()->getPackageManager()->loadPackage(fullFilename);
    if( package == 0 ){
        Py_RETURN_NONE;
    }else{
        pyBPackage* pyPackage = PyObject_New(pyBPackage, &pyBPackage_type);
        pyPackage->package = package;
        return (PyObject *)pyPackage;
    }
}

static PyObject* pyBAssetsManager_loadTexture(pyBAssetsManager* self, PyObject* args)
{
    char* filename; bool mipmap = true; bool preload = true;
    int location = ON_WORKING_DIR;

    if (!PyArg_ParseTuple(args, "s|ibb", &filename, &location, &mipmap, &preload)){
        //PyErr_SetString(PyExc_AttributeError, "parameters is: getSceneByIndex(<int>absolutePath)");
        return NULL;
    }
    
    pyBTextureRef* tx = PyObject_New(pyBTextureRef, &pyBTextureRef_type);
    tx->textureRef = self->level->loadTexture(filename, (BAssetLocation)location, mipmap, preload);
    return (PyObject *)tx;
}

static PyObject* pyBAssetsManager_loadSound(pyBAssetsManager* self, PyObject* args)
{
    char* filename; 
    int location = ON_WORKING_DIR;
    bool preload = true;

    if (!PyArg_ParseTuple(args, "s|ib", &filename, &location, &preload)){
        return NULL;
    }
    
    pyBSoundRef* soundRef = PyObject_New(pyBSoundRef, &pyBSoundRef_type);
    soundRef->soundRef = self->level->loadSound(filename, (BAssetLocation)location, preload);
    return (PyObject *)soundRef;    
}



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
    {    "createMesh"        , (PyCFunction)pyBAssetsManager_createMesh         , METH_KEYWORDS , ""},
    {    "createTexture"     , (PyCFunction)pyBAssetsManager_createTexture      , METH_VARARGS , ""},
    {    "loadFont"          , (PyCFunction)pyBAssetsManager_loadFont           , METH_VARARGS  , ""},
    {    "loadMesh"          , (PyCFunction)pyBAssetsManager_loadMesh           , METH_VARARGS  , ""},
    {    "loadPackage"       , (PyCFunction)pyBAssetsManager_loadPackage        , METH_VARARGS  , ""},
    {    "loadTexture"       , (PyCFunction)pyBAssetsManager_loadTexture        , METH_VARARGS  , ""},
    {    "loadSound"         , (PyCFunction)pyBAssetsManager_loadSound          , METH_VARARGS  , ""},
//    {    "setCurrentSceneId" , (PyCFunction)pyBAssetsManager_setCurrentSceneId  , METH_VARARGS , ""},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static PyTypeObject pyBAssetsManager_type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "BAssetsManager",
    sizeof(pyBAssetsManager),         /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)pyBAssetsManager_dealloc,/*tp_dealloc*/
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