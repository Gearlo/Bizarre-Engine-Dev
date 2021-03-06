/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BOBone.cpp
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


BOBone::BOBone(void):
BObject3d()
{
}

BOBone::~BOBone(void)
{
	BObject3d::clearObject3d();
}

// copy constructor
BOBone::BOBone(const BOBone & bone): 
BObject3d(bone),
m_inversePoseMatrix(bone.m_inversePoseMatrix),
m_skinMatrix(bone.m_skinMatrix)
{}

void BOBone::processChildsLinking(void)
{
	unsigned int i;
	unsigned int size = getChildsNumber();

	BOBone * child = NULL;
	for(i=0; i<size; i++) // for all childs
	{
		child = (BOBone *)getChild(i);

		// compute parenting (parent matrix * child local matrix)
		child->computeLocalMatrix();
		(*child->getMatrix()) = (*getMatrix()) * (*child->getMatrix());
		child->processChildsLinking();
	}
}