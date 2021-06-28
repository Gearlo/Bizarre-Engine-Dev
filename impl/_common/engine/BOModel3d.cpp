/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BOModel3d.cpp
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


#include <Bizarre.h>


BPhysicsConstraint::BPhysicsConstraint(void):
constraintId(0),
parentObjectId(0),
lowerAngularLimit(-180),
upperAngularLimit(180),
disableParentCollision(false),
parentName("...")
{}

BPhysicsConstraint::BPhysicsConstraint(const BPhysicsConstraint & constraint):
constraintId(0),
parentObjectId(0),
parentName(constraint.parentName),
pivot(constraint.pivot),
lowerLinearLimit(constraint.lowerLinearLimit),
upperLinearLimit(constraint.upperLinearLimit),
lowerAngularLimit(constraint.lowerAngularLimit),
upperAngularLimit(constraint.upperAngularLimit),
disableParentCollision(constraint.disableParentCollision)
{}


BPhysicsProperties::BPhysicsProperties(void):
	m_constraint(NULL),
	m_ghost(false),
	m_shapeId(0),
	m_collisionObjectId(0),
	m_collisionShape(U_COLLISION_SHAPE_BOX),
	m_friction(0.5f),
	m_mass(0),
	m_restitution(0.0f),
	m_linearDamping(0.01f),
	m_angularDamping(0.01f),
	m_angularFactor(1),
	m_linearFactor(1, 1, 1)
{}

BPhysicsProperties::BPhysicsProperties(const BPhysicsProperties & physicsProperties):
	m_constraint(NULL),
	m_ghost(physicsProperties.m_ghost),
	m_shapeId(physicsProperties.m_shapeId),
	m_collisionObjectId(0),
	m_collisionShape(physicsProperties.m_collisionShape),
	m_friction(physicsProperties.m_friction),
	m_mass(physicsProperties.m_mass),
	m_restitution(physicsProperties.m_restitution),
	m_linearDamping(physicsProperties.m_linearDamping),
	m_angularDamping(physicsProperties.m_angularDamping),
	m_angularFactor(physicsProperties.m_angularFactor),
	m_linearFactor(physicsProperties.m_linearFactor)
{
	if(physicsProperties.m_constraint)
		m_constraint = new BPhysicsConstraint(*physicsProperties.m_constraint);
}

BPhysicsProperties::~BPhysicsProperties(void)
{
	deleteConstraint();
}

void BPhysicsProperties::deleteConstraint(void)
{
	SAFE_DELETE(m_constraint);
}

BPhysicsConstraint * BPhysicsProperties::createConstraint(void)
{
	deleteConstraint();
	m_constraint = new BPhysicsConstraint();
	return m_constraint;
}




BOModel3d::BOModel3d(BMeshRef * meshRef, BMeshRef* physicsMeshRef):
BObject3d(),
m_isInvisible(false),
m_animationSpeed(1),
m_currentFrame(0),
m_currentLoop(0),
m_animationId(0),
m_physicsProperties(NULL),
m_animationsState( ANIMATION_STATE_NONE ),
m_currentAnimation( 0u )
{
	setMeshRef(meshRef, physicsMeshRef);
	animations_timer = new BTimer();
}

BOModel3d::BOModel3d(const BOModel3d & entity):
BObject3d(entity),
m_isInvisible(entity.m_isInvisible),
m_physicsProperties(NULL),
m_animationSpeed(entity.m_animationSpeed),
m_currentFrame(entity.m_currentFrame),
m_currentLoop(entity.m_currentLoop),
m_animationId(entity.m_animationId),
animations_timer( entity.animations_timer )
{
	setMeshRef(entity.m_meshRef, entity.m_physicsMeshRef);
	if(entity.m_physicsProperties)
		m_physicsProperties = new BPhysicsProperties(*entity.m_physicsProperties);
}

BOModel3d::~BOModel3d(void)
{
	deletePhysicsProperties();
	BObject3d::clearObject3d();
}

void BOModel3d::changeAnimation(unsigned int animationId)
{
	BMesh * mesh = getMesh();
	if(! mesh)
	{
		m_animationId = animationId;
		return;
	}

	if(animationId >= mesh->getAnimsPropsNumber())
		return;

	bool init = false;

	// change anim
	/* if(animationId != m_animationId)
	{
		m_animationId = animationId;
		init = true;
	}
	else
	{
		// or restart stopped anim
		BAnimProperties * animRange = &mesh->getAnimsProps()[m_animationId];
		if(m_currentLoop == animRange->loops)
			init = true;
	} */
	if( m_currentAnimation != animationId ){
		BAnimProperties * animRange = &mesh->getAnimsProps()[m_animationId];
		BAnimTransitionProperties * animTransition = animRange->getTransition( m_animationId );

		if( animTransition && animTransition->transitionAnim != NONE_ANIMATION ){
			m_animationId = animTransition->transitionAnim;
			m_animationsState = ANIMATION_STATE_TRANSITION;
		}else{
			m_animationId = animationId;
			m_animationsState = ANIMATION_STATE_PLAYING;
		}
		m_currentAnimation = animationId;
		init = true;
	}else
	{
		// or restart stopped anim
		BAnimProperties * animRange = &mesh->getAnimsProps()[m_animationId];
		if(m_currentLoop == animRange->loops)
			init = true;
	}


	if(init)
	{
		BAnimProperties * animRange = &mesh->getAnimsProps()[m_animationId];

		if(m_animationSpeed >= 0)
			m_currentFrame = animRange->start;
		else
			m_currentFrame = animRange->end;

		m_currentLoop = 0;
	}
}

