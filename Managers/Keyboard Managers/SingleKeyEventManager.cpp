#include "SingleKeyEventManager.h"
#include "InputableAttorney.h"
#include "DebugOut.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k) : key(k), keyPrevFrameState(false)
{
};

void SingleKeyEventManager::DeregisterKeyPress(Inputable* in)
{
	keyPressedList.erase(in->getKeyPressListRef(key));
}

void SingleKeyEventManager::DeregisterKeyRelease(Inputable* in)
{
	keyReleasedList.erase(in->getKeyReleaseListRef(key));
}

void SingleKeyEventManager::RegisterKeyPress(Inputable* in)
{
	InputableAttorney::Registration::setKeyPressListRef(in, key, keyPressedList.insert(keyPressedList.end(), in));
}

void SingleKeyEventManager::RegisterKeyRelease(Inputable* in)
{
	InputableAttorney::Registration::setKeyReleaseListRef(in, key, keyReleasedList.insert(keyReleasedList.end(), in));
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	//GetKeyState returns true if the key is being held down and false if it is not
	if (Keyboard::GetKeyState(key) && !keyPrevFrameState)
	{
		//extremely hacky code to print which specific key had its press event fire
		std::string msg = getKeyName(key) + " key pressed\n";
		const char* msgCStr = msg.c_str();
		DebugMsg::out(const_cast<char*>(msgCStr));
		
		InputableList::iterator it;
		for (it = keyPressedList.begin(); it != keyPressedList.end(); it++)
		{
			InputableAttorney::keyPressed((*it), key);
		}
		keyPrevFrameState = true;
	}
	else if (!Keyboard::GetKeyState(key) && keyPrevFrameState)
	{
		//extremely hacky code to print which specific key had its press event fire
		std::string msg = getKeyName(key) + " key released\n";
		const char* msgCStr = msg.c_str();
		DebugMsg::out(const_cast<char*>(msgCStr));
		
		InputableList::iterator it;
		for (it = keyReleasedList.begin(); it != keyReleasedList.end(); it++)
		{
			InputableAttorney::keyReleased((*it), key);
		}
		keyPrevFrameState = false;
	}
}

