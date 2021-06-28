/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BShaderRef.cpp
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


BShaderRef::BShaderRef(unsigned int shaderId, U_SHADER_TYPES type, const char * filename):
	m_shaderId(shaderId),
	m_type(type){
	m_filename.set(filename);
}

BShaderRef::~BShaderRef(void){
	clear();
}

BShaderRef * BShaderRef::getNew(unsigned int shaderId, U_SHADER_TYPES type, const char * filename){
	return new BShaderRef(shaderId, type, filename);
}

void BShaderRef::clear(void){
	Bizarre::getInstance()->getRenderingContext()->deleteShader(&m_shaderId);
}

void BShaderRef::destroy(void){
	delete this;
}

void BShaderRef::update(void)
{
	Bizarre * engine = Bizarre::getInstance();
	//BWorld * world = engine->getWorld();
	BAssetsManager * level = engine->getAssetsManager();
	BRenderingContext * render = engine->getRenderingContext();

	char * text = readTextFile(getFilename());
	if(text)
	{
		// gen shader if null
		if(m_shaderId == 0)
		{
			switch(m_type)
			{
			case M_SHADER_VERTEX:
				render->createVertexShader(&m_shaderId);
				break;
			case M_SHADER_PIXEL:
				render->createPixelShader(&m_shaderId);
				break;
			}
		}

		// send shader source
		render->sendShaderSource(m_shaderId, text);
		SAFE_FREE(text);

		BFXManager * FXManager = level->getFXManager();

		unsigned int i;
		unsigned int size = FXManager->getFXRefsNumber();
		for(i=0; i<size; i++)
		{
			BFXRef * FXRef = FXManager->getFXRef(i);
			if((FXRef->getPixelShaderRef() == this) || (FXRef->getVertexShaderRef() == this))
			{
				unsigned int FXId = FXRef->getFXId();
				render->updateFX(FXId);
			}
		}
	}
}