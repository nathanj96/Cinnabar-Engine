#ifndef SCENE_MANAGER
#define SCENE_MANAGER

//Forward declaration
class Scene;
class SceneManagerAttorney;
class Camera;
class TerrainModel;

class SceneChangeCommandBase;
class SceneChangeNullCommand;
class SceneChangeCommand;

#include "Vect.h"

class SceneManager
{
	friend class SceneManagerAttorney;
public:

	/**********************************************************************************************//**
	 * \fn	static void SceneManager::setNewScene(Scene* newSc);
	 * \ingroup SCENECREATION
	 * \brief	On the frame after this is called, the scene will change to newSc. This deletes all the
	 * 			objects from the current scene, as well as the scene instance itself, then creates
	 * 			a new scene along with all of its associated objects. Singletons remain unaffected.
	 *
	 * \param newSc The scene to change to.
	 **************************************************************************************************/

	static void setNewScene(Scene* newSc);
	static Scene* getCurrentScene();

	/**********************************************************************************************//**
	 * \fn	static void SceneManager::setStartScene(Scene* newScene);
	 * \ingroup SCENECREATION
	 * \brief	Called before the game loop begins, in the user-defined LoadResources() function. 
	 * 			Determines which scene to begin the game loop in.
	 *
	 * \author	Nathan
	 * \date	3/14/2020
	 *
	 * \param newScene	The starting scene.
	 **************************************************************************************************/

	static void setStartScene(Scene* newScene);

	/**********************************************************************************************//**
	 * \fn	static Camera* SceneManager::getCurrentCamera();
	 *
	 * \brief	Wraps several calls for user readability.
	 **************************************************************************************************/

	static Camera* getCurrentCamera();

	/**********************************************************************************************//**
	 * \fn	static Camera* SceneManager::getCurrent2DCamera();
	 *
	 * \brief	Wraps several calls for user readability.
	 **************************************************************************************************/

	static Camera* getCurrent2DCamera();

	//wrappers for terrain model functions for ease of use
	static float GetTerrainHeightAt2DCoords(float x, float z);
	static Vect GetTerrainNormAt2DCoords(float x, float z);

	/**********************************************************************************************//**
	 * \fn	static TerrainModel* SceneManager::GetCurrentTerrain();
	 * \ingroup TERRAINMODELMETHODS
	 * \brief	Retrieves the currently active terrain.
	 *
	 * \returns	The current terrain.
	 **************************************************************************************************/

	static TerrainModel* GetCurrentTerrain();

	/**********************************************************************************************//**
	 * \fn	static void SceneManager::SetCurrentTerrain(TerrainModel* newTerr);
	 * \ingroup TERRAINMODELMETHODS
	 * \brief	Sets the currently active terrain.
	 *
	 * \param [in,out]	newTerr	The new terrain.
	 **************************************************************************************************/

	static void SetCurrentTerrain(TerrainModel* newTerr);
private:
	enum class SceneChangeState
	{
		NO_PENDING_CHANGE,
		PENDING_CHANGE
	};

	//Singleton setup
	static SceneManager* sceneManagerInstance;

	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager() = default;

	static SceneManager& Instance()
	{
		if (!sceneManagerInstance)
			sceneManagerInstance = new SceneManager;

		return *sceneManagerInstance;
	}

	Scene* currentScene;

	SceneChangeCommandBase* currSceneChangeCmdPtr;
	SceneChangeNullCommand* sceneNoChangeCmdPtr;
	SceneChangeCommand* sceneChangeCmdPtr;
	SceneChangeState currSceneChangeState;

	/**********************************************************************************************//**
	 * \fn	static void SceneManager::ChangeScene(Scene* newSc);
	 *
	 * \brief	Internal process of a scene change. User should not modify/have access to.
	 **************************************************************************************************/

	static void ChangeScene(Scene* newSc);

	/**********************************************************************************************//**
	 * \fn	static void SceneManager::Update();
	 *
	 * \brief	Common functionality that every scene needs to have for its update tick. User should not
	 * 			modify or have access to.
	 **************************************************************************************************/

	static void Update();

	/**********************************************************************************************//**
	 * \fn	static void SceneManager::Draw();
	 *
	 * \brief	Draws this 
	 *
	 * \author	Common functionality that every scene needs to have for its draw tick. User should not
	 * 			modify or have access to.
	 **************************************************************************************************/

	static void Draw();
	static void Initialize();
	static void Terminate();

	/**********************************************************************************************//**
	 * \fn	static void SceneManager::initializeStartScene();
	 * \ingroup SCENECREATION
	 * \brief	Called by the engine during game startup. Initializes the scene set by setStartScene().
	 * 			User should not modify or have access to.
	 **************************************************************************************************/

	static void initializeStartScene();
};

#endif SCENE_MANAGER