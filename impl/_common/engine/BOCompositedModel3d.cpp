#include <Bizarre.h>



BOCompositedModel3dSubMesh::BOCompositedModel3dSubMesh( BOCompositedModel3d * target, BSubMesh * subMesh, const BVector3f & position ): 
onBakedVerticesPosition (0u),
onBakedNormalsPosition  (0u),
onBakedTangentsPosition (0u),
onBakedTexCoordsPosition(0u),
onBakedIndicesPosition  (0u),
onBakedPVerticesPosition(0u),
onBakedPNormalsPosition (0u),
onBakedPTangentsPosition(0u),
onBakedPIndicesPosition (0u),
m_subMesh ( subMesh     ),
m_physicsSubMesh( NULL  ),
m_position( position    ),
m_rotation( BVector3f() ),
m_scale   ( BVector3f(1.0f, 1.0f, 1.0f ) ),
m_target( target )
{}

BOCompositedModel3d::BOCompositedModel3d() : BOModel3d( NULL, NULL ){
    m_meshRef = BMeshRef::getNew( BMesh::getNew(), "compositedMesh" );
}



void BOCompositedModel3d::bake(){
    if( !m_cSubMeshs.size() )
        return;

    updateMatrix();

    bakeMeshs();
    bakePhysicsMeshs();
    
    if( m_physicsMeshRef )
        setMeshRef( m_meshRef, m_physicsMeshRef );
    else
        setMeshRef( m_meshRef );

}

