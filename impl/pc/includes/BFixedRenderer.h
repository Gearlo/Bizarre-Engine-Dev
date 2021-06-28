/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Maratis
// BFixedRenderer.h
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


#ifndef _M_FIXED_RENDERER_H
#define _M_FIXED_RENDERER_H


// Fixed Renderer
class BFixedRenderer : public BRenderer
{
public:
	
	BFixedRenderer(void);
	~BFixedRenderer(void);
	
private:
	
	// skin cache
	unsigned int m_verticesNumber;
	unsigned int m_normalsNumber;
	BVector3f * m_vertices;
	BVector3f * m_normals;
	
private:
	
	void updateSkinning(BMesh * mesh, BArmature * armature);
	void drawDisplay(BSubMesh * subMesh, BDisplay * display, BVector3f * vertices, BVector3f * normals, BColor * colors);
	void drawDisplayTriangles(BSubMesh * subMesh, BDisplay * display, BVector3f * vertices);
	void drawOpaques(BSubMesh * subMesh, BArmature * armature);
	void drawTransparents(BSubMesh * subMesh, BArmature * armature);
	void updateVisibility(BScene * scene, BOCamera * camera);
	void enableFog(BOCamera * camera);
	
	float getDistanceToCam(BOCamera * camera, const BVector3f & pos);
	
	// skin cache
	BVector3f * getVertices(unsigned int size);
	BVector3f * getNormals(unsigned int size);
	
public:
	
	// destroy
	void destroy(void);
	
	// get new
	static BRenderer * getNew(void);

	// name
	static const char * getStaticName(void){ return "FixedRenderer"; }
	const char * getName(void){ return getStaticName(); }
	
	// draw
	void drawScene(BScene * scene, BOCamera * camera);
	
	// extra
	void drawText(BOText * textObj);
};

#endif