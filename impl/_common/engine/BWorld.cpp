#include <Bizarre.h>

BWorld::BWorld():
m_currentSceneId(0),
m_requestedSceneId(0xFFFFFFFF),
sceneLayersConfig( SCENE_LAYERS_NONE ) //eliminar
{
//	scene_world = new BScene();
//	scene_gui = new BScene2d();

//	m_scenes.push_back(scene_world);
//	m_scenes.push_back(  scene_gui);
	for(int i = 0; i < SCENE_LAYERS_NUMBER; i++)
		sceneLayers[i] = NULL;

}



void BWorld::configureScenes( BSceneLayersConfig layers ){ //TODO: si ya existe una configuracion deben limpiearse // modificar
	sceneLayersConfig = layers;
	switch(sceneLayersConfig){
		case SCENE_LAYERS_SKY1_WORLD2_GUI3:{
			sceneLayers[SCENE_LAYER_SKY] = new BScene();   // sky
			sceneLayers[SCENE_LAYER_WORLD] = new BScene();   // world
			sceneLayers[SCENE_LAYER_GUI] = new BScene2d(); // gui

			m_scenes.push_back( sceneLayers[SCENE_LAYER_SKY] );
			m_scenes.push_back( sceneLayers[SCENE_LAYER_WORLD] );
			m_scenes.push_back( sceneLayers[SCENE_LAYER_GUI] );

			sceneLayers[SCENE_LAYER_SKY]->addNewCamera();
			sceneLayers[SCENE_LAYER_WORLD]->addNewCamera();
			BOCamera * camera = sceneLayers[SCENE_LAYER_GUI]->addNewCamera();
		} break;

		case SCENE_LAYERS_WORLD1_GUI2:{
			sceneLayers[SCENE_LAYER_SKY] =           NULL; // sky
			sceneLayers[SCENE_LAYER_WORLD] = new   BScene(); // world
			sceneLayers[SCENE_LAYER_GUI] = new BScene2d(); // gui

			m_scenes.push_back( sceneLayers[  SCENE_LAYER_WORLD] );
			m_scenes.push_back( sceneLayers[  SCENE_LAYER_GUI] );

			//sceneLayers[  SCENE_LAYER_SKY]->addNewCamera();
			sceneLayers[SCENE_LAYER_WORLD]->addNewCamera();
			sceneLayers[SCENE_LAYER_GUI]->addNewCamera();
		} break;
	}
}


BScene * BWorld::addNewSceneToLayer( BSceneLayer layer ){
	if( !(layer < SCENE_LAYERS_NUMBER) )
		return NULL;

	if( sceneLayers[layer] ){
		//TODO: limpiar la escena y destruirla
	}
	sceneLayers[layer] = addNewScene();
	return sceneLayers[layer];
}

BScene * BWorld::addNewScene2dToLayer( BSceneLayer layer ){
	if( !(layer < SCENE_LAYERS_NUMBER) )
		return NULL;

	if( sceneLayers[layer] ){
		//TODO: limpiar la escena y destruirla
	}
	sceneLayers[layer] = addNewScene();
	return sceneLayers[layer];
}

BScene * BWorld::addNewScene(void)
{
	BScene * scene = new BScene();
	m_scenes.push_back(scene);
	return scene;
}

BScene * BWorld::addNewScene2d(void)
{
	BScene * scene = new BScene2d();
	m_scenes.push_back(scene);
	return scene;
}

void BWorld::clearScenes(void)
{
	unsigned int i;
	unsigned int sSize = getScenesNumber();
	for(i=0; i<sSize; i++)
		SAFE_DELETE(m_scenes[i]);

	m_currentSceneId = 0;
	m_scenes.clear();
}


