/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BGui
// BX11Window.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2011 teZeriusz <lukasz.wychrystenko@gmail.com>
// Copyright (c) 2011 Anael Seghezzi <www.maratis3d.com>
// Copyright (c) some parts using GLFW X11 code : http://www.glfw.org/
// Copyright (c) 2013 Yannick Pflanzer <yp1995@live.de>
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <unistd.h>

#ifndef __CYGWIN__
	#include <X11/extensions/xf86vmode.h>
#endif

#define linux // eliminar
#ifdef linux
	#include <BJoystickLinux.h>

	// Joystick class
	BJoystickLinux joystick1(JOY1_DEV);
	BJoystickLinux joystick2(JOY2_DEV);
#endif

// start time
static struct timeval startTime;

// X11
static Display * display = NULL;
static GLXContext context;
static Window window;
static Window rootWindow;
static int screen;
static Cursor nullCursor;
static Atom wmDelete;

#ifndef __CYGWIN__
	static XF86VidModeModeInfo desktopMode;
#endif


static Cursor createNULLCursor(Display * display, Window root)
{
    Pixmap    cursormask;
    XGCValues xgc;
    GC        gc;
    XColor    col;
    Cursor    cursor;

    cursormask = XCreatePixmap(display, root, 1, 1, 1);
    xgc.function = GXclear;
    gc = XCreateGC(display, cursormask, GCFunction, &xgc);
    XFillRectangle(display, cursormask, gc, 0, 0, 1, 1);
    col.pixel = 0;
    col.red = 0;
    col.flags = 4;
    cursor = XCreatePixmapCursor(display, cursormask, cursormask, &col,&col, 0, 0);
    XFreePixmap(display, cursormask);
    XFreeGC(display, gc);

    return cursor;
}

static int translateChar(XKeyEvent * event)
{
    KeySym keysym;

    // Get X11 keysym
    XLookupString(event, NULL, 0, &keysym, NULL);

    // Convert to Unicode (see x11_keysym2unicode.c)
    return (int) _glfwKeySym2Unicode( keysym );
}

static int translateKey(int keycode)
{
    KeySym key, key_lc, key_uc;

    // Try secondary keysym, for numeric keypad keys
    // Note: This way we always force "NumLock = ON", which at least
    // enables GLFW users to detect numeric keypad keys
    key = XKeycodeToKeysym(display, keycode, 1);
    switch( key )
    {
		// Numeric keypad
        case XK_KP_0:         return BKey_KP0;
        case XK_KP_1:         return BKey_KP1;
        case XK_KP_2:         return BKey_KP2;
        case XK_KP_3:         return BKey_KP3;
        case XK_KP_4:         return BKey_KP4;
        case XK_KP_5:         return BKey_KP5;
        case XK_KP_6:         return BKey_KP6;
        case XK_KP_7:         return BKey_KP7;
        case XK_KP_8:         return BKey_KP8;
        case XK_KP_9:         return BKey_KP9;
        case XK_KP_Enter:     return BKey_KP_ENTER;
        default:              break;
    }

    // Now try pimary keysym
    key = XKeycodeToKeysym(display, keycode, 0);
    switch( key )
    {
		// Special keys (non character keys)
        case XK_Escape:       return BKey_ESCAPE;
        case XK_Tab:          return BKey_TAB;
        case XK_Shift_L:      return BKey_LSHIFT;
        case XK_Shift_R:      return BKey_RSHIFT;
        case XK_Control_L:    return BKey_LCONTROL;
        case XK_Control_R:    return BKey_RCONTROL;
        case XK_Meta_L:
        case XK_Alt_L:        return BKey_LALT;
        case XK_Mode_switch:  // Mapped to Alt_R on many keyboards
        case XK_Meta_R:
        case XK_ISO_Level3_Shift: // AltGr on at least some machines
        case XK_Alt_R:        return BKey_RALT;
        case XK_Super_L:      return BKey_LSUPER;
        case XK_Super_R:      return BKey_RSUPER;
        case XK_Menu:         return BKey_MENU;
        case XK_Num_Lock:     return BKey_NUMLOCK;
        //case XK_Caps_Lock:    return BKey_CAPS_LOCK;
        //case XK_Scroll_Lock:  return BKey_SCROLL;
        case XK_Pause:        return BKey_PAUSE;
        case XK_KP_Delete:
        case XK_Delete:       return BKey_DELETE;
        case XK_BackSpace:    return BKey_BACKSPACE;
        case XK_Return:       return BKey_RETURN;
        case XK_KP_Home:
        case XK_Home:         return BKey_HOME;
        case XK_KP_End:
        case XK_End:          return BKey_END;
        case XK_KP_Page_Up:
        case XK_Page_Up:      return BKey_PAGEUP;
        case XK_KP_Page_Down:
        case XK_Page_Down:    return BKey_PAGEDOWN;
        case XK_KP_Insert:
        case XK_Insert:       return BKey_INSERT;
        case XK_KP_Left:
        case XK_Left:         return BKey_LEFT;
        case XK_KP_Right:
        case XK_Right:        return BKey_RIGHT;
        case XK_KP_Down:
        case XK_Down:         return BKey_DOWN;
        case XK_KP_Up:
        case XK_Up:           return BKey_UP;
        case XK_F1:           return BKey_F1;
        case XK_F2:           return BKey_F2;
        case XK_F3:           return BKey_F3;
        case XK_F4:           return BKey_F4;
        case XK_F5:           return BKey_F5;
        case XK_F6:           return BKey_F6;
        case XK_F7:           return BKey_F7;
        case XK_F8:           return BKey_F8;
        case XK_F9:           return BKey_F9;
        case XK_F10:          return BKey_F10;
        case XK_F11:          return BKey_F11;
        case XK_F12:          return BKey_F12;

		// Numeric keypad (should have been detected in secondary keysym!)
        case XK_KP_Subtract:  return BKey_SUB;
        case XK_KP_Add:       return BKey_ADD;
        case XK_KP_Enter:     return BKey_KP_ENTER;

		// The rest (should be printable keys)
        default:
		{
            // Make uppercase
            XConvertCase( key, &key_lc, &key_uc );
            key = key_uc;

            // Valid ISO 8859-1 character?
            if( (key >=  32 && key <= 126) ||
			   (key >= 160 && key <= 255) )
            {
                return (int) key;
            }

            return -1;
		}
    }
}

