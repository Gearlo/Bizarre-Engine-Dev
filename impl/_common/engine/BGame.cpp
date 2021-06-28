/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BGame.cpp
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

static unsigned int s_renderBufferId = 0;


BGame::BGame(void):
m_isRunning(false)
{}

BGame::~BGame(void)
{
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();

	// delete frame buffer
	if(s_renderBufferId != 0)
		render->deleteFrameBuffer(&s_renderBufferId);
}



void BGame::update(void){

	Bizarre* engine = Bizarre::getInstance();
	BWorld* world = engine->getWorld();
	BScriptContext * scriptContext = engine->getScriptContext();

	// update script
	if(scriptContext)
		scriptContext->run_method(script, "onUpdate"); 
		
	world->update();

	BScene** scenesLayers = world->getSceneLayers();

	for (int i = 0; i < world->getSceneLayersNumber(); i++) {
		if( !scenesLayers[i] ) continue;

		scenesLayers[i]->updateObjectsBehaviors();
		scenesLayers[i]->update();
		if ( i == SCENE_LAYER_WORLD ) scenesLayers[i]->updatePhysics();
		scenesLayers[i]->updateObjectsMatrices();
	}
	
	// flush input
	engine->getInputContext()->flush();
	
	// update postponed requests
	engine->updateRequests();
}


void BGame::onBegin(){
	Bizarre * engine = Bizarre::getInstance();

	BWorld * world = engine->getWorld();
	world->configureScenes();

	BScriptContext * scriptContext = engine->getScriptContext();

	// update script
	if(scriptContext)
		scriptContext->run_method(script, "onBegin");

	//////////////////////////////////
	BScene * scene = Bizarre::getInstance()->getWorld()->getWorldScene();
	BOCompositedModel3d * cModel = scene->addNewCompositedModel();

	BMeshRef * mesh = Bizarre::getInstance()->getAssetsManager()->loadMesh( "meshs/simpleCube.xml" );
}


void BGame::onBeginScene(void)
{
	// get level
	BWorld * world = Bizarre::getInstance()->getWorld();
	if(! world)
		return;

	// get current scene
	BScene * scene = world->getWorldScene();
	if(! scene)
		return;

	// begin scene
	scene->begin();
}

void BGame::onEndScene(void)
{
	Bizarre * engine = Bizarre::getInstance();
	BScriptContext * scriptContext = engine->getScriptContext();

	// update script
	if(scriptContext)
		scriptContext->run_method(script, "onEnd");

	scriptContext->decRef(script);
	
	
	engine->getPhysicsContext()->clear();

	/*// get level
	BAssetsManager * level = Bizarre::getInstance()->getAssetsManager();
	if(! level)
		return;*/

	// get world
	BWorld * world = Bizarre::getInstance()->getWorld();
	if(! world)
		return;

	if( world->getSkyScene() )
		world->getSkyScene()->end();
		
	if( world->getWorldScene() )
		world->getWorldScene()->end();

	if( world->getGuiScene() )
		world->getGuiScene()->end();

	// get current scene
	//BScene * scene = world->getCurrentScene();
	//if(! scene)
	//	return;

	// end scene
	//scene->end();
}

/*
void BGame::restart(){
	Bizarre * engine = Bizarre::getInstance();
	BAssetsManager * assets = engine->getAssetsManager();
	BWorld * world = engine->getWorld();

	world->clearScenes();
	assets->clear();
}
*/