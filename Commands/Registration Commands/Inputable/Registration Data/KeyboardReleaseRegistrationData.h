#ifndef KEYBOARD_RELEASE_REGISTRATION_DATA
#define KEYBOARD_RELEASE_REGISTRATION_DATA

//forward declaration
class RegisterKeyReleasedCommand;
class DeregisterKeyReleasedCommand;
class Inputable;

#include "RegistrationState.h"
#include "Keyboard.h"
//for list ref
#include "SingleKeyEventManager.h"

class KeyboardReleaseRegistrationData
{
public:
	RegistrationState keyReleaseRegState;
	SingleKeyEventManager::InputableListRef keyReleaseListRef;
	RegisterKeyReleasedCommand* keyReleaseRegistrationCmdPtr;
	DeregisterKeyReleasedCommand* keyReleaseDeregistrationCmdPtr;

	KeyboardReleaseRegistrationData() = delete;
	~KeyboardReleaseRegistrationData();
	KeyboardReleaseRegistrationData(Inputable* in, AZUL_KEY k);

	void setKeyReleaseListRef(SingleKeyEventManager::InputableListRef newRef);
	SingleKeyEventManager::InputableListRef getKeyReleaseListRef() const;
};

#endif KEYBOARD_RELEASE_REGISTRATION_DATA