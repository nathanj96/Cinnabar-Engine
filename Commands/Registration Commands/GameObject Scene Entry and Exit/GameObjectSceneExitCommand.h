#ifndef GAME_OBJECT_SCENE_EXIT_COMMAND
#define GAME_OBJECT_SCENE_EXIT_COMMAND

//forward declaration
class GameObject;

#include "RegistrationCommandBase.h"

class GameObjectSceneExitCommand : public RegistrationCommandBase
{
private:
	GameObject* objRef;
public:
	GameObjectSceneExitCommand() = delete;
	GameObjectSceneExitCommand(const GameObjectSceneExitCommand&) = delete;
	GameObjectSceneExitCommand& operator=(const GameObjectSceneExitCommand&) = delete;
	~GameObjectSceneExitCommand() = default;

	GameObjectSceneExitCommand(GameObject* obj);
	virtual void Execute() override;
};

#endif GAME_OBJECT_SCENE_EXIT_COMMAND