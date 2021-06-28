#ifndef _U_WORLD_H_
#define _U_WORLD_H_

//#include  <Bizarre.h>


enum BSceneLayersConfig{
	SCENE_LAYERS_NONE,
	SCENE_LAYERS_SKY1_WORLD2_GUI3,
	SCENE_LAYERS_WORLD1_GUI2,
	SCENE_LAYERS_CUSTOM
};

enum BSceneLayer{
	SCENE_LAYER_SKY = 0u,
	SCENE_LAYER_WORLD = 1u,
	SCENE_LAYER_GUI = 2u,
	SCENE_LAYER_4 = 3u,
	SCENE_LAYER_5 = 4u,

	SCENE_LAYERS_NUMBER = 5u
};

//#define SCENES_LAYERS_NUMBER 3u

class M_ENGINE_EXPORT BWorld{
private:
    // scenes
	unsigned int		m_currentSceneId;
	unsigned int		m_requestedSceneId;
	
	
	BScene2d* scene_gui;
	BScene* scene_world;

	vector <BScene *>	m_scenes; // es necesario?
	BScene * sceneLayers[SCENE_LAYERS_NUMBER];
	
	BSceneLayersConfig sceneLayersConfig;

public:
	BWorld(void);
	//TODO: falta destructor

public: //new in Bizarre
	void configureScenes( BSceneLayersConfig layers = SCENE_LAYERS_SKY1_WORLD2_GUI3 );

	//Layers
	inline BSceneLayersConfig getSceneLayersConfig(void){ return sceneLayersConfig; }
	
	inline      BScene**       getSceneLayers(void){ return          sceneLayers; }
		         BScene*   addNewSceneToLayer( BSceneLayer layer );
	    	     BScene* addNewScene2dToLayer( BSceneLayer layer );
	inline  unsigned int getSceneLayersNumber(void){ return  SCENE_LAYERS_NUMBER; }
	inline       BScene* getSceneByLayer(BSceneLayer layer){ return ( layer < SCENE_LAYERS_NUMBER)? sceneLayers[layer] : NULL; }
	inline         void    setSceneLayer(BSceneLayer layer, BScene * scene ){ if(layer < SCENE_LAYERS_NUMBER) sceneLayers[layer] = scene; }
	inline         void    setSceneLayer(BSceneLayer layer, unsigned int sceneId ){ if(layer < SCENE_LAYERS_NUMBER) sceneLayers[layer] = getSceneByIndex(sceneId); }
	//inline unsigned int getSceneLayersNumber(void){ return sceneLayersNumber; }



	inline BScene * getWorldScene(void){     return sceneLayers[SCENE_LAYER_WORLD]; } // eliminar
	inline BScene *   getGuiScene(void){     return sceneLayers[SCENE_LAYER_GUI]; } // eliminar
	inline BScene *   getSkyScene(void){     return sceneLayers[SCENE_LAYER_SKY]; } // eliminar

public:
	void clearScenes(void);

	void changeCurrentSceneIfRequested();

    // scenes
	void changeCurrentScene(unsigned int id); // does not change scene straight away, instead it requests to do it
	void deleteScene(unsigned int id);
	bool getSceneIndexByName(const char * name, unsigned int * index);
	
	BScene * addNewScene(void);
	BScene * addNewScene2d(void);
	BScene * getSceneByName(const char * name);
	BScene * getCurrentScene(void);
	void setCurrentSceneId(unsigned int id);
	inline unsigned int getCurrentSceneId(void){ return m_currentSceneId; }
	inline unsigned int getScenesNumber(void){ return m_scenes.size(); }
	inline BScene * getSceneByIndex(unsigned int id){ return m_scenes[id]; }

	void update(void);
};


#endif