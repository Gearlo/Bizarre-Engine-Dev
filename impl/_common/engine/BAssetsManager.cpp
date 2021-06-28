/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BAssetsManager.cpp
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


#include <stdio.h>
#include <Bizarre.h>


// level
BAssetsManager::BAssetsManager(void):
tempDirectory(NULL),
currentDirectory(NULL)
{}

BAssetsManager::~BAssetsManager(void)
{
	clear();
}


void BAssetsManager::getGlobalFilename(const char* filename, char* fullFilename, BAssetLocation location){
    //char fullFilename[256];
    switch(location){
        case ON_WORKING_DIR:
            strcpy(fullFilename, currentDirectory);
            strcat(fullFilename, "/" );
            strcat(fullFilename, filename );
            break;
        
        case ON_TEMP_DIR:
            strcpy(fullFilename, tempDirectory);
            strcat(fullFilename, "/" );
            strcat(fullFilename, filename );
            break;
            
        default:
            strcpy(fullFilename, filename);
            break;
    }
}

void BAssetsManager::incrDataRefScore(BDataRef * ref)
{
	if(! ref)
		return;

	if(ref->getScore() == 0)
		sendToUpdateQueue(ref);

	ref->incrScore();
}

void BAssetsManager::decrDataRefScore(BDataRef * ref)
{
	if(! ref)
		return;

	if(ref->getScore() == 1)
		sendToClearQueue(ref);

	ref->decrScore();
}

BFontRef * BAssetsManager::loadFont(const char * filename, BAssetLocation location)
{
	char fullFilename[256];
    this->getGlobalFilename(filename, fullFilename, location);

	unsigned int i;
	unsigned int size = m_fontManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BFontRef * ref = (BFontRef *)m_fontManager.getRef(i);
		if(strcmp(ref->getFilename(), fullFilename) == 0)
		{
			if(ref->getScore() == 0)
				ref->update();
			ref->incrScore();
			return ref;
		}
	}

	// add data
	BFontRef * ref = BFontRef::getNew(NULL, fullFilename);
	m_fontManager.addRef(ref);
	if(ref->getScore() == 0)
		ref->update();
	ref->incrScore();
	return ref;
}

BMeshRef * BAssetsManager::loadMesh(const char * filename, BAssetLocation location, const bool preload)
{

	char fullFilename[256];
    this->getGlobalFilename(filename, fullFilename, location);


	unsigned int i;
	unsigned int size = m_meshManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BMeshRef * ref = (BMeshRef *)m_meshManager.getRef(i);
		if(strcmp(ref->getFilename(), fullFilename) == 0)
		{
			if(preload)
			{
				if(ref->getScore() == 0)
					ref->update();
				ref->incrScore();
			}

			return ref;
		}
	}

	// add data
	BMeshRef * ref = BMeshRef::getNew(NULL, fullFilename);
	m_meshManager.addRef(ref);

	if(preload)
	{
		if(ref->getScore() == 0)
			ref->update();
		ref->incrScore();
	}

	return ref;
}

BArmatureAnimRef * BAssetsManager::loadArmatureAnim(const char * filename, const bool preload)
{
	unsigned int i;
	unsigned int size = m_armatureAnimManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BArmatureAnimRef * ref = (BArmatureAnimRef *)m_armatureAnimManager.getRef(i);
		if(strcmp(ref->getFilename(), filename) == 0)
		{
			if(preload)
			{
				if(ref->getScore() == 0)
					ref->update();
				ref->incrScore();
			}

			return ref;
		}
	}

	// add data
	BArmatureAnimRef * ref = BArmatureAnimRef::getNew(NULL, filename);
	m_armatureAnimManager.addRef(ref);

	if(preload)
	{
		if(ref->getScore() == 0)
			ref->update();
		ref->incrScore();
	}

	return ref;
}

