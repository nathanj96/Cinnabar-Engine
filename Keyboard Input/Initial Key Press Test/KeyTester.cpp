#include "KeyTester.h"

KeyTester::KeyTester(AZUL_KEY key) : keyToTest(key), prevKeyState(false)
{
};

void KeyTester::TestKey()
{
	//GetKeyState returns true if the key is being held down and false if it is not
	if (Keyboard::GetKeyState(keyToTest) && !prevKeyState)
	{
		DebugMsg::out("Key pressed\n");
		prevKeyState = true;
	}
	else if(!Keyboard::GetKeyState(keyToTest) && prevKeyState)
	{
		DebugMsg::out("Key released\n");
		prevKeyState = false;
	}
}