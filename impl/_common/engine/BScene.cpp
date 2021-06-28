/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BScene.cpp
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


BScene::BScene():
m_dataMode(M_DATA_STATIC),
m_currentFrame(0),
m_currentCamera(0),
m_gravity(0, 0, -0.981f)
{}

BScene::~BScene()
{
	stopAllSounds();

	// delete objects
	unsigned int oSize = m_objects.size();
	for(unsigned int i=0; i<oSize; i++)
		SAFE_DELETE(m_objects[i]);

	m_objects.clear();

	m_entities.clear();
	m_cameras.clear();
	m_lights.clear();
	m_sounds.clear();
}

BOCamera * BScene::addNewCamera(void)
{
	BOCamera * newCamera = new BOCamera();
	m_cameras.push_back(newCamera);
	m_objects.push_back(newCamera);
	return newCamera;
}

BOCamera * BScene::addNewCamera(const BOCamera & camera)
{
	BOCamera * newCamera = new BOCamera(camera);
	m_cameras.push_back(newCamera);
	m_objects.push_back(newCamera);
	return newCamera;
}

BOCompositedModel3d * BScene::addNewCompositedModel(){
	BOCompositedModel3d * newCModel = new BOCompositedModel3d();
	m_entities.push_back( (BOModel3d*)newCModel );
	m_objects. push_back( (BOModel3d*)newCModel );
	return newCModel;
}

BOLight * BScene::addNewLight(void)
{
	BOLight * newLight = new BOLight();
	m_lights.push_back(newLight);
	m_objects.push_back(newLight);
	return newLight;
}

BOLight * BScene::addNewLight(const BOLight & light)
{
	BOLight * newLight = new BOLight(light);
	m_lights.push_back(newLight);
	m_objects.push_back(newLight);
	return newLight;
}

BOModel3d * BScene::addNewModel(BMeshRef * meshRef, BMeshRef* physicsMeshRef )
{
	BOModel3d * newEntity = new BOModel3d(meshRef, physicsMeshRef);
	m_entities.push_back(newEntity);
	m_objects.push_back(newEntity);
	return newEntity;
}

BOModel3d * BScene::addNewModel(const BOModel3d & entity)
{
	BOModel3d * newEntity = new BOModel3d(entity);
	m_entities.push_back(newEntity);
	m_objects.push_back(newEntity);
	return newEntity;
}


BOSprite * BScene::addNewSprite( BTextureRef* image, float width, bool centered ) // for tests
{
	BOSprite* sprite = new BOSprite( this, image, width, centered );
	m_entities.push_back( sprite );
	m_entities.push_back( sprite );
	m_objects.push_back( sprite );
	return sprite;
}


BOSound * BScene::addNewSound(BSoundRef * soundRef)
{
	BOSound * newSoundSource = new BOSound(soundRef);
	m_sounds.push_back(newSoundSource);
	m_objects.push_back(newSoundSource);
	return newSoundSource;
}

BOSound * BScene::addNewSound(const BOSound & sound)
{
	BOSound * newSoundSource = new BOSound(sound);
	m_sounds.push_back(newSoundSource);
	m_objects.push_back(newSoundSource);
	return newSoundSource;
}

BOText * BScene::addNewText(BFontRef * fontRef)
{
	BOText * newText = new BOText(fontRef);
	m_texts.push_back(newText);
	m_objects.push_back(newText);
	return newText;
}

BOText * BScene::addNewText(const BOText & text)
{
	BOText * newText = new BOText(text);
	m_texts.push_back(newText);
	m_objects.push_back(newText);
	return newText;
}

BOCamera * BScene::getCurrentCamera(void)
{
	unsigned int cSize = getCamerasNumber();
	if(cSize > 0)
	{
		if(m_currentCamera < cSize)
			return getCameraByIndex(m_currentCamera);
		else
			return getCameraByIndex(0);
	}
	
	return NULL;
}

void BScene::setName(const char * name)
{
	m_name.set(name);
}