BTexturesAnimRef * BAssetsManager::loadTexturesAnim(const char * filename, const bool preload)
{
	unsigned int i;
	unsigned int size = m_texturesAnimManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BTexturesAnimRef * ref = (BTexturesAnimRef *)m_texturesAnimManager.getRef(i);
		if(strcmp(ref->getFilename(), filename) == 0)
		{
			if(preload)
			{
				if(ref->getScore() == 0)
					ref->update();
				ref->incrScore();
			}

			return ref;
		}
	}

	// add data
	BTexturesAnimRef * ref = BTexturesAnimRef::getNew(NULL, filename);
	m_texturesAnimManager.addRef(ref);

	if(preload)
	{
		if(ref->getScore() == 0)
			ref->update();
		ref->incrScore();
	}

	return ref;
}

BMaterialsAnimRef * BAssetsManager::loadMaterialsAnim(const char * filename, const bool preload)
{
	unsigned int i;
	unsigned int size = m_materialsAnimManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BMaterialsAnimRef * ref = (BMaterialsAnimRef *)m_materialsAnimManager.getRef(i);
		if(strcmp(ref->getFilename(), filename) == 0)
		{
			if(preload)
			{
				if(ref->getScore() == 0)
					ref->update();
				ref->incrScore();
			}

			return ref;
		}
	}

	// add data
	BMaterialsAnimRef * ref = BMaterialsAnimRef::getNew(NULL, filename);
	m_materialsAnimManager.addRef(ref);

	if(preload)
	{
		if(ref->getScore() == 0)
			ref->update();
		ref->incrScore();
	}

	return ref;
}

BSoundRef * BAssetsManager::loadSound(const char * filename, BAssetLocation location, const bool preload)
{
	char fullFilename[256];
    this->getGlobalFilename(filename, fullFilename, location);

	unsigned int i;
	unsigned int size = m_soundManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BSoundRef * ref = (BSoundRef *)m_soundManager.getRef(i);
		if(strcmp(ref->getFilename(), fullFilename) == 0)
		{
			if(preload)
			{
				if(ref->getScore() == 0)
					ref->update();
				ref->incrScore();
			}

			return ref;
		}
	}

	// add data
	BSoundRef * ref = BSoundRef::getNew(0, fullFilename);
	m_soundManager.addRef(ref);

	if(preload)
	{
		if(ref->getScore() == 0)
			ref->update();
		ref->incrScore();
	}

	return ref;
}

BTextureRef * BAssetsManager::loadTexture(const char * filename, BAssetLocation location, const bool mipmap, const bool preload)
{
	BRenderInfo* renderInfo = BRenderInfo::getInstance();

	char fullFilename[256];
    this->getGlobalFilename(filename, fullFilename, location);


	unsigned int i;
	unsigned int size = m_textureManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BTextureRef * ref = (BTextureRef *)m_textureManager.getRef(i);
		if(strcmp(ref->getFilename(), fullFilename) == 0) 
		{
			if(preload)
			{
				
				if(ref->getScore() == 0)
					ref->update();
				ref->incrScore();

			/*	if(renderInfo->disabledTextureFilter){
					BRenderingContext* render = Bizarre::getInstance()->getRenderingContext();
					render->bindTexture(ref->getTextureId());
         			render->setTextureFilterMode(M_TEX_FILTER_LINEAR, M_TEX_FILTER_NEAREST);
				}*/	
			}

			return ref;
		}
	}

	// add data
	BTextureRef * ref = BTextureRef::getNew(0, fullFilename, mipmap);
	m_textureManager.addRef(ref);

	if(preload)
	{
		if(ref->getScore() == 0)
			ref->update();
		ref->incrScore();

	/*	if(renderInfo->disabledTextureFilter){
			BRenderingContext* render = Bizarre::getInstance()->getRenderingContext();
			render->bindTexture(ref->getTextureId());
			render->setTextureFilterMode(M_TEX_FILTER_NEAREST, M_TEX_FILTER_NEAREST);
		} */	
	}

	return ref;
}

