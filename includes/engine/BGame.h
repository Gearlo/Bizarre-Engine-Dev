/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// BGame.h
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


#ifndef _M_GAME_H
#define _M_GAME_H


class M_ENGINE_EXPORT BGame
{
private:
	BScript * script;
	bool m_isRunning;

public:

	BGame(void);
	virtual ~BGame(void);

public:
	inline void setScript( BScript* script ){ this->script =  script; }

public:
	// is running
	inline bool isRunning(void){ return m_isRunning; }

	// begin / end
	void begin(void) { onBegin(); onBeginLevel(); onBeginScene(); m_isRunning = true; }
	void end(void) { onEndScene(); onEndLevel(); onEnd(); m_isRunning = false; }

	// events
	virtual void update(void);
	virtual void draw(void);

	virtual void onBegin(void);
	virtual void onEnd(void){}

	virtual void onBeginLevel(void) { }
	virtual void onEndLevel(void){}

	virtual void onBeginScene(void);
	virtual void onEndScene(void);

	//void restart(void);
};

#endif
