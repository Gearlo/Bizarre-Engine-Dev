#include <Bizarre.h>
#include <BGameWinEvents.h>
#include <BInput.h>
#include <BStandardRenderer.h>
#include <BFixedRenderer.h>
#include <BWindow.h>

// Contexts
#include <BALContext.h>
#include <BGLContext.h>
#include <BBulletContext.h>
#include <BTTheadingContext.h>
#include <BWinContext.h>


#include <BLoaders.h>
//#include <BMeshLoad.h>

#include <BPackageManagerNPK.h>

//#include <MyGame.h>
struct threadArgs{
    int argc; 
    char** argv;
    threadArgs( int argc, char* argv[] ){ this->argc = argc; this->argv = argv; }
};

void * BizarreMainThread( void * _args ){
    threadArgs * args = (threadArgs*)_args;
    char * workingDir = (args->argc > 1)? args->argv[1]: (char*)BWindow::getInstance()->getWorkingDirectory();

    std::cout << workingDir << std::endl;

    Bizarre* engine = Bizarre::getInstance();    
    engine->setWorkingDir(workingDir);

    delete args;

    BScriptContext* python = BScriptContext::getInstance();
    python->initializeContext();

    python->run_string("import startup");

    return NULL;
}


int BizarreMain(int argc, char* argv[]){

    //BizarreMainThread( (void*)( new threadArgs(argc, argv) ) );
    BTThreadingContext * threading = BTThreadingContext::getInstance();
    
    threading->createThread( BizarreMainThread, (void*)( new threadArgs(argc, argv)), THREAD_MAIN );
    threading->waitThread( THREAD_MAIN );

    return 0;
}



void windowEvents(MWinEvent * windowEvents);
inline void Update(void)
{
    BGame * game = Bizarre::getInstance()->getGame();
    if( game && game->isRunning() )
        game->update();		
}


inline void Draw(void)
{
	BWindow* window = BWindow::getInstance();
        
	Bizarre * engine = Bizarre::getInstance();
	BRenderingContext * render = engine->getRenderingContext();
	BGame * game = engine->getGame();

	// set basic viewport
	render->disableScissorTest();
	render->setViewport(0, 0, window->getWidth(), window->getHeight());

	if( game && game->isRunning() )	
            game->draw();
	
	window->swapBuffer();
}


