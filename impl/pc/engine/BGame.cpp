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


void BGame::draw(void){
	Bizarre * engine = Bizarre::getInstance();
	BWorld* world = engine->getWorld();
	BRenderingContext * render = engine->getRenderingContext();
        
	render->enableDepthTest();
    
	BScene** scenesLayers = world->getSceneLayers();
	bool clearedColorBuffer = false;

	for ( int i = 0; i < world->getSceneLayersNumber(); i++) {
		if( !scenesLayers[i] ) return;
		
		BOCamera * camera = scenesLayers[i]->getCurrentCamera();
		render->setClearColor(camera->getClearColor());
		if ( !clearedColorBuffer ){
			render->clear(M_BUFFER_COLOR | M_BUFFER_DEPTH);
			clearedColorBuffer = true;
		}else
			render->clear(M_BUFFER_DEPTH);
		
		
		
		camera->enable();
		if ( i == SCENE_LAYER_WORLD ) camera->updateListener(); // la comprobacion debe ser de otra manera
		scenesLayers[i]->draw(camera);
		scenesLayers[i]->drawObjectsBehaviors();
	}
}



/*
void BGame::draw(void)
{
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();


	// get level
	BAssetsManager * level = Bizarre::getInstance()->getAssetsManager();
	if(! level)
		return;

	BWorld * world = Bizarre::getInstance()->getWorld();
	if(! world)
		return;

	// get current scene
	BScene * scene = world->getCurrentScene();
	if(! scene)
		return;


	// render to texture
	{
		unsigned int currentFrameBuffer = 0;
		render->getCurrentFrameBuffer(&currentFrameBuffer);

		int viewport[4];
		bool recoverViewport = false;

		unsigned int c, cSize = scene->getCamerasNumber();
		for(c=0; c<cSize; c++)
		{
			BOCamera * camera = scene->getCameraByIndex(c);
			
			if(camera->isActive() && camera->getRenderColorTexture())
			{
				if(! recoverViewport)
				{
					render->getViewport(viewport);
					recoverViewport = true;
				}

				BTextureRef * colorTexture = camera->getRenderColorTexture();
				BTextureRef * depthTexture = camera->getRenderDepthTexture();

				unsigned int width = colorTexture->getWidth();
				unsigned int height = colorTexture->getHeight();

				// render buffer
				if(s_renderBufferId == 0)
					render->createFrameBuffer(&s_renderBufferId);

				render->bindFrameBuffer(s_renderBufferId);

				render->enableDepthTest();

				render->attachFrameBufferTexture(M_ATTACH_COLOR0, colorTexture->getTextureId());
				if(depthTexture)
					render->attachFrameBufferTexture(M_ATTACH_DEPTH, depthTexture->getTextureId());

				render->setViewport(0, 0, width, height);
				render->setClearColor(camera->getClearColor());
				render->clear(M_BUFFER_COLOR | M_BUFFER_DEPTH);

				// draw the scene
				camera->enable();
				scene->draw(camera);

				// finish render to texture
				render->bindFrameBuffer(currentFrameBuffer);
			}
		}

		// recover viewport
		if(recoverViewport)
			render->setViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}


	// depth test
	render->enableDepthTest();

	// render scene
	if(scene->getCamerasNumber() == 0)
	{
		// draw scene with default camera
		BOCamera camera;

		render->setClearColor(camera.getClearColor());
		render->clear(M_BUFFER_COLOR | M_BUFFER_DEPTH);

		camera.enable();
		camera.updateListener();
		scene->draw(&camera);
		scene->drawObjectsBehaviors();
	}
	else
	{
		BOCamera * camera = scene->getCurrentCamera();

		// draw current scene
		if(! camera->getRenderColorTexture())
		{
			render->setClearColor(camera->getClearColor());
			render->clear(M_BUFFER_COLOR | M_BUFFER_DEPTH);

			camera->enable();
			camera->updateListener();
			scene->draw(camera);
			scene->drawObjectsBehaviors();
		}
		
		// draw scene layer
		unsigned int sceneLayerId = camera->getSceneLayer();
		if(sceneLayerId > 0 && sceneLayerId <= world->getScenesNumber())
		{
			BScene * sceneLayer = world->getSceneByIndex(sceneLayerId-1);
			BOCamera * layerCamera = sceneLayer->getCurrentCamera();
			if(layerCamera)
			{
				layerCamera->enable();
				camera = layerCamera;
			}

			// draw on top
			render->clear(M_BUFFER_DEPTH);
			sceneLayer->draw(camera);
			sceneLayer->drawObjectsBehaviors();
		}
	}
}
*/