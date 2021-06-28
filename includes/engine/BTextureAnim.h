/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BTextureAnim.h
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


#ifndef _M_TEXTURE_ANIM
#define _M_TEXTURE_ANIM


class M_ENGINE_EXPORT BTextureAnim
{
public:

	BTextureAnim(void);
	~BTextureAnim(void);

private:

	unsigned int m_translateKeysNumber;
	unsigned int m_scaleKeysNumber;
	unsigned int m_rotationKeysNumber;

	BKey * m_translateKeys;
	BKey * m_scaleKeys;
	BKey * m_rotationKeys;

public:

	BKey * allocTranslateKeys(unsigned int size);
	BKey * allocScaleKeys(unsigned int size);
	BKey * allocRotationKeys(unsigned int size);

	void clearTranslateKeys(void);
	void clearScaleKeys(void);
	void clearRotationKeys(void);

	inline unsigned int getTranslateKeysNumber(void){ return m_translateKeysNumber; }
	inline unsigned int getScaleKeysNumber(void){ return m_scaleKeysNumber; }
	inline unsigned int getRotationKeysNumber(void){ return m_rotationKeysNumber; }

	inline BKey * getTranslateKeys(void){ return m_translateKeys; }
	inline BKey * getScaleKeys(void){ return m_scaleKeys; }
	inline BKey * getRotationKeys(void){ return m_rotationKeys; }
};

#endif