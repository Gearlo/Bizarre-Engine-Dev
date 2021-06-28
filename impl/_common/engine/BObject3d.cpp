/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BObject3d.cpp
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


// constructor
BObject3d::BObject3d(void):
	m_parent(NULL),
	m_scale(1, 1, 1),
	m_isVisible(true),
	m_isActive(true),
	m_needToUpdate(true)
{}

// destructor
BObject3d::~BObject3d(void)
{
	clearObject3d();
}

void BObject3d::clearObject3d(void)
{
	unsigned int i;
	unsigned int bSize = m_behaviors.size();
	for(i=0; i<bSize; i++)
		m_behaviors[i]->destroy();
	
	m_behaviors.clear();
	m_childs.clear();
}

// copy constructor
BObject3d::BObject3d(const BObject3d & object):
	m_parent(NULL),
	m_position(object.m_position),
	m_scale(object.m_scale),
	m_rotation(object.m_rotation),
	m_matrix(object.m_matrix),
	m_isVisible(object.m_isVisible),
	m_isActive(object.m_isActive),
	m_needToUpdate(object.m_needToUpdate)
{
	if(object.m_parent)
		linkTo(object.m_parent);

	unsigned int i;
	unsigned int bSize = object.m_behaviors.size();
	for(i=0; i<bSize; i++)
		addBehavior(object.m_behaviors[i]->getCopy(this));
}

void BObject3d::setName(const char * name)
{
	m_name.set(name);
}

void BObject3d::updateBehaviors(void)
{
	unsigned int i;
	unsigned int bSize = m_behaviors.size();
	for(i=0; i<bSize; i++)
		m_behaviors[i]->update();
}

void BObject3d::drawBehaviors(void)
{
	unsigned int i;
	unsigned int bSize = m_behaviors.size();
	for(i=0; i<bSize; i++)
		m_behaviors[i]->draw();
}

void BObject3d::deleteBehavior(unsigned int id)
{
	SAFE_DELETE(m_behaviors[id]);
	m_behaviors.erase(m_behaviors.begin() + id);
}

void BObject3d::invertBehavior(unsigned int idA, unsigned int idB)
{
	BBehavior * behavior = m_behaviors[idA];
	m_behaviors[idA] = m_behaviors[idB];
	m_behaviors[idB] = behavior;
}

void BObject3d::changeBehavior(unsigned int id, BBehavior * behavior)
{
	if(! behavior)
		return;

	SAFE_DELETE(m_behaviors[id]);
	m_behaviors[id] = behavior;
}

void BObject3d::removeChild(BObject3d * child)
{
	unsigned int i;
	unsigned int cSize = m_childs.size();
	for(i=0; i<cSize; i++)
	{
		if(m_childs[i] == child)
		{
			m_childs.erase(m_childs.begin() + i);
			return;
		}
	}
}

void BObject3d::unlinkChilds(void)
{
	unsigned int i;
	unsigned int cSize = m_childs.size();
	for(i=0; i<cSize; i++)
		m_childs[i]->setParent(NULL);
	m_childs.clear();
}

void BObject3d::unLink(void)
{
	if(! getParent())
		return;
	
	// remove child from actual parent
	getParent()->removeChild(this);
	m_parent = NULL;
}

void BObject3d::linkTo(BObject3d * parent)
{
	if(! parent)
		return;

	if(parent == this)
		return;

	if(! getParent()) // if not already linked
	{
		m_parent = parent;
		parent->addChild(this);
		return;
	}

	// if already linked
	if(getParent() == parent)
		return;

	// remove child from actual parent
	getParent()->removeChild(this);
	m_parent = parent;
	parent->addChild(this);
}

void BObject3d::update(void)
{}

void BObject3d::updateMatrix(void)
{
	computeLocalMatrix();

	if(hasParent()){
		m_matrix = m_parent->m_matrix * m_matrix;
	}
}

void BObject3d::computeLocalMatrix(void)
{
	m_matrix.setRotationAxis(m_rotation.getAngle(), m_rotation.getAxis());
	m_matrix.setTranslationPart(m_position);
	m_matrix.scale(m_scale);
}

void BObject3d::computeChildsMatrices(void)
{
	unsigned int i;
	unsigned int childSize = m_childs.size();
	BObject3d * childObject = NULL;

	for(i=0; i<childSize; i++) // for all childs
	{
		childObject = m_childs[i];

		// compute parenting (parent matrix * child local matrix)
		if(m_needToUpdate || childObject->needToUpdate())
		{
			childObject->computeLocalMatrix();
			childObject->m_matrix = m_matrix * childObject->m_matrix;
			childObject->m_needToUpdate = true;
		}
		childObject->computeChildsMatrices();
	}

	m_needToUpdate = false;
}

BVector3f BObject3d::getUniformRotatedVector(const BVector3f & vector)
{
	float L = vector.getLength();
	return (m_matrix.getRotatedVector3(vector).getNormalized() * L);
}

void BObject3d::setPosition(const BVector3f & position)
{
	if(position != m_position)
	{
		m_position = position;
		m_needToUpdate = true;
	}
}

void BObject3d::setEulerRotation(const BVector3f & euler)
{
	BQuaternion rotation = BQuaternion(euler.x, euler.y, euler.z);
	if(rotation != m_rotation)
	{
		m_rotation = rotation;
		m_needToUpdate = true;
	}
}

void BObject3d::setAxisAngleRotation(const BVector3f & axis, const float angle)
{
	BQuaternion rotation = BQuaternion(angle, axis);
	if(rotation != m_rotation)
	{
		m_rotation = rotation;
		m_needToUpdate = true;
	}
}

void BObject3d::addAxisAngleRotation(const BVector3f & axis, const float angle)
{
	m_rotation *= BQuaternion(angle, axis);
	m_needToUpdate = true;
}

void BObject3d::setRotation(const BQuaternion & rotation)
{
	if(rotation != m_rotation)
	{
		m_rotation = rotation;
		m_needToUpdate = true;
	}
}

void BObject3d::setScale(const BVector3f & scale)
{
	if(scale != m_scale)
	{
		m_scale = scale;
		m_needToUpdate = true;
	}
}