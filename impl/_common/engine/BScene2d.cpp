#include <Bizarre.h>

BScene2d::BScene2d(){
    mainCamera2d = addNewCamera();
    mainCamera2d->enableOrtho(true);
    mainCamera2d->setFov(100.0f);
    mainCamera2d->setPosition( BVector3f(0.f, 0.f, 50.f) );
    mainCamera2d->setEulerRotation( BVector3f(0.f, 0.f, 0.f) );
}


BVector3f BScene2d::positionRelativeToAbsolute2D(BVector2f relative, bool screenRatio, float depth ) const {
    BSystemContext * system = Bizarre::getInstance()->getSystemContext();
    
    BVector3f absolute;
    if(screenRatio){
        unsigned int width, height;
        system->getScreenSize(&width, &height);
        float ratio = (float)width/(float)height;
        absolute.x = mainCamera2d->getPosition().x + (relative.x - 0.5f)  * mainCamera2d->getFov() * ratio;
    }else{
        absolute.x = mainCamera2d->getPosition().x + (relative.x - 0.5f)  * mainCamera2d->getFov();
    }
     // multiply Y by the ortho Fov and the screen ratio
    absolute.y = mainCamera2d->getPosition().y - (relative.y - 0.5f) * mainCamera2d->getFov(); // multiply Y by the ortho Fov 
    absolute.z = depth;
    
    return absolute;
}


BVector2f BScene2d::positionAbsoluteToRelative2D(BVector3f absolute, bool screenRatio, float depth ) const {

    BSystemContext * system = Bizarre::getInstance()->getSystemContext();
    
    BVector2f relative;
    if(screenRatio){
        unsigned int width, height;
        system->getScreenSize(&width, &height);
        float ratio = (float)width/(float)height;
        relative.x =  (absolute.x - mainCamera2d->getPosition().x ) / ( mainCamera2d->getFov() * ratio);
    }else{
        relative.x =  (absolute.x - mainCamera2d->getPosition().x ) / mainCamera2d->getFov();
    }
    
    relative.y = ( absolute.y + mainCamera2d->getPosition().y ) / mainCamera2d->getFov();
    
    
    return relative;
}

BVector3f BScene2d::scaleRelativeToAbsolute2D(BVector2f relative, bool screenRatio, float depth) const {
    float ratio = 1.0f;

    BVector3f absolute;
    if(screenRatio){
        BSystemContext * system = Bizarre::getInstance()->getSystemContext();
    
        unsigned int width, height;
        system->getScreenSize(&width, &height);
        float ratio = (float)width/(float)height;
    }

    absolute.x = mainCamera2d->getPosition().x + relative.x  * mainCamera2d->getFov() * ratio;    
    absolute.y = mainCamera2d->getPosition().y - relative.y * mainCamera2d->getFov() * ratio; // multiply Y by the ortho Fov 
    absolute.z = depth;
    
    return absolute;
}
