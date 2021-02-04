#ifndef KEYBOARD_PRESS_REGISTRATION_DATA
#define KEYBOARD_PRESS_REGISTRATION_DATA

//forward declaration
class RegisterKeyPressedCommand;
class DeregisterKeyPressedCommand;
class Inputable;

#include "RegistrationState.h"
#include "Keyboard.h"
//for list ref
#include "SingleKeyEventManager.h"

class KeyboardPressRegistrationData
{
public:
	RegistrationState keyPressRegState;
	SingleKeyEventManager::InputableListRef keyPressListRef;
	RegisterKeyPressedCommand* keyPressRegistrationCmdPtr;
	DeregisterKeyPressedCommand* keyPressDeregistrationCmdPtr;

	KeyboardPressRegistrationData() = delete;
	~KeyboardPressRegistrationData();
	KeyboardPressRegistrationData(Inputable* in, AZUL_KEY k);

	void setKeyPressListRef(SingleKeyEventManager::InputableListRef newRef);
	SingleKeyEventManager::InputableListRef getKeyPressListRef() const;
};

#endif KEYBOARD_PRESS_REGISTRATION_DATA