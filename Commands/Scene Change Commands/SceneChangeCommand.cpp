#include "SceneChangeCommand.h"
#include "SceneManagerAttorney.h"
#include "Scene.h"

SceneChangeCommand::SceneChangeCommand() : newScene(nullptr)
{
};

void SceneChangeCommand::setNewScene(Scene* newSc)
{
	newScene = newSc;
}

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::Commands::ChangeScene(newScene);
}