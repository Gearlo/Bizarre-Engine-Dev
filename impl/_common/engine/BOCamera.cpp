/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BOCamera.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#include <BEngine.h>


// constructor
BOCamera::BOCamera(void):
BObject3d(),
m_ortho(false),
m_fog(false),
m_fov(60),
m_fogDistance(0),
m_clippingNear(1),
m_clippingFar(1000),
m_clearColor(0.2f, 0.3f, 0.4f),
m_sceneLayer(0),
m_renderColorTexture(NULL),
m_renderDepthTexture(NULL)
{
	m_currentViewport[0] = 0;
	m_currentViewport[1] = 0;
	m_currentViewport[2] = 0;
	m_currentViewport[3] = 0;
}

// destructor
BOCamera::~BOCamera(void)
{
	BObject3d::clearObject3d();
}

// copy constructor
BOCamera::BOCamera(const BOCamera & camera):
BObject3d(camera),
m_ortho(camera.m_ortho),
m_fog(camera.m_fog),
m_fov(camera.m_fov),
m_fogDistance(camera.m_fogDistance),
m_clippingNear(camera.m_clippingNear),
m_clippingFar(camera.m_clippingFar),
m_clearColor(camera.m_clearColor),
m_sceneLayer(camera.m_sceneLayer),
m_renderColorTexture(NULL),
m_renderDepthTexture(NULL)
{}

BVector3f BOCamera::getProjectedPoint(const BVector3f & point) const
{
	BVector4f v = m_currentViewMatrix * BVector4f(point);
	v = m_currentProjMatrix * v;
	v.x = v.x / v.w;
	v.y = v.y / v.w;
	v.z = v.z / v.w;

	v.x = m_currentViewport[0] + (m_currentViewport[2] * ((v.x + 1) / 2.0f));
	v.y = m_currentViewport[1] + (m_currentViewport[3] * ((v.y + 1) / 2.0f));
	v.z = (v.z + 1) / 2.0f;

	return BVector3f(v.x, v.y, v.z);
}

BVector3f BOCamera::getUnProjectedPoint(const BVector3f & point) const
{
	BVector4f nPoint;

	nPoint.x = (2 * ((point.x - m_currentViewport[0]) / ((float)m_currentViewport[2]))) - 1;
	nPoint.y = (2 * ((point.y - m_currentViewport[1]) / ((float)m_currentViewport[3]))) - 1;
	nPoint.z = (2 * point.z) - 1;
	nPoint.w = 1;

	BMatrix4x4 matrix = (m_currentProjMatrix * m_currentViewMatrix).getInverse();
	BVector4f v = matrix * nPoint;
	
	if(v.w == 0)
		return getTransformedPosition();
	
	float iw = 1.0f / v.w;
	return BVector3f(v.x, v.y, v.z)*iw;
}


BVector3f BOCamera::getRelativeDisplace( const BVector3f & position, const BVector2f & displace ){
    BVector3f relativeDirection = position - getPosition();
    relativeDirection.z = 0.0f;
    relativeDirection.normalize();
    
    BVector2f displaceVector = displace;
    displaceVector.normalize();
    
    if(displaceVector.getLength() > 0.1){
        float cameraAngle = acos(relativeDirection.x);
        if(relativeDirection.y < 0.0f){ cameraAngle = 2.0f*M_PI - cameraAngle; }
        float displaceAngle  = acos(displaceVector.x);
        if(displaceVector.y < 0.0f){ displaceAngle  = 2.0f*M_PI - displaceAngle; }
            
        float relativeAngle =  cameraAngle + displaceAngle - ((1.0f / 2.0f) * M_PI);
        BVector3f relativeDisplace = BVector3f( cos(relativeAngle) , sin(relativeAngle), .0f );            
        ///std::cout << toText(relativeDisplace) << std::endl;
   
        return relativeDisplace;
    }
    return BVector3f();
} 
 


void BOCamera::updateListener(void)
{
	BSoundContext * soundContext = Bizarre::getInstance()->getSoundContext();
	if(soundContext)
	{
		BVector3f position = getTransformedPosition();
		BVector3f direction = getRotatedVector(BVector3f(0, 0, -1));
		BVector3f up = getRotatedVector(BVector3f(0, 1, 0));
		soundContext->updateListenerPosition(position, direction, up);
	}
}

void BOCamera::enable(void)
{
	BRenderingContext * render = Bizarre::getInstance()->getRenderingContext();
	

	// get viewport
	render->getViewport(m_currentViewport);

	// projection mode
	render->setMatrixMode(M_MATRIX_PROJECTION);
	render->loadIdentity();

	float ratio = (m_currentViewport[2] / (float)m_currentViewport[3]);

	BVector3f scale = getTransformedScale();
	BVector3f iScale(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);

	BMatrix4x4 iScaleMatrix;
	iScaleMatrix.setScale(iScale);

	BMatrix4x4 inverseMatrix = ((*getMatrix()) * iScaleMatrix).getInverse();

	// perspective view
	if(! isOrtho())
	{
		// normal perspective projection
		render->setPerspectiveView(m_fov, ratio, m_clippingNear, m_clippingFar);

		// model view mode
		render->setMatrixMode(M_MATRIX_MODELVIEW);
		render->loadIdentity();

		render->multMatrix(&inverseMatrix);

		// get current matrices
		render->getModelViewMatrix(&m_currentViewMatrix);
		render->getProjectionMatrix(&m_currentProjMatrix);
		return;
	}

	// ortho view
	float height = m_fov * 0.5f;
	float width = height * ratio;

	render->setOrthoView(-width, width, -height, height, m_clippingNear, m_clippingFar);

	// model view mode
	render->setMatrixMode(M_MATRIX_MODELVIEW);
	render->loadIdentity();
	
	render->multMatrix(&inverseMatrix);

	// get current matrices
	render->getModelViewMatrix(&m_currentViewMatrix);
	render->getProjectionMatrix(&m_currentProjMatrix);
}