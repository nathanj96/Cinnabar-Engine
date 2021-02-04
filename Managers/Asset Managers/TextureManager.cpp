#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::textureManagerInstance = nullptr;

TextureManager::TextureManager()
{
	//I can't make this assignment if it's a const string?
	defaultPath = "Textures/";
}

void TextureManager::loadTexture(MapKey textureKey, std::string textureFilename)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	TextureMap::iterator it = Instance().textureMap.find(textureKey);
	if (it != Instance().textureMap.end())
	{
		throw std::runtime_error("Texture " + textureKey + " already loaded!");
	}
	else
	{
		std::string insertPath = Instance().defaultPath + textureFilename;
		//Texture constructor specifically calls for a C-string
		Texture* newTexture = new Texture(insertPath.c_str());
		Instance().textureMap.insert(KeyTexturePair(textureKey, newTexture));
	}
}

void TextureManager::loadTexture(MapKey textureKey, unsigned char redVal, unsigned char blueVal, unsigned char greenVal)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	TextureMap::iterator it = Instance().textureMap.find(textureKey);
	if (it != Instance().textureMap.end())
	{
		throw std::runtime_error("Texture " + textureKey + " already loaded!");
	}
	else
	{
		//use Texture constructor for RGB values (alpha is implicitly set to 255)
		Texture* newTexture = new Texture(redVal, blueVal, greenVal);
		Instance().textureMap.insert(KeyTexturePair(textureKey, newTexture));
	}
}

void TextureManager::loadFontTexture(MapKey textureKey, std::string textureFilename)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	TextureMap::iterator it = Instance().textureMap.find(textureKey);
	if (it != Instance().textureMap.end())
	{
		throw std::runtime_error("Texture " + textureKey + " already loaded!");
	}
	else
	{
		Texture* newTexture = new Texture(textureFilename.c_str());
		Instance().textureMap.insert(KeyTexturePair(textureKey, newTexture));
	}
}

Texture* TextureManager::getTexture(MapKey textureKey)
{
	//Make sure the texture you're looking for is actually present...
	TextureMap::iterator it = Instance().textureMap.find(textureKey);
	if (it == Instance().textureMap.end())
	{
		throw std::runtime_error("Texture " + textureKey + " not found!");
	}
	//(*iterator).second returns the value of an iterator
	return (*it).second;
}

//need to delete the instance pointer on game end too
void TextureManager::Terminate()
{
	unloadTextures();
	delete textureManagerInstance;
	textureManagerInstance = nullptr;
}

void TextureManager::unloadTextures()
{
	//delete texture objects from the heap
	TextureMap::iterator it;
	for (it = Instance().textureMap.begin(); it != Instance().textureMap.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
}