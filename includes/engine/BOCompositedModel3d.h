/*

*/

#ifndef _B_OCOMPOSITEDMODEL_H
#define _B_OCOMPOSITEDMODEL_H

#include <vector>
#include <algorithm>
#include <BMeshTools.h>


/*
    -agregar un id  de posicion en la submalla a submesh 
    -trabajar la parte de materiales texturas y displays
    -ver que posibilidades independientes hay para una submalla, animaciones por ejemplo
    -la posibilidad de generar una submalla ligada a una parte de la malla compuesta
    -buscar una forma de trabajar el skin y los armatures(ya pensado)
*/

class BOCompositedModel3d;

class BOCompositedModel3dSubMesh{
private:
    // mesh data
    BSubMesh * m_subMesh;
    BSubMesh * m_physicsSubMesh;
    BOCompositedModel3d * m_target;

private:
    // transform
    BVector3f m_position;
    BVector3f m_rotation;
    BVector3f m_scale;

private:
    // baked mesh functions
    unsigned int onBakedVerticesPosition ;
    unsigned int onBakedNormalsPosition  ;
    unsigned int onBakedTangentsPosition ;
    unsigned int onBakedTexCoordsPosition;
    unsigned int onBakedIndicesPosition  ;

    // baked physics mesh functions
    unsigned int onBakedPVerticesPosition ;
    unsigned int onBakedPNormalsPosition  ;
    unsigned int onBakedPTangentsPosition ;
    unsigned int onBakedPIndicesPosition  ;

    friend class BOCompositedModel3d;

public:
    BOCompositedModel3dSubMesh( BOCompositedModel3d * target, BSubMesh * subMesh, const BVector3f & position = BVector3f() );
    
    //SubMesh
    inline void setSubMesh( BSubMesh * subMesh ){ m_subMesh = subMesh; }
    inline void setPhysicsSubMesh( BSubMesh * subMesh ){ m_physicsSubMesh = subMesh; }
    inline BSubMesh* getSubMesh(void){ return m_subMesh; }
    inline BSubMesh* getPhysicsSubMesh(void){ return m_physicsSubMesh; }


    // transformations
    inline void setPosition( const BVector3f & position ){ m_position = position; }
    inline BVector3f getPosition( void ){ return m_position; }

    inline void setScale(const BVector3f & scale){ m_scale = scale; }
    inline BVector3f getScale(void) const { return m_scale; }

    inline BVector3f getEulerRotation(void) const { return m_rotation; }
    inline void setEulerRotation(const BVector3f & euler){ m_rotation = euler; }

};


class M_ENGINE_EXPORT BOCompositedModel3d : public BOModel3d{
private:
    std::vector<BOCompositedModel3dSubMesh*> m_cSubMeshs;


private:
    void setMeshRef(BMeshRef * meshRef, BMeshRef * physicsMeshRef = NULL){ BOModel3d::setMeshRef(meshRef, physicsMeshRef ); }

    void bakeMeshs(void);
    void bakePhysicsMeshs(void);

public:
    BOCompositedModel3d(void);

    // composite submesh
    inline BOCompositedModel3dSubMesh * addCompositeSubMesh( BSubMesh * subMesh, const BVector3f & position = BVector3f() )
        { BOCompositedModel3dSubMesh * ncSubMesh = new BOCompositedModel3dSubMesh( this, subMesh, position ); m_cSubMeshs.push_back( ncSubMesh ); return ncSubMesh; }

    inline BOCompositedModel3dSubMesh * getCompositeSubMesh( unsigned int Id ) \
        { return m_cSubMeshs[ min( (unsigned int)Id, (unsigned int)m_cSubMeshs.size() ) ]; }

    void bake();

    //void AsyncBake(void){}
    
};


#endif