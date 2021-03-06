/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Maratis
// BMeshLoad.cpp
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


#include <Bizarre.h>
#include <tinyxml.h>

#include <BLoaders.h>
#include <BMeshTools.h>

inline void readFloatKeys(TiXmlElement * node, BKey * keys)
{
	TiXmlElement * kNode = node->FirstChildElement("k");
	for(kNode; kNode; kNode=kNode->NextSiblingElement("k"))
	{
		int t = 0;
		float * value = keys->createFloatData();

		kNode->QueryIntAttribute("t", &t);
		kNode->QueryFloatAttribute("value", value);

		keys->setT(t);
		keys++;
	}
}

inline void readVector2Keys(TiXmlElement * node, BKey * keys)
{
	TiXmlElement * kNode = node->FirstChildElement("k");
	for(kNode; kNode; kNode=kNode->NextSiblingElement("k"))
	{
		int t = 0;
		BVector2f * vector2 = keys->createVector2Data();

		kNode->QueryIntAttribute("t", &t);
		kNode->QueryFloatAttribute("x", &vector2->x);
		kNode->QueryFloatAttribute("y", &vector2->y);

		keys->setT(t);
		keys++;
	}
}

inline void readVector3Keys(TiXmlElement * node, BKey * keys)
{
	TiXmlElement * kNode = node->FirstChildElement("k");
	for(kNode; kNode; kNode=kNode->NextSiblingElement("k"))
	{
		int t = 0;
		BVector3f * vector3 = keys->createVector3Data();

		kNode->QueryIntAttribute("t", &t);
		kNode->QueryFloatAttribute("x", &vector3->x);
		kNode->QueryFloatAttribute("y", &vector3->y);
		kNode->QueryFloatAttribute("z", &vector3->z);

		keys->setT(t);
		keys++;
	}
}

bool xmlArmatureAnimLoad(const char * filename, void * data)
{
	TiXmlDocument doc(filename);
	if(! doc.LoadFile())
		return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement * pRootNode;
	TiXmlHandle hRoot(0);

	// Maratis
	pRootNode = hDoc.FirstChildElement().Element();
	if(! pRootNode)
		return false;

	if(strcmp(pRootNode->Value(), "Maratis") != 0)
		return false;

	hRoot = TiXmlHandle(pRootNode);

	// BonesAnim
	TiXmlElement * armatureAnimNode = pRootNode->FirstChildElement("ArmatureAnim");
	if(! armatureAnimNode)
		return false;

	unsigned int bonesAnimNumber = 0;
	armatureAnimNode->QueryUIntAttribute("num", &bonesAnimNumber);
	if(bonesAnimNumber == 0)
		return false;

	// create armature anim
	BArmatureAnim * armatureAnim = (BArmatureAnim *)data;
	BObject3dAnim * objAnims = armatureAnim->allocBonesAnim(bonesAnimNumber);

	// Bone
	TiXmlElement * boneNode = armatureAnimNode->FirstChildElement("Bone");
	for(boneNode; boneNode; boneNode=boneNode->NextSiblingElement("Bone"))
	{
		// position
		TiXmlElement * positionNode = boneNode->FirstChildElement("position");
		if(positionNode)
		{
			unsigned int kSize = 0;
			positionNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = objAnims->allocPositionKeys(kSize);
			readVector3Keys(positionNode, keys);
		}

		// rotation
		TiXmlElement * rotationNode = boneNode->FirstChildElement("rotation");
		if(rotationNode)
		{
			unsigned int kSize = 0;
			rotationNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = objAnims->allocRotationKeys(kSize);

			// k
			TiXmlElement * kNode = rotationNode->FirstChildElement("k");
			for(kNode; kNode; kNode=kNode->NextSiblingElement("k"))
			{
				int t = 0;
				BVector3f euler;
				BQuaternion * rotation = keys->createQuaternionData();

				kNode->QueryIntAttribute("t", &t);
				kNode->QueryFloatAttribute("x", &euler.x);
				kNode->QueryFloatAttribute("y", &euler.y);
				kNode->QueryFloatAttribute("z", &euler.z);

				rotation->setFromAngles(euler.x, euler.y, euler.z);

				keys->setT(t);
				keys++;
			}
		}

		// scale
		TiXmlElement * scaleNode = boneNode->FirstChildElement("scale");
		if(scaleNode)
		{
			unsigned int kSize = 0;
			scaleNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = objAnims->allocScaleKeys(kSize);
			readVector3Keys(scaleNode, keys);
		}

		objAnims++;
	}

	return true;
}

