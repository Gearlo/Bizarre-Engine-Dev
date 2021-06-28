#include <Bizarre.h>


#include <scripting/pyBEngine.h>

void BScriptContext::initializeContext(){
    

    BizarreModule = Py_InitModule3("Bizarre", NULL, "This is a maratis api");

    if(PyType_Ready(&pyBArmature_type) < 0) return;
    if(PyType_Ready(&pyBFontRef_type) < 0) return;
    if(PyType_Ready(&pyUwinputContext_type) < 0) return;
    if(PyType_Ready(&pyBMaterial_type) < 0) return;
    if(PyType_Ready(&pyBDisplay_type) < 0) return;
    if(PyType_Ready(&pyBAnimTransitionProperties_type) < 0) return;
    if(PyType_Ready(&pyBAnimProperties_type) < 0) return;
    if(PyType_Ready(&pyBMesh_type) < 0) return;
    if(PyType_Ready(&pyBMeshRef_type) < 0) return;
    if(PyType_Ready(&pyBSkinPoint_type) < 0) return;
    if(PyType_Ready(&pyBSkinData_type) < 0) return;
    if(PyType_Ready(&pyBSubMesh_type) < 0) return;
    if(PyType_Ready(&pyBOCompositedModel3dSubMesh_type) < 0) return;

    pyBOBone_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOBone_type) < 0) return;
    
    pyBOCamera_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOCamera_type) < 0) return;

    pyBOCompositedModel3d_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOCompositedModel3d_type) < 0) return;
    
    pyBOLight_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOLight_type) < 0) return;
    
    pyBOModel3d_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOModel3d_type) < 0) return;

    pyBOSound_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOSound_type) < 0) return;

    pyBOText_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOText_type) < 0) return;

    pyBOSprite_type.tp_base = &pyBObject3d_type;
    if(PyType_Ready(&pyBOSprite_type) < 0) return;

    if(PyType_Ready(&pyBPackage_type) < 0) return;
    //if(PyType_Ready(&pyBPackageManager_type) < 0) return;
    if(PyType_Ready(&pyBPhysicsContext_type) < 0) return;
    if(PyType_Ready(&pyBPhysicsProperties_type) < 0) return;
    if(PyType_Ready(&pyBRenderInfo_type) < 0) return;
    if(PyType_Ready(&pyBScene_type) < 0) return;
    if(PyType_Ready(&pyBScene_type) < 0) return;
    if(PyType_Ready(&pyBSoundRef_type) < 0) return;
    if(PyType_Ready(&pyBSystemContext_type) < 0) return;
    if(PyType_Ready(&pyBTexture_type) < 0) return;
    if(PyType_Ready(&pyBTextureRef_type) < 0) return;
    if(PyType_Ready(&pyUVector4_type) < 0) return;
    if(PyType_Ready(&pyUVector3_type) < 0) return;
    if(PyType_Ready(&pyUVector2_type) < 0) return;
    if(PyType_Ready(&pyBGame_type) < 0) return;
    if(PyType_Ready(&pyBImage_type) < 0) return;
    if(PyType_Ready(&pyBAssetsManager_type) < 0) return;
    if(PyType_Ready(&pyBWorld_type) < 0) return;
    if(PyType_Ready(&pyBEngine_type) < 0) return;
    

    Py_INCREF(&pyBArmature_type);
    Py_INCREF(&pyBFontRef_type);
    Py_INCREF(&pyUwinputContext_type);
    Py_INCREF(&pyBMaterial_type);
    Py_INCREF(&pyBDisplay_type);
    Py_INCREF(&pyBAnimTransitionProperties_type);
    Py_INCREF(&pyBAnimProperties_type);
    Py_INCREF(&pyBMesh_type);
    Py_INCREF(&pyBMeshRef_type);
    Py_INCREF(&pyBSkinPoint_type);
    Py_INCREF(&pyBSkinData_type);
    Py_INCREF(&pyBSubMesh_type);
    Py_INCREF(&pyBTextureRef_type);
    Py_INCREF(&pyBOBone_type);
    Py_INCREF(&pyBOCamera_type);
    Py_INCREF(&pyBOCompositedModel3d_type);
    Py_INCREF(&pyBOCompositedModel3dSubMesh_type);
    Py_INCREF(&pyBOLight_type);
    Py_INCREF(&pyBOSound_type);
    Py_INCREF(&pyBOText_type);
    Py_INCREF(&pyBObject3d_type);
    Py_INCREF(&pyBScene_type);
    Py_INCREF(&pyBPhysicsContext_type);
    Py_INCREF(&pyBPhysicsProperties_type);
    Py_INCREF(&pyBSoundRef_type);
    Py_INCREF(&pyBSystemContext_type);
    Py_INCREF(&pyBRenderInfo_type);
    Py_INCREF(&pyBTexture_type);
    Py_INCREF(&pyBTextureRef_type);
    Py_INCREF(&pyUVector4_type);
    Py_INCREF(&pyUVector3_type);
    Py_INCREF(&pyUVector2_type);
    Py_INCREF(&pyBGame_type);
    Py_INCREF(&pyBImage_type);
    Py_INCREF(&pyBWorld_type);
    Py_INCREF(&pyBAssetsManager_type);
    Py_INCREF(&pyBEngine_type);
    Py_INCREF(&pyBOSprite_type);
    
    PyModule_AddObject(BizarreModule,"BVector4f",(PyObject*)&pyUVector4_type);
    PyModule_AddObject(BizarreModule,"BVector3f",(PyObject*)&pyUVector3_type);
    PyModule_AddObject(BizarreModule,"BVector2f",(PyObject*)&pyUVector2_type);
    PyModule_AddObject(BizarreModule,"BGame",(PyObject*)&pyBGame_type);
    PyModule_AddObject(BizarreModule,"BImage",(PyObject*)&pyBImage_type);
    PyModule_AddObject(BizarreModule,"BInputContext",(PyObject*)&pyUwinputContext_type);
    //PyModule_AddObject(BizarreModule,"BMesh",(PyObject*)&pyBMesh_type);
    PyModule_AddObject(BizarreModule,"BMeshRef",(PyObject*)&pyBMeshRef_type);
    PyModule_AddObject(BizarreModule,"BPhysicsContext",(PyObject*)&pyBPhysicsContext_type);
    PyModule_AddObject(BizarreModule,"BRenderInfo",(PyObject*)&pyBRenderInfo_type);
    PyModule_AddObject(BizarreModule,"BSubMesh",(PyObject*)&pyBSubMesh_type);
    PyModule_AddObject(BizarreModule,"BSystemContext",(PyObject*)&pyBSystemContext_type);
    PyModule_AddObject(BizarreModule,"BWorld",(PyObject*)&pyBWorld_type);
    PyModule_AddObject(BizarreModule,"Bizarre",(PyObject*)&pyBEngine_type);
    
    PyModule_AddIntConstant(BizarreModule, "ON_WORKING_DIR", ON_WORKING_DIR);
    PyModule_AddIntConstant(BizarreModule, "ON_TEMP_DIR", ON_TEMP_DIR);
    PyModule_AddIntConstant(BizarreModule, "ON_ABSOLUTE_DIR", ON_ABSOLUTE_DIR);

    PyModule_AddIntConstant(BizarreModule, "SCENE_LAYERS_NONE", SCENE_LAYERS_NONE);
    PyModule_AddIntConstant(BizarreModule, "SCENE_LAYERS_SKY1_WORLD2_GUI3", SCENE_LAYERS_SKY1_WORLD2_GUI3);
    PyModule_AddIntConstant(BizarreModule, "SCENE_LAYERS_WORLD1_GUI2", SCENE_LAYERS_WORLD1_GUI2);

    PyModule_AddIntConstant(BizarreModule, "SCENE_LAYERS_WORLD1_GUI2", SCENE_LAYERS_WORLD1_GUI2);

    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_LEFT", GUI_ALIGN_LEFT);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_RIGHT",GUI_ALIGN_RIGHT);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_CENTER",GUI_ALIGN_CENTER);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_LEFT_OUTER",GUI_ALIGN_LEFT_OUTER);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_RIGHT_OUTER",GUI_ALIGN_RIGHT_OUTER);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_DOWN",GUI_ALIGN_DOWN);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_UP",GUI_ALIGN_UP);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_DOWN_OUTER",GUI_ALIGN_DOWN_OUTER);
    PyModule_AddIntConstant(BizarreModule, "GUI_ALIGN_UP_OUTER", GUI_ALIGN_UP_OUTER);

    PyModule_AddIntConstant(BizarreModule, "SPRITE_ROTATE_NONE", SPRITE_ROTATE_NONE);
    PyModule_AddIntConstant(BizarreModule, "SPRITE_ROTATE_FULL", SPRITE_ROTATE_FULL);
    PyModule_AddIntConstant(BizarreModule, "SPRITE_ROTATE_HALF_Z", SPRITE_ROTATE_HALF_Z);

    PyModule_AddIntConstant(BizarreModule, "U_CULL_NONE", U_CULL_NONE);
    PyModule_AddIntConstant(BizarreModule, "U_CULL_FRONT", U_CULL_FRONT);
    PyModule_AddIntConstant(BizarreModule, "U_CULL_BACK", U_CULL_BACK);
    PyModule_AddIntConstant(BizarreModule, "U_CULL_FRONT_BACK", U_CULL_FRONT_BACK);

    PyModule_AddIntConstant(BizarreModule, "U_PRIMITIVE_POINTS", U_PRIMITIVE_POINTS );
	PyModule_AddIntConstant(BizarreModule, "U_PRIMITIVE_LINES", U_PRIMITIVE_LINES );
	PyModule_AddIntConstant(BizarreModule, "U_PRIMITIVE_LINE_LOOP", U_PRIMITIVE_LINE_LOOP ); 
	PyModule_AddIntConstant(BizarreModule, "U_PRIMITIVE_LINE_STRIP", U_PRIMITIVE_LINE_STRIP );
	PyModule_AddIntConstant(BizarreModule, "U_PRIMITIVE_TRIANGLES", U_PRIMITIVE_TRIANGLES );
	PyModule_AddIntConstant(BizarreModule, "U_PRIMITIVE_TRIANGLE_STRIP", U_PRIMITIVE_TRIANGLE_STRIP );
	PyModule_AddIntConstant(BizarreModule, "U_PRIMITIVE_TRIANGLE_FAN", U_PRIMITIVE_TRIANGLE_FAN );

    PyModule_AddIntConstant(BizarreModule, "U_UINT", U_UINT);
    PyModule_AddIntConstant(BizarreModule, "U_USHORT", U_USHORT);

    PyModule_AddIntConstant(BizarreModule, "NONE_ANIMATION", NONE_ANIMATION);
    
    //UWindow* window = UWindow::getInstance();

    Bizarre * engine = Bizarre::getInstance();
    const char * workingDir = engine->getWorkingDir();
    //const char * tempDir = window->getTempDirectory();

    if( workingDir ){
        char scriptsDir1[512];
        char scriptsDir2[512];
        char scriptsDir3[512];
        char scriptsDir4[512];
        char script[600];

        strcpy(scriptsDir1, (char*)workingDir );
        strcpy(scriptsDir2, (char*)workingDir );
        strcpy(scriptsDir3, (char*)workingDir );

        
        strcat(scriptsDir1, (char*)"\\scripts" );
        strcat(scriptsDir3, (char*)"/scripts" );
        

        //strcpy(scriptsDir3, (char*)tempDir );
        //strcpy(scriptsDir4, (char*)tempDir );
        //strcat(scriptsDir3, (char*)"/Bizarre" );
        //strcat(scriptsDir4, (char*)"/Bizarre/scripts" );
        
        strcpy(script,"from sys import path\n");
        strcat(script, "path.extend(['");
        strcat(script, scriptsDir1);
        strcat(script, "','");
        strcat(script, scriptsDir2);
        strcat(script, "','");
        strcat(script, scriptsDir3);
        //strcat(script, "','");
        //strcat(script, scriptsDir4);
        strcat(script, "'])");

        run_string(script);
    }
    //python->run_string(scriptsDirAdd)
}