void BScene::setScriptFilename(const char * scriptFilename)
{
	m_scriptFilename.set(scriptFilename);
}

bool createShape(BOModel3d * entity, BPhysicsProperties * phyProps, unsigned int * shapeId)
{
	BPhysicsContext * physics = Bizarre::getInstance()->getPhysicsContext();

	// get bounding box
	BBox3d * box = entity->getPhysicsBoundingBox();

	BVector3f scale = entity->getTransformedScale();

	// swith shapes
	switch(phyProps->getCollisionShape())
	{
	default:
	case U_COLLISION_SHAPE_BOX:
		physics->createBoxShape(shapeId, (box->max - box->min)*scale*0.5f);
		break;

	case U_COLLISION_SHAPE_SPHERE:
		{
			BVector3f vec = (box->max - box->min)*scale*0.5f;
			float radius = vec.x;
			radius = MAX(radius, vec.y);
			radius = MAX(radius, vec.z);
			physics->createSphereShape(shapeId, radius);
		}
		break;

	case U_COLLISION_SHAPE_CONE:
		{
			BVector3f vec = (box->max - box->min)*scale;
			float height = vec.y;
			float radius = vec.x*0.5f;
			radius = MAX(radius, vec.z*0.5f);
			physics->createConeShape(shapeId, radius, height);
		}
		break;

	case U_COLLISION_SHAPE_CAPSULE:
		{
			BVector3f vec = (box->max - box->min)*scale;
			float height = vec.y;
			float radius = vec.x*0.5f;
			radius = MAX(radius, vec.z*0.5f);
			physics->createCylinderShape(shapeId, radius, height);
		}
		break;

	case U_COLLISION_SHAPE_CYLINDER:
		{
			BVector3f vec = (box->max - box->min)*scale;
			float height = vec.y;
			float radius = vec.x*0.5f;
			radius = MAX(radius, vec.z*0.5f);
			physics->createCylinderShape(shapeId, radius, height);
		}
		break;

	case U_COLLISION_SHAPE_CONVEX_HULL:
		{
			BMesh * mesh = entity->getPhysicsMesh();			
			if(mesh)
			{
				BSubMesh * subMeshs = mesh->getSubMeshs();
				unsigned int subMeshsNumber = mesh->getSubMeshsNumber();
				if(subMeshsNumber == 0)
					return false;

				if(subMeshsNumber == 1)
				{
					BSubMesh * subMesh = &subMeshs[0];
					if(subMesh->getVerticesSize() > 0)
						physics->createConvexHullShape(shapeId, subMesh->getVertices(), subMesh->getVerticesSize(), entity->getScale());
				}
				else
				{
					physics->createMultiShape(shapeId);
					unsigned int s;
					for(s=0; s<subMeshsNumber; s++)
					{
						unsigned int subShapeId;
						BSubMesh * subMesh = &subMeshs[s];
						if(subMesh->getVerticesSize() > 0)
						{
							physics->createConvexHullShape(&subShapeId, subMesh->getVertices(), subMesh->getVerticesSize(), entity->getScale());
							physics->addChildShape(*shapeId, subShapeId, BVector3f(), BQuaternion());
						}
					}
				}
			}
			else{
				return false;
			}
		}
		break;

	case U_COLLISION_SHAPE_TRIANGLE_MESH:
		{
			BMesh * mesh = entity->getPhysicsMesh();
			if(mesh)
			{
				BSubMesh * subMeshs = mesh->getSubMeshs();
				unsigned int subMeshsNumber = mesh->getSubMeshsNumber();
				if(subMeshsNumber == 0)
					return false;

				if(subMeshsNumber == 1)
				{
					
					BSubMesh * subMesh = &subMeshs[0];
					if(subMesh->getVerticesSize() >= 3)
						physics->createTriangleMeshShape(shapeId,
							subMesh->getVertices(), subMesh->getVerticesSize(),
							subMesh->getIndices(), subMesh->getIndicesSize(), subMesh->getIndicesType(),
							entity->getScale()
						);
				}
				else
				{
					physics->createMultiShape(shapeId);
					unsigned int s;
					for(s=0; s<subMeshsNumber; s++)
					{
						unsigned int subShapeId;
						BSubMesh * subMesh = &subMeshs[s];
						if(subMesh->getVerticesSize() >= 3)
						{
							physics->createTriangleMeshShape(&subShapeId,
								subMesh->getVertices(), subMesh->getVerticesSize(),
								subMesh->getIndices(), subMesh->getIndicesSize(), subMesh->getIndicesType(),
								entity->getScale()
							);
							physics->addChildShape(*shapeId, subShapeId, BVector3f(), BQuaternion());
						}
					}
				}
			}
			else{
				return false;
			}
		}
		break;
	}

	return true;
}

