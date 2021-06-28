/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BEngine.h
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#ifndef _M_ENGINE_H
#define _M_ENGINE_H

#ifdef WIN32
/*
	// M_ENGINE_EXPORT
	#if defined(Bizarre_DLL)
		#define M_ENGINE_EXPORT __declspec( dllexport )
	#elif defined(Bizarre_STATIC)
		#define M_ENGINE_EXPORT
	#else
		#define M_ENGINE_EXPORT __declspec( dllimport )
	#endif
*/

	#define M_ENGINE_EXPORT
#else

	// M_ENGINE_EXPORT
	#define M_ENGINE_EXPORT

#endif


// object3d type
#define U_OBJECT3D			0
#define U_OBJECT3D_BONE		1
#define U_OBJECT3D_CAMERA	2
#define U_OBJECT3D_LIGHT	3
#define U_OBJECT3D_MODEL	4
#define U_OBJECT3D_SOUND	5
#define U_OBJECT3D_TEXT		6

// dataRef type
#define U_REF_MESH				0
#define U_REF_TEXTURE			1
#define U_REF_SOUND				2
#define U_REF_ARMATURE_ANIM		3
#define U_REF_MATERIALS_ANIM	4
#define U_REF_TEXTURES_ANIM		5
#define U_REF_SHADER			6
#define U_REF_FONT				7

// classes
class BScene;
class BAssetsManager;
class BGame;

class BObject3d;
class BOBone;
class BOLight;
class BOCamera;
class BOModel3d;
class BOCompositedModel3d;
class BOSound;
class BOText;

class BFontRef;
class BShaderRef;
class BSoundRef;
class BMeshRef;
class BTextureRef;
class BArmatureAnimRef;
class BTexturesAnimRef;
class BMaterialsAnimRef;


#include <BCore.h>

#include "ULog.h"

#include "BPackageManager.h"

#include "BKey.h"
#include "BObject3dAnim.h"
#include "BTextureAnim.h"
#include "BMaterialAnim.h"

#include "BArmatureAnim.h"
#include "BTexturesAnim.h"
#include "BMaterialsAnim.h"

#include "BFXManager.h"

#include "BVariable.h"
#include "BBehavior.h"
#include "BBehaviorCreator.h"
#include "BBehaviorManager.h"

#include "BRenderer.h"
#include "BRendererCreator.h"
#include "BRendererManager.h"

#include "BBox3d.h"
#include "BFrustum.h"

#include "BFont.h"
#include "BTexture.h"
#include "BMaterial.h"
#include "BArmature.h"
#include "BMesh.h"
#include "BMeshTools.h"

#include "BFontRef.h"
#include "BShaderRef.h"
#include "BSoundRef.h"
#include "BMeshRef.h"
#include "BTextureRef.h"
#include "BArmatureAnimRef.h"
#include "BTexturesAnimRef.h"
#include "BMaterialsAnimRef.h"

#include "BObject3d.h"
#include "BOBone.h"
#include "BOCamera.h"
#include "BOLight.h"
#include "BOSound.h"
#include "BOModel3d.h"
#include "BOCompositedModel3d.h"
#include "BOText.h"
#include "BOSprite.h"

#include "BScene.h"
#include "BScene2d.h"
#include "BAssetsManager.h"
#include "BGame.h"

#include "BWorld.h"

int BizarreMain(int argc, char* argv[]);

class M_ENGINE_EXPORT BStartConfig{
public:	
    BStartConfig(void);

public:
	BGame* game;
        
    unsigned int window_width;
    unsigned int window_height;
    bool window_fullscreen;
    const char* window_title;

	char* renderer_name;

	friend class Bizarre;
/*public:
	inline void setGame( BGame* game ){ this->game = game; }
	inline void setScreen( unsigned int width, unsigned int height, bool fullscreen, char* title = NULL ){
		window_width = width; window_height = height; window_fullscreen = fullscreen; window_title = title;
	}
*/

};

class M_ENGINE_EXPORT Bizarre
{
public:

	Bizarre(void);
	~Bizarre(void);

	// instance
	static Bizarre * getInstance(void);

	void start( BStartConfig startConfig = BStartConfig() );
private:
	// dirs
	char * m_workingDir;

	// active
	bool m_isActive;
	
