/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BOModel3d.h
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


#ifndef _B_OMODEL_H
#define _B_OMODEL_H


// collision shape types
enum U_COLLISION_SHAPE_TYPE
{
	U_COLLISION_SHAPE_BOX = 0,
	U_COLLISION_SHAPE_SPHERE,
	U_COLLISION_SHAPE_CONE,
	U_COLLISION_SHAPE_CAPSULE,
	U_COLLISION_SHAPE_CYLINDER,
	U_COLLISION_SHAPE_CONVEX_HULL,
	U_COLLISION_SHAPE_TRIANGLE_MESH
};



struct BPhysicsConstraint
{
	BPhysicsConstraint(void);
	BPhysicsConstraint(const BPhysicsConstraint & constraint);
	
	unsigned int constraintId;
	unsigned int parentObjectId;
	
	BString parentName;
	BVector3f pivot;
	BVector3f lowerLinearLimit;
	BVector3f upperLinearLimit;
	BVector3f lowerAngularLimit;
	BVector3f upperAngularLimit;
	bool disableParentCollision;
};



class M_ENGINE_EXPORT BPhysicsProperties
{
public:

	BPhysicsProperties(void);
	BPhysicsProperties(const BPhysicsProperties & physicsProperties);
	~BPhysicsProperties(void);

private:

	BPhysicsConstraint * m_constraint;
	
	unsigned int m_shapeId;
	unsigned int m_collisionObjectId;
	U_COLLISION_SHAPE_TYPE m_collisionShape;

	bool m_ghost;
	float m_mass;
	float m_friction;
	float m_restitution;
	float m_linearDamping;
	float m_angularDamping;
	float m_angularFactor;
	BVector3f m_linearFactor;

public:

	// constyraint
	void deleteConstraint(void);
	BPhysicsConstraint * createConstraint(void);
	inline BPhysicsConstraint * getConstraint(void){ return m_constraint; }

	// shape id
	inline void setShapeId(unsigned int shapeId){ m_shapeId = shapeId; }
	inline unsigned int getShapeId(void){ return m_shapeId; }

	// collision object id
	inline void setCollisionObjectId(unsigned int collisionObjectId){ m_collisionObjectId = collisionObjectId; }
	inline unsigned int getCollisionObjectId(void){ return m_collisionObjectId; }

	// collision shape
	inline void setCollisionShape(U_COLLISION_SHAPE_TYPE collisionShape){ m_collisionShape = collisionShape; }
	inline U_COLLISION_SHAPE_TYPE getCollisionShape(void){ return m_collisionShape; }

	// ghost
	inline void setGhost(bool ghost){ m_ghost = ghost; }
	inline bool isGhost(void){ return m_ghost; }

	// mass
	inline void setMass(float mass){ m_mass = mass; }
	inline float getMass(void){ return m_mass; }

	// friction
	inline void setFriction(float friction){ m_friction = friction; }
	inline float getFriction(void){ return m_friction; }

	// restitution
	inline void setRestitution(float restitution){ m_restitution = restitution; }
	inline float getRestitution(void){ return m_restitution; }

	// linear damping
	inline void setLinearDamping(float linearDamping){ m_linearDamping = linearDamping; }
	inline float getLinearDamping(void){ return m_linearDamping; }

	// angular damping
	inline void setAngularDamping(float angularDamping){ m_angularDamping = angularDamping; }
	inline float getAngularDamping(void){ return m_angularDamping; }

	// angular factor
	inline void setAngularFactor(float angularFactor){ m_angularFactor = angularFactor; }
	inline float getAngularFactor(void){ return m_angularFactor; }

	// linear factor
	inline void setLinearFactor(const BVector3f & linearFactor){ m_linearFactor = linearFactor; }
	inline BVector3f * getLinearFactor(void){ return &m_linearFactor; }
};




class M_ENGINE_EXPORT BOModel3d : public BObject3d
{
public:

	// constructor / destructor
	BOModel3d(BMeshRef * meshRef, BMeshRef* physicsMeshRef = NULL );
	~BOModel3d(void);

