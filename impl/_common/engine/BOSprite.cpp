#include <Bizarre.h>



BOSprite::USpriteText::USpriteText(){
    object = NULL;
    size = 8.0f;
    adjust = true;
    strcpy(text, "");// = "";
    hAlign = GUI_ALIGN_CENTER;
    vAlign = GUI_ALIGN_CENTER;
    position_offset = BVector3f();
}

/*
BOSprite::BOSprite(float width, float height, MTextureRef* image, component_space space, bool centered) : BGUIObject(NULL, space){
   texts = NULL;
   isUpdateNeeded = false;
   
   BWorld* world = BWorld::getInstance(); 
   BVector3f calculatedPosition; 
   
    if(space == GUI_SPACE_2D){
        this->scene = world->getScene_Gui();
        BGUI* gui = BGUI::getInstance();
        BVector3f calculatedScale = gui->scaleRelativeToAbsolute2D( BVector2f(width, height) );
        
        width = calculatedScale.x;
        height = calculatedScale.y;
        
        
        calculatedPosition = gui->positionRelativeToAbsolute2D( BVector2f(QUASIZERO, QUASIZERO) );
    }else
        this->scene = world->getScene_World();
   
   size = BVector2f( width, height );
   
   height = -height;
   BVector2f min;
   BVector2f max;
   if(!centered){
       min = BVector2f( .0f, -height );
       max = BVector2f( width, .0f);
   }else{
       min = BVector2f( -width / 2, -height / 2 );
       max = BVector2f(  width / 2,  height / 2 );
   }
   
   MMesh* planeMesh = BAssets::getInstance()->createPlane(min, max, image);
   MMeshRef* meshRef = new MMeshRef(planeMesh, "<image>");
   
   plane =  this->scene->addNewEntity(meshRef);
   plane->setPosition(calculatedPosition);
   object = plane;
   //setPosition( BVector2f(QUASIZERO, QUASIZERO) );
}

*/

BOSprite::BOSprite(BScene * scene, BTextureRef* image, float width, bool centered): 
BOModel3d(NULL),
rotateToCamera(SPRITE_ROTATE_NONE)
{
   this->scene = scene;
   texts = NULL;
   isUpdateNeeded = false;
   
   //BWorld* world = BWorld::getInstance(); 
   BVector3f calculatedPosition; 
   
   float height = (float)image->getHeight() / (float)image->getWidth() * width;
   
    if(scene->getSpace() == GUI_SPACE_2D){
        BScene2d * scene2d = (BScene2d*)scene;
        BVector3f calculatedScale = scene2d->scaleRelativeToAbsolute2D( BVector2f(width, height), true );
        
        width = calculatedScale.x;
        height = calculatedScale.y;
        
        
        calculatedPosition = scene2d->positionRelativeToAbsolute2D( BVector2f(QUASIZERO, QUASIZERO), true );
    }else{
        rotateToCamera = SPRITE_ROTATE_FULL;
    }
   
   size = BVector2f( width, height );
   
   height = -height;
   BVector2f min;
   BVector2f max;
   if(!centered){
       min = BVector2f( .0f, -height );
       max = BVector2f( width, .0f);
   }else{
       min = BVector2f( -width / 2, -height / 2 );
       max = BVector2f(  width / 2,  height / 2 );
   }
   
   BMesh* planeMesh = Bizarre::getInstance()->getAssetsManager()->createPlaneFromBox(min, max, image);
   BMeshRef* meshRef = new BMeshRef(planeMesh, "<image>");
   setMeshRef( meshRef );

   //plane =  this->scene->addNewModel(this);
   setPosition(calculatedPosition);
   //object = plane;
   setPosition( BVector3f(QUASIZERO, QUASIZERO, QUASIZERO) );
}



unsigned int BOSprite::addText(BFontRef* font, const char* Text){
/*    BWorld* world = BWorld::getInstance();
    
    MScene* scene;
    if( space == GUI_SPACE_2D )
        scene = world->getScene_Gui();
    else
        scene = world->getScene_World();
*/    
    if(!texts)
        texts = new BList<USpriteText*>();
    
    USpriteText* text = new USpriteText();
    
    text->object = scene->addNewText( font );
    text->object->setText( Text );
    
    strcpy(text->text, Text);
    text->object->linkTo( this );
    
    this->isUpdateNeeded = true;
    
    texts->append(text);
    
    
    
    return texts->leght() - 1u; // TODO: revisar si retorna el indice  correto
}