void BWorld::setCurrentSceneId(unsigned int id)
{
	BAssetsManager * assetsManager = Bizarre::getInstance()->getAssetsManager();
	if(!assetsManager)
		return;


	if(id == m_currentSceneId)
	{
		assetsManager->updateQueueDatas();
		return;
	}

	// previous scene
	BScene * scene = getCurrentScene();
	if(scene->getDataMode() == M_DATA_DYNAMIC || scene->getDataMode() == M_DATA_STREAM)
	{
		// meshs
		unsigned int i;

		unsigned int eSize = scene->getEntitiesNumber();
		for(i=0; i<eSize; i++)
		{
			BOModel3d * entity = scene->getModelByIndex(i);
			BMesh * mesh = entity->getMesh();
			if(mesh)
			{
				// textures
				unsigned int t;
				unsigned int tSize = mesh->getTexturesNumber();
				for(t=0; t<tSize; t++)
				{
					BTextureRef * ref = mesh->getTexture(t)->getTextureRef();
					assetsManager->decrDataRefScore(ref);
				}

				// armature anim
				{
					BArmatureAnimRef * ref = mesh->getArmatureAnimRef();
					assetsManager->decrDataRefScore(ref);
				}

				// textures anim
				{
					BTexturesAnimRef * ref = mesh->getTexturesAnimRef();
					assetsManager->decrDataRefScore(ref);
				}

				// materials anim
				{
					BMaterialsAnimRef * ref = mesh->getMaterialsAnimRef();
					assetsManager->decrDataRefScore(ref);
				}
			}

			// mesh
			BMeshRef * ref = entity->getMeshRef();
			assetsManager->decrDataRefScore(ref);

		}

		// sounds
		unsigned int sSize = scene->getSoundsNumber();
		for(i=0; i<sSize; i++)
		{
			BOSound * sound = scene->getSoundByIndex(i);
			BSoundRef * ref = sound->getSoundRef();
			assetsManager->decrDataRefScore(ref);
		}

		// clear queue data
		assetsManager->clearQueueDatas();
	}

	// change current id
	m_currentSceneId = id;

	// next scene
	scene = getCurrentScene();
	if(scene->getDataMode() == M_DATA_DYNAMIC || scene->getDataMode() == M_DATA_STREAM)
	{
		// meshs
		unsigned int i;

		unsigned int eSize = scene->getEntitiesNumber();
		for(i=0; i<eSize; i++)
		{
			BOModel3d * entity = scene->getModelByIndex(i);
			BMesh * mesh = entity->getMesh();
			if(mesh)
			{
				// textures
				unsigned int t;
				unsigned int tSize = mesh->getTexturesNumber();
				for(t=0; t<tSize; t++)
				{
					BTextureRef * ref = mesh->getTexture(t)->getTextureRef();
					assetsManager->incrDataRefScore(ref);
				}

				// armature anim
				{
					BArmatureAnimRef * ref = mesh->getArmatureAnimRef();
					assetsManager->incrDataRefScore(ref);
				}

				// textures anim
				{
					BTexturesAnimRef * ref = mesh->getTexturesAnimRef();
					assetsManager->incrDataRefScore(ref);
				}

				// materials anim
				{
					BMaterialsAnimRef * ref = mesh->getMaterialsAnimRef();
					assetsManager->incrDataRefScore(ref);
				}
			}

			// mesh
			BMeshRef * ref = entity->getMeshRef();
			assetsManager->incrDataRefScore(ref);
		}

		// sounds
		unsigned int sSize = scene->getSoundsNumber();
		for(i=0; i<sSize; i++)
		{
			BOSound * sound = scene->getSoundByIndex(i);
			BSoundRef * ref = sound->getSoundRef();
			assetsManager->incrDataRefScore(ref);
		}
	}

	// updateQueueData
	assetsManager->updateQueueDatas();
}

void BWorld::changeCurrentScene(unsigned int id)
{
	m_requestedSceneId = id;
}

void BWorld::changeCurrentSceneIfRequested()
{
	if(m_requestedSceneId == 0xFFFFFFFF)
		return;

	if(m_requestedSceneId != m_currentSceneId)
	{
		Bizarre * engine = Bizarre::getInstance();

		if(m_requestedSceneId < getScenesNumber())
		{
			BScene * scene = getCurrentScene();

			// onEndScene
			BGame * game = engine->getGame();
			if(game)
				game->onEndScene();

			// change scene
			setCurrentSceneId(m_requestedSceneId);
			scene = getCurrentScene();

			// onBeginScene
			if(game)
				game->onBeginScene();
		}
	}

	m_requestedSceneId = 0xFFFFFFFF; // reset requested scene
}

void BWorld::deleteScene(unsigned int id)
{
	SAFE_DELETE(m_scenes[id]);
	m_scenes.erase(m_scenes.begin() + id);

	unsigned int sSize = getScenesNumber();
	if(sSize == 0)
	{
		m_currentSceneId = 0;
		return;
	}

	unsigned int maxId = (unsigned int)((int)getScenesNumber() - 1);
	if(m_currentSceneId > maxId)
		m_currentSceneId = maxId;
}

//Todo: eliminar esta funci[on]
BScene * BWorld::getCurrentScene(void)
{
	unsigned int sSize = getScenesNumber();
	if(m_currentSceneId < sSize)
		return m_scenes[m_currentSceneId];

	return NULL;
}

BScene * BWorld::getSceneByName(const char * name)
{
	unsigned int i;
	unsigned int sSize = getScenesNumber();
	for(i=0; i<sSize; i++)
	{
		if(! strcmp(name, m_scenes[i]->getName()))
			return m_scenes[i];
	}

	return NULL;
}

bool BWorld::getSceneIndexByName(const char * name, unsigned int * index)
{
	unsigned int i;
	unsigned int sSize = getScenesNumber();
	for(i=0; i<sSize; i++)
	{
		if(! strcmp(name, m_scenes[i]->getName()))
		{
			(*index) = i;
			return true;
		}
	}

	return false;
}

void BWorld::update(){

	if( sceneLayersConfig = SCENE_LAYERS_SKY1_WORLD2_GUI3 ){
		getSkyScene()->getCurrentCamera()->setEulerRotation( getWorldScene()->getCurrentCamera()->getEulerRotation() );
	}

}