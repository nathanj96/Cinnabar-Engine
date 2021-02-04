#ifndef SCENE_CHANGE_NULL_COMMAND
#define SCENE_CHANGE_NULL_COMMAND

#include "SceneChangeCommandBase.h"

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	SceneChangeNullCommand() = default;
	SceneChangeNullCommand(const SceneChangeNullCommand&) = default;
	SceneChangeNullCommand& operator=(const SceneChangeNullCommand&) = default;
	~SceneChangeNullCommand() = default;

	//placeholder command used when the scene mananger is checking
	//whether or not the scene needs to be changed - always have a scene
	//change command running Execute() every frame. This uses less overhead
	//than an if check every frame for if a scene change was requested
	virtual void Execute() override
	{
	};
};

#endif SCENE_CHANGE_NULL_COMMAND