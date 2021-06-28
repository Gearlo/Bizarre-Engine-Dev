/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BTextureAnim.cpp
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


BTextureAnim::BTextureAnim(void):
m_translateKeysNumber(0),
m_scaleKeysNumber(0),
m_rotationKeysNumber(0),
m_translateKeys(NULL),
m_scaleKeys(NULL),
m_rotationKeys(NULL)
{}

BTextureAnim::~BTextureAnim(void)
{
	clearTranslateKeys();
	clearScaleKeys();
	clearRotationKeys();
}

BKey * BTextureAnim::allocTranslateKeys(unsigned int size)
{
	clearTranslateKeys();
	if(size == 0)
		return NULL;

	m_translateKeysNumber = size;
	m_translateKeys = new BKey[size];
	return m_translateKeys;
}

BKey * BTextureAnim::allocScaleKeys(unsigned int size)
{
	clearScaleKeys();
	if(size == 0)
		return NULL;

	m_scaleKeysNumber = size;
	m_scaleKeys = new BKey[size];
	return m_scaleKeys;
}

BKey * BTextureAnim::allocRotationKeys(unsigned int size)
{
	clearRotationKeys();
	if(size == 0)
		return NULL;

	m_rotationKeysNumber = size;
	m_rotationKeys = new BKey[size];
	return m_rotationKeys;
}

void BTextureAnim::clearTranslateKeys(void)
{
	SAFE_DELETE_ARRAY(m_translateKeys);
	m_translateKeysNumber = 0;
}

void BTextureAnim::clearScaleKeys(void)
{
	SAFE_DELETE_ARRAY(m_scaleKeys);
	m_scaleKeysNumber = 0;
}

void BTextureAnim::clearRotationKeys(void)
{
	SAFE_DELETE_ARRAY(m_rotationKeys);
	m_rotationKeysNumber = 0;
}