void BScene::prepareCollisionShape(BOModel3d * entity)
{
	BPhysicsContext * physics = Bizarre::getInstance()->getPhysicsContext();
	BPhysicsProperties * phyProps = entity->getPhysicsProperties();

	if(! phyProps)
		return;

	unsigned int shapeId = 0;
	if(createShape(entity, phyProps, &shapeId))
	{	
		// has physics child
		bool hasPhysicsChild = false;
		unsigned int o;
		unsigned int oSize = entity->getChildsNumber();
		for(o=0; o<oSize; o++)
		{
			BObject3d * childObject = entity->getChild(o);
			if(childObject->getType() == U_OBJECT3D_MODEL)
			{
				BOModel3d * childEntity = (BOModel3d*)childObject;
				BPhysicsProperties * childPhyProps = childEntity->getPhysicsProperties();
				if(childPhyProps)
				{
					if(! childPhyProps->isGhost())
					{
						hasPhysicsChild = true;
						break;
					}
				}
			}
		}

		// create multi shape
		if(hasPhysicsChild)
		{
			unsigned int subShapeId = shapeId;
			physics->createMultiShape(&shapeId);
			physics->addChildShape(shapeId, subShapeId, BVector3f(), BQuaternion());
		}

		phyProps->setShapeId(shapeId);
	}
}

void BScene::prepareCollisionObject(BOModel3d * entity)
{
	BPhysicsContext * physics = Bizarre::getInstance()->getPhysicsContext();
	BPhysicsProperties * phyProps = entity->getPhysicsProperties();
	if(! phyProps)
		return;

	unsigned int shapeId = phyProps->getShapeId();
	if(shapeId == 0)
		return;

	// has physics parent
	BPhysicsProperties * parentPhyProps = NULL;
	BOModel3d * parentEntity = NULL;
	if(! phyProps->isGhost())
	{
		BObject3d * parentObject = entity->getParent();
		if(parentObject)
		{
			if(parentObject->getType() == U_OBJECT3D_MODEL)
			{
				parentEntity = (BOModel3d*)parentObject;
				parentPhyProps = parentEntity->getPhysicsProperties();
			}
		}
	}

	if(parentPhyProps) // add shape to parent multi-shape
	{
		BVector3f position = entity->getPosition() * parentEntity->getTransformedScale();
		BQuaternion rotation = entity->getRotation();

		phyProps->setShapeId(shapeId);
		physics->addChildShape(parentPhyProps->getShapeId(), shapeId, position, rotation);
	}
	else // create collision object
	{
		unsigned int collisionObjectId;

		if(phyProps->isGhost())
		{
			BVector3f euler = entity->getTransformedRotation();

			physics->createGhost(
				&collisionObjectId, shapeId,
				entity->getTransformedPosition(),
				BQuaternion(euler.x, euler.y, euler.z)
			);

			phyProps->setShapeId(shapeId);
			phyProps->setCollisionObjectId(collisionObjectId);
		}
		else
		{
			physics->createRigidBody(
				&collisionObjectId, shapeId,
				entity->getPosition(), entity->getRotation(),
				phyProps->getMass()
			);

			phyProps->setShapeId(shapeId);
			phyProps->setCollisionObjectId(collisionObjectId);

			physics->setObjectRestitution(collisionObjectId, phyProps->getRestitution());
			physics->setObjectDamping(collisionObjectId, phyProps->getLinearDamping(), phyProps->getAngularDamping());
			physics->setObjectAngularFactor(collisionObjectId, phyProps->getAngularFactor());
			physics->setObjectLinearFactor(collisionObjectId, *phyProps->getLinearFactor());
			physics->setObjectFriction(collisionObjectId, phyProps->getFriction());
		}

		// deactivate
		if(! entity->isActive())
			physics->deactivateObject(collisionObjectId);

		// set user pointer (entity)
		physics->setObjectUserPointer(collisionObjectId, entity);
	}
}