void BOCompositedModel3d::bakeMeshs(){
    BMesh * newMesh = getMesh();
    newMesh->clearSubMeshs();
    
    BAssetsManager * assetsManager = Bizarre::getInstance()->getAssetsManager();

    if ( !newMesh->getTexturesNumber() ){
        newMesh->allocTextures(1);
        BTexture * texture = newMesh->addNewTexture( assetsManager->getDefaultTexture(DEFAULT_TEX_NO_TEXTURE) );
        texture->setUWrapMode(M_WRAP_REPEAT);
        texture->setVWrapMode(M_WRAP_REPEAT);
            
        texture->setTexTranslate( BVector2f(0.0f,0.0f) );
        texture->setTexScale( BVector2f(1.f, 1.f) );
        texture->setTexRotate(0.0f);
    }


    if ( !newMesh->getMaterialsNumber() ){
        newMesh->allocMaterials(1);
        BMaterial * material = newMesh->addNewMaterial();
        material->setType(1);

        material->setOpacity(1.f);
        material->setShininess(.0f);
        material->setCustomValue(.0f);
        material->setDiffuse(BVector3f(1.0f, 1.0f, 1.0f));
        material->setSpecular(BVector3f());
        material->setEmit(BVector3f(1.0f, 1.0f, 1.0f));
        material->setCustomColor(BVector3f());
            
        material->setBlendMode(M_BLENDING_NONE);

        material->allocTexturesPass(1);
        material->addTexturePass( newMesh->getTexture(0u), M_TEX_COMBINE_REPLACE, 0u );

    }


    unsigned int verticesNumber, normalsNumber, tangentsNumber, texCoordsNumber, indicesNumber ,displaysNumber;
    verticesNumber = normalsNumber = tangentsNumber = texCoordsNumber = indicesNumber = displaysNumber = 0u;

    for( int i = 0; i < m_cSubMeshs.size() ; i++ ){
        BOCompositedModel3dSubMesh * compositeSubMesh = m_cSubMeshs[i];
        BSubMesh * subMesh = compositeSubMesh-> getSubMesh();
        BVector3f position = compositeSubMesh->getPosition();

        compositeSubMesh->onBakedVerticesPosition  =  verticesNumber;
        compositeSubMesh->onBakedNormalsPosition   =   normalsNumber;
        compositeSubMesh->onBakedTangentsPosition  =  tangentsNumber;
        compositeSubMesh->onBakedTexCoordsPosition = texCoordsNumber;
        compositeSubMesh->onBakedIndicesPosition   =   indicesNumber;
 

        verticesNumber +=   subMesh->getVerticesSize();
        normalsNumber  +=    subMesh->getNormalsSize();
        tangentsNumber +=   subMesh->getTangentsSize();
        texCoordsNumber+=  subMesh->getTexCoordsSize();
        indicesNumber  +=    subMesh->getIndicesSize();
        displaysNumber += subMesh->getDisplaysNumber();
    }

    BSubMesh * newSubMeshs = newMesh->allocSubMeshs(1);

    BVector3f * vertices  = newSubMeshs->allocVertices ( verticesNumber );
	BVector3f * normals   = newSubMeshs->allocNormals  ( verticesNumber );
	BVector3f * tangents  = newSubMeshs->allocTangents ( verticesNumber );
	BVector2f * texCoords = newSubMeshs->allocTexCoords( verticesNumber );
    void      * indices   = newSubMeshs->allocIndices  ( indicesNumber, ( indicesNumber >= USHRT_MAX - 1 )? U_UINT : U_USHORT );

    for( int i = 0; i < m_cSubMeshs.size() ; i++ ){
        BOCompositedModel3dSubMesh * compositeSubMesh = m_cSubMeshs[i];
        BSubMesh * subMesh = compositeSubMesh-> getSubMesh();
        
        BVector3f position = compositeSubMesh->getPosition();
        BVector3f rotation = compositeSubMesh->getEulerRotation();
        BVector3f scale = compositeSubMesh->getScale();

        BMatrix4x4 matrix0;
        matrix0.setRotationEuler( rotation.x, rotation.y, rotation.z );
        matrix0.setTranslationPart( position );
        matrix0.scale( scale );

        for( int i = 0; i < subMesh->getVerticesSize(); i++ )
            vertices[ compositeSubMesh->onBakedVerticesPosition + i ] = matrix0 * subMesh->getVertices()[i];

        for( int i = 0; i < subMesh->getNormalsSize(); i++ )
            normals[ compositeSubMesh->onBakedNormalsPosition  + i ] = matrix0.getRotatedVector3( subMesh->getNormals()[i] );
        
        for( int i = 0; i < subMesh->getTangentsSize(); i++ )
            tangents[ compositeSubMesh->onBakedTangentsPosition + i ] = matrix0.getRotatedVector3( subMesh->getTangents()[i] );

        for( int i = 0; i < subMesh->getTexCoordsSize(); i++ )
            texCoords[ compositeSubMesh->onBakedTexCoordsPosition + i ] = subMesh->getTexCoords()[i];
        

        if( newSubMeshs->getIndicesType() == U_UINT ){
            unsigned int * uintIndices = (unsigned int *)indices;
            for( int i = 0; i < subMesh->getIndicesSize(); i++ ){
                uintIndices[ compositeSubMesh->onBakedIndicesPosition + i ] = compositeSubMesh->onBakedVerticesPosition + ( (unsigned int*)subMesh->getIndices() )[i];
            }
        }else{
            unsigned short * ushortIndices = (unsigned short *)indices;
            for( int i = 0; i < subMesh->getIndicesSize(); i++ ){
                ushortIndices[ compositeSubMesh->onBakedIndicesPosition + i ] = compositeSubMesh->onBakedVerticesPosition + ( (unsigned short*)subMesh->getIndices() )[i];
            } 
        }


        newSubMeshs->getBoundingBox()->initFromPoints( newSubMeshs->getVertices(), newSubMeshs->getVerticesSize() ); // probablemente lento

        newSubMeshs->allocDisplays(1);
        unsigned int begin = 0u, size = indicesNumber;
        BDisplay * display = newSubMeshs->addNewDisplay(U_PRIMITIVE_TRIANGLES, begin, size);
        //display->setMaterial( newMesh->getMaterial(0u) );
        display->setMaterial( newMesh->getMaterial(0u) );
        display->setCullMode(U_CULL_NONE);

    }

}


