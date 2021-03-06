/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BGLContext.cpp
//
// OpenGL-Glew Rendering Context
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

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
	#include <OpenGL/OpenGL.h>
    #include <OpenGL/gl.h>
#else
	#include <GLee.h>
#endif

#include <BGLContext.h>


static int g_GLversion = 0;
static float maxAnisotropy = 0.0f;


GLenum returnGLType(U_TYPES type)
{
	switch(type)
	{
	default:
		return GL_NONE;

	case M_BOOL:
		return GL_BOOL;

	case M_BYTE:
		return GL_BYTE;

	case M_UBYTE:
		return GL_UNSIGNED_BYTE;

	case U_SHORT:
		return GL_SHORT;

	case U_USHORT:
		return GL_UNSIGNED_SHORT;

	case U_INT:
		return GL_INT;

	case U_UINT:
		return GL_UNSIGNED_INT;

	case M_FLOAT:
		return GL_FLOAT;

	case M_DOUBLE:
		return GL_DOUBLE;
	}
}

GLenum returnPrimitiveType(U_PRIMITIVE_TYPES type)
{
	switch(type)
	{
	default:
		return GL_NONE;

	case U_PRIMITIVE_LINES:
		return GL_LINES;

	case U_PRIMITIVE_LINE_LOOP:
		return GL_LINE_LOOP;

	case U_PRIMITIVE_LINE_STRIP:
		return GL_LINE_STRIP;

	case U_PRIMITIVE_TRIANGLES:
		return GL_TRIANGLES;

	case U_PRIMITIVE_TRIANGLE_STRIP:
		return GL_TRIANGLE_STRIP;

	case U_PRIMITIVE_TRIANGLE_FAN:
		return GL_TRIANGLE_FAN;
	}
}

GLenum returnTexFilterMode(M_TEX_FILTER_MODES mode)
{
	switch(mode)
	{
	default:
	case M_TEX_FILTER_NEAREST:
		return GL_NEAREST;

	case M_TEX_FILTER_NEAREST_MIPMAP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;

	case M_TEX_FILTER_NEAREST_MIPMAP_LINEAR:
		return GL_NEAREST_MIPMAP_LINEAR;

	case M_TEX_FILTER_LINEAR:
		return GL_LINEAR;

	case M_TEX_FILTER_LINEAR_MIPMAP_NEAREST:
		return GL_LINEAR_MIPMAP_NEAREST;

	case M_TEX_FILTER_LINEAR_MIPMAP_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;
	}
}

GLenum returnTexMode(M_TEX_MODES mode)
{
	switch(mode)
	{
	case M_R:
		return GL_R;

	case M_RG:
		return GL_RG;

	default:
	case M_RGB:
		return GL_RGB;

	case M_RGBA:
		return GL_RGBA;

	case M_DEPTH:
		return GL_DEPTH_COMPONENT;
	}
}

GLenum returnAttachType(M_FRAME_BUFFER_ATTACHMENT type)
{
	if(type == M_ATTACH_DEPTH)
		return GL_DEPTH_ATTACHMENT_EXT;
	else if(type == M_ATTACH_STENCIL)
		return GL_STENCIL_ATTACHMENT_EXT;
	else
		return GL_COLOR_ATTACHMENT0_EXT + ((int)type - 2);
}

BGLContext::BGLContext(void):
m_currentFrameBuffer(0)
{
	// version
	const char * version = (const char *)glGetString(GL_VERSION);
	if(version)
	{
	    m_gl_version=version;
		sscanf(version, "%d", &g_GLversion);
	}

	// init cull face (back)
	enableCullFace();
	setCullMode(U_CULL_BACK);

	// normalize
	glEnable(GL_NORMALIZE);

	// fog
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_MODE, GL_LINEAR);

	// depth
	enableDepthTest();
	setDepthMode(M_DEPTH_LEQUAL);
	glClearDepth(1.0f);

	// line
	glLineWidth(1);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// point
	//glPointSize(2.0);
	//glEnable(GL_POINT_SMOOTH);

	//float coeffs[] = {1.0f, 0, 0};
	//glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, coeffs);

	//glPointParameterf (GL_POINT_SIZE_MAX, 100.0);
	//glPointParameterf (GL_POINT_SIZE_MIN, 1.0f);

	// stencil
	glClearStencil(0);

	// pixel pack/unpack
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	// anisotropic filtering
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
}

BGLContext::~BGLContext(void)
{}

