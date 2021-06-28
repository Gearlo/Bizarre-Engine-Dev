/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BMesh.cpp
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


#include <BEngine.h>


// BDisplay
BDisplay::BDisplay(U_PRIMITIVE_TYPES primitiveType, unsigned int begin, unsigned int size):
m_primitiveType(primitiveType),
m_begin(begin),
m_size(size),
m_cullMode(U_CULL_BACK),
m_material(NULL),
m_visibility(true)
{}

BDisplay::BDisplay(const BDisplay & display):
m_primitiveType(display.m_primitiveType),
m_begin(display.m_begin),
m_size(display.m_size),
m_cullMode(display.m_cullMode),
m_material(display.m_material),
m_visibility(display.m_visibility)
{}

BDisplay::~BDisplay(void)
{}




// BSubMesh
BSubMesh::BSubMesh(void):

m_morphingData(NULL),
m_skinData(NULL),

m_indicesSize(0),
m_verticesSize(0),
m_normalsSize(0),
m_tangentsSize(0),
m_texCoordsSize(0),
m_colorsSize(0),

m_indicesType(U_UINT),
m_indices(NULL),

m_vertices(NULL),
m_normals(NULL),
m_tangents(NULL),
m_texCoords(NULL),
m_colors(NULL),

m_vboId1(0),
m_vboId2(0),

m_displaysNumber(0),
m_displays(NULL)
{}

BSubMesh::~BSubMesh(void)
{
	clearVBO();
	
	clearIndices();
	clearVertices();
	clearNormals();
	clearTangents();
	clearTexCoords();
	clearColors();

	clearDisplays();

	clearMorphingData();
	clearSkinData();
}

void BSubMesh::clearMapChannelOffset(void)
{
	m_mapChannelsOffset.clear();
}

void BSubMesh::setMapChannelOffset(unsigned int channel, unsigned int offset)
{
	m_mapChannelsOffset[channel] = offset;
}

bool BSubMesh::isMapChannelExist(unsigned int channel)
{
	map<unsigned int, unsigned int>::iterator iter = m_mapChannelsOffset.find(channel);
	return (iter != m_mapChannelsOffset.end());
}

unsigned int BSubMesh::getMapChannelOffset(unsigned int channel)
{
	map<unsigned int, unsigned int>::iterator iter = m_mapChannelsOffset.find(channel);
	if(iter != m_mapChannelsOffset.end())
		return iter->second;
	return 0;
}

void BSubMesh::clearMorphingData(void)
{
	SAFE_DELETE(m_morphingData);
}

BMorphingData * BSubMesh::createMorphingData(void)
{
	BMorphingData * morphingData = new BMorphingData();
	clearMorphingData();
	m_morphingData = morphingData;
	return morphingData;
}

void BSubMesh::clearSkinData(void)
{
	SAFE_DELETE(m_skinData);
}

BSkinData * BSubMesh::createSkinData(void)
{
	BSkinData * skinData = new BSkinData();
	clearSkinData();
	m_skinData = skinData;
	return skinData;
}

void BSubMesh::clearIndices(void)
{
	m_indicesSize = 0;
	SAFE_FREE(m_indices);
}

void BSubMesh::clearVertices(void)
{
	m_verticesSize = 0;
	SAFE_DELETE_ARRAY(m_vertices);
}

void BSubMesh::clearNormals(void)
{
	m_normalsSize = 0;
	SAFE_DELETE_ARRAY(m_normals);
}

void BSubMesh::clearTangents(void)
{
	m_tangentsSize = 0;
	SAFE_DELETE_ARRAY(m_tangents);
}

void BSubMesh::clearTexCoords(void)
{
	m_texCoordsSize = 0;
	SAFE_DELETE_ARRAY(m_texCoords);
}

void BSubMesh::clearColors(void)
{
	m_colorsSize = 0;
	SAFE_DELETE_ARRAY(m_colors);
}

