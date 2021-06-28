/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BMaterialAnim.h
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


#ifndef _M_MATERIAL_ANIM
#define _M_MATERIAL_ANIM


class M_ENGINE_EXPORT BMaterialAnim
{
public:

	BMaterialAnim(void);
	~BMaterialAnim(void);

private:

	unsigned int m_opacityKeysNumber;
	unsigned int m_shininessKeysNumber;
	unsigned int m_customValueKeysNumber;
	unsigned int m_diffuseKeysNumber;
	unsigned int m_specularKeysNumber;
	unsigned int m_emitKeysNumber;
	unsigned int m_customColorKeysNumber;

	BKey * m_opacityKeys;
	BKey * m_shininessKeys;
	BKey * m_customValueKeys;
	BKey * m_diffuseKeys;
	BKey * m_specularKeys;
	BKey * m_emitKeys;
	BKey * m_customColorKeys;

public:

	BKey * allocOpacityKeys(unsigned int size);
	BKey * allocShininessKeys(unsigned int size);
	BKey * allocCustomValueKeys(unsigned int size);
	BKey * allocDiffuseKeys(unsigned int size);
	BKey * allocSpecularKeys(unsigned int size);
	BKey * allocEmitKeys(unsigned int size);
	BKey * allocCustomColorKeys(unsigned int size);

	void clearOpacityKeys(void);
	void clearShininessKeys(void);
	void clearCustomValueKeys(void);
	void clearDiffuseKeys(void);
	void clearSpecularKeys(void);
	void clearEmitKeys(void);
	void clearCustomColorKeys(void);

	inline unsigned int getOpacityKeysNumber(void){ return m_opacityKeysNumber; }
	inline unsigned int getShininessKeysNumber(void){ return m_shininessKeysNumber; }
	inline unsigned int getCustomValueKeysNumber(void){ return m_customValueKeysNumber; }
	inline unsigned int getDiffuseKeysNumber(void){ return m_diffuseKeysNumber; }
	inline unsigned int getSpecularKeysNumber(void){ return m_specularKeysNumber; }
	inline unsigned int getEmitKeysNumber(void){ return m_emitKeysNumber; }
	inline unsigned int getCustomColorKeysNumber(void){ return m_customColorKeysNumber; }

	inline BKey * getOpacityKeys(void){ return m_opacityKeys; }
	inline BKey * getShininessKeys(void){ return m_shininessKeys; }
	inline BKey * getCustomValueKeys(void){ return m_customValueKeys; }
	inline BKey * getDiffuseKeys(void){ return m_diffuseKeys; }
	inline BKey * getSpecularKeys(void){ return m_specularKeys; }
	inline BKey * getEmitKeys(void){ return m_emitKeys; }
	inline BKey * getCustomColorKeys(void){ return m_customColorKeys; }
};

#endif