// view
void BGLContext::setPerspectiveView(float fov, float ratio, float zNear, float zFar)
{
	BMatrix4x4 matrix;

	float ymax, xmax;
	ymax = zNear * tanf((float)(fov * M_PI / 360.0f));
	xmax = ymax * ratio;

	float left = -xmax;
	float right = xmax;
	float bottom = -ymax;
	float top = ymax;

	float temp, temp2, temp3, temp4;
	temp = 2.0f * zNear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zFar - zNear;
	matrix.entries[0] = temp / temp2;
	matrix.entries[1] = 0.0;
	matrix.entries[2] = 0.0;
	matrix.entries[3] = 0.0;
	matrix.entries[4] = 0.0;
	matrix.entries[5] = temp / temp3;
	matrix.entries[6] = 0.0;
	matrix.entries[7] = 0.0;
	matrix.entries[8] = (right + left) / temp2;
	matrix.entries[9] = (top + bottom) / temp3;
	matrix.entries[10] = (-zFar - zNear) / temp4;
	matrix.entries[11] = -1.0;
	matrix.entries[12] = 0.0;
	matrix.entries[13] = 0.0;
	matrix.entries[14] = (-temp * zFar) / temp4;
	matrix.entries[15] = 0.0;

	multMatrix(&matrix);
}

void BGLContext::setOrthoView(float left, float right, float bottom, float top, float zNear, float zFar){
	glOrtho(left, right, bottom, top, zNear, zFar);
}

// viewport
void BGLContext::setViewport(int x, int y, unsigned int width, unsigned int height){
	glViewport(x, y, width, height);
}

// clear
void BGLContext::clear(int buffer)
{
	switch(buffer)
	{
	case M_BUFFER_COLOR:
		glClear(GL_COLOR_BUFFER_BIT);
		return;

	case M_BUFFER_DEPTH:
		glClear(GL_DEPTH_BUFFER_BIT);
		return;

	case M_BUFFER_STENCIL:
		glClear(GL_STENCIL_BUFFER_BIT);
		return;

	case M_BUFFER_COLOR | M_BUFFER_DEPTH:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;

	case M_BUFFER_COLOR | M_BUFFER_STENCIL:
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		return;

	case M_BUFFER_COLOR | M_BUFFER_DEPTH | M_BUFFER_STENCIL:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		return;

	case M_BUFFER_DEPTH | M_BUFFER_STENCIL:
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		return;
	}
}

void BGLContext::setClearColor(const BVector4f & color){
	glClearColor(color.x, color.y, color.z, color.w);
}

// texture
void BGLContext::enableTexture(void)
{
	glEnable(GL_TEXTURE_2D);
}

void BGLContext::disableTexture(void)
{
	glDisable(GL_TEXTURE_2D);
}

void BGLContext::setTextureGenMode(M_TEX_GEN_MODES mode)
{
}

void BGLContext::setTextureFilterMode(M_TEX_FILTER_MODES min, M_TEX_FILTER_MODES mag)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, returnTexFilterMode(min));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, returnTexFilterMode(mag));
}

void BGLContext::setTextureUWrapMode(M_WRAP_MODES wrap)
{
	int glWrap = GL_REPEAT;
	if(wrap == M_WRAP_CLAMP)
		glWrap = GL_CLAMP_TO_EDGE;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
}

void BGLContext::setTextureVWrapMode(M_WRAP_MODES wrap)
{
	int glWrap = GL_REPEAT;
	if(wrap == M_WRAP_CLAMP)
		glWrap = GL_CLAMP_TO_EDGE;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);
}

void BGLContext::setTextureCombineMode(M_TEX_COMBINE_MODES combine)
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);

	switch(combine)
	{
	case M_TEX_COMBINE_REPLACE:
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_REPLACE);
		break;

	case M_TEX_COMBINE_MODULATE:
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
		break;

	case M_TEX_COMBINE_ADD:
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_ADD);
		break;

	case M_TEX_COMBINE_SUB:
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_SUBTRACT);
		break;
	}
}

