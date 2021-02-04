
#ifndef SPRITE_FONT_MANAGER
#define SPRITE_FONT_MANAGER

#include <string>
using namespace std;
#include <unordered_map>

class SpriteFont;
class SpriteFontManagerAttorney;

class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;
private:
	using MapKey = std::string;
	using SpriteFontMap = std::unordered_map<MapKey, SpriteFont*>;
	using KeySpriteFontPair = std::pair<MapKey, SpriteFont*>;

	std::string defaultPath;
	SpriteFontMap fontMap;

	//Singleton setup
	static SpriteFontManager* spriteFontManagerInstance;

	SpriteFontManager();
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator=(const SpriteFontManager&) = delete;
	~SpriteFontManager() = default;

	static SpriteFontManager& Instance()
	{
		if (!spriteFontManagerInstance)
			spriteFontManagerInstance = new SpriteFontManager;

		return *spriteFontManagerInstance;
	}

	static void unloadSpriteFonts();
	/**********************************************************************************************//**
	* \fn	static void SpriteFontManager::Terminate();
	* \ingroup SPRITEFONTMANAGER
	* \brief	Called when the game ends. Unloads all sprite fonts. User should not have access to or
	* 			modify.
	**************************************************************************************************/
	static void Terminate();

public:
	//used by SpriteFont constructor to take a given file path and extract just the name of the file from it
	static const int defaultPathLen;
	static const int fileExtLen;

	/**********************************************************************************************//**
	* \fn	static SpriteFont* SpriteFontManager::getSpriteFont(MapKey spriteFontKey);
	* \ingroup SPRITEFONTMANAGER
	* \brief	Used to retrieve a given SpriteFont.
	*
	* \param 	spriteFontKey	The key associated with the SpriteFont when it was loaded.
	*
	* \returns	The SpriteFont with the given key. Throws an error if the key is not found.
	**************************************************************************************************/
	static SpriteFont* getSpriteFont(MapKey spriteFontKey);

	/**********************************************************************************************//**
	* \fn	static void SpriteFontManager::loadSpriteFont(MapKey spriteFontKey, std::string filename);
	* \ingroup SPRITEFONTMANAGER
	* \brief	Loads a given sprite font. The sprite font is associated with the key spriteFontKey for future retrieval.
	*
	* \param 	spriteFontKey	The sprite font key.
	* \param 	modelFilename	Filename of the sprite font file. This parameter must match the spriteFontKey, as well
	* 							as the key of a previously loaded Texture, in order to work. For example.
	*							\code
	*								 {
	*									TextureManager::loadFontTexture("TestFont", "Fonts/TestFont.tga");
	*									SpriteFontManager::loadSpriteFont("TestFont", "TestFont");
	*								 }
	*							\endcode
	**************************************************************************************************/
	static void loadSpriteFont(MapKey spriteFontKey, std::string filename);
};

#endif SPRITE_FONT_MANAGER