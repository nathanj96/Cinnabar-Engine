#include "TerrainModelManager.h"
#include "TerrainModel.h"

TerrainModelManager* TerrainModelManager::terrainModelManagerInstance = nullptr;

TerrainModelManager::TerrainModelManager()
{
	//I can't make this assignment if it's a const string?
	//for right now heightmaps are in the texture folder - change later
	defaultPath = "Textures/";
}

void TerrainModelManager::loadTerrain(MapKey key, const char* heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, ShaderObject* shd, Texture* tx)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	TerrainMap::iterator it = Instance().terrMap.find(key);
	if (it != Instance().terrMap.end())
	{
		throw std::runtime_error("Terrain " + key + " already loaded!");
	}
	else
	{
		std::string insertPath = Instance().defaultPath + heightmapFile;
		//Texture constructor specifically calls for a C-string
		TerrainModel* newTerrain = new TerrainModel(insertPath.c_str(), len, maxheight, ytrans, RepeatU, RepeatV, shd, tx);
		Instance().terrMap.insert(KeyTerrainPair(key, newTerrain));
	}
}

TerrainModel* TerrainModelManager::getTerrain(MapKey key)
{
	//Make sure the model you're looking for is actually present...
	TerrainMap::iterator it = Instance().terrMap.find(key);
	if (it == Instance().terrMap.end())
	{
		throw std::runtime_error("Terrain " + key + " not found!");
	}
	//(*iterator).second returns the value of an iterator
	return (*it).second;
}

void TerrainModelManager::unloadTerrains()
{
	//delete terrain models from the heap
	TerrainMap::iterator it;
	for (it = Instance().terrMap.begin(); it != Instance().terrMap.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
}

//need to delete the instance pointer on game end too
void TerrainModelManager::Terminate()
{
	unloadTerrains();
	delete terrainModelManagerInstance;
	terrainModelManagerInstance = nullptr;
}