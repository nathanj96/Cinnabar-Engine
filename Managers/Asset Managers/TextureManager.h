//Manager for controlling the loading and retrieval of textures

#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

//forward declaration
class Texture;
class TextureManagerAttorney;

#include <string>
//Map class type that will contain the textures - Using unordered map
//because it allows for quicker direct access of elements
#include <unordered_map>
//for std::string
using namespace std;

//Manager for controlling the loading and retrieval of shaders

class TextureManager
{
	friend class TextureManagerAttorney;
private:
	//Manager-specific typedefs:
	using MapKey = std::string;
	using TextureMap = std::unordered_map<MapKey, Texture*>;
	using KeyTexturePair = std::pair<MapKey, Texture*>;

	//The folder that all texture assets should be placed in. Saving this
	//location allows the convenience of not having to type the full path
	//name out repeatedly
	std::string defaultPath;
	//use strings to access specific textures
	TextureMap textureMap;

	//Singleton setup
	static TextureManager* textureManagerInstance;

	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	~TextureManager() = default;

	static TextureManager& Instance()
	{
		if (!textureManagerInstance)
			textureManagerInstance = new TextureManager;

		return *textureManagerInstance;
	}
	//On game exit, unload all textures
	static void unloadTextures();

	/**********************************************************************************************//**
	* \fn	static void TextureManager::Terminate();
	* \ingroup TEXTUREMANAGER
	* \brief	Called when the game ends. Unloads all textures.
	**************************************************************************************************/
	static void Terminate();
public:
	/**********************************************************************************************//**
	 * \fn	static Texture* TextureManager::getTexture(MapKey textureKey);
	 * \ingroup TEXTUREMANAGER
	 * \brief	Used to retrieve a given Texture.
	 *
	 * \param 	textureKey	The key associated with the Texture when it was loaded.
	 *
	 * \returns	The Texture with the given key. Throws an error if the key is not found.
	 **************************************************************************************************/
	static Texture* getTexture(MapKey textureKey);

	/**********************************************************************************************//**
	 * \fn	static void TextureManager::loadTexture(MapKey textureKey, std::string textureFilename);
	 * \ingroup TEXTUREMANAGER
	 * \brief	Loads a given .tga texture. The texture is associated with the key textureKey for future retrieval.
	 *
	 * \note Cinnabar Engine only supports .tga texture files for import.
	 *
	 * \param 	textureKey	 	The texture key.
	 * \param 	textureFilename	Filename of the texture file. Specify the entire filename with its extension, as such:
	 *							\code
	 *								 {
	 *								 TextureManager::loadTexture("newTexture", "texture1.azul");
	 *								 }
	 *							\endcode
	 **************************************************************************************************/
	static void loadTexture(MapKey textureKey, std::string textureFilename);

	/**********************************************************************************************//**
	 * \fn	static void TextureManager::loadTexture(MapKey textureKey, unsigned char redVal, unsigned char blueVal, unsigned char greenVal);
	 * \ingroup TEXTUREMANAGER
	 * \brief	Loads a solid color texture using the RGB values provided. The texture is associated with the
	 * 			key textureKey for future retrieval.
	 *
	 * \param 	textureKey	The texture key.
	 * \param 	redVal	  	The red value, from 0 to 255.
	 * \param 	blueVal   	The blue value, from 0 to 255.
	 * \param 	greenVal  	The green value, from 0 to 255.
	 **************************************************************************************************/

	static void loadTexture(MapKey textureKey, unsigned char redVal, unsigned char blueVal, unsigned char greenVal);

	/**********************************************************************************************//**
	 * \fn	static void TextureManager::loadFontTexture(MapKey textureKey, std::string textureFilename);
	 * \ingroup TEXTUREMANAGER
	 * \brief	Loads a given .tga texture to be used by a SpriteFont. The texture is associated with the 
	 * 			key textureKey for future retrieval.
	 *
	 * \note Cinnabar Engine only supports .tga texture files for import.
	 * \note Sprite fonts should be placed in the Fonts folder, then loaded <b>only<\b> with this function.
	 *
	 * \param 	textureKey	 	The texture key.
	 * \param 	textureFilename	Filename of the texture file. Specify the entire filename with its extension, 
	 * 							as well as the Fonts folder prefix, as such:
	 *							\code
	 *								 {
	 *								 TextureManager::loadFontTexture("newFontTexture", "Fonts/TestFont.azul");
	 *								 }
	 *							\endcode
	 **************************************************************************************************/
	static void loadFontTexture(MapKey textureKey, std::string textureFilename);
};

#endif TEXTURE_MANAGER