#include "GameObject.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

#include "RegistrationCommandBase.h"
#include "GameObjectSceneEntryCommand.h"
#include "GameObjectSceneExitCommand.h"

GameObject::GameObject()
{
	sceneEntryCmdPtr = new GameObjectSceneEntryCommand(this);
	sceneExitCmdPtr = new GameObjectSceneExitCommand(this);
	sceneRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

GameObject::~GameObject()
{
	delete sceneEntryCmdPtr;
	delete sceneExitCmdPtr;
}

void GameObject::ConnectToScene()
{
	assert(sceneRegState == RegistrationState::PENDING_REGISTRATION);
	//registration state maintenance
	SceneEntry();
	sceneRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void GameObject::DisconnectFromScene()
{
	assert(sceneRegState == RegistrationState::PENDING_DEREGISTRATION);
	//registration state maintenance
	SceneExit();
	sceneRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void GameObject::SubmitEntryCommand()
{
	assert(sceneRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::toGameObject::submitEntryExitCommand(sceneEntryCmdPtr);
	sceneRegState = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::SubmitExitCommand()
{
	//either of these can be valid because this command can be sent more than once in the same frame
	assert(sceneRegState == RegistrationState::CURRENTLY_REGISTERED || sceneRegState == RegistrationState::PENDING_DEREGISTRATION);
	//only submit a command if the object is still fully registered though
	if (sceneRegState == RegistrationState::CURRENTLY_REGISTERED)
	{
		SceneAttorney::toGameObject::submitEntryExitCommand(sceneExitCmdPtr);
		sceneRegState = RegistrationState::PENDING_DEREGISTRATION;
	}
}