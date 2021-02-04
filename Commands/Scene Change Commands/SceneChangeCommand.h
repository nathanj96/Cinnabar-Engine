//use when a scene actually needs to change

#ifndef SCENE_CHANGE_COMMAND
#define SCENE_CHANGE_COMMAND

class Scene;

#include "SceneChangeCommandBase.h"

class SceneChangeCommand : public SceneChangeCommandBase
{
private:
	Scene* newScene;
public:
	SceneChangeCommand();
	SceneChangeCommand(const SceneChangeCommand&) = default;
	SceneChangeCommand& operator=(const SceneChangeCommand&) = default;
	~SceneChangeCommand() = default;

	virtual void Execute() override;
	void setNewScene(Scene* newSc);
};

#endif SCENE_CHANGE_COMMAND