bool xmlTextureAnimLoad(const char * filename, void * data)
{
	TiXmlDocument doc(filename);
	if(! doc.LoadFile())
		return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement * pRootNode;
	TiXmlHandle hRoot(0);

	// Maratis
	pRootNode = hDoc.FirstChildElement().Element();
	if(! pRootNode)
		return false;

	if(strcmp(pRootNode->Value(), "Maratis") != 0)
		return false;

	hRoot = TiXmlHandle(pRootNode);

	// TextureAnim
	TiXmlElement * textureAnimNode = pRootNode->FirstChildElement("TextureAnim");
	if(! textureAnimNode)
		return false;

	unsigned int texturesAnimNumber = 0;
	textureAnimNode->QueryUIntAttribute("num", &texturesAnimNumber);
	if(texturesAnimNumber == 0)
		return false;

	// create textures anim
	BTexturesAnim * texturesAnim = (BTexturesAnim *)data;
	BTextureAnim * texAnims = texturesAnim->allocTexturesAnim(texturesAnimNumber);

	// Texture
	TiXmlElement * textureNode = textureAnimNode->FirstChildElement("Texture");
	for(textureNode; textureNode; textureNode=textureNode->NextSiblingElement("Texture"))
	{
		// translate
		TiXmlElement * translateNode = textureNode->FirstChildElement("translate");
		if(translateNode)
		{
			unsigned int kSize = 0;
			translateNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = texAnims->allocTranslateKeys(kSize);
			readVector2Keys(translateNode, keys);
		}

		// scale
		TiXmlElement * scaleNode = textureNode->FirstChildElement("scale");
		if(scaleNode)
		{
			unsigned int kSize = 0;
			scaleNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = texAnims->allocScaleKeys(kSize);
			readVector2Keys(scaleNode, keys);
		}

		// rotate
		TiXmlElement * rotateNode = textureNode->FirstChildElement("rotate");
		if(rotateNode)
		{
			unsigned int kSize = 0;
			rotateNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = texAnims->allocRotationKeys(kSize);
			readFloatKeys(rotateNode, keys);
		}

		texAnims++;
	}

	return true;
}

bool xmlMaterialAnimLoad(const char * filename, void * data)
{
	TiXmlDocument doc(filename);
	if(! doc.LoadFile())
		return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement * pRootNode;
	TiXmlHandle hRoot(0);

	// Maratis
	pRootNode = hDoc.FirstChildElement().Element();
	if(! pRootNode)
		return false;

	if(strcmp(pRootNode->Value(), "Maratis") != 0)
		return false;

	hRoot = TiXmlHandle(pRootNode);

	// TextureAnim
	TiXmlElement * materialAnimNode = pRootNode->FirstChildElement("MaterialAnim");
	if(! materialAnimNode)
		return false;

	unsigned int materialsAnimNumber = 0;
	materialAnimNode->QueryUIntAttribute("num", &materialsAnimNumber);
	if(materialsAnimNumber == 0)
		return false;

	// create materials anim
	BMaterialsAnim * materialsAnim = (BMaterialsAnim *)data;
	BMaterialAnim * matAnims = materialsAnim->allocMaterialsAnim(materialsAnimNumber);

	// Material
	TiXmlElement * materialNode = materialAnimNode->FirstChildElement("Material");
	for(materialNode; materialNode; materialNode=materialNode->NextSiblingElement("Material"))
	{
		// opacity
		TiXmlElement * opacityNode = materialNode->FirstChildElement("opacity");
		if(opacityNode)
		{
			unsigned int kSize = 0;
			opacityNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = matAnims->allocOpacityKeys(kSize);
			readFloatKeys(opacityNode, keys);
		}

		// shininess
		TiXmlElement * shininessNode = materialNode->FirstChildElement("shininess");
		if(shininessNode)
		{
			unsigned int kSize = 0;
			shininessNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = matAnims->allocShininessKeys(kSize);
			readFloatKeys(shininessNode, keys);
		}

		// customValue
		TiXmlElement * customValueNode = materialNode->FirstChildElement("customValue");
		if(customValueNode)
		{
			unsigned int kSize = 0;
			customValueNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = matAnims->allocCustomValueKeys(kSize);
			readFloatKeys(customValueNode, keys);
		}

		// diffuseColor
		TiXmlElement * diffuseColorNode = materialNode->FirstChildElement("diffuseColor");
		if(diffuseColorNode)
		{
			unsigned int kSize = 0;
			diffuseColorNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = matAnims->allocDiffuseKeys(kSize);
			readVector3Keys(diffuseColorNode, keys);
		}

		// specularColor
		TiXmlElement * specularColorNode = materialNode->FirstChildElement("specularColor");
		if(specularColorNode)
		{
			unsigned int kSize = 0;
			specularColorNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = matAnims->allocSpecularKeys(kSize);
			readVector3Keys(specularColorNode, keys);
		}

		// emitColor
		TiXmlElement * emitColorNode = materialNode->FirstChildElement("emitColor");
		if(emitColorNode)
		{
			unsigned int kSize = 0;
			emitColorNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = matAnims->allocEmitKeys(kSize);
			readVector3Keys(emitColorNode, keys);
		}

		// customColor
		TiXmlElement * customColorNode = materialNode->FirstChildElement("customColor");
		if(customColorNode)
		{
			unsigned int kSize = 0;
			customColorNode->QueryUIntAttribute("num", &kSize);
			BKey * keys = matAnims->allocCustomColorKeys(kSize);
			readVector3Keys(customColorNode, keys);
		}

		matAnims++;
	}

	return true;
}

