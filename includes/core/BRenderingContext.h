/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BRenderingContext.h
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


#ifndef _M_RENDERING_CONTEXT_H
#define _M_RENDERING_CONTEXT_H

#include <BImplTypes.h>


// rendering context
class M_CORE_EXPORT BRenderingContext
{
public:

	// destructor
	virtual ~BRenderingContext(void){}

	//  version
    virtual const char* getRendererVersion() = 0;

	// view
	virtual void setOrthoView(float left, float right, float bottom, float top, float zNear, float zFar) = 0;
	virtual void setPerspectiveView(float fov, float ratio, float zNear, float zFar) = 0;

	// viewport
	virtual void setViewport(int x, int y, unsigned int width, unsigned int height) = 0;

	// clear
	virtual void clear(int buffer) = 0;
	virtual void setClearColor(const BVector4f & color) = 0;

	// texture
	virtual void enableTexture(void) = 0;
	virtual void disableTexture(void) = 0;
	virtual void setTextureGenMode(M_TEX_GEN_MODES mode) = 0;
	virtual void setTextureFilterMode(M_TEX_FILTER_MODES min, M_TEX_FILTER_MODES mag) = 0;
	virtual void setTextureUWrapMode(M_WRAP_MODES wrap) = 0;
	virtual void setTextureVWrapMode(M_WRAP_MODES wrap) = 0;
	virtual void setTextureCombineMode(M_TEX_COMBINE_MODES combine) = 0;
	virtual void bindTexture(unsigned int textureId, const unsigned int multitextureId = 0) = 0;
	virtual void createTexture(unsigned int * textureId) = 0;
	virtual void deleteTexture(unsigned int * textureId) = 0;
	virtual void sendTextureImage(BImage * image, bool mipMap, bool filter, bool compress) = 0;
	virtual void texImage(unsigned int level, unsigned int width, unsigned int height, U_TYPES type, M_TEX_MODES mode, const void * pixels) = 0;
	virtual void texSubImage(unsigned int level, int xoffset, int yoffset, unsigned int width, unsigned int height, U_TYPES type, M_TEX_MODES mode, const void * pixels) = 0;
	virtual void generateMipMap(void) = 0;
	virtual void getTexImage(unsigned int level, BImage * image){}

	// frame buffer
	virtual void createFrameBuffer(unsigned int * frameBufferId) = 0;
	virtual void deleteFrameBuffer(unsigned int * frameBufferId) = 0;
	virtual void bindFrameBuffer(unsigned int frameBufferId) = 0;
	virtual void getCurrentFrameBuffer(unsigned int * frameBufferId) = 0;
	virtual void attachFrameBufferTexture(M_FRAME_BUFFER_ATTACHMENT attachment, unsigned int textureId) = 0;
	virtual void attachFrameBufferRB(M_FRAME_BUFFER_ATTACHMENT attachment, unsigned int renderBufferId){}
	virtual void setDrawingBuffers(M_FRAME_BUFFER_ATTACHMENT * buffers, unsigned int size) = 0;

	// render buffer
	virtual void createRenderBuffer(unsigned int * renderBufferId){}
	virtual void deleteRenderBuffer(unsigned int * renderBufferId){}
	virtual void bindRenderBuffer(unsigned int renderBufferId){}
	virtual void setRenderBuffer(M_RENDER_BUFFER_MODES mode, unsigned int width, unsigned int height){}

	// shaders
	virtual void createVertexShader(unsigned int * shaderId) = 0;
	virtual void createPixelShader(unsigned int * shaderId) = 0;
	virtual void deleteShader(unsigned int * shaderId) = 0;
	virtual void sendShaderSource(unsigned int shaderId, const char * source) = 0;