void BGLContext::bindTexture(unsigned int textureId, unsigned int multitextureId)
{
	glActiveTexture(GL_TEXTURE0 + multitextureId);
	glClientActiveTexture(GL_TEXTURE0 + multitextureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void BGLContext::createTexture(unsigned int * textureId)
{
	glGenTextures(1, textureId);
}

void BGLContext::deleteTexture(unsigned int * textureId)
{
	glDeleteTextures(1, textureId);
}

void BGLContext::sendTextureImage(BImage * image, bool mipMap, bool filter, bool compress)
{
	// get properties
	unsigned int bytePerPix = image->getComponents();

	unsigned int width  = image->getWidth();
	unsigned int height = image->getHeight();

	int internalFormat = GL_RGB;
	int format = GL_RGB;

	if(compress)
	{
		if(bytePerPix == 4)
		{
			format = GL_RGBA;
			internalFormat = GL_COMPRESSED_RGBA_ARB;
		}
		else
		{
			internalFormat = GL_COMPRESSED_RGB_ARB;
		}
	}
	else
	{
		if(bytePerPix == 4)
		{
			format = GL_RGBA;
			internalFormat = GL_RGBA;
		}
	}

	int glType = GL_TEXTURE_2D;

	glEnable(glType);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	if(filter)
	{
		glTexParameteri(glType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if(mipMap)
			glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(glType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if(mipMap)
			glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		else
			glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	glTexImage2D(glType, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, image->getData());
	if(mipMap)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy); // anisotropic filtering
		glGenerateMipmapEXT(glType);
	}

	/*
	if(mipMap)
		gluBuild2DMipmaps(glType, bytePerPix, width, height, format, GL_UNSIGNED_BYTE, image->getData());
	else
		glTexImage2D(glType, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, image->getData());
	*/
}

void BGLContext::texImage(unsigned int level, unsigned int width, unsigned int height, U_TYPES type, M_TEX_MODES mode, const void * pixels)
{
	GLenum format = returnTexMode(mode);
	GLenum intFormat = format;
	//if(type == M_FLOAT && mode == M_RGB)
	//	intFormat = GL_RGB32F_ARB;

	glTexImage2D(GL_TEXTURE_2D, level, intFormat, width, height, 0, format, returnGLType(type), pixels);
	if(level > 0)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy); // anisotropic filtering
}

void BGLContext::texSubImage(unsigned int level, int xoffset, int yoffset, unsigned int width, unsigned int height, U_TYPES type, M_TEX_MODES mode, const void * pixels)
{
	GLenum format = returnTexMode(mode);
	glTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, format, returnGLType(type), pixels);
	if(level > 0)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy); // anisotropic filtering
}

void BGLContext::generateMipMap(void){
	glGenerateMipmapEXT(GL_TEXTURE_2D);
}

void BGLContext::getTexImage(unsigned int level, BImage * image)
{
	if(image)
	{
		int width, height;
		int r, g, b, a, depth, format;

		glGetTexLevelParameteriv(GL_TEXTURE_2D, level, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, level, GL_TEXTURE_HEIGHT, &height);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, level, GL_TEXTURE_RED_SIZE, &r);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, level, GL_TEXTURE_GREEN_SIZE, &g);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, level, GL_TEXTURE_BLUE_SIZE, &b);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, level, GL_TEXTURE_ALPHA_SIZE, &a);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, level, GL_TEXTURE_DEPTH_SIZE, &depth);

		unsigned int dpp = 0;
		if(b > 0)
		{
			if(a > 0)
			{
				format = GL_RGBA;
				dpp = 4;
			}
			else
			{
				format = GL_RGB;
				dpp = 3;
			}
		}
		else if(depth > 0)
		{
			format = GL_DEPTH_COMPONENT;
			dpp = 1;
		}

		if(dpp > 0)
		{
			image->create(M_UBYTE, width, height, dpp);
			glGetTexImage(GL_TEXTURE_2D, level, format, GL_UNSIGNED_BYTE, image->getData());
		}
	}
}

// frame buffer
void CHECK_FRAMEBUFFER_STATUS()
{
	GLenum status;
	status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

	switch(status){
		case GL_FRAMEBUFFER_COMPLETE:
            break;
          case GL_FRAMEBUFFER_UNSUPPORTED:
			printf("couldn't find a supported config\n");
			break;
          default:
            printf("error");
	}
}


