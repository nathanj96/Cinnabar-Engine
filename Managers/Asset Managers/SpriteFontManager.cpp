#include "SpriteFontManager.h"
#include "SpriteFont.h"

SpriteFontManager* SpriteFontManager::spriteFontManagerInstance = nullptr;
const int SpriteFontManager::defaultPathLen = Instance().defaultPath.length();
//".tga" = 4 chars
const int SpriteFontManager::fileExtLen = 4;

SpriteFontManager::SpriteFontManager()
{
	//I can't make this assignment if it's a const string?
	defaultPath = "Fonts/";
}

void SpriteFontManager::unloadSpriteFonts()
{
	//delete sprite font objects from the heap
	SpriteFontMap::iterator it;
	for (it = Instance().fontMap.begin(); it != Instance().fontMap.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
}

void SpriteFontManager::Terminate()
{
	unloadSpriteFonts();
	delete spriteFontManagerInstance;
	spriteFontManagerInstance = nullptr;
}

SpriteFont* SpriteFontManager::getSpriteFont(MapKey spriteFontKey)
{
	//Make sure the sprite font you're looking for is actually present...
	SpriteFontMap::iterator it = Instance().fontMap.find(spriteFontKey);
	if (it == Instance().fontMap.end())
	{
		throw std::runtime_error("Sprite font not found!");
	}
	//(*iterator).second returns the value of an iterator
	return (*it).second;
}

void SpriteFontManager::loadSpriteFont(MapKey spriteFontKey, std::string filename)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	SpriteFontMap::iterator it = Instance().fontMap.find(spriteFontKey);
	if (it != Instance().fontMap.end())
	{
		throw std::runtime_error("Sprite font " + spriteFontKey + " already loaded!");
	}
	else
	{
		std::string insertPath = Instance().defaultPath + filename;
		//ShaderObject constructor specifically calls for a C-string
		SpriteFont* newSpriteFont = new SpriteFont(insertPath.c_str());
		Instance().fontMap.insert(KeySpriteFontPair(spriteFontKey, newSpriteFont));
	}
}