//Use to print on screen what key was pressed/released
std::string SingleKeyEventManager::getKeyName(AZUL_KEY k) const
{
	std::string retString;
	switch (k)
	{
	case(AZUL_KEY::KEY_SPACE):
	{
		retString = "Space";
		break;
	}
	case(AZUL_KEY::KEY_APOSTROPHE):
	{
		retString = "Apostraphe";
		break;
	}
	case(AZUL_KEY::KEY_COMMA):
	{
		retString = "Comma";
		break;
	}
	case(AZUL_KEY::KEY_MINUS):
	{
		retString = "Minus";
		break;
	}
	case(AZUL_KEY::KEY_PERIOD):
	{
		retString = "Period";
		break;
	}
	case(AZUL_KEY::KEY_SLASH):
	{
		retString = "Slash";
		break;
	}
	case(AZUL_KEY::KEY_0):
	{
		retString = "0";
		break;
	}
	case(AZUL_KEY::KEY_1):
	{
		retString = "1";
		break;
	}
	case(AZUL_KEY::KEY_2):
	{
		retString = "2";
		break;
	}
	case(AZUL_KEY::KEY_3):
	{
		retString = "3";
		break;
	}
	case(AZUL_KEY::KEY_4):
	{
		retString = "4";
		break;
	}
	case(AZUL_KEY::KEY_5):
	{
		retString = "5";
		break;
	}
	case(AZUL_KEY::KEY_6):
	{
		retString = "6";
		break;
	}
	case(AZUL_KEY::KEY_7):
	{
		retString = "7";
		break;
	}
	case(AZUL_KEY::KEY_8):
	{
		retString = "8";
		break;
	}
	case(AZUL_KEY::KEY_9):
	{
		retString = "9";
		break;
	}
	case(AZUL_KEY::KEY_SEMICOLON):
	{
		retString = "Semicolon";
		break;
	}
	case(AZUL_KEY::KEY_EQUAL):
	{
		retString = "Equal";
		break;
	}
	case(AZUL_KEY::KEY_A):
	{
		retString = "A";
		break;
	}
	case(AZUL_KEY::KEY_B):
	{
		retString = "B";
		break;
	}
	case(AZUL_KEY::KEY_C):
	{
		retString = "C";
		break;
	}
	case(AZUL_KEY::KEY_D):
	{
		retString = "D";
		break;
	}
	case(AZUL_KEY::KEY_E):
	{
		retString = "E";
		break;
	}
	case(AZUL_KEY::KEY_F):
	{
		retString = "F";
		break;
	}
	case(AZUL_KEY::KEY_G):
	{
		retString = "G";
		break;
	}
	case(AZUL_KEY::KEY_H):
	{
		retString = "H";
		break;
	}
	case(AZUL_KEY::KEY_I):
	{
		retString = "I";
		break;
	}
	case(AZUL_KEY::KEY_J):
	{
		retString = "J";
		break;
	}
	case(AZUL_KEY::KEY_K):
	{
		retString = "K";
		break;
	}
	case(AZUL_KEY::KEY_L):
	{
		retString = "L";
		break;
	}
	case(AZUL_KEY::KEY_M):
	{
		retString = "M";
		break;
	}
	case(AZUL_KEY::KEY_N):
	{
		retString = "N";
		break;
	}
	case(AZUL_KEY::KEY_O):
	{
		retString = "O";
		break;
	}
	case(AZUL_KEY::KEY_P):
	{
		retString = "P";
		break;
	}
	case(AZUL_KEY::KEY_Q):
	{
		retString = "Q";
		break;
	}
	case(AZUL_KEY::KEY_R):
	{
		retString = "R";
		break;
	}
	case(AZUL_KEY::KEY_S):
	{
		retString = "S";
		break;
	}
	case(AZUL_KEY::KEY_T):
	{
		retString = "T";
		break;
	}
	case(AZUL_KEY::KEY_U):
	{
		retString = "U";
		break;
	}
	case(AZUL_KEY::KEY_V):
	{
		retString = "V";
		break;
	}
	case(AZUL_KEY::KEY_W):
	{
		retString = "W";
		break;
	}
	case(AZUL_KEY::KEY_X):
	{
		retString = "X";
		break;
	}
	case(AZUL_KEY::KEY_Y):
	{
		retString = "Y";
		break;
	}
	case(AZUL_KEY::KEY_Z):
	{
		retString = "Z";
		break;
	}
	case(AZUL_KEY::KEY_LEFT_BRACKET):
	{
		retString = "[";
		break;
	}
	case(AZUL_KEY::KEY_BACKSLASH):
	{
		retString = "'\'";
		break;
	}
	case(AZUL_KEY::KEY_RIGHT_BRACKET):
	{
		retString = "]";
		break;
	}
	case(AZUL_KEY::KEY_GRAVE_ACCENT):
	{
		retString = "`";
		break;
	}
	case(AZUL_KEY::KEY_WORLD_1):
	{
		retString = "Key world 1";
		break;
	}
	case(AZUL_KEY::KEY_WORLD_2):
	{
		retString = "Key world 2";
		break;
	}

	case(AZUL_KEY::KEY_ARROW_UP):
	{
		retString = "Up arrow";
		break;
	}
	case(AZUL_KEY::KEY_ARROW_DOWN):
	{
		retString = "Down arrow";
		break;
	}
	case(AZUL_KEY::KEY_ARROW_LEFT):
	{
		retString = "Left arrow";
		break;
	}
	case(AZUL_KEY::KEY_ARROW_RIGHT):
	{
		retString = "Right arrow";
		break;
	}

	/* Function keys */
	case(AZUL_KEY::KEY_ESCAPE):
	{
		retString = "Escape";
		break;
	}
	case(AZUL_KEY::KEY_ENTER):
	{
		retString = "Enter";
		break;
	}
	case(AZUL_KEY::KEY_TAB):
	{
		retString = "Tab";
		break;
	}
	case(AZUL_KEY::KEY_BACKSPACE):
	{
		retString = "Backspace";
		break;
	}
	case(AZUL_KEY::KEY_INSERT):
	{
		retString = "Insert";
		break;
	}
	case(AZUL_KEY::KEY_DELETE):
	{
		retString = "Delete";
		break;
	}
	//KEY_RIGHT           = GLFW_KEY_RIGHT,
	//KEY_LEFT            = GLFW_KEY_LEFT,
	//KEY_DOWN            = GLFW_KEY_DOWN,
	//KEY_UP              = GLFW_KEY_UP,
	case(AZUL_KEY::KEY_PAGE_UP):
	{
		retString = "Page up";
		break;
	}
	case(AZUL_KEY::KEY_PAGE_DOWN):
	{
		retString = "Page down";
		break;
	}
	case(AZUL_KEY::KEY_HOME):
	{
		retString = "Home";
		break;
	}
	case(AZUL_KEY::KEY_END):
	{
		retString = "End";
		break;
	}
	case(AZUL_KEY::KEY_CAPS_LOCK):
	{
		retString = "Caps lock";
		break;
	}
	case(AZUL_KEY::KEY_SCROLL_LOCK):
	{
		retString = "Scroll lock";
		break;
	}
	case(AZUL_KEY::KEY_NUM_LOCK):
	{
		retString = "Num lock";
		break;
	}
	// KEY_PRINT_SCREEN    = 283,
	case(AZUL_KEY::KEY_PAUSE):
	{
		retString = "Pause";
		break;
	}
	case(AZUL_KEY::KEY_F1):
	{
		retString = "F1";
		break;
	}
	case(AZUL_KEY::KEY_F2):
	{
		retString = "F2";
		break;
	}
	case(AZUL_KEY::KEY_F3):
	{
		retString = "F3";
		break;
	}
	case(AZUL_KEY::KEY_F4):
	{
		retString = "F4";
		break;
	}
	case(AZUL_KEY::KEY_F5):
	{
		retString = "F5";
		break;
	}
	case(AZUL_KEY::KEY_F6):
	{
		retString = "F6";
		break;
	}
	case(AZUL_KEY::KEY_F7):
	{
		retString = "F7";
		break;
	}
	case(AZUL_KEY::KEY_F8):
	{
		retString = "F8";
		break;
	}
	case(AZUL_KEY::KEY_F9):
	{
		retString = "F9";
		break;
	}
	case(AZUL_KEY::KEY_F10):
	{
		retString = "F10";
		break;
	}
	case(AZUL_KEY::KEY_F11):
	{
		retString = "F11";
		break;
	}
	case(AZUL_KEY::KEY_F12):
	{
		retString = "F12";
		break;
	}
	case(AZUL_KEY::KEY_F13):
	{
		retString = "F13";
		break;
	}
	case(AZUL_KEY::KEY_F14):
	{
		retString = "F14";
		break;
	}
	case(AZUL_KEY::KEY_F15):
	{
		retString = "F15";
		break;
	}
	case(AZUL_KEY::KEY_F16):
	{
		retString = "F16";
		break;
	}
	case(AZUL_KEY::KEY_F17):
	{
		retString = "F17";
		break;
	}
	case(AZUL_KEY::KEY_F18):
	{
		retString = "F18";
		break;
	}
	case(AZUL_KEY::KEY_F19):
	{
		retString = "F19";
		break;
	}
	case(AZUL_KEY::KEY_F20):
	{
		retString = "F20";
		break;
	}
	case(AZUL_KEY::KEY_F21):
	{
		retString = "F21";
		break;
	}
	case(AZUL_KEY::KEY_F22):
	{
		retString = "F22";
		break;
	}
	case(AZUL_KEY::KEY_F23):
	{
		retString = "F23";
		break;
	}
	case(AZUL_KEY::KEY_F24):
	{
		retString = "F24";
		break;
	}
	case(AZUL_KEY::KEY_F25):
	{
		retString = "F25";
		break;
	}
	case(AZUL_KEY::KEY_KP_0):
	{
		retString = "Keypad 0";
		break;
	}
	case(AZUL_KEY::KEY_KP_1):
	{
		retString = "Keypad 1";
		break;
	}
	case(AZUL_KEY::KEY_KP_2):
	{
		retString = "Keypad 2";
		break;
	}
	case(AZUL_KEY::KEY_KP_3):
	{
		retString = "Keypad 3";
		break;
	}
	case(AZUL_KEY::KEY_KP_4):
	{
		retString = "Keypad 4";
		break;
	}
	case(AZUL_KEY::KEY_KP_5):
	{
		retString = "Keypad 5";
		break;
	}
	case(AZUL_KEY::KEY_KP_6):
	{
		retString = "Keypad 6";
		break;
	}
	case(AZUL_KEY::KEY_KP_7):
	{
		retString = "Keypad 7";
		break;
	}
	case(AZUL_KEY::KEY_KP_8):
	{
		retString = "Keypad 8";
		break;
	}
	case(AZUL_KEY::KEY_KP_9):
	{
		retString = "Keypad 9";
		break;
	}
	case(AZUL_KEY::KEY_KP_DECIMAL):
	{
		retString = "Keypad decimal";
		break;
	}
	case(AZUL_KEY::KEY_KP_DIVIDE):
	{
		retString = "Keypad divide";
		break;
	}
	case(AZUL_KEY::KEY_KP_MULTIPLY):
	{
		retString = "Keypad Multiply";
		break;
	}
	case(AZUL_KEY::KEY_KP_SUBTRACT):
	{
		retString = "Keypad subtract";
		break;
	}
	case(AZUL_KEY::KEY_KP_ADD):
	{
		retString = "Keypad add";
		break;
	}
	case(AZUL_KEY::KEY_KP_ENTER):
	{
		retString = "Keypad enter";
		break;
	}
	case(AZUL_KEY::KEY_KP_EQUAL):
	{
		retString = "Keypad equal";
		break;
	}
	case(AZUL_KEY::KEY_LEFT_SHIFT):
	{
		retString = "Left shift";
		break;
	}
	case(AZUL_KEY::KEY_LEFT_CONTROL):
	{
		retString = "Left control";
		break;
	}
	case(AZUL_KEY::KEY_LEFT_ALT):
	{
		retString = "Left alt";
		break;
	}
	case(AZUL_KEY::KEY_LEFT_SUPER):
	{
		retString = "Left super";
		break;
	}
	case(AZUL_KEY::KEY_RIGHT_SHIFT):
	{
		retString = "Right shift";
		break;
	}
	case(AZUL_KEY::KEY_RIGHT_CONTROL):
	{
		retString = "Right control";
		break;
	}
	case(AZUL_KEY::KEY_RIGHT_ALT):
	{
		retString = "Right alt";
		break;
	}
	case(AZUL_KEY::KEY_RIGHT_SUPER):
	{
		retString = "Right super";
		break;
	}
	case(AZUL_KEY::KEY_MENU):
	{
		retString = "Menu";
		break;
	}
	default:
	{
		retString = "INVALID_KEY";
		break;
	}
	}
	return retString;
}