void BGLContext::createFrameBuffer(unsigned int * frameBufferId){
	glGenFramebuffersEXT(1, frameBufferId);
}
void BGLContext::deleteFrameBuffer(unsigned int * frameBufferId){
	glDeleteFramebuffersEXT(1, frameBufferId);
}
void BGLContext::bindFrameBuffer(unsigned int frameBufferId){
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBufferId);
	m_currentFrameBuffer = frameBufferId;
}
void BGLContext::getCurrentFrameBuffer(unsigned int * frameBufferId){
	(*frameBufferId) = m_currentFrameBuffer;
}
void BGLContext::attachFrameBufferTexture(M_FRAME_BUFFER_ATTACHMENT attachment, unsigned int textureId){
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, returnAttachType(attachment), GL_TEXTURE_2D, textureId, 0);
}
void BGLContext::attachFrameBufferRB(M_FRAME_BUFFER_ATTACHMENT attachment, unsigned int renderBufferId){
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, returnAttachType(attachment), GL_RENDERBUFFER_EXT, renderBufferId);

	CHECK_FRAMEBUFFER_STATUS();
}
void BGLContext::setDrawingBuffers(M_FRAME_BUFFER_ATTACHMENT * buffers, unsigned int size)
{
	if(size == 0)
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	else
	{
		static GLenum glBuffers[8];

		size = MIN(8, size);
		for(unsigned int i=0; i<size; i++)
			glBuffers[i] = returnAttachType(buffers[i]);

		glDrawBuffers(size, glBuffers);

		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);
	}
}

// render buffer
void BGLContext::createRenderBuffer(unsigned int * renderBufferId){
	glGenRenderbuffersEXT(1, renderBufferId);
}

void BGLContext::deleteRenderBuffer(unsigned int * renderBufferId){
	glDeleteRenderbuffersEXT(1, renderBufferId);
}

void BGLContext::bindRenderBuffer(unsigned int renderBufferId){
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderBufferId);
}

void BGLContext::setRenderBuffer(M_RENDER_BUFFER_MODES mode, unsigned int width, unsigned int height)
{
	GLenum internalMode;

	switch(mode)
	{
		default:
			return;
		case M_RENDER_DEPTH:
			internalMode = GL_DEPTH_COMPONENT;
			break;
		case M_RENDER_STENCIL:
			internalMode = GL_STENCIL_INDEX;
			break;
		case M_RENDER_DEPTH_STENCIL:
			internalMode = GL_DEPTH_STENCIL_EXT;
			break;
	}

	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_STENCIL_EXT, width, height);
}

// shaders
void BGLContext::createVertexShader(unsigned int * shaderId){
	*shaderId = (unsigned int)(unsigned long)glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
}

void BGLContext::createPixelShader(unsigned int * shaderId){
	*shaderId = (unsigned int)(unsigned long)glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
}

void BGLContext::deleteShader(unsigned int * shaderId){
	glDeleteObjectARB((GLhandleARB)(*shaderId));
}

void BGLContext::sendShaderSource(unsigned int shaderId, const char * source)
{
	glShaderSourceARB((GLhandleARB)shaderId, 1, &source, NULL);
	glCompileShaderARB((GLhandleARB)shaderId);

	GLint compiled;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		printf("ERROR OpenGL : unable to compile shader\n");
		char shader_link_error[4096];
        glGetInfoLogARB((GLhandleARB)shaderId, sizeof(shader_link_error), NULL, shader_link_error);
		printf("%s", shader_link_error);
	}
}

// FX
void BGLContext::bindFX(unsigned int fxId){
	glUseProgramObjectARB((GLhandleARB)fxId);
}

void BGLContext::createFX(unsigned int * fxId, unsigned int vertexShaderId, unsigned int pixelShaderId)
{
	*fxId = (unsigned int)(unsigned long)glCreateProgramObjectARB();
	glAttachObjectARB((GLhandleARB)*fxId, (GLhandleARB)vertexShaderId);
	glAttachObjectARB((GLhandleARB)*fxId, (GLhandleARB)pixelShaderId);
	glLinkProgramARB((GLhandleARB)*fxId);
}

void BGLContext::updateFX(unsigned int fxId)
{
	glLinkProgramARB((GLhandleARB)fxId);
}

void BGLContext::deleteFX(unsigned int * fxId){
	glDeleteObjectARB((GLhandleARB)(*fxId));
}

void BGLContext::sendUniformInt(unsigned int fxId, const char * name, int * values, const int count){
	GLint uValue = glGetUniformLocationARB((GLhandleARB)fxId, name);
	if(uValue != -1) glUniform1ivARB(uValue, count, values);
}

void BGLContext::sendUniformFloat(unsigned int fxId, const char * name, float * values, const int count){
	GLint uValue = glGetUniformLocationARB((GLhandleARB)fxId, name);
	if(uValue != -1) glUniform1fvARB(uValue, count, values);
}

void BGLContext::sendUniformVec2(unsigned int fxId, const char * name, float * values, const int count){
	GLint uValue = glGetUniformLocationARB((GLhandleARB)fxId, name);
	if(uValue != -1) glUniform2fvARB(uValue, count, values);
}

