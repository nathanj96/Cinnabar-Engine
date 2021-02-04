#include "GameUpdatable.h"

#include "GameRegistrationManagerAttorney.h"
#include "GameRegistrationCommandBase.h"
#include "GameRegisterUpdateCommand.h"
#include "GameDeregisterUpdateCommand.h"

GameUpdatable::GameUpdatable()
{
	updateRegState = RegistrationState::CURRENTLY_DEREGISTERED;
	updateRegistrationCmdPtr = new GameRegisterUpdateCommand(this);
	updateDeregistrationCmdPtr = new GameDeregisterUpdateCommand(this);
}

void GameUpdatable::SubmitRegisterUpdatableCommand()
{
	assert(updateRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	GameRegistrationManagerAttorney::toGameUpdatable::submitUpdateCommand(updateRegistrationCmdPtr);
	updateRegState = RegistrationState::PENDING_REGISTRATION;
}

void GameUpdatable::SubmitDeregisterUpdatableCommand()
{
	assert(updateRegState == RegistrationState::CURRENTLY_REGISTERED);


	GameRegistrationManagerAttorney::toGameUpdatable::submitUpdateCommand(updateDeregistrationCmdPtr);
	updateRegState = RegistrationState::PENDING_DEREGISTRATION;
}

void GameUpdatable::RegisterUpdatable()
{
	assert(updateRegState == RegistrationState::PENDING_REGISTRATION);
	GameRegistrationManagerAttorney::toGameUpdatable::registerUpdatable(this);
	updateRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void GameUpdatable::DeregisterUpdatable()
{
	assert(updateRegState == RegistrationState::PENDING_DEREGISTRATION);
	GameRegistrationManagerAttorney::toGameUpdatable::deregisterUpdatable(this);
	updateRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void GameUpdatable::setUpdateObjRef(GameUpdatableManager::UpdatableListRef ref)
{
	updateObjRef = ref;
}

GameUpdatableManager::UpdatableListRef GameUpdatable::getUpdateObjRef()
{
	return updateObjRef;
}

GameUpdatable::~GameUpdatable()
{
	delete updateRegistrationCmdPtr;
	updateRegistrationCmdPtr = nullptr;
	delete updateDeregistrationCmdPtr;
	updateDeregistrationCmdPtr = nullptr;
}