void BOSprite::setTilesNumber(unsigned int M, unsigned int N){
        getMesh()->getTexture(0u)->setTexScale( BVector2f( 1.f/(float)M, 1.f/(float)N ) );    
        tiles_M = M; tiles_N = N; currentTile = 1u;
        
        if( !(M == 1 && N == 1) )
            setTile( currentTile );
}

// TODO: funciona mal, el valor 0 se repite al final
void BOSprite::setTile(unsigned int tile){/*Función pendiente*/
        tile = tile == 0? 1 : tile + 1;
        currentTile = tile;
        int n,m;
        
        //if(tile < 1) tile = 1;
        
        if( tile%tiles_M == 0 )
            n = tile/tiles_M - 1;
        else
            n = tile/tiles_M;
        
        m = tile - ( n* tiles_M ) - 1;

        float displace_x, displace_y;
        
        if( tiles_M%2 > 0 ){
            int mid = (tiles_M - 1)/2;
            displace_x = m - mid;
        }else{
            float mid = (float)(tiles_M/2) - .5f;
            displace_x = (float)m - mid;
        }
        
        if( tiles_N%2 > 0 ){
            int mid = (tiles_N - 1)/2;
            displace_y = n - mid;
        }else{
            float mid = (float)(tiles_N/2) - .5f;
            displace_y = (float)n - mid;
        }
        
        getMesh()->getTexture(0u)->setTexTranslate( BVector2f(displace_x, displace_y) );
}

void BOSprite::updateGui(){
    if(!texts) {isUpdateNeeded = false; return;}
    
    texts->restart();
    USpriteText* text = texts->next();
    int i = 0;
    
    #define picHeight  abs( picBox->max.y - picBox->min.y )
    #define picWidth   abs( picBox->max.x - picBox->min.x )
    #define textHeight abs(textBox->max.y - textBox->min.y)
    #define textWidth  abs(textBox->max.x - textBox->min.x)

    #define picHeightMid  ( ( picBox->max.y + picBox->min.y ) / 2.0f )
    #define picWidthMid   ( ( picBox->max.x + picBox->min.x ) / 2.0f )
    #define textHeightMid ( ( textBox->max.y+ textBox->min.y ) / 2.0f )
    #define textWidthMid  ( ( textBox->max.x+ textBox->min.x ) / 2.0f )

    while(text){
            BBox3d* picBox = getBoundingBox();
            BBox3d* textBox = text->object->getBoundingBox();
            
            //BVector3f newPosition = BVector3f(.0f, .0f, .5f);
            BVector3f newPosition = ( scene->getSpace() == GUI_SPACE_2D )? BVector3f(.0f, .0f, .5f) : BVector3f(.0f, .0f, -.5f);
            BVector3f newRotation = ( scene->getSpace() == GUI_SPACE_2D )? BVector3f( 180.f, .0f, .0f) : BVector3f( 0.f, .0f, .0f);
            char factor = ( scene->getSpace() == GUI_SPACE_2D )? 1 : -1;

            text->object->setText( text->text );
            text->object->setSize( text->size );
            
            if(text->adjust){
                bool adjusted = false;
                while(!adjusted){
                    text->object->setSize( text->object->getSize() - 1.0f );

                    //std::cout << "text: " << textWidth << " x " << textHeight << ", pic: " << picWidth << " x " << picHeight << std::endl;
                    switch( text->vAlign ){
                        case GUI_ALIGN_CENTER:
                        case GUI_ALIGN_UP:
                        case GUI_ALIGN_DOWN:
                            if( text->hAlign == GUI_ALIGN_CENTER || text->hAlign == GUI_ALIGN_LEFT || text->hAlign == GUI_ALIGN_RIGHT )
                                adjusted = ( picHeight > textHeight ) && ( picWidth > textWidth );
                            else
                                adjusted = picHeight > textHeight;
                            break;
                        
                        case GUI_ALIGN_UP_OUTER:
                        case GUI_ALIGN_DOWN_OUTER:
                            if( text->hAlign == GUI_ALIGN_CENTER || text->hAlign == GUI_ALIGN_LEFT || text->hAlign == GUI_ALIGN_RIGHT )
                                adjusted = picWidth > textWidth;
                            else
                                adjusted = true;
                            break;
                        default:
                            adjusted = true;
                            break;
                    }
                }
            }
                
            
            switch(text->hAlign){
                case GUI_ALIGN_LEFT:
                    text->object->setAlign( U_ALIGN_LEFT );
                    newPosition.x = .0f;
                    break;
                case GUI_ALIGN_LEFT_OUTER: // ¿debería desplazar la imagen a la derecha?
                    text->object->setAlign( U_ALIGN_RIGHT );
                    newPosition.x = .0f;
                    break;
                case GUI_ALIGN_RIGHT: 
                    text->object->setAlign( U_ALIGN_RIGHT );
                    newPosition.x = picWidth;
                    break;
                case GUI_ALIGN_RIGHT_OUTER:
                    text->object->setAlign( U_ALIGN_LEFT );
                    newPosition.x = picWidth;
                    break;
                case GUI_ALIGN_CENTER:
                default:
                    text->object->setAlign( U_ALIGN_CENTER );
                    newPosition.x = picWidthMid;
                    break;
            }
            
            
            BString _text = text->text;
            switch(text->vAlign){
                case GUI_ALIGN_DOWN:
                    if ( _text.countOccurrences('\n') > 1)
                        newPosition.y = factor* ( picBox->min.y + textHeight );
                    else
                        newPosition.y = factor*picBox->min.y;
                    break;
                case GUI_ALIGN_DOWN_OUTER:
                    newPosition.y = factor*picBox->min.y - textHeight / (_text.countOccurrences('\n') + 1);
                    break;
                case GUI_ALIGN_UP: // Todo: no funciona correctamente en espacio 3d y si el sprite est[a centrado]
                    newPosition.y = picBox->max.y - textHeight / (_text.countOccurrences('\n') + 1);
                    break;
                case GUI_ALIGN_UP_OUTER: // Todo: no funciona correctamente en espacio 3d y si el sprite est[a centrado]
                    newPosition.y = picBox->max.y ;
                    break;
                case GUI_ALIGN_CENTER:
                default:
                    newPosition.y =  factor*( picBox->max.y + picBox->min.y ) / 2.0f - (textHeight / (_text.countOccurrences('\n') + 1) ) / 2.0f ;
                    break;
            }
            if ( scene->getSpace() == GUI_SPACE_3D ) newPosition.y *= -1;
            
            BVector3f newPosition_offset;
            
            if( text->position_offset.getLength() > .0f )
                if(scene->getSpace() == GUI_SPACE_2D){
                    BScene2d* scene2d = (BScene2d*)scene;
                    newPosition_offset = scene2d->positionRelativeToAbsolute2D( BVector2f( .5f + text->position_offset.x, .5f + text->position_offset.y), true );
                    newPosition_offset.z = text->position_offset.z;
                }else
                    newPosition_offset = text->position_offset;
            
            text->object->setEulerRotation( newRotation);
            text->object->setPosition( newPosition + newPosition_offset );
            
        i++;
        text = texts->next();
    }
    
    isUpdateNeeded = false;
}