	// copy constructor
	BOModel3d(const BOModel3d & entity);
private: // Bizarre impl
	enum animation_state{
        ANIMATION_STATE_NONE = 0,
        ANIMATION_STATE_PLAYING,
        ANIMATION_STATE_TRANSITION
    };
    BTimer* animations_timer;
    


protected:
	// mesh
	BMeshRef * m_meshRef;
	/// is mesh used for physics simulations
	BMeshRef * m_physicsMeshRef; // createShape new in Bizarre

private:
	// invisible
	bool m_isInvisible;

	// animation
	/// Animación interna, puede ser una animación o una transición
	unsigned int m_animationId; 
	animation_state m_animationsState; // Bizarre new
	/// Animación en curso, es la que ven los objetos externos (no toma en cuenta si es una transición)
	animation m_currentAnimation; // Bizarre new
	int m_currentLoop;
	float m_animationSpeed;
	float m_currentFrame;
	

	// collision
	BPhysicsProperties * m_physicsProperties;

	// bounding box
	/// view model bounding box
	BBox3d m_boundingBox; 
	/// physics model bounding box
	BBox3d m_PhysicsBoundingBox; 

public:

	// type
	int getType(void){ return U_OBJECT3D_MODEL; }

	void setActive(bool active);
	
	// invisible
	void setInvisible(bool invisible){ m_isInvisible = invisible; }
	bool isInvisible(void){ return m_isInvisible; }

	// mesh
	inline BMesh * getMesh(void){ return (! m_meshRef)? NULL : m_meshRef->getMesh(); }
	inline  BMesh * getPhysicsMesh(void){ return (!m_physicsMeshRef)? NULL : m_physicsMeshRef->getMesh(); }

	void setMeshRef(BMeshRef * meshRef, BMeshRef * physicsMeshRef = NULL);
	inline BMeshRef * getMeshRef(void){ return m_meshRef; }
	inline BMeshRef * getPhysicsMeshRef(void){ return m_physicsMeshRef; }

	// animation
	//void addAnimation(model_animation animation, unsigned int animationId);
    //inline void addAnimationTransition(unsigned int outAnimation, unsigned int inAnimation, unsigned int transitionAnimation){animations[outAnimation].animationTransitions[inAnimation] = transitionAnimation; } 
    //inline void addPostAnimation(model_animation animation, model_animation postAnimation){animations[animation].animationPost = postAnimation;}
    //inline void addPostAnimationDelay(model_animation animation, double delay){ animations[animation].animationEndDelay = delay; }

	//transformations
	inline void setPosition(const BVector3f & position){ BObject3d::setPosition(position); } // optimization of virtual methods

	void changeAnimation(unsigned int animationId);
	bool isAnimationOver(void);
	inline void setAnimationSpeed(float animationSpeed){ m_animationSpeed = animationSpeed; }
	inline void setCurrentFrame(float currentFrame){ m_currentFrame = currentFrame; }
	inline unsigned int getAnimationId(void){ return m_animationId; }
	inline float getAnimationSpeed(void){ return m_animationSpeed; }
	inline float getCurrentFrame(void){ return m_currentFrame; }

	// physics
	void deletePhysicsProperties(void);
	BPhysicsProperties * createPhysicsProperties(void);
	inline BPhysicsProperties * getPhysicsProperties(void){ return m_physicsProperties; }

	// bounding box
	inline BBox3d * getBoundingBox(void){ return &m_boundingBox; }
	inline BBox3d * getPhysicsBoundingBox(void){ return &m_PhysicsBoundingBox; }


	// load
	inline void loadPhysics(void){ getPhysicsMeshRef()->update();  }
	inline void load(void){ getPhysicsMeshRef()->update(); if( getMeshRef() != getPhysicsMeshRef() ) getMeshRef()->update(); } // Todo: preparar su ejecucion en hilo secundario
	inline bool isLoaded(void){ return getMesh() && getPhysicsMesh(); }
	inline bool isPhysicsLoad(void){ return getPhysicsMesh(); }

	// update
	void update(void);

	// visibility
	void updateVisibility(BOCamera * camera);
};

#endif