void BOModel3d::deletePhysicsProperties(void)
{
	SAFE_DELETE(m_physicsProperties);
}

BPhysicsProperties * BOModel3d::createPhysicsProperties(void)
{
	deletePhysicsProperties();
	BPhysicsProperties * physicsProperties = new BPhysicsProperties();
	m_physicsProperties = physicsProperties;
	return physicsProperties;
}

void BOModel3d::setActive(bool active)
{
	m_isActive = active;
}

void BOModel3d::setMeshRef(BMeshRef * meshRef, BMeshRef * physicsMeshRef )
{
	
	BMesh * mesh = NULL;
	// set mesh ref
	m_meshRef = meshRef;

	if(m_meshRef)
	{
		mesh = m_meshRef->getMesh();
		if(mesh)
			m_boundingBox = (*mesh->getBoundingBox());
	}

	
	if (!physicsMeshRef)
		m_physicsMeshRef = m_meshRef;
	else
		m_physicsMeshRef = physicsMeshRef;


	
	if(m_physicsMeshRef)
	{
		mesh = m_physicsMeshRef->getMesh();
		if(mesh)
			m_PhysicsBoundingBox = (*mesh->getBoundingBox());
	}
	
}

/* BMesh * BOModel3d::getMesh(void)
{
	if(! m_meshRef)
		return NULL;

	return m_meshRef->getMesh();
}*/

void BOModel3d::updateVisibility(BOCamera * camera)
{
	if(m_isInvisible){
		setVisible(false);
		return;
	}

	BFrustum * frustum = camera->getFrustum();

	BVector3f * min = &m_boundingBox.min;
	BVector3f * max = &m_boundingBox.max;

	BVector3f points[8] = {
		getTransformedVector(BVector3f(min->x, min->y, min->z)),
		getTransformedVector(BVector3f(min->x, max->y, min->z)),
		getTransformedVector(BVector3f(max->x, max->y, min->z)),
		getTransformedVector(BVector3f(max->x, min->y, min->z)),
		getTransformedVector(BVector3f(min->x, min->y, max->z)),
		getTransformedVector(BVector3f(min->x, max->y, max->z)),
		getTransformedVector(BVector3f(max->x, max->y, max->z)),
		getTransformedVector(BVector3f(max->x, min->y, max->z))
	};

	// is box in frustum
	setVisible(frustum->isVolumePointsVisible(points, 8));
}

bool BOModel3d::isAnimationOver(void)
{
	BMesh * mesh = getMesh();
	if(mesh)
	{
		if(mesh->getAnimsPropsNumber() > 0)
		{
			BAnimProperties * animRange = &mesh->getAnimsProps()[m_animationId];

			// end loops
			if(animRange->loops >= 0 && m_currentLoop == animRange->loops)
				return true;

			// next frame
			float nextFrame = m_currentFrame + m_animationSpeed;

			if(m_animationSpeed > 0)
				return (nextFrame >= (animRange->end + 1));
			else
				return (nextFrame <= animRange->start);
		}
	}

	return false;
}

void BOModel3d::update(void)
{
	BMesh * mesh = getMesh();
	bool initAnim = false;
	if(mesh)
	{
		// anim
	 	if(mesh->getAnimsPropsNumber() > 0 && m_animationSpeed > 0)
		{
			BAnimProperties * animRange = &mesh->getAnimsProps()[m_animationId];

			switch( m_animationsState ){
			case ANIMATION_STATE_TRANSITION:
				if( isAnimationOver() ){
					m_animationId = m_currentAnimation;
					m_animationsState = ANIMATION_STATE_PLAYING;
					initAnim = true;
				}
				break;
				
			case ANIMATION_STATE_PLAYING:
				if( isAnimationOver() ){
					double endDelay = animRange->atTheEndDelayAnim;
					bool hasPostAnimation = animRange->atTheEndAnim != NONE_ANIMATION;
					
					if(hasPostAnimation && animations_timer->getTime() > endDelay){
						m_animationId = animRange->atTheEndAnim;
						initAnim = true;
					}
				}else
					animations_timer->restart();
				
			break;
		}


		if(initAnim)
		{
			animRange = &mesh->getAnimsProps()[m_animationId];
			if(m_animationSpeed >= 0)
				m_currentFrame = animRange->start;
			else
				m_currentFrame = animRange->end;

			m_currentLoop = 0;

			m_currentAnimation = m_animationId;
		}

			animRange = &mesh->getAnimsProps()[m_animationId];
			// end loop
			if(animRange->loops >= 0 && m_currentLoop == animRange->loops)
				return;

			// next frame
			float nextFrame = m_currentFrame + m_animationSpeed;

			// update current frame
			if(animRange->loops < 0)
				m_currentFrame = loopFloat(nextFrame, animRange->start, (animRange->end + 1));
			else
			{
				if(isAnimationOver())
					m_currentLoop++;

				if(m_currentLoop < animRange->loops)
					m_currentFrame = loopFloat(nextFrame, animRange->start, (animRange->end + 1));
			}
		}
	}
}
