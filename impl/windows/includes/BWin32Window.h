/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BGui
// MWin32Window.h
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


#ifndef _M_WIN32_WINDOW_H
#define _M_WIN32_WINDOW_H

#ifdef __CYGWIN__
#include <w32api.h>
#endif

#include <BCore.h>
#include <windows.h>
#include <list>


class BWindow
{
private:

	// windows contexts
	HDC m_hDC;
	HWND m_hWnd;
	HGLRC m_hRC;
	HINSTANCE m_hInstance;

	// infos
	bool m_focus;
	bool m_active;
	bool m_fullscreen;

	int	m_position[2];
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_colorBits;

	char m_title[256];
	char m_workingDirectory[256];

	// joysticks
	BJoystick m_joysticks[2];

	// events function pointer
	void (* m_pointerEvent)(MWinEvent * windowEvent);

public:

	BWindow(void);
	~BWindow(void);

	// instance
	static BWindow * getInstance(void)
	{
		static BWindow m_instance;
		return &m_instance;
	};

public:

	// create
	bool create(const char * title, unsigned int width, unsigned int height, int colorBits, bool fullscreen);

	// events
	inline void setPointerEvent(void (*pointerEvent)(MWinEvent * windowEvent)){ m_pointerEvent = pointerEvent; }
	void sendEvents(MWinEvent * events);
	bool onEvents(void);

	// cursor
	void setCursorPos(int x, int y);
	void hideCursor(void);
	void showCursor(void);

	// properties
	bool getFocus(void){ return m_focus; }
	inline bool isActive(void){ return m_active; }
	inline bool isFullscreen(void){ return m_fullscreen; }

	void setTitle(const char * title);
	void setFullscreen(bool fullscreen);
	void setFocus(bool focus){ m_focus = focus; }
	inline void setActive(bool active){ m_active = active; }

	// coords
	bool isMouseOverWindow(void);

	inline int getXPosition(void){ return m_position[0]; }
	inline int getYPosition(void){ return m_position[1]; }
	inline unsigned int getWidth(void){ return m_width; }
	inline unsigned int getHeight(void){ return m_height; }

	// swap buffer
	void swapBuffer(void);

	// system tick
	static unsigned long getSystemTick(void);

	// directories
	void setCurrentDirectory(const char * directory);
	void setWorkingDirectory(const char * directory);

	const char * getTempDirectory(void);
	const char * getCurrentDirectory(void);
	inline const char * getWorkingDirectory(void){ return m_workingDirectory; }

	// joysticks
	BJoystick * getJoystick1(void){ return &m_joysticks[0]; }
	BJoystick * getJoystick2(void){ return &m_joysticks[1]; }

	// execute
	void execute(const char * path, const char * args);

	// sleep
	void sleep(double time);
	
	// files parsing
    bool getOpenMultipleFiles(const char * title, const char * filter, string * repertory, list <string> * filesList);
    const char * getOpenDir(const char * title, const char * startPath = NULL);
	const char * getOpenFilename(const char * title, const char * filter, const char * startPath = NULL);
    const char * getSaveFilename(const char * title, const char * filter, const char * startPath = NULL);
};

#define BKey_BACKSPACE	128
#define BKey_TAB		129
#define BKey_CLEAR		130
#define BKey_RETURN		131
#define BKey_PAUSE		132
#define BKey_ESCAPE		133
#define BKey_SPACE		32
#define BKey_DELETE		134
#define BKey_KP0		135
#define BKey_KP1		136
#define BKey_KP2		137
#define BKey_KP3		138
#define BKey_KP4		139
#define BKey_KP5		140
#define BKey_KP6		141
#define BKey_KP7		142
#define BKey_KP8		143
#define BKey_KP9		144
#define BKey_KP_ENTER	145
#define BKey_UP			146
#define BKey_DOWN		147
#define BKey_RIGHT		148
#define BKey_LEFT		149
#define BKey_INSERT		150
#define BKey_HOME		151
#define BKey_END		152
#define BKey_PAGEUP		153
#define BKey_PAGEDOWN	154
#define BKey_F1			155
#define BKey_F2			156
#define BKey_F3			157
#define BKey_F4			158
#define BKey_F5			159
#define BKey_F6			160
#define BKey_F7			161
#define BKey_F8			162
#define BKey_F9			163
#define BKey_F10		164
#define BKey_F11		165
#define BKey_F12		166
#define BKey_NUMLOCK	167
#define BKey_RSHIFT		168
#define BKey_LSHIFT		169
#define BKey_SHIFT		169 // deprecated
#define BKey_RCONTROL	171
#define BKey_LCONTROL	172
#define BKey_CONTROL	172 // deprecated
#define BKey_RALT		174
#define BKey_LALT		175
#define BKey_ADD		176
#define BKey_SUB		177
#define BKey_HELP		178
#define BKey_PRINT		179
#define BKey_MENU		180
#define BKey_RSUPER		181
#define BKey_LSUPER		182
#define BKey_DUMMY		255

#endif
