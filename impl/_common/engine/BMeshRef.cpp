/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BMeshRef.cpp
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


BMeshRef::BMeshRef(BMesh * mesh, const char * filename):m_mesh(mesh)
{
	m_filename.set(filename);
}

BMeshRef::~BMeshRef(void)
{
	clear();
}

BMeshRef * BMeshRef::getNew(BMesh * mesh, const char * filename)
{
	return new BMeshRef(mesh, filename);
}

void BMeshRef::clear(void)
{
	if(m_mesh)
	{
		m_mesh->destroy();
		m_mesh = NULL;
	}
}

void BMeshRef::destroy(void)
{
	delete this;
}

void BMeshRef::update(void)
{
	Bizarre * engine = Bizarre::getInstance();

	if(! m_mesh)
		m_mesh = BMesh::getNew();

	if(! engine->getMeshLoader()->loadData(getFilename(), m_mesh))
		ULOG_WARNING("Cannot load data " << getFilename());
}