void BScene::prepareConstraints(BOModel3d * entity)
{
	BPhysicsContext * physics = Bizarre::getInstance()->getPhysicsContext();
	BPhysicsProperties * phyProps = entity->getPhysicsProperties();

	if(! phyProps)
		return;

	unsigned int objectId = phyProps->getCollisionObjectId();
	BPhysicsConstraint * constraint = phyProps->getConstraint();

	if((! constraint) || (objectId == 0) || phyProps->isGhost())
		return;

	if(! entity->getParent())
	{
		BOModel3d * constraintParent = getModelByName(constraint->parentName.getSafeString());
		if(constraintParent)
		{
			BPhysicsProperties * parentPhyProps = constraintParent->getPhysicsProperties();
			if(parentPhyProps)
			{
				unsigned int parentObjectId = parentPhyProps->getCollisionObjectId();
				if(parentObjectId != 0)
				{
					physics->createConstraint(
											  &constraint->constraintId,
											  parentObjectId,
											  objectId,
											  constraint->pivot,
											  constraint->disableParentCollision
											  );

					constraint->parentObjectId = parentObjectId;
					physics->setLinearLimit(constraint->constraintId, constraint->lowerLinearLimit, constraint->upperLinearLimit);
					physics->setAngularLimit(constraint->constraintId, constraint->lowerAngularLimit, constraint->upperAngularLimit);
				}
			}
		}
	}
}

void BScene::preparePhysics(void)
{
	BPhysicsContext * physics = Bizarre::getInstance()->getPhysicsContext();
	if(! physics)
		return;


	physics->init(BVector3f(-10000), BVector3f(10000));
	physics->setWorldGravity(m_gravity);

	// create shapes
	unsigned int i;
	unsigned int size = getEntitiesNumber();

	for(i=0; i<size; i++)
	{
		BOModel3d * entity = getModelByIndex(i);
		prepareCollisionShape(entity);
	}

	// create objects
	for(i=0; i<size; i++)
	{
		BOModel3d * entity = getModelByIndex(i);
		prepareCollisionObject(entity);
	}

	// create constraints
	for(i=0; i<size; i++)
	{
		BOModel3d * entity = getModelByIndex(i);
		prepareConstraints(entity);
	}
}

