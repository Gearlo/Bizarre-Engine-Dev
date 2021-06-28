/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BObject3dAnim.h
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


#ifndef _B_OBJECT3D_ANIM
#define _B_OBJECT3D_ANIM


class M_ENGINE_EXPORT BObject3dAnim
{
public:

	BObject3dAnim(void);
	~BObject3dAnim(void);

private:

	unsigned int m_positionKeysNumber;
	unsigned int m_scaleKeysNumber;
	unsigned int m_rotationKeysNumber;

	BKey * m_positionKeys;
	BKey * m_scaleKeys;
	BKey * m_rotationKeys;

public:

	BKey * allocPositionKeys(unsigned int size);
	BKey * allocScaleKeys(unsigned int size);
	BKey * allocRotationKeys(unsigned int size);

	void clearPositionKeys(void);
	void clearScaleKeys(void);
	void clearRotationKeys(void);

	inline unsigned int getPositionKeysNumber(void){ return m_positionKeysNumber; }
	inline unsigned int getScaleKeysNumber(void){ return m_scaleKeysNumber; }
	inline unsigned int getRotationKeysNumber(void){ return m_rotationKeysNumber; }

	inline BKey * getPositionKeys(void){ return m_positionKeys; }
	inline BKey * getScaleKeys(void){ return m_scaleKeys; }
	inline BKey * getRotationKeys(void){ return m_rotationKeys; }
};

#endif