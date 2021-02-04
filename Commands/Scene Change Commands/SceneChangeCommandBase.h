#ifndef SCENE_CHANGE_COMMAND_BASE
#define SCENE_CHANGE_COMMAND_BASE

class SceneChangeCommandBase
{
public:
	SceneChangeCommandBase() = default;
	SceneChangeCommandBase(const SceneChangeCommandBase&) = default;
	SceneChangeCommandBase& operator=(const SceneChangeCommandBase&) = default;
	virtual ~SceneChangeCommandBase() = default;

	//different for each command
	virtual void Execute() = 0;
};

#endif SCENE_CHANGE_COMMAND_BASE

