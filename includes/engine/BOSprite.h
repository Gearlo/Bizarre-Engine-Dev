#ifndef UGUIPICTURE_H
#define UGUIPICTURE_H

//#include <gui/BGuiComponent.h>
//#include <core/UMath.h>

#include <BOModel3d.h>
#include <BImplTypes.h>


// TODO: este objeto no es nada seguro, agregar comprobaciones de valores nulos

enum BSpriteRotate{
    SPRITE_ROTATE_NONE = 0,
    SPRITE_ROTATE_FULL,
    SPRITE_ROTATE_HALF_Z,
};

class BOSprite: public BOModel3d{
private:
    struct USpriteText{
        USpriteText(void);
        BOText* object;
        
        char text[256];
        float size;
        bool adjust;
        
        gui_align hAlign;
        gui_align vAlign;
        
        BVector3f position_offset;
    };
    
private:
    BVector3f size;
    unsigned int tiles_M, tiles_N, currentTile;

    bool isUpdateNeeded;
    BList<USpriteText*>* texts;
    BScene * scene;

    //rotation
    BSpriteRotate rotateToCamera;

public:
    BOSprite(BScene * scene, BTextureRef* image, float width = 0.1f, bool centered = false);

    inline gui_object_type getGuiObjecType(void){ return GUI_PICTURE; }

    // text
    unsigned int addText( BFontRef* font, const char* Text = "" );
    
    inline void setText(char* text){  setText(text, 0u); };
    inline void setText(char* text, unsigned int id){ if(this->texts){ strcpy(texts->get(id)->text, text) /*= text*/; isUpdateNeeded =true; } }

    void setTextAdjust( bool adjust, unsigned int id = 0u ){ if(texts){ texts->get(id)->adjust = adjust; isUpdateNeeded = true;}  } 
    void setTextPositionOffset( const BVector3f & offset, unsigned int id = 0u ){ if(texts){ texts->get(id)->position_offset = offset; isUpdateNeeded = true;}  }
    void setTextSize(float size){ setTextSize(size, 0u); }
    void setTextSize(float size, unsigned int id){ if(texts){ texts->get(id)->size = size; isUpdateNeeded = true;} }
    void setTextColor( const BVector4f & color, unsigned int id = 0u ){ texts->get(id)->object->setColor(color); }


    //inline void setAlign( U_ALIGN_MODES aling ){ setHAling((gui_align)aling, 0u); }
    inline void setHAling( gui_align aling, unsigned int id = 0u){ if(texts){ texts->get(id)->hAlign = aling; isUpdateNeeded = true;} }
    inline void setVAling( gui_align aling, unsigned int id = 0u){ if(texts){ texts->get(id)->vAlign = aling; isUpdateNeeded = true;} }
    
    
    
    // tiles
    void setTilesNumber(unsigned int M, unsigned int N);
    void setTile(unsigned int tile);
    inline void setVisibility(bool visibility){ if(visibility) setVisible(true); else setInvisible(true); }
    
    
    //inline MBox3d * getBoundingBox(void){ plane->getBoundingBox(); };
    inline void setColor( const BVector3f & color){ getMesh()->getMaterial(0u)->setEmit( color ); }
    inline BVector3f getColor(void){ return getMesh()->getMaterial(0u)->getEmit(); }
    //inline const char* getText(void){ return ""; }
    inline unsigned int getTilesNumber(void){ return tiles_M * tiles_N; }
    inline unsigned int getTile(void){ return currentTile; }
    inline bool getVisibility(void){ if( isInvisible() ) return false; else return true; } //TODO: que feo esto
    
    // Transformations
    inline BVector3f getAbsoluteSize(void){ return size; }
    inline BSpriteRotate getRotationType(void){ return rotateToCamera; }

    void setPosition(const BVector3f & position);
    inline void setEulerRotation(const BVector3f & euler){ if(rotateToCamera == SPRITE_ROTATE_NONE) BObject3d::setEulerRotation( euler ); }
    inline void setRotationType( BSpriteRotate rotationType ){ rotateToCamera = rotationType; }

    inline bool needUpdateGui(){ return isUpdateNeeded; }
    void updateGui(void);
    void update(void);
};

#endif /* UGUIPICTURE_H */

