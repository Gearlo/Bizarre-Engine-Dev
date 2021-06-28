/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Maratis
// BStandardRenderer.h
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


#ifndef _M_STANDARD_RENDERER_H
#define _M_STANDARD_RENDERER_H


#define MAX_ENTITY_LIGHTS 256
#define MAX_SHADOW_LIGHTS 64
#define MAX_DEFAULT_FXS 16
#define MAX_OPAQUE 4096
#define MAX_TRANSP 2048


// Entity light
struct BEntityLight
{
	BBox3d lightBox;
	BOLight * light;
};


// SubMesh pass
class BSubMeshPass
{
public:
	BSubMeshPass(void):occlusionQuery(0){}
	
	unsigned int occlusionQuery;
	unsigned int subMeshId;
	unsigned int lightsNumber;
	BObject3d * object;
	BOLight * lights[4];
};


// Shadow Light
class BShadowLight
{
public:
	BShadowLight(void):shadowTexture(0), score(0){}
	
	int score;
	unsigned int shadowTexture;
	unsigned int shadowQuality;
	float biasUnity;
	BMatrix4x4 shadowMatrix;
};


// Standard Renderer
class BStandardRenderer : public BRenderer
{
public:
	
	BStandardRenderer(void);
	~BStandardRenderer(void);
	
private:
	
	// globals
	bool m_forceNoFX;
	unsigned int m_fboId;
	int m_lightShadow[4];
	int m_lightShadowTexture[4];
	float m_lightShadowBias[4];
	float m_lightShadowBlur[4];
	
	BMatrix4x4 m_currModelViewMatrix;
	BMatrix4x4 m_lightShadowMatrix[4];
	BOCamera * m_currentCamera;
	
	// shadow lights
	unsigned int m_randTexture;
	map<unsigned long, BShadowLight> m_shadowLights;
	
	// skin cache
	unsigned int m_verticesNumber;
	unsigned int m_normalsNumber;
	unsigned int m_tangentsNumber;
	BVector3f * m_vertices;
	BVector3f * m_normals;
	BVector3f * m_tangents;
	
	// default FXs
	unsigned int m_FXsNumber;
	unsigned int m_vertShaders[MAX_DEFAULT_FXS];
	unsigned int m_fragShaders[MAX_DEFAULT_FXS];
	unsigned int m_FXs[MAX_DEFAULT_FXS];
	
	// lists
	int m_transpSortList[MAX_TRANSP];
	int m_opaqueSortList[MAX_OPAQUE];
	float m_transpSortZList[MAX_TRANSP];
	float m_opaqueSortZList[MAX_OPAQUE];
	BSubMeshPass m_transpList[MAX_TRANSP];	
	BSubMeshPass m_opaqueList[MAX_OPAQUE];
	
	// lights list
	int m_entityLightsList[MAX_ENTITY_LIGHTS];
	float m_entityLightsZList[MAX_ENTITY_LIGHTS];
	BEntityLight m_entityLights[MAX_ENTITY_LIGHTS];
	
private:
	
	void addFX(const char * vert, const char * frag);
	void updateSkinning(BMesh * mesh, BArmature * armature);
	void drawDisplay(BSubMesh * subMesh, BDisplay * display, BVector3f * vertices, BVector3f * normals, BVector3f * tangents, BColor * colors);
	//void drawDisplayTriangles(BSubMesh * subMesh, BDisplay * display, BVector3f * vertices);
	void drawOpaques(BSubMesh * subMesh, BArmature * armature);
	void drawTransparents(BSubMesh * subMesh, BArmature * armature);
	void setShadowMatrix(BMatrix4x4 * matrix, BOCamera * camera);
	void updateVisibility(BScene * scene, BOCamera * camera);
	void enableFog(BOCamera * camera);
	
	void initVBO(BSubMesh * subMesh);
	
	float getDistanceToCam(BOCamera * camera, const BVector3f & pos);
	
	// shadow lights
	BShadowLight * createShadowLight(BOLight * light);
	void destroyUnusedShadowLights(void);
	void decreaseShadowLights(void);
	
	// skin cache
	BVector3f * getVertices(unsigned int size);
	BVector3f * getNormals(unsigned int size);
	BVector3f * getTangents(unsigned int size);
	
	// subMesh
	void prepareSubMesh(BScene * scene, BOCamera * camera, BOModel3d * entity, BSubMesh * subMesh);
	
public:
	
	// destroy
	void destroy(void);
	
	// get new
	static BRenderer * getNew(void);

	// name
	static const char * getStaticName(void){ return "StandardRenderer"; }
	const char * getName(void){ return getStaticName(); }
	
	// draw
	void drawScene(BScene * scene, BOCamera * camera);
	
	// extra
	void drawText(BOText * textObj);
};

#endif