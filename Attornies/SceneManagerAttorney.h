#ifndef SCENE_MANAGER_ATTORNEY
#define SCENE_MANAGER_ATTORNEY

class CinnabarEngine;
class Scene;
class SceneChangeCommand;

#include "SceneManager.h"

class SceneManagerAttorney
{
public:
	class Engine
	{
		friend class CinnabarEngine;
	private:
		static void Initialize()
		{
			SceneManager::Initialize();
		}
		static void Terminate()
		{
			SceneManager::Terminate();
		}
		static void initializeStartScene()
		{
			SceneManager::initializeStartScene();
		}
		static void Update()
		{
			SceneManager::Update();
		}
		static void Draw()
		{
			SceneManager::Draw();
		}
	};
	class Commands
	{
		friend class SceneChangeCommand;
	private:
		static void ChangeScene(Scene* newSc)
		{
			SceneManager::ChangeScene(newSc);
		}
	};
};

#endif SCENE_MANAGER_ATTORNEY