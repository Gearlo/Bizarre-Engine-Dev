/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BMaterial.h
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


#ifndef _M_MATERIAL_H
#define _M_MATERIAL_H


// Texture Pass
class M_ENGINE_EXPORT BTexturePass
{
public:

	BTexturePass(BTexture * texture, M_TEX_COMBINE_MODES combineMode, unsigned int mapChannel):
		m_mapChannel(mapChannel),
		m_texture(texture),
		m_combineMode(combineMode)
		{}

	BTexturePass(const BTexturePass & texturePass):
		m_mapChannel(texturePass.m_mapChannel),
		m_texture(texturePass.m_texture),
		m_combineMode(texturePass.m_combineMode)
		{}

private:
	
	// texture
	unsigned int m_mapChannel;
	BTexture * m_texture;

	// combine mode
	M_TEX_COMBINE_MODES m_combineMode;

public:
	
	// texture
	inline void setMapChannel(unsigned int mapChannel){ m_mapChannel = mapChannel; }
	inline void setTexture(BTexture * texture){ m_texture = texture; }

	inline unsigned int getMapChannel(void){ return m_mapChannel; }
	inline BTexture * getTexture(void){ return m_texture; }

	// combine mode
	inline void setCombineMode(M_TEX_COMBINE_MODES combineMode){ m_combineMode = combineMode; }
	inline M_TEX_COMBINE_MODES getCombineMode(void){ return m_combineMode; }
};


// Material
class M_ENGINE_EXPORT BMaterial
{
public:

	BMaterial(void);
	BMaterial(const BMaterial & material);
	~BMaterial(void);

private:

	// type
	int m_type;
	
	// FX
	BFXRef * m_FXRef;
	BFXRef * m_ZFXRef;

	// blend mode
	M_BLENDING_MODES m_blendMode;

	// properties
	float m_opacity;
	float m_shininess;
	float m_customValue;
	BVector3f m_diffuse;
	BVector3f m_specular;
	BVector3f m_emit;
	BVector3f m_customColor;

	// textures pass
	unsigned int m_texturesPassNumber;
	BTexturePass ** m_texturesPass;

public:

	// type
	inline void setType(int type){ m_type = type; }
	inline int getType(void){ return m_type; }
	
	// FX
	inline void setFXRef(BFXRef * FXRef){ m_FXRef = FXRef; }
	inline void setZFXRef(BFXRef * ZFXRef){ m_ZFXRef = ZFXRef; }
	inline BFXRef * getFXRef(void){ return m_FXRef; }
	inline BFXRef * getZFXRef(void){ return m_ZFXRef; }

	// blend mode
	inline void setBlendMode(M_BLENDING_MODES blendMode){ m_blendMode = blendMode; }
	inline M_BLENDING_MODES getBlendMode(void){ return m_blendMode; }

	// properties
	inline void setOpacity(float opacity){ m_opacity = opacity; }
	inline void setShininess(float shininess){ m_shininess = shininess; }
	inline void setCustomValue(float customValue){ m_customValue = customValue; }
	inline void setDiffuse(const BVector3f & diffuse){ m_diffuse = diffuse; }
	inline void setSpecular(const BVector3f & specular){ m_specular = specular; }
	inline void setEmit(const BVector3f & emit){ m_emit = emit; }
	inline void setCustomColor(const BVector3f & customColor){ m_customColor = customColor; }
	
	inline float getOpacity(void){ return m_opacity; }
	inline float getShininess(void){ return m_shininess; }
	inline float getCustomValue(void){ return m_customValue; }
	inline BVector3f getEmit(void) const { return m_emit; }
	inline BVector3f getDiffuse(void) const { return m_diffuse; }
	inline BVector3f getSpecular(void) const { return m_specular; }
	inline BVector3f getCustomColor(void) const { return m_customColor; }

	// textures pass
	void allocTexturesPass(unsigned int size);
	void clearTexturesPass(void);
	void addTexturePass(BTexture * texture, M_TEX_COMBINE_MODES combineMode, unsigned int mapChannel);
	inline unsigned int getTexturesPassNumber(void){ return m_texturesPassNumber; }
	inline BTexturePass * getTexturePass(unsigned int id){ return m_texturesPass[id]; }
};

#endif