	// FX
	virtual void bindFX(unsigned int fxId) = 0;
	virtual void createFX(unsigned int * fxId, unsigned int vertexShaderId, unsigned int pixelShaderId) = 0;
	virtual void updateFX(unsigned int fxId) = 0;
	virtual void deleteFX(unsigned int * fxId) = 0;
	virtual void sendUniformInt(unsigned int fxId, const char * name, int * values, const int count = 1) = 0;
	virtual void sendUniformFloat(unsigned int fxId, const char * name, float * value, const int count = 1) = 0;
    virtual void sendUniformVec2(unsigned int fxId, const char * name, float * values, const int count = 1) = 0;
	virtual void sendUniformVec3(unsigned int fxId, const char * name, float * values, const int count = 1) = 0;
	virtual void sendUniformVec4(unsigned int fxId, const char * name, float * values, const int count = 1) = 0;
	virtual void sendUniformMatrix(unsigned int fxId, const char * name, BMatrix4x4 * matrix, const int count = 1, const bool transpose = false) = 0;
	virtual void getAttribLocation(unsigned int fxId, const char * name, int * location) = 0;

	// VBO
	virtual void createVBO(unsigned int * vboId){}
	virtual void deleteVBO(unsigned int * vboId){}
	virtual void bindVBO(M_VBO_TYPES type, unsigned int vboId){}
	virtual void setVBO(M_VBO_TYPES type, const void * data, unsigned int size, M_VBO_MODES mode){}
	virtual void setVBOSubData(M_VBO_TYPES type, unsigned int offset, const void * data, unsigned int size){}
	
	// arrays
	virtual void enableVertexArray(void) = 0;
	virtual void enableColorArray(void) = 0;
	virtual void enableNormalArray(void) = 0;
	virtual void enableTexCoordArray(void) = 0;
	virtual void enableAttribArray(unsigned int location) = 0;
	virtual void disableVertexArray(void) = 0;
	virtual void disableColorArray(void) = 0;
	virtual void disableNormalArray(void) = 0;
	virtual void disableTexCoordArray(void) = 0;
	virtual void disableAttribArray(unsigned int location) = 0;
	virtual void setVertexPointer(U_TYPES type, unsigned int components, const void * pointer) = 0;
	virtual void setColorPointer(U_TYPES type, unsigned int components, const void * pointer) = 0;
	virtual void setNormalPointer(U_TYPES type, const void * pointer) = 0;
	virtual void setTexCoordPointer(U_TYPES type, unsigned int components, const void * pointer) = 0;
	virtual void setAttribPointer(unsigned int location, U_TYPES type, unsigned int components, const void * pointer, const bool normalized = false) = 0;

	// draw
	virtual void drawArray(U_PRIMITIVE_TYPES type, unsigned int begin, unsigned int size) = 0;
	virtual void drawElement(U_PRIMITIVE_TYPES type, unsigned int size, U_TYPES indicesType, const void * indices) = 0;

	// lines
	virtual void enableLineAntialiasing(void) = 0;
	virtual void disableLineAntialiasing(void) = 0;

	// material
	virtual void setMaterialDiffuse(const BVector4f & diffuse) = 0;
	virtual void setMaterialSpecular(const BVector4f & specular) = 0;
	virtual void setMaterialAmbient(const BVector4f & ambient) = 0;
	virtual void setMaterialEmit(const BVector4f & emit) = 0;
	virtual void setMaterialShininess(float shininess) = 0;

	// scissor
	virtual void enableScissorTest(void) = 0;
	virtual void disableScissorTest(void) = 0;
	virtual void setScissor(int x, int y, unsigned int width, unsigned int height) = 0;

	// color
	virtual void setColor(const BColor & color) = 0;
	virtual void setColor3(const BVector3f & color) = 0;
	virtual void setColor4(const BVector4f & color) = 0;

	// masks
	virtual void setColorMask(bool r, bool g, bool b, bool a) = 0;
	virtual void setDepthMask(bool depth) = 0;

	// alpha
	virtual void setAlphaTest(float value) = 0;

