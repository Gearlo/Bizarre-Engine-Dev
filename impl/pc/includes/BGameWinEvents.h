/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Maratis
// BGameWinEvents.h
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


#ifndef _M_GAME_WIN_EVENTS_H
#define _M_GAME_WIN_EVENTS_H


const char * getKeyName(unsigned int key)
{
	// ascii
	if(key >= 65 && key <= 90)
	{
		static char name[2] = {0, 0};
		name[0] = (char)key;
		return name;
	}

	// keyboard keys
	switch(key)
	{
	case BKey_BACKSPACE: return "BACKSPACE";
	case BKey_TAB:		 return "TAB";
	case BKey_ESCAPE:	 return "ESCAPE";
	case BKey_SPACE:	 return "SPACE";
	case BKey_DELETE:	 return "DELETE";

	case BKey_KP_ENTER:
	case BKey_RETURN:	 return "ENTER";
	case BKey_UP:		 return "UP";
	case BKey_DOWN:		 return "DOWN";
	case BKey_LEFT:		 return "LEFT";
	case BKey_RIGHT:	 return "RIGHT";
	case BKey_F1:		 return "F1";
	case BKey_F2:		 return "F2";
	case BKey_F3:		 return "F3";
	case BKey_F4:		 return "F4";
	case BKey_F5:		 return "F5";
	case BKey_F6:		 return "F6";
	case BKey_F7:		 return "F7";
	case BKey_F8:		 return "F8";
	case BKey_F9:		 return "F9";
	case BKey_F10:		 return "F10";
	case BKey_F11:		 return "F11";
	case BKey_F12:		 return "F12";
	case BKey_RSHIFT:	 return "RSHIFT";
	case BKey_LSHIFT:	 return "LSHIFT";
	case BKey_RCONTROL:	 return "RCONTROL";
	case BKey_LCONTROL:	 return "LCONTROL";
	case BKey_RALT:		 return "RALT";
	case BKey_LALT:		 return "LALT";

	
	case '0': case BKey_KP0: return "0";
    case '1': case BKey_KP1: return "1";
    case '2': case BKey_KP2: return "2";
    case '3': case BKey_KP3: return "3";
    case '4': case BKey_KP4: return "4";
    case '5': case BKey_KP5: return "5";
    case '6': case BKey_KP6: return "6";
    case '7': case BKey_KP7: return "7";
    case '8': case BKey_KP8: return "8";
    case '9': case BKey_KP9: return "9";
	
	}

	return NULL;
}

void gameWinEvents(MWinEvent * windowEvents)
{
	BWindow* window = BWindow::getInstance();
	BInputContext * input = Bizarre::getInstance()->getInputContext();
	BMouse * mouse = BMouse::getInstance();

	
	switch(windowEvents->type)
	{
	case MWIN_EVENT_MOUSE_BUTTON_DOWN:
		switch(windowEvents->data[0])
		{
		case MMOUSE_BUTTON_LEFT:
			input->downKey("MOUSE_BUTTON1");
			break;
		case MMOUSE_BUTTON_MIDDLE:
			input->downKey("MOUSE_BUTTON2");
			break;
		case MMOUSE_BUTTON_RIGHT:
			input->downKey("MOUSE_BUTTON3");
			break;
		}
		break;

	case MWIN_EVENT_MOUSE_BUTTON_UP:
		switch(windowEvents->data[0])
		{
		case MMOUSE_BUTTON_LEFT:
			input->upKey("MOUSE_BUTTON1");
			break;
		case MMOUSE_BUTTON_MIDDLE:
			input->upKey("MOUSE_BUTTON2");
			break;
		case MMOUSE_BUTTON_RIGHT:
			input->upKey("MOUSE_BUTTON3");
			break;
		}
		break;

	case MWIN_EVENT_MOUSE_MOVE:
		input->setAxis("MOUSE_X", (float)(mouse->getXPosition() / (float)window->getWidth()));
		input->setAxis("MOUSE_Y", (float)(mouse->getYPosition() / (float)window->getHeight()));
		break;

	case MWIN_EVENT_MOUSE_WHEEL_MOVE:
		input->setAxis("MOUSE_WHEEL", (float)mouse->getWheelDirection());
		break;
			
	case MWIN_EVENT_KEY_DOWN:
		{
			unsigned int key = windowEvents->data[0];
			const char * name = getKeyName(key);
			if(name)
				input->downKey(name);

			//std::cout << "keydown " << name << std::endl;
		}
		break;

	case MWIN_EVENT_KEY_UP:
		{
			unsigned int key = windowEvents->data[0];
			const char * name = getKeyName(key);
			if(name)
				input->upKey(name);
			//std::cout << "keyUp " << name << std::endl;
		}
		
		break;


	case MWIN_EVENT_CHAR:
        {
            unsigned int key = windowEvents->data[0];
            const char * name = getKeyName(key);
            if(name)
                input->downKey(name);
        }
        break; 

	case MWIN_EVENT_JOYSTICK1_UPDATE:
		{
			BJoystick * joystick = window->getJoystick1();

			char name[32];
			for(int i=0; i<8; i++)
			{
				if(joystick->onKeyDown(i))
				{
					sprintf(name, "JOY1_BUTTON%d", i+1);
					input->downKey(name);
				}
				else if(joystick->onKeyUp(i))
				{
					sprintf(name, "JOY1_BUTTON%d", i+1);
					input->upKey(name);
				}
			}

			input->setAxis("JOY1_X", joystick->getX());
			input->setAxis("JOY1_Y", joystick->getY());
			input->setAxis("JOY1_Z", joystick->getZ());
			input->setAxis("JOY1_R", joystick->getR());
			input->setAxis("JOY1_U", joystick->getU());
			input->setAxis("JOY1_V", joystick->getV());
		}
		break;

	case MWIN_EVENT_JOYSTICK2_UPDATE:
		{
			BJoystick * joystick = window->getJoystick2();

			char name[32];
			for(int i=0; i<8; i++)
			{
				if(joystick->onKeyDown(i))
				{
					sprintf(name, "JOY2_BUTTON%d", i+1);
					input->downKey(name);
				}
				else if(joystick->onKeyUp(i))
				{
					sprintf(name, "JOY2_BUTTON%d", i+1);
					input->upKey(name);
				}
			}

			input->setAxis("JOY2_X", joystick->getX());
			input->setAxis("JOY2_Y", joystick->getY());
			input->setAxis("JOY2_Z", joystick->getZ());
			input->setAxis("JOY2_R", joystick->getR());
			input->setAxis("JOY2_U", joystick->getU());
			input->setAxis("JOY2_V", joystick->getV());
		}
		break;
	}
}

#endif