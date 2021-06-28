#include <Bizarre.h>

void BRenderInfo::changeRenderer(const char * name){
	Bizarre * engine = Bizarre::getInstance();
	BRendererManager * rendererManager = engine->getRendererManager();

	BRendererCreator * renderer = rendererManager->getRendererByName(name);
	if(renderer)
	{
		if(engine->getRenderer())
			engine->getRenderer()->destroy();
		engine->setRenderer( renderer->getNewRenderer() );
	}
}