#ifdef linux
static void updateJoystick(BJoystick* joystick, BJoystickLinux* joystickLinux, 
			   BWindow* window, MWIN_EVENT_TYPE event)
{
	joystickLinux->updateData();
	
	for(int i=0; i<8; i++)
	{
		bool pressed = joystick->isKeyPressed(i);
		
		if(joystickLinux->getButton(i))
		{
			joystick->downKey(i);
		}
		else
		{
			joystick->upKey(i);
		}
	}
	
	joystick->setX(joystickLinux->getDeltaAxis(0));
	joystick->setY(joystickLinux->getDeltaAxis(1));
	joystick->setZ(joystickLinux->getDeltaAxis(2));
	joystick->setU(joystickLinux->getDeltaAxis(3));
	joystick->setR(joystickLinux->getDeltaAxis(4));
	joystick->setV(joystickLinux->getDeltaAxis(5));
	
	MWinEvent events;
	events.type = event; // MWIN_EVENT_JOYSTICK1_UPDATE;
	window->sendEvents(&events);
	
	joystick->flush();
}
#endif

BWindow::BWindow(void):
m_focus(true),
m_active(true),
m_fullscreen(false),
m_width(0),
m_height(0),
m_colorBits(0),
m_pointerEvent(NULL)
{
	m_position[0] = 0;
	m_position[1] = 0;
	strcpy(m_workingDirectory, getCurrentDirectory());
	strcpy(m_title, "");

	// start time
	gettimeofday(&startTime, NULL);
}

BWindow::~BWindow(void)
{
    if(display)
    {
        if(context)
        {
            glXMakeCurrent(display, None, NULL);
            glXDestroyContext(display, context);
            context = NULL;
        }

        if(m_fullscreen)
        {
			#ifndef __CYGWIN__
				XF86VidModeSwitchToMode(display, screen, &desktopMode);
				XF86VidModeSetViewPort(display, screen, 0, 0);
			#endif
        }

        XCloseDisplay(display);
    }
}

const char * BWindow::getTempDirectory(void)
{
	static char tempDirectory[8] = "/tmp";
	return tempDirectory;
}

const char * BWindow::getCurrentDirectory(void)
{
	static char currentDirectory[256];
	getcwd(currentDirectory, 256);
	return currentDirectory;
}

