#ifndef GAME_OBJECT_SCENE_ENTRY_COMMAND
#define GAME_OBJECT_SCENE_ENTRY_COMMAND

#include "RegistrationCommandBase.h"

//forward declaration
class GameObject;

class GameObjectSceneEntryCommand : public RegistrationCommandBase
{
private:
	GameObject* objRef;
public:
	GameObjectSceneEntryCommand() = delete;
	GameObjectSceneEntryCommand(const GameObjectSceneEntryCommand&) = delete;
	GameObjectSceneEntryCommand& operator=(const GameObjectSceneEntryCommand&) = delete;
	~GameObjectSceneEntryCommand() = default;

	GameObjectSceneEntryCommand(GameObject* obj);
	virtual void Execute() override;
};

#endif GAME_OBJECT_SCENE_ENTRY_COMMAND