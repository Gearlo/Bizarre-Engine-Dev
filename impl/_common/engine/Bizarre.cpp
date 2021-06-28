/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// Bizarre.cpp
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


BStartConfig::BStartConfig():
game(NULL),
window_width(800u),
window_height(600u),
window_fullscreen(false),
window_title("Bizarre Engine"),
renderer_name("FixedRenderer")
{


}

Bizarre::Bizarre():
m_isActive(true),
m_assetsManager(NULL),
m_game(NULL),
m_renderer(NULL),
m_soundContext(NULL),
m_renderingContext(NULL),
m_physicsContext(NULL),
m_scriptContext(NULL),
m_inputContext(NULL),
m_systemContext(NULL),
m_packageManager(NULL),
m_requestedLevelToLoad(NULL),
m_workingDir(NULL)
{}

Bizarre::~Bizarre(void)
{
	SAFE_FREE(m_requestedLevelToLoad);
}

Bizarre * Bizarre::getInstance()
{
	static Bizarre m_instance;
	return &m_instance;
}

void Bizarre::setRenderingContext(BRenderingContext * renderingContext)
{
	m_renderingContext = renderingContext;
}

void Bizarre::setSoundContext(BSoundContext * soundContext)
{
	m_soundContext = soundContext;
}

void Bizarre::setPhysicsContext(BPhysicsContext * physicsContext)
{
	m_physicsContext = physicsContext;
}

void Bizarre::setScriptContext(BScriptContext * scriptContext)
{
	m_scriptContext = scriptContext;
}

void Bizarre::setInputContext(BInputContext * inputContext)
{
	m_inputContext = inputContext;
}

void Bizarre::setSystemContext(BSystemContext * systemContext)
{
	m_systemContext = systemContext;
}

void Bizarre::setThreadingContext(BThreadingContext * threadingContext){
	m_threadingContext = threadingContext;
}

void Bizarre::setPackageManager(BPackageManager * packageManager)
{
	m_packageManager = packageManager;
}

void Bizarre::setLevel(BAssetsManager * level)
{
	m_assetsManager = level;
}

void Bizarre::updateRequests(void)
{
	loadLevelIfRequested();
	if(m_world)
		m_world->changeCurrentSceneIfRequested();
}

bool Bizarre::loadLevel(const char * filename)
{
	if(! filename)
		return false;

	if(! m_world)
		return false;

	char globalFilename[256];
	getGlobalFilename(globalFilename, m_systemContext->getWorkingDirectory(), filename);

	// Check if there is a level under the given name
	if(! isFileExist(globalFilename))
		return false;

	if(m_game)
	{
		if(m_game->isRunning())
		{
			m_game->onEndScene();
			m_game->onEndLevel();
		}
	}

	if(m_levelLoader.loadData(globalFilename, m_assetsManager))
	{
		if(m_game){
			if(m_game->isRunning())
			{
				m_game->onBeginLevel();
				m_game->onBeginScene();
			}
		}
		return true;
	}

	return false;
}

void Bizarre::requestLoadLevel(const char * filename)
{
	SAFE_FREE(m_requestedLevelToLoad);

	unsigned int len = strlen(filename);
	m_requestedLevelToLoad = (char*)malloc(len + 1);
	strcpy(m_requestedLevelToLoad, filename);
}

bool Bizarre::doesLevelExist(const char * filename)
{
	if(! filename)
		return false;

	char globalFilename[256];
	getGlobalFilename(globalFilename, m_systemContext->getWorkingDirectory(), filename);
	return isFileExist(globalFilename);
}

void Bizarre::setGame(BGame * game, bool restartScenes, bool restartAssets )
{	
	if( m_game ){
		m_game->end();

		if ( restartScenes ){
			BWorld * world = getWorld(); 
			world->clearScenes();
			world->configureScenes();
		}

		if ( restartAssets ){
			BAssetsManager * assets = getAssetsManager();
			assets->clear();
		}

		/*
		if ( restartScripting ){
			BScriptContext * scripting = getScriptContext();
			scripting->finalizeContext();
			scripting->initializeContext(); 
		}
		*/

		SAFE_DELETE(m_game);
	}

	m_game = game;
	game->begin();
}

void Bizarre::setRenderer(BRenderer * renderer)
{
	m_renderer = renderer;
}

void Bizarre::loadLevelIfRequested()
{
	if(m_requestedLevelToLoad == NULL)
		return;

	loadLevel(m_requestedLevelToLoad);
	SAFE_FREE(m_requestedLevelToLoad);
}
