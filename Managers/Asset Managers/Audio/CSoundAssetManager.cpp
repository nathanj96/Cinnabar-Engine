#include "CSoundAssetManager.h"
#include "CSound.h"

CSoundAssetManager* CSoundAssetManager::CSoundAssetManagerInstance = nullptr;

CSoundAssetManager::CSoundAssetManager()
{
	//I can't make this assignment if it's a const string?
	defaultPath = "Sounds/";
}

void CSoundAssetManager::loadSound(MapKey soundKey, std::string modelFilename)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	SoundMap::iterator it = Instance().soundMap.find(soundKey);
	if (it != Instance().soundMap.end())
	{
		throw std::runtime_error("Sound " + soundKey + " already loaded!");
	}
	else
	{
		std::string insertPath = Instance().defaultPath + modelFilename;
		//Texture constructor specifically calls for a C-string
		CSound* newSound = new CSound(insertPath.c_str());
		Instance().soundMap.insert(KeySoundPair(soundKey, newSound));
	}
}

CSound* CSoundAssetManager::getSound(MapKey key)
{
	//Make sure the model you're looking for is actually present...
	SoundMap::iterator it = Instance().soundMap.find(key);
	if (it == Instance().soundMap.end())
	{
		throw std::runtime_error("Sound " + key + " not found!");
	}
	//(*iterator).second returns the value of an iterator
	return (*it).second;
}

//need to delete the instance pointer on game end too
void CSoundAssetManager::Terminate()
{
	unloadSounds();
	delete CSoundAssetManagerInstance;
	CSoundAssetManagerInstance = nullptr;
}

void CSoundAssetManager::unloadSounds()
{
	//delete model objects from the heap
	SoundMap::iterator it;
	for (it = Instance().soundMap.begin(); it != Instance().soundMap.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
}