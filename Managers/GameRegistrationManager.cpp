#include "GameRegistrationManager.h"
#include "GameRegistrationCommandBroker.h"
#include "GameUpdatableManager.h"
#include "GameRegistrationCommandBroker.h"

GameRegistrationManager* GameRegistrationManager::gameRegistrationManagerInstance = nullptr;

GameRegistrationManager::GameRegistrationManager()
{
	updateMgr = new GameUpdatableManager();
	cmdBroker = new GameRegistrationCommandBroker();
}

void GameRegistrationManager::SubmitCommand(GameRegistrationCommandBase* cmd)
{
	Instance().cmdBroker->AddCommand(cmd);
}

void GameRegistrationManager::RegisterUpdatable(GameUpdatable* upd)
{
	Instance().updateMgr->Register(upd);
}

void GameRegistrationManager::DeregisterUpdatable(GameUpdatable* upd)
{
	Instance().updateMgr->Deregister(upd);
}

void GameRegistrationManager::ProcessUpdates()
{
	//process commands first, then do any necessary updates (same structure as scenes, basically)
	Instance().cmdBroker->ProcessCommands();
	Instance().updateMgr->processElements();
}

void GameRegistrationManager::Terminate()
{
	delete gameRegistrationManagerInstance;
	gameRegistrationManagerInstance = nullptr;
}

GameRegistrationManager::~GameRegistrationManager()
{
	delete updateMgr;
	updateMgr = nullptr;
	delete cmdBroker;
	cmdBroker = nullptr;
}