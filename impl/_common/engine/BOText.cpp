/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BOText.cpp
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
BOText::BOText(BFontRef * fontRef):
BObject3d(),
m_align(U_ALIGN_LEFT),
m_size(16),
m_color(1, 1, 1, 1)
{
	setFontRef(fontRef);
}

// copy constructor
BOText::BOText(const BOText & text):
BObject3d(text),
m_text(text.m_text),
m_align(text.m_align),
m_size(text.m_size),
m_fontRef(text.m_fontRef),
m_color(text.m_color),
m_boundingBox(text.m_boundingBox)
{
	prepare();
}

// destructor
BOText::~BOText(void)
{
	BObject3d::clearObject3d();
}

void BOText::setFontRef(BFontRef * fontRef)
{
	m_fontRef = fontRef;
	prepare();
}

BFont * BOText::getFont(void)
{
	if(! m_fontRef)
		return NULL;

	return m_fontRef->getFont();
}

void BOText::setText(const char * text)
{
	m_text.set(text);
	prepare();
}

void BOText::setAlign(U_ALIGN_MODES align)
{
	m_align = align;
	prepare();
}

void BOText::setSize(float size)
{ 
	m_size = size;
	prepare();
}

void BOText::updateLinesOffset(void)
{
	BFont * font = getFont();
	const char * text = m_text.getData();

	float tabSize = m_size*2;
	float fontSize = (float)font->getFontSize();
	float widthFactor = font->getTextureWith() / fontSize;
	float xc = 0;
	float min = 0;
	float max = 0;

	// bounding box
	BVector3f * boxMin = &m_boundingBox.min;
	BVector3f * boxMax = &m_boundingBox.max;
	
	// clear lines
	m_linesOffset.clear();

	if(text)
	{
		unsigned int i;
		unsigned int size = strlen(text);
		for(i=0; i<size; i++)
		{
			if(text[i] == '\n') // return
			{
				switch(m_align)
				{
					case U_ALIGN_LEFT:
						m_linesOffset.push_back(0);
						break;
					case U_ALIGN_RIGHT:
						m_linesOffset.push_back(-(max - min));
						break;
					case U_ALIGN_CENTER:
						m_linesOffset.push_back(-(max - min)*0.5f);
						break;
				}
				
				min = 0;
				max = 0;
				xc = 0;
				continue;
			}
			
			if(text[i] == '\t') // tab
			{
				int tab = (int)(xc / tabSize) + 1;
				xc = tab*tabSize;
				continue;
			}
			
			// get character
			unsigned int charCode = (unsigned int)((unsigned char)text[i]);
			BCharacter * character = font->getCharacter(charCode);
			if(! character)
				continue;
			
			BVector2f scale = character->getScale();
			BVector2f offset = character->getOffset() * m_size;
			
			float width = scale.x * widthFactor * m_size;
			
			float charMin = xc + offset.x;
			float charMax = charMin + width;
			
			if(charMin < min)
				min = charMin;
			
			if(charMax > max)
				max = charMax;
			
			//move to next character
			xc += character->getXAdvance() * m_size;
		}
	}

	// last char (always should be executed!)
	switch(m_align)
	{
	case U_ALIGN_LEFT:
		m_linesOffset.push_back(0);
		break;
	case U_ALIGN_RIGHT:
		m_linesOffset.push_back(-(max - min));
		break;
	case U_ALIGN_CENTER:
		m_linesOffset.push_back(-(max - min)*0.5f);
		break;
	}

	float globalOffset = boxMax->x - boxMin->x;

	switch(m_align)
	{
	case U_ALIGN_RIGHT:
		boxMin->x -= globalOffset;
		boxMax->x -= globalOffset;
		break;
	case U_ALIGN_CENTER:
		boxMin->x -= globalOffset*0.5f;
		boxMax->x -= globalOffset*0.5f;
		break;
	}
}

void BOText::prepare(void)
{
	BFont * font = getFont();
	const char * text = m_text.getData();
	if(! text)
	{
		m_boundingBox = BBox3d();
		return;
	}
	
	if(! (strlen(text) > 0 && font)){
		m_boundingBox = BBox3d();
		return;
	}

	BVector3f * min = &m_boundingBox.min;
	BVector3f * max = &m_boundingBox.max;

	(*min) = (*max) = BVector3f(0, 0, 0);

	float tabSize = m_size*2;
	float fontSize = (float)font->getFontSize();
	float widthFactor = font->getTextureWith() / fontSize;
	float heightFactor = font->getTextureHeight() / fontSize;
	float xc = 0, yc = 0;

	unsigned int i;
	unsigned int size = strlen(text);
	for(i=0; i<size; i++)
	{
		if(text[i] == '\n') // return
		{
			yc += m_size;
			xc = 0;
			continue;
		}

		if(text[i] == '\t') // tab
		{
			int tab = (int)(xc / tabSize) + 1;
			xc = tab*tabSize;
			continue;
		}

		// get character
		unsigned int charCode = (unsigned int)((unsigned char)text[i]);
		BCharacter * character = font->getCharacter(charCode);
		if(! character)
			continue;

		BVector2f scale = character->getScale();
		BVector2f offset = character->getOffset() * m_size;

		float width = scale.x * widthFactor * m_size;
		float height = scale.y * heightFactor * m_size;

		BVector2f charMin = BVector2f(xc, yc) + offset;
		BVector2f charMax = charMin + BVector2f(width, height);

		if(charMin.x < min->x)
			min->x = charMin.x;
		if(charMin.y < min->y)
			min->y = charMin.y;

		if(charMax.x > max->x)
			max->x = charMax.x;
		if(charMax.y > max->y)
			max->y = charMax.y;

		//move to next character
		xc += character->getXAdvance() * m_size;
	}

	updateLinesOffset();
}

void BOText::updateVisibility(BOCamera * camera)
{
	BFrustum * frustum = camera->getFrustum();

	BVector3f * min = &m_boundingBox.min;
	BVector3f * max = &m_boundingBox.max;

	BVector3f points[8] = {
		getTransformedVector(BVector3f(min->x, min->y, min->z)),
		getTransformedVector(BVector3f(min->x, max->y, min->z)),
		getTransformedVector(BVector3f(max->x, max->y, min->z)),
		getTransformedVector(BVector3f(max->x, min->y, min->z)),
		getTransformedVector(BVector3f(min->x, min->y, max->z)),
		getTransformedVector(BVector3f(min->x, max->y, max->z)),
		getTransformedVector(BVector3f(max->x, max->y, max->z)),
		getTransformedVector(BVector3f(max->x, min->y, max->z))
	};

	// is box in frustum
	setVisible(frustum->isVolumePointsVisible(points, 8));
}