void BGLContext::sendUniformVec3(unsigned int fxId, const char * name, float * values, const int count){
	GLint uValue = glGetUniformLocationARB((GLhandleARB)fxId, name);
	if(uValue != -1) glUniform3fvARB(uValue, count, values);
}

void BGLContext::sendUniformVec4(unsigned int fxId, const char * name, float * values, const int count){
	GLint uValue = glGetUniformLocationARB((GLhandleARB)fxId, name);
	if(uValue != -1) glUniform4fvARB(uValue, count, values);
}

void BGLContext::sendUniformMatrix(unsigned int fxId, const char * name, BMatrix4x4 * matrix, const int count, const bool transpose){
	GLint uValue = glGetUniformLocationARB((GLhandleARB)fxId, name);
	if(uValue != -1) glUniformMatrix4fvARB(uValue, count, transpose, matrix->entries);
}

void BGLContext::getAttribLocation(unsigned int fxId, const char * name, int * location)
{
	(*location) = glGetAttribLocationARB((GLhandleARB)fxId, name);
}

// VBO
void BGLContext::createVBO(unsigned int * vboId){
	glGenBuffersARB(1, vboId);
}
void BGLContext::deleteVBO(unsigned int * vboId){
	glDeleteBuffersARB(1, vboId);
}
void BGLContext::bindVBO(M_VBO_TYPES type, unsigned int vboId)
{
	GLenum gltype = type == M_VBO_ARRAY ? GL_ARRAY_BUFFER_ARB : GL_ELEMENT_ARRAY_BUFFER_ARB;
	glBindBufferARB(gltype, vboId);
}
void BGLContext::setVBO(M_VBO_TYPES type, const void * data, unsigned int size, M_VBO_MODES mode)
{
	GLenum gltype = type == M_VBO_ARRAY ? GL_ARRAY_BUFFER_ARB : GL_ELEMENT_ARRAY_BUFFER_ARB;
	switch(mode)
	{
		case M_VBO_STATIC:
			glBufferDataARB(gltype, size, data, GL_STATIC_DRAW_ARB);
			break;
		case M_VBO_DYNAMIC:
			glBufferDataARB(gltype, size, data, GL_DYNAMIC_DRAW_ARB);
			break;
		case M_VBO_STREAM:
			glBufferDataARB(gltype, size, data, GL_STREAM_DRAW_ARB);
			break;
	}
}
void BGLContext::setVBOSubData(M_VBO_TYPES type, unsigned int offset, const void * data, unsigned int size)
{
	GLenum gltype = type == M_VBO_ARRAY ? GL_ARRAY_BUFFER_ARB : GL_ELEMENT_ARRAY_BUFFER_ARB;
	glBufferSubDataARB(gltype, offset, size, data);
}

// arrays
void BGLContext::enableVertexArray(void){
	glEnableClientState(GL_VERTEX_ARRAY);
}

void BGLContext::enableColorArray(void){
	glEnableClientState(GL_COLOR_ARRAY);
}

void BGLContext::enableNormalArray(void){
	glEnableClientState(GL_NORMAL_ARRAY);
}

