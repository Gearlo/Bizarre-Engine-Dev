/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BGui
// BGui.h
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


#ifndef _M_GUI_H
#define _M_GUI_H


// variable types
enum M_VAR_TYPE
{
	M_VAR_NONE = 0,
	M_VAR_BOOL,
	M_VAR_INT,
	M_VAR_UINT,
	M_VAR_FLOAT,
	M_VAR_STRING
};

class BGuiButton;
class BGuiMenu;
class BGuiText;
class BGuiImage;
class BGuiEditText;
class BGuiSlide;
class BGuiWindow;

#include <stdio.h>
#include <vector>
#include <string>
#include <BCore.h>

#include "BWindow.h"
//#include "BGuiEvents.h"
//#include "BGuiTextureFont.h"
//#include "BGui2d.h"
//#include "BGuiSlide.h"
//#include "BGuiWindow.h"
//#include "BGuiButton.h"
//#include "BGuiMenu.h"
//#include "BGuiText.h"
//#include "BGuiImage.h"
//#include "BGuiEditText.h"
//#include "BGuiFileBrowser.h"

#include "BWinEvents.h"


// global functions
//void set2dMode(BRenderingContext * render);

/*
// gui texture
class BGuiTexture
{
public:

	std::string name;
	unsigned int textureId;
};

// BGui
class BGui
{
public:

	BGui(void);
	~BGui(void);

	// instance
	static BGui * getInstance(void)
	{
		static BGui m_instance;
		return &m_instance;
	};

private:

	// rendering context
	BRenderingContext * m_render;

	// textures
	std::vector <BGuiTexture *> m_textures;

	// fonts
	std::vector <BGuiTextureFont *> m_fonts;

	// windows
	std::vector <BGuiWindow *> m_windows;

public:

	// rendering context
	void setRenderingContext(BRenderingContext * render){ m_render = render; }
	BRenderingContext * getRenderingContext(void){ return m_render; }

	// windows
	void unHighLightAllWindows(void);

	// clear
	void clear(void);

	// editing
	bool isSomethingEditing(void);

	// textures
	bool loadTexture(const char * filename, unsigned int * textureId);

	// fonts
	inline void addFont(BGuiTextureFont * font){ m_fonts.push_back(font); }
	inline unsigned int getFontsNumber(void){ return m_fonts.size(); }
	inline BGuiTextureFont * getFont(unsigned int id){ return m_fonts[id]; }

	// windows
	inline void addWindow(BGuiWindow * window){ m_windows.push_back(window); }
	inline unsigned int getWindowsNumber(void){ return m_windows.size(); }
	inline BGuiWindow * getWindow(unsigned int id){ return m_windows[id]; }

	// drawing
	void draw(void);

	// events
	void onEvent(MWinEvent * windowEvent);
};
 */

#endif
