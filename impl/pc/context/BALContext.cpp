/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MCore
// MSOpenALContext.cpp
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


#include <BALContext.h>


ALenum returnALFormat(B_SOUND_FORMAT format)
{
	switch(format)
	{
	default:
	case B_SOUND_FORMAT_MONO8 :
		return AL_FORMAT_MONO8;

	case B_SOUND_FORMAT_STEREO8 :
		return AL_FORMAT_STEREO8;

	case B_SOUND_FORMAT_MONO16 :
		return AL_FORMAT_MONO16;

	case B_SOUND_FORMAT_STEREO16 :
		return AL_FORMAT_STEREO16;
	}
}

BALContext::BALContext(void)
{
    // device
	m_device = alcOpenDevice(NULL);
    if(! m_device)
	{
		printf("ERROR OpenAL : unable to create device\n");
        return;
	}

    // context
	m_context = alcCreateContext(m_device, NULL);
    if(! m_context)
	{
		printf("ERROR OpenAL : unable to create context\n");
        return;
	}

	// init context
	initContext();
}

BALContext::~BALContext(void)
{
    ALCcontext * context = alcGetCurrentContext();
    ALCdevice * device = alcGetContextsDevice(context);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void BALContext::initContext(void)
{
	// make current context
    if(! alcMakeContextCurrent(m_context))
	{
		printf("ERROR OpenAL : unable to make current context\n");
        return;
	}
}

void BALContext::createBuffer(unsigned int * bufferId)
{
	alGenBuffers(1, bufferId);
}

void BALContext::deleteBuffer(unsigned int * bufferId)
{
	if(*bufferId > 0)
	{
		// unlink sources
		map<unsigned int, unsigned int>::iterator
		mit (m_sources.begin()),
		mend(m_sources.end());

		for(;mit!=mend;++mit)
		{
		  if(mit->second == (*bufferId))
		  {
			  stopSource(mit->first);
			  setSourceBufferId(mit->first, 0);
		  }
		}	

		// delete buffer
		alDeleteBuffers(1, bufferId);
	}
}

void BALContext::sendBufferSound(unsigned int bufferId, BSound * sound)
{
	if(! sound)
		return;

	// properties
	ALenum format = returnALFormat(sound->getFormat());

    // send data
	alBufferData(bufferId, format, sound->getData(), sound->getSize(), sound->getSampleRate());

	ALenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
       printf("ERROR OpenAL : unable to send sound data\n");
	   return;
    }
}

void BALContext::sendBufferData(unsigned int bufferId, B_SOUND_FORMAT format, void * data, unsigned int size, unsigned int freq)
{
	// properties
	ALenum alFormat = returnALFormat(format);

    // send data
	alBufferData(bufferId, alFormat, data, size, freq);

	ALenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
       printf("ERROR OpenAL : unable to send sound data\n");
	   return;
    }
}

float BALContext::getBufferDuration(unsigned int bufferId)
{
	int size;
	int bits;
	int freq;

	alGetBufferi(bufferId, AL_SIZE, &size);
	alGetBufferi(bufferId, AL_BITS, &bits);
	alGetBufferi(bufferId, AL_FREQUENCY, &freq);

	float duration = size / (float)((bits/8.0f) * freq);
	return duration;
}

// source
void BALContext::createSource(unsigned int * sourceId, unsigned int bufferId)
{
	alGenSources(1, sourceId);
	setSourceBufferId(*sourceId, bufferId);

	// init velocity
	ALfloat sourceVel[] = {0.0, 0.0, 0.0};
	alSourcefv(*sourceId, AL_VELOCITY, sourceVel);

	m_sources[*sourceId] = bufferId;
}

void BALContext::deleteSource(unsigned int * sourceId)
{
	if(*sourceId > 0)
	{
		map<unsigned int, unsigned int>::iterator iter = m_sources.find(*sourceId);
		if(iter != m_sources.end())
			m_sources.erase(iter);
	
		alDeleteSources(1, sourceId);
	}
}

void BALContext::enableSourceLoop(unsigned int sourceId)
{
	alSourcei(sourceId, AL_LOOPING, 1);
}

