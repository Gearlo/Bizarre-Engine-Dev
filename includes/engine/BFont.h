/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BFont.h
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


#ifndef _M_FONT_H
#define _M_FONT_H


// Character
class M_ENGINE_EXPORT BCharacter
{
public:

	BCharacter(void);
	BCharacter(float xAdvance, const BVector2f & offset, const BVector2f & pos, const BVector2f & scale):
		m_xAdvance(xAdvance),
		m_offset(offset),
		m_pos(pos),
		m_scale(scale)
	{}

private:

	float m_xAdvance;
	BVector2f m_offset;
	BVector2f m_pos;
	BVector2f m_scale;
	
public:

	inline float getXAdvance(void){ return m_xAdvance; }
	inline BVector2f getOffset(void) const { return m_offset; }
	inline BVector2f getPos(void) const { return m_pos; }
	inline BVector2f getScale(void) const { return m_scale; }
};


// Font
class M_ENGINE_EXPORT BFont
{
public:

	BFont(void);
	~BFont(void);

	static BFont * getNew(void);
	void destroy(void);

private:

	unsigned int m_textureId;
	unsigned int m_textureWidth;
	unsigned int m_textureHeight;
	unsigned int m_fontSize;

	map <unsigned int, BCharacter> m_characters;

public:

	// texture
	inline void setTextureId(unsigned int textureId){ m_textureId = textureId; }
	inline void setTextureWidth(unsigned int width){ m_textureWidth = width; }
	inline void setTextureHeight(unsigned int height){ m_textureHeight = height; }
	inline unsigned int getTextureId(void){ return m_textureId; }
	inline unsigned int getTextureWith(void){ return m_textureWidth; }
	inline unsigned int getTextureHeight(void){ return m_textureHeight; }

	// font size
	inline void setFontSize(unsigned int fontSize){ m_fontSize = fontSize; }
	inline unsigned int getFontSize(void){ return m_fontSize; }

	// character
	void setCharacter(unsigned int charCode, const BCharacter & character);
	unsigned int getCharactersNumber(void);
	BCharacter * getCharacter(unsigned int charCode);
	BCharacter * getCharacterByIndex(unsigned int id);
	inline map <unsigned int, BCharacter> * getCharacters(void){ return &m_characters; }
};

#endif