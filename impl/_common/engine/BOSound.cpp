/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BOSound.cpp
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
BOSound::BOSound(BSoundRef * soundRef):
	BObject3d(),
	m_sourceId(0),
	m_soundRef(soundRef)
{
	unsigned int bufferId = 0;
	if(m_soundRef)
		bufferId = m_soundRef->getBufferId();

	// create Source
	Bizarre::getInstance()->getSoundContext()->createSource(&m_sourceId, bufferId);

	setLooping(false);
	setRelative(false);
	setPitch(1.0f);
	setGain(50.0f);
	setRadius(10.0f);
	setRolloff(1.0f);
}

// copy constructor
BOSound::BOSound(const BOSound & sound):
	BObject3d(sound),
	m_sourceId(0),
	m_soundRef(sound.m_soundRef)
{
	unsigned int bufferId = 0;
	if(m_soundRef)
		bufferId = m_soundRef->getBufferId();

	// create Source
	Bizarre::getInstance()->getSoundContext()->createSource(&m_sourceId, bufferId);

	setLooping(sound.m_isLooping);
	setRelative(sound.m_isRelative);
	setPitch(sound.m_pitch);
	setGain(sound.m_gain);
	setRadius(sound.m_radius);
	setRolloff(sound.m_rolloff);
}

// destructor
BOSound::~BOSound(void)
{
	BObject3d::clearObject3d();
	Bizarre::getInstance()->getSoundContext()->deleteSource(&m_sourceId);
}

void BOSound::setSoundRef(BSoundRef * soundRef)
{
	m_soundRef = soundRef;

	unsigned int bufferId = 0;
	if(m_soundRef)
		bufferId = m_soundRef->getBufferId();

	Bizarre::getInstance()->getSoundContext()->setSourceBufferId(m_sourceId, bufferId);
}

bool BOSound::isPlaying(void)
{
	return Bizarre::getInstance()->getSoundContext()->isSourcePlaying(m_sourceId);
}

float BOSound::getTimePos(void)
{
	return Bizarre::getInstance()->getSoundContext()->getSourceTimePos(m_sourceId);
}

float BOSound::getSoundDuration(void)
{
	if(m_soundRef)
		return Bizarre::getInstance()->getSoundContext()->getBufferDuration(m_soundRef->getBufferId());
	else
		return 0.0f;
}

void BOSound::play(void)
{
	BSoundContext * soundContext = Bizarre::getInstance()->getSoundContext();

	if(m_soundRef)
	{
		unsigned int bufferId = m_soundRef->getBufferId();
		soundContext->setSourceBufferId(m_sourceId, bufferId);
		soundContext->playSource(m_sourceId);
	}
}

void BOSound::pause(void)
{
	Bizarre::getInstance()->getSoundContext()->pauseSource(m_sourceId);
}

void BOSound::stop(void)
{
	Bizarre::getInstance()->getSoundContext()->stopSource(m_sourceId);
}

void BOSound::setLooping(bool loop)
{ 
	BSoundContext * soundContext = Bizarre::getInstance()->getSoundContext();

	if(loop != m_isLooping)
	{
		if(loop)
			soundContext->enableSourceLoop(m_sourceId);
		else
			soundContext->disableSourceLoop(m_sourceId);

		m_isLooping = loop;
	}
}

void BOSound::setRelative(bool relative)
{
	m_isRelative = relative;
	Bizarre::getInstance()->getSoundContext()->setSourceRelative(m_sourceId, m_isRelative);
}

void BOSound::setPitch(float pitch)
{
	m_pitch = pitch;
	Bizarre::getInstance()->getSoundContext()->setSourcePitch(m_sourceId, m_pitch);
}

void BOSound::setGain(float gain)
{
	m_gain = gain;
	Bizarre::getInstance()->getSoundContext()->setSourceGain(m_sourceId, m_gain);
}

void BOSound::setRadius(float radius)
{
	m_radius = radius;
	Bizarre::getInstance()->getSoundContext()->setSourceRadius(m_sourceId, m_radius);
}

void BOSound::setRolloff(float rolloff)
{
	m_rolloff = rolloff;
	Bizarre::getInstance()->getSoundContext()->setSourceRolloff(m_sourceId, m_rolloff);
}

void BOSound::update(void)
{
	Bizarre::getInstance()->getSoundContext()->setSourcePosition(m_sourceId, getTransformedPosition());
}