void Bizarre::start( BStartConfig startConfig ){
  //BStartConfig* config = new BStartConfig();
  //config->setScreen( 800u, 600u, false, "Maratis Port");

  //if( startFunction )
  //    startFunction( config );

  BWindow* window = BWindow::getInstance();
  BRenderInfo * renderInfo = BRenderInfo::getInstance();

  //if(argc > 1){ window->setWorkingDirectory(argv[1]); };

  window->setWorkingDirectory( m_workingDir );
  window->setPointerEvent(windowEvents); // window events 
  window->create( startConfig.window_title, startConfig.window_width, startConfig.window_height, 32u, startConfig.window_fullscreen );

      setInputContext( new         BInput() );
  setRenderingContext( new     BGLContext() );
     setSystemContext( new    BWinContext() );
    setPhysicsContext( new BBulletContext() );
     setScriptContext( new BScriptContext() );
      setSoundContext( new     BALContext() );
  setThreadingContext( BTThreadingContext::getInstance() );
  setLevel( new BAssetsManager() );
    //setGame( new MyGame() );


  m_assetsManager->setCurrentDir( m_workingDir ); 
  m_assetsManager->setTempDir( (char*)window->getTempDirectory() );

  getImageLoader()->addLoader(B_loadImage); // image loader

  //fonts loaders
  getFontLoader()->addLoader(B_loadFont);
  getFontLoader()->addLoader(B_loadBinFont);

  getMeshLoader()->addLoader(xmlMeshLoad); 
  //engine->getMeshLoader()->addLoader(M_loadBinMesh);
  getArmatureAnimLoader()->addLoader(xmlArmatureAnimLoad);
  //engine->getArmatureAnimLoader()->addLoader(M_loadBinArmatureAnim );
  getTexturesAnimLoader()->addLoader(xmlTextureAnimLoad);
  //engine->getTexturesAnimLoader()->addLoader(M_loadBinTexturesAnim);	
  getMaterialsAnimLoader()->addLoader(xmlMaterialAnimLoad);
  //engine->getMaterialsAnimLoader()->addLoader(M_loadBinMaterialsAnim);

  getSoundLoader()->addLoader(B_loadModMusic);
  getSoundLoader()->addLoader(B_loadWavSound);
  //getSoundLoader()->addLoader(B_loadSound);

  // add renderers
  getRendererManager()->addRenderer(BStandardRenderer::getStaticName(), BStandardRenderer::getNew);
  getRendererManager()->addRenderer(BFixedRenderer::getStaticName(), BFixedRenderer::getNew);

  // package manager
  setPackageManager( new BPackageManagerNPK() );
  getPackageManager()->init();
  //BPackage pack = getPackageManager()->loadPackage( "/home/ariel/utopianenginedev/data/test.npk" );
  //BPackageEnt ent = getPackageManager()->addFileToPackage("/home/ariel/utopianenginedev/data/music/funky_trousers.mod", pack, "funky_trousers.mod");
  //getPackageManager()->closePackage(pack);

  //BRenderer * renderer = getRendererManager()->getRendererByName( "StandardRenderer" )->getNewRenderer();
  setRenderer( getRendererManager()->getRendererByName( startConfig.renderer_name )->getNewRenderer() );

  //m_scriptContext->initializeContext();
  m_world = new BWorld();

  setGame( startConfig.game ); // automatic game begin() call
  //m_game->begin();

  // time
  unsigned int frequency = renderInfo->maxFps;
  unsigned long previousFrame = 0u;
  unsigned long startTick = window->getSystemTick();

  	// on events
	while(window->isActive())
	{
		// on events
		if(window->onEvents())
		{
			// compute target tick
			unsigned long currentTick = window->getSystemTick();

			unsigned long tick = currentTick - startTick;
			unsigned long frame = (unsigned long)(tick * (frequency * 0.001f));

			// update elapsed time
			unsigned int i;
			unsigned int steps = (unsigned int)(frame - previousFrame);

			if(window->getFocus())
			{
				// don't wait too much
				if(steps >= (frequency/2))
				{
					Update();
					Draw();
					previousFrame += steps;
					continue;
				}

				// update
				for(i=0; i<steps; i++)
				{
					Update();
					previousFrame++;
				}

				// draw
				if(steps > 0){
					Draw();
				}
			}
			else
			{
				previousFrame = frame;
				window->swapBuffer();
			}
		}
	}  
      

  //ULog(5, "ending game...");
  m_game->end();

  //ULog(5, "destroying renderer...");
  //renderer->destroy();

    //<-- falla al intentar borrar el game
  //SAFE_DELETE(m_world);

  //SAFE_DELETE(m_renderingContext);
  SAFE_DELETE( m_soundContext );
  //SAFE_DELETE(m_physicsContext);

  //SAFE_DELETE(m_scriptContext);
  //SAFE_DELETE(m_inputContext);
  //SAFE_DELETE(m_systemContext);
}





void windowEvents(MWinEvent * windowEvents)
{
    //std::cout << "windowEvents(...)" std::endl;
    

	Bizarre * engine = Bizarre::getInstance();

	// game
	BGame * game = engine->getGame();
	if(game)
	{
		if(game->isRunning()){
			gameWinEvents(windowEvents);
		}
	}

	if(windowEvents->type == MWIN_EVENT_KEY_DOWN && windowEvents->data[0] == BKey_ESCAPE){
		BWindow::getInstance()->setActive(false);
	}

	if(windowEvents->type == MWIN_EVENT_WINDOW_CLOSE){
		BWindow::getInstance()->setActive(false);
	}
    
}