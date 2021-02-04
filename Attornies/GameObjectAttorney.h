#ifndef GAME_OBJECT_ATTORNEY
#define GAME_OBJECT_ATTORNEY

#include "GameObject.h"

//forward declaration
class GameObjectSceneEntryCommand;
class GameObjectSceneExitCommand;

class GameObjectAttorney
{
	friend class GameObjectSceneEntryCommand;
	friend class GameObjectSceneExitCommand;
private:
	static void connectToScene(GameObject* obj)
	{
		obj->ConnectToScene();
	}
	static void disconnectFromScene(GameObject* obj)
	{
		obj->DisconnectFromScene();
	}
};

#endif GAME_OBJECT_ATTORNEY