bool loadAnim(TiXmlElement * rootNode, const char * repertory, BMesh * mesh)
{
	BAssetsManager * level = Bizarre::getInstance()->getAssetsManager();


	// Animation
	TiXmlElement * animationNode = rootNode->FirstChildElement("Animation");
	if(! animationNode)
		return false;

	// TextureAnim
	TiXmlElement * texAnimNode = animationNode->FirstChildElement("TextureAnim");
	if(texAnimNode)
	{
		const char * file = texAnimNode->Attribute("file");
		if(file)
		{
			// path
			char path[256];
			getGlobalFilename(path, repertory, file);

			// load textures anim
			BTexturesAnimRef * texturesAnim = level->loadTexturesAnim(path);
			mesh->setTexturesAnimRef(texturesAnim);
		}
	}

	// MaterialAnim
	TiXmlElement * matAnimNode = animationNode->FirstChildElement("MaterialAnim");
	if(matAnimNode)
	{
		const char * file = matAnimNode->Attribute("file");
		if(file)
		{
			// path
			char path[256];
			getGlobalFilename(path, repertory, file);

			// load materials anim
			BMaterialsAnimRef * materialsAnim = level->loadMaterialsAnim(path);
			mesh->setMaterialsAnimRef(materialsAnim);
		}
	}

	// ArmatureAnim
	TiXmlElement * armAnimNode = animationNode->FirstChildElement("ArmatureAnim");
	if(armAnimNode)
	{
		const char * file = armAnimNode->Attribute("file");
		if(file)
		{
			// path
			char path[256];
			getGlobalFilename(path, repertory, file);

			// load armature anim
			BArmatureAnimRef * armatureAnim = level->loadArmatureAnim(path);
			mesh->setArmatureAnimRef(armatureAnim);
		}
	}

	// Anims
	TiXmlElement * animsNode = animationNode->FirstChildElement("Anims");
	if(animsNode)
	{
		unsigned int animsNumber = 0;
		animsNode->QueryUIntAttribute("num", &animsNumber);
		if(animsNumber > 0)
		{
			BAnimProperties * animsRanges = mesh->allocAnimsProps(animsNumber);

			TiXmlElement * animNode = animsNode->FirstChildElement("anim");
			for(animNode; animNode; animNode=animNode->NextSiblingElement("anim"))
			{
				animNode->QueryIntAttribute("start", &animsRanges->start);
				animNode->QueryIntAttribute("end", &animsRanges->end);
				animNode->QueryIntAttribute("loops", &animsRanges->loops);

				animsRanges++;
			}
		}
	}

	return true;
}

bool loadAnimFile(BMesh * mesh, const char * filename, const char * repertory)
{
	TiXmlDocument doc(filename);
	if(! doc.LoadFile())
		return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement * pRootNode;
	TiXmlHandle hRoot(0);

	// Maratis
	pRootNode = hDoc.FirstChildElement().Element();
	if(! pRootNode)
		return false;

	if(strcmp(pRootNode->Value(), "Maratis") != 0)
		return false;

	hRoot = TiXmlHandle(pRootNode);

	return loadAnim(pRootNode, repertory, mesh);
}

