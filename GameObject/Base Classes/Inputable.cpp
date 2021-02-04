#include "Inputable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

#include "RegistrationCommandBase.h"
#include "RegisterKeyPressedCommand.h"
#include "DeregisterKeyPressedCommand.h"
#include "RegisterKeyReleasedCommand.h"
#include "DeregisterKeyReleasedCommand.h"
#include "DebugOut.h"

Inputable::~Inputable()
{
	while (!pressRegisteredKeys.empty())
	{
		KeyPressRegistrationMap::iterator it = pressRegisteredKeys.begin();
		delete (*it).second;
		pressRegisteredKeys.erase(it);
	}
	while (!releaseRegisteredKeys.empty())
	{
		KeyReleaseRegistrationMap::iterator it = releaseRegisteredKeys.begin();
		delete (*it).second;
		releaseRegisteredKeys.erase(it);
	}
}

void Inputable::SubmitKeyRegistration(AZUL_KEY k, Inputable::EVENT_TYPE e)
{
	assert(e == Inputable::KEY_PRESS || e == Inputable::KEY_RELEASE);
	if (e == Inputable::KEY_PRESS)
	{
		//check whether the given key is already registered for presses
		KeyPressRegistrationMap::iterator it = pressRegisteredKeys.find(k);
		if (it != pressRegisteredKeys.end())
		{
			KeyboardPressRegistrationData* kbDat = (*it).second;
			assert(kbDat->keyPressRegState == RegistrationState::CURRENTLY_DEREGISTERED);
			SceneAttorney::toInputable::submitInputCommand(kbDat->keyPressRegistrationCmdPtr);
			kbDat->keyPressRegState = RegistrationState::PENDING_REGISTRATION;
		}
		else
		{
			KeyboardPressRegistrationData* newRegData = new KeyboardPressRegistrationData(this, k);
			pressRegisteredKeys.insert(std::pair<AZUL_KEY, KeyboardPressRegistrationData*>(k, newRegData));
			SceneAttorney::toInputable::submitInputCommand(newRegData->keyPressRegistrationCmdPtr);
			newRegData->keyPressRegState = RegistrationState::PENDING_REGISTRATION;
		}
	}
	else if(e == Inputable::KEY_RELEASE)
	{
		//check whether the given key is already registered for releases
		KeyReleaseRegistrationMap::iterator it = releaseRegisteredKeys.find(k);
		if (it != releaseRegisteredKeys.end())
		{
			KeyboardReleaseRegistrationData* kbDat = (*it).second;
			assert(kbDat->keyReleaseRegState == RegistrationState::CURRENTLY_DEREGISTERED);
			SceneAttorney::toInputable::submitInputCommand(kbDat->keyReleaseRegistrationCmdPtr);
			kbDat->keyReleaseRegState = RegistrationState::PENDING_REGISTRATION;
		}
		else
		{
			KeyboardReleaseRegistrationData* newRegData = new KeyboardReleaseRegistrationData(this, k);
			releaseRegisteredKeys.insert(std::pair<AZUL_KEY, KeyboardReleaseRegistrationData*>(k, newRegData));
			SceneAttorney::toInputable::submitInputCommand(newRegData->keyReleaseRegistrationCmdPtr);
			newRegData->keyReleaseRegState = RegistrationState::PENDING_REGISTRATION;
		}
	}
}

void Inputable::SubmitKeyDeregistration(AZUL_KEY k, Inputable::EVENT_TYPE e)
{
	assert(e == Inputable::KEY_PRESS || e == Inputable::KEY_RELEASE);
	if (e == Inputable::KEY_PRESS)
	{
		//check whether the given key is already registered for presses
		KeyPressRegistrationMap::iterator it = pressRegisteredKeys.find(k);
		KeyboardPressRegistrationData* kbDat = (*it).second;
		assert(kbDat->keyPressRegState == RegistrationState::CURRENTLY_REGISTERED);
		SceneAttorney::toInputable::submitInputCommand(kbDat->keyPressDeregistrationCmdPtr);
		kbDat->keyPressRegState = RegistrationState::PENDING_DEREGISTRATION;
	}
	else if (e == Inputable::KEY_RELEASE)
	{
		//check whether the given key is already registered for releases
		KeyReleaseRegistrationMap::iterator it = releaseRegisteredKeys.find(k);
		KeyboardReleaseRegistrationData* kbDat = (*it).second;
		assert(kbDat->keyReleaseRegState == RegistrationState::CURRENTLY_REGISTERED);
		SceneAttorney::toInputable::submitInputCommand(kbDat->keyReleaseDeregistrationCmdPtr);
		kbDat->keyReleaseRegState = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void Inputable::SceneKeyPressRegistration(AZUL_KEY k)
{
	KeyPressRegistrationMap::iterator it = pressRegisteredKeys.find(k);
	KeyboardPressRegistrationData* kbDat = (*it).second;
	assert(kbDat->keyPressRegState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::toInputable::registerKeyPress(this, k);
	kbDat->keyPressRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneKeyReleaseRegistration(AZUL_KEY k)
{
	KeyReleaseRegistrationMap::iterator it = releaseRegisteredKeys.find(k);
	KeyboardReleaseRegistrationData* kbDat = (*it).second;
	assert(kbDat->keyReleaseRegState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::toInputable::registerKeyRelease(this, k);
	kbDat->keyReleaseRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneKeyPressDeregistration(AZUL_KEY k)
{
	KeyPressRegistrationMap::iterator it = pressRegisteredKeys.find(k);
	KeyboardPressRegistrationData* kbDat = (*it).second;
	assert(kbDat->keyPressRegState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::toInputable::deregisterKeyPress(this, k);
	kbDat->keyPressRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Inputable::SceneKeyReleaseDeregistration(AZUL_KEY k)
{
	KeyReleaseRegistrationMap::iterator it = releaseRegisteredKeys.find(k);
	KeyboardReleaseRegistrationData* kbDat = (*it).second;
	assert(kbDat->keyReleaseRegState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::toInputable::deregisterKeyRelease(this, k);
	kbDat->keyReleaseRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Inputable::setKeyPressListRef(AZUL_KEY k, SingleKeyEventManager::InputableListRef newRef)
{
	KeyPressRegistrationMap::iterator it = pressRegisteredKeys.find(k);
	//key should always have a place in the registration map at this point
	assert(it != pressRegisteredKeys.end());
	(*it).second->setKeyPressListRef(newRef);
}

void Inputable::setKeyReleaseListRef(AZUL_KEY k, SingleKeyEventManager::InputableListRef newRef)
{
	KeyReleaseRegistrationMap::iterator it = releaseRegisteredKeys.find(k);
	//key should always have a place in the registration map at this point
	assert(it != releaseRegisteredKeys.end());
	(*it).second->setKeyReleaseListRef(newRef);
}

SingleKeyEventManager::InputableListRef Inputable::getKeyPressListRef(AZUL_KEY k)
{
	KeyPressRegistrationMap::iterator it = pressRegisteredKeys.find(k);
	//key should always have a place in the registration map at this point
	assert(it != pressRegisteredKeys.end());
	return (*it).second->getKeyPressListRef();
}

SingleKeyEventManager::InputableListRef Inputable::getKeyReleaseListRef(AZUL_KEY k)
{
	KeyReleaseRegistrationMap::iterator it = releaseRegisteredKeys.find(k);
	//key should always have a place in the registration map at this point
	assert(it != releaseRegisteredKeys.end());
	return (*it).second->getKeyReleaseListRef();
}