void BOCompositedModel3d::bakePhysicsMeshs(){
    
    unsigned int verticesNumber, normalsNumber, tangentsNumber, texCoordsNumber, indicesNumber;
    verticesNumber = normalsNumber = tangentsNumber = texCoordsNumber = indicesNumber = 0u;

    for( int i = 0; i < m_cSubMeshs.size() ; i++ ){
        BOCompositedModel3dSubMesh * compositeSubMesh = m_cSubMeshs[i];

        BSubMesh * subMesh = compositeSubMesh->getPhysicsSubMesh();
        if( !subMesh )
            continue;

        BVector3f position = compositeSubMesh->getPosition();

        compositeSubMesh->onBakedPVerticesPosition   =  verticesNumber;
        compositeSubMesh->onBakedPNormalsPosition   =   normalsNumber;
        compositeSubMesh->onBakedPTangentsPosition  =  tangentsNumber;
        compositeSubMesh->onBakedPIndicesPosition   =   indicesNumber;
 

        verticesNumber +=   subMesh->getVerticesSize();
        normalsNumber  +=    subMesh->getNormalsSize();
        tangentsNumber +=   subMesh->getTangentsSize();
        indicesNumber  +=    subMesh->getIndicesSize();
    }

    if( verticesNumber == 0u || indicesNumber == 0u )
        return;
    
    m_physicsMeshRef = BMeshRef::getNew( BMesh::getNew(), "compositedPhysicsMesh" );
    BMesh * newPhysicsMesh = getPhysicsMesh();
    newPhysicsMesh->clearSubMeshs();

    BSubMesh * newSubMeshs = newPhysicsMesh->allocSubMeshs(1);

    BVector3f * vertices  = newSubMeshs->allocVertices ( verticesNumber );
	BVector3f * normals   = newSubMeshs->allocNormals  ( verticesNumber );
	BVector3f * tangents  = newSubMeshs->allocTangents ( verticesNumber );
    void      * indices   = newSubMeshs->allocIndices  ( indicesNumber, ( indicesNumber >= USHRT_MAX - 1 )? U_UINT : U_USHORT );

    for( int i = 0; i < m_cSubMeshs.size() ; i++ ){
        BOCompositedModel3dSubMesh * compositeSubMesh = m_cSubMeshs[i];
        
        BSubMesh * subMesh = compositeSubMesh->getPhysicsSubMesh();
        if( !subMesh )
            continue;
        
        BVector3f position = compositeSubMesh->getPosition();
        BVector3f rotation = compositeSubMesh->getEulerRotation();
        BVector3f eRotation = getEulerRotation();
        BVector3f scale = compositeSubMesh->getScale();

        BMatrix4x4 matrix0;
        matrix0.setRotationEuler( rotation.x, rotation.y, rotation.z );
        matrix0.setTranslationPart( position );
        matrix0.scale( scale );

        for( int i = 0; i < subMesh->getVerticesSize(); i++ )
            vertices[ compositeSubMesh->onBakedPVerticesPosition + i ] = matrix0 * subMesh->getVertices()[i];

        for( int i = 0; i < subMesh->getNormalsSize(); i++ )
            normals[ compositeSubMesh->onBakedPNormalsPosition  + i ] = matrix0.getRotatedVector3( subMesh->getNormals()[i] );
        
        for( int i = 0; i < subMesh->getTangentsSize(); i++ )
            tangents[ compositeSubMesh->onBakedPTangentsPosition + i ] = matrix0.getRotatedVector3( subMesh->getTangents()[i] );
        

        if( newSubMeshs->getIndicesType() == U_UINT ){
            unsigned int * uintIndices = (unsigned int *)indices;
            for( int i = 0; i < subMesh->getIndicesSize(); i++ ){
                uintIndices[ compositeSubMesh->onBakedPIndicesPosition + i ] = compositeSubMesh->onBakedVerticesPosition + ( (unsigned int*)subMesh->getIndices() )[i];
            }
        }else{
            unsigned short * ushortIndices = (unsigned short *)indices;
            for( int i = 0; i < subMesh->getIndicesSize(); i++ ){
                ushortIndices[ compositeSubMesh->onBakedPIndicesPosition + i ] = compositeSubMesh->onBakedVerticesPosition + ( (unsigned short*)subMesh->getIndices() )[i];
            } 
        }


        newSubMeshs->getBoundingBox()->initFromPoints( newSubMeshs->getVertices(), newSubMeshs->getVerticesSize() ); // probablemente lento
        newPhysicsMesh->getBoundingBox()->min = newSubMeshs->getBoundingBox()->min; // probablemente lento
        newPhysicsMesh->getBoundingBox()->max = newSubMeshs->getBoundingBox()->max;


        newSubMeshs->allocDisplays(1);
        unsigned int begin = 0u, size = indicesNumber;
        BDisplay * display = newSubMeshs->addNewDisplay(U_PRIMITIVE_TRIANGLES, begin, size);
        //display->setMaterial( newMesh->getMaterial(0u) );
        display->setMaterial( NULL );
        display->setCullMode(U_CULL_NONE);

    }

}