	// depth
	virtual void enableDepthTest(void) = 0;
	virtual void disableDepthTest(void) = 0;
	virtual void setDepthMode(M_DEPTH_MODES mode) = 0;

	// stencil
	virtual void enableStencilTest(void) = 0;
	virtual void disableStencilTest(void) = 0;
	virtual void setStencilFunc(M_STENCIL_FUNCS func, int ref=0){};
	virtual void setStencilOp(M_STENCIL_OPS op){};

	// cull face
	virtual void enableCullFace(void) = 0;
	virtual void disableCullFace(void) = 0;
	virtual void setCullMode(U_CULL_MODES mode) = 0;

	// occlusion
	virtual void createQuery(unsigned int * queryId){}
	virtual void deleteQuery(unsigned int * queryId){}
	virtual void beginQuery(unsigned int queryId){}
	virtual void endQuery(void){}
	virtual void getQueryResult(unsigned int queryId, unsigned int * result){}

	// matrix
	virtual void loadIdentity(void) = 0;
	virtual void setMatrixMode(M_MATRIX_MODES mode) = 0;
	virtual void pushMatrix(void) = 0;
	virtual void popMatrix(void) = 0;
	virtual void multMatrix(const BMatrix4x4 * matrix) = 0;
	virtual void translate(const BVector3f & position) = 0;
	virtual void rotate(const BVector3f & axis, float angle) = 0;
	virtual void scale(const BVector3f & scale) = 0;
	virtual void getViewport(int * viewport) = 0;
	virtual void getModelViewMatrix(BMatrix4x4 * matrix) = 0;
	virtual void getProjectionMatrix(BMatrix4x4 * matrix) = 0;
	virtual void getTextureMatrix(BMatrix4x4 * matrix) = 0;

	// fog
	virtual void enableFog(void) = 0;
	virtual void disableFog(void) = 0;
	virtual void setFogColor(const BVector3f & color) = 0;
	virtual void setFogDistance(float min, float max) = 0;
	virtual void getFogColor(BVector3f * color) = 0;
	virtual void getFogDistance(float * min, float * max) = 0;

	// lighting
	virtual void enableLighting(void) = 0;
	virtual void disableLighting(void) = 0;
	virtual void enableLight(unsigned int id) = 0;
	virtual void disableLight(unsigned int id) = 0;
	virtual void setLightPosition(unsigned int id, const BVector4f & position) = 0;
	virtual void setLightDiffuse(unsigned int id, const BVector4f & diffuse) = 0;
	virtual void setLightSpecular(unsigned int id, const BVector4f & specular) = 0;
	virtual void setLightAmbient(unsigned int id, const BVector4f & ambient) = 0;
	virtual void setLightAttenuation(unsigned int id, float constant, float linear, float quadratic) = 0;
	virtual void setLightSpotDirection(unsigned int id, const BVector3f & direction) = 0;
	virtual void setLightSpotAngle(unsigned int id, float angle) = 0;
	virtual void setLightSpotExponent(unsigned int id, float exponent) = 0;
	virtual void getLightPosition(unsigned int id, BVector4f * position) = 0;
	virtual void getLightDiffuse(unsigned int id, BVector4f * diffuse) = 0;
	virtual void getLightSpecular(unsigned int id, BVector4f * specular) = 0;
	virtual void getLightAmbient(unsigned int id, BVector4f * ambient) = 0;
	virtual void getLightAttenuation(unsigned int id, float * constant, float * linear, float * quadratic) = 0;
	virtual void getLightSpotDirection(unsigned int id, BVector3f * direction) = 0;
	virtual void getLightSpotAngle(unsigned int id, float * angle) = 0;
	virtual void getLightSpotExponent(unsigned int id, float * exponent) = 0;

	// blending
	virtual void enableBlending(void) = 0;
	virtual void disableBlending(void) = 0;
	virtual void setBlendingMode(M_BLENDING_MODES mode) = 0;
};

#endif