void BWindow::setCursorPos(int x, int y)
{
	XWarpPointer(display, None, window, 0, 0, 0, 0, x, y);
}

void BWindow::hideCursor(void)
{
	XDefineCursor(display, window, nullCursor);
}

void BWindow::showCursor(void)
{
	XUngrabPointer(display, CurrentTime);
	XUndefineCursor(display, window);
}

void BWindow::setTitle(const char * title)
{
	XStoreName(display, window, title);
    XSetIconName(display, window, title);
}

void BWindow::setCurrentDirectory(const char * directory)
{
	chdir(directory);
}

void BWindow::setWorkingDirectory(const char * directory)
{
	strcpy(m_workingDirectory, directory);
}

void BWindow::sendEvents(MWinEvent * events)
{
	BKeyboard * keyboard = BKeyboard::getInstance();
	BMouse * mouse = BMouse::getInstance();

	switch(events->type)
	{
		case MWIN_EVENT_KEY_DOWN:
			keyboard->onKeyDown(events->data[0]);
			break;

		case MWIN_EVENT_KEY_UP:
			keyboard->onKeyUp(events->data[0]);
			break;

		case MWIN_EVENT_WINDOW_RESIZE:
			m_width = (unsigned int)events->data[0];
			m_height = (unsigned int)events->data[1];
			break;

		case MWIN_EVENT_WINDOW_MOVE:
			m_position[0] = events->data[0];
			m_position[1] = events->data[1];
			break;

		case MWIN_EVENT_MOUSE_BUTTON_DOWN:
			mouse->downButton(events->data[0]);
			break;

		case MWIN_EVENT_MOUSE_BUTTON_UP:
			mouse->upButton(events->data[0]);
			break;

		case MWIN_EVENT_MOUSE_WHEEL_MOVE:
			mouse->setWheelDirection(events->data[0]);
			break;

		case MWIN_EVENT_MOUSE_MOVE:
			mouse->setPosition(events->data[0], events->data[1]);
			break;
	}

	if(m_pointerEvent)
		m_pointerEvent(events);
}

bool BWindow::isMouseOverWindow(void)
{
	BMouse * mouse = BMouse::getInstance();
	int x = mouse->getXPosition();
	int y = mouse->getYPosition();

	if(x >= 0 && y >= 0 && x < (int)getWidth() && y < (int)getHeight())
		return true;

	return false;
}

unsigned long BWindow::getSystemTick(void)
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);

	return ((currentTime.tv_sec - startTime.tv_sec) * 1000 + (currentTime.tv_usec - startTime.tv_usec)/1000.0) + 0.5;
}

