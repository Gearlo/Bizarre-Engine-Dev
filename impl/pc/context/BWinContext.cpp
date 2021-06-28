/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BWinContext.h
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


#include <BWindow.h>
#include "BWinContext.h"


// screen
void BWinContext::getScreenSize(unsigned int * width, unsigned int * height)
{
	BWindow* window = BWindow::getInstance();
	*width = window->getWidth();
	*height = window->getHeight();
}

// cursor
void BWinContext::setCursorPosition(int x, int y)
{
	BWindow* window = BWindow::getInstance();
	window->setCursorPos(window->getXPosition() + x, window->getYPosition() + y);
}

void BWinContext::hideCursor(void)
{
	BWindow* window = BWindow::getInstance();
	window->hideCursor();
}

void BWinContext::showCursor(void)
{
	BWindow* window = BWindow::getInstance();
	window->showCursor();
}

// working directory
const char * BWinContext::getWorkingDirectory(void)
{
	BWindow* window = BWindow::getInstance();
	return window->getWorkingDirectory();
}

// system tick
unsigned long BWinContext::getSystemTick(void)
{
	BWindow* window = BWindow::getInstance();
	return window->getSystemTick();
}
