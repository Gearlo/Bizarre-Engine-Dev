/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BScene.h
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


#ifndef _M_SCENE_H
#define _M_SCENE_H


#include <BImplTypes.h>

// data modes
enum M_DATA_MODES
{
	M_DATA_STATIC = 0,
	M_DATA_DYNAMIC,
	M_DATA_STREAM
};

// BScene
class M_ENGINE_EXPORT BScene
{
public:

	// constructor / destructor
	BScene(void);
	~BScene(void);

private:

	// name
	BString m_name;

	// data mode
	M_DATA_MODES m_dataMode;

	// script
	BString m_scriptFilename;

	// objects pointers
	vector <BObject3d *> m_objects;

	// objects
	vector <BOCamera *> m_cameras;
	vector <BOLight *> m_lights;
	vector <BOModel3d *> m_entities;
	vector <BOModel3d *> m_sprites;
	vector <BOSound *> m_sounds;
	vector <BOText *> m_texts;

	// current frame
	int m_currentFrame;

	// current camera
	unsigned int m_currentCamera;

	// gravity
	BVector3f m_gravity;

public:

	// name
	void setName(const char * name);
	inline const char * getName(void){ return m_name.getSafeString(); }

	// data mode
	inline void setDataMode(M_DATA_MODES dataMode){ m_dataMode = dataMode; }
	inline M_DATA_MODES getDataMode(void){ return m_dataMode; }

	// script
	void setScriptFilename(const char * scriptFilename);
	inline const char * getScriptFilename(void){ return m_scriptFilename.getData(); }

	// gravity
	inline void setGravity(const BVector3f & gravity){ m_gravity = gravity; }
	inline BVector3f getGravity(void) const { return m_gravity; }

	// sounds
	void playLoopSounds(void);
	void stopAllSounds(void);

	// delete object
	void deleteObject(BObject3d * object);

	// add objects
	BOCamera  * addNewCamera(void);
	BOCamera  * addNewCamera(const BOCamera & camera);
	BOCompositedModel3d * addNewCompositedModel(void);
	BOLight   * addNewLight(void);
	BOLight   * addNewLight(const BOLight & light);
	BOModel3d * addNewModel(BMeshRef * meshRef, BMeshRef * physicsMeshRef = NULL);
	BOModel3d * addNewModel(const BOModel3d & entity);
	BOSprite  * addNewSprite( BTextureRef* image, float width = 0.1f, bool centered = false ); // for test
	BOSound   * addNewSound(BSoundRef * soundRef);
	BOSound   * addNewSound(const BOSound & sound);
	BOText    * addNewText(BFontRef * fontRef);
	BOText    * addNewText(const BOText & text);
	

	// get objects number
	inline unsigned int getObjectsNumber(void){ return m_objects.size(); }
	inline unsigned int getCamerasNumber(void){ return m_cameras.size(); }
	inline unsigned int getLightsNumber(void){ return m_lights.size(); }
	inline unsigned int getEntitiesNumber(void){ return m_entities.size(); }
	inline unsigned int getSoundsNumber(void){ return m_sounds.size(); }
	inline unsigned int getTextsNumber(void){ return m_texts.size(); }

	// current camera
	inline void setCurrentCameraId(unsigned int id){ m_currentCamera = id; }
	inline unsigned int getCurrentCameraId(void){ return m_currentCamera; }
	BOCamera * getCurrentCamera(void);

	//space
	virtual inline component_space getSpace(void){ return GUI_SPACE_3D; }

	// current frame
	inline void setCurrentFrame(int currentFrame){ m_currentFrame = currentFrame; }
	inline int getCurrentFrame(void){ return m_currentFrame; }

	// get objects
	BObject3d * getObjectByName(const char * name);
	BOLight * getLightByName(const char * name);
	BOCamera * getCameraByName(const char * name);
	BOModel3d * getModelByName(const char * name);
	BOSound * getSoundByName(const char * name);
	BOText * getTextByName(const char * name);
	bool getObjectIndex(const char * name, unsigned int * id);

	inline BObject3d * getObjectByIndex(unsigned int index){ return m_objects[index]; }
	inline BOLight * getLightByIndex(unsigned int index){ return m_lights[index]; }
	inline BOCamera * getCameraByIndex(unsigned int index){ return m_cameras[index]; }
	inline BOModel3d * getModelByIndex(unsigned int index){ return m_entities[index]; }
	inline BOSound * getSoundByIndex(unsigned int index){ return m_sounds[index]; }
	inline BOText * getTextByIndex(unsigned int index){ return m_texts[index]; }

	// begin / end
	void begin(void);
	void end(void);

	// physics
	void prepareCollisionShape(BOModel3d * entity);
	void prepareCollisionObject(BOModel3d * entity);
	void prepareConstraints(BOModel3d * entity);
	void preparePhysics(void);
	void updatePhysics(void);

	// update
	virtual void update(void);

	// behaviors
	void updateObjectsBehaviors(void);
	void drawObjectsBehaviors(void);
	
	// update objects
	void updateObjectsMatrices(void);

	// draw
	void draw(BOCamera * camera);
};


#endif