void BALContext::disableSourceLoop(unsigned int sourceId)
{
	alSourcei(sourceId, AL_LOOPING, 0);
}

void BALContext::setSourceRelative(unsigned int sourceId, bool relative)
{
	alSourcei(sourceId, AL_SOURCE_RELATIVE, (ALint)relative);
}

void BALContext::setSourceBufferId(unsigned int sourceId, unsigned int bufferId)
{
	alSourcei(sourceId, AL_BUFFER, bufferId);
	m_sources[sourceId] = bufferId;
}

void BALContext::setSourcePosition(unsigned int sourceId, const BVector3f & position)
{
	alSourcefv(sourceId, AL_POSITION, position);
}

void BALContext::setSourceRadius(unsigned int sourceId, float radius)
{
	// the distance under which the volume for the source would normally drop by half
	alSourcef(sourceId, AL_REFERENCE_DISTANCE, radius);
}

void BALContext::setSourcePitch(unsigned int sourceId, float pitch)
{
	alSourcef(sourceId, AL_PITCH, pitch);
}

void BALContext::setSourceGain(unsigned int sourceId, float gain)
{
	alSourcef(sourceId, AL_GAIN, gain);
}

void BALContext::setSourceRolloff(unsigned int sourceId, float rolloff)
{
	alSourcef(sourceId, AL_ROLLOFF_FACTOR, rolloff);
}

void BALContext::setSourceOffset(unsigned int sourceId, float offset)
{
	alSourcef(sourceId, AL_SEC_OFFSET, offset);
}

float BALContext::getSourceOffset(unsigned int sourceId)
{
	float time;
	alGetSourcef(sourceId, AL_SEC_OFFSET, &time);
	return time;
}

void BALContext::playSource(unsigned int sourceId)
{
	alSourcePlay(sourceId);
}

void BALContext::pauseSource(unsigned int sourceId)
{
	alSourcePause(sourceId);
}

void BALContext::stopSource(unsigned int sourceId)
{
	alSourceStop(sourceId);
}

bool BALContext::isSourcePaused(unsigned int sourceId)
{
	ALint state;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

	if(state == AL_PAUSED)
		return true;
	else
		return false;
}

bool BALContext::isSourcePlaying(unsigned int sourceId)
{
	ALint state;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

	if(state == AL_PLAYING)
		return true;
	else
		return false;
}

float BALContext::getSourceTimePos(unsigned int sourceId)
{
	int bits;
	int freq;
	int bOffset;

	ALint buffer;
	alGetSourcei(sourceId, AL_BUFFER, &buffer);
	alGetSourcei(sourceId, AL_BYTE_OFFSET, &bOffset);

	alGetBufferi(buffer, AL_BITS, &bits);
	alGetBufferi(buffer, AL_FREQUENCY, &freq);

	float timePos = bOffset / (float)((bits/8.0f) * freq);
	return timePos;
}

void BALContext::queueSourceBuffer(unsigned int sourceId, unsigned int * buffers, unsigned int bufferSize)
{
	alSourceQueueBuffers(sourceId, bufferSize, buffers);
}

void BALContext::unqueueSourceBuffer(unsigned int sourceId, unsigned int * buffers, unsigned int bufferSize)
{
	alSourceUnqueueBuffers(sourceId, bufferSize, buffers);
}

unsigned int BALContext::getSourceBuffersQueued(unsigned int sourceId)
{
	ALint queued = 0;
    alGetSourcei(sourceId, AL_BUFFERS_QUEUED, &queued);
	return (unsigned int)queued;
}

unsigned int BALContext::getSourceBuffersProcessed(unsigned int sourceId)
{
	ALint processed = 0;
    alGetSourcei(sourceId, AL_BUFFERS_PROCESSED, &processed);
	return (unsigned int)processed;
}

// listener
void BALContext::updateListenerPosition(const BVector3f & position, const BVector3f & direction, const BVector3f & up)
{
	ALfloat ListenerPos[] = { position.x, position.y, position.z };
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerOri[] = { 
		direction.x, direction.y, direction.z, 
		up.x, up.y, up.z
	};

	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}