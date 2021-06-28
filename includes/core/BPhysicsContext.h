/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BPhysicsContext.h
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


#ifndef _M_PHYSICS_CONTEXT_H
#define _M_PHYSICS_CONTEXT_H


class M_CORE_EXPORT BPhysicsContext
{
public:

	// destructor
	virtual ~BPhysicsContext(void){}

	// init
	virtual void init(const BVector3f & worldMin, const BVector3f & worldMax) = 0;

	// destroy
	virtual void clear(void) = 0;

	// update simulation
	virtual void setSimulationQuality(unsigned int quality) = 0;
	virtual void updateSimulation(void) = 0;

	// world
	virtual void setWorldGravity(const BVector3f & gravity) = 0;

	// create object
	virtual void createGhost(unsigned int * objectId, unsigned int shapeId, const BVector3f & position, const BQuaternion & rotation) = 0;
	virtual void createRigidBody(unsigned int * objectId, unsigned int shapeId, const BVector3f & position, const BQuaternion & rotation, float mass) = 0;

	// activate / deactivate
	virtual void activateObject(unsigned int objectId) = 0;
	virtual void deactivateObject(unsigned int objectId) = 0;
	
	// delete object
	virtual void deleteObject(unsigned int * objectId) = 0;

	// object properties
	virtual void enableObjectKinematic(unsigned int objectId) = 0;
	virtual void disableObjectKinematic(unsigned int objectId) = 0;

	virtual void setObjectShape(unsigned int objectId, unsigned int shapeId) = 0;
	virtual void setObjectMass(unsigned int objectId, float mass) = 0;
	virtual void setObjectRestitution(unsigned int objectId, float restitution) = 0;
	virtual void setObjectFriction(unsigned int objectId, float friction) = 0;
	virtual void setObjectLinearFactor(unsigned int objectId, const BVector3f & linearFactor) = 0;
	virtual void setObjectAngularFactor(unsigned int objectId, float angularFactor) = 0;
	virtual void setObjectDamping(unsigned int objectId, float linearDamping, float angularDamping) = 0;
	virtual void setObjectTransform(unsigned int objectId, const BVector3f & position, const BQuaternion & rotation) = 0;
	virtual void getObjectTransform(unsigned int objectId, BVector3f * position, BQuaternion * rotation) = 0;

	virtual void setObjectUserPointer(unsigned int objectId, void * userPointer) = 0;
	virtual void * getObjectUserPointer(unsigned int objectId) = 0;
	
	// affectors
	virtual void addCentralForce(unsigned int objectId, const BVector3f & force) = 0;
	virtual void getCentralForce(unsigned int objectId, BVector3f * force) = 0;
	virtual void addTorque(unsigned int objectId, const BVector3f & torque) = 0;
	virtual void getTorque(unsigned int objectId, BVector3f * torque) = 0;
	virtual void clearForces(unsigned int objectId) = 0;

	// objects collision
	virtual int isObjectInCollision(unsigned int objectId, unsigned int * collisionList = NULL, unsigned int size = 0) = 0;
	virtual bool isObjectsCollision(unsigned int object1Id, unsigned int object2Id) = 0;
	virtual bool isRayHit(const BVector3f & start, const BVector3f & end, unsigned int * objectId = NULL, BVector3f * point = NULL, BVector3f * normal = NULL) = 0;

	// create shape
	virtual void createMultiShape(unsigned int * shapeId) = 0;

	virtual void createBoxShape(unsigned int * shapeId, const BVector3f & scale) = 0;
	virtual void createSphereShape(unsigned int * shapeId, float radius) = 0;
	virtual void createConeShape(unsigned int * shapeId, float radius, float height) = 0;
	virtual void createCapsuleShape(unsigned int * shapeId, float radius, float height) = 0;
	virtual void createCylinderShape(unsigned int * shapeId, float radius, float height) = 0;

	virtual void createConvexHullShape(unsigned int * shapeId, const BVector3f * vertices, unsigned int verticesNumber, const BVector3f scale = BVector3f(1)) = 0;
	virtual void createTriangleMeshShape(unsigned int * shapeId, const BVector3f * vertices, unsigned int verticesNumber, const void * indices, unsigned int indicesNumber, U_TYPES indicesType, const BVector3f scale = BVector3f(1)) = 0;

	// delete shape
	virtual void deleteShape(unsigned int * shapeId) = 0;

	// add child shape to multishape
	virtual void addChildShape(unsigned int multiShapeId, unsigned int shapeId, const BVector3f & position, const BQuaternion & rotation) = 0;

	// create constraint
	virtual void createConstraint(unsigned int * constraintId, unsigned int parentObjectId, unsigned int objectId, const BVector3f & pivot, bool disableParentCollision) = 0;
	virtual void setLinearLimit(unsigned int constraintId, const BVector3f & lower, const BVector3f & upper) = 0;
	virtual void setAngularLimit(unsigned int constraintId, const BVector3f & lower, const BVector3f & upper) = 0;
	
	// delete constraint
	virtual void deleteConstraint(unsigned int * constraintId) = 0;
};

#endif