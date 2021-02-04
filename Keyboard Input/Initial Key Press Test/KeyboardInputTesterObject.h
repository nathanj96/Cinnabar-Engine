//First trying to figure out how to detect keyboard input

#ifndef KEYBOARD_INPUT_TESTER_OBJECT
#define KEYBOARD_INPUT_TESTER_OBJECT

class RegisterUpdateCommand;
class KeyTester;
#include "GameObject.h"

class KeyboardInputTesterObject : public GameObject
{
private:
	KeyTester* keyTesterRef;
public:
	KeyboardInputTesterObject();
	KeyboardInputTesterObject(const KeyboardInputTesterObject&) = default;
	KeyboardInputTesterObject& operator=(const KeyboardInputTesterObject&) = default;
	~KeyboardInputTesterObject();

	virtual void Update();
};

#endif KEYBOARD_INPUT_TESTER_OBJECT