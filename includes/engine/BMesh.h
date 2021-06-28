/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BMesh.h
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


#ifndef _M_MESH_H
#define _M_MESH_H

#include "BMorphingData.h"
#include "BSkinData.h"


// Constants
#include <limits.h>

#define NONE_ANIMATION UINT_MAX







// Display
class M_ENGINE_EXPORT BDisplay
{
public:

	BDisplay(U_PRIMITIVE_TYPES primitiveType, unsigned int begin, unsigned int size);
	BDisplay(const BDisplay & display);
	~BDisplay(void);

private:

	// draw array infos
	U_PRIMITIVE_TYPES m_primitiveType;
	unsigned int m_begin;
	unsigned int m_size;

	// cull mode
	U_CULL_MODES m_cullMode;

	// material
	BMaterial * m_material;

	// visibility
	bool m_visibility;

public:

	// array infos
	inline U_PRIMITIVE_TYPES getPrimitiveType(void){ return m_primitiveType; }
	inline unsigned int getBegin(void){ return m_begin; }
	inline unsigned int getSize(void){ return m_size; }

	// cull mode
	inline void setCullMode(U_CULL_MODES cullMode){ m_cullMode = cullMode; }
	inline U_CULL_MODES getCullMode(void){ return m_cullMode; }

	// material
	inline void setMaterial(BMaterial * material){ m_material = material; }
	inline BMaterial * getMaterial(void){ return m_material; }

	// visibility
	inline void setVisibility(bool visibility){ m_visibility = visibility; }
	inline bool isVisible(void){ return m_visibility; }
};


// SubMesh
class M_ENGINE_EXPORT BSubMesh
{
public:

	BSubMesh(void);
	~BSubMesh(void);

private:

	// morphing data
	BMorphingData * m_morphingData;

	// skin data
	BSkinData * m_skinData;

	// data
	unsigned int m_indicesSize;
	unsigned int m_verticesSize;
	unsigned int m_normalsSize;
	unsigned int m_tangentsSize;
	unsigned int m_texCoordsSize;
	unsigned int m_colorsSize;

	U_TYPES m_indicesType;
	void * m_indices;

	BColor * m_colors;
	BVector3f * m_vertices;
	BVector3f * m_normals;
	BVector3f * m_tangents;
	BVector2f * m_texCoords;

	// VBO (optional)
	unsigned int m_vboId1;
	unsigned int m_vboId2; // for indices
	
	// mapChannels offset (map of textureCoords offsets used for channel mapping)
	map<unsigned int, unsigned int> m_mapChannelsOffset;
	
	// displays
	unsigned int m_displaysNumber;
	BDisplay ** m_displays;

	// bounding box
	BBox3d m_boundingBox;

public:

	// morphing data
	void clearMorphingData(void);
	BMorphingData * createMorphingData(void);
	inline BMorphingData * getMorphingData(void){ return m_morphingData; }

	// skin data
	void clearSkinData(void);
	BSkinData * createSkinData(void);
	inline BSkinData * getSkinData(void){ return m_skinData; }

	// data
	void clearIndices(void);
	void clearVertices(void);
	void clearNormals(void);
	void clearTangents(void);
	void clearTexCoords(void);
	void clearColors(void);

	void * allocIndices(unsigned int size, U_TYPES type);
	BColor * allocColors(unsigned int size);
	BVector3f * allocVertices(unsigned int size);
	BVector3f * allocNormals(unsigned int size);
	BVector3f * allocTangents(unsigned int size);
	BVector2f * allocTexCoords(unsigned int size);

	inline unsigned int getIndicesSize(void){ return m_indicesSize; }
	inline unsigned int getVerticesSize(void){ return m_verticesSize; }
	inline unsigned int getNormalsSize(void){ return m_normalsSize; }
	inline unsigned int getTangentsSize(void){ return m_tangentsSize; }
	inline unsigned int getTexCoordsSize(void){ return m_texCoordsSize; }
	inline unsigned int getColorsSize(void){ return m_colorsSize; }

	U_TYPES getIndicesType(void){ return m_indicesType; }
	inline void	* getIndices(void){ return m_indices; }

	inline BColor * getColors(void){ return m_colors; }
	inline BVector3f * getVertices(void){ return m_vertices; }
	inline BVector3f * getNormals(void){ return m_normals; }
	inline BVector3f * getTangents(void){ return m_tangents; }
	inline BVector2f * getTexCoords(void){ return m_texCoords; }

	// VBO
	void clearVBO(void);
	unsigned int * getVBOid1(void){ return &m_vboId1; }
	unsigned int * getVBOid2(void){ return &m_vboId2; }
	
	// mapChannels offset
	void clearMapChannelOffset(void);
	void setMapChannelOffset(unsigned int channel, unsigned int offset);
	bool isMapChannelExist(unsigned int channel);
	unsigned int getMapChannelOffset(unsigned int channel);
	map<unsigned int, unsigned int> * getMapChannelOffsets(void){ return &m_mapChannelsOffset; }
	
	// displays
	void allocDisplays(unsigned int size);
	void clearDisplays(void);
	BDisplay * addNewDisplay(U_PRIMITIVE_TYPES primitiveType, unsigned int begin, unsigned int size);
	BDisplay * addNewDisplay( BDisplay * display );
	inline unsigned int getDisplaysNumber(void){ return m_displaysNumber; }
	inline BDisplay * getDisplay(unsigned int id){ return m_displays[id]; }

	// bounding box
	inline BBox3d * getBoundingBox(void){ return &m_boundingBox; }

	// transparency
	bool hasTransparency(void);
};


// BAnimProperties
typedef unsigned int animation;