BShaderRef * BAssetsManager::loadShader(const char * filename, U_SHADER_TYPES type)
{
	unsigned int i;
	unsigned int size = m_shaderManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
		BShaderRef * ref = (BShaderRef *)m_shaderManager.getRef(i);
		if(strcmp(ref->getFilename(), filename) == 0)
		{
			if(ref->getScore() == 0)
				ref->update();
			ref->incrScore();
			return ref;
		}
	}

	BShaderRef * ref = BShaderRef::getNew(0, type, filename);
	m_shaderManager.addRef(ref);
	if(ref->getScore() == 0)
		ref->update();
	ref->incrScore();
	return ref;
}

BFXRef * BAssetsManager::createFX(BShaderRef * vertexShaderRef, BShaderRef * pixelShaderRef)
{
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();

	unsigned int i;
	unsigned int size = m_FXManager.getFXRefsNumber();
	for(i=0; i<size; i++)
	{
		BFXRef * FXRef = (BFXRef *)m_FXManager.getFXRef(i);
		if((FXRef->getVertexShaderRef() == vertexShaderRef) && (FXRef->getPixelShaderRef() == pixelShaderRef))
			return FXRef;
	}

	unsigned int FXId;
	render->createFX(&FXId, vertexShaderRef->getShaderId(), pixelShaderRef->getShaderId());
	return m_FXManager.addFXRef(FXId, vertexShaderRef, pixelShaderRef);
}

void BAssetsManager::sendToUpdateQueue(BDataRef * ref)
{
	m_updateQueue.push_back(ref);
}

void BAssetsManager::sendToClearQueue(BDataRef * ref)
{
	m_clearQueue.push_back(ref);
}

void BAssetsManager::updateQueueDatas(void)
{
	unsigned int i;
	for(i=0; i<m_updateQueue.size(); i++)
	{
		BDataRef * ref = m_updateQueue[i];
		ref->update();
	}

	m_updateQueue.clear();
}

void BAssetsManager::clearQueueDatas(void)
{
	unsigned int i;
	for(i=0; i<m_clearQueue.size(); i++)
	{
		BDataRef * ref = m_clearQueue[i];
		ref->clear();
	}

	m_clearQueue.clear();
}

/*
BScene * BAssetsManager::addNewScene(void)
{
	BScene * scene = new BScene();
	m_scenes.push_back(scene);
	return scene;
}
*/

void BAssetsManager::clear(void)
{
	//clearScenes();

	m_updateQueue.clear();
	m_clearQueue.clear();

	m_FXManager.clear();
	m_armatureAnimManager.clear();
	m_textureManager.clear();
	m_shaderManager.clear();
	m_soundManager.clear();
	m_meshManager.clear();
	m_fontManager.clear();
	m_armatureAnimManager.clear();
	m_texturesAnimManager.clear();
	m_materialsAnimManager.clear();
}


BTextureRef * BAssetsManager::createTextureFromImage(const char * name, BImage * image )
{
	//BRenderInfo* renderInfo = BRenderInfo::getInstance();
	unsigned int i;
	unsigned int size = m_textureManager.getRefsNumber();
	for(i=0; i<size; i++)
	{
			
		BTextureRef * ref = (BTextureRef *)m_textureManager.getRef(i);
		if(strcmp(ref->getFilename(), name) == 0) 
		{	
			
			if(ref->getScore() == 0)
				ref->fromImage( image );
			ref->incrScore();
				
			return ref;
		}
	}

	// add data
	BTextureRef * ref = BTextureRef::getNew(0, name, true);
	m_textureManager.addRef(ref);

	if(ref->getScore() == 0)
		ref->fromImage( image );
	ref->incrScore();

	/*
	if(renderInfo->disabledTextureFilter){
		BRenderingContext* render = Bizarre::getInstance()->getRenderingContext();
		render->bindTexture(ref->getTextureId());
		render->setTextureFilterMode(M_TEX_FILTER_NEAREST, M_TEX_FILTER_NEAREST);
	}	
	*/

	return ref;
}