	// contexts
	BSoundContext * m_soundContext;
	BRenderingContext * m_renderingContext;
	BPhysicsContext * m_physicsContext;
	BScriptContext * m_scriptContext;
	BInputContext * m_inputContext;
	BSystemContext * m_systemContext;
	BThreadingContext * m_threadingContext;

	// data loaders
	BDataLoader m_fontLoader;
	BDataLoader m_imageLoader;
	BDataLoader m_soundLoader;
	BDataLoader m_meshLoader;
	BDataLoader m_armatureAnimLoader;
	BDataLoader m_texturesAnimLoader;
	BDataLoader m_materialsAnimLoader;
	BDataLoader m_levelLoader;

	// behavior manager
	BBehaviorManager m_behaviorManager;
	
	// renderer manager
	BRendererManager m_rendererManager; 

	// package manager
	BPackageManager * m_packageManager;
	
	// level
	BAssetsManager * m_assetsManager;

	// game
	BWorld * m_world;
	BGame * m_game;
	
	// renderer
	BRenderer * m_renderer;

	// stores the name of the level to load when loading is save
	char * m_requestedLevelToLoad;
	
private:
	
	void loadLevelIfRequested(); // Checks if a level was requested to be loaded and loads it
	
public:

	// active
	inline void setActive(bool active){ m_isActive = active; }
	inline bool isActive(void){ return m_isActive; }

	// contexts
	void setSoundContext(BSoundContext * soundContext);
	void setRenderingContext(BRenderingContext * renderingContext);
	void setPhysicsContext(BPhysicsContext * physicsContext);
	void setScriptContext(BScriptContext * scriptContext);
	void setInputContext(BInputContext * inputContext);
	void setSystemContext(BSystemContext * systemContext);
	void setThreadingContext(BThreadingContext * threadingContext);

	// get contexts
	inline BSoundContext * getSoundContext(void){ return m_soundContext; }
	inline BRenderingContext * getRenderingContext(void){ return m_renderingContext; }
	inline BPhysicsContext * getPhysicsContext(void){ return m_physicsContext; }
	inline BScriptContext * getScriptContext(void){ return m_scriptContext; }
	inline BInputContext * getInputContext(void){ return m_inputContext; }
	inline BSystemContext * getSystemContext(void){ return m_systemContext; }

	// dir
	inline void setWorkingDir( char * workingDir ){ m_workingDir = workingDir; }
	inline char * getWorkingDir(void){ return m_workingDir; }

	// data loaders
	BDataLoader * getFontLoader(void){ return &m_fontLoader; }
	BDataLoader * getImageLoader(void){ return &m_imageLoader; }
	BDataLoader * getSoundLoader(void){ return &m_soundLoader; }
	BDataLoader * getMeshLoader(void){ return &m_meshLoader; }
	BDataLoader * getArmatureAnimLoader(void){ return &m_armatureAnimLoader; }
	BDataLoader * getTexturesAnimLoader(void){ return &m_texturesAnimLoader; }
	BDataLoader * getMaterialsAnimLoader(void){ return &m_materialsAnimLoader; }
	//BDataLoader * getAssetsManagerLoader(void){ return &m_levelLoader; } // eliminar

	// behavior manager
	inline BBehaviorManager * getBehaviorManager(void){ return &m_behaviorManager; }

	// renderer manager
	inline BRendererManager * getRendererManager(void){ return &m_rendererManager; }

	// package manager
	void setPackageManager(BPackageManager * packageManager);
	inline BPackageManager * getPackageManager(void){ return m_packageManager; }

	// update requests
	void updateRequests(void);

	// level
	void setLevel(BAssetsManager * level);
	bool loadLevel(const char * filename); // loads level immediately
	void requestLoadLevel(const char * filename); // send a request to load a level
	bool doesLevelExist(const char * filename);
	inline BAssetsManager * getAssetsManager(void){ return m_assetsManager; }

	// game
	void setGame(BGame * game, bool restartScenes = true, bool restartAssets = true );
	inline BGame * getGame(void){ return m_game; }

	//world
	inline BWorld * getWorld(void){ return m_world; }
	
	// renderer
	void setRenderer(BRenderer * renderer);
	inline BRenderer * getRenderer(void){ return m_renderer; }
};


#endif