void BScene::deleteObject(BObject3d * object)
{
	if(! object)
		return;

	unsigned int i;
	unsigned int oSize;

	// objects
	switch(object->getType())
	{
	case U_OBJECT3D_MODEL:
		{
			// entities
			oSize = m_entities.size();
			for(i=0; i<oSize; i++){
				BObject3d * obj = m_entities[i];
				if(obj == object){
					m_entities.erase(m_entities.begin() + i);
					break;
				}
			}
		}
		break;

	case U_OBJECT3D_CAMERA:
		{
			// cameras
			oSize = m_cameras.size();
			for(i=0; i<oSize; i++){
				BObject3d * obj = m_cameras[i];
				if(obj == object){
					m_cameras.erase(m_cameras.begin() + i);
					break;
				}
			}
		}
		break;

	case U_OBJECT3D_LIGHT:
		{
			// lights
			oSize = m_lights.size();
			for(i=0; i<oSize; i++){
				BObject3d * obj = m_lights[i];
				if(obj == object){
					m_lights.erase(m_lights.begin() + i);
					break;
				}
			}
		}
		break;

	case U_OBJECT3D_SOUND:
		{
			// sounds
			oSize = m_sounds.size();
			for(i=0; i<oSize; i++){
				BObject3d * obj = m_sounds[i];
				if(obj == object){
					m_sounds.erase(m_sounds.begin() + i);
					break;
				}
			}
		}
		break;

	case U_OBJECT3D_TEXT:
		{
			// sounds
			oSize = m_texts.size();
			for(i=0; i<oSize; i++){
				BObject3d * obj = m_texts[i];
				if(obj == object){
					m_texts.erase(m_texts.begin() + i);
					break;
				}
			}
		}
		break;
	}

	// objects pointer
	oSize = m_objects.size();
	for(i=0; i<oSize; i++){
		BObject3d * obj = m_objects[i];
		if(obj == object)
		{
			obj->unLink();
			obj->unlinkChilds();

			m_objects.erase(m_objects.begin() + i);
			SAFE_DELETE(obj);
			return;
		}
	}
}

bool BScene::getObjectIndex(const char * name, unsigned int * id)
{
	unsigned int i;
	unsigned int oSize = getObjectsNumber();
	for(i=0; i<oSize; i++)
	{
		if(strcmp(name, m_objects[i]->getName()) == 0)
		{
			(*id) = i;
			return true;
		}
	}

	return false;
}

BObject3d * BScene::getObjectByName(const char * name)
{
	unsigned int id;
	if(getObjectIndex(name, &id)){
		return m_objects[id];
	}

	return NULL;
}

BOLight * BScene::getLightByName(const char * name)
{
	unsigned int i;
	unsigned int size = getLightsNumber();
	for(i=0; i<size; i++)
	{
		if(strcmp(name, m_lights[i]->getName()) == 0)
			return m_lights[i];
	}

	return NULL;
}

BOCamera * BScene::getCameraByName(const char * name)
{
	unsigned int i;
	unsigned int size = getCamerasNumber();
	for(i=0; i<size; i++)
	{
		if(strcmp(name, m_cameras[i]->getName()) == 0)
			return m_cameras[i];
	}

	return NULL;
}

BOModel3d * BScene::getModelByName(const char * name)
{
	unsigned int i;
	unsigned int size = getEntitiesNumber();
	for(i=0; i<size; i++)
	{
		if(strcmp(name, m_entities[i]->getName()) == 0)
			return m_entities[i];
	}

	return NULL;
}

BOSound * BScene::getSoundByName(const char * name)
{
	unsigned int i;
	unsigned int size = getSoundsNumber();
	for(i=0; i<size; i++)
	{
		if(strcmp(name, m_sounds[i]->getName()) == 0)
			return m_sounds[i];
	}

	return NULL;
}

BOText * BScene::getTextByName(const char * name)
{
	unsigned int i;
	unsigned int size = getTextsNumber();
	for(i=0; i<size; i++)
	{
		if(strcmp(name, m_texts[i]->getName()) == 0)
			return m_texts[i];
	}

	return NULL;
}

void BScene::begin(void)
{
	Bizarre * engine = Bizarre::getInstance();
	BScriptContext * scriptContext = engine->getScriptContext();

	updateObjectsMatrices();
	playLoopSounds();
	preparePhysics();

	// run script
//	if(scriptContext)
//		scriptContext->runScript(getScriptFilename());
}

void BScene::end(void)
{
	stopAllSounds();
}