///No se recomienda el uso de la animacion 0
class M_ENGINE_EXPORT BAnimTransitionProperties{
private:

public:
	animation nextAnim; 
	animation transitionAnim;
	
	
	BAnimTransitionProperties(
		animation nextAnim = NONE_ANIMATION,
		animation transitionAnim = NONE_ANIMATION
		//animation atTheEndAnim = NONE_ANIMATION,
		//animation atTheEndDelayAnim = .0
	):
		nextAnim( nextAnim ),
		transitionAnim( transitionAnim )
		//atTheEndAnim( atTheEndAnim ),
		//atTheEndDelayAnim( atTheEndDelayAnim )
	{}
};


class M_ENGINE_EXPORT BAnimProperties : public BRange
{
private:
	unsigned int transitionsNumber;
	BAnimTransitionProperties * transitions;

public:
	BAnimProperties(void):
	  loops(-1),
	  transitionsNumber( 0u ),
	  atTheEndAnim( NONE_ANIMATION ),
	  atTheEndDelayAnim( .0 ),
	  transitions( NULL )
	{}

	int loops;
	animation atTheEndAnim;
	double    atTheEndDelayAnim;

	inline BAnimTransitionProperties * allocTransitions( unsigned int size ){ transitionsNumber = size; transitions = new BAnimTransitionProperties[size]; return transitions; }
	inline unsigned int getTransitionsNumber(void){ return transitionsNumber; }
	inline BAnimTransitionProperties * getTransitions(void){ return transitions; }
	inline void setTransition( unsigned int transNumber,animation nextAnim, animation transitionAnim ){ if(transNumber < transitionsNumber) transitions[transNumber] = BAnimTransitionProperties(nextAnim, transitionAnim); }
	inline BAnimTransitionProperties * getTransition( animation nextAnim ){ 
		if( !transitions ) return NULL;

		for( unsigned int i = 0u; i < transitionsNumber; i++ ){
			BAnimTransitionProperties * tmpTransition = &transitions[ i ];
			if( tmpTransition->nextAnim == nextAnim )
				return tmpTransition;
		}

		return NULL;
	}


};


// Mesh
class M_ENGINE_EXPORT BMesh
{
public:

	BMesh(void);
	~BMesh(void);

	static BMesh * getNew(void);
	void destroy(void);

private:

	// anims ranges
	unsigned int m_animsRangesNumber;
	BAnimProperties * m_animsRanges;

	// armature anim
	BArmatureAnimRef * m_armatureAnimRef;

	// textures anim
	BTexturesAnimRef * m_texturesAnimRef;

	// materials anim
	BMaterialsAnimRef * m_materialsAnimRef;

	// armature
	BArmature * m_armature;

	// textures
	unsigned int m_texturesNumber;
	BTexture ** m_textures;

	// materials
	unsigned int m_materialsNumber;
	BMaterial ** m_materials;

	// subMeshs
	unsigned int m_subMeshsNumber;
	BSubMesh * m_subMeshs;

	// bounding box
	BBox3d m_boundingBox;

public:

	// clear
	void clear(void);

	// anims ranges
	void clearAnimsProps(void);
	BAnimProperties * allocAnimsProps(unsigned int size);
	inline unsigned int getAnimsPropsNumber(void){ return m_animsRangesNumber; }
	inline BAnimProperties * getAnimProps(unsigned int animId){ return &m_animsRanges[animId]; }
	inline BAnimProperties * getAnimsProps(void){ return m_animsRanges; }

	// armature anim
	inline void setArmatureAnimRef(BArmatureAnimRef * armatureAnimRef){ m_armatureAnimRef = armatureAnimRef; }
	inline BArmatureAnimRef * getArmatureAnimRef(void){ return m_armatureAnimRef; }
	BArmatureAnim * getArmatureAnim(void);

	// textures anim
	inline void setTexturesAnimRef(BTexturesAnimRef * texturesAnimRef){ m_texturesAnimRef = texturesAnimRef; }
	inline BTexturesAnimRef * getTexturesAnimRef(void){ return m_texturesAnimRef; }
	BTexturesAnim * getTexturesAnim(void);

	// materials anim
	inline void setMaterialsAnimRef(BMaterialsAnimRef * materialsAnimRef){ m_materialsAnimRef = materialsAnimRef; }
	inline BMaterialsAnimRef * getMaterialsAnimRef(void){ return m_materialsAnimRef; }
	BMaterialsAnim * getMaterialsAnim(void);

	// armature
	void clearArmature(void);
	BArmature * createArmature(void);
	inline BArmature * getArmature(void){ return m_armature; }

	// textures
	void allocTextures(unsigned int size);
	void clearTextures(void);
	BTexture * addNewTexture(BTextureRef * texRef);
	inline unsigned int getTexturesNumber(void){ return m_texturesNumber; }
	inline BTexture * getTexture(unsigned int id){ return m_textures[id]; }

	// materials
	void allocMaterials(unsigned int size);
	void clearMaterials(void);
	BMaterial * addNewMaterial(BMaterial * material);
	BMaterial * addNewMaterial(void);
	inline unsigned int getMaterialsNumber(void){ return m_materialsNumber; }
	inline BMaterial * getMaterial(unsigned int id){ return m_materials[id]; }

	// subMeshs
	void clearSubMeshs(void);
	BSubMesh * allocSubMeshs(unsigned int size);
	inline unsigned int getSubMeshsNumber(void){ return m_subMeshsNumber; }
	inline BSubMesh * getSubMeshs(void){ return m_subMeshs; }

	// bounding box
	void updateBoundingBox(void);
	inline BBox3d * getBoundingBox(void){ return &m_boundingBox; }
};

#endif