BMesh* BAssetsManager::createPlaneFromBox(const BVector3f& min, const BVector3f& max, BTextureRef * textureRef ,U_CULL_MODES cullfaces){
    BMesh* mesh = new BMesh();
    mesh->clear();
        
    mesh->allocTextures(1);
    BTexture* texture = mesh->addNewTexture(textureRef);
    texture->setUWrapMode(M_WRAP_REPEAT);
    texture->setVWrapMode(M_WRAP_REPEAT);
        
    texture->setTexTranslate( BVector2f(0.0f,0.0f) );
    texture->setTexScale( BVector2f(1.f, 1.f) );
    texture->setTexRotate(0.0f);
    
    mesh->allocMaterials(1);
    BMaterial * material = mesh->addNewMaterial();
    material->setType(1);
    float opacity=1, shininess=0, customValue=0;
    BVector3f diffuseColor = BVector3f(1.0f, 1.0f, 1.0f);
    BVector3f specularColor;
    BVector3f emitColor = BVector3f(1.0f, 1.0f, 1.0f);
    BVector3f customColor;
    int blendType = 0;
        
    material->setOpacity(opacity);
    material->setShininess(shininess);
    material->setCustomValue(customValue);
    material->setDiffuse(diffuseColor);
    material->setSpecular(specularColor);
    material->setEmit(emitColor);
    material->setCustomColor(customColor);
        
        
    material->setBlendMode(M_BLENDING_ALPHA);
        
    material->allocTexturesPass(1);
    material->addTexturePass(texture, M_TEX_COMBINE_MODULATE, 0); // <---------
    
    mesh->getBoundingBox()->min = min;
    mesh->getBoundingBox()->max = max;
    
    BSubMesh * subMeshs = mesh->allocSubMeshs(1);
    
    subMeshs[0].getBoundingBox()->min = min;
    subMeshs[0].getBoundingBox()->max = max;
    
    BVector3f * vertices = subMeshs[0].allocVertices(4);
    vertices[0] = min;
    vertices[1] = BVector3f(max.x, min.y, max.z);
    vertices[2] = max;
    vertices[3] = BVector3f(min.x, max.y , min.z );
    
	BVector3f * normals = subMeshs[0].allocNormals(4);
	normals[0] = BVector3f(.0f, .0f, 1.0f);
    normals[1] = BVector3f(.0f, .0f, 1.0f);
    normals[2] = BVector3f(.0f, .0f, 1.0f);
    normals[3] = BVector3f(.0f, .0f, 1.0f);

    //std::cout << "a: " << toText(min) << "  b: " << toText(BVector3f(max.x, min.y, max.z)) << "  c: " << toText(max) << "  d: " << toText(vertices[3]) << std::endl;
        
    //BVector3f * normals = subMeshs[0].allocNormals(4);
    //normals[0] = BVector3f(.0f, .0f, 1.0f);
    //normals[1] = BVector3f(.0f, .0f, 1.0f);
    //normals[2] = BVector3f(.0f, .0f, 1.0f);
    //normals[3] = BVector3f(.0f, .0f, 1.0f);
    
    BVector2f * texCoords = subMeshs[0].allocTexCoords(4);
    texCoords[0] = BVector2f(.0f, .99f);
    texCoords[1] = BVector2f(.99f, .99f);
    texCoords[2] = BVector2f(.99f, .0f);
    texCoords[3] = BVector2f(.0f, .0f);
    subMeshs[0].setMapChannelOffset(0u, 0u);
    
    subMeshs[0].allocIndices(6, U_USHORT);
    unsigned short * indices = (unsigned short *)subMeshs[0].getIndices();
       
    indices[0] =  0u;
    indices[1] =  1u;
    indices[2] =  2u;
    indices[3] =  2u;
    indices[4] =  3u;
    indices[5] =  0u;
        
        
    subMeshs[0].allocDisplays(1);
    unsigned int begin = 0u, size = 6u, cullFace = 0;
    BDisplay * display = subMeshs[0].addNewDisplay(U_PRIMITIVE_TRIANGLES, begin, size);
    display->setMaterial(material);
    display->setCullMode(cullfaces);
    
    return mesh;
}