void BScene::updatePhysics(void)
{
	BPhysicsContext * physics = Bizarre::getInstance()->getPhysicsContext();
	if(! physics)
		return;

	unsigned int i;
	unsigned int size = getEntitiesNumber();
	for(i=0; i<size; i++)
	{	
		//std::cout << "obj: " << i << endl;
		BOModel3d * entity = getModelByIndex(i);
		if(! entity->isActive())
			continue;

		BPhysicsProperties * phyProps = entity->getPhysicsProperties();
		if(! phyProps)
			continue;

		//std::cout << "physics true: " << i << endl;

		if(phyProps->getCollisionObjectId() > 0)
		{
			BObject3d * parent = entity->getParent();
			if(parent && phyProps->isGhost())
			{
				BVector3f euler = entity->getTransformedRotation();
				physics->setObjectTransform(
					phyProps->getCollisionObjectId(),
					entity->getTransformedPosition(),
					BQuaternion(euler.x, euler.y, euler.z)
				);
			}
			else if(entity->needToUpdate())
			{	
				physics->setObjectTransform(
					phyProps->getCollisionObjectId(),
					entity->getPosition(),
					entity->getRotation()
				);
			}else{
				//std::cout << "Fisicas no funcionales 1" << endl;
			}
		}else{
			//std::cout << "Fisicas no funcionales 2" << endl;
		}
	}

	physics->setWorldGravity(m_gravity);
	physics->updateSimulation();

	for(i=0; i<size; i++)
	{
		BOModel3d * entity = getModelByIndex(i);
		if(! entity->isActive())
			continue;

		BPhysicsProperties * phyProps = entity->getPhysicsProperties();
		if(phyProps)
		{
			if((phyProps->getCollisionObjectId() > 0) && (! phyProps->isGhost()))
			{
				BVector3f position = entity->getPosition();
				BQuaternion rotation = entity->getRotation();

				physics->getObjectTransform(phyProps->getCollisionObjectId(), &position, &rotation);

				entity->setPosition(position);
				entity->setRotation(rotation);
			}
		}
	}
}

void BScene::updateObjectsBehaviors(void)
{
	unsigned int i;
	unsigned int oSize = getObjectsNumber();
	for(i=0; i<oSize; i++)
	{
		BObject3d * object = getObjectByIndex(i);
		if(! object->isActive())
			continue;

		object->updateBehaviors();
	}
}

void BScene::drawObjectsBehaviors(void)
{
	unsigned int i;
	unsigned int oSize = getObjectsNumber();
	for(i=0; i<oSize; i++)
	{
		BObject3d * object = getObjectByIndex(i);
		if(! object->isActive())
			continue;

		object->drawBehaviors();
	}
}

void BScene::updateObjectsMatrices(void)
{
	unsigned int i;
	unsigned int oSize = getObjectsNumber();
	for(i=0; i<oSize; i++)
	{
		BObject3d * object = getObjectByIndex(i);
		if(! object->isActive())
			continue;

		if(! object->hasParent())
		{
			if(object->needToUpdate())
				object->computeLocalMatrix();
			object->computeChildsMatrices();
		}
	}
}

void BScene::update(void)
{
	// update objects
	unsigned int i;
	unsigned int oSize = getObjectsNumber();
	for(i=0; i<oSize; i++)
	{
		BObject3d * object = getObjectByIndex(i);
		if(object->isActive())
			object->update();
	}

	// update current frame
	m_currentFrame++;
}

void BScene::playLoopSounds()
{
	unsigned int i;

	// sound sources
	unsigned int sSize = getSoundsNumber();
	for(i=0; i<sSize; i++)
	{
		if(m_sounds[i]->isActive() && m_sounds[i]->isLooping())
			m_sounds[i]->play();
	}
}

void BScene::stopAllSounds()
{
	unsigned int i;

	// sound sources
	unsigned int sSize = getSoundsNumber();
	for(i=0; i<sSize; i++)
		m_sounds[i]->stop();
}

void BScene::draw(BOCamera * camera)
{
	Bizarre * engine = Bizarre::getInstance();
	BRenderer * renderer = engine->getRenderer();
	if(renderer)
		renderer->drawScene(this, camera);
}