void * BSubMesh::allocIndices(unsigned int size, U_TYPES type)
{
	clearIndices();
	if(size == 0)
		return NULL;

	m_indicesSize = size;

	switch(type)
	{
	default:
	case U_UINT:
		m_indicesType = U_UINT;
		m_indices = malloc(sizeof(unsigned int)*size);
		break;
	case U_USHORT:
		m_indicesType = U_USHORT;
		m_indices = malloc(sizeof(unsigned short)*size);
		break;
	}
	
	return m_indices;
}

BVector3f * BSubMesh::allocVertices(unsigned int size)
{
	clearVertices();
	if(size == 0)
		return NULL;

	m_verticesSize = size;
	m_vertices = new BVector3f[size];

	return m_vertices;
}

BVector3f * BSubMesh::allocNormals(unsigned int size)
{
	clearNormals();
	if(size == 0)
		return NULL;

	m_normalsSize = size;
	m_normals = new BVector3f[size];

	return m_normals;
}

BVector3f * BSubMesh::allocTangents(unsigned int size)
{
	clearTangents();
	if(size == 0)
		return NULL;
	
	m_tangentsSize = size;
	m_tangents = new BVector3f[size];
	
	return m_tangents;
}

BVector2f * BSubMesh::allocTexCoords(unsigned int size)
{
	clearTexCoords();
	if(size == 0)
		return NULL;

	m_texCoordsSize = size;
	m_texCoords = new BVector2f[size];

	return m_texCoords;
}

BColor * BSubMesh::allocColors(unsigned int size)
{
	clearColors();
	if(size == 0)
		return NULL;

	m_colorsSize = size;
	m_colors = new BColor[size];

	return m_colors;
}

void BSubMesh::clearVBO(void)
{
	Bizarre * engine = Bizarre::getInstance();
	BRenderingContext * render = engine->getRenderingContext();
	if(render && m_vboId1>0)
	{
		render->deleteVBO(&m_vboId1);
		render->deleteVBO(&m_vboId2);
	}
}

void BSubMesh::allocDisplays(unsigned int size)
{
	clearDisplays();
	if(size == 0)
		return;
	m_displays = (BDisplay **) malloc(sizeof(void *)*size);
}

void BSubMesh::clearDisplays(void)
{
	unsigned int i;
	for(i=0; i<m_displaysNumber; i++)
		SAFE_DELETE(m_displays[i]);

	m_displaysNumber = 0;
	SAFE_FREE(m_displays);
}

BDisplay * BSubMesh::addNewDisplay(U_PRIMITIVE_TYPES primitiveType, unsigned int begin, unsigned int size)
{
	BDisplay * display = new BDisplay(primitiveType, begin, size);
	m_displays[m_displaysNumber] = display;
	m_displaysNumber++;
	return display;
}

BDisplay * BSubMesh::addNewDisplay( BDisplay * display )
{
	//BDisplay * display = new BDisplay(primitiveType, begin, size);
	m_displays[m_displaysNumber] = display;
	m_displaysNumber++;
	return display;
}

bool BSubMesh::hasTransparency(void)
{
	
	unsigned int i;
	unsigned int displayNumber = getDisplaysNumber();
	for(i=0; i<displayNumber; i++)
	{
		BDisplay * display = getDisplay(i);

		if((! display->isVisible()) || (! display->getMaterial()))
			continue;

		if(display->getMaterial()->getBlendMode() != M_BLENDING_NONE)
			return true;
	}
	
	return false;
}


// BMesh
BMesh::BMesh(void):

m_animsRangesNumber(0),
m_animsRanges(NULL),

m_armatureAnimRef(NULL),
m_texturesAnimRef(NULL),
m_materialsAnimRef(NULL),

m_armature(NULL),

m_texturesNumber(0),
m_textures(NULL),

m_materialsNumber(0),
m_materials(NULL),

m_subMeshsNumber(0),
m_subMeshs(NULL)
{}

BMesh::~BMesh(void)
{
	clear();
}

BMesh * BMesh::getNew(void)
{
	return new BMesh();
}

void BMesh::destroy(void)
{
	delete this;
}

void BMesh::clear(void)
{
	clearArmature();
	clearTextures();
	clearMaterials();
	clearSubMeshs();
	clearAnimsProps();
	
	m_armatureAnimRef = NULL;
	m_texturesAnimRef = NULL;
	m_materialsAnimRef = NULL;
}

