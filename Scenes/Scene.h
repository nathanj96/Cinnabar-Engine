//Base class for all scenes

#ifndef SCENE
#define SCENE

//Forward declarations
class Updatable;
class Drawable;
class Alarmable;
class Inputable;
class UpdatableManager;
class DrawableManager;
class AlarmableManager;
class CameraManager;
class KeyboardEventManager;
class TerrainManager;
class RegistrationCommandBase;
class RegistrationCommandBroker;
class VisualizerCommandBase;
class VisualizerCommandBroker;
class CAudioCommandBase;
class CAudioCommandBroker;
class SceneAttorney;

#include "CollisionManager.h"
#include "AlarmableManager.h"
#include "Keyboard.h"

class Scene
{
	friend class SceneAttorney;
private:
	UpdatableManager* updateManager;
	DrawableManager* drawManager;
	AlarmableManager* alarmManager;
	CameraManager* cameraManager;
	KeyboardEventManager* keyInputManager;
	CollisionManager* collisionManager;
	TerrainManager* terrainManager;
	
	RegistrationCommandBroker* registrationCmdBroker;
	VisualizerCommandBroker* visualizerCmdBroker;
	CAudioCommandBroker* CSoundCmdBroker;

	void RegisterUpdate(Updatable* up);
	void RegisterDraw(Drawable* draw);
	void RegisterDraw2D(Drawable* draw);
	void RegisterAlarm(float t, Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber);
	void RegisterKeyPress(Inputable* in, AZUL_KEY k);
	void RegisterKeyRelease(Inputable* in, AZUL_KEY k);
	void DeregisterUpdate(Updatable* up);
	void DeregisterDraw(Drawable* draw);
	void DeregisterDraw2D(Drawable* draw);
	void DeregisterAlarm(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber);
	void DeregisterKeyPress(Inputable* in, AZUL_KEY k);
	void DeregisterKeyRelease(Inputable* in, AZUL_KEY k);
	void SubmitCommand(RegistrationCommandBase* cmd);
	void SubmitCommand(VisualizerCommandBase* cmd);
	void SubmitCommand(CAudioCommandBase* cmd);

	virtual void Initialize()
	{
	};
	virtual void SceneEnd()
	{
	};
	void Update();
	void Draw();
protected:

	/**********************************************************************************************//**
	 * \fn	template <typename C1, typename C2> void Scene::SetCollisionPair()
	 * \ingroup COLLIDABLEMETHODS
	 * \brief	Call this function when the scene needs to start checking for collisions between C1
	 * 			objects and C2 objects.
	 *
	 * \tparam	C1	A derived Collidable class.
	 * \tparam	C2	A different derived Collidable class.
	 **************************************************************************************************/

	template <typename C1, typename C2> void SetCollisionPair()
	{
		collisionManager->SetCollisionPair<C1, C2>();
	}

	/**********************************************************************************************//**
	 * \fn	template<typename C1> void Scene::SetCollisionSelf()
	 * \ingroup COLLIDABLEMETHODS
	 * \brief	Call this function when the scene needs to start checking for collisions between C1 objects
	 * 			and other C1 objects.
	 *
	 * \tparam	C1	A derived Collidable class.
	 **************************************************************************************************/

	template<typename C1> void SetCollisionSelf()
	{
		collisionManager->SetCollisionSelf<C1>();
	}

	/**********************************************************************************************//**
	 * \fn	template<typename C1> void Scene::SetCollisionTerrain()
	 * \ingroup COLLIDABLEMETHODS
	 * \brief	Call this function when the scene needs to start checking for collisions between C1 objects
	 * 			and the scene's current terrain.
	 *
	 * \tparam	C1	A derived Collid
	 **************************************************************************************************/

	template<typename C1> void SetCollisionTerrain()
	{
		collisionManager->SetCollisionTerrain<C1>();
	}
public:
	Scene();
	Scene(const Scene&) = default;
	Scene& operator=(const Scene&) = default;
	virtual ~Scene();

	/**********************************************************************************************//**
	 * \fn	CameraManager* Scene::getCameraMgr();
	 * \ingroup SCENEMETHODS
	 * \brief	Returns the current scene's camera manager. Access to this is needed in order to get
	 * 			the camera currently in use.
	 *
	 * \returns	A pointer to the current scene's camera manager.
	 **************************************************************************************************/

	CameraManager* getCameraMgr() const;

	/**********************************************************************************************//**
	 * \fn	CollisionManager* Scene::getCollisionMgr();
	 * \ingroup SCENEMETHODS
	 * \brief	Returns the current scene's collision manager. Required by the engine to process
	 * 			collision; user should not need to call for any other purpose.
	 *
	 * \returns	A pointer to the current scene's collision manager.
	 **************************************************************************************************/

	CollisionManager* getCollisionMgr() const;

	//Used to test terrain collision
	TerrainManager* getTerrainMgr() const;
};

#endif SCENE