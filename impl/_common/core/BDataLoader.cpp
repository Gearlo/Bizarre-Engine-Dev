/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BDataLoader.cpp
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


#include <BCore.h>


// Data load function
BDataLoadFunction::BDataLoadFunction(bool (* functionPtr)(const char * filename, void * data)):
m_functionPtr(functionPtr)
{}

BDataLoadFunction::~BDataLoadFunction(void)
{}

// Data loader
BDataLoader::BDataLoader(void)
{}

BDataLoader::~BDataLoader(void)
{
	clear();
}

void BDataLoader::clear(void)
{
	unsigned int i;
	unsigned int lSize = m_loaders.size();
	for(i=0; i<lSize; i++)
		SAFE_DELETE(m_loaders[i]);

	m_loaders.clear();
}

void BDataLoader::addLoader(bool (* functionPtr)(const char * filename, void * data))
{
	m_loaders.push_back(new BDataLoadFunction(functionPtr));
}

bool BDataLoader::loadData(const char * filename, void * data)
{
	// parse loaders
	unsigned int i;
	unsigned int lSize = m_loaders.size();
	for(i=0; i<lSize; i++)
	{
		BDataLoadFunction * loader = m_loaders[i];
		if(loader->m_functionPtr(filename, data))
			return true;
	}

	return false;
}
