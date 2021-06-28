#ifndef _U_SCENE_2D_H
#define _U_SCENE_2D_H


#include <BScene.h>

class M_ENGINE_EXPORT BScene2d : public BScene{
public:
    BScene2d(void);

private:
    BOCamera * mainCamera2d;


public:
    BVector3f positionRelativeToAbsolute2D(BVector2f relative, bool screenRatio = false, float depth = .0f ) const;
    BVector2f positionAbsoluteToRelative2D(BVector3f absolute, bool screenRatio = false, float depth = .0f ) const;
    BVector3f    scaleRelativeToAbsolute2D(BVector2f relative, bool screenRatio  = false, float depth  = .0f ) const;

    //space
	inline component_space getSpace(void){ return GUI_SPACE_2D; }
    
    //void update(void)
};

#endif