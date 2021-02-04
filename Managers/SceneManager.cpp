#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"
#include "SceneAttorney.h"
#include "Camera.h"
#include "TerrainManager.h"
#include "TerrainModel.h"

#include "SceneChangeCommandBase.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"

SceneManager* SceneManager::sceneManagerInstance = nullptr;

void SceneManager::setStartScene(Scene* newScene)
{
	Instance().currentScene = newScene;
}

void SceneManager::Initialize()
{
	Instance().sceneNoChangeCmdPtr = new SceneChangeNullCommand();
	Instance().sceneChangeCmdPtr = new SceneChangeCommand();
	Instance().currSceneChangeCmdPtr = Instance().sceneNoChangeCmdPtr;
	Instance().currSceneChangeState = SceneChangeState::NO_PENDING_CHANGE;
}

void SceneManager::setNewScene(Scene* newSc)
{
	assert(Instance().currSceneChangeState == SceneChangeState::NO_PENDING_CHANGE);
	Instance().sceneChangeCmdPtr->setNewScene(newSc);
	Instance().currSceneChangeCmdPtr = Instance().sceneChangeCmdPtr;
	Instance().currSceneChangeState = SceneChangeState::PENDING_CHANGE;
}

void SceneManager::ChangeScene(Scene* newSc)
{
	//make sure a scene change is pending
	assert(Instance().currSceneChangeState == SceneChangeState::PENDING_CHANGE);
	//clean up the current scene
	SceneAttorney::toSceneManager::SceneEnd(Instance().currentScene);
	delete Instance().currentScene;
	//update new scene ref
	Instance().currentScene = newSc;
	//switch to new scene
	SceneAttorney::toSceneManager::Initialize(newSc);
	//switch back to no scene change command
	Instance().currSceneChangeCmdPtr = Instance().sceneNoChangeCmdPtr;
	//tell the scene change command that there is now no longer a scene to
	//switch to (safety reasons, and helps with an edge case)
	Instance().sceneChangeCmdPtr->setNewScene(newSc);
	Instance().currSceneChangeState = SceneChangeState::NO_PENDING_CHANGE;
}

Scene* SceneManager::getCurrentScene()
{
	return Instance().currentScene;
}

Camera* SceneManager::getCurrentCamera()
{
	return SceneManager::getCurrentScene()->getCameraMgr()->getCurrentCamera();
}

Camera* SceneManager::getCurrent2DCamera()
{
	return SceneManager::getCurrentScene()->getCameraMgr()->getCurrent2DCamera();
}

TerrainModel* SceneManager::GetCurrentTerrain()
{
	return SceneManager::getCurrentScene()->getTerrainMgr()->getCurrentTerrain();
}

void SceneManager::SetCurrentTerrain(TerrainModel* newTerr)
{
	SceneManager::getCurrentScene()->getTerrainMgr()->setCurrentTerrain(newTerr);
}

float SceneManager::GetTerrainHeightAt2DCoords(float x, float z)
{
	return SceneManager::getCurrentScene()->getTerrainMgr()->getCurrentTerrain()->interpHeightAt2DCoords(x, z);
}

Vect SceneManager::GetTerrainNormAt2DCoords(float x, float z)
{
	return SceneManager::GetCurrentTerrain()->interpNormalAt2DCoords(x, z);
}

void SceneManager::initializeStartScene()
{
	SceneAttorney::toSceneManager::Initialize(Instance().currentScene);
}

void SceneManager::Update()
{
	//switch scene if needed
	Instance().currSceneChangeCmdPtr->Execute();
	SceneAttorney::toSceneManager::Update(Instance().currentScene);
}

void SceneManager::Draw()
{
	SceneAttorney::toSceneManager::Draw(Instance().currentScene);
}

void SceneManager::Terminate()
{
	//clean up the current scene
	SceneAttorney::toSceneManager::SceneEnd(Instance().currentScene);
	delete Instance().currentScene;
	Instance().currentScene = nullptr;

	//clean up commands
	Instance().currSceneChangeCmdPtr = nullptr;
	delete Instance().sceneNoChangeCmdPtr;
	Instance().sceneNoChangeCmdPtr = nullptr;
	delete Instance().sceneChangeCmdPtr;
	Instance().sceneChangeCmdPtr = nullptr;

	//clean up the manager
	delete sceneManagerInstance;
	sceneManagerInstance = nullptr;
}