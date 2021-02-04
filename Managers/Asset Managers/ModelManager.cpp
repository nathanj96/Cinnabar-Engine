#include "ModelManager.h"

ModelManager* ModelManager::modelManagerInstance = nullptr;

ModelManager::ModelManager()
{
	//I can't make this assignment if it's a const string?
	defaultPath = "Models/";
}

void ModelManager::loadModel(MapKey modelKey, std::string modelFilename)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	ModelMap::iterator it = Instance().modelMap.find(modelKey);
	if (it != Instance().modelMap.end())
	{
		throw std::runtime_error("Model " + modelKey + " already loaded!");
	}
	else
	{
		std::string insertPath = Instance().defaultPath + modelFilename;
		//Texture constructor specifically calls for a C-string
		Model* newModel = new Model(insertPath.c_str());
		Instance().modelMap.insert(KeyModelPair(modelKey, newModel));
	}
}

void ModelManager::loadModel(MapKey modelKey, Model::PreMadeModels pmModel)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	ModelMap::iterator it = Instance().modelMap.find(modelKey);
	if (it != Instance().modelMap.end())
	{
		throw std::runtime_error("Model " + modelKey +  " already loaded!");
	}
	else
	{
		//use Model constructor with PreMadeModels enum
		Model* newModel = new Model(pmModel);
		Instance().modelMap.insert(KeyModelPair(modelKey, newModel));
	}
}

void ModelManager::loadModel(MapKey modelKey, Model* model)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
//already have this functionality but just to show that I understand it)
	ModelMap::iterator it = Instance().modelMap.find(modelKey);
	if (it != Instance().modelMap.end())
	{
		throw std::runtime_error("Model " + modelKey + " already loaded!");
	}
	else
	{
		Instance().modelMap.insert(KeyModelPair(modelKey, model));
	}
}

Model* ModelManager::getModel(MapKey modelKey)
{
	//Make sure the model you're looking for is actually present...
	ModelMap::iterator it = Instance().modelMap.find(modelKey);
	if (it == Instance().modelMap.end())
	{
		throw std::runtime_error("Model " + modelKey + " not found!");
	}
	//(*iterator).second returns the value of an iterator
	return (*it).second;
}

//need to delete the instance pointer on game end too
void ModelManager::Terminate()
{
	unloadModels();
	delete modelManagerInstance;
	modelManagerInstance = nullptr;
}

void ModelManager::unloadModels()
{
	//delete model objects from the heap
	ModelMap::iterator it;
	for (it = Instance().modelMap.begin(); it != Instance().modelMap.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
}