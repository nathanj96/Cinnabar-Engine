#include "GameObjectSceneEntryCommand.h"

#include "GameObjectAttorney.h"

GameObjectSceneEntryCommand::GameObjectSceneEntryCommand(GameObject* obj) : objRef(obj)
{
};

void GameObjectSceneEntryCommand::Execute()
{
	GameObjectAttorney::connectToScene(objRef);
}