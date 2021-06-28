/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BKey.cpp
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


BKey::BKey(void):
m_t(0),
m_data(NULL)
{}

BKey::~BKey(void)
{
	SAFE_FREE(m_data);
}

float * BKey::createFloatData(void)
{
	SAFE_FREE(m_data);
	float * value = new float;
	m_data = value;
	return value;
}

BVector2f * BKey::createVector2Data(void)
{
	SAFE_FREE(m_data);
	BVector2f * vec2 = new BVector2f();
	m_data = vec2;
	return vec2;
}

BVector3f * BKey::createVector3Data(void)
{
	SAFE_FREE(m_data);
	BVector3f * vec3 = new BVector3f();
	m_data = vec3;
	return vec3;
}

BVector4f * BKey::createVector4Data(void)
{
	SAFE_FREE(m_data);
	BVector4f * vec4 = new BVector4f();
	m_data = vec4;
	return vec4;
}

BQuaternion * BKey::createQuaternionData(void)
{
	SAFE_FREE(m_data);
	BQuaternion * quat = new BQuaternion();
	m_data = quat;
	return quat;
}