BTextureRef* BAssetsManager::getDefaultTexture( BDefaultTextureType type ){
	const char * textureName;
	
	switch(type){
		default:
		case DEFAULT_TEX_NO_TEXTURE:
			textureName = "___DEFAULT_TEX_NO_TEXTURE_";
			break;
		
		case DEFAULT_TEX_NOT_FOUND:
			textureName = "___DEFAULT_TEX_NOT_FOUND_";
			break;

	}


	BTextureRef * ref = NULL;

	unsigned int size = m_textureManager.getRefsNumber();
	for(int i=0; i<size; i++)
	{
		ref = (BTextureRef *)m_textureManager.getRef(i);
		if(strcmp(ref->getFilename(), textureName) == 0) 
		{
			return ref;
		}
	}


	BImage image;
	
	const unsigned int xSize = 128u, ySize = 128u; 

	image.create( M_UBYTE, xSize, ySize, 3 );
	
	const char * pixelsArray[12];
	switch(type){
		default:
		case DEFAULT_TEX_NO_TEXTURE:
			pixelsArray[ 0] =	"                                          ";
			pixelsArray[ 1] =	"                                          ";
			pixelsArray[ 2] =	"                                          ";
			pixelsArray[ 3] =	"    **   *   *** ** * * *** * * **  **    ";
			pixelsArray[ 4] =	"    * * * *   *  *  * *  *  * * * * *     ";
			pixelsArray[ 5] =	"    * * * *   *  **  *   *  * * **  **    ";
			pixelsArray[ 6] =	"    * * * *   *  *  * *  *  * * * * *     ";
			pixelsArray[ 7] =	"    * * * *   *  *  * *  *  * * * * *     ";
			pixelsArray[ 8] =	"    * *  *    *  ** * *  *   ** * * **    ";
			pixelsArray[ 9] =	"                                          ";
			pixelsArray[ 10] =	"                                          ";
			pixelsArray[ 11] =	"                                          ";
			break;
		
		case DEFAULT_TEX_NOT_FOUND:
			pixelsArray[ 0] =	"                                                                ";
			pixelsArray[ 1] =	"                                                                ";
			pixelsArray[ 2] =	"                                                                ";
			pixelsArray[ 3] =	"   *** ** * * *** * * **  **  **   *  ***  **  *  * * **  **    ";
			pixelsArray[ 4] =	"    *  *  * *  *  * * * * *   * * * *  *   *  * * * * * * * *   ";
			pixelsArray[ 5] =	"    *  **  *   *  * * **  **  * * * *  *   ** * * * * * * * *   ";
			pixelsArray[ 6] =	"    *  *  * *  *  * * * * *   * * * *  *   *  * * * * * * * *   ";
			pixelsArray[ 7] =	"    *  *  * *  *  * * * * *   * * * *  *   *  * * * * * * * *   ";
			pixelsArray[ 8] =	"    *  ** * *  *   ** * * **  * *  *   *   *   *   ** * * **    ";
			pixelsArray[ 9] =	"                                                                ";
			pixelsArray[ 10] =	"                                                                ";
			pixelsArray[ 11] =	"                                                                ";
			break;

	}


	
	
	unsigned char pixel[3];
	char pixelCharacter;
	unsigned int hArraySize = strlen(pixelsArray[0]);

	for(unsigned int i = 0u; i < xSize; i++)
		for(unsigned int j = 0u; j < ySize; j++){
			pixelCharacter = pixelsArray[ i%12 ][ j%hArraySize ];

			switch(pixelCharacter){
				case '*':
					pixel[0] = 255;
					pixel[1] = 255;
					pixel[2] = 255;
					break;

				default:
				case ' ':
					pixel[0] = 255;
					pixel[1] = 	 0;
					pixel[2] = 220;
			}

			image.writePixel( j, i, &pixel );
		}

	BRenderInfo * renderOptions = BRenderInfo::getInstance();
	bool Disabledfilter = renderOptions->disabledTextureFilter;
	
	renderOptions->disabledTextureFilter = true;
	
	ref = this->createTextureFromImage( textureName, &image );
	
	renderOptions->disabledTextureFilter = Disabledfilter;

	return ref;
}