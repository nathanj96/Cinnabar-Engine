#include "KeyboardReleaseRegistrationData.h"

#include "RegisterKeyReleasedCommand.h"
#include "DeregisterKeyReleasedCommand.h"
#include "Inputable.h"

KeyboardReleaseRegistrationData::KeyboardReleaseRegistrationData(Inputable* in, AZUL_KEY k)
{
	keyReleaseRegState = RegistrationState::CURRENTLY_DEREGISTERED;
	keyReleaseRegistrationCmdPtr = new RegisterKeyReleasedCommand(in, k);
	keyReleaseDeregistrationCmdPtr = new DeregisterKeyReleasedCommand(in, k);
}

KeyboardReleaseRegistrationData::~KeyboardReleaseRegistrationData()
{
	delete keyReleaseRegistrationCmdPtr;
	delete keyReleaseDeregistrationCmdPtr;
}


void KeyboardReleaseRegistrationData::setKeyReleaseListRef(SingleKeyEventManager::InputableListRef newRef)
{
	keyReleaseListRef = newRef;
}


SingleKeyEventManager::InputableListRef KeyboardReleaseRegistrationData::getKeyReleaseListRef() const
{
	return keyReleaseListRef;
}