void BOSprite::setPosition(const BVector3f & position){
    BVector3f calculatedPosition;
    
    if(scene->getSpace() == GUI_SPACE_2D){
        calculatedPosition = ( (BScene2d*)scene )->positionRelativeToAbsolute2D( BVector2f(position.x, position.y), true );
        calculatedPosition.z = position.z;
    }else{
        calculatedPosition = position;
    }
    
    BObject3d::setPosition(calculatedPosition); 
}

void BOSprite::update(void){ 
    if( isUpdateNeeded ) updateGui(); 

    if( scene->getSpace() == GUI_SPACE_3D && rotateToCamera != 0 ){

        BVector3f directionalVector = getPosition() - scene->getCurrentCamera()->getPosition();
        BVector3f directionXY = directionalVector;
        directionXY.z = 0.0f;
        directionXY.normalize();
        
        BVector3f directionXYZ = directionalVector;
        directionXYZ.normalize();

        float Hangle = (180.0f * acos(directionXY.x))/M_PI;
        float Vangle;
        float Oangle;

        switch( rotateToCamera ){
            case SPRITE_ROTATE_FULL:
                Vangle = - (180.0f * acos(directionXYZ.z))/M_PI;
                Hangle -= 90.0f;
                Oangle = .0f;
                if(directionXY.y < 0.0f){ Hangle = 360.0f - Hangle; }
                break;

            case SPRITE_ROTATE_HALF_Z:
                Vangle = 90.0f;
                Hangle += 90;
                Oangle = 180.0f;
                if( directionXY.y < 0.0f ) Hangle = -Hangle;
                break;
        }

        BObject3d::setEulerRotation( BVector3f(Vangle, Oangle, Hangle) );
        //setEulerRotation(BVector3f(Vangle, Oangle, Hangle));
    }

    BOModel3d::update(); 
}