bool xmlMeshLoad(const char * filename, void * data)
{
    ULOG_DEBUG("xmlMeshLoad " << filename?filename:"NULL");
	
	BAssetsManager * level = Bizarre::getInstance()->getAssetsManager();

	// read document
	TiXmlDocument doc(filename);
	if(! doc.LoadFile())
	{
	    ULOG_WARNING("TiXmlDocument load failed : " << doc.ErrorDesc() << " line " << doc.ErrorRow());
	    return false;
	}

	TiXmlHandle hDoc(&doc);
	TiXmlElement * pRootNode;
	TiXmlHandle hRoot(0);

	// Maratis
	pRootNode = hDoc.FirstChildElement().Element();
	if(! pRootNode)
	{
	    ULOG_WARNING("Cannot find any root node");
	    return false;
	}

	if(strcmp(pRootNode->Value(), "Maratis") != 0)
	{
	    ULOG_WARNING("Cannot find Maratis root node");
	    return false;
	}

	hRoot = TiXmlHandle(pRootNode);


	// Mesh
	TiXmlElement * pMeshNode = pRootNode->FirstChildElement("Mesh");
	if(! pMeshNode)
	{
	    ULOG_WARNING("Cannot find a Mesh node");
	    return false;
	}

	// create new mesh
	BMesh * mesh = (BMesh *)data;
	mesh->clear();

	char path[256];
	char meshRep[256];
	char vertShadPath[256];
	char fragShadPath[256];

	// mesh rep
	getRepertory(meshRep, filename);

	// animation
	if(! loadAnim(pMeshNode, meshRep, mesh))
	{
		// load external anim file (depracated)
		char animFilename[256];
		strcpy(animFilename, filename);
		strcpy(animFilename + strlen(animFilename) - 4, "anim");
		loadAnimFile(mesh, animFilename, meshRep);
	}

	// Textures
	TiXmlElement * texturesNode = pMeshNode->FirstChildElement("Textures");
	if(texturesNode)
	{
	    ULOG_DEBUG("entering Textures node");
		
		unsigned int numTextures = 0;
		texturesNode->QueryUIntAttribute("num", &numTextures);
		mesh->allocTextures(numTextures);

		// Texture
		TiXmlElement * textureNode = texturesNode->FirstChildElement("Texture");
		for(textureNode; textureNode; textureNode=textureNode->NextSiblingElement("Texture"))
		{
			const char * file = NULL;
			bool mipmap = true;

			// image
			TiXmlElement * imageNode = textureNode->FirstChildElement("image");
			if(imageNode)
			{
				int value = 1;
				file = imageNode->Attribute("filename");
				imageNode->QueryIntAttribute("mipmap", &value);
				mipmap = (value == 1);
			}

			if(! file)
			{
				mesh->addNewTexture(NULL);
				continue;
			}

			// load texture
			getGlobalFilename(path, meshRep, file);

			BTextureRef * texRef = level->loadTexture(path, ON_ABSOLUTE_DIR, mipmap);
			BTexture * texture = mesh->addNewTexture(texRef);

			// tile
			TiXmlElement * tileNode = textureNode->FirstChildElement("tile");
			if(tileNode)
			{
				const char * uTile = tileNode->Attribute("u");
				const char * vTile = tileNode->Attribute("v");
				if(uTile){
					if(strcmp(uTile, "clamp") == 0)
						texture->setUWrapMode(M_WRAP_CLAMP);
					else
						texture->setUWrapMode(M_WRAP_REPEAT);
				}
				if(vTile){
					if(strcmp(vTile, "clamp") == 0)
						texture->setVWrapMode(M_WRAP_CLAMP);
					else
						texture->setVWrapMode(M_WRAP_REPEAT);
				}
			}

			// translate
			TiXmlElement * translateNode = textureNode->FirstChildElement("translate");
			if(translateNode)
			{
				BVector2f translate = texture->getTexTranslate();
				translateNode->QueryFloatAttribute("x", &translate.x);
				translateNode->QueryFloatAttribute("y", &translate.y);
				texture->setTexTranslate(translate);
			}

			// scale
			TiXmlElement * scaleNode = textureNode->FirstChildElement("scale");
			if(scaleNode)
			{
				BVector2f scale = texture->getTexScale();
				scaleNode->QueryFloatAttribute("x", &scale.x);
				scaleNode->QueryFloatAttribute("y", &scale.y);
				texture->setTexScale(scale);
			}

			// rotate
			TiXmlElement * rotateNode = textureNode->FirstChildElement("rotate");
			if(rotateNode)
			{
				float angle = 0;
				rotateNode->QueryFloatAttribute("angle", &angle);
				texture->setTexRotate(angle);
			}
		}
	}


	// Materials
	TiXmlElement * materialsNode = pMeshNode->FirstChildElement("Materials");
	if(materialsNode)
	{
	    ULOG_DEBUG("entering Materials node");
		
		unsigned int numMaterials = 0;
		materialsNode->QueryUIntAttribute("num", &numMaterials);
		mesh->allocMaterials(numMaterials);

		// Material
		TiXmlElement * materialNode = materialsNode->FirstChildElement("Material");
		for(materialNode; materialNode; materialNode=materialNode->NextSiblingElement("Material"))
		{
			BMaterial * material = mesh->addNewMaterial();

			int type = 0;
			materialNode->QueryIntAttribute("type", &type);
			material->setType(type);

			float opacity=1, shininess=0, customValue=0;
			BVector3f diffuseColor;
			BVector3f specularColor;
			BVector3f emitColor;
			BVector3f customColor;

			// blend
			int blendType = 0;
			TiXmlElement * blendNode = materialNode->FirstChildElement("blend");
			if(blendNode)
				blendNode->QueryIntAttribute("type", &blendType);

			switch(blendType)
			{
			case 2:
				material->setBlendMode(M_BLENDING_ALPHA);
				break;
			case 3:
				material->setBlendMode(M_BLENDING_ADD);
				break;
			case 4:
				material->setBlendMode(M_BLENDING_PRODUCT);
				break;
			}

			// opacity
			TiXmlElement * opacityNode = materialNode->FirstChildElement("opacity");
			if(opacityNode)
				opacityNode->QueryFloatAttribute("value", &opacity);

			// shininess
			TiXmlElement * shininessNode = materialNode->FirstChildElement("shininess");
			if(shininessNode)
				shininessNode->QueryFloatAttribute("value", &shininess);

			// customValue
			TiXmlElement * customValueNode = materialNode->FirstChildElement("customValue");
			if(customValueNode)
				customValueNode->QueryFloatAttribute("value", &customValue);

			material->setOpacity(opacity);
			material->setShininess(shininess);
			material->setCustomValue(customValue);

			// diffuseColor
			TiXmlElement * diffuseColorNode = materialNode->FirstChildElement("diffuseColor");
			if(diffuseColorNode){
				diffuseColorNode->QueryFloatAttribute("r", &diffuseColor.x);
				diffuseColorNode->QueryFloatAttribute("g", &diffuseColor.y);
				diffuseColorNode->QueryFloatAttribute("b", &diffuseColor.z);
				material->setDiffuse(diffuseColor);
			}

			// specularColor
			TiXmlElement * specularColorNode = materialNode->FirstChildElement("specularColor");
			if(specularColorNode){
				specularColorNode->QueryFloatAttribute("r", &specularColor.x);
				specularColorNode->QueryFloatAttribute("g", &specularColor.y);
				specularColorNode->QueryFloatAttribute("b", &specularColor.z);
				material->setSpecular(specularColor);
			}

			// emitColor
			TiXmlElement * emitColorNode = materialNode->FirstChildElement("emitColor");
			if(emitColorNode){
				emitColorNode->QueryFloatAttribute("r", &emitColor.x);
				emitColorNode->QueryFloatAttribute("g", &emitColor.y);
				emitColorNode->QueryFloatAttribute("b", &emitColor.z);
				material->setEmit(emitColor);
			}

			// customColor
			TiXmlElement * customColorNode = materialNode->FirstChildElement("customColor");
			if(customColorNode){
				customColorNode->QueryFloatAttribute("r", &customColor.x);
				customColorNode->QueryFloatAttribute("g", &customColor.y);
				customColorNode->QueryFloatAttribute("b", &customColor.z);
				material->setCustomColor(customColor);
			}

			// TexturesPass
			TiXmlElement * texturesPassNode = materialNode->FirstChildElement("TexturesPass");
			if(texturesPassNode)
			{
				unsigned int numTexturesPass = 0;
				texturesPassNode->QueryUIntAttribute("num", &numTexturesPass);
				material->allocTexturesPass(numTexturesPass);

				// texturePass
				TiXmlElement * texturePassNode = texturesPassNode->FirstChildElement("texturePass");
				for(texturePassNode; texturePassNode; texturePassNode=texturePassNode->NextSiblingElement("texturePass"))
				{
					int textureId = -1;
					unsigned int mapChannel = 0;

					const char * mode = texturePassNode->Attribute("mode");
					texturePassNode->QueryIntAttribute("texture", &textureId);

					if(textureId < 0)
					{
						material->addTexturePass(NULL, M_TEX_COMBINE_MODULATE, 0);
						continue;
					}

					texturePassNode->QueryUIntAttribute("mapChannel", &mapChannel);

					// combine mode
					M_TEX_COMBINE_MODES texCombine = M_TEX_COMBINE_MODULATE;

					if(strcmp(mode, "modulate") == 0)
						texCombine = M_TEX_COMBINE_MODULATE;
					else if(strcmp(mode, "replace") == 0)
						texCombine = M_TEX_COMBINE_REPLACE;
					else if(strcmp(mode, "alpha") == 0)
						texCombine = M_TEX_COMBINE_ALPHA;
					else if(strcmp(mode, "dot") == 0)
						texCombine = M_TEX_COMBINE_DOT;
					else if(strcmp(mode, "add") == 0)
						texCombine = M_TEX_COMBINE_ADD;
					else if(strcmp(mode, "sub") == 0)
						texCombine = M_TEX_COMBINE_SUB;

					// add texture pass
					material->addTexturePass(mesh->getTexture(textureId), texCombine, mapChannel);
				}
			}

			// FX
			{
				// vertexShader
				const char * vertShadFile = NULL;
				TiXmlElement * vertexShaderNode = materialNode->FirstChildElement("vertexShader");
				if(vertexShaderNode){
					vertShadFile = vertexShaderNode->Attribute("file");
				}

				// fragmentShader
				const char * fragShadFile = NULL;
				TiXmlElement * fragmentShaderNode = materialNode->FirstChildElement("fragmentShader");
				if(fragmentShaderNode){
					fragShadFile = fragmentShaderNode->Attribute("file");
				}

				// create FX
				if(vertShadFile && fragShadFile)
				{
					getGlobalFilename(vertShadPath, meshRep, vertShadFile);
					getGlobalFilename(fragShadPath, meshRep, fragShadFile);

					BShaderRef * vertShad = level->loadShader(vertShadPath, M_SHADER_VERTEX);
					BShaderRef * pixShad = level->loadShader(fragShadPath, M_SHADER_PIXEL);
					if(vertShad && pixShad)
					{
						BFXRef * FXRef = level->createFX(vertShad, pixShad);
						material->setFXRef(FXRef);
					}
				}
			}

			// ZFX (optional optim)
			{
				// ZVertexShader
				const char * vertShadFile = NULL;
				TiXmlElement * vertexShaderNode = materialNode->FirstChildElement("ZVertexShader");
				if(vertexShaderNode){
					vertShadFile = vertexShaderNode->Attribute("file");
				}

				// ZFragmentShader
				const char * fragShadFile = NULL;
				TiXmlElement * fragmentShaderNode = materialNode->FirstChildElement("ZFragmentShader");
				if(fragmentShaderNode){
					fragShadFile = fragmentShaderNode->Attribute("file");
				}

				// create ZFX
				if(vertShadFile && fragShadFile)
				{
					getGlobalFilename(vertShadPath, meshRep, vertShadFile);
					getGlobalFilename(fragShadPath, meshRep, fragShadFile);

					BShaderRef * vertShad = level->loadShader(vertShadPath, M_SHADER_VERTEX);
					BShaderRef * pixShad = level->loadShader(fragShadPath, M_SHADER_PIXEL);
					if(vertShad && pixShad)
					{
						BFXRef * ZFXRef = level->createFX(vertShad, pixShad);
						material->setZFXRef(ZFXRef);
					}
				}
			}
		}
	}


	// Bones
	TiXmlElement * bonesNode = pMeshNode->FirstChildElement("Bones");
	if(bonesNode)
	{
	    ULOG_DEBUG("entering Bones node");
		
		BArmature * armature = mesh->createArmature();

		unsigned int b, numBones = 0;
		bonesNode->QueryUIntAttribute("num", &numBones);
		armature->allocBones(numBones);

		// add bones
		for(b=0; b<numBones; b++)
			armature->addNewBone();
		b = 0;

		// Bone
		TiXmlElement * boneNode = bonesNode->FirstChildElement("Bone");
		for(boneNode; boneNode; boneNode=boneNode->NextSiblingElement("Bone"))
		{
			if(b >= armature->getBonesNumber())
				break;

			BOBone * bone = armature->getBone(b);

			const char * name = boneNode->Attribute("name");
			if(name)
				bone->setName(name);

			// parent
			TiXmlElement * parentNode = boneNode->FirstChildElement("parent");
			if(parentNode){
				unsigned int boneId = 0;
				parentNode->QueryUIntAttribute("id", &boneId);
				bone->linkTo(armature->getBone(boneId));
			}

			// position
			TiXmlElement * positionNode = boneNode->FirstChildElement("position");
			if(positionNode){
				BVector3f position;
				positionNode->QueryFloatAttribute("x", &position.x);
				positionNode->QueryFloatAttribute("y", &position.y);
				positionNode->QueryFloatAttribute("z", &position.z);
				bone->setPosition(position);
			}

			// rotation
			TiXmlElement * rotationNode = boneNode->FirstChildElement("rotation");
			if(rotationNode){

				BVector3f euler;
				rotationNode->QueryFloatAttribute("x", &euler.x);
				rotationNode->QueryFloatAttribute("y", &euler.y);
				rotationNode->QueryFloatAttribute("z", &euler.z);
				bone->setEulerRotation(euler);
			}

			// scale
			TiXmlElement * scaleNode = boneNode->FirstChildElement("scale");
			if(scaleNode){
				BVector3f scale;
				scaleNode->QueryFloatAttribute("x", &scale.x);
				scaleNode->QueryFloatAttribute("y", &scale.y);
				scaleNode->QueryFloatAttribute("z", &scale.z);
				bone->setScale(scale);
			}

			b++;
		}

		// construct bones inverse pose matrix
		armature->constructBonesInversePoseMatrix();
	}


	// SubMeshs
	TiXmlElement * subMeshsNode = pMeshNode->FirstChildElement("SubMeshs");
	if(! subMeshsNode)
		return true;

	unsigned int nuBSubMeshs = 0;
	subMeshsNode->QueryUIntAttribute("num", &nuBSubMeshs);
	if(nuBSubMeshs == 0)
		return true;

	// alloc subMeshs
	BSubMesh * subMeshs = mesh->allocSubMeshs(nuBSubMeshs);

	// BoundingBox
	TiXmlElement * boundingBoxNode = pMeshNode->FirstChildElement("BoundingBox");
	if(boundingBoxNode)
	{
		BVector3f * min = &mesh->getBoundingBox()->min;
		BVector3f * max = &mesh->getBoundingBox()->max;

		boundingBoxNode->QueryFloatAttribute("minx", &min->x);
		boundingBoxNode->QueryFloatAttribute("miny", &min->y);
		boundingBoxNode->QueryFloatAttribute("minz", &min->z);

		boundingBoxNode->QueryFloatAttribute("maxx", &max->x);
		boundingBoxNode->QueryFloatAttribute("maxy", &max->y);
		boundingBoxNode->QueryFloatAttribute("maxz", &max->z);
	}

	// SubMesh
	TiXmlElement * SubMeshNode = subMeshsNode->FirstChildElement("SubMesh");
	for(SubMeshNode; SubMeshNode; SubMeshNode=SubMeshNode->NextSiblingElement("SubMesh"))
	{
		BSubMesh * subMesh = subMeshs;

		// BoundingBox
		boundingBoxNode = SubMeshNode->FirstChildElement("BoundingBox");
		if(boundingBoxNode)
		{
			BVector3f * min = &subMesh->getBoundingBox()->min;
			BVector3f * max = &subMesh->getBoundingBox()->max;

			boundingBoxNode->QueryFloatAttribute("minx", &min->x);
			boundingBoxNode->QueryFloatAttribute("miny", &min->y);
			boundingBoxNode->QueryFloatAttribute("minz", &min->z);

			boundingBoxNode->QueryFloatAttribute("maxx", &max->x);
			boundingBoxNode->QueryFloatAttribute("maxy", &max->y);
			boundingBoxNode->QueryFloatAttribute("maxz", &max->z);
		}

		// Vertices
		TiXmlElement * verticesNode = SubMeshNode->FirstChildElement("Vertices");
		if(verticesNode)
		{
			unsigned int numVertices = 0;
			verticesNode->QueryUIntAttribute("num", &numVertices);
			BVector3f * vertices = subMesh->allocVertices(numVertices);

			// vertex
			TiXmlElement * vertexNode = verticesNode->FirstChildElement("vertex");
			for(vertexNode; vertexNode; vertexNode=vertexNode->NextSiblingElement("vertex"))
			{
				vertexNode->QueryFloatAttribute("x", &vertices->x);
				vertexNode->QueryFloatAttribute("y", &vertices->y);
				vertexNode->QueryFloatAttribute("z", &vertices->z);
				vertices++;
			}
		}

		// Normals
		TiXmlElement * normalsNode = SubMeshNode->FirstChildElement("Normals");
		if(normalsNode)
		{
			unsigned int numNormals = 0;
			normalsNode->QueryUIntAttribute("num", &numNormals);
			BVector3f * normals = subMesh->allocNormals(numNormals);

			// normal
			TiXmlElement * normalNode = normalsNode->FirstChildElement("normal");
			for(normalNode; normalNode; normalNode=normalNode->NextSiblingElement("normal"))
			{
				normalNode->QueryFloatAttribute("x", &normals->x);
				normalNode->QueryFloatAttribute("y", &normals->y);
				normalNode->QueryFloatAttribute("z", &normals->z);
				normals->normalize();
				normals++;
			}
		}

		// Tangents
		TiXmlElement * tangentsNode = SubMeshNode->FirstChildElement("Tangents");
		if(tangentsNode)
		{
			unsigned int numTangents = 0;
			tangentsNode->QueryUIntAttribute("num", &numTangents);
			BVector3f * tangents = subMesh->allocTangents(numTangents);

			// tangent
			TiXmlElement * tangentNode = tangentsNode->FirstChildElement("tangent");
			for(tangentNode; tangentNode; tangentNode=tangentNode->NextSiblingElement("tangent"))
			{
				tangentNode->QueryFloatAttribute("x", &tangents->x);
				tangentNode->QueryFloatAttribute("y", &tangents->y);
				tangentNode->QueryFloatAttribute("z", &tangents->z);
				tangents->normalize();
				tangents++;
			}
		}

		// TexCoords
		TiXmlElement * texCoordsNode = SubMeshNode->FirstChildElement("TexCoords");
		if(texCoordsNode)
		{
			// num
			unsigned int numTexCoords = 0;
			texCoordsNode->QueryUIntAttribute("num", &numTexCoords);
			BVector2f * texCoords = subMesh->allocTexCoords(numTexCoords);

			// mapChannels
			unsigned int numVertices = subMesh->getVerticesSize();
			const char * mapChannelsData = texCoordsNode->Attribute("mapChannels");

			// read channels
			if(mapChannelsData)
			{
				char str[256];
				strcpy(str, mapChannelsData);
				char * pch;

				unsigned int offset = 0;
				pch = strtok(str, " ");
				while(pch != NULL)
				{
					unsigned int channel = 0;
					sscanf(pch, "%d", &channel);

					subMesh->setMapChannelOffset(channel, offset);

					pch = strtok(NULL, " ");
					offset += numVertices;
				}
			}
			// create default channels
			else if((numVertices > 0) && (numTexCoords > numVertices))
			{
				unsigned int numChannels = numTexCoords / numVertices;
				for(unsigned int c=0; c<numChannels; c++)
					subMesh->setMapChannelOffset(c, numVertices*c);
			}

			// texCoord
			TiXmlElement * texCoordNode = texCoordsNode->FirstChildElement("texCoord");
			for(texCoordNode; texCoordNode; texCoordNode=texCoordNode->NextSiblingElement("texCoord"))
			{
				texCoordNode->QueryFloatAttribute("x", &texCoords->x);
				texCoordNode->QueryFloatAttribute("y", &texCoords->y);
				texCoords++;
			}
		}

		// Colors
		TiXmlElement * colorsNode = SubMeshNode->FirstChildElement("Colors");
		if(colorsNode)
		{
			unsigned int numColors = 0;
			colorsNode->QueryUIntAttribute("num", &numColors);
			BColor * colors = subMesh->allocColors(numColors);

			// color
			TiXmlElement * colorNode = colorsNode->FirstChildElement("color");
			for(colorNode; colorNode; colorNode=colorNode->NextSiblingElement("color"))
			{
				float x = 1, y = 1, z = 1, w = 1;
				colorNode->QueryFloatAttribute("x", &x);
				colorNode->QueryFloatAttribute("y", &y);
				colorNode->QueryFloatAttribute("z", &z);
				colorNode->QueryFloatAttribute("w", &w);

				colors->r = (unsigned char)x*255;
				colors->g = (unsigned char)y*255;
				colors->b = (unsigned char)z*255;
				colors->a = (unsigned char)w*255;;

				colors++;
			}
		}

		// Indices
		TiXmlElement * indicesNode = SubMeshNode->FirstChildElement("Indices");
		if(indicesNode)
		{
			U_TYPES indicesType;
			unsigned int vSize = subMesh->getVerticesSize();

			if(vSize < 65536){
				indicesType = U_USHORT;
			}
			else{
				indicesType = U_UINT;
			}

			unsigned int numIndices = 0;
			indicesNode->QueryUIntAttribute("num", &numIndices);
			subMesh->allocIndices(numIndices, indicesType);

			// indices
			TiXmlElement * indexNode = indicesNode->FirstChildElement("index");
			switch(indicesType)
			{
			case U_USHORT:
				{
					unsigned short * indices = (unsigned short *)subMesh->getIndices();
					for(indexNode; indexNode; indexNode=indexNode->NextSiblingElement("index"))
					{
						unsigned int id;
						indexNode->QueryUIntAttribute("value", &id);
						*indices = (unsigned short)id;
						indices++;
					}
				}
				break;
			case U_UINT:
				{
					unsigned int * indices = (unsigned int *)subMesh->getIndices();
					for(indexNode; indexNode; indexNode=indexNode->NextSiblingElement("index"))
					{
						indexNode->QueryUIntAttribute("value", indices);
						indices++;
					}
				}
				break;
			}
		}

		// Skins
		TiXmlElement * skinsNode = SubMeshNode->FirstChildElement("Skins");
		if(skinsNode)
		{
			BSkinData * skinData = subMesh->createSkinData();

			unsigned int numSkins = 0;
			skinsNode->QueryUIntAttribute("num", &numSkins);
			BSkinPoint * skinPoints = skinData->allocPoints(numSkins);

			// skin
			TiXmlElement * skinNode = skinsNode->FirstChildElement("skin");
			for(skinNode; skinNode; skinNode=skinNode->NextSiblingElement("skin"))
			{
				unsigned int vertexId = 0;
				unsigned int numBones = 0;

				skinNode->QueryUIntAttribute("vertex", &vertexId);
				skinNode->QueryUIntAttribute("numBones", &numBones);

				if(numBones > 0)
				{
					skinPoints->setVertexId(vertexId);
					skinPoints->allocateBonesLinks(numBones);

					unsigned short * bonesIds = skinPoints->getBonesIds();
					float * bonesWeights = skinPoints->getBonesWeights();

					TiXmlElement * boneNode = skinNode->FirstChildElement("bone");
					for(boneNode; boneNode; boneNode=boneNode->NextSiblingElement("bone"))
					{
						unsigned int id;
						boneNode->QueryUIntAttribute("id", &id);
						boneNode->QueryFloatAttribute("weight", bonesWeights);

						*bonesIds = id;

						bonesIds++;
						bonesWeights++;
					}
				}

				skinPoints++;
			}
		}

		// Displays
		TiXmlElement * displaysNode = SubMeshNode->FirstChildElement("Displays");
		if(displaysNode)
		{
			unsigned int numDisplays = 0;
			displaysNode->QueryUIntAttribute("num", &numDisplays);
			subMesh->allocDisplays(numDisplays);

			// display
			TiXmlElement * displayNode = displaysNode->FirstChildElement("display");
			for(displayNode; displayNode; displayNode=displayNode->NextSiblingElement("display"))
			{
				unsigned int begin, size, material, cullFace = 0;

				displayNode->QueryUIntAttribute("begin", &begin);
				displayNode->QueryUIntAttribute("size", &size);
				displayNode->QueryUIntAttribute("material", &material);
				displayNode->QueryUIntAttribute("cullFace", &cullFace);

				// create display
				BDisplay * display = subMesh->addNewDisplay(U_PRIMITIVE_TRIANGLES, begin, size);

				// set material
				if(material < mesh->getMaterialsNumber())
					display->setMaterial(mesh->getMaterial(material));

				// set cull mode
				U_CULL_MODES cullMode = U_CULL_BACK;
				if(cullFace == 1)
					cullMode = U_CULL_FRONT;
				else if(cullFace == 2)
					cullMode = U_CULL_NONE;
				display->setCullMode(cullMode);
			}
		}

		// generate tangents if needed
		if(! subMesh->getTangents())
			generateTangents(subMesh);


		subMeshs++;
	}

    ULOG_DEBUG("xmlMeshLoad success: "<<nuBSubMeshs<<" submeshs found");
	
	return true;
}
