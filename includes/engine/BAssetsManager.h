/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BAssetsManager.h
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


#ifndef _U_ASSETS_MANAGER_H
#define _U_ASSETS_MANAGER_H


#include <BImplTypes.h>

enum BAssetLocation{
    ON_WORKING_DIR = 0,
    ON_TEMP_DIR,
    ON_ABSOLUTE_DIR,
};

enum BDefaultTextureType{
	DEFAULT_TEX_NO_TEXTURE = 0,
	DEFAULT_TEX_NOT_FOUND
};

// level
class M_ENGINE_EXPORT BAssetsManager
{
private:
	char* tempDirectory;
    char* currentDirectory;

	// FX manager
	BFXManager m_FXManager;

	// data managers
	BDataManager m_fontManager;
	BDataManager m_textureManager;
	BDataManager m_shaderManager;
	BDataManager m_soundManager;
	BDataManager m_meshManager;
	BDataManager m_armatureAnimManager;
	BDataManager m_texturesAnimManager;
	BDataManager m_materialsAnimManager;

	// data queues
	vector <BDataRef *> m_updateQueue;
	vector <BDataRef *> m_clearQueue;


	// scenes
/*	unsigned int		m_currentSceneId;
	unsigned int		m_requestedSceneId;
	vector <BScene *>	m_scenes;   */

public:

	// constructors / destructors
	 BAssetsManager(void);
	 ~BAssetsManager(void);

private:

	friend class Bizarre;
	friend class BWorld;
	
	void incrDataRefScore(BDataRef * ref);
	void decrDataRefScore(BDataRef * ref);	

public:

	// clear
	void clear(void);
//	void clearScenes(void);

	// files
	void getGlobalFilename(const char* filename, char* fullFilename, BAssetLocation location = ON_WORKING_DIR);

	// FX manager
	inline BFXManager * getFXManager(void){ return &m_FXManager; }
	BFXRef * createFX(BShaderRef * vertexShaderRef, BShaderRef * pixelShaderRef);

	// data managers
	inline BDataManager * getFontManager(void){ return &m_fontManager; }
	inline BDataManager * getTextureManager(void){ return &m_textureManager; }
	inline BDataManager * getShaderManager(void){ return &m_shaderManager; }
	inline BDataManager * getSoundManager(void){ return &m_soundManager; }
	inline BDataManager * getMeshManager(void){ return &m_meshManager; }
	inline BDataManager * getArmatureAnimManager(void){ return &m_armatureAnimManager; }
	inline BDataManager * getTexturesAnimManager(void){ return &m_texturesAnimManager; }
	inline BDataManager * getMaterialsAnimManager(void){ return &m_materialsAnimManager; }

	BFontRef * loadFont(const char * filename, BAssetLocation location = ON_WORKING_DIR);
	BMeshRef * loadMesh(const char * filename, BAssetLocation location = ON_WORKING_DIR, const bool preload = true);
	BArmatureAnimRef * loadArmatureAnim(const char * filename, const bool preload = true);
	BTexturesAnimRef * loadTexturesAnim(const char * filename, const bool preload = true);
	BMaterialsAnimRef * loadMaterialsAnim(const char * filename, const bool preload = true);
	BTextureRef * loadTexture(const char * filename, BAssetLocation location = ON_WORKING_DIR, const bool mipmap = true, const bool preload = true);
	BSoundRef * loadSound(const char * filename, BAssetLocation location = ON_WORKING_DIR, const bool preload = true);
	BShaderRef * loadShader(const char * filename, U_SHADER_TYPES type);

	// queue data updates
	void sendToUpdateQueue(BDataRef * ref);
	void sendToClearQueue(BDataRef * ref);
	void updateQueueDatas(void);
	void clearQueueDatas(void);

	// dirs
	inline void setCurrentDir(char* currentDir){ this->currentDirectory = currentDir; }
	inline void    setTempDir(char*    tempDir){       this->tempDirectory = tempDir; }

	inline char* getCurrentDir(void){ return currentDirectory; }


	// generate assets
	BTextureRef* createTextureFromImage( const char * name, BImage * image );
    BMesh* createPlaneFromBox(const BVector3f & min, const BVector3f & max, BTextureRef * textureRef = NULL, U_CULL_MODES cullfaces = U_CULL_NONE);	

	// default assets
	BTextureRef* getDefaultTexture( BDefaultTextureType type = DEFAULT_TEX_NO_TEXTURE );
};

#endif