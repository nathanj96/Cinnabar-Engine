//Manager for controlling the loading and retrieval of models

#ifndef MODEL_MANAGER
#define MODEL_MANAGER

#include <string>
//Map class type that will contain the models - Using unordered map
//because it allows for quicker direct access of elements
#include <unordered_map>
//need Model include to access PreMadeModels enum
#include "Model.h"

//for std::string
using namespace std;
class ModelManagerAttorney;

//Manager for controlling the loading and retrieval of models

class ModelManager
{
	//so engine can terminate it on game end
	friend class ModelManagerAttorney;
private:
	//manager-specific type definitions:
	using MapKey = std::string;
	using ModelMap = std::unordered_map<MapKey, Model*>;
	using KeyModelPair = std::pair<MapKey, Model*>;

	//The folder that all models assets should be placed in. Saving this
	//location allows the convenience of not having to type the full path
	//name out repeatedly
	std::string defaultPath;
	//use strings to access specific models
	ModelMap modelMap;

	//Singleton setup
	static ModelManager* modelManagerInstance;

	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	~ModelManager() = default;

	static ModelManager& Instance()
	{
		if (!modelManagerInstance)
			modelManagerInstance = new ModelManager;

		return *modelManagerInstance;
	}

	/**********************************************************************************************//**
	 * \fn	static void ModelManager::Terminate();
	 * \ingroup MODELMANAGER
	 * \brief	Called when the game ends. Unloads all models.
	 **************************************************************************************************/

	static void Terminate();
	//On game exit, unload all models
	static void unloadModels();
public:

	/**********************************************************************************************//**
	 * \fn	static Model* ModelManager::getModel(MapKey modelKey);
	 * \ingroup MODELMANAGER
	 * \brief	Used to retrieve a given Model.
	 *
	 * \param 	modelKey	The key associated with the Model when it was loaded.
	 *
	 * \returns	The Model with the given key. Throws an error if the key is not found.
	 **************************************************************************************************/

	static Model* getModel(MapKey modelKey);

	/**********************************************************************************************//**
	 * \fn	static void ModelManager::loadModel(MapKey modelKey, std::string modelFilename);
	 * \ingroup MODELMANAGER
	 * \brief	Loads a given .azul model. The model is associated with the key modelKey for future retrieval.
	 *
	 * \note Cinnabar Engine only supports .azul model files for import.
	 * 		 
	 * \param 	modelKey	 	The model key.
	 * \param 	modelFilename	Filename of the model file. Specify the entire filename with its extension, as such:
	 *							\code
	 *								 {
	 *								 ModelManager::loadModel("newModel", "model1.azul");
	 *								 }
	 *							\endcode
	 **************************************************************************************************/

	static void loadModel(MapKey modelKey, std::string modelFilename);

	/**********************************************************************************************//**
	 * \fn	static void ModelManager::loadModel(MapKey modelKey, Model::PreMadeModels pmModel);
	 * \ingroup MODELMANAGER
	 * \brief	Loads a pre-made model defined by the Cinnabar Engine. The model is associated with the key
	 * 			modelKey for future retrieval.
	 *
	 * \param 	modelKey The model key. The function will throw an error if the provided key is already in use.
	 * \param 	pmModel  Which premade model to use. 	
	 **************************************************************************************************/

	static void loadModel(MapKey modelKey, Model::PreMadeModels pmModel);

	//needed to load skybox...
	static void loadModel(MapKey modelKey, Model* model);
};

#endif MODEL_MANAGER