bool BWindow::onEvents(void)
{
	while(XPending(display))
	{
		MWinEvent mevent;

		XEvent event;
		XNextEvent(display, &event);

		switch(event.type)
		{
			case Expose:
			{
				if(event.xexpose.count != 0)
					break;
				// refresh
				break;
			}

			case ButtonPress:
			{
				// A mouse button was pressed or a scrolling event occurred
				if(event.xbutton.button == Button1)
				{
					mevent.type = MWIN_EVENT_MOUSE_BUTTON_DOWN;
					mevent.data[0] = MMOUSE_BUTTON_LEFT;
					sendEvents(&mevent);
				}
				else if(event.xbutton.button == Button2)
				{
					mevent.type = MWIN_EVENT_MOUSE_BUTTON_DOWN;
					mevent.data[0] = MMOUSE_BUTTON_MIDDLE;
					sendEvents(&mevent);
				}
				else if(event.xbutton.button == Button3)
				{
					mevent.type = MWIN_EVENT_MOUSE_BUTTON_DOWN;
					mevent.data[0] = MMOUSE_BUTTON_RIGHT;
					sendEvents(&mevent);
				}

				// XFree86 3.3.2 and later translates mouse wheel up/down into
				// mouse button 4 & 5 presses
				else if(event.xbutton.button == Button4)
				{
					mevent.type = MWIN_EVENT_MOUSE_WHEEL_MOVE;
					mevent.data[0] = 1;
					sendEvents(&mevent);
				}
				else if( event.xbutton.button == Button5 )
				{
					mevent.type = MWIN_EVENT_MOUSE_WHEEL_MOVE;
					mevent.data[0] = -1;
					sendEvents(&mevent);
				}
				break;
			}

			case ButtonRelease:
			{
				if(event.xbutton.button == Button1)
				{
					mevent.type = MWIN_EVENT_MOUSE_BUTTON_UP;
					mevent.data[0] = MMOUSE_BUTTON_LEFT;
					sendEvents(&mevent);
				}
				else if(event.xbutton.button == Button2)
				{
					mevent.type = MWIN_EVENT_MOUSE_BUTTON_UP;
					mevent.data[0] = MMOUSE_BUTTON_MIDDLE;
					sendEvents(&mevent);
				}
				else if(event.xbutton.button == Button3)
				{
					mevent.type = MWIN_EVENT_MOUSE_BUTTON_UP;
					mevent.data[0] = MMOUSE_BUTTON_RIGHT;
					sendEvents(&mevent);
				}
				break;
			}

			case KeyPress:
			{
				int key = translateKey(event.xkey.keycode);
				if(key > 0 && key < 256)
				{
					mevent.type = MWIN_EVENT_KEY_DOWN;
					mevent.data[0] = key;
					sendEvents(&mevent);
				}

				int car = translateChar(&event.xkey);

				//if(car == 127 || car == 32 || car == 13 || car == 9) // not return, space, delete etc..
				//	break;
				if(car == -1) 
					break;

				mevent.type = MWIN_EVENT_CHAR;
				mevent.data[0] = car;
				sendEvents(&mevent);

				break;
			}

			case KeyRelease:
			{
				int key = translateKey(event.xkey.keycode);
				if(key > 0 && key < 256)
				{
					mevent.type = MWIN_EVENT_KEY_UP;
					mevent.data[0] = key;
					sendEvents(&mevent);
				}

				break;
			}

			case MotionNotify:
			{
				mevent.type = MWIN_EVENT_MOUSE_MOVE;
				mevent.data[0] = event.xmotion.x;
				mevent.data[1] = event.xmotion.y;
				sendEvents(&mevent);
				break;
			}

			case ConfigureNotify:
			{
				if(event.xconfigure.width != m_width || event.xconfigure.height != m_height)
				{
					mevent.type = MWIN_EVENT_WINDOW_RESIZE;
					mevent.data[0] = event.xconfigure.width;
					mevent.data[1] = event.xconfigure.height;
					sendEvents(&mevent);
				}
				break;
			}

			case FocusIn:
			{
				m_focus = true;
				break;
			}

			case FocusOut:
			{
				m_focus = false;
				break;
			}

			case DestroyNotify:
			{
				mevent.type = MWIN_EVENT_WINDOW_CLOSE;
				sendEvents(&mevent);
				break;
			}

			case ClientMessage:
			{
				if((Atom)event.xclient.data.l[0] == wmDelete)
				{
					mevent.type = MWIN_EVENT_WINDOW_CLOSE;
					sendEvents(&mevent);
				}
				break;
			}

			default:
				break;
		}
	}

#ifdef linux
	BWindow* window = BWindow::getInstance();

	BJoystick* joystick = window->getJoystick1();
	updateJoystick(joystick, &joystick1, window, MWIN_EVENT_JOYSTICK1_UPDATE);

	joystick = window->getJoystick2();
	updateJoystick(joystick, &joystick2, window, MWIN_EVENT_JOYSTICK2_UPDATE);	
#endif
	
	return true;
}

void BWindow::swapBuffer(void)
{
	glXSwapBuffers(display, window);
}

