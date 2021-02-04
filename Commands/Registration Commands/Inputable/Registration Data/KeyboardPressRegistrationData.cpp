#include "KeyboardPressRegistrationData.h"

#include "RegisterKeyPressedCommand.h"
#include "DeregisterKeyPressedCommand.h"
#include "Inputable.h"

KeyboardPressRegistrationData::KeyboardPressRegistrationData(Inputable* in, AZUL_KEY k)
{
	keyPressRegState = RegistrationState::CURRENTLY_DEREGISTERED;
	keyPressRegistrationCmdPtr = new RegisterKeyPressedCommand(in, k);
	keyPressDeregistrationCmdPtr = new DeregisterKeyPressedCommand(in, k);
}

KeyboardPressRegistrationData::~KeyboardPressRegistrationData()
{
	delete keyPressRegistrationCmdPtr;
	delete keyPressDeregistrationCmdPtr;
}

void KeyboardPressRegistrationData::setKeyPressListRef(SingleKeyEventManager::InputableListRef newRef)
{
	keyPressListRef = newRef;
}


SingleKeyEventManager::InputableListRef KeyboardPressRegistrationData::getKeyPressListRef() const
{
	return keyPressListRef;
}