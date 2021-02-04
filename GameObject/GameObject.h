//using approach # 1

#ifndef GAME_OBJECT
#define GAME_OBJECT

//forward declaration
class GameObjectSceneEntryCommand;
class GameObjectSceneExitCommand;
class GameObjectAttorney;

#include "RegistrationState.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Inputable.h"
#include "Alarmable.h"
#include "Collidable.h"

class GameObject : public Updatable, public Drawable, public Inputable, public Alarmable, public Collidable
{
	friend class GameObjectAttorney;
private:
	GameObjectSceneEntryCommand* sceneEntryCmdPtr;
	GameObjectSceneExitCommand* sceneExitCmdPtr;
	RegistrationState sceneRegState;

	//engine-level functions to process scene entry/exit of GameObjects

	void ConnectToScene();
	void DisconnectFromScene();

	/**********************************************************************************************//**
	 * \fn	virtual void GameObject::SceneEntry()
	 * \ingroup GAMELOOPEVENTS
	 * \brief	Executed when a GameObject "enters" the scene.
	 **************************************************************************************************/

	virtual void SceneEntry()
	{
	};

	/**********************************************************************************************//**
	 * \fn	virtual void GameObject::SceneExit()
	 * \ingroup GAMELOOPEVENTS
	 * \brief	Executed when a GameObject "exits" the scene.
	 **************************************************************************************************/

	virtual void SceneExit()
	{
	};
public:
	GameObject();
	GameObject(const GameObject&) = default;
	GameObject& operator=(const GameObject&) = default;
	virtual ~GameObject();

	/**********************************************************************************************//**
	 * \fn	void GameObject::SubmitEntryCommand();
	 *
	 * \brief	Used on persistent GameObjects that need to "enter" and "exit" the scene. On the frame after
	 * 			this function is called, the GameObject will "enter" the scene according to
	 * 			GameObject::SceneEntry().
	 **************************************************************************************************/

	void SubmitEntryCommand();

	/**********************************************************************************************//**
	 * \fn	void GameObject::SubmitExitCommand();
	 *
	 * \brief	Used on persistent GameObjects that need to "enter" and "exit" the scene. On the frame after
	 * 			this function is called, the GameObject will "exit" the scene according to
	 * 			GameObject::SceneExit().
	 **************************************************************************************************/

	void SubmitExitCommand();
};

#endif GAME_OBJECT