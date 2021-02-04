#include "Scene.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "KeyboardEventManager.h"
#include "TerrainManager.h"
#include "RegistrationCommandBroker.h"
#include "RegistrationCommandBase.h"
#include "VisualizerCommandBroker.h"
#include "VisualizerCommandBase.h"
#include "CAudioCommandBroker.h"
#include "CAudioCommandBase.h"
#include "AlarmableAttorney.h"
#include "AlarmableManagerAttorney.h"

/**********************************************************************************************//**
 * \fn	Scene::Scene()
 * \ingroup SCENECREATION
 * \brief	Base constructor for the Scene class, called by the engine after the previous scene is
 * 			deleted (if initializing the first scene, this deletion does not occur). This function
 * 			performs only the setup necessary for any Scene to work; for setup of specific scenes,
 * 			such as creating cameras, the user should define the Initialize() function for that
 * 			given scene. User should not modify or have access to.
 **************************************************************************************************/

Scene::Scene()
{
	updateManager = new UpdatableManager();
	drawManager = new DrawableManager();
	alarmManager = new AlarmableManager();
	cameraManager = new CameraManager();
	keyInputManager = new KeyboardEventManager();
	collisionManager = new CollisionManager();
	terrainManager = new TerrainManager();
	registrationCmdBroker = new RegistrationCommandBroker();
	visualizerCmdBroker = new VisualizerCommandBroker();
	CSoundCmdBroker = new CAudioCommandBroker();
}

void Scene::SubmitCommand(RegistrationCommandBase* cmd)
{
	registrationCmdBroker->addCommand(cmd);
}

void Scene::SubmitCommand(VisualizerCommandBase* cmd)
{
	visualizerCmdBroker->AddCommand(cmd);
}

void Scene::SubmitCommand(CAudioCommandBase* cmd)
{
	CSoundCmdBroker->AddCommand(cmd);
}

void Scene::RegisterUpdate(Updatable* up)
{
	updateManager->Register(up);
}

void Scene::RegisterDraw(Drawable* draw)
{
	drawManager->Register(draw);
}

void Scene::RegisterDraw2D(Drawable* draw)
{
	drawManager->Register2D(draw);
}

void Scene::DeregisterUpdate(Updatable* up)
{
	updateManager->Deregister(up);
}

void Scene::DeregisterDraw(Drawable* draw)
{
	drawManager->Deregister(draw);
}

void Scene::DeregisterDraw2D(Drawable* draw)
{
	drawManager->Deregister2D(draw);
}

void Scene::RegisterAlarm(float t, Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber)
{
	alarmManager->RegisterAlarm(t, alarm, alarmNumber);
}

void Scene::DeregisterAlarm(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber)
{
	alarmManager->DeregisterAlarm(alarm, alarmNumber);
}

void Scene::RegisterKeyPress(Inputable* in, AZUL_KEY k)
{
	keyInputManager->RegisterKeyPress(in, k);
}

void Scene::RegisterKeyRelease(Inputable* in, AZUL_KEY k)
{
	keyInputManager->RegisterKeyRelease(in, k);
}

void Scene::DeregisterKeyPress(Inputable* in, AZUL_KEY k)
{
	keyInputManager->DeregisterKeyPress(in, k);
}

void Scene::DeregisterKeyRelease(Inputable* in, AZUL_KEY k)
{
	keyInputManager->DeregisterKeyRelease(in, k);
}

void Scene::Update()
{
	//process any registration changes before the next frame
	registrationCmdBroker->processCommands();
	collisionManager->ProcessCollision();
	//alarms should probably be processed before too
	AlarmableManagerAttorney::processAlarms(alarmManager);
	keyInputManager->ProcessKeyEvents();
	updateManager->processElements();
	//god cam. Comment out the following line to disable it.
	//cameraManager->UpdateGodCam();
	CSoundCmdBroker->ProcessCommands();
}

void Scene::Draw()
{
	//order of calls is so 2d elements appear on top of 2d ones
	visualizerCmdBroker->ProcessCommands();
	//draw manager doesn't have access to terrain manager, so need to put this here
	terrainManager->renderCurrentTerrain();
	drawManager->processElements();
}

CameraManager* Scene::getCameraMgr() const
{
	return cameraManager;
}

//part of the process of getting collision ID's
CollisionManager* Scene::getCollisionMgr() const
{
	return collisionManager;
}

TerrainManager* Scene::getTerrainMgr() const
{
	return terrainManager;
}

/**********************************************************************************************//**
 * \fn	Scene::~Scene()
 *
 * \brief	Base destructor for the Scene class, called by the engine the frame after
 * 			SceneManager::setNewScene() is called. This function only performs the cleanup needed
 * 			to shut down any Scene; cleanup for specific scenes, such as deleting GameObjects,
 * 			should be user-defined in the Scene's SceneEnd() function. User should not modify
 * 			or have access to.
 *
 * \author	Nathan
 * \date	4/8/2020
 **************************************************************************************************/

Scene::~Scene()
{
	delete updateManager;
	updateManager = nullptr;
	delete drawManager;
	drawManager = nullptr;
	delete alarmManager;
	alarmManager = nullptr;
	delete cameraManager;
	cameraManager = nullptr;
	delete keyInputManager;
	keyInputManager = nullptr;
	delete collisionManager;
	collisionManager = nullptr;
	delete registrationCmdBroker;
	registrationCmdBroker = nullptr;
	delete terrainManager;
	terrainManager = nullptr;
	delete visualizerCmdBroker;
	visualizerCmdBroker = nullptr;
	delete CSoundCmdBroker;
	CSoundCmdBroker = nullptr;
}