void BGLContext::enableTexCoordArray(void){
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void BGLContext::enableAttribArray(unsigned int location)
{
	glEnableVertexAttribArray(location);
}

void BGLContext::disableVertexArray(void){
	glDisableClientState(GL_VERTEX_ARRAY);
}

void BGLContext::disableColorArray(void){
	glDisableClientState(GL_COLOR_ARRAY);
}

void BGLContext::disableNormalArray(void){
	glDisableClientState(GL_NORMAL_ARRAY);
}

void BGLContext::disableTexCoordArray(void){
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void BGLContext::disableAttribArray(unsigned int location)
{
	glDisableVertexAttribArray(location);
}

void BGLContext::setVertexPointer(U_TYPES type, unsigned int components, const void * pointer){
	glVertexPointer(components, returnGLType(type), 0, pointer);
}

void BGLContext::setColorPointer(U_TYPES type, unsigned int components, const void * pointer){
	glColorPointer(components, returnGLType(type), 0, pointer);
}

void BGLContext::setNormalPointer(U_TYPES type, const void * pointer){
	glNormalPointer(returnGLType(type), 0, pointer);
}

void BGLContext::setTexCoordPointer(U_TYPES type, unsigned int components, const void * pointer){
	glTexCoordPointer(components, returnGLType(type), 0, pointer);
}

void BGLContext::setAttribPointer(unsigned int location, U_TYPES type, unsigned int components, const void * pointer, const bool normalized)
{
	glVertexAttribPointer(location, components, returnGLType(type), normalized, 0, pointer);
}

// draw
void BGLContext::drawArray(U_PRIMITIVE_TYPES type, unsigned int begin, unsigned int size)
{
	glDrawArrays(returnPrimitiveType(type), begin, size);
}

void BGLContext::drawElement(U_PRIMITIVE_TYPES type, unsigned int size, U_TYPES indicesType, const void * indices)
{
	glDrawElements(returnPrimitiveType(type), size, returnGLType(indicesType), indices);
}

// lines
void BGLContext::enableLineAntialiasing(void)	{ glEnable(GL_LINE_SMOOTH); }
void BGLContext::disableLineAntialiasing(void)	{ glDisable(GL_LINE_SMOOTH); }

// material
void BGLContext::setMaterialDiffuse(const BVector4f & diffuse){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
}
void BGLContext::setMaterialSpecular(const BVector4f & specular){
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
}
void BGLContext::setMaterialAmbient(const BVector4f & ambient){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
}
void BGLContext::setMaterialEmit(const BVector4f & emit){
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
}
void BGLContext::setMaterialShininess(float shininess){
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

// scissor
void BGLContext::enableScissorTest(void) { glEnable(GL_SCISSOR_TEST); }
void BGLContext::disableScissorTest(void){ glDisable(GL_SCISSOR_TEST); }
void BGLContext::setScissor(int x, int y, unsigned int width, unsigned int height){
	glScissor(x, y, width, height);
}

// color
void BGLContext::setColor(const BColor & color){
	glColor4ub(color.r, color.g, color.b, color.a);
}

void BGLContext::setColor4(const BVector4f & color){
	glColor4f(color.x, color.y, color.z, color.w);
}
void BGLContext::setColor3(const BVector3f & color){
	glColor4f(color.x, color.y, color.z, 1.0f);
}

// masks
void BGLContext::setColorMask(bool r, bool g, bool b, bool a){
	glColorMask(r, g, b, a);
}
void BGLContext::setDepthMask(bool depth){
	glDepthMask(depth);
}

void BGLContext::setAlphaTest(float value)
{
	if(value > 0.0f)
		glEnable(GL_ALPHA_TEST);
	else {
		glDisable(GL_ALPHA_TEST);
	}

	glAlphaFunc(GL_GREATER, value);
}

// depth
void BGLContext::enableDepthTest(void) { glEnable (GL_DEPTH_TEST); }
void BGLContext::disableDepthTest(void){ glDisable(GL_DEPTH_TEST); }
void BGLContext::setDepthMode(M_DEPTH_MODES mode)
{
	switch(mode)
	{
	case M_DEPTH_ALWAYS:
		glDepthFunc(GL_ALWAYS);
		return;

	case M_DEPTH_LESS:
		glDepthFunc(GL_LESS);
		return;

	case M_DEPTH_GREATER:
		glDepthFunc(GL_GREATER);
		return;

	case M_DEPTH_EQUAL:
		glDepthFunc(GL_EQUAL);
		return;

	case M_DEPTH_LEQUAL:
		glDepthFunc(GL_LEQUAL);
		return;

	case M_DEPTH_GEQUAL:
		glDepthFunc(GL_GEQUAL);
		return;

	case M_DEPTH_NOTEQUAL:
		glDepthFunc(GL_NOTEQUAL);
		return;
	}
}

// stencil
void BGLContext::enableStencilTest(void) { glEnable (GL_STENCIL_TEST); }
void BGLContext::disableStencilTest(void){ glDisable(GL_STENCIL_TEST); }
void BGLContext::setStencilFunc(M_STENCIL_FUNCS func, int ref)
{
	switch(func)
	{
		default:
		case M_STENCIL_ALWAYS:
			glStencilFunc(GL_ALWAYS, ref, ~0);
			break;
		case M_STENCIL_EQUAL:
			glStencilFunc(GL_EQUAL, ref, ~0);
			break;
		case M_STENCIL_NOTEQUAL:
			glStencilFunc(GL_NOTEQUAL, ref, ~0);
			break;
		case M_STENCIL_NEVER:
			glStencilFunc(GL_NEVER, ref, ~0);
			break;
		case M_STENCIL_LESS:
			glStencilFunc(GL_LESS, ref, ~0);
			break;
		case M_STENCIL_LEQUAL:
			glStencilFunc(GL_LEQUAL, ref, ~0);
			break;
		case M_STENCIL_GREATER:
			glStencilFunc(GL_GREATER, ref, ~0);
			break;
		case M_STENCIL_GEQUAL:
			glStencilFunc(GL_GEQUAL, ref, ~0);
			break;
	}
}
void BGLContext::setStencilOp(M_STENCIL_OPS op)
{
	switch(op)
	{
		default:
		case M_STENCIL_KEEP:
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
			break;
		case M_STENCIL_INVERT:
			glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);
			break;
		case M_STENCIL_DECR:
			glStencilOp(GL_KEEP, GL_DECR, GL_DECR);
			break;
		case M_STENCIL_INCR:
			glStencilOp(GL_KEEP, GL_INCR, GL_INCR);
			break;
		case M_STENCIL_REPLACE:
			glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
			break;
	}
}

// cull face
void BGLContext::enableCullFace(void) { glEnable (GL_CULL_FACE); }
void BGLContext::disableCullFace(void){ glDisable(GL_CULL_FACE); }
void BGLContext::setCullMode(U_CULL_MODES mode)
{
	switch(mode)
	{
	case U_CULL_FRONT:
		glCullFace(GL_FRONT);
		return;

	case U_CULL_BACK:
		glCullFace(GL_BACK);
		return;

	case U_CULL_FRONT_BACK:
		glCullFace(GL_FRONT_AND_BACK);
		return;
	}
}

// occlusion
void BGLContext::createQuery(unsigned int * queryId){
	glGenQueriesARB(1, queryId);
}
void BGLContext::deleteQuery(unsigned int * queryId){
	glDeleteQueriesARB(1, queryId);
}
void BGLContext::beginQuery(unsigned int queryId){
	glBeginQueryARB(GL_SAMPLES_PASSED_ARB, queryId);
}
void BGLContext::endQuery(void){
	glEndQueryARB(GL_SAMPLES_PASSED_ARB);
}
void BGLContext::getQueryResult(unsigned int queryId, unsigned int * result){
	glGetQueryObjectuivARB(queryId, GL_QUERY_RESULT_ARB, result);
}

// matrix
void BGLContext::loadIdentity(void){
	glLoadIdentity();
}

void BGLContext::setMatrixMode(M_MATRIX_MODES matrixMode)
{
	switch(matrixMode)
	{
	case M_MATRIX_MODELVIEW:
		glMatrixMode(GL_MODELVIEW);
		return;

	case M_MATRIX_PROJECTION:
		glMatrixMode(GL_PROJECTION);
		return;

	case M_MATRIX_TEXTURE:
		glMatrixMode(GL_TEXTURE);
		return;
	}
}

void BGLContext::pushMatrix(void)									{ glPushMatrix(); }
void BGLContext::popMatrix(void)									{ glPopMatrix(); }
void BGLContext::multMatrix(const BMatrix4x4 * matrix)				{ glMultMatrixf(matrix->entries); }
void BGLContext::translate(const BVector3f & position)				{ glTranslatef(position.x, position.y, position.z); }
void BGLContext::rotate(const BVector3f & axis, float angle)			{ glRotatef(angle, axis.x, axis.y, axis.z); }
void BGLContext::scale(const BVector3f & scale)						{ glScalef(scale.x, scale.y, scale.z); }
void BGLContext::getViewport(int * viewport)
{
	glGetIntegerv(GL_VIEWPORT, viewport);
}
void BGLContext::getModelViewMatrix(BMatrix4x4 * matrix)
{
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix->entries);
}
void BGLContext::getProjectionMatrix(BMatrix4x4 * matrix)
{
	glGetFloatv(GL_PROJECTION_MATRIX, matrix->entries);
}
void BGLContext::getTextureMatrix(BMatrix4x4 * matrix)
{
	glGetFloatv(GL_TEXTURE_MATRIX, matrix->entries);
}

// fog
void BGLContext::enableFog(void)						{ glEnable (GL_FOG); }
void BGLContext::disableFog(void)						{ glDisable(GL_FOG); }
void BGLContext::setFogColor(const BVector3f & color)
{
	glFogfv(GL_FOG_COLOR, BVector4f(color));
	m_fogColor = color;
}
void BGLContext::setFogDistance(float min, float max)
{
	glFogf(GL_FOG_START, min);
	glFogf(GL_FOG_END,   max);
	m_fogMin = min;
	m_fogMax = max;
}
void BGLContext::getFogColor(BVector3f * color){
	(*color) = m_fogColor;
}
void BGLContext::getFogDistance(float * min, float * max){
	(*min) = m_fogMin;
	(*max) = m_fogMax;
}

// lighting
void BGLContext::enableLighting(void)			{ glEnable (GL_LIGHTING); }
void BGLContext::disableLighting(void)			{ glDisable(GL_LIGHTING); }
void BGLContext::enableLight(unsigned int id)	{ glEnable (GL_LIGHT0 + id); }
void BGLContext::disableLight(unsigned int id)	{ glDisable(GL_LIGHT0 + id); }
void BGLContext::setLightPosition(unsigned int id, const BVector4f & position)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].position = position;
		glLightfv(GL_LIGHT0 + id, GL_POSITION, position);
	}
}
void BGLContext::setLightDiffuse(unsigned int id, const BVector4f & diffuse)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].diffuse = diffuse;
		glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, diffuse);
	}
}
void BGLContext::setLightSpecular(unsigned int id, const BVector4f & specular)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].specular = specular;
		glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular);
	}
}
void BGLContext::setLightAmbient(unsigned int id, const BVector4f & ambient)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].ambient = ambient;
		glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient);
	}
}
void BGLContext::setLightAttenuation(unsigned int id, float constant, float linear, float quadratic)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].constant = constant;
		m_lights[id].linear = linear;
		m_lights[id].quadratic = quadratic;
		glLightf(GL_LIGHT0 + id, GL_CONSTANT_ATTENUATION, constant);
		glLightf(GL_LIGHT0 + id, GL_LINEAR_ATTENUATION, linear);
		glLightf(GL_LIGHT0 + id, GL_QUADRATIC_ATTENUATION, quadratic);
	}
}
void BGLContext::setLightSpotDirection(unsigned int id, const BVector3f & direction)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].direction = direction;
		glLightfv(GL_LIGHT0 + id, GL_SPOT_DIRECTION, direction);
	}
}
void BGLContext::setLightSpotAngle(unsigned int id, float angle)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].angle = angle;
		glLightf(GL_LIGHT0 + id, GL_SPOT_CUTOFF, angle);
	}
}
void BGLContext::setLightSpotExponent(unsigned int id, float exponent)
{
	if(id < MAX_MRCLIGHTS)
	{
		m_lights[id].exponent = exponent*128.0f;
		glLightf(GL_LIGHT0 + id, GL_SPOT_EXPONENT, m_lights[id].exponent);
	}
}
void BGLContext::getLightPosition(unsigned int id, BVector4f * position)
{
	if(id < MAX_MRCLIGHTS)
		(*position) = m_lights[id].position;
}
void BGLContext::getLightDiffuse(unsigned int id, BVector4f * diffuse)
{
	if(id < MAX_MRCLIGHTS)
		(*diffuse) = m_lights[id].diffuse;
}
void BGLContext::getLightSpecular(unsigned int id, BVector4f * specular)
{
	if(id < MAX_MRCLIGHTS)
		(*specular) = m_lights[id].specular;
}
void BGLContext::getLightAmbient(unsigned int id, BVector4f * ambient)
{
	if(id < MAX_MRCLIGHTS)
		(*ambient) = m_lights[id].ambient;
}
void BGLContext::getLightAttenuation(unsigned int id, float * constant, float * linear, float * quadratic)
{
	if(id < MAX_MRCLIGHTS)
	{
		(*constant) = m_lights[id].constant;
		(*linear) = m_lights[id].linear;
		(*quadratic) = m_lights[id].quadratic;
	}
}
void BGLContext::getLightSpotDirection(unsigned int id, BVector3f * direction)
{
	if(id < MAX_MRCLIGHTS)
		(*direction) = m_lights[id].direction;
}
void BGLContext::getLightSpotAngle(unsigned int id, float * angle)
{
	if(id < MAX_MRCLIGHTS)
		(*angle) = m_lights[id].angle;
}
void BGLContext::getLightSpotExponent(unsigned int id, float * exponent)
{
	if(id < MAX_MRCLIGHTS)
		(*exponent) = m_lights[id].exponent;
}

// blending
void BGLContext::enableBlending(void)	{ glEnable (GL_BLEND); }
void BGLContext::disableBlending(void)	{ glDisable(GL_BLEND); }
void BGLContext::setBlendingMode(M_BLENDING_MODES mode)
{
	switch(mode)
	{
	case M_BLENDING_NONE:
		glBlendFunc(GL_ONE, GL_ZERO);
		break;
	case M_BLENDING_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case M_BLENDING_ADD:
		glBlendFunc(GL_ONE, GL_ONE);
		break;
	case M_BLENDING_PRODUCT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		break;
	case M_BLENDING_LIGHT:
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
		break;
	}
}
