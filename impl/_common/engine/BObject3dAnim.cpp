/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BObject3dAnim.cpp
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


BObject3dAnim::BObject3dAnim(void):
m_positionKeysNumber(0),
m_scaleKeysNumber(0),
m_rotationKeysNumber(0),
m_positionKeys(NULL),
m_scaleKeys(NULL),
m_rotationKeys(NULL)
{}

BObject3dAnim::~BObject3dAnim(void)
{
	clearPositionKeys();
	clearScaleKeys();
	clearRotationKeys();
}

BKey * BObject3dAnim::allocPositionKeys(unsigned int size)
{
	clearPositionKeys();
	if(size == 0)
		return NULL;

	m_positionKeysNumber = size;
	m_positionKeys = new BKey[size];
	return m_positionKeys;
}

BKey * BObject3dAnim::allocScaleKeys(unsigned int size)
{
	clearScaleKeys();
	if(size == 0)
		return NULL;

	m_scaleKeysNumber = size;
	m_scaleKeys = new BKey[size];
	return m_scaleKeys;
}

BKey * BObject3dAnim::allocRotationKeys(unsigned int size)
{
	clearRotationKeys();
	if(size == 0)
		return NULL;

	m_rotationKeysNumber = size;
	m_rotationKeys = new BKey[size];
	return m_rotationKeys;
}

void BObject3dAnim::clearPositionKeys(void)
{
	SAFE_DELETE_ARRAY(m_positionKeys);
	m_positionKeysNumber = 0;
}

void BObject3dAnim::clearScaleKeys(void)
{
	SAFE_DELETE_ARRAY(m_scaleKeys);
	m_scaleKeysNumber = 0;
}

void BObject3dAnim::clearRotationKeys(void)
{
	SAFE_DELETE_ARRAY(m_rotationKeys);
	m_rotationKeysNumber = 0;
}