bool BWindow::create(const char * title, unsigned int width, unsigned int height, int colorBits, bool fullscreen)
{
	static int dblBuf[] = {GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};
	XVisualInfo * vi;
	Colormap cmap;
	XSetWindowAttributes swa;


	// open display
	display = XOpenDisplay(NULL);

	vi = glXChooseVisual(display, DefaultScreen(display), dblBuf);
	context = glXCreateContext(display, vi, None, True);
	rootWindow = RootWindow(display,vi->screen);
	cmap = XCreateColormap(display,rootWindow,vi->visual,AllocNone);
	swa.colormap = cmap; swa.border_pixel = 0;

	// fullscreen
#ifndef __CYGWIN__
	
	int vmMajor, vmMinor;
	if(XF86VidModeQueryVersion(display, &vmMajor, &vmMinor) && fullscreen)
	{
		screen = DefaultScreen(display);

		int modeNum, screenMode=0;
		XF86VidModeModeInfo **modes;
		XF86VidModeGetAllModeLines(display, screen, &modeNum, &modes);

		if(modeNum > 0)
		{
			desktopMode = *modes[0];

			for(int i=0; i<modeNum; i++)
			{
				if((modes[i]->hdisplay == width) && (modes[i]->vdisplay == height))
					screenMode = i;
			}

			XF86VidModeSwitchToMode(display, screen, modes[screenMode]);
			XF86VidModeSetViewPort(display, screen, 0, 0);
			m_width = modes[screenMode]->hdisplay;
			m_height = modes[screenMode]->vdisplay;

			XFree(modes);

			swa.override_redirect = True;
			swa.event_mask =
			StructureNotifyMask | KeyPressMask | KeyReleaseMask |
			PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
			ExposureMask | FocusChangeMask | VisibilityChangeMask;

			window = XCreateWindow(
				display, rootWindow,
				0, 0, m_width, m_height, 0, vi->depth, InputOutput, vi->visual,
				CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
				&swa);

			XWarpPointer(display, None, window, 0, 0, 0, 0, 0, 0);
			XMapRaised(display, window);
			XGrabKeyboard(display, window, True, GrabModeAsync, GrabModeAsync, CurrentTime);
			XGrabPointer(display, window, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);

			m_fullscreen = true;
		}
		else
		{
			return false;
		}
	}
	
	else
		
#endif
		
	// window
	{
		m_fullscreen = false;

		swa.event_mask =
		StructureNotifyMask | KeyPressMask | KeyReleaseMask |
		PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
		ExposureMask | FocusChangeMask | VisibilityChangeMask;

		m_width = width;
		m_height = height;

		window = XCreateWindow(
			display, rootWindow,
			0, 0, m_width, m_height, 0, vi->depth, InputOutput, vi->visual,
			CWBorderPixel | CWColormap | CWEventMask,
			&swa);

		wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(display, window, &wmDelete, 1);

		XSetStandardProperties(display, window, title, title, None, NULL, 0, NULL);
		XMapWindow(display, window);
	}

	// make current context
	glXMakeCurrent(display, window, context);

	// cursor
	nullCursor = createNULLCursor(display, rootWindow);

	return true;
}

void BWindow::execute(const char * path, const char * args)
{
	char dst[512];
	memset(dst, 0, 512);

	strcat(dst, path);
	strcat(dst, " ");
	strcat(dst, args);

	system(dst);
}

void BWindow::sleep(double time)
{
	if( time == 0.0 )
    {
		sched_yield();
		return;
    }
	
    struct timeval  currenttime;
    struct timespec wait;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    long dt_sec, dt_usec;
	
    // Not all pthread implementations have a pthread_sleep() function. We
    // do it the portable way, using a timed wait for a condition that we
    // will never signal. NOTE: The unistd functions sleep/usleep suspends
    // the entire PROCESS, not a signle thread, which is why we can not
    // use them to implement glfwSleep.
	
    // Set timeout time, relatvie to current time
    gettimeofday( &currenttime, NULL );
    dt_sec  = (long) time;
    dt_usec = (long) ((time - (double)dt_sec) * 1000000.0);
    wait.tv_nsec = (currenttime.tv_usec + dt_usec) * 1000L;
    if( wait.tv_nsec > 1000000000L )
    {
        wait.tv_nsec -= 1000000000L;
        dt_sec++;
    }
    wait.tv_sec  = currenttime.tv_sec + dt_sec;
	
    // Initialize condition and mutex objects
    pthread_mutex_init( &mutex, NULL );
    pthread_cond_init( &cond, NULL );
	
    // Do a timed wait
    pthread_mutex_lock( &mutex );
    pthread_cond_timedwait( &cond, &mutex, &wait );
    pthread_mutex_unlock( &mutex );
	
    // Destroy condition and mutex objects
    pthread_mutex_destroy( &mutex );
    pthread_cond_destroy( &cond );
}

bool BWindow::getOpenMultipleFiles(const char * title, const char * filter, string * repertory, list <string> * filesList, const char * startPath)
{
	return false;
}

const char * BWindow::getOpenDir(const char * title, const char * startPath)
{
	return NULL;
}

const char * BWindow::getOpenFilename(const char * title, const char * filter, const char * startPath)
{
	return NULL;
}

const char * BWindow::getSaveFilename(const char * title, const char * filter, const char * startPath)
{
	return NULL;
}
