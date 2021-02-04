#include "GameObjectSceneExitCommand.h"

#include "GameObjectAttorney.h"

GameObjectSceneExitCommand::GameObjectSceneExitCommand(GameObject* obj) : objRef(obj)
{
};

void GameObjectSceneExitCommand::Execute()
{
	GameObjectAttorney::disconnectFromScene(objRef);
}