void BMesh::clearAnimsProps(void)
{
	m_animsRangesNumber = 0;
	SAFE_DELETE_ARRAY(m_animsRanges);
}

BAnimProperties * BMesh::allocAnimsProps(unsigned int size)
{
	clearAnimsProps();
	if(size == 0)
		return NULL;

	m_animsRangesNumber = size;
	m_animsRanges = new BAnimProperties[m_animsRangesNumber];
	return m_animsRanges;
}

BArmatureAnim * BMesh::getArmatureAnim(void)
{
	if(! m_armatureAnimRef)
		return NULL;

	return m_armatureAnimRef->getArmatureAnim();
}

BTexturesAnim * BMesh::getTexturesAnim(void)
{
	if(! m_texturesAnimRef)
		return NULL;

	return m_texturesAnimRef->getTexturesAnim();
}

BMaterialsAnim * BMesh::getMaterialsAnim(void)
{
	if(! m_materialsAnimRef)
		return NULL;

	return m_materialsAnimRef->getMaterialsAnim();
}

void BMesh::clearArmature(void)
{
	SAFE_DELETE(m_armature);
}

BArmature * BMesh::createArmature(void)
{
	clearArmature();
	m_armature = new BArmature();
	return m_armature;
}

void BMesh::allocTextures(unsigned int size)
{
	clearTextures();
	if(size == 0)
		return;
	m_textures = (BTexture **) malloc(sizeof(void *)*size);
}

void BMesh::clearTextures(void)
{
	unsigned int i;
	for(i=0; i<m_texturesNumber; i++)
		SAFE_DELETE(m_textures[i]);

	m_texturesNumber = 0;
	SAFE_FREE(m_textures);
}

BTexture * BMesh::addNewTexture(BTextureRef * texRef)
{
	BTexture * texture = new BTexture(texRef);
	m_textures[m_texturesNumber] = texture;
	m_texturesNumber++;
	return texture;
}

void BMesh::allocMaterials(unsigned int size)
{
	clearMaterials();
	if(size == 0)
		return;
	m_materials = (BMaterial **) malloc(sizeof(void *)*size);
}

void BMesh::clearMaterials(void)
{
	unsigned int i;
	for(i=0; i<m_materialsNumber; i++)
		SAFE_DELETE(m_materials[i]);

	m_materialsNumber = 0;
	SAFE_FREE(m_materials);
}

BMaterial * BMesh::addNewMaterial(BMaterial * material)
{
	m_materials[m_materialsNumber] = material;
	m_materialsNumber++;
	return material;
}

BMaterial * BMesh::addNewMaterial(void)
{
	BMaterial * material = new BMaterial();
	m_materials[m_materialsNumber] = material;
	m_materialsNumber++;
	return material;
}

BSubMesh * BMesh::allocSubMeshs(unsigned int size)
{
	clearSubMeshs();
	if(size == 0)
		return NULL;

	m_subMeshsNumber = size;
	m_subMeshs = new BSubMesh[size];
	return m_subMeshs;
}

void BMesh::clearSubMeshs(void)
{
	m_subMeshsNumber = 0;
	SAFE_DELETE_ARRAY(m_subMeshs);
}

void BMesh::updateBoundingBox(void)
{
	if(m_subMeshsNumber > 0)
	{
		BVector3f * min = &m_boundingBox.min;
		BVector3f * max = &m_boundingBox.max;

		BBox3d * box = m_subMeshs[0].getBoundingBox();
		(*min) = box->min;
		(*max) = box->max;

		unsigned int i;
		for(i=1; i<m_subMeshsNumber; i++)
		{
			box = m_subMeshs[i].getBoundingBox();

			BVector3f * subMin = &box->min;
			BVector3f * subMax = &box->max;

			min->x = MIN(min->x, subMin->x);
			min->y = MIN(min->y, subMin->y);
			min->z = MIN(min->z, subMin->z);

			max->x = MAX(max->x, subMax->x);
			max->y = MAX(max->y, subMax->y);
			max->z = MAX(max->z, subMax->z);
		}
	}
}