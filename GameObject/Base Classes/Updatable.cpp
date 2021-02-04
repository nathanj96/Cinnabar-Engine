#include "Updatable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

#include "RegistrationCommandBase.h"
#include "RegisterUpdateCommand.h"
#include "DeregisterUpdateCommand.h"

//object needs to be registered manually
Updatable::Updatable()
{
	updateRegState = RegistrationState::CURRENTLY_DEREGISTERED;
	updateRegistrationCmdPtr = new RegisterUpdateCommand(this);
	updateDeregistrationCmdPtr = new DeregisterUpdateCommand(this);
}

void Updatable::SubmitRegisterUpdatableCommand()
{
	//make sure it's not already registered
	assert(updateRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::toUpdatable::submitUpdateCommand(updateRegistrationCmdPtr);
	updateRegState = RegistrationState::PENDING_REGISTRATION;
}

void Updatable::SubmitDeregisterUpdatableCommand()
{
	//make sure it's already registered
	assert(updateRegState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::toUpdatable::submitUpdateCommand(updateDeregistrationCmdPtr);
	updateRegState = RegistrationState::PENDING_DEREGISTRATION;
}

void Updatable::RegisterUpdatable()
{
	//make sure it's waiting to be registered (this is called from a registration command Execute())
	assert(updateRegState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::toUpdatable::registerUpdate(this);
	updateRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::DeregisterUpdatable()
{
	//make sure it's waiting to be registered (this is called from a registration command Execute())
	assert(updateRegState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::toUpdatable::deregisterUpdate(this);
	updateRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Updatable::setUpdateObjRef(UpdatableManager::UpdatableListRef ref)
{
	updateObjRef = ref;
}

UpdatableManager::UpdatableListRef Updatable::getUpdateObjRef() const
{
	return updateObjRef;
}

Updatable::~Updatable()
{
	delete updateRegistrationCmdPtr;
	updateRegistrationCmdPtr = nullptr;
	delete updateDeregistrationCmdPtr;
	updateDeregistrationCmdPtr = nullptr;
}